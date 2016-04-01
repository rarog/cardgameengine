
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

#ifndef CARDSMODEL_H
#define CARDSMODEL_H

#include <QObject>
#include <QMap>
#include <QSize>
#include "Cards/CardStack.h"

class GameStatus;

class CardsModel : public QObject
{
    Q_OBJECT
public:
    explicit CardsModel ( QObject * parent = 0 );

    void fillGameStatus ( GameStatus * gameStatus ) const;

    QString stackNameForId ( QString id ) const;
    Card * cardForId ( QString id ) const;
    CardStack * stackAtPos ( QPoint point );
    QString stackNameAtPos ( QPoint point );
    void testForOrphanedCards() const;
signals:

public slots:
    CardStack * createStack ( QString name );
    CardStack * stack ( QString name );
    void moveTopCardFromTo ( QString sourceStack, QString destinationStack ) ;
    void setSize ( QSize size )
    {
        _dimension = size;
    }
    void setSize ( int width, int height )
    {
        _dimension = QSize ( width, height );
    }
protected:
    QMap<QString, CardStack *> _stacks;
    QSize _dimension;
    QMap<QString, Card *> _cards;
};

#endif // CARDSMODEL_H
