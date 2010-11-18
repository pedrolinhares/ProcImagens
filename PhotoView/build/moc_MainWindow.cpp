/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created: Wed Nov 17 14:03:09 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/MainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   11,   12,   11, 0x08,
      35,   11,   11,   11, 0x08,
      49,   11,   11,   11, 0x08,
      69,   11,   11,   11, 0x08,
      83,   11,   11,   11, 0x08,
     103,   11,   11,   11, 0x08,
     119,   11,   11,   11, 0x08,
     135,   11,   11,   11, 0x08,
     154,   11,   11,   11, 0x08,
     174,   11,   11,   11, 0x08,
     200,  195,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0bool\0openFileChooser()\0"
    "toGrayScale()\0resizeImageDialog()\0"
    "resizeImage()\0restoreOriginalIm()\0"
    "binarImDialog()\0binarizeImage()\0"
    "setWidthValue(int)\0setHeightValue(int)\0"
    "setChosenMethod(int)\0text\0"
    "enableBinButton(QString)\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { bool _r = openFileChooser();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: toGrayScale(); break;
        case 2: resizeImageDialog(); break;
        case 3: resizeImage(); break;
        case 4: restoreOriginalIm(); break;
        case 5: binarImDialog(); break;
        case 6: binarizeImage(); break;
        case 7: setWidthValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: setHeightValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: setChosenMethod((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: enableBinButton((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
