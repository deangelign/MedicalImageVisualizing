/****************************************************************************
** Meta object code from reading C++ file 'brightcontrastdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "brightcontrastdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'brightcontrastdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BrightContrastDialog_t {
    QByteArrayData data[20];
    char stringdata0[394];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BrightContrastDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BrightContrastDialog_t qt_meta_stringdata_BrightContrastDialog = {
    {
QT_MOC_LITERAL(0, 0, 20), // "BrightContrastDialog"
QT_MOC_LITERAL(1, 21, 12), // "brightSignal"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 11), // "brightValue"
QT_MOC_LITERAL(4, 47, 14), // "contrastSignal"
QT_MOC_LITERAL(5, 62, 8), // "contrast"
QT_MOC_LITERAL(6, 71, 14), // "negativeSignal"
QT_MOC_LITERAL(7, 86, 8), // "negative"
QT_MOC_LITERAL(8, 95, 19), // "normalizationSignal"
QT_MOC_LITERAL(9, 115, 13), // "normalization"
QT_MOC_LITERAL(10, 129, 44), // "on_horizontalSliderBrightDIal..."
QT_MOC_LITERAL(11, 174, 5), // "value"
QT_MOC_LITERAL(12, 180, 46), // "on_horizontalSliderContrastDi..."
QT_MOC_LITERAL(13, 227, 31), // "on_checkBoxNormalizacao_toggled"
QT_MOC_LITERAL(14, 259, 7), // "checked"
QT_MOC_LITERAL(15, 267, 27), // "on_checkBoxNegativo_toggled"
QT_MOC_LITERAL(16, 295, 29), // "on_spinBoxBright_valueChanged"
QT_MOC_LITERAL(17, 325, 4), // "arg1"
QT_MOC_LITERAL(18, 330, 31), // "on_spinBoxContrast_valueChanged"
QT_MOC_LITERAL(19, 362, 31) // "on_checkBoxLimiarizacao_toggled"

    },
    "BrightContrastDialog\0brightSignal\0\0"
    "brightValue\0contrastSignal\0contrast\0"
    "negativeSignal\0negative\0normalizationSignal\0"
    "normalization\0"
    "on_horizontalSliderBrightDIalog_valueChanged\0"
    "value\0on_horizontalSliderContrastDialog_valueChanged\0"
    "on_checkBoxNormalizacao_toggled\0checked\0"
    "on_checkBoxNegativo_toggled\0"
    "on_spinBoxBright_valueChanged\0arg1\0"
    "on_spinBoxContrast_valueChanged\0"
    "on_checkBoxLimiarizacao_toggled"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BrightContrastDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,
       6,    1,   75,    2, 0x06 /* Public */,
       8,    1,   78,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   81,    2, 0x08 /* Private */,
      12,    1,   84,    2, 0x08 /* Private */,
      13,    1,   87,    2, 0x08 /* Private */,
      15,    1,   90,    2, 0x08 /* Private */,
      16,    1,   93,    2, 0x08 /* Private */,
      18,    1,   96,    2, 0x08 /* Private */,
      19,    1,   99,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Float,    5,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Bool,   14,

       0        // eod
};

void BrightContrastDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BrightContrastDialog *_t = static_cast<BrightContrastDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->brightSignal((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->contrastSignal((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->negativeSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->normalizationSignal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_horizontalSliderBrightDIalog_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_horizontalSliderContrastDialog_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->on_checkBoxNormalizacao_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_checkBoxNegativo_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_spinBoxBright_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_spinBoxContrast_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_checkBoxLimiarizacao_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (BrightContrastDialog::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BrightContrastDialog::brightSignal)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (BrightContrastDialog::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BrightContrastDialog::contrastSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (BrightContrastDialog::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BrightContrastDialog::negativeSignal)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (BrightContrastDialog::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&BrightContrastDialog::normalizationSignal)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject BrightContrastDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BrightContrastDialog.data,
      qt_meta_data_BrightContrastDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *BrightContrastDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BrightContrastDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BrightContrastDialog.stringdata0))
        return static_cast<void*>(const_cast< BrightContrastDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int BrightContrastDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void BrightContrastDialog::brightSignal(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BrightContrastDialog::contrastSignal(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void BrightContrastDialog::negativeSignal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void BrightContrastDialog::normalizationSignal(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
