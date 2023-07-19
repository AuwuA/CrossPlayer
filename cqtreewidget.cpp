#include "cqtreewidget.h"

CQTreeWidget::CQTreeWidget(QWidget *parent) : QTreeWidget{parent}
{
//    this->setStyleSheet("QWidget{background-color: rgb(49, 49, 49);}"
//                        "QTreeWidget::item{height: 20;}"
//                        "QTreeWidget{background-color: rgb(49, 49, 49);"
//                        "\nfont: 20px 'Microsoft YaHei';\ncolor: rgb(0, 255, 255);}"
//                        "QTreeView::arrow{background-color:white ;}");

//    const QString VSCROLLBAR_STYLE =
//        "QTreeWidget{background: #1d1d1d;border: 1px solid #3c3c3c;border-radius: 4px;color:#ffffff;}"
//        "QScrollBar:vertical{margin:0px 0px 0px 0px; background-color:rgb(255,255,255,100); border: 0px; width:5px;}"
//        "QScrollBar:horizontal{margin:0px 0px 0px 0px; background-color:rgb(255,255,255,100); border: 0px; width:5px;}"
//        // 滑块颜色
//        "QScrollBar::handle:vertical{ background-color: white; width: 5px; }"
//        "QScrollBar::add-page:vertical{ background-color: black; }"
//        "QScrollBar::sub-page:vertical{ background-color: black; }"
//        "QScrollBar::sub-line:vertical{ subcontrol-origin: margin; border: 0px solid red; height:5px; }"
//        "QScrollBar::up-arrow:vertical{subcontrol-origin: margin; background-color: blue; height:5px;}"
//        "QScrollBar::down-arrow:vertical{ background-color: yellow; }"
//        "QScrollBar::add-line:vertical{ subcontrol-origin: margin; border: 1px solid green; height:5px;}";

const QString VSCROLLBAR_STYLE{
                               "QTreeWidget{background: #1d1d1d;border: 1px solid #3c3c3c;border-radius: 4px;color:#ffffff;}"
                               "QScrollBar:vertical{margin:0px 0px 0px 0px; background-color:rgb(255,255,255); border: 0px; width:5px;}"
                               "QScrollBar:horizontal{margin:0px 0px 0px 0px; background-color:rgb(255,255,255); border: 0px; width:5px;}"
                               "QScrollBar::handle:vertical{ background-color: white; width: 5px; }"
                               "QScrollBar::add-page:vertical{ background-color: black; }"
                               "QScrollBar::sub-page:vertical{ background-color: black; }"
};
    this->setStyleSheet(VSCROLLBAR_STYLE);

    this->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->setHeaderHidden(true);
    iniTreeHeader();
    createActions();
    connectSignalAndSlot();
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &CQTreeWidget::customContextMenuRequested, this, &CQTreeWidget::do_showMenu);
}

void CQTreeWidget::createActions()
{
    m_actAddFiles = new QAction{this};
    m_actAddFiles->setText("添加视频文件");
    m_actAddFolder = new QAction{this};
    m_actAddFolder->setText("添加文件夹");
    m_actRemoveFile = new QAction{this};
    m_actRemoveFile->setText("移除当前文件");
    m_actRemoveAll = new QAction{this};
    m_actRemoveAll->setText("移除所有文件");
    m_actSortByNameAcs = new QAction{this};
    m_actSortByNameAcs->setText("按文件名升序排序");
    m_actSortByNameDes = new QAction{this};
    m_actSortByNameDes->setText("按文件名降序排序");
    m_actSortBySizeAcs = new QAction{this};
    m_actSortBySizeAcs->setText("按时长升序排序");
    m_actSortBySizeDes = new QAction{this};
    m_actSortBySizeDes->setText("按时长降序排序");
}

