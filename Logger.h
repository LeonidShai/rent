#ifndef LOGGER_H
#define LOGGER_H

#include <QDebug>
#include <QHash>

class QFile;

class Logger
{
public:
    ~Logger();
    static void instance();

    static void writeMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg);
    static void close();

private:
    static bool isInit;
    static QFile logFile;
    static QHash<QtMsgType, QString> contextNames;
};

#endif // LOGGER_H
