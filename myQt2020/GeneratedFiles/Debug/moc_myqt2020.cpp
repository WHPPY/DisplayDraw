/****************************************************************************
** Meta object code from reading C++ file 'myqt2020.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../myqt2020.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'myqt2020.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_myQt2020_t {
    QByteArrayData data[14];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myQt2020_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myQt2020_t qt_meta_stringdata_myQt2020 = {
    {
QT_MOC_LITERAL(0, 0, 8), // "myQt2020"
QT_MOC_LITERAL(1, 9, 8), // "recvInfo"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 12), // "t_waistGirth"
QT_MOC_LITERAL(4, 32, 10), // "t_hipGirth"
QT_MOC_LITERAL(5, 43, 13), // "t_crotchDepth"
QT_MOC_LITERAL(6, 57, 16), // "t_trousersLength"
QT_MOC_LITERAL(7, 74, 13), // "t_sweepBottom"
QT_MOC_LITERAL(8, 88, 8), // "changeSL"
QT_MOC_LITERAL(9, 97, 9), // "boolValue"
QT_MOC_LITERAL(10, 107, 8), // "changeCL"
QT_MOC_LITERAL(11, 116, 6), // "showBP"
QT_MOC_LITERAL(12, 123, 6), // "showFP"
QT_MOC_LITERAL(13, 130, 11) // "savePicture"

    },
    "myQt2020\0recvInfo\0\0t_waistGirth\0"
    "t_hipGirth\0t_crotchDepth\0t_trousersLength\0"
    "t_sweepBottom\0changeSL\0boolValue\0"
    "changeCL\0showBP\0showFP\0savePicture"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myQt2020[] = {

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
       1,    5,   44,    2, 0x08 /* Private */,
       8,    1,   55,    2, 0x08 /* Private */,
      10,    1,   58,    2, 0x08 /* Private */,
      11,    1,   61,    2, 0x08 /* Private */,
      12,    1,   64,    2, 0x08 /* Private */,
      13,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,    6,    7,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,

       0        // eod
};

void myQt2020::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myQt2020 *_t = static_cast<myQt2020 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->recvInfo((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5]))); break;
        case 1: _t->changeSL((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->changeCL((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->showBP((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->showFP((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->savePicture(); break;
        default: ;
        }
    }
}

const QMetaObject myQt2020::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_myQt2020.data,
      qt_meta_data_myQt2020,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *myQt2020::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myQt2020::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_myQt2020.stringdata0))
        return static_cast<void*>(const_cast< myQt2020*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int myQt2020::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
