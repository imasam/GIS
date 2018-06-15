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

	// ����
	void activate();

	// ֹͣ����
	void deactivate();

	// ��ս��
	void clear();

	// ��ո���
	void clearHighlights();

	// ���ʶ�����е�Ҫ��
	void addFeature(const QgsMapToolIdentify::IdentifyResult& result);

	// ʸ��ͼ���addFeature
	void addFeature( QgsVectorLayer * layer,const QgsFeature &f,const QMap< QString, QString > &derivedAttributes );

	// դ��ͼ���addFeature
	void addFeature( QgsRasterLayer * layer,
		const QString& label,
		const QMap< QString, QString > &attributes,
		const QMap< QString, QString > &derivedAttributes,
		const QgsFields &fields = QgsFields(),
		const QgsFeature &feature = QgsFeature(),
		const QMap<QString, QVariant> &params = ( QMap<QString, QVariant>() ) );

	// ʹҪ�ظ���
	void highlightFeature( QTreeWidgetItem *item );

	QString representValue( QgsVectorLayer* vlayer, const QString& fieldName, const QVariant& value );

private slots:
	// ͼ�㱻ɾ��ʱ�Ĵ���ۺ���
	void layerDestroyed();

private:
	// ��ȡʸ��ͼ���Ӧ��item
	QTreeWidgetItem* layerItem( QObject *object );
	QTreeWidgetItem* layerItem( QTreeWidgetItem *item );

	// ��qtreewidgetitem��ȡ��featureitem
	QTreeWidgetItem* featureItem( QTreeWidgetItem *item );

	// ��QTreeWidgetItemתlayer
	QgsVectorLayer *vectorLayer( QTreeWidgetItem *item );
	QgsRasterLayer *rasterLayer( QTreeWidgetItem *item );

	// �Ͽ��źŲ�����
	void disconnectLayer( QObject *layer );

	// ������ͷ��
	void setColumnText( int column, const QString & label );

	//QString representValue( QgsVectorLayer* vlayer, const QString& fieldName, const QVariant& value );

private:
	QgsMapCanvas* mCanvas;

	QMap< QString, QMap< QString, QVariant > > mWidgetCaches;

	// ���ڴ�ŶԻ�����Ĵ�������
	QDockWidget* mDock;

	// ��ʶ���Ҫ���б�
	QList<QgsFeature> mFeatures;

	// ���������map
	QMap<QTreeWidgetItem *, QgsHighlight * > mHighlights;

	Ui::QgsIdentifyResultDialog ui;
};

#endif // QGSIDENTIFYRESULTDIALOG_H
