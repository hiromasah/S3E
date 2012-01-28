/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Thu Oct 22 14:22:00 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      24,   11,   11,   11, 0x08,
      50,   11,   11,   11, 0x08,
      78,   11,   11,   11, 0x08,
     106,   11,   11,   11, 0x08,
     138,  132,   11,   11, 0x08,
     185,   11,   11,   11, 0x08,
     217,   11,   11,   11, 0x08,
     244,   11,   11,   11, 0x08,
     278,   11,   11,   11, 0x08,
     309,   11,   11,   11, 0x08,
     337,   11,   11,   11, 0x08,
     375,   11,   11,   11, 0x08,
     404,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0timerProc()\0"
    "on_actionHelp_triggered()\0"
    "on_action_About_triggered()\0"
    "on_actionDelete_triggered()\0"
    "on_action_Add_triggered()\0index\0"
    "on_comboBox_Recipient_currentIndexChanged(int)\0"
    "on_pushButton_Encrypt_clicked()\0"
    "on_action_Exit_triggered()\0"
    "on_actionAddress_Book_triggered()\0"
    "on_pushButton_Delete_clicked()\0"
    "on_pushButton_Add_clicked()\0"
    "on_actionUser_Information_triggered()\0"
    "on_pushButton_Exit_clicked()\0"
    "on_pushButton_Ref_clicked()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

const QMetaObject *MainWindow::metaObject() const
{
    return &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: timerProc(); break;
        case 1: on_actionHelp_triggered(); break;
        case 2: on_action_About_triggered(); break;
        case 3: on_actionDelete_triggered(); break;
        case 4: on_action_Add_triggered(); break;
        case 5: on_comboBox_Recipient_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: on_pushButton_Encrypt_clicked(); break;
        case 7: on_action_Exit_triggered(); break;
        case 8: on_actionAddress_Book_triggered(); break;
        case 9: on_pushButton_Delete_clicked(); break;
        case 10: on_pushButton_Add_clicked(); break;
        case 11: on_actionUser_Information_triggered(); break;
        case 12: on_pushButton_Exit_clicked(); break;
        case 13: on_pushButton_Ref_clicked(); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
