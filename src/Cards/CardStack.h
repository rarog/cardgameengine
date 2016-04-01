
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

#ifndef CARDSTACK_H
#define CARDSTACK_H

#include <QObject>
#include <QStack>
#include <QPoint>
#include "Cards/Card.h"
#include "Cards/SelectionMode.h"

class GameStatus;

class CardStack : public QObject
{
    Q_OBJECT
    Q_ENUMS ( Orientation )
public:
    explicit CardStack ( QString name, QObject * parent = 0 );

    enum Orientation
    {
        ToCenter = 0,
        ToLeft ,
        ToBottom
    };

    void fillGameStatus ( GameStatus * gameStatus ) const;
signals:

public slots:
    void shuffle();
    void layOnTop ( Card * card );
    Card * pop( );
    Card * top( );

    void moveTopCardToStack ( CardStack * otherStack );
    void moveAllCardsToStack ( CardStack * otherStack );

    void setPos ( QPoint value )
    {
        _position = value;
    }
    QPoint pos() const
    {
        return _position;
    }
    void setPos ( int x, int y )
    {
        _position = QPoint ( x, y );
    }

    void setOrientation ( Orientation value )
    {
        _orientation = value;
    }
    void setOrientation ( QString orientation )
    {
        if ( orientation == "down" )
        {
            _orientation = ToBottom;
        }
        if ( orientation == "left" )
        {
            _orientation = ToLeft;
        }
    }
    Orientation orientation() const
    {
        return _orientation;
    }

    int indexOfId ( QString id ) const ;
    bool containsId ( QString id ) const ;

    bool isEmpty() const
    {
        return _stack.isEmpty();
    }

    void dropCard ( Card * card );
    int indexOfCard ( Card * card );
    void insertCard ( int index, Card * card );
    void sort();
    void setSelectionMode ( QString mode );
    void flip();
protected:
    QStack<Card *>  _stack;
    QPoint _position;
    Orientation _orientation;
    SelectionMode _selectionMode;
    const QString _name;
};

#endif // CARDSTACK_H
