/****************************************************************************
** Meta object code from reading C++ file 'ui_wdg_flist.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/ui_wdg_flist.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ui_wdg_flist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ui_wdg_flist_t {
    QByteArrayData data[8];
    char stringdata0[89];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui_wdg_flist_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui_wdg_flist_t qt_meta_stringdata_ui_wdg_flist = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ui_wdg_flist"
QT_MOC_LITERAL(1, 13, 3), // "upd"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 12), // "son_dblclick"
QT_MOC_LITERAL(4, 31, 5), // "index"
QT_MOC_LITERAL(5, 37, 15), // "son_cm_copyLink"
QT_MOC_LITERAL(6, 53, 19), // "son_cm_copyLinkDesc"
QT_MOC_LITERAL(7, 73, 15) // "son_cm_openLink"

    },
    "ui_wdg_flist\0upd\0\0son_dblclick\0index\0"
    "son_cm_copyLink\0son_cm_copyLinkDesc\0"
    "son_cm_openLink"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui_wdg_flist[] = {

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
       3,    1,   40,    2, 0x0a /* Public */,
       5,    0,   43,    2, 0x0a /* Public */,
       6,    0,   44,    2, 0x0a /* Public */,
       7,    0,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ui_wdg_flist::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ui_wdg_flist *_t = static_cast<ui_wdg_flist *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->upd(); break;
        case 1: _t->son_dblclick((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: _t->son_cm_copyLink(); break;
        case 3: _t->son_cm_copyLinkDesc(); break;
        case 4: _t->son_cm_openLink(); break;
        default: ;
        }
    }
}

const QMetaObject ui_wdg_flist::staticMetaObject = {
    { &QTreeView::staticMetaObject, qt_meta_stringdata_ui_wdg_flist.data,
      qt_meta_data_ui_wdg_flist,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ui_wdg_flist::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui_wdg_flist::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ui_wdg_flist.stringdata0))
        return static_cast<void*>(const_cast< ui_wdg_flist*>(this));
    return QTreeView::qt_metacast(_clname);
}

int ui_wdg_flist::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeView::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_ui_wdg_flist_control_t {
    QByteArrayData data[1];
    char stringdata0[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui_wdg_flist_control_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui_wdg_flist_control_t qt_meta_stringdata_ui_wdg_flist_control = {
    {
QT_MOC_LITERAL(0, 0, 20) // "ui_wdg_flist_control"

    },
    "ui_wdg_flist_control"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui_wdg_flist_control[] = {

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

void ui_wdg_flist_control::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ui_wdg_flist_control::staticMetaObject = {
    { &QItemDelegate::staticMetaObject, qt_meta_stringdata_ui_wdg_flist_control.data,
      qt_meta_data_ui_wdg_flist_control,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ui_wdg_flist_control::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui_wdg_flist_control::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ui_wdg_flist_control.stringdata0))
        return static_cast<void*>(const_cast< ui_wdg_flist_control*>(this));
    return QItemDelegate::qt_metacast(_clname);
}

int ui_wdg_flist_control::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_ui_wdg_flist_mdl_t {
    QByteArrayData data[1];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui_wdg_flist_mdl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui_wdg_flist_mdl_t qt_meta_stringdata_ui_wdg_flist_mdl = {
    {
QT_MOC_LITERAL(0, 0, 16) // "ui_wdg_flist_mdl"

    },
    "ui_wdg_flist_mdl"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui_wdg_flist_mdl[] = {

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

void ui_wdg_flist_mdl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ui_wdg_flist_mdl::staticMetaObject = {
    { &QAbstractItemModel::staticMetaObject, qt_meta_stringdata_ui_wdg_flist_mdl.data,
      qt_meta_data_ui_wdg_flist_mdl,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ui_wdg_flist_mdl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui_wdg_flist_mdl::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ui_wdg_flist_mdl.stringdata0))
        return static_cast<void*>(const_cast< ui_wdg_flist_mdl*>(this));
    return QAbstractItemModel::qt_metacast(_clname);
}

int ui_wdg_flist_mdl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
