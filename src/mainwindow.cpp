#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialoguserinfo.h"
#include "dialogaddressbook.h"
#include "cgpgexec.h"
#include "formhelp.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    QCoreApplication::setOrganizationName(programName); //Avoid QSettings trouble in Vista x64
    QCoreApplication::addLibraryPath("plugins");

    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerProc()));

    programVersion = "1.06";
    programName = "S3E";
    formalProgramName = "Simple and Secure Software for Encryption";

    // Prepare help widget
    formHelp = new FormHelp(0, tr(formalProgramName.toAscii()) + "(" + programName + ")");

    QTextCodec *codec = QTextCodec::codecForName("Shift-JIS");
    QTextDecoder *decoder = codec->makeDecoder();

    if(QCoreApplication::arguments().size() > 1){
        QString firstArgument(QCoreApplication::arguments().at(1));
        if(firstArgument == "-uninstall"){
//            QSettings settings(programName, "Recipient Information");
//            settings.clear();
//            QSettings usettings(programName, "User Information");
//            usettings.clear();
            timer->start(1000);
            return;
        }
    }

    QString iniFname = programName + ".ini";
    QSettings *ini_settings;
    ini_settings = new QSettings(iniFname, QSettings::IniFormat);

    // Get the path to GnuPG
    pathToGnuPG = decoder->toUnicode(ini_settings->value("PathToGnuPG/PathToGnuPG").toByteArray());

    // Get Process Execution Timeout (default 60sec)
    processExecutionTimeoutSeconds = ini_settings->value("Timeout/ProcessExecution").toString();

    // Check the path to GnuPG
    if(! CheckPathToGnuPG(ini_settings)){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::critical(this, tr("Error"),
              "GNU PG : " + pathToGnuPG + " " +
              tr("is not found.") + "\n" +
              tr("Set the path to GNU PG in ini file."),
              QMessageBox::Ok);
    }

    // For the first run after installation
    bool isInstall = false;

    if(QCoreApplication::arguments().size() > 1){
        QString firstArgument(QCoreApplication::arguments().at(1));
        if(firstArgument == "-install"){
            isInstall = true;
        }
    }
    if(isInstall){
        presetOnInstall(ini_settings);
    }

    // Get user information
    DialogUserInfo *formu = new DialogUserInfo(this);
    userName = formu->getUserInfo("Name");
    userId = formu->getUserInfo("ID");
    if (isInstall || (userId == ""))
    {
        setWindowTitle(tr(formalProgramName.toAscii()) + "(" + programName + ")");
        QMessageBox::information(this, tr("Confirm"), tr("Please set user information."));
        formu->setModal(true);
        formu->show();
    }
    QString userInfo = userName + " (" + userId + ")";
    setWindowTitle(tr(formalProgramName.toAscii()) + "(" + programName + ")" + " - " + userInfo);

    rewriteFileStatus();

    clearWorkingFolder();
    
    // Get recipient list
    setRecipientComboBox();

    // Pickup drag and drop files
    if(QCoreApplication::arguments().size() > 1){
        QString firstArgument(QCoreApplication::arguments().at(1));
        if(firstArgument != "-install"){
            QStringList files;
            for(int ii = 1; ii < QCoreApplication::arguments().size(); ii++){
                QString path = QCoreApplication::arguments().at(ii);
                files.append(path);;
            }
            getTargetFiles(files);
        }
    }
}

