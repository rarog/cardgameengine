
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

#include "AnimatedGraphicsScene.h"
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QGraphicsItem>


AnimatedGraphicsScene::AnimatedGraphicsScene ( QObject * parent ) :
    QGraphicsScene ( parent )
    , _activeTimeLine ( NULL )
{
}

void AnimatedGraphicsScene::startAnimation()
{
    _activeTimeLine->start();
}

void AnimatedGraphicsScene::addPositionAnimation ( QGraphicsItem * item, QPointF destinationPoint )
{
    item->setPos ( destinationPoint );
    return;
    if ( item->pos() == destinationPoint )
    {
        return ;
    }

    QGraphicsItemAnimation * newAnimation = new QGraphicsItemAnimation ( _activeTimeLine );
    newAnimation->setTimeLine ( _activeTimeLine );
    newAnimation->setItem ( item );
    newAnimation->setPosAt ( 0, item->pos() );
    newAnimation->setPosAt ( 1, destinationPoint );
}

void AnimatedGraphicsScene::prepareAnimation()
{
    if ( _activeTimeLine != NULL )
    {
        delete _activeTimeLine;
    }
    _activeTimeLine = new QTimeLine ( 500 );
}
