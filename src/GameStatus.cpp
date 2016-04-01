
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

#include "GameStatus.h"

GameStatus::GameStatus ( QObject * parent ) :
    QObject ( parent )
{
}

GameStatus::GameStatus ( const GameStatus & other )
{
    _dimension = other._dimension;
    _cards = other._cards;
    _stacksGridPosition = other._stacksGridPosition;
}

GameStatus & GameStatus::operator = ( const GameStatus & other )
{
    _dimension = other._dimension;
    _cards = other._cards;
    _stacksGridPosition = other._stacksGridPosition;
    return *this;
}
