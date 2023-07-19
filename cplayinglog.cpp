#include "cplayinglog.h"

CplayingLog::CplayingLog()
{

}

CplayingLog::~CplayingLog()
{
    if (m_streamWriter != nullptr) {
        delete m_streamWriter;
        m_streamWriter = nullptr;
    }
    if (m_streamReadter != nullptr) {
        delete m_streamReadter;
        m_streamReadter = nullptr;
    }
}

void CplayingLog::readHistoryFromLog(CQTreeWidget *playListWidget)
{
     QFile logFile(m_playingLog);
     if (!logFile.open(QFile::ReadOnly | QFile::Text)) {
         return;
     }
     m_streamReadter = {new QXmlStreamReader{&logFile}};

     QTreeWidgetItem * parentIten {};
     // 一行一行读部分父子节点
     while(!m_streamReadter->atEnd()){
          if( m_streamReadter->readNext() == QXmlStreamReader::StartElement ){
              QXmlStreamAttributes  Attributes  = m_streamReadter->attributes();
              if (m_streamReadter->name().toString() == "DIR") {
                  parentIten = new QTreeWidgetItem{static_cast<int>(treeItemType::itemFolder)};
                  parentIten->setText(static_cast<int>(treeColNum::colName), Attributes.value("LASTDIR").toString());
                  parentIten->setData(static_cast<int>(treeColNum::colName), Qt::UserRole, Attributes.value("LASTDIR").toString());
                  playListWidget->addTopLevelItem(parentIten);
                  parentIten->setExpanded(true);
//                  qDebug()<<Attributes.value("FULLDIR").toString();
//                  qDebug()<<Attributes.value("LASTDIR").toString();
              } else if (m_streamReadter->name().toString() == "PLAYINFO") {
                  QTreeWidgetItem * childItem {new QTreeWidgetItem(static_cast<int>(treeItemType::itemVideo))};
                  childItem->setText(static_cast<int>(treeColNum::colName), Attributes.value("FILENAME").toString());
                  childItem->setData(static_cast<int>(treeColNum::colName), Qt::UserRole, Attributes.value("FULLNAME").toString());

                  childItem->setData(static_cast<int>(treeColNum::colTime), Qt::UserRole, Attributes.value("TOTALTIME").toLongLong());
                  childItem->setData(static_cast<int>(treeColNum::colTime), Qt::UserRole + 1, Attributes.value("PLAYEDTIME").toLongLong());
                  if (nullptr != parentIten) {
                      parentIten->addChild(childItem);
                  }
//                  qDebug()<<Attributes.value("FILENAME").toString();
//                  qDebug()<<Attributes.value("FULLNAME").toString();
//                  qDebug()<<Attributes.value("TOTALTIME").toString();
//                  qDebug()<<Attributes.value("PLAYEDTIME").toString();
              }
          }
     }
}

void CplayingLog::writeHistoryToLog(CQTreeWidget *playListWidget)
{
    QFile logFile(m_playingLog);
    if (!logFile.open(QIODeviceBase::WriteOnly | QIODevice::Truncate)) {
        return;
    }
    m_streamWriter = {new QXmlStreamWriter{&logFile}};
    m_streamWriter->setAutoFormatting(true);
    m_streamWriter->writeStartDocument();
    m_streamWriter->writeStartElement("PLAYHISTORY");
    for (qsizetype i= 0; i < playListWidget->topLevelItemCount(); ++i) {
        auto *parItem{playListWidget->takeTopLevelItem(i)};
        // 最后一级目录
        m_streamWriter->writeStartElement("DIR");
        // 王征路径不带文件名
        m_streamWriter->writeAttribute("FULLDIR", parItem->data(static_cast<int>(treeColNum::colName), Qt::UserRole).toString());
        m_streamWriter->writeAttribute("LASTDIR", parItem->text(static_cast<int>(treeColNum::colName)));
        for (int j = 0; j < parItem->childCount(); ++j) {
            m_streamWriter->writeStartElement("PLAYINFO");
            m_streamWriter->writeAttribute("FILENAME", parItem->child(j)->text(static_cast<int>(treeColNum::colName)));
            m_streamWriter->writeAttribute("FULLNAME", parItem->child(j)->data(static_cast<int>(treeColNum::colName), Qt::UserRole).toString());
            m_streamWriter->writeAttribute("TOTALTIME", parItem->child(j)->data(static_cast<int>(treeColNum::colTime), Qt::UserRole).toString());
            m_streamWriter->writeAttribute("PLAYEDTIME", parItem->child(j)->data(static_cast<int>(treeColNum::colTime), Qt::UserRole + 1).toString());
            m_streamWriter->writeEndElement();
        }
        m_streamWriter->writeEndElement();
    }
    m_streamWriter->writeEndElement();
    m_streamWriter->writeEndDocument();
    logFile.close();
}
