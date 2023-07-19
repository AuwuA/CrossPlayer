#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CplayingLog playlog;
    playlog.readHistoryFromLog(ui->playListTreeWidget);
    iniGraph();
    m_player = new QMediaPlayer{this};
    m_player->stop();
    QAudioOutput *audoOutPut {new QAudioOutput{this}};
    m_player->setAudioOutput(audoOutPut);
    m_player->setVideoOutput(ui->videoWidget);
    connectSignalAndSlots();
    ui->videoWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    // this->setWindowFlag(Qt::FramelessWindowHint);
}

MainWindow::~MainWindow()
{
    CplayingLog playlog;
    playlog.writeHistoryToLog(ui->playListTreeWidget);
    delete ui;
}

void MainWindow::do_showSignal(bool isShowing)
{
     if (isShowing && ui->playListWidget->isHidden()) {
        m_isHidePlayList = false;
         ui->playListWidget->show();
     } else if (!isShowing && !(ui->playListWidget->isHidden())) {
         m_isHidePlayList = true;
         ui->playListWidget->hide();
     }
}

void MainWindow::do_startPlay(bool playingState)
{
     QTreeWidgetItem *itemFile {ui->playListTreeWidget->currentItem()};
     if (nullptr == itemFile || itemFile->type() == static_cast<int>(treeItemType::itemFolder)) {
         qobject_cast<CPlayButton*>(sender())->setPlayState(false);
         return;
     }
     // 如果还未播放过本视频则初始化播源，设置进度条为0
     if (m_player->position() == 0) {
         QString filePath {itemFile->data(static_cast<int>(treeColNum::colName), Qt::UserRole).toString()};
         m_player->setSource(QUrl::fromLocalFile(filePath));
         ui->sliderDura->setMinValue(0);
         ui->sliderDura->setMaxValue(m_player->duration());
         ui->sliderDura->setValue(0);
     }

     // 从新播放
     if (m_player->position() == m_player->duration()) {
         m_player->setPosition(0);
         ui->sliderDura->setValue(0);
         m_player->play();
         itemFile->setData(static_cast<int>(treeColNum::colTime), Qt::UserRole + 1, 0);
         return;
     }

     // 如果正在播放则停止播放反之开始播放,并记录当前播放位置
     if (!playingState) {
         m_player->pause();
         itemFile->setData(static_cast<int>(treeColNum::colTime), Qt::UserRole + 1, m_player->position());
         return;
     }
     m_player->play();




     /************************************没问题*****************************************/

//     if (m_player->position() == 0) {
//         QString filePath {itemFile->data(static_cast<int>(treeColNum::colName), Qt::UserRole).toString()};
//         m_player->setSource(QUrl::fromLocalFile(filePath));
//         ui->sliderDura->setMinValue(0);
//         ui->sliderDura->setMaxValue(m_player->duration());
//         ui->sliderDura->setValue(0);
//     }
//     if (m_player->isPlaying()) {
//         qDebug() << "m_player->position() == " << m_player->position();
//         itemFile->setData(static_cast<int>(treeColNum::colTime), Qt::UserRole + 1, m_player->position());
//         m_player->pause();
//     } else {
//         m_player->play();
//     }

}

void MainWindow::do_stopClicked()
{
     saveCrrentVideoPlayedTime();
     m_player->stop();
     ui->btnPlay->setPlayState(false);
}

void MainWindow::do_preClicked()
{
     QTreeWidgetItem *item {saveCrrentVideoPlayedTime()};
     if (nullptr == item) {
         return;
     }

     QTreeWidgetItem *parentItem{item->parent()};
     if (nullptr == parentItem) {
         return;
     }
     int index {parentItem->indexOfChild(item)};
     if (index > 0) {
         m_player->stop();
         item = parentItem->child(index - 1);
         ui->playListTreeWidget->setCurrentItem(item);
         m_player->setSource(QUrl::fromLocalFile(item->data(static_cast<int>(treeColNum::colName),Qt::UserRole).toString()));
         m_player->setPosition(item->data(static_cast<int>(treeColNum::colTime),Qt::UserRole + 1).toLongLong());
         ui->btnPlay->setPlayState(true);
         m_player->play();
//         ui->playListTreeWidget->setCurrentItem(item);
//         do_startPlay(true);
     }
}

