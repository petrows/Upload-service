/****************************************************************************
** Meta object code from reading C++ file 'u_upload.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/u_upload.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'u_upload.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_u_upload_file_t {
    QByteArrayData data[13];
    char stringdata0[146];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_u_upload_file_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_u_upload_file_t qt_meta_stringdata_u_upload_file = {
    {
QT_MOC_LITERAL(0, 0, 13), // "u_upload_file"
QT_MOC_LITERAL(1, 14, 8), // "progress"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "done"
QT_MOC_LITERAL(4, 29, 5), // "total"
QT_MOC_LITERAL(5, 35, 14), // "status_changed"
QT_MOC_LITERAL(6, 50, 13), // "state_changed"
QT_MOC_LITERAL(7, 64, 24), // "u_upload_file::FileState"
QT_MOC_LITERAL(8, 89, 5), // "state"
QT_MOC_LITERAL(9, 95, 15), // "flist_progr_del"
QT_MOC_LITERAL(10, 111, 14), // "copy_file_link"
QT_MOC_LITERAL(11, 126, 9), // "_progress"
QT_MOC_LITERAL(12, 136, 9) // "_req_done"

    },
    "u_upload_file\0progress\0\0done\0total\0"
    "status_changed\0state_changed\0"
    "u_upload_file::FileState\0state\0"
    "flist_progr_del\0copy_file_link\0_progress\0"
    "_req_done"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_u_upload_file[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,
       5,    0,   54,    2, 0x06 /* Public */,
       6,    1,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   58,    2, 0x0a /* Public */,
      10,    0,   59,    2, 0x0a /* Public */,
      11,    2,   60,    2, 0x08 /* Private */,
      12,    0,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    3,    4,
    QMetaType::Void,

       0        // eod
};

void u_upload_file::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        u_upload_file *_t = static_cast<u_upload_file *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->progress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 1: _t->status_changed(); break;
        case 2: _t->state_changed((*reinterpret_cast< u_upload_file::FileState(*)>(_a[1]))); break;
        case 3: _t->flist_progr_del(); break;
        case 4: _t->copy_file_link(); break;
        case 5: _t->_progress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 6: _t->_req_done(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (u_upload_file::*_t)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&u_upload_file::progress)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (u_upload_file::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&u_upload_file::status_changed)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (u_upload_file::*_t)(u_upload_file::FileState );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&u_upload_file::state_changed)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject u_upload_file::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_u_upload_file.data,
      qt_meta_data_u_upload_file,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *u_upload_file::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *u_upload_file::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_u_upload_file.stringdata0))
        return static_cast<void*>(const_cast< u_upload_file*>(this));
    return QObject::qt_metacast(_clname);
}

int u_upload_file::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void u_upload_file::progress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void u_upload_file::status_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void u_upload_file::state_changed(u_upload_file::FileState _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_u_upload_t {
    QByteArrayData data[15];
    char stringdata0[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_u_upload_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_u_upload_t qt_meta_stringdata_u_upload = {
    {
QT_MOC_LITERAL(0, 0, 8), // "u_upload"
QT_MOC_LITERAL(1, 9, 15), // "upload_progress"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 4), // "done"
QT_MOC_LITERAL(4, 31, 5), // "total"
QT_MOC_LITERAL(5, 37, 11), // "update_info"
QT_MOC_LITERAL(6, 49, 20), // "file_upload_progress"
QT_MOC_LITERAL(7, 70, 18), // "file_upload_status"
QT_MOC_LITERAL(8, 89, 24), // "u_upload_file::FileState"
QT_MOC_LITERAL(9, 114, 5), // "state"
QT_MOC_LITERAL(10, 120, 14), // "status_recheck"
QT_MOC_LITERAL(11, 135, 15), // "ulist_progr_del"
QT_MOC_LITERAL(12, 151, 16), // "copy_upload_link"
QT_MOC_LITERAL(13, 168, 9), // "show_form"
QT_MOC_LITERAL(14, 178, 11) // "update_form"

    },
    "u_upload\0upload_progress\0\0done\0total\0"
    "update_info\0file_upload_progress\0"
    "file_upload_status\0u_upload_file::FileState\0"
    "state\0status_recheck\0ulist_progr_del\0"
    "copy_upload_link\0show_form\0update_form"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_u_upload[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       5,    0,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   65,    2, 0x0a /* Public */,
       7,    1,   70,    2, 0x0a /* Public */,
      10,    0,   73,    2, 0x0a /* Public */,
      11,    0,   74,    2, 0x0a /* Public */,
      12,    0,   75,    2, 0x0a /* Public */,
      13,    0,   76,    2, 0x0a /* Public */,
      14,    0,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    3,    4,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void u_upload::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        u_upload *_t = static_cast<u_upload *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->upload_progress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 1: _t->update_info(); break;
        case 2: _t->file_upload_progress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 3: _t->file_upload_status((*reinterpret_cast< u_upload_file::FileState(*)>(_a[1]))); break;
        case 4: _t->status_recheck(); break;
        case 5: _t->ulist_progr_del(); break;
        case 6: _t->copy_upload_link(); break;
        case 7: _t->show_form(); break;
        case 8: _t->update_form(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (u_upload::*_t)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&u_upload::upload_progress)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (u_upload::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&u_upload::update_info)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject u_upload::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_u_upload.data,
      qt_meta_data_u_upload,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *u_upload::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *u_upload::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_u_upload.stringdata0))
        return static_cast<void*>(const_cast< u_upload*>(this));
    return QObject::qt_metacast(_clname);
}

int u_upload::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void u_upload::upload_progress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void u_upload::update_info()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