void CQTreeWidget::iniTreeHeader()
{
//    this->clear();
//    this->setColumnCount(3);
//    QTreeWidgetItem *headerItem{new QTreeWidgetItem};

//    headerItem->setText(static_cast<int>(treeColNum::colName), "文件");
//    headerItem->setText(static_cast<int>(treeColNum::colTime), "时长");
//    headerItem->setText(static_cast<int>(treeColNum::colSize), "大小");
//    headerItem->setTextAlignment(static_cast<int>(treeColNum::colName), Qt::AlignLeft | Qt::AlignBottom);
//    headerItem->setTextAlignment(static_cast<int>(treeColNum::colTime), Qt::AlignLeft | Qt::AlignBottom);
//    headerItem->setTextAlignment(static_cast<int>(treeColNum::colSize), Qt::AlignLeft | Qt::AlignBottom);
//    setItemFontPointSize(headerItem, 8);
//    this->setHeaderItem(headerItem);

    this->clear();
    this->setColumnCount(3);
    QTreeWidgetItem *headerItem{new QTreeWidgetItem};

    headerItem->setText(static_cast<int>(treeColNum::colName), "文件");
    headerItem->setText(static_cast<int>(treeColNum::colTime), "时长");
    headerItem->setTextAlignment(static_cast<int>(treeColNum::colName), Qt::AlignLeft | Qt::AlignBottom);
    headerItem->setTextAlignment(static_cast<int>(treeColNum::colTime), Qt::AlignLeft | Qt::AlignBottom);
    setItemFontPointSize(headerItem, 8);
    this->setHeaderItem(headerItem);
}

QTreeWidgetItem *CQTreeWidget::getParentItem(const QString &fileFullName)
{
    for (int var {}; var < this->topLevelItemCount(); ++var) {
        if (topLevelItem(var)->data(static_cast<int>(treeColNum::colName), Qt::UserRole).toString() == fileFullName) {
            return topLevelItem(var);
        }
    }

    QStringList strLst {fileFullName.split("/")};
    QString finalName{strLst.back()};

    QTreeWidgetItem *topItem {new QTreeWidgetItem{static_cast<int>(treeItemType::itemFolder)}};
    topItem->setText(static_cast<int>(treeColNum::colName), finalName);

    topItem->setData(static_cast<int>(treeColNum::colName), Qt::UserRole, fileFullName);

    topItem->setTextAlignment(static_cast<int>(treeColNum::colName), Qt::AlignLeft | Qt::AlignBottom);
    setItemFontPointSize(topItem, 8);
    this->addTopLevelItem(topItem);
    return topItem;
}

void CQTreeWidget::addItemFromNameLst(const QStringList &fileNameLst)
{
    for (qsizetype i {}; i < fileNameLst.size(); ++i) {
        QFileInfo fileInfo(fileNameLst.at(i));
        QTreeWidgetItem *parItem {getParentItem(fileInfo.absolutePath())};
        QTreeWidgetItem *item{new QTreeWidgetItem{static_cast<int>(treeItemType::itemVideo)}};

        auto findSameVideoItem{[](QTreeWidgetItem *tmpParaItem,const  QStringList &strList, qsizetype index)-> bool{
                for (qsizetype j{}; j < tmpParaItem->childCount(); j++) {
                    if (tmpParaItem->child(j)->data(static_cast<int>(treeColNum::colName), Qt::UserRole).toString() == strList.at(index)) {
                        return true;
                    }
                }
                return false;
            }
        };
        if (findSameVideoItem(parItem, fileNameLst, i)) {
            delete item;
            item = nullptr;
            continue;
        }

        QMediaPlayer mediaPlayer{this};
        mediaPlayer.setSource(QUrl::fromLocalFile(fileNameLst.at(i)));
        mediaPlayer.stop();


        QTime tmpTime{0, 0, 0};
        tmpTime = tmpTime.addMSecs(static_cast<int>(mediaPlayer.duration()));
        QString timeStr {tmpTime.toString("hh时mm分ss秒")};

        qint64 totalTime {mediaPlayer.duration()};

        item->setText(static_cast<int>(treeColNum::colName), fileInfo.baseName());
        item->setData(static_cast<int>(treeColNum::colName), Qt::UserRole, fileNameLst.at(i));
        item->setText(static_cast<int>(treeColNum::colTime), timeStr);
        item->setData(static_cast<int>(treeColNum::colTime), Qt::UserRole, totalTime);
        // 初始化已播放的时间为0
        item->setData(static_cast<int>(treeColNum::colTime), Qt::UserRole + 1, 0);

//        QString sizeStr{};
//        qint64 totalSize {fileInfo.size()};

//        if (totalSize < 1024) {
//            sizeStr = QString::number(static_cast<int>(totalSize)) + " bytes";
//        } else if(totalSize >= 1024 && totalSize < 1024 * 1024) {
//            sizeStr = QString::number(static_cast<int>(totalSize / 1024)) + " K " + QString::number(static_cast<int>(totalSize % 1024)) + " bytes";
//        } else if(totalSize >= 1024 * 1024 && totalSize < 1024 * 1024 * 1024) {
//            sizeStr = QString::number(static_cast<int>(totalSize / (1024 * 1024))) + " M " +
//                      QString::number(static_cast<int>(totalSize % (1024 * 1024) / 1024)) + " K " +
//                      QString::number(static_cast<int>(totalSize / (1024 * 1024 * 1024))) + " bytes";
//        } else if (totalSize >= 1024 * 1024 * 1024) {
//            sizeStr = QString::number(static_cast<int>(totalSize / (1024 * 1024 * 1024))) + " G " +
//                      QString::number(static_cast<int>(totalSize % (1024 * 1024 * 1024) / (1024 * 1024))) + " M " +
//                      QString::number(static_cast<int>(totalSize % (1024 * 1024 * 1024)) % (1024 * 1024) / (1024)) + " K " +
//                      QString::number(static_cast<int>(totalSize % 1024)) + " bytes";
//        }
//        item->setText(static_cast<int>(treeColNum::colSize), sizeStr);
//        item->setData(static_cast<int>(treeColNum::colSize), Qt::UserRole, totalSize);



        setItemFontPointSize(item, 8);

        parItem->addChild(item);
        parItem->setExpanded(true);
    }
}

