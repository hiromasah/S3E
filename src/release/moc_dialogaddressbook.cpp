/****************************************************************************
** Meta object code from reading C++ file 'dialogaddressbook.h'
**
** Created: Thu Oct 22 14:22:13 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dialogaddressbook.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialogaddressbook.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DialogAddressBook[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,
      60,   52,   18,   18, 0x08,
      97,   18,   18,   18, 0x08,
     138,   18,   18,   18, 0x08,
     182,  176,   18,   18, 0x08,
     229,   18,   18,   18, 0x08,
     260,   18,   18,   18, 0x08,
     287,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DialogAddressBook[] = {
    "DialogAddressBook\0\0on_checkBoxIsRecipient_clicked()\0"
    "checked\0on_checkBoxIsRecipient_toggled(bool)\0"
    "on_plainTextEdit_PublicKey_textChanged()\0"
    "on_lineEdit_Title_textEdited(QString)\0"
    "index\0on_comboBox_Recipient_currentIndexChanged(int)\0"
    "on_pushButton_Delete_clicked()\0"
    "on_pushButton_OK_clicked()\0"
    "on_pushButton_NewRecipient_clicked()\0"
};

const QMetaObject DialogAddressBook::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogAddressBook,
      qt_meta_data_DialogAddressBook, 0 }
};

const QMetaObject *DialogAddressBook::metaObject() const
{
    return &staticMetaObject;
}

void *DialogAddressBook::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DialogAddressBook))
        return static_cast<void*>(const_cast< DialogAddressBook*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogAddressBook::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_checkBoxIsRecipient_clicked(); break;
        case 1: on_checkBoxIsRecipient_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: on_plainTextEdit_PublicKey_textChanged(); break;
        case 3: on_lineEdit_Title_textEdited((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: on_comboBox_Recipient_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: on_pushButton_Delete_clicked(); break;
        case 6: on_pushButton_OK_clicked(); break;
        case 7: on_pushButton_NewRecipient_clicked(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
