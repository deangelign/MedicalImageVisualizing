/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HelloWorld/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[16];
    char stringdata0[423];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 27), // "on_action3D_Image_triggered"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 29), // "on_spinBoxImageZ_valueChanged"
QT_MOC_LITERAL(4, 70, 4), // "arg1"
QT_MOC_LITERAL(5, 75, 29), // "on_spinBoxImageY_valueChanged"
QT_MOC_LITERAL(6, 105, 29), // "on_spinBoxImageX_valueChanged"
QT_MOC_LITERAL(7, 135, 18), // "on_mirrorZ_clicked"
QT_MOC_LITERAL(8, 154, 34), // "on_rotateZ_90AntiClockwise_cl..."
QT_MOC_LITERAL(9, 189, 34), // "on_rotateY_90Anticlockwise_cl..."
QT_MOC_LITERAL(10, 224, 36), // "on_rotateY_90Anticlockwise_2_..."
QT_MOC_LITERAL(11, 261, 28), // "on_actionLabel_map_triggered"
QT_MOC_LITERAL(12, 290, 42), // "on_labelFigureZ_customContext..."
QT_MOC_LITERAL(13, 333, 3), // "pos"
QT_MOC_LITERAL(14, 337, 42), // "on_labelFigureY_customContext..."
QT_MOC_LITERAL(15, 380, 42) // "on_labelFigureX_customContext..."

    },
    "MainWindow\0on_action3D_Image_triggered\0"
    "\0on_spinBoxImageZ_valueChanged\0arg1\0"
    "on_spinBoxImageY_valueChanged\0"
    "on_spinBoxImageX_valueChanged\0"
    "on_mirrorZ_clicked\0"
    "on_rotateZ_90AntiClockwise_clicked\0"
    "on_rotateY_90Anticlockwise_clicked\0"
    "on_rotateY_90Anticlockwise_2_clicked\0"
    "on_actionLabel_map_triggered\0"
    "on_labelFigureZ_customContextMenuRequested\0"
    "pos\0on_labelFigureY_customContextMenuRequested\0"
    "on_labelFigureX_customContextMenuRequested"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    1,   75,    2, 0x08 /* Private */,
       5,    1,   78,    2, 0x08 /* Private */,
       6,    1,   81,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    1,   89,    2, 0x08 /* Private */,
      14,    1,   92,    2, 0x08 /* Private */,
      15,    1,   95,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   13,
    QMetaType::Void, QMetaType::QPoint,   13,
    QMetaType::Void, QMetaType::QPoint,   13,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_action3D_Image_triggered(); break;
        case 1: _t->on_spinBoxImageZ_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_spinBoxImageY_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_spinBoxImageX_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_mirrorZ_clicked(); break;
        case 5: _t->on_rotateZ_90AntiClockwise_clicked(); break;
        case 6: _t->on_rotateY_90Anticlockwise_clicked(); break;
        case 7: _t->on_rotateY_90Anticlockwise_2_clicked(); break;
        case 8: _t->on_actionLabel_map_triggered(); break;
        case 9: _t->on_labelFigureZ_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 10: _t->on_labelFigureY_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 11: _t->on_labelFigureX_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
