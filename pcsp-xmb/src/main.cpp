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

#include <QtCore>
#include <QtGui>
#include "qpcspxmb.h"

void center(QWidget &widget)
{
    int x, y;
    int screenWidth;
    int screenHeight;
    int width, height;
    QSize windowSize;

    QDesktopWidget *desktop = QApplication::desktop();

    width = widget.frameGeometry().width();
    height = widget.frameGeometry().height();  

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;

    widget.move( x, y );
}

QString findDirectory()
{
    //TODO Create umdfolder if not exist
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
    QString directory = QFileDialog::getExistingDirectory(0, "Select UMD images folder", ".", options);

    return directory;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(qpcspxmb);

    QPcspXmb w(0, 0);
    //center(w); // [hlide] wrong way to center a window in multi-display
    w.show();

    return a.exec();
}
