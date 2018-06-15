#include "qgisdev.h"
//#include <stdio.h>

QgisDev* QgisDev::qInstance = nullptr;

QgisDev::QgisDev(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags),
	  mMapCanvas(nullptr),
	  mLayerTreeCanvasBridge(nullptr),

	  mZoomIn(nullptr),
	  mZoomOut(nullptr),
	  mPan(nullptr),
	  mMeasure(nullptr),
	  mIdentify(nullptr)  
{
	ui.setupUi(this);
	qInstance = this;
	init();
}

QgisDev::~QgisDev()
{
	mMapCanvas->stopRendering();
	closeProj();

	delete mPan;
	delete mZoomIn;
	delete mZoomOut;
	delete mMeasure;
	delete mIdentify;
	delete mAnnotation;
	delete mMapCanvas;
	delete mLayerTreeCanvasBridge;

	QgsApplication::exitQgis();
	delete QgsProject::instance();
}

void QgisDev::closeEvent(QCloseEvent *e)
{
	QMessageBox::StandardButton answer(QMessageBox::Discard);
	if(QgsProject::instance()->isDirty())
	{
		answer = QMessageBox::information(
			this, 
			tr("退出"),
			tr("未保存的修改，是否退出？"),
			QMessageBox::Yes | QMessageBox::No,QMessageBox::No );
		if(QMessageBox::Yes == answer)
		{
			QgsProject::instance()->setDirty(false);
			e->accept();
		}
		else
			e->ignore();
	}
}

// 初始化
void QgisDev::init()
{
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));	// 设置中文编码

	QWidget *centralWidget = this->centralWidget();
	QGridLayout *centralLayout = new QGridLayout( centralWidget );
	centralWidget->setLayout( centralLayout );
	centralLayout->setContentsMargins( 0, 0, 0, 0 );

	mMapCanvas = new QgsMapCanvas( centralWidget, "theMapCanvas" );
	mMapCanvas->enableAntiAliasing(true);
	mMapCanvas->setVisible(true);
	mMapCanvas->setCanvasColor(QColor(255, 255, 255));
	centralLayout->addWidget(mMapCanvas, 0, 0, 1, 1);

	mLayerTreeCanvasBridge = new QgsLayerTreeMapCanvasBridge(QgsProject::instance()->layerTreeRoot(), mMapCanvas, this);
	mLayerTreeCanvasBridge->setAutoEnableCrsTransform(true);

	// 生成功能工具
	mPan = new QgsMapToolPan(mMapCanvas);
	mZoomOut = new QgsMapToolZoom(mMapCanvas, true);
	mZoomIn = new QgsMapToolZoom(mMapCanvas, false);
	mMeasure = new QgsMeasureTool(mMapCanvas);
	mAnnotation = new QgsMapToolAnnotation(mMapCanvas);
	mIdentify = new QgsMapToolIdentifyAction(mMapCanvas);
	
	// 设置不同工具的按钮互斥
	mToolGroupMap = new QActionGroup(this);
	mToolGroupMap->addAction(ui.actionpan);
	mToolGroupMap->addAction(ui.actionZoomIn);
	mToolGroupMap->addAction(ui.actionZoomOut);
	mToolGroupMap->addAction(ui.actionMeasure);
	mToolGroupMap->setExclusive(true);

	mToolGroupLayer = new QActionGroup(this);
	mToolGroupLayer->addAction(ui.actionAnnotation);
	mToolGroupLayer->addAction(ui.actionIdentify);

	// 标记已修改
	connect(mMapCanvas, SIGNAL(layersChanged()), this, SLOT(markDirty()));
	// 绑定读写
	connect(QgsProject::instance(), SIGNAL(writeProject(QDomDocument&)), mLayerTreeCanvasBridge, SLOT(writeProject(QDomDocument&)));
	connect(QgsProject::instance(), SIGNAL(readProject(QDomDocument)), mLayerTreeCanvasBridge, SLOT(readProject(QDomDocument)));
	// 绑定标注
	connect(QgsProject::instance(), SIGNAL(readProject(const QDomDocument&)), this,
		SLOT(loadAnnotationItemsFromProject(const QDomDocument&)));
	connect(QgsProject::instance(), SIGNAL(writeProject(QDomDocument&)),this, 
		SLOT(writeAnnotationItemsToProject(QDomDocument&)));
	// 绑定图层管理器
	connect(ui.layerList, SIGNAL( itemSelectionChanged()), this, SLOT(layerSelected()));
	connect(QgsMapLayerRegistry::instance(), SIGNAL(layersAdded(QList<QgsMapLayer*>)),
			this, SLOT(addToManagerWindow(QList<QgsMapLayer*>)));
	// 绑定动作
	connect(ui.actionNewProj, SIGNAL(triggered()), this, SLOT(newProj()));
	connect(ui.actionOpenProj, SIGNAL(triggered()), this, SLOT(openProj()));
	connect(ui.actionSaveProj, SIGNAL(triggered()), this, SLOT(saveProj()));
	connect(ui.actionSaveProjAs, SIGNAL(triggered()), this, SLOT(saveProjAs()));
	//connect(ui.actionCloseProj, SIGNAL(triggered()), this, SLOT(closeProj()));
		
	connect(ui.actionpan, SIGNAL(triggered()), this, SLOT(pan()));
	connect(ui.actionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));
	connect(ui.actionZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));
	connect(ui.actionMeasure, SIGNAL(triggered()), this, SLOT(measure()));
	
	connect(ui.actionAnnotation, SIGNAL(triggered()), this, SLOT(annotation()));
	connect(ui.actionShow, SIGNAL(triggered()), this, SLOT(showLayersWindow()));

	connect(ui.actionAddVector, SIGNAL(triggered()), this, SLOT(addVectorLayer()));
	connect(ui.actionAddRaster, SIGNAL(triggered()), this, SLOT(addRasterLayer()));
	connect(ui.actionAddWFS, SIGNAL(triggered()), this, SLOT(addWFSLayer()));
	connect(ui.actionAddWCS, SIGNAL(triggered()), this, SLOT(addWCSLayer()));
	connect(ui.actionAddWMS, SIGNAL(triggered()), this, SLOT(addWMSLayer()));
	connect(ui.actionDelete, SIGNAL(triggered()), this, SLOT(deleteLayer()));

	connect(ui.actionIdentify, SIGNAL(triggered()), this, SLOT(identify()));
}

