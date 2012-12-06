#include "stdafx.h"
#include "psplibxmlparser.h"
#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include <QMapIterator>
#include "nidgenerator.h"


NIDgenerator::NIDgenerator(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	version="0.2";
}

NIDgenerator::~NIDgenerator()
{

}
void NIDgenerator::ChooseXML()
{
      QString fileName = QFileDialog::getOpenFileName(this,
                                 tr("Choose a file to open"),
                                 "",
                                 tr("xml Files (*.xml);;xml Files (*.xml)"));


	if(fileName.isEmpty())
		return;
	ReadXML(fileName);
}
int NIDgenerator::ReadXML(QString filename)
{
 
  handler.readFile(filename);
  QMap<QString,NIDrec>::const_iterator iter;
  int count=0;
  QString previouskey;
  for(iter = handler.NIDmap.begin(); iter !=handler.NIDmap.end(); ++iter) 
  {
	  
	  QString lib = iter.key();
	  if(lib != previouskey)
	  {
        QListWidgetItem *libslist =new QListWidgetItem(ui.librariesList );
	    previouskey=lib;
	    libslist->setText(lib);  	  
		ui.librariesList->insertItem(count+1,libslist);
	    count++;
	  }

  }
  return 0;
}
void NIDgenerator::CreateFiles()
{
	QDir dir("");
	if(!dir.exists("modules"))
		dir.mkdir("modules");
	QList<QString> selectedmodulesNames;
    QList<QListWidgetItem *> selected=ui.librariesList->selectedItems();
    QListWidgetItem *item;
	foreach(item,selected)
	{
       QString sel = item->text();
	   WriteModuleFileheader(sel);
	   WriteModuleFile(sel);
	   selectedmodulesNames << sel;
	   WriteSyscallsheader(selectedmodulesNames);
	   WriteNIDmapper(selectedmodulesNames);
	}
}
void NIDgenerator::WriteModuleFileheader(QString modulename)
{
	QFile file("modules/"+modulename +".h");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
     QMap<QString,NIDrec>::const_iterator i = handler.NIDmap.find(modulename);

	   out << "////////////////////////////////////////////////////////////////\n";
       out << "///This file is auto - generated from NIDgenerator version " + version + "\n";
       out << "////////////////////////////////////////////////////////////////\n";
	   out << "#ifndef " + modulename+"_h__\n";
	   out << "#define " + modulename+"_h__\n";
       out << "\n";
	   out << "namespace " + modulename + "\n";
	   out << "{\n";
	   out << "\textern bool Reboot();\n";
	   out << "\textern bool ShutDown();\n";
	   out << "\n";
	 while (i != handler.NIDmap.end() && i.key() == modulename) 
	 {
		   QString nidname = i.value().function;
		   out<<"\textern int " + nidname + "(); \n";
		   i++;
	  }
	 out << "}\n";
	 out << "\n";
	 out << "#endif";
}
void NIDgenerator::WriteModuleFile(QString modulename)
{
	QFile file("modules/"+modulename +".cpp");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
     QMap<QString,NIDrec>::const_iterator i = handler.NIDmap.find(modulename);
	  out << "////////////////////////////////////////////////////////////////\n";
      out << "///This file is auto - generated from NIDgenerator version " + version + "\n";
      out << "////////////////////////////////////////////////////////////////\n";
	 out << "#include \"stdafx.h\"\n";
	 out << "#include \"" + modulename + ".h\"\n";
	 out << "#include \"hle/types.h\"\n";
     out << "#include \"log.h\"\n";
     out << "\n";
     out << "namespace " + modulename +"\n";
     out << "{\n";
	 out << "\tstatic bool "+ modulename +"_ready = false;\n";
	 out << "\n";
	 out << "\tbool Reboot()\n";
	 out << "\t{\n";
	 out << "\t\tShutDown();\n";
	 out << "\t\t"+modulename +"_ready = true;\n";
	 out << "\t\treturn true;\n";
	 out << "\t}\n";
	 out << "\tbool ShutDown()\n";
	 out << "\t{\n";
	 out << "\t\tif (" + modulename + "_ready)\n";
	 out << "\t\t{\n";
	 out << "\t\t\t"+modulename +"_ready = false;\n";
	 out << "\t\t}\n";
	 out << "\t\treturn true;\n";
	 out << "\t}\n";
	 out << "\n";
     while (i != handler.NIDmap.end() && i.key() == modulename) 
	 {
		   QString nidname = i.value().function;
		   out<<"\tint " + nidname + "()\n";
		   out<<"\t{\n";
		   out<<"\t\t//TODO implement me\n";
		   out<<"\t\terrorf("+ modulename + ",\"UNIMPLEMENTED " + nidname + " function\");\n";
		   out<<"\t\treturn 0;\n";
		   out<<"\t}\n";
		   i++;
	  }
	 out << "}\n";
     out << "namespace syscalls\n";
	 out << "{\n";
	 QMap<QString,NIDrec>::const_iterator k = handler.NIDmap.find(modulename);
     while (k != handler.NIDmap.end() && k.key() == modulename) 
	 {
		   QString nidname = k.value().function;
		   out<<"\tvoid " + nidname + "(AlContext &context){ V0 = " + modulename +"::"+nidname+"();};\n";
		   k++;
	  }
	 out << "}\n";
}
void NIDgenerator::WriteSyscallsheader(QList<QString> modules)
{
   
      	QFile file("syscalls.h");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);   
	    out << "////////////////////////////////////////////////////////////////\n";
        out << "///This file is auto - generated from NIDgenerator version " + version + "\n";
        out << "////////////////////////////////////////////////////////////////\n";
		out << "namespace syscalls\n";
        out << "{\n";
        for (int i = 0; i < modules.size(); ++i) 
        {
		   out<<"\n";
		   out<<"\t///////////" + modules.at(i) + "//////////////////////\n";
           QMap<QString,NIDrec>::const_iterator k = handler.NIDmap.find(modules.at(i));
           while (k != handler.NIDmap.end() && k.key() == modules.at(i)) 
	       {
		     QString nidname = k.value().function;
		     out<<"\textern void " + nidname + "(AlContext &context);\n";
		     k++;
	       }
  
        }
		out<<"}\n";
}
void NIDgenerator::WriteNIDmapper(QList<QString> modules)
{
      	QFile file("NIDmap.cpp");
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);   
	    out << "////////////////////////////////////////////////////////////////\n";
        out << "///This file is auto - generated from NIDgenerator version " + version + "\n";
        out << "////////////////////////////////////////////////////////////////\n";
        out << "#include \"stdafx.h\"\n";
		out << "#include \"hle/syscalls.h\"\n";
		out << "\n";
        for (int i = 0; i < modules.size(); ++i) 
        {
		   out << "\tKernelSyscall const " + modules.at(i) + "[] =\n";
	       out << "\t{\n";
           QMap<QString,NIDrec>::const_iterator k = handler.NIDmap.find(modules.at(i));
           while (k != handler.NIDmap.end() && k.key() == modules.at(i)) 
	       {
		     QString nidname = k.value().function;
			 QString NID = k.value().NID;
			 out << "\t\tHLE_FUNC0("+NID+", "+ nidname + "),\n";
		     k++;
	       }
		   out<<"\t};\n";
		   out<<"\n";
  
        }
}