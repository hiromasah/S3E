/********************************************************************************
** Form generated from reading ui file 'dialogaddressbook.ui'
**
** Created: Sat Jul 18 18:02:23 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DIALOGADDRESSBOOK_H
#define UI_DIALOGADDRESSBOOK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogAddressBook
{
public:
    QGroupBox *groupBox;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEdit_Title;
    QLabel *label_RealName;
    QLabel *label_Email;
    QLabel *label_Comment;
    QLabel *label_FileName;
    QLabel *label_Fingerprint;
    QLabel *label_8;
    QPlainTextEdit *plainTextEdit_PublicKey;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_PubKeyId;
    QLabel *label_SubKeyId;
    QLabel *label_PubKeysize;
    QLabel *label_SubKeysize;
    QLabel *label_PubKeyCreatedLabel;
    QLabel *label_PubKeyCreated;
    QLabel *label_PubKeyExpire;
    QLabel *label_14;
    QLabel *label_SubKeyCreated;
    QLabel *label_SubKeyExpire;
    QLabel *label_15;
    QLabel *label_16;
    QPlainTextEdit *plainTextEdit_Sigs;
    QLabel *label_17;
    QLabel *label_13;
    QLabel *label_18;
    QLabel *label_19;
    QCheckBox *checkBoxIsRecipient;
    QPushButton *pushButton_OK;
    QPushButton *pushButton_Delete;
    QGroupBox *groupBox_2;
    QComboBox *comboBox_Recipient;
    QLabel *label;
    QPushButton *pushButton_NewRecipient;

    void setupUi(QDialog *DialogAddressBook)
    {
        if (DialogAddressBook->objectName().isEmpty())
            DialogAddressBook->setObjectName(QString::fromUtf8("DialogAddressBook"));
        DialogAddressBook->resize(740, 610);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogAddressBook->sizePolicy().hasHeightForWidth());
        DialogAddressBook->setSizePolicy(sizePolicy);
        DialogAddressBook->setMinimumSize(QSize(740, 610));
        DialogAddressBook->setMaximumSize(QSize(740, 610));
        groupBox = new QGroupBox(DialogAddressBook);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 70, 721, 491));
        QFont font;
        font.setPointSize(12);
        groupBox->setFont(font);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 140, 101, 20));
        label_2->setLayoutDirection(Qt::RightToLeft);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 300, 111, 20));
        label_3->setLayoutDirection(Qt::RightToLeft);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(0, 330, 121, 20));
        label_4->setLayoutDirection(Qt::RightToLeft);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 360, 111, 20));
        label_5->setLayoutDirection(Qt::RightToLeft);
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 390, 111, 20));
        label_6->setLayoutDirection(Qt::RightToLeft);
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 200, 111, 20));
        label_7->setLayoutDirection(Qt::RightToLeft);
        lineEdit_Title = new QLineEdit(groupBox);
        lineEdit_Title->setObjectName(QString::fromUtf8("lineEdit_Title"));
        lineEdit_Title->setGeometry(QRect(130, 140, 571, 20));
        label_RealName = new QLabel(groupBox);
        label_RealName->setObjectName(QString::fromUtf8("label_RealName"));
        label_RealName->setGeometry(QRect(130, 300, 571, 20));
        label_RealName->setAutoFillBackground(false);
        label_RealName->setFrameShape(QFrame::WinPanel);
        label_RealName->setFrameShadow(QFrame::Sunken);
        label_Email = new QLabel(groupBox);
        label_Email->setObjectName(QString::fromUtf8("label_Email"));
        label_Email->setGeometry(QRect(130, 330, 571, 20));
        label_Email->setAutoFillBackground(false);
        label_Email->setFrameShape(QFrame::WinPanel);
        label_Email->setFrameShadow(QFrame::Sunken);
        label_Comment = new QLabel(groupBox);
        label_Comment->setObjectName(QString::fromUtf8("label_Comment"));
        label_Comment->setGeometry(QRect(130, 360, 571, 20));
        label_Comment->setAutoFillBackground(false);
        label_Comment->setFrameShape(QFrame::WinPanel);
        label_Comment->setFrameShadow(QFrame::Sunken);
        label_FileName = new QLabel(groupBox);
        label_FileName->setObjectName(QString::fromUtf8("label_FileName"));
        label_FileName->setGeometry(QRect(130, 200, 571, 20));
        label_FileName->setAutoFillBackground(false);
        label_FileName->setFrameShape(QFrame::WinPanel);
        label_FileName->setFrameShadow(QFrame::Sunken);
        label_Fingerprint = new QLabel(groupBox);
        label_Fingerprint->setObjectName(QString::fromUtf8("label_Fingerprint"));
        label_Fingerprint->setGeometry(QRect(130, 390, 571, 20));
        label_Fingerprint->setAutoFillBackground(false);
        label_Fingerprint->setFrameShape(QFrame::WinPanel);
        label_Fingerprint->setFrameShadow(QFrame::Sunken);
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 20, 111, 20));
        label_8->setLayoutDirection(Qt::RightToLeft);
        plainTextEdit_PublicKey = new QPlainTextEdit(groupBox);
        plainTextEdit_PublicKey->setObjectName(QString::fromUtf8("plainTextEdit_PublicKey"));
        plainTextEdit_PublicKey->setGeometry(QRect(130, 20, 571, 111));
        plainTextEdit_PublicKey->setReadOnly(false);
        plainTextEdit_PublicKey->setTabStopWidth(80);
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(50, 230, 71, 20));
        label_9->setLayoutDirection(Qt::RightToLeft);
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(50, 260, 71, 20));
        label_10->setLayoutDirection(Qt::RightToLeft);
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(240, 230, 61, 20));
        label_11->setLayoutDirection(Qt::RightToLeft);
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(240, 260, 61, 20));
        label_12->setLayoutDirection(Qt::RightToLeft);
        label_PubKeyId = new QLabel(groupBox);
        label_PubKeyId->setObjectName(QString::fromUtf8("label_PubKeyId"));
        label_PubKeyId->setGeometry(QRect(150, 230, 91, 20));
        label_PubKeyId->setAutoFillBackground(false);
        label_PubKeyId->setFrameShape(QFrame::WinPanel);
        label_PubKeyId->setFrameShadow(QFrame::Sunken);
        label_SubKeyId = new QLabel(groupBox);
        label_SubKeyId->setObjectName(QString::fromUtf8("label_SubKeyId"));
        label_SubKeyId->setGeometry(QRect(150, 260, 91, 21));
        label_SubKeyId->setAutoFillBackground(false);
        label_SubKeyId->setFrameShape(QFrame::WinPanel);
        label_SubKeyId->setFrameShadow(QFrame::Sunken);
        label_PubKeysize = new QLabel(groupBox);
        label_PubKeysize->setObjectName(QString::fromUtf8("label_PubKeysize"));
        label_PubKeysize->setGeometry(QRect(310, 230, 61, 20));
        label_PubKeysize->setAutoFillBackground(false);
        label_PubKeysize->setFrameShape(QFrame::WinPanel);
        label_PubKeysize->setFrameShadow(QFrame::Sunken);
        label_SubKeysize = new QLabel(groupBox);
        label_SubKeysize->setObjectName(QString::fromUtf8("label_SubKeysize"));
        label_SubKeysize->setGeometry(QRect(310, 260, 61, 20));
        label_SubKeysize->setAutoFillBackground(false);
        label_SubKeysize->setFrameShape(QFrame::WinPanel);
        label_SubKeysize->setFrameShadow(QFrame::Sunken);
        label_PubKeyCreatedLabel = new QLabel(groupBox);
        label_PubKeyCreatedLabel->setObjectName(QString::fromUtf8("label_PubKeyCreatedLabel"));
        label_PubKeyCreatedLabel->setGeometry(QRect(370, 230, 61, 20));
        label_PubKeyCreatedLabel->setLayoutDirection(Qt::RightToLeft);
        label_PubKeyCreated = new QLabel(groupBox);
        label_PubKeyCreated->setObjectName(QString::fromUtf8("label_PubKeyCreated"));
        label_PubKeyCreated->setGeometry(QRect(440, 230, 91, 20));
        label_PubKeyCreated->setAutoFillBackground(false);
        label_PubKeyCreated->setFrameShape(QFrame::WinPanel);
        label_PubKeyCreated->setFrameShadow(QFrame::Sunken);
        label_PubKeyExpire = new QLabel(groupBox);
        label_PubKeyExpire->setObjectName(QString::fromUtf8("label_PubKeyExpire"));
        label_PubKeyExpire->setGeometry(QRect(610, 230, 91, 20));
        label_PubKeyExpire->setAutoFillBackground(false);
        label_PubKeyExpire->setFrameShape(QFrame::WinPanel);
        label_PubKeyExpire->setFrameShadow(QFrame::Sunken);
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(540, 230, 61, 20));
        label_14->setLayoutDirection(Qt::RightToLeft);
        label_SubKeyCreated = new QLabel(groupBox);
        label_SubKeyCreated->setObjectName(QString::fromUtf8("label_SubKeyCreated"));
        label_SubKeyCreated->setGeometry(QRect(440, 260, 91, 20));
        label_SubKeyCreated->setAutoFillBackground(false);
        label_SubKeyCreated->setFrameShape(QFrame::WinPanel);
        label_SubKeyCreated->setFrameShadow(QFrame::Sunken);
        label_SubKeyExpire = new QLabel(groupBox);
        label_SubKeyExpire->setObjectName(QString::fromUtf8("label_SubKeyExpire"));
        label_SubKeyExpire->setGeometry(QRect(610, 260, 91, 20));
        label_SubKeyExpire->setAutoFillBackground(false);
        label_SubKeyExpire->setFrameShape(QFrame::WinPanel);
        label_SubKeyExpire->setFrameShadow(QFrame::Sunken);
        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(370, 260, 61, 20));
        label_15->setLayoutDirection(Qt::RightToLeft);
        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(540, 260, 61, 20));
        label_16->setLayoutDirection(Qt::RightToLeft);
        plainTextEdit_Sigs = new QPlainTextEdit(groupBox);
        plainTextEdit_Sigs->setObjectName(QString::fromUtf8("plainTextEdit_Sigs"));
        plainTextEdit_Sigs->setGeometry(QRect(130, 420, 571, 61));
        plainTextEdit_Sigs->setReadOnly(true);
        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 420, 111, 20));
        label_17->setLayoutDirection(Qt::RightToLeft);
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(120, 230, 21, 20));
        label_13->setLayoutDirection(Qt::RightToLeft);
        label_18 = new QLabel(groupBox);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(120, 260, 21, 20));
        label_18->setLayoutDirection(Qt::RightToLeft);
        label_19 = new QLabel(groupBox);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(20, 170, 101, 20));
        label_19->setLayoutDirection(Qt::RightToLeft);
        checkBoxIsRecipient = new QCheckBox(groupBox);
        checkBoxIsRecipient->setObjectName(QString::fromUtf8("checkBoxIsRecipient"));
        checkBoxIsRecipient->setGeometry(QRect(130, 170, 551, 18));
        pushButton_OK = new QPushButton(DialogAddressBook);
        pushButton_OK->setObjectName(QString::fromUtf8("pushButton_OK"));
        pushButton_OK->setGeometry(QRect(540, 570, 191, 28));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_OK->sizePolicy().hasHeightForWidth());
        pushButton_OK->setSizePolicy(sizePolicy1);
        pushButton_OK->setFont(font);
        pushButton_Delete = new QPushButton(DialogAddressBook);
        pushButton_Delete->setObjectName(QString::fromUtf8("pushButton_Delete"));
        pushButton_Delete->setGeometry(QRect(450, 570, 81, 28));
        pushButton_Delete->setFont(font);
        groupBox_2 = new QGroupBox(DialogAddressBook);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 721, 51));
        groupBox_2->setFont(font);
        comboBox_Recipient = new QComboBox(groupBox_2);
        comboBox_Recipient->setObjectName(QString::fromUtf8("comboBox_Recipient"));
        comboBox_Recipient->setGeometry(QRect(130, 20, 451, 22));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 101, 20));
        label->setLayoutDirection(Qt::RightToLeft);
        pushButton_NewRecipient = new QPushButton(groupBox_2);
        pushButton_NewRecipient->setObjectName(QString::fromUtf8("pushButton_NewRecipient"));
        pushButton_NewRecipient->setGeometry(QRect(590, 16, 111, 28));
        QWidget::setTabOrder(comboBox_Recipient, pushButton_NewRecipient);
        QWidget::setTabOrder(pushButton_NewRecipient, plainTextEdit_PublicKey);
        QWidget::setTabOrder(plainTextEdit_PublicKey, lineEdit_Title);
        QWidget::setTabOrder(lineEdit_Title, checkBoxIsRecipient);
        QWidget::setTabOrder(checkBoxIsRecipient, pushButton_Delete);
        QWidget::setTabOrder(pushButton_Delete, pushButton_OK);
        QWidget::setTabOrder(pushButton_OK, plainTextEdit_Sigs);

        retranslateUi(DialogAddressBook);

        QMetaObject::connectSlotsByName(DialogAddressBook);
    } // setupUi

    void retranslateUi(QDialog *DialogAddressBook)
    {
        DialogAddressBook->setWindowTitle(QApplication::translate("DialogAddressBook", "Recipient List Setting", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DialogAddressBook", "Public Key Information", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DialogAddressBook", "Title", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("DialogAddressBook", "Real Name", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("DialogAddressBook", "EMail Address", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("DialogAddressBook", "Comment", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("DialogAddressBook", "Fingerprint", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("DialogAddressBook", "Key File Name", 0, QApplication::UnicodeUTF8));
        label_RealName->setStyleSheet(QString());
        label_RealName->setText(QString());
        label_Email->setStyleSheet(QString());
        label_Email->setText(QString());
        label_Comment->setStyleSheet(QString());
        label_Comment->setText(QString());
        label_FileName->setStyleSheet(QString());
        label_FileName->setText(QString());
        label_Fingerprint->setStyleSheet(QString());
        label_Fingerprint->setText(QString());
        label_8->setText(QApplication::translate("DialogAddressBook", "Public Key", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("DialogAddressBook", "Pub Key", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("DialogAddressBook", "Sub Key", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("DialogAddressBook", "Keysize", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("DialogAddressBook", "Keysize", 0, QApplication::UnicodeUTF8));
        label_PubKeyId->setStyleSheet(QString());
        label_PubKeyId->setText(QString());
        label_SubKeyId->setStyleSheet(QString());
        label_SubKeyId->setText(QString());
        label_PubKeysize->setStyleSheet(QString());
        label_PubKeysize->setText(QString());
        label_SubKeysize->setStyleSheet(QString());
        label_SubKeysize->setText(QString());
        label_PubKeyCreatedLabel->setText(QApplication::translate("DialogAddressBook", "Created", 0, QApplication::UnicodeUTF8));
        label_PubKeyCreated->setStyleSheet(QString());
        label_PubKeyCreated->setText(QString());
        label_PubKeyExpire->setStyleSheet(QString());
        label_PubKeyExpire->setText(QString());
        label_14->setText(QApplication::translate("DialogAddressBook", "Expire", 0, QApplication::UnicodeUTF8));
        label_SubKeyCreated->setStyleSheet(QString());
        label_SubKeyCreated->setText(QString());
        label_SubKeyExpire->setStyleSheet(QString());
        label_SubKeyExpire->setText(QString());
        label_15->setText(QApplication::translate("DialogAddressBook", "Created", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("DialogAddressBook", "Expire", 0, QApplication::UnicodeUTF8));
        plainTextEdit_Sigs->setStyleSheet(QApplication::translate("DialogAddressBook", "background-color: rgb(212, 208, 200);", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("DialogAddressBook", "Sigs", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("DialogAddressBook", "ID", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("DialogAddressBook", "ID", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("DialogAddressBook", "Recipient List", 0, QApplication::UnicodeUTF8));
        checkBoxIsRecipient->setText(QApplication::translate("DialogAddressBook", "List up on the recipient list if checked", 0, QApplication::UnicodeUTF8));
        pushButton_OK->setText(QApplication::translate("DialogAddressBook", "OK", 0, QApplication::UnicodeUTF8));
        pushButton_Delete->setText(QApplication::translate("DialogAddressBook", "Delete", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("DialogAddressBook", "Public Key Select", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DialogAddressBook", "Title", 0, QApplication::UnicodeUTF8));
        pushButton_NewRecipient->setText(QApplication::translate("DialogAddressBook", "New Recipient", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(DialogAddressBook);
    } // retranslateUi

};

namespace Ui {
    class DialogAddressBook: public Ui_DialogAddressBook {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGADDRESSBOOK_H
