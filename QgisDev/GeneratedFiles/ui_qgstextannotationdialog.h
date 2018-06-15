/********************************************************************************
** Form generated from reading UI file 'qgstextannotationdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QGSTEXTANNOTATIONDIALOG_H
#define UI_QGSTEXTANNOTATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QgsTextAnnotationDialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QPushButton *okButton;
    QPushButton *deleteButton;
    QLabel *label;
    QTextEdit *textEdit;

    void setupUi(QDialog *QgsTextAnnotationDialog)
    {
        if (QgsTextAnnotationDialog->objectName().isEmpty())
            QgsTextAnnotationDialog->setObjectName(QString::fromUtf8("QgsTextAnnotationDialog"));
        QgsTextAnnotationDialog->resize(414, 194);
        layoutWidget = new QWidget(QgsTextAnnotationDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 150, 392, 33));
        hboxLayout = new QHBoxLayout(layoutWidget);
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        okButton = new QPushButton(layoutWidget);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        deleteButton = new QPushButton(layoutWidget);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));

        hboxLayout->addWidget(deleteButton);

        label = new QLabel(QgsTextAnnotationDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 72, 15));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        textEdit = new QTextEdit(QgsTextAnnotationDialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(10, 30, 391, 111));

        retranslateUi(QgsTextAnnotationDialog);

        QMetaObject::connectSlotsByName(QgsTextAnnotationDialog);
    } // setupUi

    void retranslateUi(QDialog *QgsTextAnnotationDialog)
    {
        QgsTextAnnotationDialog->setWindowTitle(QApplication::translate("QgsTextAnnotationDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("QgsTextAnnotationDialog", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        deleteButton->setText(QApplication::translate("QgsTextAnnotationDialog", "\345\210\240\351\231\244", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("QgsTextAnnotationDialog", "\346\240\207\346\263\250\345\206\205\345\256\271\357\274\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QgsTextAnnotationDialog: public Ui_QgsTextAnnotationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QGSTEXTANNOTATIONDIALOG_H
