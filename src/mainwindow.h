#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtGui/QMainWindow>
#include "formhelp.h"

namespace Ui
{
    class MainWindow;
    class QDragEnterEvent;
    class QDropEvent;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setRecipientComboBox();
    void encriptionComplete(bool stat);

    QString pathToGnuPG;
    QString processExecutionTimeoutSeconds;
    QString formalProgramName, programName, programVersion;
    QString userName, userId;

private:
    bool CheckPathToGnuPG(QSettings *ini_settings);
    void presetOnInstall(QSettings *ini_settings);
    int isDup(QString fpath);
    void rewriteFileStatus();
    void clearWorkingFolder();
    void eraseFilesInFolder(QString folder);
    void getTargetFiles(QStringList files);
    bool getTargetFolder(QString folder);
    bool getTargetFile(QString fpath, int cnt);
    bool encryptExecute(QString keyid, QString filePath, QString *result);

    QTimer *timer;
    Ui::MainWindow *ui;
    FormHelp *formHelp;
    QString openFilesPath;
    QString workingFolder, tgzFname;

private slots:
    void timerProc();
    void on_actionHelp_triggered();
    void on_action_About_triggered();
    void on_actionDelete_triggered();
    void on_action_Add_triggered();
    void on_comboBox_Recipient_currentIndexChanged(int index);
    void on_pushButton_Encrypt_clicked();
    void on_action_Exit_triggered();
    void on_actionAddress_Book_triggered();
    void on_pushButton_Delete_clicked();
    void on_pushButton_Add_clicked();
    void on_actionUser_Information_triggered();
    void on_pushButton_Exit_clicked();
    void on_pushButton_Ref_clicked();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
