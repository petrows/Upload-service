/****************************************************************************
** Meta object code from reading C++ file 'ui_main.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/ui_main.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ui_main.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ui_main_t {
    QByteArrayData data[12];
    char stringdata0[258];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui_main_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui_main_t qt_meta_stringdata_ui_main = {
    {
QT_MOC_LITERAL(0, 0, 7), // "ui_main"
QT_MOC_LITERAL(1, 8, 23), // "on_actionHide_triggered"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 23), // "on_actionExit_triggered"
QT_MOC_LITERAL(4, 57, 29), // "on_actionNew_upload_triggered"
QT_MOC_LITERAL(5, 87, 27), // "on_actionSettings_triggered"
QT_MOC_LITERAL(6, 115, 3), // "upd"
QT_MOC_LITERAL(7, 119, 23), // "on_btnNewUpload_clicked"
QT_MOC_LITERAL(8, 143, 32), // "on_actionAbout_program_triggered"
QT_MOC_LITERAL(9, 176, 28), // "on_actionHome_page_triggered"
QT_MOC_LITERAL(10, 205, 27), // "on_actionAbout_Qt_triggered"
QT_MOC_LITERAL(11, 233, 24) // "on_btnClipUpload_clicked"

    },
    "ui_main\0on_actionHide_triggered\0\0"
    "on_actionExit_triggered\0"
    "on_actionNew_upload_triggered\0"
    "on_actionSettings_triggered\0upd\0"
    "on_btnNewUpload_clicked\0"
    "on_actionAbout_program_triggered\0"
    "on_actionHome_page_triggered\0"
    "on_actionAbout_Qt_triggered\0"
    "on_btnClipUpload_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui_main[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    0,   66,    2, 0x0a /* Public */,
       5,    0,   67,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x0a /* Public */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ui_main::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ui_main *_t = static_cast<ui_main *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionHide_triggered(); break;
        case 1: _t->on_actionExit_triggered(); break;
        case 2: _t->on_actionNew_upload_triggered(); break;
        case 3: _t->on_actionSettings_triggered(); break;
        case 4: _t->upd(); break;
        case 5: _t->on_btnNewUpload_clicked(); break;
        case 6: _t->on_actionAbout_program_triggered(); break;
        case 7: _t->on_actionHome_page_triggered(); break;
        case 8: _t->on_actionAbout_Qt_triggered(); break;
        case 9: _t->on_btnClipUpload_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ui_main::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ui_main.data,
      qt_meta_data_ui_main,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ui_main::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui_main::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ui_main.stringdata0))
        return static_cast<void*>(const_cast< ui_main*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ui_main::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
