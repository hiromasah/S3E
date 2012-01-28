#ifndef DIALOGADDRESSBOOK_H
#define DIALOGADDRESSBOOK_H

#include <QtGui/QDialog>
#include "mainwindow.h"

namespace Ui {
    class DialogAddressBook;
    class QDragEnterEvent;
    class QDropEvent;
}

class DialogAddressBook : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(DialogAddressBook)
public:
    explicit DialogAddressBook(QWidget *parent = 0);
    virtual ~DialogAddressBook();
    void presetRecipientInformation(QString title, QString fpath, QString isRecipient);

    QString pathToGnuPG;

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void closeEvent(QCloseEvent *event);
    virtual void changeEvent(QEvent *e);

private:
    void clearRecipientInformation();
    void importPublicKeyText();
    void importPublicKeyFile(QString fileOrText);
    QString displayRecipientInformation(QString keyid);
    void displayRecipientFileInformation(QString fileName, QString title, QString isRecipient);
    void setRecipientComboBox();
    void addKeyidList(QString keyid, QString title, QString fpath, QString isRecipient);
    void deleteRecipient(QString keyid);
    QString importPublicKey(QString fpath);
    QString checkIfAlreadyImported(QString fpath);

    Ui::DialogAddressBook *m_ui;
    MainWindow *wparent;
    bool isImported, isTitleOrCheckChanged, isPublicKeyPasted, isTemporaryKeyFile;
    bool isIgnoreIndexChange;

private slots:
    void on_checkBoxIsRecipient_clicked();
    void on_checkBoxIsRecipient_toggled(bool checked);
    void on_plainTextEdit_PublicKey_textChanged();
    void on_lineEdit_Title_textEdited(QString );
    void on_comboBox_Recipient_currentIndexChanged(int index);
    void on_pushButton_Delete_clicked();
    void on_pushButton_OK_clicked();
    void on_pushButton_NewRecipient_clicked();
};

#endif // DIALOGADDRESSBOOK_H
