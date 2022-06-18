#include "Logger.h"

#include <QFile>
#include <QDateTime>

bool Logger::isInit = false;
QFile Logger::logFile;
QHash<QtMsgType, QString> Logger::contextNames = {
    {QtMsgType::QtDebugMsg, "Debug"},
    {QtMsgType::QtInfoMsg, "Info"},
    {QtMsgType::QtWarningMsg, "Warning"},
    {QtMsgType::QtCriticalMsg, "Critical"},
    {QtMsgType::QtFatalMsg, "Fatal"}
};

Logger::~Logger()
{
    close();
}

void Logger::instance()
{
    if (!isInit)
    {
        logFile.setFileName("Rent.log");
        logFile.open(QIODevice::WriteOnly | QIODevice::Text);

        qInstallMessageHandler(Logger::writeMessage);
        isInit = true;
    }
}

void Logger::writeMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QString message = QString("%1 | %2 | %3 | %4 | %5 | %6\n").
            arg(QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm:ss")).
            arg(Logger::contextNames.value(type)).
            arg(context.line).
            arg(QString(context.file).section('\\', -1)).
            arg(QString(context.function).section('(', -2, -2).section(' ', -1)).
            arg(msg);

    logFile.write(message.toLocal8Bit());
    logFile.flush();
}

void Logger::close()
{
    if (logFile.isOpen())
    {
        qDebug() << "Application Rent is closed";
        logFile.close();
        isInit = false;
    }
}
