#include "dialogaddressbook.h"
#include "cgpgexec.h"
#include "ui_dialogaddressbook.h"
#include <QtGui>

DialogAddressBook::DialogAddressBook(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::DialogAddressBook)
{
    wparent = (MainWindow *)parent;
    pathToGnuPG = wparent->pathToGnuPG;

    m_ui->setupUi(this);
    isImported = false;
    isTitleOrCheckChanged = false;
    isPublicKeyPasted = false;
    isTemporaryKeyFile = false;
    isIgnoreIndexChange = false;

    setRecipientComboBox();
}

DialogAddressBook::~DialogAddressBook()
{
    delete m_ui;
}

 void DialogAddressBook::closeEvent(QCloseEvent *event)
 {
    if(isImported){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Confirm"),
                                        tr("Cancel import?"),
                                        QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes){
            isImported = false;
            isTitleOrCheckChanged = false;

            QString keyid = m_ui->label_PubKeyId->text();
            deleteRecipient(keyid);

            event->accept();
        }
        else{
            event->ignore();
        }
    }
    else if(isTitleOrCheckChanged){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Confirm"),
                                        tr("Cancel edit?"),
                                        QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes){
            isTitleOrCheckChanged = false;

            event->accept();
        }
        else{
            event->ignore();
        }
    }
    else{
        event->accept();
    }
}

void DialogAddressBook::dragEnterEvent(QDragEnterEvent *event)
{
    if(m_ui->plainTextEdit_PublicKey->isReadOnly()){
        event->ignore();
    }
    else{
        if (event->mimeData()->hasUrls()) {
            event->acceptProposedAction();
        } else {
            event->ignore();
        }
    }
}

void DialogAddressBook::dragMoveEvent(QDragMoveEvent *event)
{
    if(m_ui->plainTextEdit_PublicKey->isReadOnly()){
        event->ignore();
    }
    else{
        if (event->mimeData()->hasUrls()) {
            event->acceptProposedAction();
        } else {
            event->ignore();
        }
    }
}

void DialogAddressBook::dropEvent(QDropEvent *event)
{
    if(m_ui->plainTextEdit_PublicKey->isReadOnly()){
        event->ignore();
    }
    else{
        const QMimeData *mimeData = event->mimeData();
        if (mimeData->hasUrls()) {
            QList<QUrl> urlList = mimeData->urls();
            if(urlList.size()){
                if(urlList.size() == 1) {
                    QString path = urlList.at(0).path().mid(1);
                    QFileInfo *fileinfo = new QFileInfo(path);
                    if(fileinfo->isFile()){
                        isTemporaryKeyFile = false;

                        importPublicKeyFile(path);
                    }
                    else{
                        QMessageBox::information(this, tr("Information"), "Select a public key file.");
                    }
                }
                else{
                    QMessageBox::information(this, tr("Information"), "Select one public key file.");
                }
            }
            event->acceptProposedAction();
        }
        else{
            event->ignore();
        }
    }
}

void DialogAddressBook::presetRecipientInformation(QString title, QString fpath, QString isRecipient)
{
    // Import public key into gpg.
    QString keyid = importPublicKey(fpath);
    if(! keyid.isEmpty()){
        addKeyidList(keyid, title, fpath, isRecipient);
    }
}

void DialogAddressBook::changeEvent(QEvent *e)
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

void DialogAddressBook::clearRecipientInformation()
{
    m_ui->plainTextEdit_PublicKey->clear();
    m_ui->plainTextEdit_PublicKey->setStyleSheet("background-color: rgb(255, 255, 255);");
    m_ui->plainTextEdit_PublicKey->setReadOnly(false);
    m_ui->lineEdit_Title->setText("");
    m_ui->checkBoxIsRecipient->setChecked(false);
    m_ui->label_FileName->setText("");
    m_ui->label_PubKeyId->setText("");
    m_ui->label_PubKeysize->setText("");
    m_ui->label_PubKeyCreated->setText("");
    m_ui->label_PubKeyExpire->setText("");
    m_ui->label_SubKeyId->setText("");
    m_ui->label_SubKeysize->setText("");
    m_ui->label_SubKeyCreated->setText("");
    m_ui->label_SubKeyExpire->setText("");
    m_ui->label_RealName->setText("");
    m_ui->label_Email->setText("");
    m_ui->label_Comment->setText("");
    m_ui->label_Fingerprint->setText("");
    m_ui->plainTextEdit_Sigs->clear();
}
void DialogAddressBook::importPublicKeyText()
{
    QString yyyymmddhhmmss = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
    QString keyFname = "pub" + yyyymmddhhmmss + ".asc";
    QString keyPath = QDir::currentPath() + "/" + keyFname;
    QFile keyfile(keyPath);
    if (keyfile.open(QFile::WriteOnly | QFile::Text)){
        keyfile.write(m_ui->plainTextEdit_PublicKey->toPlainText().toAscii());
        keyfile.close();

        isTemporaryKeyFile = true;

        importPublicKeyFile(keyPath);
    }
}

