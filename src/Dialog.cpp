
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

#include "Dialog.h"
#include "ui_Dialog.h"
#include "CardGame.h"
#include "GameLogics/ScriptedGameLogic.h"
#include "LocalPlayer/LocalPlayer.h"
#include "LocalPlayer/LocalPlayground.h"

Dialog::Dialog ( QWidget * parent ) :
    QDialog ( parent ),
    ui ( new Ui::Dialog )
    , _currentGame ( NULL )
{
    ui->setupUi ( this );
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on__newGameButton_clicked()
{
    if ( _currentGame != NULL )
    {
        _currentGame->end();
        delete _currentGame;
    }

    GameLogic * logic = new ScriptedGameLogic ();
    _currentGame = new CardGame ( logic );

    Player * player = new LocalPlayer ( ui->_playground, _currentGame );

    _currentGame->newPlayer ( player );

    _currentGame->start();
}

void Dialog::on__evaluateButton_clicked()
{
    if ( _currentGame )
    {
        _currentGame->gameStateChanged();
    }
}
