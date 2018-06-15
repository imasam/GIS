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

	// ��ӵ�
	void addPoint(const QgsPoint& point);

	// ����ƶ�
	void mouseMove(const QgsPoint& point);
	
	// �Ƴ����һ���㣬�����ܳ���
	void removeLastPoint();

private:
	// ���ý���
	void updateSettings();

	// ��ʽ�����Ⱦ���
	QString formatDistance(double distance);

public slots:
	// ���¿�ʼ���
	void restart();

	virtual void reject() override;

	void closeEvent( QCloseEvent *e ) override;

private:
	// ���㳤�ȹ���
	QgsDistanceArea mDa;

	// ��๤��
	QgsMeasureTool* mTool;

	// ��λ
	QGis::UnitType mDistanceUnit;

	// �ܾ��볤��
	double mTotal;

	// ��ǰ�����ָ�ĵ�
	QgsPoint mCurrentPoint;

	Ui::QgsMeasureDialog ui;
};

#endif // QGSMEASUREDIALOG_H
