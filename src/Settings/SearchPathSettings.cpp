
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

#include "SearchPathSettings.h"
#include "ui_SearchPathSettings.h"
#include <QFileDialog>
#include <QSettings>
#include <QDir>

SearchPathSettings::SearchPathSettings ( QString settingsName, QWidget * parent ) :
    QWidget ( parent ),
    SettingsItem ( settingsName ),
    ui ( new Ui::SearchPathSettings )
{
    ui->setupUi ( this );
    bool bOk = connect (
                   ui->_dirListWidget->selectionModel(),
                   SIGNAL ( selectionChanged ( QItemSelection, QItemSelection ) ),
                   this, SLOT ( selectionChanged ( QItemSelection, QItemSelection ) ) );
    Q_ASSERT ( bOk );
}

SearchPathSettings::~SearchPathSettings()
{
    delete ui;
}

void SearchPathSettings::changeEvent ( QEvent * e )
{
    QWidget::changeEvent ( e );
    switch ( e->type() )
    {
    case QEvent::LanguageChange:
        ui->retranslateUi ( this );
        break;
    default:
        break;
    }
}

void SearchPathSettings::on__newButton_clicked()
{
    QString newDir = QFileDialog::getExistingDirectory ( this, "Select a new directory" );
    if ( newDir.isEmpty() == false )
    {
        ui->_dirListWidget->addItem ( newDir );
    }
    ui->_dirListWidget->sortItems();
}

void SearchPathSettings::on__deleteButton_clicked()
{
    QModelIndexList selection = ui->_dirListWidget->selectionModel()->selectedRows();
    if ( selection.isEmpty() )
    {
        ui->_deleteButton->setEnabled ( false );
        return;
    }
    for ( int i = 0 ; i < selection.size() ; i++ )
    {
        ui->_dirListWidget->takeItem ( selection.at ( i ).row() );
    }
}

void SearchPathSettings::selectionChanged ( const QItemSelection & selected, const QItemSelection &  )
{
    ui->_deleteButton->setEnabled ( selected.isEmpty() == false );
}

void SearchPathSettings::init()
{
    QStringList value;
    QSettings s;
    QVariant v = s.value ( _settingsValue );
    if ( v.isValid() && v.canConvert ( QVariant::StringList ) )
    {
        value = v.toStringList();
    }
    else
    {
        value << ":/ScriptedGames";
        value << QDir::cleanPath ( QDir::homePath() + "/.CardGameScripts" );
    }
    for ( int i = 0 ; i < value.size() ; i++ )
    {
        ui->_dirListWidget->addItem ( value[i] );
    }
}

void SearchPathSettings::saveSettings() const
{
    QStringList value;
    QSettings s;

    for ( int i = 0 ; i < ui->_dirListWidget->count() ; i++ )
    {
        value << ui->_dirListWidget->item ( i )->text();
    }
}