void MainWindow::do_nextClicked()
{
     // 先把烟来的时间读出来，当现在的前面有数据时在把现在的数据写景区，否则把原来的数据写进去

     QTreeWidgetItem *item {saveCrrentVideoPlayedTime()};
     if (nullptr == item) {
         return;
     }
     QTreeWidgetItem *parentItem{item->parent()};
     if (nullptr == parentItem) {
         return;
     }
     int index {parentItem->indexOfChild(item)};
     if (index >= 0 && index < parentItem->childCount() - 1) {
         m_player->stop();
         item = parentItem->child(index + 1);
         ui->playListTreeWidget->setCurrentItem(item);
         m_player->setSource(QUrl::fromLocalFile(item->data(static_cast<int>(treeColNum::colName),Qt::UserRole).toString()));
         m_player->setPosition(item->data(static_cast<int>(treeColNum::colTime),Qt::UserRole + 1).toLongLong());
         ui->btnPlay->setPlayState(true);
         m_player->play();
     }
}

void MainWindow::do_muteClicked(bool isNeedMute)
{
     if (!m_player->audioOutput()->isMuted() && m_player->audioOutput()->volume() != 0 && isNeedMute) {
         m_player->audioOutput()->setMuted(isNeedMute);
     } else {
         m_player->audioOutput()->setMuted(isNeedMute);
     }
}

void MainWindow::do_positionChanged(qint64 pos)
{
     ui->sliderDura->setValue(pos);
     QTime timeOne{0, 0, 0};
     timeOne = timeOne.addMSecs(static_cast<int>(pos));
     QTime timeTwo{0, 0, 0};
     timeTwo = timeTwo.addMSecs(m_player->duration());
     ui->labDura->setText(timeOne.toString("hh:mm:ss") + "/" + timeTwo.toString("hh:mm:ss"));
     if (pos == m_player->duration()) {
         ui->btnPlay->setPlayState(false);
     }
}

void MainWindow::do_durationChanged(qint64 duration)
{
     ui->sliderDura->setMinValue(0);
     ui->sliderDura->setMaxValue(duration);
     ui->sliderDura->setValue(0);
}

void MainWindow::do_doSliderDurationChanged(qint64 value)
{
     m_player->setPosition(value);
}

void MainWindow::do_doSliderVolumeChanged(qint64 value)
{
     if (value > 10000 || value < 0) {
         return;
     }
     m_player->audioOutput()->setVolume(static_cast<float>(value / 10000.0));
     if (0 == value) {
         ui->btnMute->setMuteState(true);
         ui->btnMute->repaint();
     } else {
         ui->btnMute->setMuteState(false);
         ui->btnMute->repaint();
     }
}

//void MainWindow::do_playbackStateChanged(QMediaPlayer::PlaybackState state)
//{
//     bool curState {state == QMediaPlayer::PlayingState ? true : false};
//     ui->btnStop->setEnabled(!curState);
//}

