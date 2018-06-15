#include "qgsidentifyresultsdialog.h"
#include "qgisdev.h"

QgsIdentifyResultsFeatureItem::QgsIdentifyResultsFeatureItem( const QgsFields &fields, const QgsFeature &feature, const QgsCoordinateReferenceSystem &crs, const QStringList & strings )
	: QTreeWidgetItem( strings )
	, mFields( fields )
	, mFeature( feature )
	, mCrs( crs )
{
}

QgsIdentifyResultsDialog::QgsIdentifyResultsDialog(QgsMapCanvas *canvas, QWidget *parent)
	: QDialog(parent)
	, mCanvas(canvas)
	, mDock(nullptr)
{
	ui.setupUi(this);

	mDock = new QDockWidget(tr("识别结果"), QgisDev::instance());
	mDock->setObjectName("IdentifyResultsDock");
	mDock->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
	mDock->setWidget(this);
	QgisDev::instance()->addDockWidget( Qt::RightDockWidgetArea, mDock );

	ui.lstResults->setColumnCount( 2 );
	ui.lstResults->sortByColumn( -1 );

	setColumnText( 0, tr( "Feature" ) );
	setColumnText( 1, tr( "Value" ) );
}

QgsIdentifyResultsDialog::~QgsIdentifyResultsDialog()
{
}

void QgsIdentifyResultsDialog::setColumnText( int column, const QString & label )
{
	QTreeWidgetItem* header = ui.lstResults->headerItem();
	header->setText( column, label );
}

void QgsIdentifyResultsDialog::show()
{
	if ( ui.lstResults->topLevelItemCount() > 0 )
	{
		QTreeWidgetItem *layItem = ui.lstResults->topLevelItem( 0 );
		QTreeWidgetItem *featItem = layItem->child( 0 );

		if ( ui.lstResults->topLevelItemCount() == 1 && layItem->childCount() == 1 )
		{
			ui.lstResults->setCurrentItem( featItem );
		}

		// expand first layer and feature
		featItem->setExpanded( true );
		layItem->setExpanded( true );
	}

	ui.lstResults->expandAll();

	QDialog::show();

	mDock->show();
	mDock->raise();
}

void QgsIdentifyResultsDialog::activate()
{
	Q_FOREACH ( QgsHighlight *h, mHighlights )
	{
		h->show();
	}

	if( ui.lstResults->topLevelItemCount() > 0 )
	{
		raise();
	}
}

void QgsIdentifyResultsDialog::deactivate()
{
	Q_FOREACH ( QgsHighlight *h, mHighlights )
	{
		h->hide();
	}
	clear();
}

void QgsIdentifyResultsDialog::clear()
{
	for ( int i = 0; i < ui.lstResults->topLevelItemCount(); i++ )
	{
		disconnectLayer( ui.lstResults->topLevelItem( i )->data( 0, Qt::UserRole ).value<QObject *>() );
	}

	ui.lstResults->clear();
	ui.lstResults->sortByColumn( -1 );
	clearHighlights();
}

void QgsIdentifyResultsDialog::clearHighlights()
{
	Q_FOREACH ( QgsHighlight *h, mHighlights )
	{
		delete h;
	}

	mHighlights.clear();
}

QgsVectorLayer *QgsIdentifyResultsDialog::vectorLayer( QTreeWidgetItem *item )
{
	item = layerItem( item );
	if ( !item )
		return nullptr;
	return qobject_cast<QgsVectorLayer *>( item->data( 0, Qt::UserRole ).value<QObject *>() );
}

QgsRasterLayer *QgsIdentifyResultsDialog::rasterLayer( QTreeWidgetItem *item )
{
	item = layerItem( item );
	if ( !item )
		return nullptr;
	return qobject_cast<QgsRasterLayer *>( item->data( 0, Qt::UserRole ).value<QObject *>() );
}

