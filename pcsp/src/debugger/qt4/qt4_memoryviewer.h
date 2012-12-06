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
#ifndef QT4_MEMORYVIEWER_H
#define QT4_MEMORYVIEWER_H

#include <QtGui/QWidget>
#include "ui_qt4_memoryviewer.h"

class qt4_MemoryViewer : public QWidget
{
    Q_OBJECT

public:
    qt4_MemoryViewer(QWidget *parent = 0);
    ~qt4_MemoryViewer();

public slots:
    void updateMemoryViewer();

private:
    Ui::memoryform ui;
};

#endif // QT4_MEMORYVIEWER_H