void MainWindow::iniGraph()
{
    ui->splitter->setStretchFactor(0,85);
    ui->splitter->setStretchFactor(1,15);
    this->setWindowTitle("CrossPlayer");

    // 播放进度条
    ui->sliderDura->setMaxValue(100);
    ui->sliderDura->setMinValue(0);
    ui->sliderDura->setValue(0);

    // 声音进度条
    ui->sliderVol->setMinValue(0);
    ui->sliderVol->setMaxValue(10000);
    ui->sliderVol->setValue(6700);

    // 防止键盘按下左侧播放列表跟着变
    ui->playListTreeWidget->setFocusPolicy(Qt::NoFocus);
    this->setMouseTracking(true);
    this->setAcceptDrops(true);
     // ui->playListTreeWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);
     // ui->playListWidget->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

void MainWindow::connectSignalAndSlots()
{
    connect(ui->btnShowHide, &CShowHideButton::isNeedShow, this, &MainWindow::do_showSignal);
    connect(ui->btnPlay, &CPlayButton::playingState, this, &MainWindow::do_startPlay);
    connect(m_player, &QMediaPlayer::positionChanged, this, &MainWindow::do_positionChanged);
    connect(m_player, &QMediaPlayer::durationChanged, this, &MainWindow::do_durationChanged);
    connect(ui->btnStop, &CStopButton::buttonClicked, this, &MainWindow::do_stopClicked);
    connect(ui->btnPrev, &CPreButton::buttonClicked, this, &MainWindow::do_preClicked);
    connect(ui->btnNext, &CNextButton::buttonClicked, this, &MainWindow::do_nextClicked);
    connect(ui->sliderDura, &CSlider::valueChanged, this, &MainWindow::do_doSliderDurationChanged);
    connect(ui->sliderVol, &CSlider::valueChanged, this, &MainWindow::do_doSliderVolumeChanged);
    connect(ui->btnMute, &CMuteButton::isNeedMute, this, &MainWindow::do_muteClicked);
    connect(m_player, &QMediaPlayer::playbackStateChanged, this, &MainWindow::do_playbackStateChanged);
    // connect(m_player,&QMediaPlayer::playbackStateChanged, this, &MainWindow::do_playbackStateChanged);
}

QTreeWidgetItem * MainWindow::saveCrrentVideoPlayedTime()
{
    QString curVideoPath{m_player->source().toLocalFile()};
    if (curVideoPath.isEmpty()) {
         return nullptr;
    }
    QFileInfo fileInfo{curVideoPath};
    QTreeWidgetItem *itemParent {};
    for (int i {}; i < ui->playListTreeWidget->topLevelItemCount(); ++i) {
         QTreeWidgetItem *tmpItem {ui->playListTreeWidget->topLevelItem(i)};
         QString tmpStr{tmpItem->data(static_cast<int>(treeColNum::colName), Qt::UserRole).toString()};
         if (fileInfo.absolutePath() ==  tmpStr) {
             itemParent = tmpItem;
             break;
         }
    }
    // 找当前节点
    if (itemParent != nullptr) {
         for (int i = 0; i < itemParent->childCount(); ++i) {
             if (m_player->source().path() == QUrl::fromLocalFile(itemParent->child(i)->data(static_cast<int>(treeColNum::colName), Qt::UserRole).toString()).path()) {
                 itemParent->child(i)->setData(static_cast<int>(treeColNum::colTime), Qt::UserRole + 1, m_player->position());
                 return itemParent->child(i);
             }
         }
    }
    return nullptr;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (ui->sliderDura->getEnterState() || ui->sliderVol->getEnterState()) {
         QMainWindow::mousePressEvent(event);
         return;
    }
    if (event->buttons() & Qt::LeftButton) {
         m_point = event->globalPosition().toPoint() - this->pos();
    }
    QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (ui->sliderDura->getEnterState() || ui->sliderVol->getEnterState()) {
         QMainWindow::mouseMoveEvent(event);
         return;
    }
    if (event->buttons() & Qt::LeftButton) {

         QPoint tmpPoint {event->globalPosition().toPoint() - m_point};
         this->move(tmpPoint);
         m_point = event->globalPosition().toPoint() -this->pos();
    }
    QMainWindow::mouseMoveEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //ui->playListTreeWidget->setEnabled(false);
    switch (event->key()) {
         // 全屏
    case Qt::Key_Return:
         on_act_fullWindow_triggered();
         ui->userControl->hide();
         ui->playListWidget->hide();
         break;
         // 退出全屏
    case Qt::ExtraButton22:
         on_act_escFullScreen_triggered();
         ui->userControl->show();
         // ui->playListWidget->show();
         if (!m_isHidePlayList) {
             ui->playListWidget->show();
         }
         break;
         // 块进
    case Qt::Key_Right:
    {
         qint64 curPos{m_player->position()};
         m_player->stop();
         ui->sliderDura->setValue(curPos + 200);
         do_doSliderDurationChanged(curPos + 200);
         m_player->play();
    }
         break;
         // 快退Qt::Key_Left
    case Qt::Key_Left:
    {
         qint64 curPos{m_player->position()};
         m_player->stop();
         ui->sliderDura->setValue(curPos - 200);
         do_doSliderDurationChanged(curPos - 200);
         m_player->play();
    }
         // 音量+
    case Qt::Key_Up:
         ui->sliderVol->setValue(ui->sliderVol->getValue() + 100);
         emit ui->sliderVol->valueChanged(ui->sliderVol->getValue());
         break;
         // 音量-
    case Qt::Key_Down:
         ui->sliderVol->setValue(ui->sliderVol->getValue() - 100);
         emit ui->sliderVol->valueChanged(ui->sliderVol->getValue());
         break;
         // 暂停, 播放
    case Qt::AlignTop:
    {
         bool isPlaying {m_player->isPlaying()};
         ui->btnPlay->setPlayState(!isPlaying);
         if (isPlaying) {
             m_player->pause();
         } else {
             m_player->play();
         }
    }
         break;
    case Qt::Key_C:
         if (m_curPlaybackRate >= 5.0) {
             break;
         }
         m_curPlaybackRate += 0.2;
         m_player->setPlaybackRate(m_curPlaybackRate);
         break;
    case Qt::Key_X:
         if (m_curPlaybackRate <= 0.2) {
             break;
         }
         m_curPlaybackRate -= 0.2;
         m_player->setPlaybackRate(m_curPlaybackRate);
         break;
    case Qt::Key_Z:
         m_curPlaybackRate = 1;
         m_player->setPlaybackRate(m_curPlaybackRate);
         break;
// 倍速，C 67         43
//    case Qt::AlignTop:
//    {
//         bool isPlaying {m_player->isPlaying()};
//         ui->btnPlay->setPlayState(!isPlaying);
//         if (isPlaying) {
//             m_player->pause();
//         } else {
//             m_player->play();
//         }
//    }

 // 减速，x 88        58
 //    case Qt::AlignTop:
 //    {
 //         bool isPlaying {m_player->isPlaying()};
 //         ui->btnPlay->setPlayState(!isPlaying);
 //         if (isPlaying) {
 //             m_player->pause();
 //         } else {
 //             m_player->play();
 //         }
 //    }


 // 原速，z 90      5A
 //    case Qt::AlignTop:
 //    {
 //         bool isPlaying {m_player->isPlaying()};
 //         ui->btnPlay->setPlayState(!isPlaying);
 //         if (isPlaying) {
 //             m_player->pause();
 //         } else {
 //             m_player->play();
 //         }
 //    }
    default:
         break;
    }
    return;
    //ui->playListTreeWidget->setEnabled(true);
    QMainWindow::keyPressEvent(event);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    QStringList playList {};
    for (qsizetype i = 0; i < event->mimeData()->urls().size(); ++i) {
         playList.emplace_back(event->mimeData()->urls().at(i).toLocalFile());

    }
    ui->playListTreeWidget->addItemFromNameLst(playList);
}

//void MainWindow::enterEvent(QEnterEvent *event)
//{
//    if (m_player->isPlaying() && ui->userControl->isHidden()) {
//         ui->userControl->show();
//    }
//    if (m_player->isPlaying() && ui->playListWidget->isHidden()) {
//         ui->playListWidget->show();
//    }

//    QMainWindow::enterEvent(event);
//}

//void MainWindow::leaveEvent(QEvent *event)
//{
//    if (m_player->isPlaying() && !(ui->userControl->isHidden())) {
//         ui->userControl->hide();
//    }
//    if (m_player->isPlaying() && !(ui->playListWidget->isHidden())) {
//         ui->playListWidget->hide();
//    }
//    QMainWindow::leaveEvent(event);
//}

void MainWindow::on_playListTreeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column)
    // item为目录类型直接返回
    if (item->type() == static_cast<int>(treeItemType::itemFolder)) {
         return;
    }
    QString filePath {item->data(static_cast<int>(treeColNum::colName),Qt::UserRole).toString()};
    QString curSource {m_player->source().toLocalFile()};
    if (filePath == curSource) {
         return;
    }

    // 点击到新视频，保存当前视频数据，播放新的视频
    // 保存当前视频数据
    saveCrrentVideoPlayedTime();
    // 先停止
    m_player->stop();
    m_player->setSource(QUrl::fromLocalFile(filePath));
    m_player->setPosition(item->data(static_cast<int>(treeColNum::colTime),Qt::UserRole + 1).toLongLong());
    ui->btnPlay->setPlayState(true);
    do_startPlay(true);
}