void DialogAddressBook::importPublicKeyFile(QString keyPath)
{
    bool stat = true;

    QString dupTitle = checkIfAlreadyImported(keyPath);
    if(! dupTitle.isEmpty()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Confirm"),
                                        dupTitle + " " + tr("is already imported. Replace?"),
                                        QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes){
            stat = true;
        }
        else{
            stat = false;
        }
    }
    if(stat){
        m_ui->comboBox_Recipient->setCurrentIndex(0);

        m_ui->label_FileName->setText(keyPath);

        // Import public key into gpg.
        QString keyid = importPublicKey(keyPath);

        if(! keyid.isEmpty()){

            isImported = true;

            QString title = "";
//            QSettings settings(wparent->programName, "Recipient Information");
//            QStringList keyidList = settings.value("KeyidList").toStringList();
            QString iniFname = wparent->programName + ".ini";
            QSettings *ini_settings;
            ini_settings = new QSettings(iniFname, QSettings::IniFormat);
            QStringList keyidList = ini_settings->value("RecipientInformation/KeyidList").toStringList();
            if(keyidList.indexOf(keyid) != -1){
//                title = settings.value("Title_" + keyid).toString();
                title = ini_settings->value("RecipientInformation/Title_" + keyid).toString();
            }
            QString uid = displayRecipientInformation(keyid);
            if(title.isEmpty()){
                title = uid;
            }
            displayRecipientFileInformation(keyPath, title, "1");
        }
    }
}

void DialogAddressBook::displayRecipientFileInformation(QString fileName, QString title, QString isRecipient)
{
    m_ui->lineEdit_Title->setText(title);
    if(isRecipient == "1"){
        m_ui->checkBoxIsRecipient->setChecked(true);
    }
    else{
        m_ui->checkBoxIsRecipient->setChecked(false);
    }
    
    if (!fileName.isEmpty()){
        QFile file(fileName);
        if (file.exists()){
            m_ui->label_FileName->setText(fileName);
            QFile file(fileName);
            if (file.open(QFile::ReadOnly | QFile::Text)) {
                m_ui->plainTextEdit_PublicKey->setReadOnly(true);
                m_ui->plainTextEdit_PublicKey->setStyleSheet("background-color: rgb(212, 208, 200);");
                QTextStream stream(&file);
                QString line;

                int row = 0;
                do {
                    line = stream.readLine();
                    m_ui->plainTextEdit_PublicKey->appendPlainText(line);
                    row++;
                    if(row >= 1000){
                        m_ui->plainTextEdit_PublicKey->appendPlainText("-- Exceeded max line count --");
                        break;
                    }
                } while (!stream.atEnd());
                file.close();

                m_ui->plainTextEdit_PublicKey->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);
            }
            else{
                m_ui->label_FileName->setText("");
            }
        }
        else{
            m_ui->label_FileName->setText("");
        }
    }
}

