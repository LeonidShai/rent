#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QMainWindow>
#include <QSettings>
#include "MainDisplay.h"
#include "Logger.h"
#include "FileWorker.h"

class QSplashScreen;

class MainController
{
public:
    explicit MainController(QSplashScreen* splashScreen);
    ~MainController();

    MainController(const MainController& mainController) = delete;
    MainController& operator=(const MainController& mainController) = delete;

    void saveDataInFile(const DataKeeper& dataKeeper);

private:
    MainDisplay*    m_pMainDisplay;
    QSettings*      m_pSettings;
    FileWorker*     m_pFileWorker;
    DataKeeper      m_dataHandler;
    QSplashScreen*  m_pSplashScreen;

    static const QString DEFAULT_FILENAME;

    void init();
    void saveSettings();
    void loadSettings();
    void showSplashScreenMsg(const int& mstime);
};

#endif // MAINCONTROLLER_H
