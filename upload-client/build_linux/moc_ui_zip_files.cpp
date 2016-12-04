/****************************************************************************
** Meta object code from reading C++ file 'ui_zip_files.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/ui_zip_files.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ui_zip_files.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ui_zip_files_t {
    QByteArrayData data[12];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui_zip_files_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui_zip_files_t qt_meta_stringdata_ui_zip_files = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ui_zip_files"
QT_MOC_LITERAL(1, 13, 12), // "pack_started"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 12), // "file_started"
QT_MOC_LITERAL(4, 40, 4), // "file"
QT_MOC_LITERAL(5, 45, 4), // "name"
QT_MOC_LITERAL(6, 50, 13), // "file_progress"
QT_MOC_LITERAL(7, 64, 4), // "done"
QT_MOC_LITERAL(8, 69, 5), // "total"
QT_MOC_LITERAL(9, 75, 8), // "finished"
QT_MOC_LITERAL(10, 84, 7), // "z_error"
QT_MOC_LITERAL(11, 92, 4) // "text"

    },
    "ui_zip_files\0pack_started\0\0file_started\0"
    "file\0name\0file_progress\0done\0total\0"
    "finished\0z_error\0text"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui_zip_files[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    2,   40,    2, 0x0a /* Public */,
       6,    2,   45,    2, 0x0a /* Public */,
       9,    0,   50,    2, 0x0a /* Public */,
      10,    1,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    7,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   11,

       0        // eod
};

void ui_zip_files::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ui_zip_files *_t = static_cast<ui_zip_files *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pack_started(); break;
        case 1: _t->file_started((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->file_progress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 3: _t->finished(); break;
        case 4: _t->z_error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ui_zip_files::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ui_zip_files.data,
      qt_meta_data_ui_zip_files,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ui_zip_files::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui_zip_files::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ui_zip_files.stringdata0))
        return static_cast<void*>(const_cast< ui_zip_files*>(this));
    return QDialog::qt_metacast(_clname);
}

int ui_zip_files::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