QString DialogAddressBook::displayRecipientInformation(QString keyid)
{
    QTextCodec *codec = QTextCodec::codecForName("Shift-JIS");
    QTextDecoder *decoder = codec->makeDecoder();

    QString uid = "";
    CGpgExec *gpgif = new CGpgExec(this);
    QString msg;
    QStringList wlist1, wlist2, wlist3;
    QStringList msglist;
    bool stat;
    stat = gpgif->gpgExecute("fingerprint", keyid, "", &msg);
    if(stat && !msg.isEmpty()){
        msglist = decoder->toUnicode(msg.toAscii()).split("\r\n");
        if(msglist[0].mid(0,4) == "pub "){

            // set public keyid
            m_ui->label_PubKeyId->setText(keyid);

            // Pickup expire
            wlist1 = msglist[0].split(" [");
            if(wlist1.count() > 1){
                if(!wlist1[1].isEmpty()){
                    wlist2 = wlist1[1].split(" ");
                    m_ui->label_PubKeyExpire->setText(wlist2[1].mid(0, 10));
                }
            }

            // Pickup create date
            wlist2 = wlist1[0].split("   ");
            if(wlist2.count() > 1){
                wlist1 = wlist2[1].split(" ");
                if(wlist1.count() > 1){
                    m_ui->label_PubKeyCreated->setText(wlist1[1].mid(0, 10));
                }
            }

            // Pickup pub keysize
            wlist2 = wlist1[0].split("/");
            m_ui->label_PubKeysize->setText(wlist2[0]);

            // Pickup uid
            wlist1 = msglist[2].split("                  ");
            if(wlist1.count() > 1){
                uid = wlist1[1];
            }

            // Pickup E-Mail Address
            wlist1 = uid.split(" <");
            if(wlist1.count() > 1){
                if(!wlist1[1].isEmpty()){
                    wlist2 = wlist1[1].split(">");
                    m_ui->label_Email->setText(wlist2[0]);
                }
            }

            // Pickup Comment
            wlist2 = wlist1[0].split(" (");
            if(wlist2.count() > 1){
                if(!wlist2[1].isEmpty()){
                    wlist3 = wlist2[1].split(")");
                    m_ui->label_Comment->setText(wlist3[0]);
                }
            }

            // Pickup Real name
            if(!wlist2[0].isEmpty()){
                m_ui->label_RealName->setText(wlist2[0]);
            }

            // Pickup fingerprint
            wlist1 = msglist[1].split("= ");
            if(wlist1.count() > 1){
                m_ui->label_Fingerprint->setText(wlist1[1]);
            }

            // drop additional uids
            int pos = 3;
            while(msglist[pos].mid(0,4) == "uid "){
                pos++;
            }
            if(msglist[pos].mid(0,4) == "sub "){

                // Pickup sub expire
                wlist1 = msglist[pos].split(" [");
                if(wlist1.count() > 1){
                    if(!wlist1[1].isEmpty()){
                        wlist2 = wlist1[1].split(" ");
                        m_ui->label_SubKeyExpire->setText(wlist2[1].mid(0, 10));
                    }
                }

                // Pickup sub create date
                wlist2 = wlist1[0].split("   ");
                if(wlist2.count() > 1){
                    wlist1 = wlist2[1].split(" ");
                    if(wlist1.count() > 1){
                        m_ui->label_SubKeyCreated->setText(wlist1[1].mid(0, 10));
                    }
                }

                // Pickup sub keysize
                wlist2 = wlist1[0].split("/");
                m_ui->label_SubKeysize->setText(wlist2[0]);

                // Pickup sub keyid
                if(wlist2.count() > 1){
                    m_ui->label_SubKeyId->setText(wlist2[1]);
                }

            }

            // Pickup sigs
            stat = gpgif->gpgExecute("list-sigs", keyid, "", &msg);
            if(stat && !msg.isEmpty()){
                msglist = decoder->toUnicode(msg.toAscii()).split("\r\n");
                int pos = 2;
                while(msglist[pos].mid(0,4) == "sig "){
                    m_ui->plainTextEdit_Sigs->appendPlainText(msglist[pos]);
                    pos++;
                }
            }
            else{
                QMessageBox::information(this, tr("Confirm"), decoder->toUnicode(msg.toAscii()));
            }

        }
        else{
            QMessageBox::information(this, tr("Confirm"), decoder->toUnicode(msg.toAscii()));
        }
    }
    return uid;
}

