#ifndef QGSIDENTIFYRESULTDIALOG_H
#define QGSIDENTIFYRESULTDIALOG_H

#include <QDialog>
#include <QDockWidget>
#include "ui_qgsidentifyresultsdialog.h"

// qgis include
#include <qgsmapcanvas.h>
#include <qgsvectordataprovider.h>
#include <qgsmaptoolidentify.h>
#include <qgshighlight.h>
#include <qgseditorwidgetfactory.h>
#include <qgseditorwidgetregistry.h>
#include <qgsstringutils.h>


class QgsIdentifyResultsFeatureItem: public QTreeWidgetItem
{
public:
	QgsIdentifyResultsFeatureItem( const QgsFields &fields, const QgsFeature &feature, const QgsCoordinateReferenceSystem &crs, const QStringList & strings = QStringList() );
	const QgsFields &fields() const { return mFields; }
	const QgsFeature &feature() const { return mFeature; }
	const QgsCoordinateReferenceSystem &crs() { return mCrs; }

private:
	QgsFields mFields;
	QgsFeature mFeature;
	QgsCoordinateReferenceSystem mCrs;
};

class QgsIdentifyResultsDialog : public QDialog
{
	Q_OBJECT

public:
	QgsIdentifyResultsDialog(QgsMapCanvas *canvas, QWidget *parent = 0);
	~QgsIdentifyResultsDialog();

	void show();

	// 工作
	void activate();

	// 停止工作
	void deactivate();

	// 清空结果
	void clear();

	// 清空高亮
	void clearHighlights();

	// 添加识别结果中的要素
	void addFeature(const QgsMapToolIdentify::IdentifyResult& result);

	// 矢量图层的addFeature
	void addFeature( QgsVectorLayer * layer,const QgsFeature &f,const QMap< QString, QString > &derivedAttributes );

	// 栅格图层的addFeature
	void addFeature( QgsRasterLayer * layer,
		const QString& label,
		const QMap< QString, QString > &attributes,
		const QMap< QString, QString > &derivedAttributes,
		const QgsFields &fields = QgsFields(),
		const QgsFeature &feature = QgsFeature(),
		const QMap<QString, QVariant> &params = ( QMap<QString, QVariant>() ) );

	// 使要素高亮
	void highlightFeature( QTreeWidgetItem *item );

	QString representValue( QgsVectorLayer* vlayer, const QString& fieldName, const QVariant& value );

private slots:
	// 图层被删除时的处理槽函数
	void layerDestroyed();

private:
	// 获取矢量图层对应的item
	QTreeWidgetItem* layerItem( QObject *object );
	QTreeWidgetItem* layerItem( QTreeWidgetItem *item );

	// 有qtreewidgetitem获取其featureitem
	QTreeWidgetItem* featureItem( QTreeWidgetItem *item );

	// 由QTreeWidgetItem转layer
	QgsVectorLayer *vectorLayer( QTreeWidgetItem *item );
	QgsRasterLayer *rasterLayer( QTreeWidgetItem *item );

	// 断开信号槽连接
	void disconnectLayer( QObject *layer );

	// 设置列头部
	void setColumnText( int column, const QString & label );

	//QString representValue( QgsVectorLayer* vlayer, const QString& fieldName, const QVariant& value );

private:
	QgsMapCanvas* mCanvas;

	QMap< QString, QMap< QString, QVariant > > mWidgetCaches;

	// 用于存放对话框本身的窗体容器
	QDockWidget* mDock;

	// 所识别的要素列表
	QList<QgsFeature> mFeatures;

	// 保存高亮的map
	QMap<QTreeWidgetItem *, QgsHighlight * > mHighlights;

	Ui::QgsIdentifyResultDialog ui;
};

#endif // QGSIDENTIFYRESULTDIALOG_H
