#include "cgpgexec.h"
#include "ui_cgpgexec.h"
#include <QtGui>
#include <QDialog>

CGpgExec::CGpgExec(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::CGpgExec)
{
    wparent = (MainWindow *)parent;
    pathToGnuPG = wparent->pathToGnuPG;
    processExecutionTimeoutSeconds = wparent->processExecutionTimeoutSeconds;

    m_ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerProc()));
}

// NOT USED
CGpgExec::CGpgExec(bool *stat, QWidget *parent, QString request, QString param1, QString param2, QString *result) :
    QDialog(parent),
    m_ui(new Ui::CGpgExec)
{
    wparent = (MainWindow *)parent;
    pathToGnuPG = wparent->pathToGnuPG;
    processExecutionTimeoutSeconds = wparent->processExecutionTimeoutSeconds;

    m_ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerProc()));

    QString keyid = param1;
    QString fpath = param2;
    m_ui->label_FileName->setText(fpath);
    QFile *file = new QFile(fpath);
    m_ui->label_FileSize->setText(QString("%L2").arg(file->size()));

    *stat = gpgExecute(request, keyid, fpath, result);
}

CGpgExec::~CGpgExec()
{
    delete m_ui;
    delete timer;
}

void CGpgExec::changeEvent(QEvent *e)
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

bool CGpgExec::gpgExecute(QString request, QString param1, QString param2, QString *result)
{
    QTextCodec *codec = QTextCodec::codecForName("Shift-JIS");
    QTextDecoder *decoder = codec->makeDecoder();

    QString cmdPath = pathToGnuPG;
    QProcess coprocess;
    QString filePath;
    QString keyid;
    bool stat = false;

    coprocess.setProcessChannelMode(QProcess::MergedChannels);

    if(request == "check"){
        filePath = param1;
        coprocess.start(cmdPath, QStringList() << "-n" << "--verbose" << "--import" << filePath);
        //coprocess.start(cmdPath, QStringList() << "--batch" << "--interactive" << "--import" << filePath);
    }
    else if(request == "import"){
        filePath = param1;
        coprocess.start(cmdPath, QStringList() << "--verbose" << "--import" << filePath);
    }
    else if(request == "fingerprint"){
        keyid = param1;
        coprocess.start(cmdPath, QStringList() << "--fingerprint" << keyid);
    }
    else if(request == "list-sigs"){
        keyid = param1;
        coprocess.start(cmdPath, QStringList() << "--list-sigs" << keyid);
    }
    else if(request == "delete-keys"){
        keyid = param1;
        coprocess.start(cmdPath, QStringList() << "--batch" << "--yes" << "--delete-keys" << keyid);
    }
//    else if(request == "encrypt"){
//        keyid = param1;
//        filePath = param2;
//        QProcess coprocess1;
//        coprocess1.setStandardOutputProcess(&coprocess);
//        coprocess1.start("cmd.exe", QStringList() << "/c" << "echo" << "y");
//        coprocess.start(cmdPath, QStringList() << "--command-fd" << "0" << "--encrypt" << "--recipient" << keyid << filePath);
//    }

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
//            if(request == "encrypt"){
//                if(result->isEmpty()
//                        || result->mid(15, 56) == "There is no assurance this key belongs to the named user"
//                        || result->mid(15, 56) == "この鍵が本当に本人のものである、という兆候が、ありません"
//                        ){
//                    sleepCount = timeoutSec;
//                    waitingFilePath = filePath + ".gpg";
//                    timer->start(1000);
//                    stat = true;
//               }
//                else{
//                    stat = false;
//                }
//            }
//            else{
                stat = true;
//            }
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

// NOT USED
void CGpgExec::timerProc()
{
    if(QFile::exists(waitingFilePath)){
        timer->stop();
        wparent->encriptionComplete(true);
        close();
    }
    else{
        sleepCount--;
        if(sleepCount <= 0){
            timer->stop();
            wparent->encriptionComplete(false);
            close();
        }
        else{
            timer->start(1000);
        }
    }
}
