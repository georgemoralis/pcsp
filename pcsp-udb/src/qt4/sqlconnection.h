#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"), QMessageBox::Cancel);
        return false;
    }

	QSqlQuery query;
	/*query.exec("create table if not exists games (id INTEGER PRIMARY KEY, "
               "discid varchar(10),"
			   "title varchar(100),"
			   "firmware varchar(5),"
			   "coverfront varchar(30),"
			   "coverback varchar(30),"
			   "previewpic1 varchar(30),"
			   "previewpic2 varchar(30),"
			   "region varchar(10),"
			   "company varchar(100),"
			   "language varchar(256),"
			   "genre varchar(40))");

	//create cache table
	query.exec("create table if not exists cache (id INTEGER PRIMARY KEY, "
		       "path varchar(256),"
			   "lastmodified int ,"
			   "filesize int,"
			   "gameid int,"
			   "crc32 varchar(40),"
			   "gamestatus varchar(100), "
			   "available bool DEFAULT 0)");*/
    query.exec("create table if not exists comp_0_3_0(id INTEGER PRIMARY KEY, "
               "crc32 varchar(40),"
			   "status int,"
               "gamenotes varchar(256))");
	return true;
}

static void convert_old_database()
{
   QSettings loadfromdatabase("data/gamesdatabase.ini", QSettings::IniFormat);
   QStringList keys = loadfromdatabase.childGroups();
   QSqlQuery query;
    for (int i = 0; i < keys.size(); ++i)
	{
		
       QString currectkey=keys.at(i);
	   loadfromdatabase.beginGroup(currectkey);
	   QString discid     = loadfromdatabase.value("id").toString();
       QString title      = loadfromdatabase.value("title").toString();
       QString firmware   = loadfromdatabase.value("firmware").toString();
       QString coverfront = loadfromdatabase.value("coverfront").toString();
       QString coverback  = loadfromdatabase.value("coverback").toString();
       QString preview1   = loadfromdatabase.value("previewpic1").toString();
       QString preview2   = loadfromdatabase.value("previewpic2").toString();
       QString region     = loadfromdatabase.value("region").toString();
       QString language   = loadfromdatabase.value("language").toString();
       QString genre      = loadfromdatabase.value("genre").toString();
       QString company    = loadfromdatabase.value("company").toString();
	   loadfromdatabase.endGroup();
	   query.prepare("INSERT INTO games (discid,title,firmware,coverfront,coverback,previewpic1,previewpic2,region,company,language,genre) "
              "VALUES (?, ?, ?,?,?,?,?,?,?,?,?)");
			  query.addBindValue(discid);
			  query.addBindValue(title);
			  query.addBindValue(firmware);
			  query.addBindValue(coverfront);
			  query.addBindValue(coverback);
			  query.addBindValue(preview1);
			  query.addBindValue(preview2);
			  query.addBindValue(region);
			  query.addBindValue(company);
			  query.addBindValue(language);
			  query.addBindValue(genre);
			  query.exec();
	}
}