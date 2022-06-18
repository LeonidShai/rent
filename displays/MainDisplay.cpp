#include "MainDisplay.h"
#include "ui_MainDisplay.h"
#include "MainController.h"

#include <QSettings>

MainDisplay::MainDisplay(MainController* mainController, QWidget* parent) :
    QMainWindow(parent),
    m_pUi(new Ui::MainDisplay),
    m_pMainController(mainController)
{
    m_pUi->setupUi(this);
    createConnects();
    qDebug() << "Main Display is started";
}

MainDisplay::~MainDisplay()
{
    delete m_pUi;
}

void MainDisplay::saveSettings(QSettings* settings)
{
    qInfo() << "Save settings for main display";
    settings->beginGroup("MainDisplay");
    settings->setValue("geometry", this->geometry());
    settings->setValue("checkBoxNightLight", m_pUi->checkBoxNightLight->isChecked());
    settings->setValue("radioButtonHotWater", m_pUi->radioButtonHotWater->isChecked());
    settings->setValue("radioButtonColdWater2", m_pUi->radioButtonColdWater2->isChecked());
    settings->setValue("checkBoxGaz", m_pUi->checkBoxGaz->isChecked());

    if (!m_dataKeeper.isEmpty())
    {
        settings->setValue("lastDayLight", QString::number(m_dataKeeper.dayLight()));
        settings->setValue("lastNightLight", QString::number(m_dataKeeper.nightLight()));
        settings->setValue("lastColdWater", QString::number(m_dataKeeper.coldWater()));
        settings->setValue("lastColdWater2", QString::number(m_dataKeeper.coldWater2()));
        settings->setValue("lastHotWater", QString::number(m_dataKeeper.hotWater()));
        settings->setValue("lastGaz", QString::number(m_dataKeeper.gaz()));
    }
    settings->endGroup();
}

void MainDisplay::loadSettings(QSettings* settings)
{
    setWindowTitle(settings->applicationName());
    settings->beginGroup("MainDisplay");
    this->setGeometry(settings->value("geometry", QRect(200, 200, 300, 300)).toRect());
    m_pUi->checkBoxNightLight->setChecked(settings->value("checkBoxNightLight", false).toBool());
    m_pUi->radioButtonHotWater->setChecked(settings->value("radioButtonHotWater", true).toBool());
    m_pUi->radioButtonColdWater2->setChecked(settings->value("radioButtonColdWater2", false).toBool());
    m_pUi->checkBoxGaz->setChecked(settings->value("checkBoxGaz", false).toBool());

    m_lastDataKeeper.setDayLight(settings->value("lastDayLight", QString::number(0)).toInt());
    m_lastDataKeeper.setNightLight(settings->value("lastNightLight", QString::number(0)).toInt());
    m_lastDataKeeper.setColdWater(settings->value("lastColdWater", QString::number(0)).toInt());
    m_lastDataKeeper.setColdWater2(settings->value("lastColdWater2", QString::number(0)).toInt());
    m_lastDataKeeper.setHotWater(settings->value("lastHotWater", QString::number(0)).toInt());
    m_lastDataKeeper.setGaz(settings->value("lastGaz", QString::number(0)).toInt());
    settings->endGroup();
    qInfo() << "Settings for main display were loaded";
}

void MainDisplay::init()
{
    m_pUi->labelWarnDayLight->hide();
    m_pUi->labelWarnNightLight->hide();
    m_pUi->labelWarnColdWater->hide();
    m_pUi->labelWarnHotWater->hide();
    m_pUi->labelWarnColdWater2->hide();
    m_pUi->labelWarnGaz->hide();
    m_pUi->labelError->hide();

    m_pUi->lineEditNightLight->setEnabled(m_pUi->checkBoxNightLight->isChecked());
    m_pUi->lineEditHotWater->setEnabled(m_pUi->radioButtonHotWater->isChecked());
    m_pUi->lineEditColdWater2->setEnabled(m_pUi->radioButtonColdWater2->isChecked());
    m_pUi->lineEditGaz->setEnabled(m_pUi->checkBoxGaz->isChecked());

    m_pUi->lineEditLastDayLight->setReadOnly(true);
    m_pUi->lineEditLastNightLight->setReadOnly(true);
    m_pUi->lineEditLastColdWater->setReadOnly(true);
    m_pUi->lineEditLastColdWater2->setReadOnly(true);
    m_pUi->lineEditLastHotWater->setReadOnly(true);
    m_pUi->lineEditLastGaz->setReadOnly(true);

    setNewLastValues();
}

