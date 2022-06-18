#include "FileWorker.h"
#include "Logger.h"
#include "DataKeeper.h"

#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

FileWorker::FileWorker(const QString& fileName):
    m_fileName(fileName)
{
    init();
}

FileWorker::~FileWorker()
{

}

bool FileWorker::writeToFile(const DataKeeper& dataKeeper)
{
    QFile file;
    file.setFileName(m_fileName);
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << QString("File on write step was not opened").arg(m_fileName);
        return false;
    }

    QTextStream out(&file);
    out << QDateTime::currentDateTime().toString("dd-MM-yyyy") << ";"
        << QString::number(dataKeeper.dayLight()) << ";"
        << QString::number(dataKeeper.nightLight()) << ";"
        << QString::number(dataKeeper.coldWater()) << ";"
        << QString::number(dataKeeper.coldWater2()) << ";"
        << QString::number(dataKeeper.hotWater()) << ";"
        << QString::number(dataKeeper.gaz()) << "\n";
    file.flush();
    file.close();

    return true;
}

void FileWorker::readFromFile()
{
    QFile file;
    file.setFileName(m_fileName);
}

void FileWorker::init()
{
    QFileInfo fileInfo(m_fileName);
    if (!fileInfo.exists())
    {
        QFile file;
        file.setFileName(m_fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug() << QString("File %1 on init step was not opened").arg(m_fileName);
            return;
        }

        QTextStream out(&file);
        out << "Date" << ";"
            << "DayLight" << ";"
            << "NightLight" << ";"
            << "ColdWater_1" << ";"
            << "ColdWater_2" << ";"
            << "HotWater" << ";"
            << "Gaz" << "\n";
        file.flush();
        file.close();
    }
}
