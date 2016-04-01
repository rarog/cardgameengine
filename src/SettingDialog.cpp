
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

#include "SettingDialog.h"
#include <QSettings>
#include <QProcess>
#include "ui_SettingDialog.h"
#include "Settings/ImageChooserWidget.h"
#include "Settings/SearchPathSettings.h"

SettingDialog::SettingDialog ( QWidget * parent ) :
    QDialog ( parent ),
    ui ( new Ui::SettingDialog )
{
    QSize defSize = QSize ( 128, 128 );
    ui->setupUi ( this );

    ImageChooserWidget * newTab = new ImageChooserWidget ( defSize, "BackgroundImage", this );
    newTab->addItem ( ":/images/green-felt-texture.jpg", "Felt" );
    newTab->addItem ( ":/images/slate.jpg", "Slate" );
    newTab->addItem ( ":/images/plank-wooden-texture.jpg", "Wood 1" );
    newTab->addItem ( ":/images/woodfloorboard.jpg", "Wood 2" );
    newTab->addItem ( ":/images/tablecloth1.jpg", "Tablecloth 1" );
    newTab->init();

    ui->tabWidget->addTab ( newTab, tr ( "Background" ) );
    _items.append ( newTab );

    newTab = new ImageChooserWidget ( defSize, "Backs", this );

    newTab->addItem ( ":/card_decks/backs/nicubunu_Card_backs_grid_blue.svg", "Grid Blue" );
    newTab->addItem ( ":/card_decks/backs/nicubunu_Card_backs_grid_red.svg", "Grid Red" );
    newTab->addItem ( ":/card_decks/backs/nicubunu_Card_backs_red_cards.svg", "Red Cards" );
    newTab->addItem ( ":/card_decks/backs/nicubunu_Card_backs_simple_blue.svg", "Simple Blue" );
    newTab->addItem ( ":/card_decks/backs/nicubunu_Card_backs_simple_red.svg", "Simple Red" );
    newTab->addItem ( ":/card_decks/backs/nicubunu_Card_backs_suits_blue.svg", "Suits Blue" );
    newTab->addItem ( ":/card_decks/backs/nicubunu_Card_backs_suits_red.svg", "Suits Red" );

    newTab->init();
    ui->tabWidget->addTab ( newTab, tr ( "Backs" ) );
    _items.append ( newTab );

    newTab = new ImageChooserWidget ( defSize, "Decoration", this );

    newTab->addItem ( ":/card_decks/nicubunu_Ornamental_frame.svg", "Standard" );
    newTab->addItem ( ":/card_decks/nicubunu_Ornamental_frame_simple.svg", "simple" );

    newTab->init();
    ui->tabWidget->addTab ( newTab, tr ( "Decoration" ) );
    _items.append ( newTab );

    SearchPathSettings * searchPath = new SearchPathSettings ( "ScriptDirs" );
    searchPath->init();
    _items.append ( searchPath );
    ui->tabWidget->addTab ( searchPath, tr ( "Script Directories" ) );

    QSettings s;
    ui->_userName->setText ( s.value ( "Username", tryGetUsername() ).toString() );

    ui->_realisticSlider->setValue ( s.value ( "Realism", 1 ).toInt() );
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on__cancelButton_clicked()
{
    reject();
}

void SettingDialog::on__okButton_clicked()
{
    QSettings s;
    s.setValue ( "Username", ui->_userName->text() );
    s.setValue ( "Realism", ui->_realisticSlider->value() );
    for ( int i = 0 ; i < _items.size() ; i++ )
    {
        _items.at ( i )->saveSettings();
    }
    accept();
}

QString SettingDialog::tryGetUsername() const
{
    QStringList envs = QProcess::systemEnvironment();
    foreach ( QString env, envs )
    {
        if (  env.contains ( "username", Qt::CaseInsensitive ) )
        {
            QStringList envL = env.split ( "=" );
            if ( envL.size() == 2 )
            {
                return envL[1];
            }
        }
    }
    return "";
}