void CQTreeWidget::connectSignalAndSlot()
{
    connect(m_actAddFiles, &QAction::triggered, this, &CQTreeWidget::do_addVideoFiles);
    connect(m_actAddFolder, &QAction::triggered, this, &CQTreeWidget::do_addVideoFolder);
    connect(m_actRemoveFile, &QAction::triggered, this, &CQTreeWidget::do_removeCurrentItem);
    connect(m_actRemoveAll, &QAction::triggered, this, &CQTreeWidget::do_removeAllItem);
    connect(m_actSortByNameAcs, &QAction::triggered, this, &CQTreeWidget::do_SortByNameAcs);
    connect(m_actSortByNameDes, &QAction::triggered, this, &CQTreeWidget::do_SortByNameDes);
    connect(m_actSortBySizeAcs, &QAction::triggered, this, &CQTreeWidget::do_SortBySizeAcs);
    connect(m_actSortBySizeDes, &QAction::triggered, this, &CQTreeWidget::do_SortBySizeDes);
}

void CQTreeWidget::setItemFontPointSize(QTreeWidgetItem *item, int pointSize)
{
    QFont font {item->font(static_cast<int>(treeColNum::colName))};
    font.setPointSize(8);
    item->setFont(static_cast<int>(treeColNum::colName), font);
    item->setFont(static_cast<int>(treeColNum::colTime), font);
    // item->setFont(static_cast<int>(treeColNum::colSize), font);
}

void CQTreeWidget::do_addVideoFiles()
{
    QStringList fileList {QFileDialog::getOpenFileNames(this, "打开视频文件","/home", "Videos (*.MP4 *.mp4 *.WAV *.wav)")};
    if (fileList.isEmpty()) {
        return;
    }
    addItemFromNameLst(fileList);
}

void CQTreeWidget::do_addVideoFolder()
{
    QString floderObj {QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks)};
    if (floderObj.isEmpty()) {
        return;
    }
    QDir dirObj{floderObj};
    QStringList videoList{dirObj.entryList(QDir::Files, QDir::NoSort)};
    for (qsizetype i {}; i < videoList.size(); ++i) {
        if (!(videoList.at(i).endsWith(".MP4", Qt::CaseInsensitive) || videoList.at(i).endsWith("*.WAV", Qt::CaseInsensitive))) {
            videoList.remove(i);
            i--;
            continue;
        }
        videoList[i] = floderObj + "/" + videoList.at(i);
    }
    if (!videoList.isEmpty()) {
        addItemFromNameLst(videoList);
    }
}

