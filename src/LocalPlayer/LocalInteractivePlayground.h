
/*

Copyright 2011 Claus Ilginnis <Claus@Ilginnis.de>

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.


*/

#ifndef LOCALINTERACTIVEPLAYGROUND_H
#define LOCALINTERACTIVEPLAYGROUND_H

#include "LocalPlayer/LocalPlayground.h"

class QGraphicsSceneMouseEvent;

class LocalInteractivePlayground : public LocalPlayground
{
    Q_OBJECT
public:
    explicit LocalInteractivePlayground ( QObject * parent = 0 );

signals:
    void clickedOnCard ( QString id );
    void doubleClickedOnCard ( QString id );
    void clickedOnStack ( QPoint id );
    void doubleClickedOnStack ( QPoint id );
    void wantsToMoveItem ( QStringList cardId , QString destinationCardId );
    void wantsToMoveItem ( QStringList cardId , QPoint stackCoordinate );

public slots:

protected:
    QPointF _startOfMouseAction;
    bool   _draggingActive;
    QGraphicsItemGroup * _dragGroup;
    QStringList _draggedItems;
    QString _clickId;
    QPoint  _clickStackPos;

    virtual void mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent );
    virtual void mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent );

    void emitMoveEvent ( QStringList sourceId , QPointF destinationPoint );

    bool selectCardItemsByPolicy ( QString dragStartId,  QStringList & draggedItems );
    void addItemsById ( QStringList ids , QGraphicsItemGroup * toGroup );

    QStringList getStackIds ( QPoint pos );
    static bool zLess ( const QPair< QString, double > & s1, const QPair< QString, double > & s2 );

    bool cardIdAt ( QPointF point , QString & idFound ) const;
};

#endif // LOCALINTERACTIVEPLAYGROUND_H
