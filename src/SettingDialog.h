
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

#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "Settings/SettingsItem.h"

namespace Ui
{
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog ( QWidget * parent = 0 );
    ~SettingDialog();

private slots:
    void on__cancelButton_clicked();

    void on__okButton_clicked();

protected:
    QString tryGetUsername() const;
private:
    Ui::SettingDialog * ui;
    QList<SettingsItem *> _items;
};

#endif // SETTINGDIALOG_H
