#ifndef CQTREEWIDGET_H
#define CQTREEWIDGET_H

#include <QDebug>
#include <QTime>
#include <QPoint>
#include <QMenu>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QAction>
#include <QFileInfo>
#include <QTreeWidgetItem>
#include <QHeaderView>
#include <QStringList>
#include "cmenu.h"

enum class treeItemType : int {itemFolder = 1001, itemVideo};
enum class treeColNum : int {colName = 0, colTime};
//enum class treeColNum : int {colName = 0, colTime, colSize};

class CQTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    CQTreeWidget(QWidget *parent = nullptr);
    void addItemFromNameLst(const QStringList &fileNameLst);
private:
    void createActions();
    void iniTreeHeader();
    QTreeWidgetItem *getParentItem(const QString &fileFullName);
    void connectSignalAndSlot();
    void setItemFontPointSize(QTreeWidgetItem *item, int pointSize);
private slots:
    void do_addVideoFiles();
    void do_addVideoFolder();
    void do_showMenu(const QPoint &pos);
    void do_removeCurrentItem();
    void do_removeAllItem();
    void do_SortByNameAcs();
    void do_SortByNameDes();
    void do_SortBySizeAcs();
    void do_SortBySizeDes();
private:
    QAction *m_actAddFiles;
    QAction *m_actAddFolder;
    QAction *m_actRemoveFile;
    QAction *m_actRemoveAll;
    QAction *m_actSortByNameAcs;
    QAction *m_actSortByNameDes;
    QAction *m_actSortBySizeAcs;
    QAction *m_actSortBySizeDes;
};

#endif // CQTREEWIDGET_H
