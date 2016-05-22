
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

#include "CardStack.h"
#include <QDebug>
#include <GameStatus.h>

CardStack::CardStack ( QString name, QObject * parent ) :
    QObject ( parent )
    , _position ( -1, -1 )
    , _orientation ( ToCenter )
    , _selectionMode ( SelectOnlyTop )
    , _name ( name )
{
}

void CardStack::shuffle()
{
    qDebug() << "Shuffling " << _name;
    for ( int i = 0 ; i < 100 ; i++ )
    {
        int index = qrand() % _stack.size();
        Card * card = _stack.at ( index );
        _stack.remove ( index );
        _stack.append ( card );
    }
}

void CardStack::layOnTop ( Card * card )
{
    qDebug() << "Pushed card : " << card->toString() << " To: " << _name;
    _stack.push ( card );
}

Card * CardStack::pop()
{
    Card * card = _stack.pop();
    qDebug() << "Pop card: " << card->toString() << " From: " << _name;
    return card;
}

void CardStack::moveTopCardToStack ( CardStack * otherStack )
{
    otherStack->layOnTop ( pop() );
}

Card * CardStack::top()
{
    return _stack.top();
}

void CardStack::moveAllCardsToStack ( CardStack * otherStack )
{
    otherStack->_stack += _stack;
    _stack.clear();
}

void CardStack::fillGameStatus ( GameStatus * gameStatus ) const
{
    if ( _position.x() < 0 )
    {
        return;
    }
    if ( _position.y() < 0 )
    {
        return;
    }

    gameStatus->_stacksGridPosition.append ( _position );
    for ( int i = 0 ; i < _stack.size() ; i++ )
    {
        Card * card = _stack.at ( i );
        GameStatus::Card sCard;
        sCard._suit = card->isHidden() ? CardEnum::InvalidSuit : card->suit();
        sCard._rank = card->isHidden() ? static_cast<GameStatus::CardRank> ( -1 ) : card->rank();
        sCard._selectionMode = _selectionMode;
        sCard._gridPos = _position;
        sCard._zOrder = i;
        sCard._orientation = static_cast<GameStatus::Orientation> ( _orientation );
        sCard._id = card->id();
        gameStatus->_cards.append ( sCard );
    }
}

int CardStack::indexOfId ( QString id ) const
{
    for ( int i = 0 ; i < _stack.size() ; i++ )
    {
        Card * card = _stack.at ( i );
        if ( card->id() == id )
        {
            return i;
        }
    }
    return -1;
}

bool CardStack::containsId ( QString id ) const
{
    return indexOfId ( id ) != -1;
}

void CardStack::dropCard ( Card * card )
{
    qDebug() << "drop card: " << card->toString() << " From: " << _name;

    int index = indexOfCard ( card );
    if ( index != -1 )
    {
        _stack.remove ( index );
    }
}

int CardStack::indexOfCard ( Card * card )
{
    return _stack.indexOf ( card );
}

void CardStack::insertCard ( int index, Card * card )
{
    _stack.insert ( index, card );
}

bool less ( const Card * a, const Card * b )
{
    if ( a->suit() < b->suit() )
    {
        return true;
    }
    if ( a->suit() > b->suit() )
    {
        return false;
    }
    if ( a->rank() < b->rank() )
    {
        return true;
    }
    if ( a->rank() > b->rank() )
    {
        return false;
    }
    return false ; // equal
}

void CardStack::sort()
{
    qSort ( _stack.begin(), _stack.end(), less );
}

void CardStack::setSelectionMode ( QString mode )
{
    if ( mode == "None"         )
    {
        _selectionMode = SelectNone;
        return ;
    }
    if ( mode == "OnlyTop"      )
    {
        _selectionMode = SelectOnlyTop;
        return ;
    }
    if ( mode == "Single"       )
    {
        _selectionMode = SelectSingle;
        return ;
    }
    if ( mode == "ThisAndAbove" )
    {
        _selectionMode = SelectThisAndAbove;
        return ;
    }
    if ( mode == "ThisAndBelow" )
    {
        _selectionMode = SelectThisAndBelow;
        return ;
    }

    Q_ASSERT ( false );
}

void CardStack::flip()
{
    int count = _stack.size();
    QStack<Card *> temp;
    for ( int i = 0 ; i < count ; i++ )
    {
        Card * card = _stack.at ( 0 );
        _stack.remove ( 0 );
        // Original code indeed flips the cards, but for some unknown reason the cards happen to be already hidden and become visible.
        // This is a workaround to ensure that cards are indeed hidden.
        //card->show ( card->isHidden() );
        card->show ( false );
        temp.insert ( 0, card );
    }
    _stack = temp;
}

