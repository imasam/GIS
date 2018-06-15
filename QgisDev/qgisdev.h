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
	// 初始化界面
	void init();

	// 有项目后使菜单栏可用
	void enableMenu();

	// 设置窗体标题
	void setTitle();

	/*----------------------------项目管理----------------------------*/
	// 新建项目
	void newProj();
	// 打开项目
	void openProj();
	// 保存项目
	bool saveProj();
	// 另存为项目
	void saveProjAs();
	// 关闭项目
	void closeProj();

	// 标记为已修改
	void markDirty();
	// 保存修改
	void saveDirty();
	
	/*----------------------------地图操作----------------------------*/
	// 工具选择
	void setMapTool(QgsMapTool *tool);
	// 取消选中
	void unsetMapTool();
	// 放大地图
	void zoomIn();
	// 缩小地图
	void zoomOut();
	// 平移地图
	void pan();
	// 测距
	void measure();

	/*----------------------------图层管理----------------------------*/

	// 图元识别
	void identify();

	// 添加矢量图层
	void addVectorLayer();
	// 添加WFS图层
	void addWFSLayer();
	// 添加栅格图层
	void addRasterLayer();
	// 添加WCS图层
	void addWCSLayer();
	// 添加WMS图层
	void addWMSLayer();

	//**********添加图层，用于WMS
	void addOpenSourceRasterLayer( const QString& url, const QString& basename, const QString& providerKey );

	// 删除图层
	void deleteLayer();

	// 显示图层管理器
	void showLayersWindow();
	// 关闭图层管理器
	//void closeLayersWindow();
	// 图层管理器里的选中图层发生变化
	void layerSelected();
	// 将图层添加到图层管理窗体
	void addToManagerWindow(QgsMapLayer* layer);
	// 将图层添加到图层管理器
	void addToManagerWindow(QList<QgsMapLayer*> layers);

	// 图层标注
	void annotation();

	/*----------------------------空间分析----------------------------*/

private:
	Ui::QgisDevClass ui;
	static QgisDev* qInstance;

	// 画布
	QgsMapCanvas* mMapCanvas;
	// 管理图层
	QgsLayerTreeMapCanvasBridge* mLayerTreeCanvasBridge;

	// 工具组
	QActionGroup* mToolGroupMap;
	QActionGroup* mToolGroupLayer;
	// 地图放大
	QgsMapToolZoom* mZoomIn;
	// 地图缩小
	QgsMapToolZoom* mZoomOut;
	// 地图平移
	QgsMapToolPan* mPan;
	// 地图测距
	QgsMeasureTool* mMeasure;
	// 图元识别
	QgsMapToolIdentifyAction* mIdentify;
	// 图层标注
	QgsMapTool* mAnnotation;
};

#endif // QGISDEV_H