MainWindow::~MainWindow()
{
    if (formHelp){
        formHelp->close();
    }

    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    if (formHelp){
        formHelp->close();
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}
void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        QStringList files;
        for (int ii = 0; ii < urlList.size(); ii++) {
            QString path = urlList.at(ii).path();
            files.append(path.mid(1));;
        }
        getTargetFiles(files);
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

bool MainWindow::CheckPathToGnuPG(QSettings *ini_settings)
{
    bool stat = true;

    QTextCodec *codec = QTextCodec::codecForName("Shift-JIS");
    QTextEncoder *encoder = codec->makeEncoder();

    // Check path to GnuPG
    if(! QFile::exists(pathToGnuPG)){
        // Set path to GnuPG
        pathToGnuPG = "c:/Program Files/gnu/gnupg/gpg.exe";
        if(! QFile::exists(pathToGnuPG)){
            QString pathToGnuPG_os64 = "c:/Program Files (x86)/gnu/gnupg/gpg.exe";
            if(QFile::exists(pathToGnuPG_os64)){
                pathToGnuPG = pathToGnuPG_os64;
            }
            else{
                QString pathToGnuPG_os2000 = "c:/gnu/gnupg/gpg.exe";
                if(QFile::exists(pathToGnuPG_os2000)){
                    pathToGnuPG = pathToGnuPG_os2000;
                }
            }
        }
        if(QFile::exists(pathToGnuPG)){
            ini_settings->setValue("PathToGnuPG/PathToGnuPG", QString(encoder->fromUnicode(pathToGnuPG)));
        }
        else{
            stat = false;
        }
    }
    return stat;
}

void MainWindow::presetOnInstall(QSettings *ini_settings)
{
//    QTextCodec *codec = QTextCodec::codecForName("Shift-JIS");
    QTextCodec *codec = QTextCodec::codecForName("System");
    QTextDecoder *decoder = codec->makeDecoder();
    QTextEncoder *encoder = codec->makeEncoder();

    // Preset user information
    QString wname = decoder->toUnicode(ini_settings->value("PresetUserInformation/Name").toByteArray());
    QString wid = ini_settings->value("PresetUserInformation/ID").toString();
//    QSettings u_settings(programName, "User Information");
//    u_settings.setValue("Name", wname);
//    u_settings.setValue("ID", wid);
//    ini_settings->setValue("PresetUserInformation/Name", QString(encoder->fromUnicode(wname)));
//    ini_settings->setValue("PresetUserInformation/ID", QString(encoder->fromUnicode(wid)));
    ini_settings->setValue("UserInformation/Name", wname);
    ini_settings->setValue("UserInformation/ID", wid);

    // Preset recipient list
    int presetKeyCount = ini_settings->value("PresetRecipientInformation/Count").toInt();
    if(presetKeyCount){
        DialogAddressBook *forma = new DialogAddressBook(this);
        char wbuf[32];
        QString wkey;
        for(int ii = 0; ii < presetKeyCount; ii++){
            ::snprintf(wbuf, 32, "PublicKeyTitle%d", ii + 1);
            wkey = QString::fromAscii(wbuf);
            QString title = decoder->toUnicode(ini_settings->value("PresetRecipientInformation/" + wkey).toByteArray());
//            ini_settings->setValue("PresetRecipientInformation/" + wkey, QString(encoder->fromUnicode(title)));

            ::snprintf(wbuf, 32, "PublicKeyFile%d", ii + 1);
            wkey = QString::fromAscii(wbuf);
            QString fname = ini_settings->value("PresetRecipientInformation/" + wkey).toString();
//            ini_settings->setValue("PresetRecipientInformation/" + wkey, QString(encoder->fromUnicode(fname)));

            ::snprintf(wbuf, 32, "IsRecipient%d", ii + 1);
            wkey = QString::fromAscii(wbuf);
            QString isRecipient = ini_settings->value("PresetRecipientInformation/" + wkey).toString();

            QString fpath = QDir::currentPath() + "/" + fname;
            forma->presetRecipientInformation(title, fpath, isRecipient);
        }
    }
}

void MainWindow::setRecipientComboBox()
{
    ui->comboBox_Recipient->clear();
    ui->comboBox_Recipient->addItem(QIcon(), "", "");
//    QSettings settings(programName, "Recipient Information");
//    QStringList keyidList = settings.value("KeyidList").toStringList();
    QString iniFname = programName + ".ini";
    QSettings *ini_settings;
    ini_settings = new QSettings(iniFname, QSettings::IniFormat);
    QStringList keyidList = ini_settings->value("RecipientInformation/KeyidList").toStringList();
    for(int ii = 0; ii < keyidList.count(); ii++){
        QString keyid = keyidList[ii];
//        QString title = settings.value("Title_" + keyid).toString();
//        QString isRecipient = settings.value("IsRecipient_" + keyid).toString();
        QString title = ini_settings->value("RecipientInformation/Title_" + keyid).toString();
        QString isRecipient = ini_settings->value("RecipientInformation/IsRecipient_" + keyid).toString();
        if(isRecipient == "1"){
            ui->comboBox_Recipient->addItem(QIcon(), title, keyid);
        }
    }
}

int MainWindow::isDup(QString fpath)
{
    int index = -1;

    QFileInfo *fileinfo = new QFileInfo(fpath);
    QString fname = fileinfo->fileName();
    for (int ii = 0; ii < ui->listWidget->count(); ii++) {
        if(ui->listWidget->item(ii)->text() == fpath) {
            index = ii;
            break;
        }
        QFileInfo fi(ui->listWidget->item(ii)->text());
        if(fname == fi.fileName()){
            index = ii;
            break;
        }
    }
    return index;
}

void MainWindow::rewriteFileStatus()
{
    int fileCount = 0;
    qint64 totalFileSize = 0;
    qint64 tera = Q_INT64_C(1099511627776);
    qint64 peta = Q_INT64_C(1125899906842624);

    for (int ii = 0; ii < ui->listWidget->count(); ii++)
    {
        QString fpath = ui->listWidget->item(ii)->text();
        QFile *file = new QFile(fpath);
        totalFileSize += file->size();
        fileCount++;
    }
    QString fileSizeString = "";
    if (totalFileSize == 0)
    {
        fileSizeString = "0";
    }
    else
    {
        fileSizeString = QString("%L2").arg(totalFileSize);
    }
    QString aboutFileSizeString = "";
    int aboutFileSize;
    if(totalFileSize < 1024){
        aboutFileSizeString = "";
    }
    else if(totalFileSize < 1024 * 1024){
        aboutFileSize = (int)(totalFileSize / 1024);
        aboutFileSizeString = " (" + tr("about") + QString("%1").arg(aboutFileSize) + tr("Kbyte") + ")";
    }
    else if (totalFileSize < 1073741824) // １ギガ 1024 * 1024 * 1024
    {
        aboutFileSize = (int)(totalFileSize / (1024 * 1024));
        aboutFileSizeString = " (" + tr("about") + QString("%1").arg(aboutFileSize) + tr("Mbyte") + ")";
    }
    else if (totalFileSize < tera) // １テラ 1024 * 1024 * 1024 * 1024
    {
        aboutFileSize = (int)(totalFileSize / (1073741824));
        aboutFileSizeString = " (" + tr("about") + QString("%1").arg(aboutFileSize) + tr("Gbyte") + ")";
    }
    else if (totalFileSize < peta) // １ペタ 1024 * 1024 * 1024 * 1024 * 1024
    {
        aboutFileSize = (int)(totalFileSize / (tera));
        aboutFileSizeString = " (" + tr("about") + QString("%1").arg(aboutFileSize) + tr("Tbyte") + ")";
    }

    ui->labelFileStatus->setText(tr("Selected File Count : ") + QString("%1").arg(fileCount) + "    " + tr("Total File Size : ") + fileSizeString + aboutFileSizeString);
}

void MainWindow::clearWorkingFolder()
{
    QDir dir(".");
    QStringList files = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Readable);
    for( int ii = 0; ii < files.count(); ii++){
        int len = userId.length();
        if(files[ii].left(len + 3) == userId + "_20"){
            eraseFilesInFolder(files[ii]);
            dir.rmdir(files[ii]);
        }
    }
}

