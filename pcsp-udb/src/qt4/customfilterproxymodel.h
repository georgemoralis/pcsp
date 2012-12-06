
#include <QSortFilterProxyModel>


class customFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    customFilterProxyModel(QObject *parent = 0);
    void setGenericFilter(int filter);
	void setGameFilter(QString gfilter);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
	int genericfilter;
	QString gamefilter;

};