void MainWindow::do_playbackStateChanged(QMediaPlayer::PlaybackState state)
{
    // 自动播放下一集
    if (state == QMediaPlayer::StoppedState && m_player->position() == m_player->duration()) {
         do_nextClicked();
    }
}


void MainWindow::on_act_Frameless_triggered()
{
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    this->show();
}


void MainWindow::on_videoWidget_customContextMenuRequested(const QPoint &pos)
{
    CMenu *menu {new CMenu{this}};

    menu->addAction(ui->act_Frameless);
    menu->addAction(ui->act_frame);
    menu->addAction(ui->act_fullWindow);
    menu->addAction(ui->act_escFullScreen);
    menu->exec(QCursor::pos());

    delete menu;
}


void MainWindow::on_act_fullWindow_triggered()
{
    if (this->windowState() & Qt::WindowFullScreen) {
         return;
    }
    this->setWindowState(Qt::WindowFullScreen);
}


void MainWindow::on_act_escFullScreen_triggered()
{
    if (this->windowState() & Qt::WindowFullScreen) {
         this->setWindowState(Qt::WindowNoState);
    }
}


void MainWindow::on_act_frame_triggered()
{
    this->setWindowFlags(this->windowFlags() ^ Qt::FramelessWindowHint);
    this->show();
}

