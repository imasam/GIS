#ifndef QGSMAPTOOLIDENTIFYACTION_H
#define QGSMAPTOOLIDENTIFYACTION_H

#include <QPoint>

// qgis include
#include <qgscursors.h>
#include <qgsmaptoolidentify.h>
#include <qgsmapcanvas.h>
#include "qgsidentifyresultsdialog.h"

class QgsMapToolIdentifyAction :
	public QgsMapToolIdentify
{
public:
	QgsMapToolIdentifyAction(QgsMapCanvas* canvas);
	~QgsMapToolIdentifyAction(void);

	virtual void canvasReleaseEvent(QgsMapMouseEvent* e) override;
	virtual void activate() override;
	virtual void deactivate() override;

private:
	QgsIdentifyResultsDialog* resultsDialog();

private:
	QgsMapCanvas* mCanvas;
	// ʶ�����Ի���
	QPointer<QgsIdentifyResultsDialog> mResultsDialog;
};

#endif