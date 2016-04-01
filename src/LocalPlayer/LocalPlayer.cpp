
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

#include "LocalPlayer.h"
#include <QMessageBox>
#include <QGraphicsView>
#include "LocalPlayer/LocalInteractivePlayground.h"
#include "Utils/WinDialog.h"

LocalPlayer::LocalPlayer ( QGraphicsView * view, QObject * parent ) :
    Player ( parent )
    , _playground ( NULL )
    , _view ( view )
{
    view->setRenderHint ( QPainter::Antialiasing );
    view->setRenderHint ( QPainter::HighQualityAntialiasing );
    view->setRenderHint ( QPainter::SmoothPixmapTransform );

    newPlayground();
}

QString LocalPlayer::getName() const
{
    return "LocalUser";
}

void LocalPlayer::displayMessage ( const QString & message ) const
{
    QMessageBox::information ( 0, "Information", message );
}

void LocalPlayer::evaluate ( GameStatus * status )
{
    _playground->evaluate ( status );
}

void LocalPlayer::clearPlayground()
{
    _playground->destroy();
}

void LocalPlayer::newPlayground()
{
    _playground = new LocalInteractivePlayground ( this );
    _view->setScene ( _playground );

    bool bOk;
    bOk = connect ( _playground, SIGNAL ( clickedOnCard ( QString ) ), this, SIGNAL ( clickedOnCard ( QString ) ) );
    Q_ASSERT ( bOk );
    bOk = connect ( _playground, SIGNAL ( doubleClickedOnCard ( QString ) ), this, SIGNAL ( doubleClickedOnCard ( QString ) ) );
    Q_ASSERT ( bOk );
    bOk = connect ( _playground, SIGNAL ( clickedOnStack ( QPoint ) ), this, SIGNAL ( clickedOnStack ( QPoint ) ) );
    Q_ASSERT ( bOk );
    bOk = connect ( _playground, SIGNAL ( doubleClickedOnStack ( QPoint ) ), this, SIGNAL ( doubleClickedOnStack ( QPoint ) ) );
    Q_ASSERT ( bOk );
    bOk = connect ( _playground, SIGNAL ( wantsToMoveItem ( QStringList, QPoint ) ), this, SIGNAL ( wantsToMoveItem ( QStringList, QPoint ) ) );
    Q_ASSERT ( bOk );
    bOk = connect ( _playground, SIGNAL ( wantsToMoveItem ( QStringList, QString ) ), this, SIGNAL ( wantsToMoveItem ( QStringList, QString ) ) );
    Q_ASSERT ( bOk );
}

void LocalPlayer::youWin ( bool won )
{
    if ( won )
    {
        WinDialog dlg ( _view );
        dlg.exec();

    }
    else
    {
        displayMessage ( "You loose. Sorry." );
    }

}
