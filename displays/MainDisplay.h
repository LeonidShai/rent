#ifndef MAINDISPLAY_H
#define MAINDISPLAY_H

#include <QMainWindow>
#include "Logger.h"
#include "DataKeeper.h"

class QSettings;
class QLineEdit;
class QLabel;
class MainController;

namespace Ui {
    class MainDisplay;
}

class MainDisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainDisplay(MainController* mainController = nullptr, QWidget* parent = nullptr);
    ~MainDisplay();

    void saveSettings(QSettings* settings);
    void loadSettings(QSettings* settings);
    void init();

    enum ERROR_TYPE
    {
        EMPTY_LINE = 0,
        INCORRECT_VALUE
    };

private slots:
    void on_pushButtonSave_clicked();
    void on_checkBoxGaz_toggled(bool checked);
    void on_checkBoxNightLight_toggled(bool checked);
    void checkString(QString inputStr);
    void on_radioButtonHotWater_clicked();
    void on_radioButtonColdWater2_clicked();

private:
    Ui::MainDisplay* m_pUi;
    MainController* m_pMainController;
    DataKeeper m_dataKeeper;
    DataKeeper m_lastDataKeeper;

    void createConnects();
    void collectData();
    bool checkFilling();
    bool checkCorrectValues();
    void clearFields();
    void setNewLastValues();

    void fillingInspector(QLineEdit* lineEdit, QLabel* labelWarn, bool& isFilled);
    void valueInspector(const int& lastValue, const int& currentValue, QLineEdit* lineEdit, bool& isCorrected);
    int chooseValue(const int& lastValue) const;

    void showError(ERROR_TYPE errorType);
};

#endif // MAINDISPLAY_H
