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
#ifndef QPcspXmb_H
#define QPcspXmb_H

#include <QtCore>
#include <QtGui>

#include "ui_qpcspxmb.h"

#include "qumdmodel.h"

class QPcspXmb : public QMainWindow, private Ui::PcspXmbUi
{
    Q_OBJECT

public:
    QPcspXmb(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~QPcspXmb();
    void refresh();

protected:
    QRegion visualRegionForSelection(QItemSelection const &) const { return QRegion(); }

private slots:
    void onChangeUmdPath();
    void onAutoRenameToggled(bool checked);
    void onModelReset();
    void onCurrentChanged(QModelIndex const &index);
    void onDoubleClicked(QModelIndex const &index);
    void onPressedButton();

private:
    QString              m_umdisospath;
    QUmdTableModel      *m_model;
    QDataWidgetMapper   *m_mapper;
    QItemSelectionModel *m_selectionModel;
    QSystemTrayIcon     *m_systray;
    QSettings            m_ini;
};

#endif // QPcspXmb_H
