
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

#include "CardsModel.h"
#include "Cards/Card.h"
#include <QDebug>
#include <QStringList>
#include "GameStatus.h"

CardsModel::CardsModel ( QObject * parent ) :
    QObject ( parent )
{
    CardStack * intial = createStack ( "initial" );

    QList<CardEnum::Suit> colorList;
    colorList << CardEnum::Spade << CardEnum::Diamond << CardEnum::Heart << CardEnum::Club;

    QList<CardEnum::Rank> valueList;
    valueList << CardEnum::Two;
    valueList << CardEnum::Three;
    valueList << CardEnum::Four;
    valueList << CardEnum::Five;
    valueList << CardEnum::Six;
    valueList << CardEnum::Seven;
    valueList << CardEnum::Eight;
    valueList << CardEnum::Nine;
    valueList << CardEnum::Ten;
    valueList << CardEnum::Jack;
    valueList << CardEnum::Queen;
    valueList << CardEnum::King;
    valueList << CardEnum::Ace;

    for ( int i = 0 ; i < colorList.size() ; i++ )
    {
        for ( int j = 0 ; j < valueList.size(); j++ )
        {
            Card * card = new Card (  valueList[j], colorList[i], this );
            intial->layOnTop ( card );
            _cards.insert ( card->id(), card );

        }
    }

    createStack ( "unused" );
}

CardStack * CardsModel::createStack ( QString name )
{
    qDebug() << "Creating new Stack: " << name;
    CardStack * newStack = new CardStack ( name, this );
    _stacks.insert ( name, newStack );
    return newStack;
}

CardStack * CardsModel::stack ( QString name )
{
    Q_ASSERT ( _stacks.contains ( name ) );
    return _stacks[name];
}

void CardsModel::moveTopCardFromTo ( QString sourceStack, QString destinationStack )
{
    qDebug() << sourceStack << " --> " << destinationStack;
    stack ( sourceStack )->moveTopCardToStack ( stack ( destinationStack ) );
}

void CardsModel::fillGameStatus ( GameStatus * gameStatus ) const
{
    gameStatus->_dimension = _dimension;
    QList<CardStack *> stacks = _stacks.values();

    for ( int i = 0 ; i < stacks.size() ; i++ )
    {
        stacks[i]->fillGameStatus ( gameStatus );
    }
    testForOrphanedCards();
}

QString CardsModel::stackNameForId ( QString id ) const
{
    Q_ASSERT ( id.isEmpty() == false );
    QStringList stackNames = _stacks.keys();

    for ( int i = 0 ; i < stackNames.size() ; i++ )
    {
        if ( _stacks[stackNames[i]]->containsId ( id ) )
        {
            return stackNames[i];
        }
    }
    Q_ASSERT ( false );
    return "";
}

Card * CardsModel::cardForId ( QString id ) const
{
    return _cards[id];
}

CardStack * CardsModel::stackAtPos ( QPoint point )
{
    QStringList stackNames = _stacks.keys();

    for ( int i = 0 ; i < stackNames.size() ; i++ )
    {
        if ( _stacks[stackNames[i]]->pos() == point )
        {
            return  _stacks[stackNames[i]];
        }
    }
    Q_ASSERT ( false );
    return NULL;
}

QString CardsModel::stackNameAtPos ( QPoint point )
{
    QStringList stackNames = _stacks.keys();

    for ( int i = 0 ; i < stackNames.size() ; i++ )
    {
        if ( _stacks[stackNames[i]]->pos() == point )
        {
            return stackNames[i];
        }
    }
    return "";
}

void CardsModel::testForOrphanedCards() const
{
    QStringList ids = _cards.keys();

    QStringList stackNames = _stacks.keys();

    for ( int i = 0 ; i < ids.size() ; i++ )
    {
        bool bFound = false;
        for ( int j = 0 ; j < stackNames.size() ; j++ )
        {
            if ( _stacks[stackNames[j]]->containsId ( ids[i] ) )
            {
                bFound = true;
            }
        } // for j

        if ( bFound == false )
        {
            qDebug() << "Orphaned card found: " << ids[i];
        }

    } // for j
}
