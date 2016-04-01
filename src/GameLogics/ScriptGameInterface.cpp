
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

#include <QScriptEngine>

#include "ScriptGameInterface.h"
#include "CardGame.h"
#include "Player.h"

ScriptGameInterface::ScriptGameInterface ( QScriptEngine * engine, CardGame * game, QObject * parent ) :
    QObject ( parent )
    , _index ( 0 )
    , _round ( 0 )
{
    _game = game;
    _engine = engine;
}

QScriptValue ScriptGameInterface::currentPlayer()
{
    return _player.property ( _index );
}

QScriptValue ScriptGameInterface::player()
{
    return _player;
}

void ScriptGameInterface::nextPlayersTurn()
{
    _index++;
    if ( _index >= _game->players().size() )
    {
        _index = 0;
    }
}

void ScriptGameInterface::initPlayerVariables()
{
    _player = _engine->newObject();
    for ( int i = 0 ; i < _game->players().size() ; i++ )
    {
        QScriptValue playerValue = _engine->newObject();
        playerValue.setProperty ( "name",  _game->players() [i]->getName() );
        playerValue.setProperty ( "id",  _game->players() [i]->id() );
        playerValue.setProperty ( "score", 0 );
        _player.setProperty ( i, playerValue );
    }
}
