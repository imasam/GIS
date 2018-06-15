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
			tr("�˳�"),
			tr("δ������޸ģ��Ƿ��˳���"),
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

// ��ʼ��
void QgisDev::init()
{
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));	// �������ı���

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

	// ���ɹ��ܹ���
	mPan = new QgsMapToolPan(mMapCanvas);
	mZoomOut = new QgsMapToolZoom(mMapCanvas, true);
	mZoomIn = new QgsMapToolZoom(mMapCanvas, false);
	mMeasure = new QgsMeasureTool(mMapCanvas);
	mAnnotation = new QgsMapToolAnnotation(mMapCanvas);
	mIdentify = new QgsMapToolIdentifyAction(mMapCanvas);
	
	// ���ò�ͬ���ߵİ�ť����
	mToolGroupMap = new QActionGroup(this);
	mToolGroupMap->addAction(ui.actionpan);
	mToolGroupMap->addAction(ui.actionZoomIn);
	mToolGroupMap->addAction(ui.actionZoomOut);
	mToolGroupMap->addAction(ui.actionMeasure);
	mToolGroupMap->setExclusive(true);

	mToolGroupLayer = new QActionGroup(this);
	mToolGroupLayer->addAction(ui.actionAnnotation);
	mToolGroupLayer->addAction(ui.actionIdentify);

	// ������޸�
	connect(mMapCanvas, SIGNAL(layersChanged()), this, SLOT(markDirty()));
	// �󶨶�д
	connect(QgsProject::instance(), SIGNAL(writeProject(QDomDocument&)), mLayerTreeCanvasBridge, SLOT(writeProject(QDomDocument&)));
	connect(QgsProject::instance(), SIGNAL(readProject(QDomDocument)), mLayerTreeCanvasBridge, SLOT(readProject(QDomDocument)));
	// �󶨱�ע
	connect(QgsProject::instance(), SIGNAL(readProject(const QDomDocument&)), this,
		SLOT(loadAnnotationItemsFromProject(const QDomDocument&)));
	connect(QgsProject::instance(), SIGNAL(writeProject(QDomDocument&)),this, 
		SLOT(writeAnnotationItemsToProject(QDomDocument&)));
	// ��ͼ�������
	connect(ui.layerList, SIGNAL( itemSelectionChanged()), this, SLOT(layerSelected()));
	connect(QgsMapLayerRegistry::instance(), SIGNAL(layersAdded(QList<QgsMapLayer*>)),
			this, SLOT(addToManagerWindow(QList<QgsMapLayer*>)));
	// �󶨶���
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
		title += " - " + tr("δ����");
	else
		title += " - " + QFileInfo(fileName).completeBaseName();

	this->setWindowTitle(title);
}

/*----------------------------��Ŀ����----------------------------*/
// �½���Ŀ
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
	
// ����Ŀ
void QgisDev::openProj()
{
	saveDirty();

	QFileInfo fullPath;
	QString path = QFileDialog::getOpenFileName(this,tr("ѡ��QGis��Ŀ"),NULL,tr("QGIS files") + " (*.qgs *.QGS)");
	if(path.isEmpty())
		return ;

	enableMenu();

	fullPath.setFile(path);
	qApp->processEvents();
	QApplication::setOverrideCursor( Qt::WaitCursor );
	closeProj();

	if(!QgsProject::instance()->read(fullPath))
		QMessageBox::critical(this, tr("����"), tr("�޷�������Ŀ�ļ�"));

	setTitle();
	mMapCanvas->freeze(false);
	mMapCanvas->updateScale();
	mMapCanvas->refresh();

	QgsProject::instance()->setDirty(false);
	QApplication::restoreOverrideCursor();
}


// ������Ŀ
bool QgisDev::saveProj()
{
	// û��ѡ����Ŀ�ļ�ʱ����ʾ�û�ѡ��
	if(QgsProject::instance()->fileName().isNull())
	{
		QFileInfo fullPath;
		QString path = QFileDialog::getSaveFileName(this,tr("ѡ��QGis��Ŀ�ı���λ��"),NULL,tr("QGIS files") + " (*.qgs *.QGS)");
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

		// ����Ƿ��д
		if(fi.exists() && !fi.isWritable())
		{
			QMessageBox::critical(this, tr("����"), tr("�޷�������Ŀ�ļ�"));
			return false;
		}
	}

	setTitle();
	// д
	return QgsProject::instance()->write();
}