QTreeWidgetItem *QgsIdentifyResultsDialog::featureItem( QTreeWidgetItem *item )
{
	if ( !item )
		return nullptr;

	QTreeWidgetItem *featItem = nullptr;
	if ( item->parent() )
	{
		if ( item->parent()->parent() )
		{
			if ( item->parent()->parent()->parent() )
			{
				// derived or action attribute item
				featItem = item->parent()->parent();
			}
			else
			{
				// attribute item
				featItem = item->parent();
			}
		}
		else
		{
			// feature item
			featItem = item;
		}
	}
	else
	{
		// top level layer item, return feature item if only one
#if 0
		if ( item->childCount() > 1 )
			return 0;
		featItem = item->child( 0 );
#endif

		int count = 0;

		for ( int i = 0; i < item->childCount(); i++ )
		{
			QgsIdentifyResultsFeatureItem *fi = dynamic_cast<QgsIdentifyResultsFeatureItem *>( item->child( i ) );
			if ( fi )
			{
				count++;
				if ( !featItem )
					featItem = fi;
			}
		}

		if ( count != 1 )
			return nullptr;
	}

	return featItem;
}

QTreeWidgetItem *QgsIdentifyResultsDialog::layerItem( QObject *object )
{
	for ( int i = 0; i < ui.lstResults->topLevelItemCount(); i++ )
	{
		QTreeWidgetItem *item = ui.lstResults->topLevelItem( i );

		if ( item->data( 0, Qt::UserRole ).value<QObject *>() == object )
			return item;
	}

	return nullptr;
}

QTreeWidgetItem *QgsIdentifyResultsDialog::layerItem( QTreeWidgetItem *item )
{
	if ( item && item->parent() )
	{
		item = featureItem( item )->parent();
	}

	return item;
}

void QgsIdentifyResultsDialog::addFeature(const QgsMapToolIdentify::IdentifyResult& result)
{
	if ( result.mLayer->type() == QgsMapLayer::VectorLayer )
	{
		addFeature( qobject_cast<QgsVectorLayer *>( result.mLayer ), result.mFeature, result.mDerivedAttributes );
	}
	else if ( result.mLayer->type() == QgsMapLayer::RasterLayer )
	{
		addFeature( qobject_cast<QgsRasterLayer *>( result.mLayer ), result.mLabel, result.mAttributes, result.mDerivedAttributes, result.mFields, result.mFeature, result.mParams );
	}
}

void QgsIdentifyResultsDialog::addFeature( QgsRasterLayer * layer, const QString& label, const QMap< QString, QString > &attributes, const QMap< QString, QString > &derivedAttributes, const QgsFields &fields /* = QgsFields() */, const QgsFeature &feature /* = QgsFeature() */, const QMap<QString, QVariant> &params /* = ( QMap<QString , QVariant>() )*/ )
{

}