void MainDisplay::createConnects()
{
    connect(m_pUi->lineEditDayLight, SIGNAL(textChanged(QString)), this, SLOT(checkString(QString)));
    connect(m_pUi->lineEditNightLight, SIGNAL(textChanged(QString)), this, SLOT(checkString(QString)));
    connect(m_pUi->lineEditColdWater, SIGNAL(textChanged(QString)), this, SLOT(checkString(QString)));
    connect(m_pUi->lineEditColdWater2, SIGNAL(textChanged(QString)), this, SLOT(checkString(QString)));
    connect(m_pUi->lineEditHotWater, SIGNAL(textChanged(QString)), this, SLOT(checkString(QString)));
    connect(m_pUi->lineEditGaz, SIGNAL(textChanged(QString)), this, SLOT(checkString(QString)));
}

void MainDisplay::collectData()
{
    m_dataKeeper.setDayLight(m_pUi->lineEditDayLight->text().toInt());

    if (m_pUi->checkBoxNightLight->isChecked())
        m_dataKeeper.setNightLight(m_pUi->lineEditNightLight->text().toInt());
    else
        m_dataKeeper.setNightLight(chooseValue(m_lastDataKeeper.nightLight()));

    m_dataKeeper.setColdWater(m_pUi->lineEditColdWater->text().toInt());

    if (m_pUi->radioButtonHotWater->isChecked())
    {
        m_dataKeeper.setHotWater(m_pUi->lineEditHotWater->text().toInt());
        m_dataKeeper.setColdWater2(chooseValue(m_lastDataKeeper.coldWater2()));
    }
    else
    {
        m_dataKeeper.setColdWater2(m_pUi->lineEditColdWater2->text().toInt());
        m_dataKeeper.setHotWater(chooseValue(m_lastDataKeeper.hotWater()));
    }

    if (m_pUi->checkBoxGaz->isChecked())
        m_dataKeeper.setGaz(m_pUi->lineEditGaz->text().toInt());
    else
        m_dataKeeper.setGaz(chooseValue(m_lastDataKeeper.gaz()));
}

int MainDisplay::chooseValue(const int& lastValue) const
{
    int value;
    if (lastValue != 0)
        value = lastValue;
    else
        value = 0;

    return value;
}

bool MainDisplay::checkFilling()
{
    bool isFilled = true;

    fillingInspector(m_pUi->lineEditDayLight, m_pUi->labelWarnDayLight, isFilled);

    if (m_pUi->checkBoxNightLight->isChecked())
        fillingInspector(m_pUi->lineEditNightLight, m_pUi->labelWarnNightLight, isFilled);

    fillingInspector(m_pUi->lineEditColdWater, m_pUi->labelWarnColdWater, isFilled);

    if (m_pUi->radioButtonHotWater->isChecked())
        fillingInspector(m_pUi->lineEditHotWater, m_pUi->labelWarnHotWater, isFilled);
    else
        fillingInspector(m_pUi->lineEditColdWater2, m_pUi->labelWarnColdWater2, isFilled);

    if (m_pUi->checkBoxGaz->isChecked())
        fillingInspector(m_pUi->lineEditGaz, m_pUi->labelWarnGaz, isFilled);

    if (!isFilled)
        showError(MainDisplay::ERROR_TYPE::EMPTY_LINE);
    else
    {
        if (!m_pUi->labelError->isHidden())
            m_pUi->labelError->hide();
    }

    return isFilled;
}

void MainDisplay::fillingInspector(QLineEdit *lineEdit, QLabel *labelWarn, bool& isFilled)
{
    if (lineEdit->text().isEmpty())
    {
        labelWarn->show();
        isFilled = false;
    }
    else
    {
        if (!labelWarn->isHidden())
            labelWarn->hide();
    }
}

bool MainDisplay::checkCorrectValues()
{
    bool isCorrected = true;

    valueInspector(m_lastDataKeeper.dayLight(), m_dataKeeper.dayLight(), m_pUi->lineEditLastDayLight, isCorrected);
    valueInspector(m_lastDataKeeper.nightLight(), m_dataKeeper.nightLight(), m_pUi->lineEditLastNightLight, isCorrected);
    valueInspector(m_lastDataKeeper.coldWater(), m_dataKeeper.coldWater(), m_pUi->lineEditLastColdWater, isCorrected);
    valueInspector(m_lastDataKeeper.coldWater2(), m_dataKeeper.coldWater2(), m_pUi->lineEditLastColdWater2, isCorrected);
    valueInspector(m_lastDataKeeper.hotWater(), m_dataKeeper.hotWater(), m_pUi->lineEditLastHotWater, isCorrected);
    valueInspector(m_lastDataKeeper.gaz(), m_dataKeeper.gaz(), m_pUi->lineEditLastGaz, isCorrected);

    if (!isCorrected)
        showError(MainDisplay::ERROR_TYPE::INCORRECT_VALUE);
    else
    {
        if (!m_pUi->labelError->isHidden())
            m_pUi->labelError->hide();
    }

    return isCorrected;
}