// ���Ϊ��Ŀ
void QgisDev::saveProjAs()
{
	// ����Ŀ�ļ�����ΪNULL����saveProj
	QString fileNameBak = QgsProject::instance()->fileName();
	bool dirtyBak = QgsProject::instance()->isDirty();

	QgsProject::instance()->setFileName(NULL);

	if(!saveProj())		// ���Ϊʧ�ܣ��ָ��ļ���
	{
		QgsProject::instance()->setFileName(fileNameBak);
		QgsProject::instance()->setDirty(dirtyBak);
	}
	setTitle();
}

// �ر���Ŀ
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

// ���Ϊ���޸�
void QgisDev::markDirty()
{
	QgsProject::instance()->setDirty(true);
}

// �����޸�
void QgisDev::saveDirty()
{
	bool dirty = QgsProject::instance()->isDirty();
	mMapCanvas->freeze(true);
	QMessageBox::StandardButton answer(QMessageBox::Discard);
	if(dirty)
	{
		answer = QMessageBox::information(this, tr("����"),tr("��Ŀ�ѱ��޸ģ��Ƿ񱣴��޸ģ�"),
			QMessageBox::Save | QMessageBox::Cancel | QMessageBox::Discard,QMessageBox::Save );
		if(QMessageBox::Save == answer)
			saveProj();
	}
	mMapCanvas->freeze(false);
}

/*----------------------------��ͼ����----------------------------*/
// ����ѡ��
void QgisDev::setMapTool(QgsMapTool *tool)
{
	if(mMapCanvas->mapTool() == tool)	// ��ѡ��ʱ�����ȡ��ѡ��
		unsetMapTool();
	else
		mMapCanvas->setMapTool(tool);
}

// ȡ��ѡ��
void QgisDev::unsetMapTool()
{
	auto tool = mMapCanvas->mapTool();	// ��õ�ǰѡ�й���

	if(tool)
	{
		mMapCanvas->unsetMapTool(tool);
	}
}

// ��ͼ�Ŵ�
void QgisDev::zoomIn()
{
	setMapTool(mZoomIn);
}

// ��ͼ��С
void QgisDev::zoomOut()
{
	setMapTool(mZoomOut);
}

// ��ͼƽ��
void QgisDev::pan()
{
	setMapTool(mPan);
}

// ��ͼ���
void QgisDev::measure()
{
	setMapTool(mMeasure);
}


/*----------------------------ͼ�����----------------------------*/

void QgisDev::identify()
{
	mMapCanvas->setMapTool(mIdentify);
}

// ���ʸ��ͼ��
void QgisDev::addVectorLayer()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("���ʸ��ͼ��"), "", "*.shp");
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

// ���դ��ͼ��
void QgisDev::addRasterLayer()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("���դ��ͼ��"), "", "*.tif");
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

// ���WFSͼ��
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



// ���WCSͼ��
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

// ���WMSͼ��
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

// ɾ��ͼ��
void QgisDev::deleteLayer()
{
	auto layer = ui.layerList->selectedItems()[0];	// ��ȡ��ǰѡ��ͼ��

	if(layer)
	{
		QMessageBox::StandardButton answer = QMessageBox::information(this, tr("ɾ��ͼ��"),
			tr("�Ƿ�ɾ������ͼ�㣺\n") + layer->text(),QMessageBox::Ok | QMessageBox::Cancel,
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

// ͼ���ע
void QgisDev::annotation()
{
	setMapTool(mAnnotation);	
}

// ��ʾͼ�������
void QgisDev::showLayersWindow()
{
	if(ui.layersManage->isHidden())
		ui.layersManage->show();
}

/*
// �ر�ͼ�������
void QgisDev::closeLayersWindow()
{
	if(ui.layerManage->isVisible())
		ui.layerManage->close();
}
*/

// ͼ����������ѡ��ͼ�㷢���仯
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

// ��ͼ����ӵ�ͼ�������
void QgisDev::addToManagerWindow(QgsMapLayer* layer)
{
	addToManagerWindow(QList<QgsMapLayer*>() << layer);
}

// ��ͼ����ӵ�ͼ�������
void QgisDev::addToManagerWindow(QList<QgsMapLayer*> layers)
{
	for(auto it = layers.begin(); it != layers.end(); it++)
	{
		QListWidgetItem *item = new QListWidgetItem(ui.layerList);
		item->setText((*it)->name());
		ui.layerList->addItem(item);
	}
}


/*----------------------------�ռ����----------------------------*/