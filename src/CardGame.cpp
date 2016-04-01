
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

#include "CardGame.h"
#include <QDebug>
#include "GameLogic.h"
#include "Cards/CardsModel.h"
#include "GameStatus.h"
#include "Player.h"

CardGame::CardGame ( GameLogic * logic, QObject * parent ) :
    QObject ( parent )
    , _logic ( logic )
{
    _logic->setGame ( this );
    bool bOk;
    bOk = connect ( _logic, SIGNAL ( gameStateChanged() ), this, SLOT ( gameStateChanged() )  );
    Q_ASSERT ( bOk );
    bOk = connect ( _logic, SIGNAL ( gameOver ( QString ) ), this, SLOT ( gameOver ( QString ) )  );
    Q_ASSERT ( bOk );
    _cards = new CardsModel();

}

void CardGame::start()
{
    _logic->init ( ":/ScriptedGames/solitaire.script" );

    for ( int i = 0 ; i < _players.size() ; i++ )
    {
        Player * player = _players[i];
        bool bOk;
        bOk = connect ( player, SIGNAL ( clickedOnCard ( QString ) ), _logic, SLOT ( clickedOnCard ( QString ) ) );
        Q_ASSERT ( bOk );
        bOk = connect ( player, SIGNAL ( doubleClickedOnCard ( QString ) ), _logic, SLOT ( doubleClickedOnCard ( QString ) ) );
        Q_ASSERT ( bOk );
        bOk = connect ( player, SIGNAL ( clickedOnStack ( QPoint ) ), _logic, SLOT ( clickedOnStack ( QPoint ) ) );
        Q_ASSERT ( bOk );
        bOk = connect ( player, SIGNAL ( doubleClickedOnStack ( QPoint ) ), _logic, SLOT ( doubleClickedOnStack ( QPoint ) ) );
        Q_ASSERT ( bOk );
        bOk = connect ( player, SIGNAL ( wantsToMoveItem ( QStringList, QPoint ) ), _logic, SLOT ( wantsToMoveItem ( QStringList, QPoint ) ) );
        Q_ASSERT ( bOk );
        bOk = connect ( player, SIGNAL ( wantsToMoveItem ( QStringList, QString ) ), _logic, SLOT ( wantsToMoveItem ( QStringList, QString ) ) );
        Q_ASSERT ( bOk );
    }

    gameStateChanged();
}

void CardGame::newPlayer ( Player * newPlayer )
{
    _players.append ( newPlayer );
}

void CardGame::end()
{
    for ( int i = 0 ; i < _players.size() ; i++ )
    {
        _players[i]->clearPlayground();
    }
}

void CardGame::gameStateChanged()
{
    qDebug() << "Gamestate changed evaluating";
    GameStatus gs;
    _cards->fillGameStatus ( &gs );
    _lastState = gs;

    for ( int i = 0 ; i < _players.size() ; i++ )
    {
        _players[i]->evaluate ( &gs );
    }
}

void CardGame::gameOver ( QString winnerId )
{
    for ( int i = 0 ; i < _players.size() ; i++ )
    {
        Player * player = _players[i];
        player->youWin ( player->id() == winnerId );
    }
    emit gameOver();
}
