/****************************************************************************
** Meta object code from reading C++ file 'cgpgexec.h'
**
** Created: Thu Oct 22 14:22:20 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cgpgexec.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cgpgexec.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CGpgExec[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CGpgExec[] = {
    "CGpgExec\0\0timerProc()\0"
};

const QMetaObject CGpgExec::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CGpgExec,
      qt_meta_data_CGpgExec, 0 }
};

const QMetaObject *CGpgExec::metaObject() const
{
    return &staticMetaObject;
}

void *CGpgExec::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CGpgExec))
        return static_cast<void*>(const_cast< CGpgExec*>(this));
    return QDialog::qt_metacast(_clname);
}

int CGpgExec::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: timerProc(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
