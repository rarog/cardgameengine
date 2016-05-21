
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

#include "LocalInteractivePlayground.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QDebug>

LocalInteractivePlayground::LocalInteractivePlayground ( QObject * parent ) :
    LocalPlayground ( parent )
    , _draggingActive ( false )
    , _dragGroup ( NULL )
{
}

void LocalInteractivePlayground::mousePressEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    QList<QGraphicsItem *> itemsPressed = items ( mouseEvent->scenePos() );

    _clickId = "";
    _startOfMouseAction = QPoint ( -1, -1 );
    _clickStackPos = QPoint ( -1, -1 );

    QString dragStartId;
    cardIdAt ( mouseEvent->scenePos(), dragStartId );

    if ( ( ( mouseEvent->buttons() & Qt::MiddleButton ) != 0 ) && ( dragStartId.isEmpty() == false ) )
    {
        emit doubleClickedOnCard ( dragStartId );
    }

    if ( ( mouseEvent->buttons() & Qt::LeftButton ) == 0 )
    {
        return;
    }

    qDebug() << "mousePressEvent";
    _clickId = dragStartId;

    if ( _clickId.isEmpty() )
    {
        if ( itemsPressed.isEmpty() )
        {
            return;
        }
        if ( itemsPressed[0]->data ( 1 ).isValid() == false )
        {
            return;
        }
        _clickStackPos = itemsPressed[0]->data ( 1 ).toPoint();
    }

    _draggingActive = false;

    if ( selectCardItemsByPolicy ( dragStartId, _draggedItems ) == false )
    {
        return;
    }

    _startOfMouseAction = mouseEvent->scenePos();

    _dragGroup = new QGraphicsItemGroup ( 0 );
    this->addItem( _dragGroup );

    addItemsById ( _draggedItems, _dragGroup );

    _dragGroup->setZValue ( 350 );

}

void LocalInteractivePlayground::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    qDebug() << "mouseMoveEvent";

    QLineF diff = QLineF ( _startOfMouseAction, mouseEvent->scenePos() );
    if ( diff.length() > 3 )
    {
        if ( _dragGroup )
        {
            _draggingActive = true;
            qDebug() << "Started button moving ...";

            _dragGroup->setPos ( diff.dx(), diff.dy() );
        }
    }
}

void LocalInteractivePlayground::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    qDebug() << "mouseReleaseEvent";
    if ( _draggingActive == false )
    {
        qDebug() << "mouseReleaseEvent: Release on item: " << _clickId;
        if ( _dragGroup != NULL )
        {
            destroyItemGroup ( _dragGroup );
            _dragGroup = NULL;
        }

        if ( _clickId.isEmpty() == false )
        {
            emit clickedOnCard ( _clickId );
        }
        else
        {
            emit clickedOnStack ( _clickStackPos );
        }
    }
    if ( _dragGroup != NULL )
    {
        qDebug() << "mouseReleaseEvent: destroying darg group";

        // TODO emit move event
        destroyItemGroup ( _dragGroup );
        _dragGroup = NULL;
    }
    if ( ( _draggingActive == true ) && ( _draggedItems.isEmpty() == false ) )
    {
        emitMoveEvent ( _draggedItems , mouseEvent->scenePos() );
    }
    _draggingActive = false;
}

void LocalInteractivePlayground::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
    QString dragStartId ;

    if ( cardIdAt ( mouseEvent->scenePos(), dragStartId ) )
    {
        emit doubleClickedOnCard ( dragStartId );
    }
}

void LocalInteractivePlayground::emitMoveEvent ( QStringList sourceId, QPointF destinationPoint )
{
    QList<QGraphicsItem *> itemsPressed = items ( destinationPoint );

    // drop on another card ?
    if ( itemsPressed.isEmpty() )
    {
        evaluate ( &_lastState );
    }

    while ( itemsPressed.isEmpty() == false )
    {
        QGraphicsItem * item = itemsPressed[0];
        itemsPressed.removeAt ( 0 );
        if ( item->data ( 0 ).isValid() )
        {
            QString destId = item->data ( 0 ).toString();
            // the dragged item is already here
            if ( sourceId[0] != destId )
            {
                emit wantsToMoveItem ( sourceId, destId );
                return;
            }
        }
        // if the destination is a stack
        if ( item->data ( 1 ).isValid() )
        {
            emit wantsToMoveItem ( sourceId, item->data ( 1 ).toPoint() );
            return;
        }
    }

    evaluate ( &_lastState );
}

bool LocalInteractivePlayground::selectCardItemsByPolicy ( QString dragStartId, QStringList & draggedItems )
{
    if ( dragStartId.isEmpty() )
    {
        return false;
    }

    S_Card card = _cards[ dragStartId ];
    draggedItems.clear();

    QStringList stack = getStackIds ( card.stackPos );
    // index coresponds to the z level
    // the lower it is the farrer/deeper it is away

    switch ( card.selectionMode )
    {
    case SelectNone:
        return false;
    case SelectSingle:
    {
        draggedItems.append ( dragStartId );
        return true;
    }
    case SelectOnlyTop:
    {
        if ( stack.back() == dragStartId )
        {
            draggedItems.append ( dragStartId );
            return true;
        }
        return false;
    }
    case SelectThisAndAbove:
    {
        while ( *stack.begin() != dragStartId )
        {
            stack.removeAt ( 0 );
        }
        draggedItems = stack;
        return true;
    }
    case SelectThisAndBelow:
    {
        while ( stack.back() != dragStartId )
        {
            stack.removeAt ( stack.size() - 1 );
        }
        draggedItems = stack;
        return true;
    }
    default:
        Q_ASSERT ( false );

    } // switch
    return false;
}

void LocalInteractivePlayground::addItemsById ( QStringList ids, QGraphicsItemGroup * toGroup )
{
    for ( int i = 0 ; i < ids.size() ; i++ )
    {
        toGroup->addToGroup ( _cards[ids[i]]._representation );
    }
}

bool LocalInteractivePlayground::zLess ( const QPair< QString, double > & s1, const QPair< QString, double > & s2 )
{
    return s1.second < s2.second;
}


QStringList LocalInteractivePlayground::getStackIds ( QPoint pos )
{
    QStringList allIds = _cards.keys();

    QList< QPair< QString, double > > list;

    for ( int i = 0; i < allIds.size() ; i++ )
    {
        S_Card card = _cards[ allIds[i]];
        if ( card.stackPos == pos )
        {
            list.append ( qMakePair ( allIds[i], card._representation->zValue() ) );
        }
    }
    qSort ( list.begin(), list.end() , zLess );

    QStringList result ;

    for ( int i = 0; i < list.size() ; i++ )
    {
        result.append ( list[i].first );
    }

    return result;
}

bool LocalInteractivePlayground::cardIdAt ( QPointF point, QString & idFound ) const
{
    QList<QGraphicsItem *> itemsPressed = items ( point );

    idFound = "";
    if ( itemsPressed.isEmpty() )
    {
        // never mind
        return false;
    }

    while ( itemsPressed.isEmpty() == false )
    {
        QGraphicsItem * item = itemsPressed.at ( 0 );
        itemsPressed.removeAt ( 0 );
        QString id = item->data ( 0 ).toString();
        if ( id.isEmpty() == false )
        {
            idFound = id;
            return true;
        }
    }

    return false;
}
