#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileInfo>
#include <QMenu>
#include <QPoint>
#include <QMouseEvent>
#include <QMoveEvent>
#include <QSplitter>
#include <QTreeWidgetItem>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMainWindow>
#include <QMimeData>
#include <QDragEnterEvent>
#include "cplayinglog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void do_showSignal(bool isShowing);
    void do_startPlay(bool isPlaying);
    void do_stopClicked();
    void do_preClicked();
    void do_nextClicked();
    void do_muteClicked(bool isNeedMute);
    void do_positionChanged(qint64 pos);
    void do_durationChanged(qint64 duration);
    void do_doSliderDurationChanged(qint64 value);
    void do_doSliderVolumeChanged(qint64 value);
    void on_playListTreeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void do_playbackStateChanged(QMediaPlayer::PlaybackState state);
    // void do_playbackStateChanged(QMediaPlayer::PlaybackState state);
protected:
    void iniGraph();
    void connectSignalAndSlots();
    QTreeWidgetItem *saveCrrentVideoPlayedTime();
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    virtual void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
//    virtual void enterEvent(QEnterEvent *event) Q_DECL_OVERRIDE;
//    virtual void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
    // virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
private slots:
    void on_act_Frameless_triggered();

    void on_videoWidget_customContextMenuRequested(const QPoint &pos);

    void on_act_fullWindow_triggered();

    void on_act_escFullScreen_triggered();

    void on_act_frame_triggered();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *m_player;
    QString m_durationTime;
    QString m_positimeTime;
    QPoint m_point;
    qreal m_curPlaybackRate {1.0};
    bool m_isHidePlayList{false};
};
#endif // MAINWINDOW_H