void MainWindow::eraseFilesInFolder(QString folder)
{
    QDir dir(folder);
    QStringList files = dir.entryList(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Readable);
    for( int ii = 0; ii < files.count(); ii++){
        QFile::remove(folder + "/" + files[ii]);
    }
}

void MainWindow::on_pushButton_Ref_clicked()
{
    QFileDialog::Options options;
    QString selectedFilter;
    options |= QFileDialog::ShowDirsOnly;
    QString folderName = QFileDialog::getExistingDirectory(this,
                                tr("Select output folder"),
                                ui->lineEdit_OutputFolder->text(),
                                options);
    if (!folderName.isEmpty())
        ui->lineEdit_OutputFolder->setText(folderName);
}

void MainWindow::on_pushButton_Exit_clicked()
{
    close();
}

void MainWindow::on_actionUser_Information_triggered()
{
    DialogUserInfo *formu = new DialogUserInfo(this);
    formu->setModal(true);
    formu->show();

    userName = formu->getUserInfo("Name");
    userId = formu->getUserInfo("ID");
    QString userInfo = userName + " (" + userId + ")";
    setWindowTitle(tr(formalProgramName.toAscii()) + "(" + programName + ")" + " - " + userInfo);
}

void MainWindow::on_pushButton_Add_clicked()
{
    QFileDialog::Options options;
//        options |= QFileDialog::DontUseNativeDialog;
    QString selectedFilter;
    QStringList files = QFileDialog::getOpenFileNames(
                                this, tr("Select target files."),
                                openFilesPath,
                                tr("All Files (*)"),
                                &selectedFilter,
                                options);
    if (files.count()) {
        getTargetFiles(files);
    }
}

