/****************************************************************************
** Meta object code from reading C++ file 'u_common.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/u_common.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'u_common.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_zip_pack_t {
    QByteArrayData data[10];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_zip_pack_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_zip_pack_t qt_meta_stringdata_zip_pack = {
    {
QT_MOC_LITERAL(0, 0, 8), // "zip_pack"
QT_MOC_LITERAL(1, 9, 5), // "error"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 10), // "file_added"
QT_MOC_LITERAL(4, 27, 12), // "file_started"
QT_MOC_LITERAL(5, 40, 13), // "file_progress"
QT_MOC_LITERAL(6, 54, 4), // "done"
QT_MOC_LITERAL(7, 59, 5), // "total"
QT_MOC_LITERAL(8, 65, 7), // "started"
QT_MOC_LITERAL(9, 73, 8) // "finished"

    },
    "zip_pack\0error\0\0file_added\0file_started\0"
    "file_progress\0done\0total\0started\0"
    "finished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_zip_pack[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       3,    2,   47,    2, 0x06 /* Public */,
       4,    2,   52,    2, 0x06 /* Public */,
       5,    2,   57,    2, 0x06 /* Public */,
       8,    0,   62,    2, 0x06 /* Public */,
       9,    0,   63,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    6,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void zip_pack::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        zip_pack *_t = static_cast<zip_pack *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->file_added((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->file_started((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->file_progress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 4: _t->started(); break;
        case 5: _t->finished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (zip_pack::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&zip_pack::error)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (zip_pack::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&zip_pack::file_added)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (zip_pack::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&zip_pack::file_started)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (zip_pack::*_t)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&zip_pack::file_progress)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (zip_pack::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&zip_pack::started)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (zip_pack::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&zip_pack::finished)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject zip_pack::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_zip_pack.data,
      qt_meta_data_zip_pack,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *zip_pack::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *zip_pack::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_zip_pack.stringdata0))
        return static_cast<void*>(const_cast< zip_pack*>(this));
    return QObject::qt_metacast(_clname);
}

int zip_pack::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void zip_pack::error(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void zip_pack::file_added(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void zip_pack::file_started(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void zip_pack::file_progress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void zip_pack::started()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void zip_pack::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
