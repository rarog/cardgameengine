
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

#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QPair>
#include "Cards/Rank.h"
#include "Cards/Suit.h"

class Card : public QObject
{
    Q_OBJECT
    //    Q_ENUMS( Suit )
    //    Q_ENUMS( Rank )
public:

    explicit Card ( CardEnum::Rank  rank, CardEnum::Suit suit, QObject * parent = 0 );

    QString toString() const;
    QString id() const
    {
        return _id;
    }

    CardEnum::Rank rank() const
    {
        return _rank;
    }
    CardEnum::Suit suit() const
    {
        return _suit;
    }


    CardEnum::Rank stringToRank ( QString rank ) const;
    CardEnum::Suit stringToSuit ( QString suit ) const;

    bool sameColor ( QString other ) const;
    bool sameSuit ( QString other ) const;
protected:
    QString _id;
    CardEnum::Rank _rank;
    CardEnum::Suit _suit;
    bool  _upsideDown;
    static QList< QPair< CardEnum::Rank, QString > > _rankNames;
    static QList< QPair< CardEnum::Suit, QString > > _suitNames;

    QString rankToString ( CardEnum::Rank rank ) const;
    QString suitToString ( CardEnum::Suit suit ) const;

    static QList<QPair<CardEnum::Rank, QString> > initRankNames();
    static QList<QPair<CardEnum::Suit, QString> > initSuitNames();

signals:

public slots:

    QString rankName() const;
    QString suitName() const;
    QString nextHigherRank() const;
    QString nextLowerRank() const;
    bool isBlack() const;
    bool isRed() const;
    bool sameColor ( const Card * other ) const;
    bool sameSuit ( const Card * other ) const;

    int compare ( QString rankName ) const;
    bool lessThan ( QString rankName ) const;
    bool greaterThan ( QString rankName ) const;
    bool equalTo ( QString rankName ) const;

    bool isUpsideDown() const
    {
        return _upsideDown;
    }
    bool isHidden() const
    {
        return _upsideDown;
    }

    void show ( bool show = true );
    void hide()
    {
        show ( false );
    }

};

#endif // CARD_H
