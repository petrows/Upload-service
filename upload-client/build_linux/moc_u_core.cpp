/****************************************************************************
** Meta object code from reading C++ file 'u_core.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/u_core.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'u_core.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_u_core_t {
    QByteArrayData data[21];
    char stringdata0[233];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_u_core_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_u_core_t qt_meta_stringdata_u_core = {
    {
QT_MOC_LITERAL(0, 0, 6), // "u_core"
QT_MOC_LITERAL(1, 7, 20), // "global_state_changed"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 4), // "exit"
QT_MOC_LITERAL(4, 34, 9), // "reload_ui"
QT_MOC_LITERAL(5, 44, 12), // "start_update"
QT_MOC_LITERAL(6, 57, 15), // "toggle_main_wnd"
QT_MOC_LITERAL(7, 73, 13), // "tray_activate"
QT_MOC_LITERAL(8, 87, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(9, 121, 3), // "res"
QT_MOC_LITERAL(10, 125, 14), // "tray_msg_click"
QT_MOC_LITERAL(11, 140, 16), // "start_new_upload"
QT_MOC_LITERAL(12, 157, 2), // "in"
QT_MOC_LITERAL(13, 160, 11), // "qsa_message"
QT_MOC_LITERAL(14, 172, 3), // "msg"
QT_MOC_LITERAL(15, 176, 14), // "tmsg_copy_link"
QT_MOC_LITERAL(16, 191, 13), // "tmsg_complete"
QT_MOC_LITERAL(17, 205, 9), // "u_upload*"
QT_MOC_LITERAL(18, 215, 3), // "upl"
QT_MOC_LITERAL(19, 219, 9), // "open_link"
QT_MOC_LITERAL(20, 229, 3) // "url"

    },
    "u_core\0global_state_changed\0\0exit\0"
    "reload_ui\0start_update\0toggle_main_wnd\0"
    "tray_activate\0QSystemTrayIcon::ActivationReason\0"
    "res\0tray_msg_click\0start_new_upload\0"
    "in\0qsa_message\0msg\0tmsg_copy_link\0"
    "tmsg_complete\0u_upload*\0upl\0open_link\0"
    "url"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_u_core[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    0,   83,    2, 0x0a /* Public */,
       7,    1,   84,    2, 0x0a /* Public */,
      10,    0,   87,    2, 0x0a /* Public */,
      11,    1,   88,    2, 0x0a /* Public */,
      11,    0,   91,    2, 0x2a /* Public | MethodCloned */,
      13,    1,   92,    2, 0x0a /* Public */,
      15,    0,   95,    2, 0x0a /* Public */,
      16,    1,   96,    2, 0x0a /* Public */,
      19,    1,   99,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, QMetaType::QString,   20,

       0        // eod
};

void u_core::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        u_core *_t = static_cast<u_core *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->global_state_changed(); break;
        case 1: _t->exit(); break;
        case 2: _t->reload_ui(); break;
        case 3: _t->start_update(); break;
        case 4: _t->toggle_main_wnd(); break;
        case 5: _t->tray_activate((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 6: _t->tray_msg_click(); break;
        case 7: _t->start_new_upload((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 8: _t->start_new_upload(); break;
        case 9: _t->qsa_message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->tmsg_copy_link(); break;
        case 11: _t->tmsg_complete((*reinterpret_cast< u_upload*(*)>(_a[1]))); break;
        case 12: _t->open_link((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< u_upload* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (u_core::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&u_core::global_state_changed)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject u_core::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_u_core.data,
      qt_meta_data_u_core,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *u_core::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *u_core::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_u_core.stringdata0))
        return static_cast<void*>(const_cast< u_core*>(this));
    return QObject::qt_metacast(_clname);
}

int u_core::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void u_core::global_state_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
