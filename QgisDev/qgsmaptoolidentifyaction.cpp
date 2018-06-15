#include "qgsmaptoolidentifyaction.h"

QgsMapToolIdentifyAction::QgsMapToolIdentifyAction(QgsMapCanvas* canvas)
	: QgsMapToolIdentify(canvas)
	, mCanvas(canvas)
{
	QPixmap myIdentifyQPixmap = QPixmap(( const char ** ) identify_cursor );
	mCursor = QCursor( myIdentifyQPixmap, 1, 1 );
}


QgsMapToolIdentifyAction::~QgsMapToolIdentifyAction(void)
{
	if(mResultsDialog)
	{
		mResultsDialog->done(0);
	}
}

void QgsMapToolIdentifyAction::canvasReleaseEvent(QgsMapMouseEvent* e)
{
	resultsDialog()->clear();

	QList<IdentifyResult> results = QgsMapToolIdentify::identify(e->x(), e->y(), DefaultQgsSetting);
	if(results.isEmpty())
		resultsDialog()->clear();
	else
	{
		for(auto rs=results.begin(); rs!=results.end(); rs++)
			resultsDialog()->addFeature(*rs);

		resultsDialog()->show();
	}
}

void QgsMapToolIdentifyAction::activate()
{
	resultsDialog()->activate();
	QgsMapToolIdentify::activate();
}

void QgsMapToolIdentifyAction::deactivate()
{
	resultsDialog()->deactivate();
	QgsMapToolIdentify::deactivate();
}

QgsIdentifyResultsDialog* QgsMapToolIdentifyAction::resultsDialog()
{
	if(!mResultsDialog)
		mResultsDialog = new QgsIdentifyResultsDialog(mCanvas, mCanvas->window());

	return mResultsDialog;
}