void MainWindow::getTargetFiles(QStringList files)
{
    for (int ii = 0; ii < files.count(); ii++) {
        QFileInfo *fileinfo = new QFileInfo(files[ii]);
        if(fileinfo->isFile()){
            if(! getTargetFile(files[ii], files.count() - ii - 1)){
                break;
            }
        }
        else{
            QMessageBox::StandardButton reply;
            reply = QMessageBox::information(this, tr("Confirm"),
                     tr("Select all files in the folder?") + "\n\n" + files[ii],
                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Abort);
            if (reply == QMessageBox::Yes){
                if(! getTargetFolder(files[ii])){
                    break;
                }
            }
            else if(reply == QMessageBox::No){
                continue;
            }
            else{
                break;
            }
        }
    }
    rewriteFileStatus();
}

bool MainWindow::getTargetFolder(QString folder)
{
    bool isContinue = true;

    QDir dir(folder);
    QStringList files = dir.entryList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks | QDir::Readable);
    for( int ii = 0; ii < files.count(); ii++){
        QFileInfo *fileinfo = new QFileInfo(folder + "/" + files[ii]);
        if(fileinfo->isFile()){
            if(!getTargetFile(folder + "/" + files[ii], files.count() - ii - 1)){
                isContinue = false;
                break;
            }
        }
        else{
            QMessageBox::StandardButton reply;
            reply = QMessageBox::information(this, tr("Confirm"),
                     tr("Select all files in the folder?") + "\n\n" + folder + "/" + files[ii],
                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Abort);
            if (reply == QMessageBox::Yes){
                if(! getTargetFolder(folder + "/" + files[ii])){
                    isContinue = false;
                    break;
                }
            }
            else if (reply == QMessageBox::No){
                continue;
            }
            else{
                isContinue = false;
                break;
            }
        }
    }

    return isContinue;
}

