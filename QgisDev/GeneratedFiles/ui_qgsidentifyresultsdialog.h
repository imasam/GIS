/********************************************************************************
** Form generated from reading UI file 'qgsidentifyresultsdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QGSIDENTIFYRESULTSDIALOG_H
#define UI_QGSIDENTIFYRESULTSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_QgsIdentifyResultDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QTreeWidget *lstResults;

    void setupUi(QDialog *QgsIdentifyResultDialog)
    {
        if (QgsIdentifyResultDialog->objectName().isEmpty())
            QgsIdentifyResultDialog->setObjectName(QString::fromUtf8("QgsIdentifyResultDialog"));
        QgsIdentifyResultDialog->resize(484, 531);
        horizontalLayout = new QHBoxLayout(QgsIdentifyResultDialog);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lstResults = new QTreeWidget(QgsIdentifyResultDialog);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        lstResults->setHeaderItem(__qtreewidgetitem);
        lstResults->setObjectName(QString::fromUtf8("lstResults"));
        lstResults->setLineWidth(2);
        lstResults->setAlternatingRowColors(true);
        lstResults->setSortingEnabled(true);

        horizontalLayout->addWidget(lstResults);


        retranslateUi(QgsIdentifyResultDialog);

        QMetaObject::connectSlotsByName(QgsIdentifyResultDialog);
    } // setupUi

    void retranslateUi(QDialog *QgsIdentifyResultDialog)
    {
        QgsIdentifyResultDialog->setWindowTitle(QApplication::translate("QgsIdentifyResultDialog", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QgsIdentifyResultDialog: public Ui_QgsIdentifyResultDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QGSIDENTIFYRESULTSDIALOG_H
