
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

#include "DirtEffect.h"
#include <QBitmap>
#include <QPainter>

QPixmap * DirtEffect::_dirtmap = NULL;

DirtEffect::DirtEffect ( float opacity, QObject * parent ) :
    QGraphicsEffect ( parent )
    , _xOffset ( 0 )
    , _yOffset ( 0 )
{
    _opacity = opacity;
    if ( _dirtmap == NULL )
    {
        _dirtmap = new QPixmap ( ":/images/dirt.png" );
    }
}

void DirtEffect::draw ( QPainter * painter )
{
    QBitmap bitmap;
    QPoint offset;
    QSize size;
    if ( sourceIsPixmap() )
    {
        // No point in drawing in device coordinates (pixmap will be scaled anyways).
        const QPixmap pixmap = sourcePixmap ( Qt::LogicalCoordinates, &offset );
        size = pixmap.size();
        bitmap = pixmap.createHeuristicMask();
        painter->drawPixmap ( offset, pixmap );
    }
    else
    {
        // Draw pixmap in device coordinates to avoid pixmap scaling;
        const QPixmap pixmap = sourcePixmap ( Qt::DeviceCoordinates, &offset );
        size = pixmap.size();
        painter->setWorldTransform ( QTransform() );
        bitmap = pixmap.createHeuristicMask();
        painter->drawPixmap ( offset, pixmap );
    }

    painter->setOpacity ( _opacity );

    QPixmap intermediate = _dirtmap->copy ( 0, 0, bitmap.size().width(), bitmap.size().height() );
    intermediate.setMask ( bitmap );

    //    QImage i = intermediate.toImage();
    //    i.save("C:/mask.png");

    painter->drawPixmap ( QRect ( offset, size ), intermediate );
}
