
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

#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QPoint>
#include <QUuid>
#include <QStringList>

class GameStatus;

class Player : public QObject
{
    Q_OBJECT
public:
    Player ( QObject * parent ) ;
    virtual QString getName() const = 0 ;
    virtual void displayMessage ( const QString & ) const = 0;
    virtual void evaluate ( GameStatus * ) = 0;
    virtual void newPlayground() = 0 ;
    virtual void clearPlayground() = 0;
    virtual QString id() const
    {
        return _id;
    }
    virtual bool isLocalPlayer() const = 0;
    virtual void youWin ( bool won ) = 0;
signals:
    void clickedOnCard (  QString id );
    void doubleClickedOnCard ( QString id );
    void clickedOnStack (  QPoint id );
    void doubleClickedOnStack ( QPoint id );
    void wantsToMoveItem ( QStringList cardId , QString destinationCardId );
    void wantsToMoveItem ( QStringList cardId , QPoint stackCoordinate );
protected:
    const QString _id;
};

#endif // PLAYER_H