bool MainWindow::getTargetFile(QString fpath, int rest)
{
    bool isContinue = true;
    int dupIndex;

    dupIndex = isDup(fpath);
    if (dupIndex != -1) {
        QMessageBox::StandardButton reply;
        if(rest > 0){
            reply = QMessageBox::information(this, tr("Confirm"),
                tr("Duplicate file name. Replace?") + "\n\n" + ui->listWidget->item(dupIndex)->text() + "\n   " + tr("to") + "\n" + fpath,
                QMessageBox::Yes | QMessageBox::No | QMessageBox::Abort);
            if(reply == QMessageBox::Abort){
                isContinue = false;
            }
            else if(reply == QMessageBox::Yes){
                ui->listWidget->item(dupIndex)->setText(fpath);
            }
        }
        else{
            reply = QMessageBox::information(this, tr("Confirm"),
                tr("Duplicate file name. Replace?") + "\n\n" + ui->listWidget->item(dupIndex)->text() + "\n   " + tr("to") + "\n" + fpath,
                QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes){
                ui->listWidget->item(dupIndex)->setText(fpath);
            }
        }
    }
    else{
        ui->listWidget->addItem(fpath);
    }
    return isContinue;
}

void MainWindow::on_pushButton_Delete_clicked()
{
    QStringList wlist;
    for (int ii = 0; ii < ui->listWidget->count(); ii++) {
        if (! ui->listWidget->item(ii)->isSelected()) {
            wlist.append(ui->listWidget->item(ii)->text());
        }
    }
    ui->listWidget->clear();
    ui->listWidget->addItems(wlist);

    rewriteFileStatus();
}

void MainWindow::on_actionAddress_Book_triggered()
{
    DialogAddressBook *form = new DialogAddressBook(this);
    form->setModal(true);
    form->show();
}

void MainWindow::on_action_Exit_triggered()
{
    close();
}

