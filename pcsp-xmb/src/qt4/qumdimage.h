#ifndef QUMDIMAGE_H
#define QUMDIMAGE_H

#include <QtCore>

class QUmdImage : public QFile
{
    Q_OBJECT

public:
    QUmdImage(QObject *parent);
    ~QUmdImage();

private:

};

#endif // QUMDIMAGE_H