void MainDisplay::valueInspector(const int& lastValue, const int& currentValue, QLineEdit* lineEdit, bool& isCorrected)
{
    if ((lastValue > currentValue) && (currentValue != 0))
    {
        isCorrected = false;
        lineEdit->setStyleSheet("QLineEdit {background-color: rgb(180, 80, 80); "
                                "border: 2px solid; border-color: darkRed; font: bold}");
    }
    else
        lineEdit->setStyleSheet("QLineEdit {background-color: white;}");
}

void MainDisplay::clearFields()
{
    m_pUi->lineEditDayLight->clear();
    m_pUi->lineEditNightLight->clear();
    m_pUi->lineEditColdWater->clear();
    m_pUi->lineEditHotWater->clear();
    m_pUi->lineEditColdWater2->clear();
    m_pUi->lineEditGaz->clear();
}

void MainDisplay::setNewLastValues()
{
    if (!m_dataKeeper.isEmpty())
        m_lastDataKeeper = m_dataKeeper;

    m_pUi->lineEditLastDayLight->setText(QString::number(m_lastDataKeeper.dayLight()));
    m_pUi->lineEditLastNightLight->setText(QString::number(m_lastDataKeeper.nightLight()));
    m_pUi->lineEditLastColdWater->setText(QString::number(m_lastDataKeeper.coldWater()));
    m_pUi->lineEditLastColdWater2->setText(QString::number(m_lastDataKeeper.coldWater2()));
    m_pUi->lineEditLastHotWater->setText(QString::number(m_lastDataKeeper.hotWater()));
    m_pUi->lineEditLastGaz->setText(QString::number(m_lastDataKeeper.gaz()));
}

void MainDisplay::showError(MainDisplay::ERROR_TYPE errorType)
{
    QString errorMessage;
    switch (errorType)
    {
        case MainDisplay::ERROR_TYPE::EMPTY_LINE:
        {
            errorMessage = "Fill the field, marked by *";
            break;
        }
        case MainDisplay::ERROR_TYPE::INCORRECT_VALUE:
        {
            errorMessage = "The input value should not be the less than last one or equal to zero";
            break;
        }
    }
    m_pUi->labelError->setText(errorMessage);
    m_pUi->labelError->show();
}

void MainDisplay::on_pushButtonSave_clicked()
{
    if(!checkFilling())
        return;

    collectData();
    if (!checkCorrectValues())
    {
        m_dataKeeper.clear();
        return;
    }

    clearFields();
    setNewLastValues();

    m_pMainController->saveDataInFile(m_dataKeeper);
}

void MainDisplay::on_checkBoxGaz_toggled(bool checked)
{
    if (!checked)
        m_pUi->lineEditGaz->clear();

    m_pUi->lineEditGaz->setEnabled(checked);

    if (!checked)
        m_pUi->labelWarnGaz->hide();
}

void MainDisplay::on_checkBoxNightLight_toggled(bool checked)
{
    if (!checked)
        m_pUi->lineEditNightLight->clear();

    m_pUi->lineEditNightLight->setEnabled(checked);

    if (!checked)
        m_pUi->labelWarnNightLight->hide();
}

void MainDisplay::checkString(QString inputStr)
{
    QLineEdit* lineEdit = qobject_cast<QLineEdit*>(sender());
    if (inputStr.size() > 5)
        inputStr.chop(1);

    if ((inputStr.size() != 0) && (!inputStr.at(inputStr.size()-1).isDigit()))
        inputStr.chop(1);

    lineEdit->setText(inputStr);
}

void MainDisplay::on_radioButtonHotWater_clicked()
{
    m_pUi->lineEditColdWater2->clear();
    m_pUi->lineEditHotWater->setEnabled(true);
    m_pUi->lineEditColdWater2->setEnabled(false);
    m_pUi->lineEditLastColdWater2->setStyleSheet("QLineEdit {background-color: white;}");
}

void MainDisplay::on_radioButtonColdWater2_clicked()
{
    m_pUi->lineEditHotWater->clear();
    m_pUi->lineEditHotWater->setEnabled(false);
    m_pUi->lineEditColdWater2->setEnabled(true);
    m_pUi->lineEditLastHotWater->setStyleSheet("QLineEdit {background-color: white;}");
}
