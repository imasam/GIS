#include "qgisdev.h"
#include <QtGui/QApplication>

#include <qgsapplication.h>

int main(int argc, char *argv[])
{
	// Qsetting
	// WFS WCS WMS
	QCoreApplication::setOrganizationName( "myName" );
	//QCoreApplication::setOrganizationDomain( "xxx.com" ); 
	QCoreApplication::setApplicationName( "QGisDev" );
	
	QgsApplication a( argc, argv, true );  
	QgsApplication::setPrefixPath( "D:/QGIS 2.18", true );  
	//QString pluginPath = QgsApplication::pluginPath(); 
	QgsApplication::initQgis();
	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

	QgisDev* w = new QgisDev();
	w->show();

	int ret = a.exec();
	delete w;
	return ret;
}