QString DialogAddressBook::checkIfAlreadyImported(QString fpath)
{
    QString title = "";
    QString keyid = "";

    CGpgExec *gpgif = new CGpgExec(this);
    QString msg;
    bool stat = gpgif->gpgExecute("check", fpath, "", &msg);
    if(stat && !msg.isEmpty()){
        QStringList msglist = msg.split("\r\n");
        QStringList wlist1, wlist2, wlist3;
        if(msglist[1].mid(0,9) == "gpg: pub "){
            // Pickup keyid
            wlist1 = msglist[1].split("  ");
            if(wlist1.count() > 1){
                wlist2 = wlist1[1].split(" ");
                wlist1 = wlist2[0].split("/");
                keyid = wlist1[1];
            }
            if(! keyid.isEmpty()){
                int index = m_ui->comboBox_Recipient->findData (keyid, Qt::UserRole, Qt::MatchExactly | Qt::MatchCaseSensitive );
                if(index > 0){
                    title = m_ui->comboBox_Recipient->itemText(index);
                }
            }
        }
    }
    return title;
}

QString DialogAddressBook::importPublicKey(QString fpath)
{
    QTextCodec *codec = QTextCodec::codecForName("Shift-JIS");
    QTextDecoder *decoder = codec->makeDecoder();

    QString keyid = "";

    CGpgExec *gpgif = new CGpgExec(this);
    QString msg;
    bool stat = gpgif->gpgExecute("import", fpath, "", &msg);
    if(stat && !msg.isEmpty()){
        QStringList msglist = msg.split("\r\n");
        QStringList wlist1, wlist2, wlist3;
        for(int ii = 0; ii < msglist.count(); ii++){
            if(msglist[ii].mid(0,9) == "gpg: pub "){
                // Pickup keyid
                wlist1 = msglist[ii].split("  ");
                if(wlist1.count() > 1){
                    wlist2 = wlist1[1].split(" ");
                    wlist1 = wlist2[0].split("/");
                    keyid = wlist1[1];
                }
                break;
            }
        }
        if(keyid.isEmpty()){
            QMessageBox::information(this, tr("Information"), decoder->toUnicode(msg.toAscii()));
        }
    }
    return keyid;
}

void DialogAddressBook::setRecipientComboBox()
{
    m_ui->comboBox_Recipient->clear();
    m_ui->comboBox_Recipient->addItem(QIcon(), "", "");
//    QSettings settings(wparent->programName, "Recipient Information");
//    QStringList keyidList = settings.value("KeyidList").toStringList();
    QString iniFname = wparent->programName + ".ini";
    QSettings *ini_settings;
    ini_settings = new QSettings(iniFname, QSettings::IniFormat);
    QStringList keyidList = ini_settings->value("RecipientInformation/KeyidList").toStringList();
    for(int ii = 0; ii < keyidList.count(); ii++){
        QString keyid = keyidList[ii];
//        QString title = settings.value("Title_" + keyid).toString();
        QString title = ini_settings->value("RecipientInformation/Title_" + keyid).toString();
        m_ui->comboBox_Recipient->addItem(QIcon(), title, keyid);
    }
}

void DialogAddressBook::addKeyidList(QString keyid, QString title, QString fpath, QString isRecipient)
{
//    QSettings settings(wparent->programName, "Recipient Information");
//    QStringList keyidList = settings.value("KeyidList").toStringList();
    QString iniFname = wparent->programName + ".ini";
    QSettings *ini_settings;
    ini_settings = new QSettings(iniFname, QSettings::IniFormat);
    QStringList keyidList = ini_settings->value("RecipientInformation/KeyidList").toStringList();
    if(keyidList.indexOf(keyid) == -1){
        keyidList.append(keyid);
//        settings.setValue("KeyidList", keyidList);
        ini_settings->setValue("RecipientInformation/KeyidList", keyidList);
    }
//    settings.setValue("Title_" + keyid, title);
//    settings.setValue("Fname_" + keyid, fpath);
//    settings.setValue("IsRecipient_" + keyid, isRecipient);
    ini_settings->setValue("RecipientInformation/Title_" + keyid, title);
    ini_settings->setValue("RecipientInformation/Fname_" + keyid, fpath);
    ini_settings->setValue("RecipientInformation/IsRecipient_" + keyid, isRecipient);
}

