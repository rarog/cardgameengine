
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

#include "WinDialog.h"
#include "ui_WinDialog.h"

WinDialog::WinDialog ( QWidget * parent ) :
    QDialog ( parent ),
    ui ( new Ui::WinDialog )
{
    ui->setupUi ( this );
}

WinDialog::~WinDialog()
{
    delete ui;
}

void WinDialog::changeEvent ( QEvent * e )
{
    QWidget::changeEvent ( e );
    switch ( e->type() )
    {
    case QEvent::LanguageChange:
        ui->retranslateUi ( this );
        break;
    default:
        break;
    }
}

void WinDialog::on__okButton_clicked()
{
    accept();
}
