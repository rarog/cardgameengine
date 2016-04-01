
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

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QSettings>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QCloseEvent>
#include "CardGame.h"
#include "AboutDialog.h"
#include "GameLogics/ScriptedGameLogic.h"
#include "LocalPlayer/LocalPlayer.h"
#include "LocalPlayer/LocalPlayground.h"
#include "SettingDialog.h"

MainWindow::MainWindow ( QWidget * parent ) :
    QMainWindow ( parent ),
    ui ( new Ui::MainWindow )
    , _currentGame ( NULL )
{
    ui->setupUi ( this );

    setupEmptyScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    if ( _currentGame != NULL )
    {
        _currentGame->end();
        delete _currentGame;
    }

    GameLogic * logic = new ScriptedGameLogic ( );
    _currentGame = new CardGame ( logic );

    bool bOk = connect ( _currentGame, SIGNAL ( gameOver() ), this, SLOT ( gameOver() ) );
    Q_ASSERT ( bOk );

    Player * player = new LocalPlayer ( ui->graphicsView, _currentGame );

    _currentGame->newPlayer ( player );

    _currentGame->start();
}

void MainWindow::gameOver()
{
    _currentGame->deleteLater();
    _currentGame = NULL;
    setupEmptyScreen();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dlg;
    dlg.exec();
}

void MainWindow::on_actionQuit_triggered()
{
    close();
}

void MainWindow::closeEvent ( QCloseEvent * event )
{
    if ( _currentGame != NULL )
    {
        int answer = QMessageBox::question (
                         this,
                         tr ( "Quit" ) ,
                         tr ( "A game is still in progress, do you real want to quit?" ),
                         QMessageBox::Yes | QMessageBox::No,
                         QMessageBox::No );
        if ( answer == QMessageBox::No )
        {
            event->ignore();
            return;
        }
        gameOver();
    }
    event->accept();
}

void MainWindow::on_actionOptions_triggered()
{
    SettingDialog dlg ( this );
    if ( dlg.exec() == QDialog::Accepted )
    {
        setupEmptyScreen();
        if ( _currentGame == NULL )
        {
            return;
        }
        foreach ( Player * player , _currentGame->players() )
        {
            if ( player->isLocalPlayer() )
            {
                player->clearPlayground();
                player->newPlayground();
                player->evaluate ( & _currentGame->lastState() );
            }
        }
    }
}

void MainWindow::setupEmptyScreen()
{
    QSettings s;

    QString imageFileName = s.value ( "BackgroundImage", ":/images/green-felt-texture.jpg" ).toString();

    QImage backgroundImage ( imageFileName );
    QBrush brush ( backgroundImage );

    QGraphicsScene * scene = new QGraphicsScene ( this );
    ui->graphicsView->setScene ( scene );
    scene->setBackgroundBrush ( brush );

    scene->setSceneRect ( 0, 0, 500, 500 );
}

void MainWindow::on_actionFullscreen_triggered()
{
    if ( isFullScreen() )
    {
        showNormal();
        ui->actionFullscreen->setChecked ( false );
    }
    else
    {
        showFullScreen();
        ui->actionFullscreen->setChecked ( true );
    }
}
