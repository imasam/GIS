#pragma once	// 解决"PCH 警告:标头停止点不能位于宏或#if块中"
#ifndef QGSMAPTOOLANNOTATION_H
#define QGSMAPTOOLANNOTATION_H

#include <qgsmaptool.h>
#include <qgsannotationitem.h>

class QgsMapToolAnnotation: public QgsMapTool
{
    Q_OBJECT

  public:
    QgsMapToolAnnotation( QgsMapCanvas* canvas );
    ~QgsMapToolAnnotation();

    void canvasPressEvent( QgsMapMouseEvent* e ) override;
    void canvasReleaseEvent( QgsMapMouseEvent* e ) override;
    void canvasMoveEvent( QgsMapMouseEvent* e ) override;
    void canvasDoubleClickEvent( QgsMapMouseEvent* e ) override;
    void keyPressEvent( QKeyEvent* e ) override;

  protected:
    /** Creates a new item. To be implemented by subclasses. Returns 0 by default*/
    virtual QgsAnnotationItem* createItem( QMouseEvent* e );
    /** Creates an editor widget (caller takes ownership)*/
    QDialog* createItemEditor( QgsAnnotationItem* item );

  private:
    /** Returns the topmost annotation item at the position (or 0 if none)*/
    QgsAnnotationItem* itemAtPos( QPointF pos );
    QgsAnnotationItem* selectedItem();
    /** Returns a list of all annotationitems in the canvas*/
    QList<QgsAnnotationItem*> annotationItems();
    /** Switches visibility states of text items*/
    void toggleTextItemVisibilities();

    QgsAnnotationItem::MouseMoveAction mCurrentMoveAction;
    QPointF mLastMousePosition;
};

#endif // QGSMAPTOOLANNOTATION_H
