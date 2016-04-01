
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class CardGame;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow ( QWidget * parent = 0 );
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void gameOver();

    void on_actionAbout_triggered();

    void on_actionQuit_triggered();

    void on_actionOptions_triggered();

    void on_actionFullscreen_triggered();

protected:
    void closeEvent ( QCloseEvent * event );
    void setupEmptyScreen();
private:
    Ui::MainWindow * ui;
    CardGame * _currentGame;
};

#endif // MAINWINDOW_H
