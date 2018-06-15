#ifndef QGSMEASUREDIALOG_H
#define QGSMEASUREDIALOG_H

#include <QDialog>
#include "ui_qgsmeasuredialog.h"
#include <QList>

// qgis include
#include <qgsproject.h>
#include <qgsmapcanvas.h>
#include <qgspoint.h>
#include <qgsdistancearea.h>

class QgsMeasureTool;

class QgsMeasureDialog : public QDialog
{
	Q_OBJECT

public:
	QgsMeasureDialog(QgsMeasureTool* tool, Qt::WindowFlags f = nullptr);

	// 添加点
	void addPoint(const QgsPoint& point);

	// 鼠标移动
	void mouseMove(const QgsPoint& point);
	
	// 移除最后一个点，更新总长度
	void removeLastPoint();

private:
	// 设置界面
	void updateSettings();

	// 格式化长度距离
	QString formatDistance(double distance);

public slots:
	// 重新开始测距
	void restart();

	virtual void reject() override;

	void closeEvent( QCloseEvent *e ) override;

private:
	// 计算长度工具
	QgsDistanceArea mDa;

	// 测距工具
	QgsMeasureTool* mTool;

	// 单位
	QGis::UnitType mDistanceUnit;

	// 总距离长度
	double mTotal;

	// 当前鼠标所指的点
	QgsPoint mCurrentPoint;

	Ui::QgsMeasureDialog ui;
};

#endif // QGSMEASUREDIALOG_H
