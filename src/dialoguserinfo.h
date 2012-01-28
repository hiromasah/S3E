#ifndef DIALOGUSERINFO_H
#define DIALOGUSERINFO_H

#include <QtGui/QDialog>
#include "mainwindow.h"

namespace Ui {
    class DialogUserInfo;
}

class DialogUserInfo : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(DialogUserInfo)
public:
    explicit DialogUserInfo(QWidget *parent = 0);
    virtual ~DialogUserInfo();
    QString getUserInfo(QString key);

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::DialogUserInfo *m_ui;
    MainWindow *wparent;

private slots:
    void on_pushButton_OK_clicked();
    void on_pushButton_Cancel_clicked();
};

#endif // DIALOGUSERINFO_H
