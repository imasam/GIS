#ifndef QGSTEXTANNATATIONDIALOG_H
#define QGSTEXTANNATATIONDIALOG_H

#include "ui_qgstextannotationdialog.h"

#include <QDialog>
#include <QTextDocument>
#include <QGraphicsScene>

// qgis include
#include <qgstextannotationitem.h>

class QgsTextAnnotationDialog :
	public QDialog
{
	Q_OBJECT

public:
	QgsTextAnnotationDialog(QgsTextAnnotationItem* item, QWidget * parent = nullptr, Qt::WindowFlags f = nullptr);
	~QgsTextAnnotationDialog(void);

private slots:
	// ���ı�Ӧ�õ�ͼ���ע��
	void applyTextToItem();

	// ���沢�˳�
	void saveQuit();

	// ɾ����ע
	void deleteItem();

private:
	// ͼ���ע��
	QgsTextAnnotationItem *mItem;

	// ��ע����
	QTextDocument* mTextDocument;

	Ui::QgsTextAnnotationDialog ui;
};

#endif