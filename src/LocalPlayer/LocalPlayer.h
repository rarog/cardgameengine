
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

#ifndef LOCALPLAYER_H
#define LOCALPLAYER_H

#include "Player.h"

class LocalInteractivePlayground;
class QGraphicsView;

class LocalPlayer : public Player
{
    Q_OBJECT
public:
    explicit LocalPlayer ( QGraphicsView * view, QObject * parent = 0 );

    virtual QString getName() const ;
    virtual void displayMessage ( const QString & ) const ;
    virtual void evaluate ( GameStatus * );
    virtual void newPlayground();
    virtual void clearPlayground();
    virtual bool isLocalPlayer() const
    {
        return true;
    }
    virtual void youWin ( bool won );
signals:

public slots:

protected:
    LocalInteractivePlayground * _playground;
    QGraphicsView * _view;
};

#endif // LOCALPLAYER_H