void QgsIdentifyResultsDialog::addFeature( QgsVectorLayer *vlayer, const QgsFeature &f, const QMap<QString, QString> &derivedAttributes )
{
	QTreeWidgetItem *layItem = layerItem( vlayer );

	if ( !layItem )
	{
		layItem = new QTreeWidgetItem( QStringList() << vlayer->name() );
		layItem->setData( 0, Qt::UserRole, QVariant::fromValue( qobject_cast<QObject *>( vlayer ) ) );
		ui.lstResults->addTopLevelItem( layItem );

		connect( vlayer, SIGNAL( layerDeleted() ), this, SLOT( layerDestroyed() ) );
// 		connect( vlayer, SIGNAL( layerCrsChanged() ), this, SLOT( layerDestroyed() ) );
// 		connect( vlayer, SIGNAL( featureDeleted( QgsFeatureId ) ), this, SLOT( featureDeleted( QgsFeatureId ) ) );
// 		connect( vlayer, SIGNAL( attributeValueChanged( QgsFeatureId, int, const QVariant & ) ),
// 			this, SLOT( attributeValueChanged( QgsFeatureId, int, const QVariant & ) ) );
// 		connect( vlayer, SIGNAL( editingStarted() ), this, SLOT( editingToggled() ) );
// 		connect( vlayer, SIGNAL( editingStopped() ), this, SLOT( editingToggled() ) );
	}

	QgsIdentifyResultsFeatureItem *featItem = new QgsIdentifyResultsFeatureItem( vlayer->fields(), f, vlayer->crs() );
	featItem->setData( 0, Qt::UserRole, FID_TO_STRING( f.id() ) );
	featItem->setData( 0, Qt::UserRole + 1, mFeatures.size() );
	mFeatures << f;
	layItem->addChild( featItem );

	if ( derivedAttributes.size() >= 0 )
	{
		QTreeWidgetItem *derivedItem = new QTreeWidgetItem( QStringList() << tr( "(Derived)" ) );
		derivedItem->setData( 0, Qt::UserRole, "derived" );
		featItem->addChild( derivedItem );

		for ( QMap< QString, QString>::const_iterator it = derivedAttributes.begin(); it != derivedAttributes.end(); ++it )
		{
			derivedItem->addChild( new QTreeWidgetItem( QStringList() << it.key() << it.value() ) );
		}
	}

 	const QgsFields &fields = vlayer->fields();
 	QgsAttributes attrs = f.attributes();
 	bool featureLabeled = false;
 	for ( int i = 0; i < attrs.count(); ++i )
 	{
 		if ( i >= fields.count() )
 			continue;
 
 		if ( vlayer->editFormConfig()->widgetType( i ) == "Hidden" )
 		{
 			continue;
 		}
 
 		// _TAG
 		QString defVal;
 		if ( fields.fieldOrigin( i ) == QgsFields::OriginProvider && vlayer->dataProvider() )
 			defVal = vlayer->dataProvider()->defaultValue( fields.fieldOriginIndex( i ), true ).toString();
 
 		QString value = defVal == attrs.at( i ) ? defVal : fields.at( i ).displayString( attrs.at( i ) );
 		QTreeWidgetItem *attrItem = new QTreeWidgetItem( QStringList() << QString::number( i ) << value );
 		featItem->addChild( attrItem );
 
 		attrItem->setData( 0, Qt::DisplayRole, vlayer->attributeDisplayName( i ) );
 		attrItem->setData( 0, Qt::UserRole, fields[i].name() );
 		attrItem->setData( 0, Qt::UserRole + 1, i );
 
 		attrItem->setData( 1, Qt::UserRole, value );
 
 		value = representValue( vlayer, fields.at( i ).name(), attrs.at( i ) );
 		bool foundLinks = false;
 		QString links = QgsStringUtils::insertLinks( value, &foundLinks );
 		if ( foundLinks )
 		{
 			QLabel* valueLabel = new QLabel( links );
 			valueLabel->setOpenExternalLinks( true );
 			attrItem->treeWidget()->setItemWidget( attrItem, 1, valueLabel );
 			attrItem->setData( 1, Qt::DisplayRole, QString() );
 		}
 		else
 		{
 			attrItem->setData( 1, Qt::DisplayRole, value );
 			attrItem->treeWidget()->setItemWidget( attrItem, 1, nullptr );
 		}
 
 		if ( fields[i].name() == vlayer->displayField() )
 		{
 			featItem->setText( 0, attrItem->text( 0 ) );
 			featItem->setText( 1, attrItem->text( 1 ) );
 			featureLabeled = true;
 		}
 	}
 
 	if ( !featureLabeled )
 	{
 		featItem->setText( 0, tr( "feature id" ) );
 		featItem->setText( 1, QString::number( f.id() ) );
 	}

	highlightFeature( featItem );
}

 QString QgsIdentifyResultsDialog::representValue( QgsVectorLayer* vlayer, const QString& fieldName, const QVariant& value )
 {
 	QVariant cache;
 	QMap<QString, QVariant>& layerCaches = mWidgetCaches[vlayer->id()];
 
 	QString widgetType = vlayer->editFormConfig()->widgetType( fieldName );
 	QgsEditorWidgetFactory* factory = QgsEditorWidgetRegistry::instance()->factory( widgetType );
 
 	int idx = vlayer->fieldNameIndex( fieldName );
 
 	if ( !factory )
 		return value.toString();
 
 	if ( layerCaches.contains( fieldName ) )
 	{
 		cache = layerCaches[ fieldName ];
 	}
 	else
 	{
 		cache = factory->createCache( vlayer, idx, vlayer->editFormConfig()->widgetConfig( fieldName ) );
 		layerCaches.insert( fieldName, cache );
 	}
 
 	return factory->representValue( vlayer, idx, vlayer->editFormConfig()->widgetConfig( fieldName ), cache, value );
 }

