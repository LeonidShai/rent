#ifndef FILEWORKER_H
#define FILEWORKER_H

#include <QString>
#include "DataKeeper.h"

class FileWorker
{
public:
    FileWorker(const QString& fileName);
    ~FileWorker();

    FileWorker(const FileWorker& fileWorker) = delete;
    FileWorker& operator=(const FileWorker& fileWorker) = delete;

    bool writeToFile(const DataKeeper& dataKeeper);
    void readFromFile();

private:
    QString m_fileName;

    void init();
};

#endif // FILEWORKER_H
