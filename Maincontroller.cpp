#include "MainController.h"
#include <QSplashScreen>
#include <QTimer>
#include <QThread>

const QString MainController::DEFAULT_FILENAME = "Readings.csv";

MainController::MainController(QSplashScreen* splashScreen):
    m_pSplashScreen(splashScreen)
{
    int mstime = 1500;
    QTimer::singleShot(mstime, m_pSplashScreen, SLOT(close()));
    init();
    showSplashScreenMsg(mstime);
}

void MainController::saveDataInFile(const DataKeeper& dataKeeper)
{
    m_pFileWorker->writeToFile(dataKeeper);
}

MainController::~MainController()
{
    saveSettings();

    delete m_pSplashScreen;
    delete m_pSettings;
    delete m_pMainDisplay;
    delete m_pFileWorker;
}

void MainController::init()
{
    qDebug() << "Main Controller is started";
    m_pSettings = new QSettings("Settings.ini", QSettings::IniFormat);

    m_pMainDisplay = new MainDisplay(this);
    m_pFileWorker = new FileWorker(DEFAULT_FILENAME);
    m_pMainDisplay->loadSettings(m_pSettings);
    m_pMainDisplay->init();

    QTimer::singleShot(1700, m_pMainDisplay, SLOT(show()));
}

void MainController::saveSettings()
{
    qInfo() << "save settings";
    m_pMainDisplay->saveSettings(m_pSettings);
}

void MainController::loadSettings()
{

}

void MainController::showSplashScreenMsg(const int &mstime)
{
    int i = 1;
    QString pointStr = "*";
    while(i < mstime)
    {
        m_pSplashScreen->showMessage(pointStr, Qt::AlignBottom | Qt::AlignCenter);
        pointStr.append("***");
        i += 100;
        QThread::msleep(100);
    }
}
