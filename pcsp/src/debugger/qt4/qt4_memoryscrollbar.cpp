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
#include "stdafx.h"
#include "qt4_memoryscrollbar.h"

qt4_MemoryScrollbar::qt4_MemoryScrollbar(QWidget *parent)
	: QScrollBar(parent)
{

}
qt4_MemoryScrollbar::qt4_MemoryScrollbar(Qt::Orientation orientation, QWidget *parent)
   : QScrollBar(orientation, parent)
{

}
qt4_MemoryScrollbar::~qt4_MemoryScrollbar()
{

}
void qt4_MemoryScrollbar::changeRange(int min, int max)
{
  QScrollBar::setRange(min, max);
}