void QgisDev::enableMenu()
{
	if(ui.menuMap->isEnabled())
		return;

	ui.actionSaveProj->setEnabled(true);
	ui.actionSaveProjAs->setEnabled(true);

	ui.menuMap->setEnabled(true);
	ui.menuLayer->setEnabled(true);
	ui.menuAnalysis->setEnabled(true);
}

void QgisDev::setTitle()
{
	QString title = "QgisDev";
	QString fileName = QgsProject::instance()->fileName();

	if(fileName.isNull())
		title += " - " + tr("未命名");
	else
		title += " - " + QFileInfo(fileName).completeBaseName();

	this->setWindowTitle(title);
}

/*----------------------------项目管理----------------------------*/
// 新建项目
void QgisDev::newProj()
{
	enableMenu();
	closeProj();
	QgsProject* proj = QgsProject::instance();

	proj->clear();
	proj->layerTreeRegistryBridge()->setNewLayersVisible(true);
	mLayerTreeCanvasBridge->clear();
	proj->setDirty(false);	

	mMapCanvas->freeze(false);
	mMapCanvas->refresh();
	mMapCanvas->clearExtentHistory();
	proj->setDirty(false);

	setTitle();
}
	
// 打开项目
void QgisDev::openProj()
{
	saveDirty();

	QFileInfo fullPath;
	QString path = QFileDialog::getOpenFileName(this,tr("选择QGis项目"),NULL,tr("QGIS files") + " (*.qgs *.QGS)");
	if(path.isEmpty())
		return ;

	enableMenu();

	fullPath.setFile(path);
	qApp->processEvents();
	QApplication::setOverrideCursor( Qt::WaitCursor );
	closeProj();

	if(!QgsProject::instance()->read(fullPath))
		QMessageBox::critical(this, tr("错误"), tr("无法读入项目文件"));

	setTitle();
	mMapCanvas->freeze(false);
	mMapCanvas->updateScale();
	mMapCanvas->refresh();

	QgsProject::instance()->setDirty(false);
	QApplication::restoreOverrideCursor();
}


// 保存项目
bool QgisDev::saveProj()
{
	// 没有选择项目文件时，提示用户选择
	if(QgsProject::instance()->fileName().isNull())
	{
		QFileInfo fullPath;
		QString path = QFileDialog::getSaveFileName(this,tr("选择QGis项目的保存位置"),NULL,tr("QGIS files") + " (*.qgs *.QGS)");
		if(path.isEmpty())
			return false;

		fullPath.setFile(path);
		if ("qgs" != fullPath.suffix().toLower())
		{
			fullPath.setFile(fullPath.filePath() + ".qgs");
		}

		QgsProject::instance()->setFileName(fullPath.filePath());
	}
	else
	{
		QFileInfo fi(QgsProject::instance()->fileName());

		// 检查是否可写
		if(fi.exists() && !fi.isWritable())
		{
			QMessageBox::critical(this, tr("错误"), tr("无法保存项目文件"));
			return false;
		}
	}

	setTitle();
	// 写
	return QgsProject::instance()->write();
}

