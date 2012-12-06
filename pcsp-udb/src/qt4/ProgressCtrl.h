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
#if !defined(PROGRESSCTRL_INCLUDED_)
#define PROGRESSCTRL_INCLUDED_

#include <QDialog>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>

class ProgressCtrl : public QDialog  
{
  Q_OBJECT
public:
  ProgressCtrl(QWidget *parent=0);
  virtual ~ProgressCtrl();

  QLabel *label() const {return nameLabel;}
  QProgressBar *progress() const {return progressBar;}
  QPushButton *stop() const {return stopButton;}
private:
  QPushButton *stopButton;
  QLabel *nameLabel;
  QProgressBar *progressBar;
};

#endif // !defined(PROGRESSCTRL_INCLUDED_)
