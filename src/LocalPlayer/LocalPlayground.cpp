
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

#include "LocalPlayground.h"
#include "GameStatus.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItemGroup>
#include <QGraphicsItem>
#include <QGraphicsSvgItem>
#include <QDebug>
#include <QFile>
#include <QSettings>
#include <QImage>
#include <QBrush>

#include <QPixmap>
#include <QPainter>
#include <QSvgRenderer>

LocalPlayground::LocalPlayground ( QObject * parent ) :
    AnimatedGraphicsScene ( parent )
{
    QSettings s;
    QString imageFileName = s.value ( "BackgroundImage", ":/images/green-felt-texture.jpg" ).toString();

    QImage backgroundImage ( imageFileName );
    QBrush brush ( backgroundImage );

    setBackgroundBrush ( brush );

    _cardSize = QSize ( 140, 190 );

    _realismLevel = s.value ( "Realism", 3 ).toInt();
}

void LocalPlayground::evaluateCards ( GameStatus * status, float padding , QRectF & boundary )
{
    for ( int i = 0 ; i < status->_cards.size() ; i++ )
    {
        const GameStatus::Card card = status->_cards[i];
        S_Card cardItem;

        if ( _cards.contains ( card._id ) == false )
        {
            newCard ( card, cardItem );
        }
        else
        {
            updateCard ( card, cardItem );
        }

        cardItem._representation->setZValue ( card._zOrder );

        QPointF posF = mapGridToScene ( card._gridPos );

        if ( card._orientation == GameStatus::ToBottom )
        {
            posF.setY ( posF.y() + padding * card._zOrder );

        }
        if ( card._orientation == GameStatus::ToLeft )
        {
            posF.setX ( posF.x() +  padding * card._zOrder );
        }

        // set the position and
        //cardItem._representation->setPos( posF );
        addPositionAnimation ( cardItem._representation, posF );
        // store the bounding rect
        QRectF cardBoundingRect =
            cardItem._representation->mapToScene (
                cardItem._representation->boundingRect() ).boundingRect();
        boundary = boundary.united ( cardBoundingRect );
    }

}


void LocalPlayground::evaluateStacks ( GameStatus * status, QRectF & boundary )
{
    for ( int i = 0 ; i < status->_stacksGridPosition.size() ; i++ )
    {
        QPoint p = status->_stacksGridPosition[i];
        bool bFrameExists = false;

        QGraphicsItem * stackRepresentation = NULL;
        for ( int j = 0 ; ( j < _stacks.size() ) && ( bFrameExists == false ) ; j++ )
        {
            if ( _stacks[j].first == p )
            {
                bFrameExists = true;
                stackRepresentation = _stacks[j].second;
            }
        } // search frame
        if ( bFrameExists == false )
        {
            QGraphicsItem * frame = _cardFactory.loadStackMarker();
            //frame = addEllipse(0,0,200,200, QPen(), QBrush(Qt::green));
            frame->setPos ( mapGridToScene ( p ) );
            //frame->setOpacity ( 0.25 );
            frame->setZValue ( -1 );
            frame->setData ( 1, p );
            addItem ( frame );
            //_allGroup->addToGroup( frame );
            _stacks.append ( qMakePair ( p, frame ) );
            stackRepresentation = frame;
        }

        QRectF stackBoundingRect =
            stackRepresentation->mapToScene (
                stackRepresentation->boundingRect() ).boundingRect();
        boundary = boundary.united ( stackBoundingRect );
    }
}

void LocalPlayground::evaluate ( GameStatus * status )
{
    _lastState = *status;
    QRectF boundary ;

    prepareAnimation();
    float pad = _cardSize.width() * 0.3;

    // align stacks and cards
    evaluateStacks ( status, boundary );
    evaluateCards ( status, pad , boundary );

    // add a kind of border
    adjustRect ( boundary, 80 );

    QPointF topLeftCornerOfBottomRightCard ( mapGridToScene ( QPoint ( status->_dimension.width() - 1 , status->_dimension.height() ) ) );
    QRectF defBoundary ( topLeftCornerOfBottomRightCard , _cardSize * 0.5 );
    boundary = boundary.united ( defBoundary );

    QRect a = boundary.toRect();
    QRect b = sceneRect().toRect();

    if ( a == b )
    {
        return;
    }

    setSceneRect ( boundary );

    // update views
    QList<QGraphicsView *> gViews = views();
    for ( int i = 0 ; i < gViews.size() ; i++ )
    {
        gViews.at ( i )->fitInView ( sceneRect(), Qt::KeepAspectRatio );
    }
    startAnimation();
}