void DialogAddressBook::deleteRecipient(QString keyid)
{
    QTextCodec *codec = QTextCodec::codecForName("Shift-JIS");
    QTextDecoder *decoder = codec->makeDecoder();

    CGpgExec *gpgif = new CGpgExec(this);
    QString msg;
    bool stat = gpgif->gpgExecute("delete-keys", keyid, "", &msg);
    if(stat && msg.isEmpty()){
//        QSettings settings(wparent->programName, "Recipient Information");
//        QStringList keyidList = settings.value("KeyidList").toStringList();
        QString iniFname = wparent->programName + ".ini";
        QSettings *ini_settings;
        ini_settings = new QSettings(iniFname, QSettings::IniFormat);
        QStringList keyidList = ini_settings->value("RecipientInformation/KeyidList").toStringList();
        int index = keyidList.indexOf(keyid);
        if(index != -1){
            keyidList.removeAt(index);
//            settings.setValue("KeyidList", keyidList);
            ini_settings->setValue("RecipientInformation/KeyidList", keyidList);
        }
//        settings.remove("Title_" + keyid);
//        settings.remove("Fname_" + keyid);
        ini_settings->remove("RecipientInformation/Title_" + keyid);
        ini_settings->remove("RecipientInformation/Fname_" + keyid);

        // Remove temporary key file
        if(isTemporaryKeyFile){

            isTemporaryKeyFile = false;

            QFile::remove(m_ui->label_FileName->text());
        }

        setRecipientComboBox();
        wparent->setRecipientComboBox();

        clearRecipientInformation();
    }
    else{
        QMessageBox::information(this, tr("Confirm"), decoder->toUnicode(msg.toAscii()));
    }
}

void DialogAddressBook::on_comboBox_Recipient_currentIndexChanged(int index)
{
    bool stat = true;
    QString msg;

    if(! isIgnoreIndexChange){
        if((isImported) || (isTitleOrCheckChanged)){
            if(isImported){
                msg = tr("Cancel import?");
            }
            else{
                msg = tr("Cancel edit?");
            }
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, tr("Confirm"),
                                            msg,
                                            QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes){
                isImported = false;
                isTitleOrCheckChanged = false;

                QString keyid = m_ui->label_PubKeyId->text();
                deleteRecipient(keyid);
            }
            else{
                isIgnoreIndexChange = true;
                if(isImported){
                    m_ui->comboBox_Recipient->setCurrentIndex(0);
                }
                else{
                    QString keyid = m_ui->label_PubKeyId->text();
                    int windex = m_ui->comboBox_Recipient->findData (keyid, Qt::UserRole, Qt::MatchExactly | Qt::MatchCaseSensitive );
                    m_ui->comboBox_Recipient->setCurrentIndex(windex);
                }
                isIgnoreIndexChange = false;

                stat = false;
            }
        }

        if(stat){
            QString keyid = m_ui->comboBox_Recipient->itemData(index, Qt::UserRole).toString();

            clearRecipientInformation();

            if(!keyid.isEmpty()){
//                QSettings settings(wparent->programName, "Recipient Information");
//                QString title = settings.value("Title_" + keyid).toString();
//                QString fname = settings.value("Fname_" + keyid).toString();
//                QString isRecipient = settings.value("IsRecipient_" + keyid).toString();
                QString iniFname = wparent->programName + ".ini";
                QSettings *ini_settings;
                ini_settings = new QSettings(iniFname, QSettings::IniFormat);
                QString title = ini_settings->value("RecipientInformation/Title_" + keyid).toString();
                QString fname = ini_settings->value("RecipientInformation/Fname_" + keyid).toString();
                QString isRecipient = ini_settings->value("RecipientInformation/IsRecipient_" + keyid).toString();
                QString uid = displayRecipientInformation(keyid);
                displayRecipientFileInformation(fname, title, isRecipient);
            }
        }
    }
}

void DialogAddressBook::on_pushButton_NewRecipient_clicked()
{
    bool stat = true;
    QString msg;
    if((isImported) || (isTitleOrCheckChanged)){
        if(isImported){
            msg = tr("Cancel import?");
        }
        else{
            msg = tr("Cancel edit?");
        }
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Confirm"),
                                        msg,
                                        QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes){
            QString keyid = m_ui->label_PubKeyId->text();
            isImported = false;
            isTitleOrCheckChanged = false;

            deleteRecipient(keyid);
        }
        else{
            stat = false;
        }
    }

    if(stat){
        QFileDialog::Options options;
        QString selectedFilter;
        QString wopenFilesPath;
        QString fileName = QFileDialog::getOpenFileName(
                                    this, tr("Select public key file."),
                                    m_ui->label_FileName->text(),
                                    tr("Public Key Files (*.asc;*.pub);;All Files (*.*)"),
                                    &selectedFilter,
                                    options);
        if (!fileName.isEmpty()){
            isTemporaryKeyFile = false;

            setCursor(Qt::WaitCursor);

            importPublicKeyFile(fileName);

            setCursor(Qt::ArrowCursor);
        }
    }
}

