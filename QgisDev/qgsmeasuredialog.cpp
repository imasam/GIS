#include "qgsmeasuredialog.h"
#include "qgsmeasuretool.h"

QgsMeasureDialog::QgsMeasureDialog(QgsMeasureTool* tool, Qt::WindowFlags f)
	: QDialog(tool->canvas()->topLevelWidget(), f)
	, mTool(tool)
{
	ui.setupUi(this);
	updateSettings();
	connect(ui.restartButton, SIGNAL(clicked()), this, SLOT(restart()));
}

void QgsMeasureDialog::updateSettings()
{
	mDistanceUnit = QgsProject::instance()->distanceUnits();
}

void QgsMeasureDialog::addPoint(const QgsPoint& point)
{
	int numPoints = mTool->points().size();
	if(numPoints > 1)
	{
		mTotal = mDa.measureLine(mTool->points());
		ui.totalDist->setText(formatDistance(mTotal));
	}
}

void QgsMeasureDialog::mouseMove(const QgsPoint& point)
{
	mCurrentPoint = point;
	QgsPoint p1(mTool->points().last()), p2(point);
	double d = mDa.measureLine(p1, p2);

	ui.totalDist->setText(formatDistance(mTotal + d));
}

void QgsMeasureDialog::removeLastPoint()
{
	// mTool中有点存在时才有必要更新长度
	if(mTool->points().size() > 0)
	{
		mTotal = mDa.measureLine(mTool->points());

		if(!mTool->done())	// 如果还未完成测距则加上最后一个点到当前鼠标的距离
		{
			double d = mDa.measureLine(mTool->points().last(), mCurrentPoint);
			ui.totalDist->setText(formatDistance(mTotal + d));
		}
		else
		{
			ui.totalDist->setText(formatDistance(mTotal));
		}
	}
}

void QgsMeasureDialog::restart()
{
	ui.totalDist->setText(formatDistance(0.0));
	mTool->restart();
}

QString QgsMeasureDialog::formatDistance(double distance)
{
	return QgsDistanceArea::formatDistance(distance, 3, mDistanceUnit, false);
}

void QgsMeasureDialog::reject()
{
	restart();
	QDialog::close();
}

void QgsMeasureDialog::closeEvent( QCloseEvent *e )
{
	reject();
	e->accept();
}