QGraphicsItem * LocalPlayground::loadImage ( GameStatus::CardSuit color, GameStatus::CardRank value )
{
    int maxAngle = 30 + 15 * ( _realismLevel - 1 );
    float angle = ( maxAngle / 2 ) - ( qrand() % maxAngle );
    angle /= 10;

    QGraphicsItem * result = _cardFactory.loadCardImage ( color, value );

    result->setRotation ( angle );

    result->setFlag ( QGraphicsItem::ItemIsMovable );
    result->setFlag ( QGraphicsItem::ItemIsSelectable );
    return result;
}

QPointF LocalPlayground::mapGridToScene ( QPoint gridPos ) const
{
    float x = gridPos.x() * _cardSize.width() * 1.2;
    float y = gridPos.y() * _cardSize.height() * 1.2;

    x += 200;
    y += 200;

    return QPointF ( x, y );
}

void LocalPlayground::destroy()
{
    _cards.clear();
    _stacks.clear();
    //    QList<QGraphicsItem *> children=_allGroup->childItems();
    //    for ( int i = 0 ; i < children.size() ; i++ )
    //    {
    //        QGraphicsItem * item = children.at(i);
    //        _allGroup->removeFromGroup( item );
    //        removeItem( item );
    //        delete item;
    //    }
}

void LocalPlayground::adjustRect ( QRectF & rect, int factor ) const
{
    QRect boundary2 = rect.toRect();

    boundary2.setLeft ( gridDown ( boundary2.left(), factor ) );
    boundary2.setRight ( gridUp ( boundary2.right(), factor )   );
    boundary2.setTop ( gridDown ( boundary2.top(), factor )  );
    boundary2.setBottom ( gridUp ( boundary2.bottom(), factor )  );

    rect = boundary2;
}

int LocalPlayground::gridUp ( int value, int factor ) const
{
    int rest = value % factor;
    value += ( factor - rest );
    return value;
}

int LocalPlayground::gridDown ( int value, int factor ) const
{
    int rest = value % factor;
    value -= rest;
    return value;
}

QGraphicsItem * LocalPlayground::generateGraphicsItem ( GameStatus::CardSuit color, GameStatus::CardRank value, float angle )
{

    QGraphicsItem * result ;
    result = _cardFactory.loadCardImage ( color, value );

    result->setRotation ( angle );

    return result;
    /* else
    else
    {
        static QSvgRenderer renderer;
        QPixmap pixmap ( ( 1 * _cardSize ).toSize() );
        pixmap.fill ( Qt::transparent );

        renderer.load ( fileName );

        QPainter painter;

        painter.begin ( ( & pixmap ) );
        painter.setRenderHint ( QPainter::Antialiasing );
        painter.setRenderHint ( QPainter::HighQualityAntialiasing );
        painter.setRenderHint ( QPainter::SmoothPixmapTransform );

        painter.rotate ( angle );

        renderer.render ( &painter, QRectF ( QPoint(), ( 1 * _cardSize ).toSize() ) );

        painter.end();

        QGraphicsPixmapItem * result = new QGraphicsPixmapItem ( pixmap.scaled ( 1 * _cardSize.toSize(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation ) );
        //result->setScale( 0.25 );
        return result;
    }
    */
}

void LocalPlayground::newCard ( const GameStatus::Card & card, LocalPlayground::S_Card & cardItem )
{
    cardItem._representation = loadImage ( card._suit, card._rank );
    cardItem.currentSuit     = card._suit;
    cardItem.currentRank     = card._rank;
    cardItem.selectionMode   = card._selectionMode;
    cardItem.stackPos        = card._gridPos;
    addItem ( cardItem._representation );
    cardItem._representation->setData ( 0, card._id );
    Q_ASSERT ( card._id.isEmpty() == false );

    _cards.insert ( card._id, cardItem );
}

void LocalPlayground::updateCard ( const GameStatus::Card & card, LocalPlayground::S_Card & cardItem )
{
    cardItem = _cards[card._id];

    // need to save new data
    cardItem.stackPos        = card._gridPos;
    cardItem.selectionMode   = card._selectionMode;
    //_cards.insert( card._id, cardItem );

    bool differentColor = cardItem.currentSuit != card._suit ;
    bool differentValue = cardItem.currentRank != card._rank ;

    // react on some kind of show
    if ( differentColor || differentValue )
    {
        removeItem ( cardItem._representation );
        delete cardItem._representation;

        cardItem._representation = loadImage ( card._suit, card._rank );
        cardItem.currentSuit     = card._suit;
        cardItem.currentRank     = card._rank;

        cardItem._representation->setData ( 0, card._id );
        // write back the new value
        addItem ( cardItem._representation );
    }
    _cards.insert ( card._id, cardItem );
}
