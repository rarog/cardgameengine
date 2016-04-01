
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

#include "CardFactory.h"
#include <QGraphicsSvgItem>
#include <QSettings>
#include <QGraphicsColorizeEffect>
#include "LocalPlayer/Utils/DirtEffect.h"

CardFactory::CardFactory ( QObject * parent ) :
    QObject ( parent )
{
    QSettings s;
    _realismLevel = s.value ( "Realism", 3 ).toInt();

    QString stackMarker = s.value ( "Stack", ":/card_decks/backs/nicubunu_Card_backs_frame.svg" ).toString();
    _renderer["Stack"] = new QSvgRenderer ( stackMarker , this );

    QString backSide = s.value ( "Backs", ":/card_decks/backs/nicubunu_Card_backs_red_cards.svg" ).toString();
    _renderer["Back"] = new QSvgRenderer ( backSide , this );
    _renderer["Decoration"] = new QSvgRenderer ( s.value ( "Decoration",  ":/card_decks/nicubunu_Ornamental_frame.svg" ).toString() , this );
}

QGraphicsItem * CardFactory::loadStackMarker()
{
    QGraphicsSvgItem * result = new QGraphicsSvgItem();

    result->setSharedRenderer ( _renderer["Stack"] );

    QGraphicsColorizeEffect * newEffect = new QGraphicsColorizeEffect();
    newEffect->setColor ( QColor ( 128 + ( 20 * _realismLevel ), 128 + ( 20 * _realismLevel ), 128 ) );
    result->setGraphicsEffect ( newEffect );

    return result;
}

QGraphicsItem * CardFactory::loadCardImage ( CardEnum::Suit color, CardEnum::Rank value )
{
    QGraphicsSvgItem * result;
    if ( color == CardEnum::InvalidSuit )
    {
        result = new QGraphicsSvgItem();

        result->setSharedRenderer ( _renderer["Back"] );
    }
    else
    {
        result = new QGraphicsSvgItem();

        result->setSharedRenderer ( _renderer["Decoration"] );
        QString fileName = this->cardFileName ( color, value );

        new QGraphicsSvgItem ( fileName, result );
    }

    //    QGraphicsColorizeEffect * newEffect = new QGraphicsColorizeEffect();
    //    newEffect->setColor( QColor(200,200,0 ));
    //    newEffect->setStrength( (_realismLevel-1)* 0.125 );
    //    result->setGraphicsEffect( newEffect );

    if ( _realismLevel > 1 )
    {
        DirtEffect * newEffect = new DirtEffect ( 0.1 * _realismLevel );
        result->setGraphicsEffect ( newEffect );
    }

    return result;
}

QString CardFactory::cardFileName ( CardEnum::Suit color, CardEnum::Rank value ) const
{
    if ( color == CardEnum::InvalidSuit )
    {
        return ":/card_decks/backs/nicubunu_Card_backs_red_cards.svg";
    }
    if ( value == CardEnum::InvalidRank )
    {
        return ":/card_decks/backs/nicubunu_Card_backs_red_cards.svg";
    }

    QString result = ":/card_decks/nicubunu_Ornamental_deck_";
    switch ( value )
    {
    case CardEnum::Two :
        result += "2";
        break;
    case CardEnum::Three:
        result += "3";
        break;
    case CardEnum::Four:
        result += "4";
        break;
    case CardEnum::Five:
        result += "5";
        break;
    case CardEnum::Six:
        result += "6";
        break;
    case CardEnum::Seven:
        result += "7";
        break;
    case CardEnum::Eight:
        result += "8";
        break;
    case CardEnum::Nine:
        result += "9";
        break;
    case CardEnum::Ten:
        result += "10";
        break;
    case CardEnum::Jack:
        result += "Jack";
        break;
    case CardEnum::Queen:
        result += "Queen";
        break;
    case CardEnum::King:
        result += "King";
        break;
    case CardEnum::Ace:
        result += "Ace";
        break;
    case CardEnum::Joker:
        result += "Joker";
        break;
    default:
        Q_ASSERT ( false );
    };
    result += "_of_";
    switch ( color )
    {
    case CardEnum::Club:
        result += "clubs";
        break;
    case CardEnum::Diamond:
        result += "diamonds";
        break;
    case CardEnum::Heart:
        result += "hearts";
        break;
    case CardEnum::Spade:
        result += "spades";
        break;
    case CardEnum::Red:
        result += "red";
        break;
    case CardEnum::Black:
        result += "black";
        break;
    default:
        Q_ASSERT ( false );
    };

    result += ".svg";
    return result;
}