void QgsIdentifyResultsDialog::layerDestroyed()
{
	QObject *theSender = sender();

	for ( int i = 0; i < ui.lstResults->topLevelItemCount(); i++ )
	{
		QTreeWidgetItem *layItem = ui.lstResults->topLevelItem( i );

		if ( layItem->data( 0, Qt::UserRole ).value<QObject *>() == sender() )
		{
			for ( int j = 0; j < layItem->childCount(); j++ )
			{
				delete mHighlights.take( layItem->child( j ) );
			}
		}
	}

	disconnectLayer( theSender );
	delete layerItem( theSender );
}

void QgsIdentifyResultsDialog::disconnectLayer( QObject *layer )
{
	if ( !layer )
		return;

	QgsVectorLayer *vlayer = qobject_cast<QgsVectorLayer *>( layer );
	if ( vlayer )
	{
		disconnect( vlayer, SIGNAL( layerDeleted() ), this, SLOT( layerDestroyed() ) );
// 		disconnect( vlayer, SIGNAL( featureDeleted( QgsFeatureId ) ), this, SLOT( featureDeleted( QgsFeatureId ) ) );
// 		disconnect( vlayer, SIGNAL( attributeValueChanged( QgsFeatureId, int, const QVariant & ) ),
// 			this, SLOT( attributeValueChanged( QgsFeatureId, int, const QVariant & ) ) );
// 		disconnect( vlayer, SIGNAL( editingStarted() ), this, SLOT( editingToggled() ) );
// 		disconnect( vlayer, SIGNAL( editingStopped() ), this, SLOT( editingToggled() ) );
	}
	else
	{
		disconnect( layer, SIGNAL( destroyed() ), this, SLOT( layerDestroyed() ) );
	}
}

void QgsIdentifyResultsDialog::highlightFeature( QTreeWidgetItem *item )
{
	QgsMapLayer *layer;
	QgsVectorLayer *vlayer = vectorLayer( item );
	QgsRasterLayer *rlayer = rasterLayer( item );

	layer = vlayer ? static_cast<QgsMapLayer *>( vlayer ) : static_cast<QgsMapLayer *>( rlayer );

	if ( !layer ) return;

	QgsIdentifyResultsFeatureItem *featItem = dynamic_cast<QgsIdentifyResultsFeatureItem *>( featureItem( item ) );
	if ( !featItem )
		return;

	if ( mHighlights.contains( featItem ) )
		return;

	if ( !featItem->feature().constGeometry() || featItem->feature().constGeometry()->wkbType() == QGis::WKBUnknown )
		return;

	QgsHighlight *highlight = nullptr;
	if ( vlayer )
	{
		highlight = new QgsHighlight( mCanvas, featItem->feature(), vlayer );
	}
	else
	{
		highlight = new QgsHighlight( mCanvas, featItem->feature().constGeometry(), layer );
		highlight->setWidth( 2 );
	}

	QColor color = QGis::DEFAULT_HIGHLIGHT_COLOR.name();
	int alpha = QGis::DEFAULT_HIGHLIGHT_COLOR.alpha();
	double buffer = QGis::DEFAULT_HIGHLIGHT_BUFFER_MM;
	double minWidth = QGis::DEFAULT_HIGHLIGHT_MIN_WIDTH_MM;

	highlight->setColor( color ); // sets also fill with default alpha
	color.setAlpha( alpha );
	highlight->setFillColor( color ); // sets fill with alpha
	highlight->setBuffer( buffer );
	highlight->setMinWidth( minWidth );
	highlight->show();
	mHighlights.insert( featItem, highlight );
}