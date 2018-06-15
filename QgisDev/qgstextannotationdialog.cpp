#include "qgstextannotationdialog.h"


QgsTextAnnotationDialog::QgsTextAnnotationDialog(QgsTextAnnotationItem* item, QWidget * parent, Qt::WindowFlags f)
	: QDialog(parent, f)
	, mItem(item)
	, mTextDocument(nullptr)

{
	ui.setupUi(this);

	if(item)
	{
		mTextDocument = item->document();
		ui.textEdit->setDocument(mTextDocument);
	}

	//connect(ui.applyButton, SIGNAL(clicked()), this, SLOT(applyTextToItem()));
	connect(ui.okButton, SIGNAL(clicked()), this, SLOT(saveQuit()));
	connect(ui.deleteButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
}


QgsTextAnnotationDialog::~QgsTextAnnotationDialog(void)
{
	delete mTextDocument;
}

void QgsTextAnnotationDialog::applyTextToItem()
{
	if ( mItem && mTextDocument )
	{
		mItem->setDocument( mTextDocument );
		mItem->update();
	}
}

void QgsTextAnnotationDialog::deleteItem()
{
	QGraphicsScene* scene = mItem->scene();
	if ( scene )
	{
		scene->removeItem( mItem );
	}
	delete mItem;
	mItem = nullptr;	
	QDialog::close();
}

void QgsTextAnnotationDialog::saveQuit()
{
	applyTextToItem();
	QDialog::accept();
}