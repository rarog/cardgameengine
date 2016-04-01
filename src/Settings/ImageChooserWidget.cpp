
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

#include "ImageChooserWidget.h"
#include <QStandardItem>
#include <QFile>
#include <QImage>
#include <QIcon>
#include <QDebug>
#include <QSettings>

ImageChooserWidget::ImageChooserWidget ( QSize size, QString settingsValue, QWidget * parent ) :
    QListView ( parent )
    , SettingsItem ( settingsValue )
{
    _model = new QStandardItemModel ( this );
    setModel ( _model );

    setIconSize ( size );
}

void ImageChooserWidget::init()
{
    QSettings s;
    QString selectedImage = s.value ( _settingsValue, _model->item ( 0, 0 )->data().toString() ).toString();

    for ( int i = 0 ; i < _model->rowCount() ; i++ )
    {
        if ( _model->item ( i )->data().toString() == selectedImage )
        {
            selectionModel()->select ( _model->index ( i, 0 ), QItemSelectionModel::ClearAndSelect );
            return;
        }
    }
}

void ImageChooserWidget::addItem ( QString fileName, QString title )
{
    if ( QFile::exists ( fileName ) == false )
    {
        qCritical() << "File does not exists: " << fileName;
        return;
    }
    QStandardItem * item = new QStandardItem ( title );

    item->setIcon ( QIcon ( fileName ) );
    item->setData ( fileName );
    _model->appendRow ( item );
    _model->sort ( 0 );
}

void ImageChooserWidget::saveSettings() const
{
    QModelIndexList selection = selectedIndexes();
    if ( selection.isEmpty() )
    {
        return;
    }
    QString selectedImage = selection.at ( 0 ).data ( Qt::UserRole + 1 ).toString();

    QSettings s;
    s.setValue ( _settingsValue , selectedImage );

}
