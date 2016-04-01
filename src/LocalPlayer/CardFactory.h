
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

#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include <QObject>
#include <QSvgRenderer>
#include <QMap>
#include "Cards/Rank.h"
#include "Cards/Suit.h"

class QGraphicsItem;

class CardFactory : public QObject
{
    Q_OBJECT
public:
    explicit CardFactory ( QObject * parent = 0 );

    QGraphicsItem * loadStackMarker();
    QGraphicsItem * loadCardImage ( CardEnum::Suit color, CardEnum::Rank value );
signals:

public slots:

protected:
    QMap<QString, QSvgRenderer *> _renderer;
    int _realismLevel;

    QString cardFileName ( CardEnum::Suit color, CardEnum::Rank value ) const;
    //void postProcess( QGraphicsItem )
};

#endif // CARDFACTORY_H
