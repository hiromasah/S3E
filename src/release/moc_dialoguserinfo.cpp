/****************************************************************************
** Meta object code from reading C++ file 'dialoguserinfo.h'
**
** Created: Thu Oct 22 14:22:07 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dialoguserinfo.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialoguserinfo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogUserInfo[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x08,
      43,   15,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogUserInfo[] = {
    "DialogUserInfo\0\0on_pushButton_OK_clicked()\0"
    "on_pushButton_Cancel_clicked()\0"
};

const QMetaObject DialogUserInfo::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogUserInfo,
      qt_meta_data_DialogUserInfo, 0 }
};

const QMetaObject *DialogUserInfo::metaObject() const
{
    return &staticMetaObject;
}

void *DialogUserInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogUserInfo))
        return static_cast<void*>(const_cast< DialogUserInfo*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogUserInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pushButton_OK_clicked(); break;
        case 1: on_pushButton_Cancel_clicked(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
