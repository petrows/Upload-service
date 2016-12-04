/****************************************************************************
** Meta object code from reading C++ file 'ui_wdg_ulist.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/ui_wdg_ulist.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ui_wdg_ulist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ui_wdg_ulist_t {
    QByteArrayData data[9];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui_wdg_ulist_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui_wdg_ulist_t qt_meta_stringdata_ui_wdg_ulist = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ui_wdg_ulist"
QT_MOC_LITERAL(1, 13, 3), // "upd"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 12), // "son_dblclick"
QT_MOC_LITERAL(4, 31, 5), // "index"
QT_MOC_LITERAL(5, 37, 10), // "copy_links"
QT_MOC_LITERAL(6, 48, 20), // "copy_all_files_links"
QT_MOC_LITERAL(7, 69, 26), // "copy_all_files_links_descr"
QT_MOC_LITERAL(8, 96, 9) // "open_info"

    },
    "ui_wdg_ulist\0upd\0\0son_dblclick\0index\0"
    "copy_links\0copy_all_files_links\0"
    "copy_all_files_links_descr\0open_info"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui_wdg_ulist[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    1,   45,    2, 0x0a /* Public */,
       5,    0,   48,    2, 0x0a /* Public */,
       6,    0,   49,    2, 0x0a /* Public */,
       7,    0,   50,    2, 0x0a /* Public */,
       8,    0,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ui_wdg_ulist::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ui_wdg_ulist *_t = static_cast<ui_wdg_ulist *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->upd(); break;
        case 1: _t->son_dblclick((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: _t->copy_links(); break;
        case 3: _t->copy_all_files_links(); break;
        case 4: _t->copy_all_files_links_descr(); break;
        case 5: _t->open_info(); break;
        default: ;
        }
    }
}

const QMetaObject ui_wdg_ulist::staticMetaObject = {
    { &QTreeView::staticMetaObject, qt_meta_stringdata_ui_wdg_ulist.data,
      qt_meta_data_ui_wdg_ulist,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ui_wdg_ulist::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui_wdg_ulist::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ui_wdg_ulist.stringdata0))
        return static_cast<void*>(const_cast< ui_wdg_ulist*>(this));
    return QTreeView::qt_metacast(_clname);
}

int ui_wdg_ulist::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeView::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_ui_wdg_ulist_control_t {
    QByteArrayData data[1];
    char stringdata0[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui_wdg_ulist_control_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui_wdg_ulist_control_t qt_meta_stringdata_ui_wdg_ulist_control = {
    {
QT_MOC_LITERAL(0, 0, 20) // "ui_wdg_ulist_control"

    },
    "ui_wdg_ulist_control"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui_wdg_ulist_control[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void ui_wdg_ulist_control::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ui_wdg_ulist_control::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_ui_wdg_ulist_control.data,
      qt_meta_data_ui_wdg_ulist_control,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ui_wdg_ulist_control::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui_wdg_ulist_control::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ui_wdg_ulist_control.stringdata0))
        return static_cast<void*>(const_cast< ui_wdg_ulist_control*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int ui_wdg_ulist_control::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_ui_wdg_ulist_mdl_t {
    QByteArrayData data[1];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui_wdg_ulist_mdl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui_wdg_ulist_mdl_t qt_meta_stringdata_ui_wdg_ulist_mdl = {
    {
QT_MOC_LITERAL(0, 0, 16) // "ui_wdg_ulist_mdl"

    },
    "ui_wdg_ulist_mdl"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui_wdg_ulist_mdl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void ui_wdg_ulist_mdl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ui_wdg_ulist_mdl::staticMetaObject = {
    { &QAbstractItemModel::staticMetaObject, qt_meta_stringdata_ui_wdg_ulist_mdl.data,
      qt_meta_data_ui_wdg_ulist_mdl,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ui_wdg_ulist_mdl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui_wdg_ulist_mdl::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ui_wdg_ulist_mdl.stringdata0))
        return static_cast<void*>(const_cast< ui_wdg_ulist_mdl*>(this));
    return QAbstractItemModel::qt_metacast(_clname);
}

int ui_wdg_ulist_mdl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
