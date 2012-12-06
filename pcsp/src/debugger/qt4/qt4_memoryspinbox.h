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
#ifndef QT4_MEMORYSPINBOX_H_
#define QT4_MEMORYSPINBOX_H_

#include <QtGui/QSpinBox>
#include <QtGui/QRegExpValidator>

class qt4_MemorySpinBox : public QSpinBox
{
    Q_OBJECT

public:
    qt4_MemorySpinBox(QWidget *parent = 0);
    ~qt4_MemorySpinBox();

    QValidator::State validate(QString &input, int &pos) const;

protected:
    QString textFromValue(int value) const;
    int valueFromText(const QString &text) const;

private:
    QRegExpValidator *m_validator;
};

#endif /* Qt4_MEMORYSPINBOX_H_ */
