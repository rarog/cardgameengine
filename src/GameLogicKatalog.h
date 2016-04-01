
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

#ifndef GAMELOGICKATALOG_H
#define GAMELOGICKATALOG_H

#include <QObject>

class GameLogic;

class GameInformation
{
    QString _name;
    bool _multiplayer;
    int _minPlayer;
    int _maxPlayer;
    virtual GameLogic * newInstance() const = 0;
};

class GameLogicKatalog : public QObject
{
    Q_OBJECT
public:

    explicit GameLogicKatalog ( QObject * parent = 0 );

    void listScriptedGames();

    const QList<GameInformation *> & games() const
    {
        return _games;
    }

protected:
    QList<GameInformation *> _games;
signals:

public slots:

};

#endif // GAMELOGICKATALOG_H