// 另存为项目
void QgisDev::saveProjAs()
{
	// 将项目文件设置为NULL，再saveProj
	QString fileNameBak = QgsProject::instance()->fileName();
	bool dirtyBak = QgsProject::instance()->isDirty();

	QgsProject::instance()->setFileName(NULL);

	if(!saveProj())		// 另存为失败，恢复文件名
	{
		QgsProject::instance()->setFileName(fileNameBak);
		QgsProject::instance()->setDirty(dirtyBak);
	}
	setTitle();
}

// 关闭项目
void QgisDev::closeProj()
{
	saveDirty();

	mMapCanvas->freeze(true);
	//removeAnnotationItems();
	QList<QgsMapCanvasLayer> emptyList;
	mMapCanvas->setLayerSet(emptyList);
	mMapCanvas->clearCache();
	QgsMapLayerRegistry::instance()->removeAllMapLayers();
	ui.layerList->clear();
}

// 标记为已修改
void QgisDev::markDirty()
{
	QgsProject::instance()->setDirty(true);
}

// 保存修改
void QgisDev::saveDirty()
{
	bool dirty = QgsProject::instance()->isDirty();
	mMapCanvas->freeze(true);
	QMessageBox::StandardButton answer(QMessageBox::Discard);
	if(dirty)
	{
		answer = QMessageBox::information(this, tr("保存"),tr("项目已被修改，是否保存修改？"),
			QMessageBox::Save | QMessageBox::Cancel | QMessageBox::Discard,QMessageBox::Save );
		if(QMessageBox::Save == answer)
			saveProj();
	}
	mMapCanvas->freeze(false);
}

/*----------------------------地图操作----------------------------*/
// 工具选择
void QgisDev::setMapTool(QgsMapTool *tool)
{
	if(mMapCanvas->mapTool() == tool)	// 已选中时点击，取消选中
		unsetMapTool();
	else
		mMapCanvas->setMapTool(tool);
}

// 取消选中
void QgisDev::unsetMapTool()
{
	auto tool = mMapCanvas->mapTool();	// 获得当前选中工具

	if(tool)
	{
		mMapCanvas->unsetMapTool(tool);
	}
}

// 地图放大
void QgisDev::zoomIn()
{
	setMapTool(mZoomIn);
}

// 地图缩小
void QgisDev::zoomOut()
{
	setMapTool(mZoomOut);
}

// 地图平移
void QgisDev::pan()
{
	setMapTool(mPan);
}

// 地图测距
void QgisDev::measure()
{
	setMapTool(mMeasure);
}


/*----------------------------图层管理----------------------------*/

void QgisDev::identify()
{
	mMapCanvas->setMapTool(mIdentify);
}

// 添加矢量图层
void QgisDev::addVectorLayer()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("添加矢量图层"), "", "*.shp");
	if(filename.isEmpty()) 
		return;

	QStringList temp = filename.split(QDir::separator());
	QString basename = temp.at(temp.size() - 1);
	QgsVectorLayer* vecLayer = new QgsVectorLayer(filename, basename, "ogr", false);
	if(!vecLayer->isValid())
	{
		QMessageBox::critical(this, "error", "layer is invalid");
		return;
	}

	mMapCanvas->freeze(true);
	QgsMapLayerRegistry::instance()->addMapLayer(vecLayer);
	
	if(mMapCanvas->isFrozen())
	{
		mMapCanvas->freeze(false);
		mMapCanvas->refresh();
	}
}

// 添加栅格图层
void QgisDev::addRasterLayer()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("添加栅格图层"), "", "*.tif");
	if(filename.isEmpty()) 
		return;

	QStringList temp = filename.split(QDir::separator());
	QString basename = temp.at(temp.size() - 1);
	QgsRasterLayer* rasLayer = new QgsRasterLayer(filename, basename, "gdal", false);
	if(!rasLayer->isValid())
	{
		QMessageBox::critical(this, "error", "layer is invalid");
		return;
	}

	mMapCanvas->freeze(true);
	QgsMapLayerRegistry::instance()->addMapLayer(rasLayer);
	
	if(mMapCanvas->isFrozen())
	{
		mMapCanvas->freeze(false);
		mMapCanvas->refresh();
	}
}

// 添加WFS图层
void QgisDev::addWFSLayer()
{
 if ( !mMapCanvas ) 
	 return;

    QDialog *wfs = dynamic_cast<QDialog*>( QgsProviderRegistry::instance()->selectWidget( QString( "WFS" ), this ) );
    if ( !wfs )
    {
        QMessageBox::warning( this, tr( "WFS" ), tr( "Cannot get WFS select dialog from provider." ) );
        return;
    }
    connect( wfs, SIGNAL( addWfsLayer( QString, QString ) ),
             this, SLOT( addWfsLayer( const QString, const QString ) ) );

    //re-enable wfs with extent setting: pass canvas info to source select
    wfs->setProperty( "MapExtent", mMapCanvas->extent().toString() );
    if ( mMapCanvas->mapSettings().hasCrsTransformEnabled() )
    {
        //if "on the fly" reprojection is active, pass canvas CRS
        wfs->setProperty( "MapCRS", mMapCanvas->mapSettings().destinationCrs().authid() );
    }

    bool bkRenderFlag = mMapCanvas->renderFlag();
    mMapCanvas->setRenderFlag( false );
    wfs->exec();
    mMapCanvas->setRenderFlag( bkRenderFlag );
    delete wfs;   
}



