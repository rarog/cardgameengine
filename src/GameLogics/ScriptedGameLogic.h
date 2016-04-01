
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

#ifndef SCRIPTEDGAMELOGIC_H
#define SCRIPTEDGAMELOGIC_H

#include "GameLogic.h"
#include <QtScript/QScriptEngine>

class ScriptedGameLogic : public GameLogic
{
    Q_OBJECT
public:
    explicit ScriptedGameLogic ( CardGame * parent = 0 );

    virtual void init ( QString fileName );
    virtual void setGame ( CardGame * parent );

    virtual void clickedOnCard (  QString id ) ;
    virtual void doubleClickedOnCard ( QString id ) ;
    virtual void wantsToMoveItem ( QStringList cardId , QString destinationCardId ) ;
    virtual void wantsToMoveItem ( QStringList cardId , QPoint stackCoordinate ) ;
    virtual void clickedOnStack (  QPoint id );
    virtual void doubleClickedOnStack ( QPoint id );
signals:

public slots:
    virtual void gameOverSlot ( QScriptValue winnerId );
protected:
    QScriptEngine _engine;
    QScriptValue callFunction ( QString functionName , QScriptValueList & args );
    inline QScriptValue callFunction ( QString functionName )
    {
        QScriptValueList args;
        return callFunction ( functionName, args );
    }
    QScriptValue cardIdListToScriptValue ( QStringList idList );
    void attachDebugger();
    void addBuiltInObjects();
};

#endif // SCRIPTEDGAMELOGIC_H
