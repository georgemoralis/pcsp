#ifndef PSPLIBXMLPARSER_H
#define PSPLIBXMLPARSER_H

#include <QXmlDefaultHandler>
	struct NIDrec
    {
      QString function;
	  QString NID;
     };
class psplibxmlparser 
{
public:
	psplibxmlparser();
	~psplibxmlparser();


    QXmlStreamReader reader;
    bool readFile(const QString &fileName);
	void readLibElement();

	QMap<QString,NIDrec> NIDmap;
private:
	QString libname;
	
};

#endif // PSPLIBXMLPARSER_H
