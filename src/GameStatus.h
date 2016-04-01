
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

#ifndef GAMESTATUS_H
#define GAMESTATUS_H

#include <QObject>
#include <QSize>
#include <QPoint>

#include "Cards/Rank.h"
#include "Cards/Suit.h"
#include "Cards/SelectionMode.h"

class GameStatus : public QObject
{
    Q_OBJECT
public:

    enum Orientation
    {
        ToCenter = 0,
        ToLeft ,
        ToBottom
    };

    typedef CardEnum::Suit CardSuit;
    typedef CardEnum::Rank CardRank;

    explicit GameStatus ( QObject * parent = 0 );
    GameStatus ( const GameStatus & other );

    GameStatus & operator= ( const GameStatus & other );

    struct Card
    {
        QString   _id;
        QPoint _gridPos;
        int    _zOrder;
        CardSuit _suit;
        CardRank _rank;
        Orientation _orientation;
        SelectionMode _selectionMode;
    };

    QSize _dimension;
    QList<Card> _cards;
    QList<QPoint> _stacksGridPosition;

};

#endif // GAMESTATUS_H
