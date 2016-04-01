
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

#ifndef LOCALVIEW_H
#define LOCALVIEW_H

#include <QGraphicsView>

class LocalView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit LocalView ( QWidget * parent = 0 );

protected:
    virtual void resizeEvent ( QResizeEvent * event );
signals:

public slots:

};

#endif // LOCALVIEW_H