void CQTreeWidget::do_showMenu(const QPoint &pos)
{
    Q_UNUSED(pos)
    CMenu *menu {new CMenu{this}};
//    menu->setStyleSheet("QMenu {"
//    "background-color: rgb(57, 65, 69);"
//    "color: rgb(255,255,255);"
//    "border: 1px solid rgb(172, 172, 172);"
//    "border-radius: 3px; }"
//    "QMenu::item {"
//    "background-color: transparent;"
//    "border-bottom: 1px solid rgb(172, 172, 172);"
//    "padding:5px 10px;"
//    "margin:0px 0px; }"
//    "QMenu::item:selected {"
//    "background-color: rgb(76, 71, 169); }");
    menu->addAction(m_actAddFiles);
    //menu->addSeparator();
    menu->addAction(m_actAddFolder);
    //menu->addSeparator();
    menu->addAction(m_actRemoveFile);
    //menu->addSeparator();
    menu->addAction(m_actRemoveAll);
    //menu->addSeparator();
    menu->addAction(m_actSortByNameAcs);
    //menu->addSeparator();
    menu->addAction(m_actSortByNameDes);
    //menu->addSeparator();
    menu->addAction(m_actSortBySizeAcs);
    //menu->addSeparator();
    menu->exec(QCursor::pos());
    delete menu;
}

void CQTreeWidget::do_removeCurrentItem()
{
    QTreeWidgetItem *item{this->currentItem()};
    if (nullptr == item) {
        return;
    }
    if (item->type() == static_cast<int>(treeItemType::itemFolder)) {
        int count {item->childCount()};
        for (int i = 0; i < count; ++i) {
            QTreeWidgetItem *tmpChild{item->child(i)};
            item->removeChild(tmpChild);
            delete tmpChild;
        }
        this->takeTopLevelItem(this->indexOfTopLevelItem(item));
        delete item;
        return;
    }
    QTreeWidgetItem *parent {item->parent()};
    parent->removeChild(item);
    delete item;
}

void CQTreeWidget::do_removeAllItem()
{
    int count{this->topLevelItemCount()};
    for (int i = 0; i < count; ++i) {
        QTreeWidgetItem *item {this->takeTopLevelItem(0)};
        this->setCurrentItem(item);
        do_removeCurrentItem();
    }
}

void CQTreeWidget::do_SortByNameAcs()
{
    QTreeWidgetItem *topItem{this->currentItem()};
    if (nullptr == topItem || 0 == this->topLevelItemCount()) {
        return;
    }
    this->sortItems(static_cast<int>(treeColNum::colName), Qt::AscendingOrder);
    int count{this->topLevelItemCount()};
    for (int i = 0; i < count; ++i) {
        this->topLevelItem(i)->sortChildren(static_cast<int>(treeColNum::colName), Qt::AscendingOrder);
    }
}

void CQTreeWidget::do_SortByNameDes()
{
    QTreeWidgetItem *topItem{this->currentItem()};
    if (nullptr == topItem || 0 == this->topLevelItemCount()) {
        return;
    }
    this->sortItems(static_cast<int>(treeColNum::colName), Qt::DescendingOrder);
    int count{this->topLevelItemCount()};
    for (int i = 0; i < count; ++i) {
        this->topLevelItem(i)->sortChildren(static_cast<int>(treeColNum::colName), Qt::DescendingOrder);
    }
}

void CQTreeWidget::do_SortBySizeAcs()
{
    int count{this->topLevelItemCount()};
    for (int i = 0; i < count; ++i) {
        this->topLevelItem(i)->sortChildren(static_cast<int>(treeColNum::colTime), Qt::AscendingOrder);
    }
}

void CQTreeWidget::do_SortBySizeDes()
{
    int count{this->topLevelItemCount()};
    for (int i = 0; i < count; ++i) {
        this->topLevelItem(i)->sortChildren(static_cast<int>(treeColNum::colTime), Qt::DescendingOrder);
    }
}
