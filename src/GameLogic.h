
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

#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QObject>
#include "CardGame.h"

#include <QPoint>
#include <QStringList>

class GameLogic : public QObject
{
    Q_OBJECT
public:
    GameLogic ( CardGame * parent ) : QObject ( parent )
    {
        _game = parent;
    }
    virtual void setGame ( CardGame * parent ) = 0;
    virtual void init ( QString ) = 0;

public slots:
    virtual void clickedOnCard (  QString id ) = 0;
    virtual void doubleClickedOnCard ( QString id ) = 0;
    virtual void clickedOnStack (  QPoint id ) = 0;
    virtual void doubleClickedOnStack ( QPoint id ) = 0;
    virtual void wantsToMoveItem ( QStringList cardId , QString destinationCardId ) = 0;
    virtual void wantsToMoveItem ( QStringList cardId , QPoint stackCoordinate ) = 0;

signals:
    void gameStateChanged();
    void gameOver ( QString winnerId );
protected:
    CardGame * _game;
};


#endif // GAMELOGIC_H
