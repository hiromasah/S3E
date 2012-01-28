/********************************************************************************
** Form generated from reading ui file 'dialoguserinfo.ui'
**
** Created: Thu Jul 30 09:56:57 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DIALOGUSERINFO_H
#define UI_DIALOGUSERINFO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogUserInfo
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *lineEdit_Name;
    QLineEdit *lineEdit_ID;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_2;
    QLabel *label_7;
    QPushButton *pushButton_OK;
    QPushButton *pushButton_Cancel;

    void setupUi(QDialog *DialogUserInfo)
    {
        if (DialogUserInfo->objectName().isEmpty())
            DialogUserInfo->setObjectName(QString::fromUtf8("DialogUserInfo"));
        DialogUserInfo->resize(750, 360);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogUserInfo->sizePolicy().hasHeightForWidth());
        DialogUserInfo->setSizePolicy(sizePolicy);
        DialogUserInfo->setMinimumSize(QSize(750, 360));
        DialogUserInfo->setMaximumSize(QSize(750, 360));
        DialogUserInfo->setContextMenuPolicy(Qt::DefaultContextMenu);
        groupBox = new QGroupBox(DialogUserInfo);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 731, 291));
        QFont font;
        font.setPointSize(12);
        groupBox->setFont(font);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 100, 101, 20));
        label->setLayoutDirection(Qt::RightToLeft);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(30, 50, 81, 20));
        label_3->setLayoutDirection(Qt::RightToLeft);
        lineEdit_Name = new QLineEdit(groupBox);
        lineEdit_Name->setObjectName(QString::fromUtf8("lineEdit_Name"));
        lineEdit_Name->setGeometry(QRect(120, 100, 581, 20));
        lineEdit_ID = new QLineEdit(groupBox);
        lineEdit_ID->setObjectName(QString::fromUtf8("lineEdit_ID"));
        lineEdit_ID->setGeometry(QRect(120, 50, 161, 20));
        lineEdit_ID->setMaxLength(32);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(120, 170, 501, 16));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(270, 200, 231, 20));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(270, 230, 241, 20));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(149, 200, 111, 20));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(150, 230, 111, 20));
        label_7->setLayoutDirection(Qt::LeftToRight);
        pushButton_OK = new QPushButton(DialogUserInfo);
        pushButton_OK->setObjectName(QString::fromUtf8("pushButton_OK"));
        pushButton_OK->setGeometry(QRect(440, 310, 221, 28));
        pushButton_OK->setFont(font);
        pushButton_Cancel = new QPushButton(DialogUserInfo);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));
        pushButton_Cancel->setGeometry(QRect(667, 310, 75, 28));
        pushButton_Cancel->setFont(font);

        retranslateUi(DialogUserInfo);

        QMetaObject::connectSlotsByName(DialogUserInfo);
    } // setupUi

    void retranslateUi(QDialog *DialogUserInfo)
    {
        DialogUserInfo->setWindowTitle(QApplication::translate("DialogUserInfo", "User Information Setting", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DialogUserInfo", "User Information", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DialogUserInfo", "User Name", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("DialogUserInfo", "ID", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        lineEdit_Name->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        lineEdit_Name->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        label_4->setText(QApplication::translate("DialogUserInfo", "The presetting naming rule of output file is as follows.", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("DialogUserInfo", "ID_yyyymmddhhmmss.tgz.gpg", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("DialogUserInfo", "ID_yyyymmddhhmmss.txt", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DialogUserInfo", "Encrypted File : ", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("DialogUserInfo", "Receipt File : ", 0, QApplication::UnicodeUTF8));
        pushButton_OK->setText(QApplication::translate("DialogUserInfo", "OK", 0, QApplication::UnicodeUTF8));
        pushButton_Cancel->setText(QApplication::translate("DialogUserInfo", "Cancel", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(DialogUserInfo);
    } // retranslateUi

};

namespace Ui {
    class DialogUserInfo: public Ui_DialogUserInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGUSERINFO_H
