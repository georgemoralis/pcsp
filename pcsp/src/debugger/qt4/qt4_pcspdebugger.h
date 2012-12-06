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
#ifndef PCSPDEBUGGER_H
#define PCSPDEBUGGER_H

#include <QtCore>
#include <QtGui>

#include "ui_qt4_pcspdebugger.h"

class pcspdebugger : public QMainWindow
{
	Q_OBJECT

public:
	friend class Debugger;

	pcspdebugger(QWidget *parent = 0, Qt::WFlags flags = 0);
	~pcspdebugger();
	Ui::pcspdebuggerClass ui;

private slots:
	void menuLogConfigure();
};

#endif // PCSPDEBUGGER_H