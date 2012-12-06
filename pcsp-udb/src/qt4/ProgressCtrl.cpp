/*
This file is part of pcsp.

pcsp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

pcsp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with pcsp.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ProgressCtrl.h"
#include <QtGui>

ProgressCtrl::ProgressCtrl(QWidget *parent)
: QDialog(parent)
{
  progressBar = new QProgressBar;
  nameLabel = new QLabel ("Name");

  stopButton = new QPushButton("&Cancel");

  QHBoxLayout *buttonLayout = new QHBoxLayout;
  buttonLayout->addStretch(1);
  buttonLayout->addWidget(stopButton);

  QVBoxLayout *vbox = new QVBoxLayout;
  vbox->addWidget(nameLabel);
  vbox->addWidget(progressBar);
  vbox->addLayout(buttonLayout);
  setLayout(vbox);
  this->setMinimumWidth(333);
}

ProgressCtrl::~ProgressCtrl()
{
}
