
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

#ifndef SEARCHPATHSETTINGS_H
#define SEARCHPATHSETTINGS_H

#include <QWidget>
#include "Settings/SettingsItem.h"
class QItemSelection;

namespace Ui
{
class SearchPathSettings;
}

class SearchPathSettings : public QWidget, public SettingsItem
{
    Q_OBJECT

public:
    explicit SearchPathSettings ( QString settingsName, QWidget * parent = 0 );
    ~SearchPathSettings();

    virtual void init();
    virtual void saveSettings() const;
protected:
    void changeEvent ( QEvent * e );

private slots:
    void on__newButton_clicked();

    void on__deleteButton_clicked();
    void selectionChanged ( const QItemSelection & selected, const QItemSelection & deselected );
private:
    Ui::SearchPathSettings * ui;
};

#endif // SEARCHPATHSETTINGS_H