void MainWindow::on_pushButton_Encrypt_clicked()
{
    bool isWorking = false;
    bool copyStat;
    QString copyErrorPath;
    QTextCodec *codec = QTextCodec::codecForName("Shift-JIS");
    QTextDecoder *decoder = codec->makeDecoder();
    QTextEncoder *encoder = codec->makeEncoder();

    if(ui->listWidget->count()){
        QString keyid = "";

        // Get recipient index.
        int index = ui->comboBox_Recipient->currentIndex();

        if(index <= 0){
            QMessageBox::information(this, tr("Confirm"), tr("Select the recipient."));
            return;
        }
        else{
            // Get public key id.
            keyid = ui->comboBox_Recipient->itemData(index, Qt::UserRole).toString();
            if(keyid.isEmpty()){
                QMessageBox::information(this, tr("Confirm"), tr("Select the recipient."));
                return;
            }
        }

        // Check if the output folder is selected.
        if(ui->lineEdit_OutputFolder->text() == ""){
            QMessageBox::information(this, tr("Confirm"), tr("Select the output folder."));
            return;
        }

        // Get current date-time string.
        QString yyyymmddhhmmss = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");

        // Make the working folder.
        workingFolder = userId + "_" + yyyymmddhhmmss;
        QDir *dir = new QDir(".");
        if(dir->mkdir(workingFolder)){

            setCursor(Qt::WaitCursor);

            // Copy target files into the working folder.
            int fileCount = 0;
            copyStat = true;
            for (int ii = 0; ii < ui->listWidget->count(); ii++)
            {
                QString fpath = ui->listWidget->item(ii)->text();
                QFile *file = new QFile(fpath);
                QFileInfo *fileinfo = new QFileInfo(fpath);
                
                // 2009-10-16 Check result of copy function
                if(file->copy(workingFolder + "/" + fileinfo->fileName())){
                    fileCount++;
                }
                else{
                    copyErrorPath = fpath;
                    copyStat = false;
                    break;
                }
            }
            
            if(copyStat){
                // Load tar32.dll.
                typedef int (StrFunc)(const HWND,const char *,char *,const int);
                QLibrary lib("tar32"); //tar32.dll
                StrFunc *func = (StrFunc *) lib.resolve("Tar");
                if (func){
                    // Make file and path names.
                    tgzFname = userId + "_" + yyyymmddhhmmss + ".tgz";

                    // Compress target files to tgz format.
                    QString param = "cfz \"" + encoder->fromUnicode(tgzFname) + "\" \"" + workingFolder + "\"";
                    char rbuf[1024];
                    rbuf[0] = '\0';
                    int tstat = func(NULL, param.toAscii(), rbuf, 1024);

                    if(tstat == 0){
                        //QMessageBox::information(this, tr("Confirm"), decoder->toUnicode(rbuf));

                        // Encrypt the tgz file.
                        QString msg;
                        bool stat;
                        //CGpgExec *gpgif = new CGpgExec(&stat, this, "encrypt", keyid, tgzFname, &msg);
                        //gpgif->setModal(true);
                        //gpgif->show();
                        //CGpgExec *gpgif = new CGpgExec(this);
                        //stat = gpgif->gpgExecute("encrypt", keyid, tgzFname, &msg);
                        stat = encryptExecute(keyid, tgzFname, &msg);
                        //QMessageBox::information(this, tr("Confirm"), decoder->toUnicode(msg.toAscii()));
                        if(stat){
                            if(QFile::exists(tgzFname + ".gpg")){
                                encriptionComplete(true);
                            }
                            else{
                               encriptionComplete(false);
                            }
                        }
                        else{
                            // gpg returned some error.
                            if(msg.contains("write error:")){
                                QMessageBox::information(this, tr("Confirm"), decoder->toUnicode(msg.toAscii()) + "\n\n"
                                    + tr("Encryption aborted.") + "\n"
                                    + tr("Not enough space is available for encryption.") + "\n"
                                    + tr("Check free space of the disk this program installed.") + "\n"
                                    + tr("About twice the free space of the target file is needed."));
                            }
                            else{
                                QMessageBox::information(this, tr("Confirm"), decoder->toUnicode(msg.toAscii()) + "\n\n"
                                    + tr("Encryption aborted."));
                            }
                            
                            if(QFile::exists(tgzFname)){
                                QFile::remove(tgzFname);
                            }
                            if(QFile::exists(tgzFname + ".gpg")){
                                QFile::remove(tgzFname + ".gpg");
                            }
                        }
                    }
                    else{
                        // tar32.dll returned error.
                        lib.unload();
                        if(QFile::exists(tgzFname)){
                            QFile::remove(tgzFname);
                        }
                        
                        if((decoder->toUnicode(rbuf)).contains("tar: Out of tape (Use -m)")){
                            QMessageBox::information(this, tr("Confirm"),
                                tr("Encryption aborted.") + "\n"
                                + tr("Not enough space is available for encryption.") + "\n"
                                + tr("Check free space of the disk this program installed.") + "\n"
                                + tr("About twice the free space of the target file is needed."));
                        }
                        else{
                            QMessageBox::information(this, tr("Confirm"), decoder->toUnicode(rbuf) + "\n\n"
                                + tr("Encryption aborted.") + "\n"
                                + tr("Not enough space is available for encryption.") + "\n"
                                + tr("Check free space of the disk this program installed.") + "\n"
                                + tr("About twice the free space of the target file is needed."));
                        }
                    }
                }
                else{
                    // tar32.dll load error.
                    QMessageBox::information(this, tr("Confirm"), tr("Can't load tar32.dll.") + "\n\n"
                        + tr("Encryption aborted."));
                }
            }
            else{
                QMessageBox::information(this, tr("Confirm"), tr("Can't copy the target file into the working folder.")
                    + "(" + copyErrorPath + ")\n\n"
                    + tr("Encryption aborted.") + "\n"
                    + tr("Not enough space is available for encryption.") + "\n"
                    + tr("Check free space of the disk this program installed.") + "\n"
                    + tr("About twice the free space of the target file is needed."));
            }
            
            if(! isWorking){
                // Clear working folder.
                for (int ii = 0; ii < ui->listWidget->count(); ii++)
                {
                    QString fpath = ui->listWidget->item(ii)->text();
                    QFile *file = new QFile(fpath);
                    QFileInfo *fileinfo = new QFileInfo(fpath);
                    QString wfpath = workingFolder + "/" + fileinfo->fileName();
                    if(QFile::exists(wfpath)){
                        file->remove(wfpath);
                    }
                }
                dir->rmdir(workingFolder);

                setCursor(Qt::ArrowCursor);
            }
        }
        else{
            // Can't make working folder.
            QMessageBox::information(this, tr("Confirm"), tr("Can't make the working folder.") + "\n\n"
                + tr("Encryption aborted.") + "\n"
                + tr("Not enough space is available for encryption.") + "\n"
                + tr("Check free space of the disk this program installed.") + "\n"
                + tr("About twice the free space of the target file is needed."));
        }
    }
}
bool MainWindow::encryptExecute(QString keyid, QString filePath, QString *result)
{
    QTextCodec *codec = QTextCodec::codecForName("Shift-JIS");
    QTextDecoder *decoder = codec->makeDecoder();

    QString cmdPath = pathToGnuPG;
    QProcess coprocess;
    bool stat = false;

    coprocess.setProcessChannelMode(QProcess::MergedChannels);

    QProcess coprocess1;
    coprocess1.setStandardOutputProcess(&coprocess);
    coprocess1.start("cmd.exe", QStringList() << "/c" << "echo" << "y");
    coprocess.start(cmdPath, QStringList() << "--command-fd" << "0" << "--encrypt" << "--recipient" << keyid << filePath);

    if (coprocess.waitForStarted()){
        int timeoutSec = 60;
        if(! processExecutionTimeoutSeconds.isEmpty()){
            bool ok;
            timeoutSec = processExecutionTimeoutSeconds.toInt(&ok, 10);
            if(timeoutSec == 0){
                timeoutSec = 60;
            }
        }
        if (!coprocess.waitForFinished(timeoutSec * 1000)){
            QMessageBox::information(this, tr("Confirm"), decoder->toUnicode(coprocess.readAll()));
        }
        else{
            *result = QString(coprocess.readAll());
            // 2009-10-16 Change judgement of result.
            if(result->isEmpty()){
                stat = true;
            }
            else{
                //"There is no assurance this key belongs to the named user"
                //"この鍵が本当に本人のものである、という兆候が、ありません"
                //これはエラーではありません。
                if((result->contains("encryption failed:")) || (result->contains("write error:"))){
                    stat = false;
                }
                else{
                    stat = true;
                }
            }
        }
    }
    else{
        QString errmsg = coprocess.errorString();
        QMessageBox::StandardButton reply;
        reply = QMessageBox::critical(this, tr("Error"),
                                        tr("Can't start GNU PG."),
                                        QMessageBox::Abort);
        if (reply == QMessageBox::Abort){
            close();
        }
    }
    return stat;
}

