#include "stdafx.h"
#include <QMap>
#include "psplibxmlparser.h"

psplibxmlparser::psplibxmlparser()
{

}

psplibxmlparser::~psplibxmlparser()
{

}
bool psplibxmlparser::readFile(const QString &fileName)
{

    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
       /* std::cerr << "Error: Cannot read file " << qPrintable(fileName)
                  << ": " << qPrintable(file.errorString())
                  << std::endl;*/
        return false;
    }
    reader.setDevice(&file);
	while(!reader.atEnd() && !reader.hasError())
	{
       QXmlStreamReader::TokenType token=reader.readNext();
      	/* If token is just StartDocument, we'll go to next.*/
		if(token == QXmlStreamReader::StartDocument) {
			continue;
		}
		/* If token is StartElement, we'll see if we can read it.*/
		if(token == QXmlStreamReader::StartElement) {
			/* If it's not library, we'll go to the next.*/
			if(reader.name() != "LIBRARY") {
				continue;
			}
			/* If it's named library, we'll dig the information from there.*/
			if(reader.name() == "LIBRARY") {
				readLibElement();
			}
		}
 
	}
	if(reader.hasError()) {
        return false;
	}
	reader.clear();
    return true;
}
void psplibxmlparser::readLibElement()
{
   bool firstname=true;
   QString libname;
   QString flags;
   QString NID;
   QString NIDname;
   bool pairNID=false;
   bool pairNIDname=false;
   reader.readNext();
   while(!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "LIBRARY")) 
   {
		if(reader.tokenType() == QXmlStreamReader::StartElement) 
		{
			/* We've found first name. */
			if(reader.name() == "NAME" && firstname) {
				reader.readNext();
				libname=reader.text().toString();
				if(NIDmap.contains(libname))//hmm we have already read it?
				{
                  continue;
				}
				flags.clear();
				firstname=false;//we have read the lib name , don't continue cause we will read NID names!
			}
			if(reader.name() == "FLAGS")
			{
               reader.readNext();
			   flags=reader.text().toString();
			}
			//if(flags == "0x40010011")
			//{
               if(reader.name() == "NID")
			   {
				  pairNID=true;
                  reader.readNext();
			      NID=reader.text().toString();
				  reader.readNext();
                  
			   }
			   if(reader.name() == "NAME")
			   {
				  pairNIDname=true;
                  reader.readNext();
			      NIDname=reader.text().toString();
				  reader.readNext();
				  
			   }
			   if(pairNID && pairNIDname)
			   {
				 NIDrec record;
				 record.NID=NID;
				 record.function=NIDname;
				 NIDmap.insertMulti(libname,record);
				 pairNID=false;
				 pairNIDname=false;
				 NID.clear();
				 NIDname.clear();
			   }
			//}
		}

        
		/* ...and next... */
		reader.readNext();
   }
}