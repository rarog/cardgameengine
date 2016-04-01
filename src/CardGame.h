
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

#ifndef CARDGAME_H
#define CARDGAME_H

#include <QObject>
#include "GameStatus.h"

class GameLogic;
class Player;
class CardsModel;

class CardGame : public QObject
{
    Q_OBJECT
public:
    explicit CardGame ( GameLogic * logic, QObject * parent = 0 );
    GameStatus & lastState()
    {
        return _lastState;
    }
signals:
    void waitingForPlayers();
    void playersPresent();
    void beginningGame();
    void gameOver();
public slots:
    void start();
    void newPlayer ( Player * newPlayer );
    void gameOver ( QString winnerId );
    void end();
    CardsModel & cards()
    {
        return *_cards;
    }
    void gameStateChanged();
    QList<Player *> & players()
    {
        return _players;
    }
protected:
    GameLogic * _logic;
    QList<Player *> _players;
    CardsModel * _cards;
    GameStatus _lastState;
};

#endif // CARDGAME_H
