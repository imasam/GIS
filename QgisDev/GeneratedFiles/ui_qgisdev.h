/********************************************************************************
** Form generated from reading UI file 'qgisdev.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QGISDEV_H
#define UI_QGISDEV_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QgisDevClass
{
public:
    QAction *actionNewProj;
    QAction *actionOpenProj;
    QAction *actionSaveProj;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionpan;
    QAction *actionMeasure;
    QAction *actionIdentify;
    QAction *actionDelete;
    QAction *actionAnnotation;
    QAction *action_12;
    QAction *action_13;
    QAction *action_14;
    QAction *actionSaveProjAs;
    QAction *actionCloseProj;
    QAction *actionShow;
    QAction *actionAddVector;
    QAction *actionAddWFS;
    QAction *actionAddRaster;
    QAction *actionAddWMS;
    QAction *actionAddWCS;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuProj;
    QMenu *menuMap;
    QMenu *menuLayer;
    QMenu *menuAdd;
    QMenu *menuAnalysis;
    QToolBar *toolBar;
    QDockWidget *layersManage;
    QWidget *dockWidgetContents;
    QListWidget *layerList;

    void setupUi(QMainWindow *QgisDevClass)
    {
        if (QgisDevClass->objectName().isEmpty())
            QgisDevClass->setObjectName(QString::fromUtf8("QgisDevClass"));
        QgisDevClass->resize(1098, 604);
        actionNewProj = new QAction(QgisDevClass);
        actionNewProj->setObjectName(QString::fromUtf8("actionNewProj"));
        actionOpenProj = new QAction(QgisDevClass);
        actionOpenProj->setObjectName(QString::fromUtf8("actionOpenProj"));
        actionSaveProj = new QAction(QgisDevClass);
        actionSaveProj->setObjectName(QString::fromUtf8("actionSaveProj"));
        actionSaveProj->setEnabled(false);
        actionZoomIn = new QAction(QgisDevClass);
        actionZoomIn->setObjectName(QString::fromUtf8("actionZoomIn"));
        actionZoomIn->setCheckable(true);
        actionZoomOut = new QAction(QgisDevClass);
        actionZoomOut->setObjectName(QString::fromUtf8("actionZoomOut"));
        actionZoomOut->setCheckable(true);
        actionpan = new QAction(QgisDevClass);
        actionpan->setObjectName(QString::fromUtf8("actionpan"));
        actionpan->setCheckable(true);
        actionMeasure = new QAction(QgisDevClass);
        actionMeasure->setObjectName(QString::fromUtf8("actionMeasure"));
        actionMeasure->setCheckable(true);
        actionIdentify = new QAction(QgisDevClass);
        actionIdentify->setObjectName(QString::fromUtf8("actionIdentify"));
        actionIdentify->setCheckable(true);
        actionDelete = new QAction(QgisDevClass);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        actionAnnotation = new QAction(QgisDevClass);
        actionAnnotation->setObjectName(QString::fromUtf8("actionAnnotation"));
        actionAnnotation->setCheckable(true);
        action_12 = new QAction(QgisDevClass);
        action_12->setObjectName(QString::fromUtf8("action_12"));
        action_13 = new QAction(QgisDevClass);
        action_13->setObjectName(QString::fromUtf8("action_13"));
        action_14 = new QAction(QgisDevClass);
        action_14->setObjectName(QString::fromUtf8("action_14"));
        actionSaveProjAs = new QAction(QgisDevClass);
        actionSaveProjAs->setObjectName(QString::fromUtf8("actionSaveProjAs"));
        actionSaveProjAs->setEnabled(false);
        actionCloseProj = new QAction(QgisDevClass);
        actionCloseProj->setObjectName(QString::fromUtf8("actionCloseProj"));
        actionShow = new QAction(QgisDevClass);
        actionShow->setObjectName(QString::fromUtf8("actionShow"));
        actionAddVector = new QAction(QgisDevClass);
        actionAddVector->setObjectName(QString::fromUtf8("actionAddVector"));
        actionAddWFS = new QAction(QgisDevClass);
        actionAddWFS->setObjectName(QString::fromUtf8("actionAddWFS"));
        actionAddRaster = new QAction(QgisDevClass);
        actionAddRaster->setObjectName(QString::fromUtf8("actionAddRaster"));
        actionAddWMS = new QAction(QgisDevClass);
        actionAddWMS->setObjectName(QString::fromUtf8("actionAddWMS"));
        actionAddWCS = new QAction(QgisDevClass);
        actionAddWCS->setObjectName(QString::fromUtf8("actionAddWCS"));
        centralWidget = new QWidget(QgisDevClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QgisDevClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QgisDevClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1098, 26));
        menuProj = new QMenu(menuBar);
        menuProj->setObjectName(QString::fromUtf8("menuProj"));
        menuMap = new QMenu(menuBar);
        menuMap->setObjectName(QString::fromUtf8("menuMap"));
        menuMap->setEnabled(false);
        menuLayer = new QMenu(menuBar);
        menuLayer->setObjectName(QString::fromUtf8("menuLayer"));
        menuLayer->setEnabled(false);
        menuAdd = new QMenu(menuLayer);
        menuAdd->setObjectName(QString::fromUtf8("menuAdd"));
        menuAnalysis = new QMenu(menuBar);
        menuAnalysis->setObjectName(QString::fromUtf8("menuAnalysis"));
        menuAnalysis->setEnabled(false);
        QgisDevClass->setMenuBar(menuBar);
        toolBar = new QToolBar(QgisDevClass);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        QgisDevClass->addToolBar(Qt::TopToolBarArea, toolBar);
        layersManage = new QDockWidget(QgisDevClass);
        layersManage->setObjectName(QString::fromUtf8("layersManage"));
        layersManage->setMinimumSize(QSize(201, 136));
        layersManage->setMaximumSize(QSize(201, 400));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        layerList = new QListWidget(dockWidgetContents);
        layerList->setObjectName(QString::fromUtf8("layerList"));
        layerList->setGeometry(QRect(0, 0, 201, 371));
        layersManage->setWidget(dockWidgetContents);
        QgisDevClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), layersManage);

        menuBar->addAction(menuProj->menuAction());
        menuBar->addAction(menuMap->menuAction());
        menuBar->addAction(menuLayer->menuAction());
        menuBar->addAction(menuAnalysis->menuAction());
        menuProj->addAction(actionNewProj);
        menuProj->addAction(actionOpenProj);
        menuProj->addAction(actionSaveProj);
        menuProj->addAction(actionSaveProjAs);
        menuMap->addAction(actionZoomIn);
        menuMap->addAction(actionZoomOut);
        menuMap->addAction(actionpan);
        menuMap->addAction(actionMeasure);
        menuLayer->addAction(actionShow);
        menuLayer->addSeparator();
        menuLayer->addAction(actionIdentify);
        menuLayer->addAction(menuAdd->menuAction());
        menuLayer->addAction(actionDelete);
        menuLayer->addAction(actionAnnotation);
        menuAdd->addAction(actionAddVector);
        menuAdd->addAction(actionAddRaster);
        menuAdd->addAction(actionAddWFS);
        menuAdd->addAction(actionAddWCS);
        menuAdd->addAction(actionAddWMS);
        menuAnalysis->addAction(action_12);
        menuAnalysis->addAction(action_13);
        menuAnalysis->addAction(action_14);

        retranslateUi(QgisDevClass);

        QMetaObject::connectSlotsByName(QgisDevClass);
    } // setupUi

    void retranslateUi(QMainWindow *QgisDevClass)
    {
        QgisDevClass->setWindowTitle(QApplication::translate("QgisDevClass", "QgisDev", 0, QApplication::UnicodeUTF8));
        actionNewProj->setText(QApplication::translate("QgisDevClass", "\346\226\260\345\273\272\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        actionOpenProj->setText(QApplication::translate("QgisDevClass", "\346\211\223\345\274\200\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        actionSaveProj->setText(QApplication::translate("QgisDevClass", "\344\277\235\345\255\230\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        actionZoomIn->setText(QApplication::translate("QgisDevClass", "\345\234\260\345\233\276\346\224\276\345\244\247", 0, QApplication::UnicodeUTF8));
        actionZoomOut->setText(QApplication::translate("QgisDevClass", "\345\234\260\345\233\276\347\274\251\345\260\217", 0, QApplication::UnicodeUTF8));
        actionpan->setText(QApplication::translate("QgisDevClass", "\345\234\260\345\233\276\345\271\263\347\247\273", 0, QApplication::UnicodeUTF8));
        actionMeasure->setText(QApplication::translate("QgisDevClass", "\345\234\260\345\233\276\346\265\213\350\267\235", 0, QApplication::UnicodeUTF8));
        actionIdentify->setText(QApplication::translate("QgisDevClass", "\345\233\276\345\205\203\350\257\206\345\210\253", 0, QApplication::UnicodeUTF8));
        actionDelete->setText(QApplication::translate("QgisDevClass", "\345\210\240\351\231\244\345\233\276\345\261\202", 0, QApplication::UnicodeUTF8));
        actionAnnotation->setText(QApplication::translate("QgisDevClass", "\345\233\276\345\261\202\346\240\207\346\263\250", 0, QApplication::UnicodeUTF8));
        action_12->setText(QApplication::translate("QgisDevClass", "\347\202\271\347\212\266\345\234\260\347\211\251\347\251\272\351\227\264\345\210\206\346\236\220", 0, QApplication::UnicodeUTF8));
        action_13->setText(QApplication::translate("QgisDevClass", "\347\272\277\347\212\266\345\234\260\347\211\251\347\251\272\351\227\264\345\210\206\346\236\220", 0, QApplication::UnicodeUTF8));
        action_14->setText(QApplication::translate("QgisDevClass", "\346\234\200\347\237\255\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        actionSaveProjAs->setText(QApplication::translate("QgisDevClass", "\345\217\246\345\255\230\344\270\272\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        actionCloseProj->setText(QApplication::translate("QgisDevClass", "\345\205\263\351\227\255\351\241\271\347\233\256", 0, QApplication::UnicodeUTF8));
        actionShow->setText(QApplication::translate("QgisDevClass", "\346\230\276\347\244\272\345\233\276\345\261\202\347\252\227\345\217\243", 0, QApplication::UnicodeUTF8));
        actionAddVector->setText(QApplication::translate("QgisDevClass", "\346\267\273\345\212\240\347\237\242\351\207\217\345\233\276\345\261\202", 0, QApplication::UnicodeUTF8));
        actionAddWFS->setText(QApplication::translate("QgisDevClass", "\346\267\273\345\212\240WFS\345\233\276\345\261\202", 0, QApplication::UnicodeUTF8));
        actionAddRaster->setText(QApplication::translate("QgisDevClass", "\346\267\273\345\212\240\345\275\261\345\203\217\345\233\276\345\261\202", 0, QApplication::UnicodeUTF8));
        actionAddWMS->setText(QApplication::translate("QgisDevClass", "\346\267\273\345\212\240WMS\345\233\276\345\261\202", 0, QApplication::UnicodeUTF8));
        actionAddWCS->setText(QApplication::translate("QgisDevClass", "\346\267\273\345\212\240WCS\345\233\276\345\261\202", 0, QApplication::UnicodeUTF8));
        menuProj->setTitle(QApplication::translate("QgisDevClass", "\351\241\271\347\233\256\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        menuMap->setTitle(QApplication::translate("QgisDevClass", "\345\234\260\345\233\276\346\223\215\344\275\234", 0, QApplication::UnicodeUTF8));
        menuLayer->setTitle(QApplication::translate("QgisDevClass", "\345\233\276\345\261\202\347\256\241\347\220\206", 0, QApplication::UnicodeUTF8));
        menuAdd->setTitle(QApplication::translate("QgisDevClass", "\346\267\273\345\212\240\345\233\276\345\261\202", 0, QApplication::UnicodeUTF8));
        menuAnalysis->setTitle(QApplication::translate("QgisDevClass", "\347\251\272\351\227\264\345\210\206\346\236\220", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("QgisDevClass", "toolBar", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        layersManage->setToolTip(QApplication::translate("QgisDevClass", "<html><head/><body><p><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        layersManage->setWhatsThis(QApplication::translate("QgisDevClass", "<html><head/><body><p><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
    } // retranslateUi

};

namespace Ui {
    class QgisDevClass: public Ui_QgisDevClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QGISDEV_H
