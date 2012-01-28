#include "dialoguserinfo.h"
#include "ui_dialoguserinfo.h"
#include <QtGui>

DialogUserInfo::DialogUserInfo(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::DialogUserInfo)
{
    wparent = (MainWindow *)parent;
    m_ui->setupUi(this);
    m_ui->lineEdit_Name->setText(getUserInfo("Name"));
    m_ui->lineEdit_ID->setText(getUserInfo("ID"));
}

DialogUserInfo::~DialogUserInfo()
{
    delete m_ui;
}

void DialogUserInfo::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QString DialogUserInfo::getUserInfo(QString key)
{
//    QSettings settings(wparent->programName, "User Information");
//    return settings.value(key).toString();
    QString iniFname = wparent->programName + ".ini";
    QSettings *ini_settings;
    ini_settings = new QSettings(iniFname, QSettings::IniFormat);
    return ini_settings->value("UserInformation/" + key).toString();
}
void DialogUserInfo::on_pushButton_Cancel_clicked()
{
    close();
}

void DialogUserInfo::on_pushButton_OK_clicked()
{
//※暗号化ファイルのファイル名は、下記の命名規則でプリセットされます。

//    ID_yyyymmddhhmmss.tgz.gpg （暗号化ファイル）
//    ID_yyyymmddhhmmss.txt　（レシートファイル）

    if(m_ui->lineEdit_ID->text() == ""){
        QMessageBox::information(this, tr("Confirm"), tr("Empty ID."));
    }
    if(m_ui->lineEdit_ID->text() != ""){
//        QSettings settings(wparent->programName, "User Information");
//        settings.setValue("Name", m_ui->lineEdit_Name->text());
//        settings.setValue("ID", m_ui->lineEdit_ID->text());
        QString iniFname = wparent->programName + ".ini";
        QSettings *ini_settings;
        ini_settings = new QSettings(iniFname, QSettings::IniFormat);
        ini_settings->setValue("UserInformation/Name", m_ui->lineEdit_Name->text());
        ini_settings->setValue("UserInformation/ID", m_ui->lineEdit_ID->text());

        QString userInfo = m_ui->lineEdit_Name->text() + " (" + m_ui->lineEdit_ID->text() + ")";
        wparent->setWindowTitle(wparent->programName + " - " + userInfo);
        wparent->userName = m_ui->lineEdit_Name->text();
        wparent->userId = m_ui->lineEdit_ID->text();

        close();
    }
}