void DialogAddressBook::on_pushButton_OK_clicked()
{
    QString keyid = m_ui->label_PubKeyId->text();
    QString title =  m_ui->lineEdit_Title->text();
    QString fpath =  m_ui->label_FileName->text();

    if(isPublicKeyPasted){
        isPublicKeyPasted = false;
        importPublicKeyText();
    }
    else{
        QString msg;
        if((isImported) || (isTitleOrCheckChanged)){
            if(isImported){
                msg = tr("Entry new recipient?");
            }
            else{
                msg = tr("Fix the change?");
            }

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, tr("Confirm"),
                                            msg,
                                            QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes){

                isImported = false;
                isTitleOrCheckChanged = false;
                isTemporaryKeyFile = false;

                QString isRecipient = "0";
                if(m_ui->checkBoxIsRecipient->isChecked()){
                    isRecipient = "1";
                }

                addKeyidList(keyid, title, fpath, isRecipient);

                setRecipientComboBox();
                wparent->setRecipientComboBox();

                int index = m_ui->comboBox_Recipient->findData (keyid, Qt::UserRole, Qt::MatchExactly | Qt::MatchCaseSensitive );
                m_ui->comboBox_Recipient->setCurrentIndex(index);

                QMessageBox::information(this, tr("Information"), tr("Entried."));
            }
            else if (reply == QMessageBox::No){
                if(isImported){
                    isImported = false;
                    isTitleOrCheckChanged = false;

                    deleteRecipient(keyid);
                }
                else{
                    isImported = false;
                    isTitleOrCheckChanged = false;

                    //int index = m_ui->comboBox_Recipient->findData (keyid, Qt::UserRole, Qt::MatchExactly | Qt::MatchCaseSensitive );
                    //if(index > 0){
                    //    title = m_ui->comboBox_Recipient->itemText(index);
                    //    m_ui->lineEdit_Title->setText(title);
                    //}
                    close();
                }
            }

        }
        else{
            close();
        }
    }
}

void DialogAddressBook::on_pushButton_Delete_clicked()
{
    if(isImported){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Confirm"),
                                        tr("Cancel import?"),
                                        QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes){
            isImported = false;
            isTitleOrCheckChanged = false;

            QString keyid = m_ui->label_PubKeyId->text();
            deleteRecipient(keyid);
        }
    }
    else{
        int index;
        index = m_ui->comboBox_Recipient->currentIndex();
        if(index > 0){
            QString keyid = m_ui->comboBox_Recipient->itemData(index, Qt::UserRole).toString();
            if(!keyid.isEmpty()){

                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, tr("Confirm"),
                                                tr("Delete selected recipient?"),
                                                QMessageBox::Yes | QMessageBox::No);
                if (reply == QMessageBox::Yes){
                    isTitleOrCheckChanged = false;

                    deleteRecipient(keyid);
                }
            }
        }
    }
}

void DialogAddressBook::on_lineEdit_Title_textEdited(QString )
{
    if(m_ui->comboBox_Recipient->currentIndex() > 0){
        isTitleOrCheckChanged = true;
    }
}

void DialogAddressBook::on_plainTextEdit_PublicKey_textChanged()
{
    if(! m_ui->plainTextEdit_PublicKey->isReadOnly()){
        if(! m_ui->plainTextEdit_PublicKey->toPlainText().isEmpty()){
            isPublicKeyPasted = true;
        }
    }
}

void DialogAddressBook::on_checkBoxIsRecipient_toggled(bool checked)
{
}

void DialogAddressBook::on_checkBoxIsRecipient_clicked()
{
    if(m_ui->comboBox_Recipient->currentIndex() > 0){
        isTitleOrCheckChanged = true;
    }
}