void MainWindow::on_comboBox_Recipient_currentIndexChanged(int index)
{
    ui->labelPublicKeyFile->setText("");

    if(index > 0){
        QString keyid = ui->comboBox_Recipient->itemData(index, Qt::UserRole).toString();
        if(! keyid.isEmpty()){
//            QSettings settings(programName, "Recipient Information");
//            QString publicKeyFname = settings.value("Fname_" + keyid).toString();
            QString iniFname = programName + ".ini";
            QSettings *ini_settings;
            ini_settings = new QSettings(iniFname, QSettings::IniFormat);
            QString publicKeyFname = ini_settings->value("RecipientInformation/Fname_" + keyid).toString();
            if(QFile::exists(publicKeyFname)){
                ui->labelPublicKeyFile->setText(tr("Public Key File : ") + publicKeyFname);
            }
        }
    }
}

void MainWindow::encriptionComplete(bool stat)
{
    //QTextCodec *codec = QTextCodec::codecForName("Shift-JIS");
    QTextCodec *codec = QTextCodec::codecForName("System");
    QTextEncoder *encoder = codec->makeEncoder();

    if(stat){
        QString gpgfname = tgzFname + ".gpg";
        QString receiptfname = workingFolder + ".txt";
        QString gpgPath = ui->lineEdit_OutputFolder->text() + "/" + gpgfname;
        QString receiptPath = ui->lineEdit_OutputFolder->text() + "/" + receiptfname;

        // Move encrypted file to the target folder.
        QFile::rename(gpgfname, gpgPath);

        // Make receipt file.
        QByteArray block;
        QFile rfile(receiptPath);
        if (rfile.open(QFile::WriteOnly | QFile::Text)){
            QFile *file = new QFile(gpgPath);
            block += "EF : " + encoder->fromUnicode(gpgfname) + "\n";
            block += "FS : " + QString("%1").arg(file->size()) + "\n";
            block += "-------------------------------------------------\n";
            for (int ii = 0; ii < ui->listWidget->count(); ii++)
            {
                QString fpath = ui->listWidget->item(ii)->text();
                QFileInfo *fileinfo = new QFileInfo(fpath);
                block += "IF : " + encoder->fromUnicode(fileinfo->fileName()) + "\n";
            }
            rfile.write(block);
            rfile.close();

            QMessageBox::information(this, tr("Confirm"), tr("Encryption Completed.") + "\n\n" + tr("Encrypted File") + ": " + gpgPath + "\n\n" + tr("Receipt File") + ": " + receiptPath);
        }
        else{
            // Can't make receipt file.
            QMessageBox::StandardButton reply;
            reply = QMessageBox::critical(this, tr("Error"),
                                            tr("Can't make receipt file.") + "(" + receiptPath + ")",
                                            QMessageBox::Abort);
            if (reply == QMessageBox::Abort){
                close();
            }
        }
    }
    else{
        QMessageBox::information(this, tr("Confirm"), tr("Encryption failed.") + "\n" + tr("Click Encript Button once more."));
    }

    QFile::remove(tgzFname);

    // Clear working folder.
    for (int ii = 0; ii < ui->listWidget->count(); ii++)
    {
        QString fpath = ui->listWidget->item(ii)->text();
        QFile *file = new QFile(fpath);
        QFileInfo *fileinfo = new QFileInfo(fpath);
        file->setPermissions(workingFolder + "/" + fileinfo->fileName(), QFile::WriteOwner);
        file->remove(workingFolder + "/" + fileinfo->fileName());
    }
    QDir *dir = new QDir(".");
    dir->rmdir(workingFolder);

    if(stat){
        // Clear the main form
        ui->listWidget->clear();
        ui->comboBox_Recipient->setCurrentIndex(0);
        ui->lineEdit_OutputFolder->setText("");
        rewriteFileStatus();
    }

    setCursor(Qt::ArrowCursor);
}

void MainWindow::on_action_Add_triggered()
{
    on_pushButton_Add_clicked();
}

void MainWindow::on_actionDelete_triggered()
{
    on_pushButton_Delete_clicked();
}

void MainWindow::on_action_About_triggered()
{
    QMessageBox::about(this, "About " + tr(formalProgramName.toAscii()) + "(" + programName + ")",
        tr(formalProgramName.toAscii()) + "(" + programName + ")" + "    Version : " + programVersion + "\n\n\n" +
        tr(formalProgramName.toAscii()) + "(" + programName + ")" + tr(" is a helper tool for encrypt files using GnuPG.") + "\n\n" +
        tr("Selected files are pack into a file tar.gz format, and it is encripted by GnuPG.") + "\n\n");
}

void MainWindow::on_actionHelp_triggered()
{
    formHelp->show();
    formHelp->activateWindow();
}

void MainWindow::timerProc()
{
    timer->stop();
    close();
}
