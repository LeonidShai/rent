#include "MainController.h"
#include "Logger.h"

#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    Logger logger;
    logger.instance();

    qDebug() << "Application Rent is started";

    QApplication a(argc, argv);
    QApplication::setOrganizationName("Home");
    QApplication::setApplicationName("Rent");

    QPixmap pix(":/img/image/rent.png");
    QSplashScreen* splashScreen = new QSplashScreen(pix);
    splashScreen->show();

    MainController w(splashScreen);

    qDebug() << "Application Rent is finished";
    return a.exec();
}
