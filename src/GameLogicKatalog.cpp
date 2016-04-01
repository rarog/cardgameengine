
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

#include "GameLogicKatalog.h"
#include <QStringList>
#include <QSettings>

GameLogicKatalog::GameLogicKatalog ( QObject * parent ) :
    QObject ( parent )
{
}

void GameLogicKatalog::listScriptedGames()
{
    QStringList value;
    QSettings s;
    QVariant v = s.value ( "ScriptDirs" );
    if ( v.isValid() && v.canConvert ( QVariant::StringList ) )
    {
        value = v.toStringList();
    }
    else
    {
        value << ":/ScriptedGames";
    }

    foreach ( QString dir, value )
    {

    }

}
