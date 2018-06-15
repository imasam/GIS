#include "qgsmeasuretool.h"


QgsMeasureTool::QgsMeasureTool(QgsMapCanvas* canvas)
	: QgsMapTool(canvas)
	, mDialog(nullptr)
	, mRubberBand(nullptr)
	, mRubberBandPoints(nullptr)
{
	mRubberBand = new QgsRubberBand(canvas, QGis::Line);
	mRubberBandPoints = new QgsRubberBand(canvas, QGis::Point);

	QPixmap myCrossHairQPixmap = QPixmap(( const char ** ) cross_hair_cursor );
	mCursor = QCursor( myCrossHairQPixmap, 8, 8 );

	mDone = true;	// true��ʾ�´ε�����¿�ʼ���

	// ��ӵ�
	mPoints.append(QgsPoint(0, 0));

	mDialog = new QgsMeasureDialog(this);
	mDialog->setWindowFlags(mDialog->windowFlags() | Qt::Tool);
}

QgsMeasureTool::~QgsMeasureTool()
{
	delete mDialog;
	delete mRubberBand;
	delete mRubberBandPoints;
}

void QgsMeasureTool::activate()
{
	mDialog->show();
	QgsMapTool::activate();

	// ensure that we have correct settings
	updateSettings();

	// If we suspect that they have data that is projected, yet the
	// map CRS is set to a geographic one, warn them.
	if ( mCanvas->mapSettings().destinationCrs().geographicFlag() &&
		( mCanvas->extent().height() > 360 ||
		mCanvas->extent().width() > 720 ) )
	{
		QMessageBox::warning( nullptr, tr( "Incorrect measure results" ),
			tr( "<p>This map is defined with a geographic coordinate system "
			"(latitude/longitude) "
			"but the map extents suggests that it is actually a projected "
			"coordinate system (e.g., Mercator). "
			"If so, the results from line or area measurements will be "
			"incorrect.</p>"
			"<p>To fix this, explicitly set an appropriate map coordinate "
			"system using the <tt>Settings:Project Properties</tt> menu." ) );
	}
}

void QgsMeasureTool::deactivate()
{
	mDialog->hide();
	QgsMapTool::deactivate();
}

void QgsMeasureTool::restart()
{
	mPoints.clear();

	mRubberBand->reset(QGis::Line);
	mRubberBandPoints->reset(QGis::Point);

	mDone = true;
}

void QgsMeasureTool::updateSettings()
{
	// ��ɫ����
	int myRed = 222, myGreen = 155, myBlue = 67;
	mRubberBand->setColor(QColor(myRed, myGreen, myBlue, 100));
	mRubberBand->setWidth(3);
	mRubberBandPoints->setIcon( QgsRubberBand::ICON_CIRCLE );
	mRubberBandPoints->setIconSize( 10 );
	mRubberBandPoints->setColor( QColor( myRed, myGreen, myBlue, 150 ) );
}

void QgsMeasureTool::canvasPressEvent( QgsMapMouseEvent* e )
{
	Q_UNUSED( e );
}

void QgsMeasureTool::canvasMoveEvent( QgsMapMouseEvent* e )
{
	if ( ! mDone )
	{
		QgsPoint point = snapPoint( e->pos() );

		mRubberBand->movePoint( point );
		mDialog->mouseMove( point );
	}
	Q_UNUSED(e);
}


void QgsMeasureTool::canvasReleaseEvent( QgsMapMouseEvent* e )
{
	QgsPoint point = snapPoint( e->pos() );

	// ���������ֹͣ���������������¿�ʼ����
	if ( mDone )	
	{
		mDialog->restart();
	}

	// ����Ҽ���ֹͣ����
	if ( e->button() == Qt::RightButton )	
	{
		mDone = true;
	}
	else if ( e->button() == Qt::LeftButton )
	{
		mDone = false;
	}

	// add the clicked point to the measuring feature
	addPoint( point );
	mDialog->show();

}

void QgsMeasureTool::undo()
{
	if ( mRubberBand )
	{
		if ( mPoints.size() < 1 )
		{
			return;
		}

		if ( mPoints.size() == 1 )
		{
			//removing first point, so restart everything
			restart();
			mDialog->restart();
		}
		else
		{
			//remove second last point from line band, and last point from points band
			mRubberBand->removePoint( -2, true );
			mRubberBandPoints->removePoint( -1, true );
			mPoints.removeLast();

			mDialog->removeLastPoint();
		}

	}
}

void QgsMeasureTool::keyPressEvent( QKeyEvent* e )
{
	if (( e->key() == Qt::Key_Backspace || e->key() == Qt::Key_Delete ) )
	{
		if ( !mDone )
		{
			undo();
		}

		e->ignore();
	}
}


void QgsMeasureTool::addPoint( const QgsPoint &point )
{
	// �����ظ���
	if ( !mPoints.isEmpty() && mPoints.last() == point )
	{
		return;
	}

	QgsPoint pnt( point );
	// �����ƶ��ĵ�
	mPoints.append( pnt );

	mRubberBand->addPoint( point );
	mRubberBandPoints->addPoint( point );
	if ( ! mDone )    // ��ֹ����Ŀ����
	{
		mDialog->addPoint( point );
	}
}


QgsPoint QgsMeasureTool::snapPoint( const QPoint& p )
{
	QgsPointLocator::Match m = mCanvas->snappingUtils()->snapToMap( p );
	return m.isValid() ? m.point() : mCanvas->getCoordinateTransform()->toMapCoordinates( p );
}
