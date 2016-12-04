/****************************************************************************
** Meta object code from reading C++ file 'ui_upload.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/ui_upload.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ui_upload.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ui_upload_t {
    QByteArrayData data[9];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui_upload_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui_upload_t qt_meta_stringdata_ui_upload = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ui_upload"
QT_MOC_LITERAL(1, 10, 6), // "reload"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 12), // "btnStateSave"
QT_MOC_LITERAL(4, 31, 7), // "is_work"
QT_MOC_LITERAL(5, 39, 14), // "btnStateDelete"
QT_MOC_LITERAL(6, 54, 18), // "on_btnSave_clicked"
QT_MOC_LITERAL(7, 73, 20), // "on_btnDelete_clicked"
QT_MOC_LITERAL(8, 94, 20) // "on_btnCancel_clicked"

    },
    "ui_upload\0reload\0\0btnStateSave\0is_work\0"
    "btnStateDelete\0on_btnSave_clicked\0"
    "on_btnDelete_clicked\0on_btnCancel_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui_upload[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    1,   55,    2, 0x0a /* Public */,
       3,    0,   58,    2, 0x2a /* Public | MethodCloned */,
       5,    1,   59,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x2a /* Public | MethodCloned */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ui_upload::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ui_upload *_t = static_cast<ui_upload *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->reload(); break;
        case 1: _t->btnStateSave((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->btnStateSave(); break;
        case 3: _t->btnStateDelete((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->btnStateDelete(); break;
        case 5: _t->on_btnSave_clicked(); break;
        case 6: _t->on_btnDelete_clicked(); break;
        case 7: _t->on_btnCancel_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject ui_upload::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ui_upload.data,
      qt_meta_data_ui_upload,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ui_upload::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui_upload::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ui_upload.stringdata0))
        return static_cast<void*>(const_cast< ui_upload*>(this));
    return QDialog::qt_metacast(_clname);
}

int ui_upload::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