// 添加WCS图层
void QgisDev::addWCSLayer()
{
	QDialog *wcs = dynamic_cast<QDialog*>( QgsProviderRegistry::instance()->selectWidget( QString( "wcs" ), this ) );
    if ( !wcs )
    {
        //QgisDev::instance()->statusBar()->showMessage( tr( "cannot add wms layer." ), 10 );
    }

    connect( wcs, SIGNAL( addRasterLayer( QString const &, QString const &, QString const & ) ),
             this, SLOT( addOpenSourceRasterLayer( QString const &, QString const &, QString const & ) ) );

    wcs->exec();

    delete wcs;
}

// 添加WMS图层
void QgisDev::addWMSLayer()
{
	QDialog *wms = dynamic_cast<QDialog*>( QgsProviderRegistry::instance()->selectWidget( QString( "wms" ), this ) );
    if ( !wms )
    {
        //QgisDev::instance()->statusBar()->showMessage( tr( "cannot add wms layer." ), 10 );
    }

    connect( wms, SIGNAL( addRasterLayer( QString const &, QString const &, QString const & ) ),
             this, SLOT( addOpenSourceRasterLayer( QString const &, QString const &, QString const & ) ) );

    wms->exec();

    delete wms;
}

void QgisDev::addOpenSourceRasterLayer( const QString& url, const QString& basename, const QString& providerKey )
{
    QgsRasterLayer *rasterLayer = 0;

    if ( providerKey.isEmpty() )
    {
        rasterLayer = new QgsRasterLayer( url, basename );
    }
    else
    {
        rasterLayer = new QgsRasterLayer( url, basename, providerKey );
    }

    if ( !rasterLayer->isValid() )
    {
        QMessageBox::critical( this, "error", "layer is invalid" );
        return;
    }

    QgsMapLayerRegistry::instance()->addMapLayer( rasterLayer );
    QgsMapLayerRegistry::instance()->addMapLayer(rasterLayer);
    mMapCanvas->setExtent( rasterLayer->extent() );
    mMapCanvas->setVisible( true );
    mMapCanvas->freeze( false );
    mMapCanvas->refresh();
}

// 删除图层
void QgisDev::deleteLayer()
{
	auto layer = ui.layerList->selectedItems()[0];	// 获取当前选中图层

	if(layer)
	{
		QMessageBox::StandardButton answer = QMessageBox::information(this, tr("删除图层"),
			tr("是否删除以下图层：\n") + layer->text(),QMessageBox::Ok | QMessageBox::Cancel,
			QMessageBox::Cancel );

		if(answer == QMessageBox::Ok)
		{
			this->setWindowTitle(mMapCanvas->currentLayer()->name());
			if(mMapCanvas->currentLayer())
				QgsMapLayerRegistry::instance()->removeMapLayer(mMapCanvas->currentLayer());
			ui.layerList->removeItemWidget(layer);
			delete layer;
		} 
	}
}

// 图层标注
void QgisDev::annotation()
{
	setMapTool(mAnnotation);	
}

// 显示图层管理器
void QgisDev::showLayersWindow()
{
	if(ui.layersManage->isHidden())
		ui.layersManage->show();
}

/*
// 关闭图层管理器
void QgisDev::closeLayersWindow()
{
	if(ui.layerManage->isVisible())
		ui.layerManage->close();
}
*/

// 图层管理器里的选中图层发生变化
void QgisDev::layerSelected()
{
	auto tmp = ui.layerList->selectedItems();
	if(tmp.isEmpty())
		return;

	auto layers = QgsMapLayerRegistry::instance()->mapLayersByName(tmp[0]->text());
	if(!layers.isEmpty())
	{
		mMapCanvas->setCurrentLayer(layers[0]);
	}
}

// 将图层添加到图层管理窗体
void QgisDev::addToManagerWindow(QgsMapLayer* layer)
{
	addToManagerWindow(QList<QgsMapLayer*>() << layer);
}

// 将图层添加到图层管理器
void QgisDev::addToManagerWindow(QList<QgsMapLayer*> layers)
{
	for(auto it = layers.begin(); it != layers.end(); it++)
	{
		QListWidgetItem *item = new QListWidgetItem(ui.layerList);
		item->setText((*it)->name());
		ui.layerList->addItem(item);
	}
}


/*----------------------------空间分析----------------------------*/