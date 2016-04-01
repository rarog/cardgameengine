
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

#ifndef LOCALPLAYGROUND_H
#define LOCALPLAYGROUND_H

#include <QGraphicsScene>
#include <QMap>
#include "GameStatus.h"
#include "Cards/SelectionMode.h"
#include "LocalPlayer/AnimatedGraphicsScene.h"
#include "LocalPlayer/CardFactory.h"

class QGraphicsItem;
class QGraphicsItemGroup;
class QResizeEvent;

class LocalPlayground : public AnimatedGraphicsScene
{
    Q_OBJECT
public:
    explicit LocalPlayground ( QObject * parent = 0 );

    virtual void evaluate ( GameStatus * );

    struct S_Card
    {
        S_Card()
        {
            _representation = NULL;
            currentSuit = ( GameStatus::CardSuit ) - 1;
            currentRank = ( GameStatus::CardRank ) - 1;
            selectionMode = ( SelectionMode ) - 1;
            stackPos = QPoint ( -5, -5 );
        }

        QGraphicsItem * _representation;
        GameStatus::CardSuit currentSuit;
        GameStatus::CardRank currentRank;
        SelectionMode selectionMode;
        QPoint stackPos;
    };
    QGraphicsItem * loadImage ( GameStatus::CardSuit color, GameStatus::CardRank value );
signals:

public slots:
    void destroy();
protected:
    QMap<QString, S_Card> _cards;
    QSizeF _cardSize;
    GameStatus _lastState;
    CardFactory _cardFactory;
    int _realismLevel;

    QList<QPair<QPoint, QGraphicsItem *> > _stacks;

    void evaluateCards ( GameStatus * status, float padding, QRectF & boundary );
    void evaluateStacks ( GameStatus * status, QRectF & boundary );

    QPointF mapGridToScene ( QPoint gridPos ) const;

    void adjustRect ( QRectF & rect , int factor ) const;
    int gridUp ( int value, int factor ) const;
    int gridDown ( int value, int factor ) const;

    QGraphicsItem * generateGraphicsItem ( GameStatus::CardSuit color, GameStatus::CardRank value, float angle ) ;

    void newCard ( const GameStatus::Card & card , S_Card & cardItem );
    void updateCard ( const GameStatus::Card & card , S_Card & cardItem );
};

#endif // LOCALPLAYGROUND_H
