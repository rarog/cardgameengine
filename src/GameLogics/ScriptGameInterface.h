
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

#ifndef SCRIPTGAMEINTERFACE_H
#define SCRIPTGAMEINTERFACE_H

#include <QObject>
#include <QScriptValue>

class CardGame;
class QScriptEngine;

class ScriptGameInterface : public QObject
{
    Q_OBJECT
public:
    explicit ScriptGameInterface ( QScriptEngine * engine, CardGame * game, QObject * parent = 0 );

    Q_PROPERTY ( int round READ round WRITE setRound )
    Q_PROPERTY ( QScriptValue currentPlayer READ currentPlayer )
    Q_PROPERTY ( QScriptValue player READ player )

    QScriptValue currentPlayer( );
    QScriptValue player( );
    int round() const
    {
        return _round;
    }
    void setRound ( int round )
    {
        _round = round;
    }
    void initPlayerVariables();
protected:
    QScriptValue _player;
    int _index;
signals:
    void gameOver ( QScriptValue winnerId );

public slots:
    void nextPlayersTurn();

private:
    CardGame * _game;
    int        _round;
    QScriptEngine * _engine;
};

#endif // SCRIPTGAMEINTERFACE_H
