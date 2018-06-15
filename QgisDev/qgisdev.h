#ifndef QGIS_DEV_H
#define QGIS_DEV_H

#include "ui_qgisdev.h"

// qt include
#include <QtGui/QMainWindow>
#include <QGridLayout>
#include <QMessageBox>
#include <QFileDialog>

// qgis include
#include <qgsmapcanvas.h>
#include <qgsmaplayerregistry.h>
#include <qgsproject.h>
#include <qgslayertreeregistrybridge.h>
#include <qgslayertreemapcanvasbridge.h>
#include <qgsvectorlayer.h>
#include <qgsrasterlayer.h>
#include <qgsmaptoolpan.h>
#include <qgsmaptoolzoom.h>
#include<qgsproviderregistry.h> 
#include <qgstextannotationitem.h>


#include "qgsmaptoolannotation.h"
#include "qgsmeasuretool.h"
#include "qgsmaptoolidentifyaction.h"

class QgisDev : public QMainWindow
{
	Q_OBJECT

public:
	QgisDev(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QgisDev();

	static QgisDev* instance() {return qInstance;}

	void closeEvent(QCloseEvent *e) override;

public slots:
	// ��ʼ������
	void init();

	// ����Ŀ��ʹ�˵�������
	void enableMenu();

	// ���ô������
	void setTitle();

	/*----------------------------��Ŀ����----------------------------*/
	// �½���Ŀ
	void newProj();
	// ����Ŀ
	void openProj();
	// ������Ŀ
	bool saveProj();
	// ���Ϊ��Ŀ
	void saveProjAs();
	// �ر���Ŀ
	void closeProj();

	// ���Ϊ���޸�
	void markDirty();
	// �����޸�
	void saveDirty();
	
	/*----------------------------��ͼ����----------------------------*/
	// ����ѡ��
	void setMapTool(QgsMapTool *tool);
	// ȡ��ѡ��
	void unsetMapTool();
	// �Ŵ��ͼ
	void zoomIn();
	// ��С��ͼ
	void zoomOut();
	// ƽ�Ƶ�ͼ
	void pan();
	// ���
	void measure();

	/*----------------------------ͼ�����----------------------------*/

	// ͼԪʶ��
	void identify();

	// ���ʸ��ͼ��
	void addVectorLayer();
	// ���WFSͼ��
	void addWFSLayer();
	// ���դ��ͼ��
	void addRasterLayer();
	// ���WCSͼ��
	void addWCSLayer();
	// ���WMSͼ��
	void addWMSLayer();

	//**********���ͼ�㣬����WMS
	void addOpenSourceRasterLayer( const QString& url, const QString& basename, const QString& providerKey );

	// ɾ��ͼ��
	void deleteLayer();

	// ��ʾͼ�������
	void showLayersWindow();
	// �ر�ͼ�������
	//void closeLayersWindow();
	// ͼ����������ѡ��ͼ�㷢���仯
	void layerSelected();
	// ��ͼ����ӵ�ͼ�������
	void addToManagerWindow(QgsMapLayer* layer);
	// ��ͼ����ӵ�ͼ�������
	void addToManagerWindow(QList<QgsMapLayer*> layers);

	// ͼ���ע
	void annotation();

	/*----------------------------�ռ����----------------------------*/

private:
	Ui::QgisDevClass ui;
	static QgisDev* qInstance;

	// ����
	QgsMapCanvas* mMapCanvas;
	// ����ͼ��
	QgsLayerTreeMapCanvasBridge* mLayerTreeCanvasBridge;

	// ������
	QActionGroup* mToolGroupMap;
	QActionGroup* mToolGroupLayer;
	// ��ͼ�Ŵ�
	QgsMapToolZoom* mZoomIn;
	// ��ͼ��С
	QgsMapToolZoom* mZoomOut;
	// ��ͼƽ��
	QgsMapToolPan* mPan;
	// ��ͼ���
	QgsMeasureTool* mMeasure;
	// ͼԪʶ��
	QgsMapToolIdentifyAction* mIdentify;
	// ͼ���ע
	QgsMapTool* mAnnotation;
};

#endif // QGISDEV_H
