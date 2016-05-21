
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

#include "Card.h"
#include <QDebug>
#include <QUuid>
#include <QPair>
#include <QVariant>

using namespace CardEnum;

#define APPEND_RANK( VAL ) result.append( qMakePair( CardEnum::VAL ,QString( #VAL ) ) )

QList< QPair< CardEnum::Rank, QString > > Card::initRankNames()
{
    QList< QPair< CardEnum::Rank, QString > > result;
    APPEND_RANK ( Two );
    APPEND_RANK ( Three );
    APPEND_RANK ( Four  );
    APPEND_RANK ( Five  );
    APPEND_RANK ( Six   );
    APPEND_RANK ( Seven );
    APPEND_RANK ( Eight );
    APPEND_RANK ( Nine  );
    APPEND_RANK ( Ten   );
    APPEND_RANK ( Jack  );
    APPEND_RANK ( Queen );
    APPEND_RANK ( King  );
    APPEND_RANK ( Ace   );
    APPEND_RANK ( Joker );

    return result;
}

QList<QPair<CardEnum::Suit, QString> > Card::initSuitNames()
{
    QList<QPair<CardEnum::Suit, QString> > result;

    APPEND_RANK (  Club );
    APPEND_RANK (  Diamond );
    APPEND_RANK (  Heart );
    APPEND_RANK (  Spade );
    APPEND_RANK (  Red );
    APPEND_RANK (  Black );
    return result;
}

QList< QPair< CardEnum::Rank, QString > > Card::_rankNames = initRankNames();
QList< QPair< CardEnum::Suit, QString > > Card::_suitNames = initSuitNames();


Card::Card (    CardEnum::Rank  value, CardEnum::Suit color, QObject * parent ) :
    QObject ( parent )
    , _upsideDown ( true )
{
    _id = QUuid::createUuid().toString();
    _rank = value;
    _suit = color;
#ifndef QT_NO_DEBUG
    _id += toString();
#endif
    //setProperty("name", toString() );
}

void Card::show ( bool show )
{
    if ( show )
    {
        qDebug() << "Showing: " << toString();
    }
    else
    {
        qDebug() << "Hiding: " << toString();
    }

    _upsideDown = !show;
}

QString Card::toString() const
{
    QString result;

    result += suitToString ( _suit );

    result += " ";

    result += rankToString ( _rank );
    return result;
}

QString Card::rankToString ( CardEnum::Rank rank ) const
{
    for ( int i = 0 ; i < _rankNames.size() ; i++ )
    {
        if ( _rankNames[i].first == rank )
        {
            return _rankNames[i].second;
        }
    }
    return "NoValue";
}

QString Card::suitToString ( CardEnum::Suit suit ) const
{
    for ( int i = 0 ; i < _suitNames.size() ; i++ )
    {
        if ( _suitNames[i].first == suit )
        {
            return _suitNames[i].second;
        }
    }
    return "NoValue";
}

CardEnum::Rank Card::stringToRank ( QString  rank ) const
{
    for ( int i = 0 ; i < _rankNames.size() ; i++ )
    {
        if ( _rankNames[i].second == rank )
        {
            return _rankNames[i].first;
        }
    }
    return ( CardEnum::Rank ) - 1;
}

CardEnum::Suit Card::stringToSuit ( QString  suit ) const
{
    for ( int i = 0 ; i < _suitNames.size() ; i++ )
    {
        if ( _suitNames[i].second == suit )
        {
            return _suitNames[i].first;
        }
    }
    return ( CardEnum::Suit ) - 1;
}

QString Card::rankName() const
{
    return rankToString ( _rank );
}

QString Card::suitName() const
{
    return suitToString ( _suit );
}

QString Card::nextHigherRank() const
{
    return rankToString ( static_cast<Rank> ( static_cast<int> ( _rank ) + 1 ) );
}

QString Card::nextLowerRank() const
{
    return rankToString ( static_cast<Rank> ( static_cast<int> ( _rank ) - 1 ) );
}

bool Card::isBlack() const
{
    if ( _suit == Black )
    {
        return true;
    }
    if ( _suit == Spade )
    {
        return true;
    }
    if ( _suit == Club )
    {
        return true;
    }

    return false;
}

bool Card::isRed() const
{
    return ! isBlack();
}

bool Card::sameColor ( const Card * other ) const
{
    return isBlack() == other->isBlack() ;
}

bool Card::sameSuit ( const Card * other ) const
{
    return _suit == other->_suit;
}

bool Card::sameColor ( QString other ) const
{
    Suit otherSuit = stringToSuit ( other );
    if ( isBlack() )
    {
        if ( otherSuit == Spade )
        {
            return true;
        }
        if ( otherSuit == Club )
        {
            return true;
        }
        if ( otherSuit == Black )
        {
            return true;
        }
        return false;
    }
    else
    {
        if ( otherSuit == Diamond )
        {
            return true;
        }
        if ( otherSuit == Heart )
        {
            return true;
        }
        if ( otherSuit == Red )
        {
            return true;
        }
        return false;
    }
}

bool Card::sameSuit ( QString other ) const
{
    return suitToString ( _suit ) == other;
}

int Card::compare ( QString rankName ) const
{
    Rank rank = stringToRank ( rankName );
    if ( rank < _rank )
    {
        return -1;
    }
    if ( rank > _rank )
    {
        return 1;
    }
    return 0;
}

bool Card::lessThan ( QString rankName ) const
{
    return compare ( rankName ) == -1;
}

bool Card::greaterThan ( QString rankName ) const
{
    return compare ( rankName ) == 1;
}

bool Card::equalTo ( QString rankName ) const
{
    return compare ( rankName ) == 0;
}
