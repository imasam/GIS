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
	// 将文本应用到图层标注项
	void applyTextToItem();

	// 保存并退出
	void saveQuit();

	// 删除标注
	void deleteItem();

private:
	// 图层标注项
	QgsTextAnnotationItem *mItem;

	// 标注内容
	QTextDocument* mTextDocument;

	Ui::QgsTextAnnotationDialog ui;
};

#endif