#ifndef CPLAYINGLOG_H
#define CPLAYINGLOG_H

#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDateTime>
#include "cqtreewidget.h"

class CplayingLog
{
public:
    CplayingLog();
    ~CplayingLog();
    void readHistoryFromLog(CQTreeWidget *playListWidget);
    void writeHistoryToLog(CQTreeWidget *playListWidget);
private:
    QXmlStreamWriter *m_streamWriter {};
    QXmlStreamReader *m_streamReadter {};
    QString m_playingLog {"./playHistory.xml"};
};

#endif // CPLAYINGLOG_H
