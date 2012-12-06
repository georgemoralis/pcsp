
#include <QtGui>

#include "customfilterproxymodel.h"


customFilterProxyModel::customFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}
void customFilterProxyModel::setGenericFilter(int filter)
{
  genericfilter=filter;
  invalidateFilter();
}
void customFilterProxyModel::setGameFilter(QString gfilter)
{
  gamefilter=gfilter;
  invalidateFilter();
}
bool customFilterProxyModel::filterAcceptsRow(int sourceRow,
        const QModelIndex &sourceParent) const
{
    QModelIndex title    = sourceModel()->index(sourceRow, 0, sourceParent);
    QModelIndex discid   = sourceModel()->index(sourceRow, 1, sourceParent);
    QModelIndex region   = sourceModel()->index(sourceRow, 2, sourceParent);
    QModelIndex fw       = sourceModel()->index(sourceRow, 3, sourceParent);
	QModelIndex company  = sourceModel()->index(sourceRow, 4, sourceParent);
	QModelIndex gamecomp = sourceModel()->index(sourceRow, 5, sourceParent);

    if(genericfilter==0)
	{
	  if(gamefilter=="10")
	  {
        return (sourceModel()->data(title).toString().contains(filterRegExp())
			 || sourceModel()->data(discid).toString().contains(filterRegExp())
			 || sourceModel()->data(region).toString().contains(filterRegExp())
			 || sourceModel()->data(fw).toString().contains(filterRegExp())
			 || sourceModel()->data(company).toString().contains(filterRegExp()));
	  }
	  else
	  {
        return (sourceModel()->data(title).toString().contains(filterRegExp())
			 || sourceModel()->data(discid).toString().contains(filterRegExp())
			 || sourceModel()->data(region).toString().contains(filterRegExp())
			 || sourceModel()->data(fw).toString().contains(filterRegExp())
			 || sourceModel()->data(company).toString().contains(filterRegExp()))
			 && sourceModel()->data(gamecomp).toString().contains(gamefilter);
	  }
	}
    if(genericfilter==1)
	{
	  if(gamefilter=="10")
	  {
        return (sourceModel()->data(title).toString().contains(filterRegExp()));
	  }
	  else
	  {
        return (sourceModel()->data(title).toString().contains(filterRegExp()))
			 && sourceModel()->data(gamecomp).toString().contains(gamefilter);
	  }
	}
    if(genericfilter==2)
	{
	  if(gamefilter=="10")
	  {
        return (sourceModel()->data(discid).toString().contains(filterRegExp()));
	  }
	  else
	  {
        return (sourceModel()->data(discid).toString().contains(filterRegExp()))
			 && sourceModel()->data(gamecomp).toString().contains(gamefilter);
	  }
	}
    if(genericfilter==3)
	{
	  if(gamefilter=="10")
	  {
        return (sourceModel()->data(region).toString().contains(filterRegExp()));
	  }
	  else
	  {
        return (sourceModel()->data(region).toString().contains(filterRegExp()))
			 && sourceModel()->data(gamecomp).toString().contains(gamefilter);
	  }
	}
    if(genericfilter==4)
	{
	  if(gamefilter=="10")
	  {
        return (sourceModel()->data(fw).toString().contains(filterRegExp()));
	  }
	  else
	  {
        return (sourceModel()->data(fw).toString().contains(filterRegExp()))
			 && sourceModel()->data(gamecomp).toString().contains(gamefilter);
	  }
	}
    if(genericfilter==5)
	{
	  if(gamefilter=="10")
	  {
        return (sourceModel()->data(company).toString().contains(filterRegExp()));
	  }
	  else
	  {
        return (sourceModel()->data(company).toString().contains(filterRegExp()))
			 && sourceModel()->data(gamecomp).toString().contains(gamefilter);
	  }
	}   

	return true;
}


