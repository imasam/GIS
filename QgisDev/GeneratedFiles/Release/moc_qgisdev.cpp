/****************************************************************************
** Meta object code from reading C++ file 'qgisdev.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qgisdev.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qgisdev.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QgisDev[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      16,    8,    8,    8, 0x0a,
      29,    8,    8,    8, 0x0a,
      40,    8,    8,    8, 0x0a,
      50,    8,    8,    8, 0x0a,
      66,    8,   61,    8, 0x0a,
      77,    8,    8,    8, 0x0a,
      90,    8,    8,    8, 0x0a,
     102,    8,    8,    8, 0x0a,
     114,    8,    8,    8, 0x0a,
     131,  126,    8,    8, 0x0a,
     155,    8,    8,    8, 0x0a,
     170,    8,    8,    8, 0x0a,
     179,    8,    8,    8, 0x0a,
     189,    8,    8,    8, 0x0a,
     195,    8,    8,    8, 0x0a,
     205,    8,    8,    8, 0x0a,
     216,    8,    8,    8, 0x0a,
     233,    8,    8,    8, 0x0a,
     247,    8,    8,    8, 0x0a,
     264,    8,    8,    8, 0x0a,
     278,    8,    8,    8, 0x0a,
     317,  292,    8,    8, 0x0a,
     367,    8,    8,    8, 0x0a,
     381,    8,    8,    8, 0x0a,
     400,    8,    8,    8, 0x0a,
     422,  416,    8,    8, 0x0a,
     462,  455,    8,    8, 0x0a,
     502,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QgisDev[] = {
    "QgisDev\0\0init()\0enableMenu()\0setTitle()\0"
    "newProj()\0openProj()\0bool\0saveProj()\0"
    "saveProjAs()\0closeProj()\0markDirty()\0"
    "saveDirty()\0tool\0setMapTool(QgsMapTool*)\0"
    "unsetMapTool()\0zoomIn()\0zoomOut()\0"
    "pan()\0measure()\0identify()\0addVectorLayer()\0"
    "addWFSLayer()\0addRasterLayer()\0"
    "addWCSLayer()\0addWMSLayer()\0"
    "url,basename,providerKey\0"
    "addOpenSourceRasterLayer(QString,QString,QString)\0"
    "deleteLayer()\0showLayersWindow()\0"
    "layerSelected()\0layer\0"
    "addToManagerWindow(QgsMapLayer*)\0"
    "layers\0addToManagerWindow(QList<QgsMapLayer*>)\0"
    "annotation()\0"
};

void QgisDev::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QgisDev *_t = static_cast<QgisDev *>(_o);
        switch (_id) {
        case 0: _t->init(); break;
        case 1: _t->enableMenu(); break;
        case 2: _t->setTitle(); break;
        case 3: _t->newProj(); break;
        case 4: _t->openProj(); break;
        case 5: { bool _r = _t->saveProj();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: _t->saveProjAs(); break;
        case 7: _t->closeProj(); break;
        case 8: _t->markDirty(); break;
        case 9: _t->saveDirty(); break;
        case 10: _t->setMapTool((*reinterpret_cast< QgsMapTool*(*)>(_a[1]))); break;
        case 11: _t->unsetMapTool(); break;
        case 12: _t->zoomIn(); break;
        case 13: _t->zoomOut(); break;
        case 14: _t->pan(); break;
        case 15: _t->measure(); break;
        case 16: _t->identify(); break;
        case 17: _t->addVectorLayer(); break;
        case 18: _t->addWFSLayer(); break;
        case 19: _t->addRasterLayer(); break;
        case 20: _t->addWCSLayer(); break;
        case 21: _t->addWMSLayer(); break;
        case 22: _t->addOpenSourceRasterLayer((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 23: _t->deleteLayer(); break;
        case 24: _t->showLayersWindow(); break;
        case 25: _t->layerSelected(); break;
        case 26: _t->addToManagerWindow((*reinterpret_cast< QgsMapLayer*(*)>(_a[1]))); break;
        case 27: _t->addToManagerWindow((*reinterpret_cast< QList<QgsMapLayer*>(*)>(_a[1]))); break;
        case 28: _t->annotation(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QgisDev::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QgisDev::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QgisDev,
      qt_meta_data_QgisDev, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QgisDev::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QgisDev::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QgisDev::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QgisDev))
        return static_cast<void*>(const_cast< QgisDev*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QgisDev::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
