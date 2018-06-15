#pragma once	// 解决"PCH 警告:标头停止点不能位于宏或#if块中"
#ifndef QGSMEASURETOOL_H
#define QGSMEASURETOOL_H

#include <QMessageBox>
#include <QList>

// qgis include
#include <qgsmaptool.h>
#include <qgsrubberband.h>
#include <qgscursors.h>
#include <qgspoint.h>
#include <qgsmapcanvas.h>

#include "qgsmeasuredialog.h"

class QgsMeasureTool :public QgsMapTool
{
	Q_OBJECT

public:
	QgsMeasureTool(QgsMapCanvas* canvas);
	~QgsMeasureTool();

	bool done() {return mDone;}

	//! Reset and start new
    void restart();

    //! Add new point
    void addPoint( const QgsPoint &point );

	//! Returns reference to array of the points
	const QList<QgsPoint>& points() {return mPoints;}

	// Inherited from QgsMapTool

	//! Mouse move event for overriding
	virtual void canvasMoveEvent( QgsMapMouseEvent* e ) override;

	//! Mouse press event for overriding
	virtual void canvasPressEvent( QgsMapMouseEvent* e ) override;

	//! Mouse release event for overriding
	virtual void canvasReleaseEvent( QgsMapMouseEvent* e ) override;

	//! called when set as currently active map tool
	virtual void activate() override;

	//! called when map tool is being deactivated
	virtual void deactivate() override;

	virtual void keyPressEvent( QKeyEvent* e ) override;

public slots:
	//! updates the projections we're using
	void updateSettings();

private:
	QgsPoint snapPoint(const QPoint& p);

	QList<QgsPoint> mPoints;

	QgsMeasureDialog* mDialog;

	//! Rubberband widget tracking the lines being drawn
	QgsRubberBand *mRubberBand;

	//! Rubberband widget tracking the added nodes to line
	QgsRubberBand *mRubberBandPoints;

	//! indicates whether we've just done a right mouse click
	bool mDone;

	/** Removes the last vertex from mRubberBand*/
	void undo();
};

#endif