/****************************************************************************
** Meta object code from reading C++ file 'u_update.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/u_update.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'u_update.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_u_update_t {
    QByteArrayData data[11];
    char stringdata0[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_u_update_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_u_update_t qt_meta_stringdata_u_update = {
    {
QT_MOC_LITERAL(0, 0, 8), // "u_update"
QT_MOC_LITERAL(1, 9, 14), // "status_changed"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 16), // "progress_chagned"
QT_MOC_LITERAL(4, 42, 6), // "cancel"
QT_MOC_LITERAL(5, 49, 12), // "start_update"
QT_MOC_LITERAL(6, 62, 14), // "_down_progress"
QT_MOC_LITERAL(7, 77, 4), // "down"
QT_MOC_LITERAL(8, 82, 5), // "total"
QT_MOC_LITERAL(9, 88, 10), // "_down_done"
QT_MOC_LITERAL(10, 99, 14) // "QNetworkReply*"

    },
    "u_update\0status_changed\0\0progress_chagned\0"
    "cancel\0start_update\0_down_progress\0"
    "down\0total\0_down_done\0QNetworkReply*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_u_update[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   48,    2, 0x0a /* Public */,
       5,    0,   49,    2, 0x0a /* Public */,
       6,    2,   50,    2, 0x08 /* Private */,
       9,    1,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    7,    8,
    QMetaType::Void, 0x80000000 | 10,    2,

       0        // eod
};

void u_update::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        u_update *_t = static_cast<u_update *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->status_changed(); break;
        case 1: _t->progress_chagned((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->cancel(); break;
        case 3: _t->start_update(); break;
        case 4: _t->_down_progress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 5: _t->_down_done((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (u_update::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&u_update::status_changed)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (u_update::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&u_update::progress_chagned)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject u_update::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_u_update.data,
      qt_meta_data_u_update,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *u_update::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *u_update::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_u_update.stringdata0))
        return static_cast<void*>(const_cast< u_update*>(this));
    return QObject::qt_metacast(_clname);
}

int u_update::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void u_update::status_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void u_update::progress_chagned(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
