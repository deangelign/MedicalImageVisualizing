/****************************************************************************
** Meta object code from reading C++ file 'refactformdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../HelloWorld/refactformdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'refactformdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RefactFormDialog_t {
    QByteArrayData data[10];
    char stringdata0[154];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RefactFormDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RefactFormDialog_t qt_meta_stringdata_RefactFormDialog = {
    {
QT_MOC_LITERAL(0, 0, 16), // "RefactFormDialog"
QT_MOC_LITERAL(1, 17, 8), // "okSignal"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 2), // "dx"
QT_MOC_LITERAL(4, 30, 2), // "dy"
QT_MOC_LITERAL(5, 33, 2), // "dz"
QT_MOC_LITERAL(6, 36, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(7, 58, 31), // "on_spinBoxRefactDx_valueChanged"
QT_MOC_LITERAL(8, 90, 31), // "on_spinBoxRefactDy_valueChanged"
QT_MOC_LITERAL(9, 122, 31) // "on_spinBoxRefactDz_valueChanged"

    },
    "RefactFormDialog\0okSignal\0\0dx\0dy\0dz\0"
    "on_buttonBox_accepted\0"
    "on_spinBoxRefactDx_valueChanged\0"
    "on_spinBoxRefactDy_valueChanged\0"
    "on_spinBoxRefactDz_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RefactFormDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   46,    2, 0x08 /* Private */,
       7,    1,   47,    2, 0x08 /* Private */,
       8,    1,   50,    2, 0x08 /* Private */,
       9,    1,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float,    3,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    4,
    QMetaType::Void, QMetaType::Double,    5,

       0        // eod
};

void RefactFormDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RefactFormDialog *_t = static_cast<RefactFormDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->okSignal((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 1: _t->on_buttonBox_accepted(); break;
        case 2: _t->on_spinBoxRefactDx_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->on_spinBoxRefactDy_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->on_spinBoxRefactDz_valueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RefactFormDialog::*_t)(float , float , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RefactFormDialog::okSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject RefactFormDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_RefactFormDialog.data,
      qt_meta_data_RefactFormDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RefactFormDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RefactFormDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RefactFormDialog.stringdata0))
        return static_cast<void*>(const_cast< RefactFormDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int RefactFormDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void RefactFormDialog::okSignal(float _t1, float _t2, float _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
