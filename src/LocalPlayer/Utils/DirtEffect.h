
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

#ifndef DIRTEFFECT_H
#define DIRTEFFECT_H

#include <QGraphicsEffect>
#include <QPixmap>

class DirtEffect : public QGraphicsEffect
{
    Q_OBJECT
public:
    explicit DirtEffect ( float opacity, QObject * parent = 0 );

protected:
    void draw ( QPainter * painter );
    int _xOffset;
    int _yOffset;
    static QPixmap * _dirtmap;
    float _opacity;
signals:

public slots:

};

#endif // DIRTEFFECT_H
