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

#ifndef __QUMDTABLEMODEL_H__
#define __QUMDTABLEMODEL_H__

#include <QtCore>
#include <QtGui>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "types.h"

#include "../loaders.h"
#include "../umdimageloader.h"
#include "../isodrv.h"
#include "../isolib.h"
#include "psf.h"

class Crc32
{
public:
    Crc32()
    {
        //0x04C11DB7 is the official polynomial used by PKZip, WinZip and Ethernet.
        unsigned int polynomial = 0x04C11DB7;

        // 256 values representing ASCII character codes.
        for (int i = 0; i <= 0xFF; ++i)
        {
            m_table[i] = Reflect(i, 8) << 24;

            for (int j = 0; j < 8; ++j)
            {
                m_table[i] = (m_table[i] << 1) ^ ((m_table[i] & (1 << 31)) ? polynomial : 0);
            }

            m_table[i] = Reflect(m_table[i], 32);
        }
    }

    unsigned int FullCRC(unsigned char const *data, unsigned int length)
    {
        unsigned int crc = 0xffffffff;
        PartialCRC(crc, data, length);
        return crc ^ 0xffffffff;
    }

    unsigned int FullCRC(QFileInfo const &entry)
    {
        unsigned int   crc32;
        unsigned char *data;
        unsigned int   size;

        QFile umdFile(entry.absoluteFilePath());
        umdFile.open(QIODevice::ReadOnly);
        size = (u32)entry.size();
        Crc32 crc;
        crc32 = 0xffffffff;
        u32 offset = 0;
        while (offset + 16*1024*1024 < size)
        {
            data = umdFile.map((quint64)offset, (quint64)16*1024*1024);
            crc.PartialCRC(crc32, data, (quint64)16*1024*1024);
            umdFile.unmap(data);
            size -= 16*1024*1024;
            offset += 16*1024*1024;
        }
        if (size > 0)
        {
            data = umdFile.map(offset, (quint64)size);
            crc.PartialCRC(crc32, data, (quint64)size);
            umdFile.unmap(data);
        }
        crc32 ^= 0xffffffff;
        umdFile.close();
        return crc32;
    }

    void PartialCRC(unsigned int &crc, unsigned char const *data, unsigned int length)
    {
        while (length--)
        {
            crc = (crc >> 8) ^ m_table[((crc) & 0xFF) ^ *data++];
        }
    }

private:
    unsigned int Reflect(unsigned int r, char const c)
    {
        unsigned int result = 0;

        // Swap bit 0 for bit 7, bit 1 For bit 6, etc....
        for (int i = 1; i < (c + 1); ++i)
        {
            if (r & 1)
            {
                result |= (1 << (c - i));
            }
            r >>= 1;
        }

        return result;
    }

    unsigned int m_table[256];
};

class UmdInfos
{
public:
    QString id;
    QString title;
    //QPixmap icon0;
    //QPixmap pic1;
    QString firmware;
    QString status;
    QString coverfront;
    QString coverback;
    QString preview1;
    QString preview2;
    QString region;
    QString language;
    QString genre;
    QString company;
	int     gamestatus;
	QString gamenotes;
    u32     crc32;
	bool     isInDatabase;

    QString icon0() { return (id.size() ? ("data/" + id) : ":/images") + "/icon0.png"; }
    //QString pic1()  { return (id.size() ? ("data/" + id) : ":/images") + "/pic1.png"; }

    QString   absoluteFilePath;
    QString   filename;
    QDateTime lastModified;
    u32       lastModinSec;
    qint64    filesize;
    bool      autorename;
	QString   compDatabaseTable;

    UmdInfos(bool autorename = false)
        :   crc32(0)
		,   gamestatus(0)
		,   isInDatabase(false)
        ,   autorename(autorename)
    {
    }

    bool operator != (QFileInfo const &entry) const
    {
        return absoluteFilePath != entry.absoluteFilePath() || lastModified != entry.lastModified();
    }

    UmdInfos(QFileInfo const &entry,QString compDatabaseName)
        :   crc32(0)
		,   isInDatabase(false)
    {
		compDatabaseTable=compDatabaseName;
		autorename=false;
        *this = entry;
    }

    UmdInfos &operator =(QFileInfo const &entry)
    {
        if (*this != entry)
        {
            absoluteFilePath = entry.absoluteFilePath();
            filename         = entry.fileName();
            lastModified     = entry.lastModified();
            lastModinSec     = lastModified.toTime_t();
            filesize         = entry.size();

            QString filesizetoString;
            filesizetoString.setNum(filesize, 10);
            QString cacheinigroup = filename + "-" + filesizetoString;

            QSettings cacheiniload("cache.dat", QSettings::IniFormat);
            
            // check to see if we have already an entry
            cacheiniload.beginGroup(cacheinigroup);
            if (absoluteFilePath == cacheiniload.value("path")) // there is an entry with the same absolute path
            {
                bool lastmodsame  = (lastModinSec == cacheiniload.value("lastmodified").toUInt());
                bool filesizesame = (filesize == cacheiniload.value("filesize").toULongLong());
                if (lastmodsame && filesizesame)
                {
                    //bingo we have a cache entry!!
                    crc32  = cacheiniload.value("crc32", u32(0)).toUInt();
                    status = cacheiniload.value("gamestatus").toString();
                    QString cached_discid = cacheiniload.value("id").toString();
                    QSettings loadfromdatabase("data/gamesdatabase.ini", QSettings::IniFormat);
                    loadfromdatabase.beginGroup(cached_discid);
                    if (loadfromdatabase.contains("title"))//check if database has the game title (one of the keys)
                    {
                        //it has load all keys and return!
                        id         = loadfromdatabase.value("id").toString();
                        title      = loadfromdatabase.value("title").toString();
                        firmware   = loadfromdatabase.value("firmware").toString();
                        //status   = loadfromdatabase.value("status").toString();
                        coverfront = loadfromdatabase.value("coverfront").toString();
                        coverback  = loadfromdatabase.value("coverback").toString();
                        preview1   = loadfromdatabase.value("previewpic1").toString();
                        preview2   = loadfromdatabase.value("previewpic2").toString();
                        region     = loadfromdatabase.value("region").toString();
                        language   = loadfromdatabase.value("language").toString();
                        genre      = loadfromdatabase.value("genre").toString();
                        company    = loadfromdatabase.value("company").toString();
						if(!genre.startsWith("<unknown>")) //then we have  it on database
                            isInDatabase=true;
						   //load compatibility list from database
					       QSqlQuery query;
					       query.exec("SELECT * FROM '" + compDatabaseTable + "' where crc32 = '" + QString("%1").arg(crc32, 8, 16, QLatin1Char('0 ')).toUpper() + "'");     
                           if(query.first())
	                       {
	    
						     gamestatus= query.value(2).toInt();
	                         gamenotes = query.value(3).toString();
					       }
					       else
					       {
                             gamestatus=0;
						     gamenotes="There aren't any info for the game on compatibility list";
							 query.prepare("INSERT INTO '" + compDatabaseTable + "' (crc32,status,gamenotes) "
                              "VALUES (?,?,?)");
			                 query.addBindValue(QString("%1").arg(crc32, 8, 16, QLatin1Char('0 ')).toUpper());
			                 query.addBindValue(gamestatus);
			                 query.addBindValue(gamenotes);
			                 query.exec();
					       }
                        return *this;
                    }


                }
            }
            int     f;
            u8     *data;
            u32     size;

            crc32 = 0;

            if (entry.exists())
            {
                umdimageloader::reboot(absoluteFilePath.toLatin1().data()); // it sucks ! it cannot handle LATIN1 or UTF8 names !!!

                size = ISOFS_getfilesize("PSP_GAME/PARAM.SFO");
                data = new u8[size];
                f = ISOFS_open("PSP_GAME/PARAM.SFO", 1);
                ISOFS_read(f, (char *)data, size);
                ISOFS_close(f);

                if (size)
                {
                    psf::load_psf(data);


					id       = QString::fromUtf8(psfinfo.disc_id).trimmed();
                    QSettings loadfromdatabase("data/gamesdatabase.ini", QSettings::IniFormat);
                    loadfromdatabase.beginGroup(id);
                    if (loadfromdatabase.contains("title"))
                    {
                        title    = loadfromdatabase.value("title").toString();
                        firmware = loadfromdatabase.value("firmware").toString();
                    }
                    else
                    {
                        title    = QString::fromUtf8(psfinfo.title);
                        firmware = QString::fromUtf8(psfinfo.psp_system_version);
                    }


                    QSettings ini("data/gamesdatabase.ini", QSettings::IniFormat);

                    ini.beginGroup(id);

                    //crc32 = ini.value("crc32", u32(0)).toUInt();

                    if (!crc32)
                    {
                        crc32 = Crc32().FullCRC(entry);

                        if (autorename)
                        {

                            absoluteFilePath = QString("%1/%2 - %3.%4").arg(entry.absolutePath(), id).arg(crc32, 8, 16, QLatin1Char('0')).arg(entry.suffix().toLower());

                            if (entry.absoluteFilePath() != absoluteFilePath)
                            {
                                umdimageloader::shutdown();
                                QFile::rename(entry.absoluteFilePath(), absoluteFilePath); 
                                umdimageloader::reboot(absoluteFilePath.toLatin1().data());
                            }
                        }
                    }
					//load compatibility list from database
					QSqlQuery query;
					query.exec("SELECT * FROM '" + compDatabaseTable + "' where crc32 = '" + QString("%1").arg(crc32, 8, 16, QLatin1Char('0 ')).toUpper() + "'");     
                    if(query.first())
	                {
	    
						   gamestatus= query.value(2).toInt();
	                       gamenotes = query.value(3).toString();
					}
					else
					{
                           gamestatus=0;
						   gamenotes="There aren't any info for the game on compatibility list";
						   query.prepare("INSERT INTO '" + compDatabaseTable + "' (crc32,status,gamenotes) "
                              "VALUES (?,?,?)");
			                 query.addBindValue(QString("%1").arg(crc32, 8, 16, QLatin1Char('0 ')).toUpper());
			                 query.addBindValue(gamestatus);
			                 query.addBindValue(gamenotes);
			                 query.exec();
					}
                    if (loadfromdatabase.contains("title"))
                    {
                        coverfront = loadfromdatabase.value("coverfront").toString();
                        coverback = loadfromdatabase.value("coverback").toString();
                        preview1 =  loadfromdatabase.value("previewpic1").toString();
                        preview2 =loadfromdatabase.value("previewpic2").toString();
                        region =loadfromdatabase.value("region").toString();
                        language =loadfromdatabase.value("language").toString();
                        genre =loadfromdatabase.value("genre").toString();
                        company =loadfromdatabase.value("company").toString();
						if(!genre.startsWith("<unknown>")) //then we have  it on database
							isInDatabase=true;
                    }
                    else
                    {
                        ini.setValue("id",          id);
                        ini.setValue("title",       title);
                        ini.setValue("firmware",    firmware);
                        ini.setValue("coverfront",  id + "-front.jpg");
                        ini.setValue("coverback",   id + "-back.jpg");
                        ini.setValue("previewpic1", id + "-preview1.jpg");
                        ini.setValue("previewpic2", id + "-preview2.jpg");
						
						isInDatabase=false;
                        
                        if (id.startsWith("ULJM"))
                        {
                            ini.setValue("region", "Japan");
                            ini.setValue("company", "<unknown>");
							ini.setValue("language", "Japanese");
                        }
						else if(id.startsWith("UCJS"))
						{
				            ini.setValue("region", "Japan");
                            ini.setValue("company", "Sony");
                            ini.setValue("language", "Japanese");
						}
                        else if (id.startsWith("UCES"))
                        {
                            ini.setValue("region", "Europe");
                            ini.setValue("company", "Sony");
                            ini.setValue("language", "<unknown>");
                        }
                        else if (id.startsWith("ULES"))
                        {
                            ini.setValue("region", "Europe");
                            ini.setValue("company", "<unknown>");
                            ini.setValue("language", "<unknown>");
                        }
                        else if (id.startsWith("ULUS"))
                        {
                            ini.setValue("region", "USA");
                            ini.setValue("company", "<unknown>");
                            ini.setValue("language", "English");
                        }
						else if(id.startsWith("NPUG"))
						{
                            ini.setValue("region", "USA");
                            ini.setValue("company", "Sony");
                            ini.setValue("language", "English");
						}
						else if(id.startsWith("UCUS"))
						{
                            ini.setValue("region", "USA");
                            ini.setValue("company", "Sony");
                            ini.setValue("language", "English");
						}
						else if(id.startsWith("NPUH"))
						{
                            ini.setValue("region", "USA");
                            ini.setValue("company", "<unknown>");
                            ini.setValue("language", "English");
						}
						else if(id.startsWith("ULAS"))
						{
                            ini.setValue("region", "China");
                            ini.setValue("company", "<unknown>");
                            ini.setValue("language", "<unknown>");
						}
						else if(id.startsWith("NPHG"))
						{
                             ini.setValue("region", "China");
                             ini.setValue("company", "Sony");
                             ini.setValue("language", "<unknown>");
						}
						else if(id.startsWith("UCAS"))
						{
                            ini.setValue("region", "China");
                            ini.setValue("company", "Sony");
                            ini.setValue("language", "<unknown>");
						}
						else if(id.startsWith("UCKS"))
						{
                             ini.setValue("region", "Korea");
                             ini.setValue("company", "Sony");
                             ini.setValue("language", "<unknown>");
						}
						else if(id.startsWith("ULKS"))
						{
                             ini.setValue("region", "Korea");
                             ini.setValue("company", "<unknown>");
                             ini.setValue("language", "<unknown>");
						}
						else if(id.startsWith("ULJS"))
						{
                             ini.setValue("region", "Japan");
							 ini.setValue("company", "<unknown>");
                             ini.setValue("language", "Japanese");
						}
						else if(id.startsWith("NPJG"))
						{
							ini.setValue("region", "Japan");
							ini.setValue("company", "Sony");
                            ini.setValue("language", "Japanese");
						}
						else if(id.startsWith("UCET"))						
						{
							ini.setValue("region", "Europe");
							ini.setValue("company", "Sony");
							ini.setValue("language", "<unknown>");
						}
						else if(id.startsWith("NPEZ"))
						{
							ini.setValue("region", "Europe");
							ini.setValue("company", "Sony");
							ini.setValue("language", "<unknown>");
						}
						else if(id.startsWith("NPUX"))
						{
							ini.setValue("region", "USA");
							ini.setValue("company", "Sony");
							ini.setValue("language", "English");
						}
						else
                        {
                            ini.setValue("region", "<unknown>");
							ini.setValue("company", "<unknown>");
                            ini.setValue("language", "<unknown>");
                        }
                    	ini.setValue("genre", "<unknown>");
                    
						region   = ini.value("region").toString();
                        language = ini.value("language").toString();
                        genre    = ini.value("genre").toString();
                        company  = ini.value("company").toString();
                    }
                    QDir().mkpath("data/" + id);

                    QPixmap icon0File(144, 80);
                    QString icon0FileName(icon0());
                    if (QFile::exists(icon0FileName))
                    {
                        icon0File.load(icon0FileName);
                    }
                    else
                    {
                        size = ISOFS_getfilesize("PSP_GAME/ICON0.PNG");
                        if (size)
                        {
                            data = new u8[size];
                            f = ISOFS_open("PSP_GAME/ICON0.PNG", 1);
                            ISOFS_read(f, (char *)data, size);
                            ISOFS_close(f);

                            icon0File.loadFromData(data, size);
                        }
                        else
                        {
                            data = 0;
                            icon0File.load(":/images/icon0.png");
                        }

                        icon0File.save(icon0FileName);

                        delete data;
                    }

                    int header;

                    status.clear();

                    size = ISOFS_getfilesize("PSP_GAME/SYSDIR/BOOT.BIN");
                    if (size)
                    {
                        int header;
                        f = ISOFS_open("PSP_GAME/SYSDIR/BOOT.BIN", 1);
                        ISOFS_read(f, (char *)&header, sizeof(int));
                        ISOFS_close(f);

                        switch (header)
                        {
                        case 0x464C457F: status = "Plain BOOT.BIN"; break;
                        case 0x5053507E: status = "Encrypted BOOT.BIN (PSP~)"; break;
                        case 0x4543537E: status = "Encrypted BOOT.BIN (~SCE)"; break;
                        case 0x00000000: break;
                        default:         status = "Unsupported BOOT.BIN"; break;
                        }
                    }

                    if (!status.size())
                    {
                        size = ISOFS_getfilesize("PSP_GAME/SYSDIR/EBOOT.BIN");
                        f = ISOFS_open("PSP_GAME/SYSDIR/EBOOT.BIN", 1);
                        ISOFS_read(f, (char *)&header, sizeof(int));
                        ISOFS_close(f);

                        switch (header)
                        {
                        case 0x464C457F: status = "Plain EBOOT.BIN"; break;
                        case 0x5053507E: status = "Encrypted EBOOT.BIN (PSP~)"; break;
                        case 0x4543537E: status = "Encrypted EBOOT.BIN (~SCE)"; break;
                        default:         status = "Unsupported EBOOT.BIN"; break;
                        }
                    }

                    //create an entry for the cachefile
                    QSettings cacheini("cache.dat", QSettings::IniFormat);
                    //check to see if we have already an entry
                    cacheini.beginGroup(cacheinigroup);
                    QString game_exists = cacheini.value("path","").toString();
                    if(game_exists.isEmpty())//not a record
                    {                     
                        cacheini.setValue("path",         absoluteFilePath);
                        cacheini.setValue("lastmodified", lastModinSec);
                        cacheini.setValue("filesize",     filesize);
                        cacheini.setValue("id",           id);
                        cacheini.setValue("crc32",        crc32);
                        cacheini.setValue("gamestatus",   status);

                    }
                    if (status.size())
                    {
                        // ini.setValue("status", status);
                        return *this;
                    }
                    ini.endGroup();
                    ini.remove(id);
                    cacheini.endGroup();
                    cacheini.remove(cacheinigroup);

                    umdimageloader::shutdown();

                }
                title    = "";
                id       = "";
                firmware = "";
                status   = "";
                crc32    = 0;
                region   = "";
                language = "";
                genre    = "";
                company  = "";
            }
        }

        return *this;
    }
};

/**
* @author hlide
*/
class QUmdTableModel : public QAbstractTableModel
{
    Q_OBJECT

        typedef QAbstractTableModel Base;

public:
    QUmdTableModel(QString const &path, QObject *parent = 0)
        :   Base(parent)
    {
    }
    void startupdatemodel()
	{
      beginResetModel();
	}
	void endupdatemodel()
	{
       endResetModel();
	}
   /* void updateModel(QString const &path, bool autorename)
    {
        QPixmap pixmap(":/images/pcsp.png");
        QSplashScreen s(pixmap);
        s.show();

        m_infos.clear();
        beginResetModel();
        QDir dir(path);
        QListIterator< QFileInfo > entry(dir.entryInfoList(QStringList() << "*.ISO" << "*.CSO", QDir::Files, QDir::Name|QDir::IgnoreCase));
        if (entry.hasNext())
        {
            while (entry.hasNext())
            {
                QFileInfo fi = entry.next();
                s.showMessage(tr("Loading %1...").arg(fi.baseName()));
                UmdInfos infos(fi, autorename);
                m_infos.push_back(infos);
                if (!m_infos.last().id.size())
                {
                    m_infos.removeLast();
                }
            }
        }
        endResetModel();

    }*/

    virtual int columnCount(QModelIndex const &parent = QModelIndex()) const
    {
        return 6;
    }

    virtual int rowCount(QModelIndex const &parent = QModelIndex()) const
    {
        return m_infos.count();
    }

    virtual bool hasChildren(QModelIndex const &parent = QModelIndex()) const
    {
        if (parent.isValid())
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    QVariant data(const QModelIndex &index, int role) const
    {
        int row = index.row();

        if (index.isValid())
        {
            UmdInfos &infos = m_infos[row];

            if (role == Qt::UserRole)
            {
                return infos.absoluteFilePath;
            }
            if(role == Qt::UserRole+1)
            {
                return infos.icon0();
            }

            if(role == Qt::UserRole+2)
            {
                return "data/" + infos.id + "/" + infos.coverfront;
            }
            if(role == Qt::UserRole+3)
            {
                return "data/" + infos.id + "/" + infos.coverback;
            }
            if(role == Qt::UserRole+4)
            {
                return "data/" + infos.id + "/" + infos.preview1;
            }
            if(role == Qt::UserRole+5)
            {
                return "data/" + infos.id + "/" + infos.preview2;
            }
			if(role == Qt::UserRole+6)
			{
               return infos.language;
			}
			if(role ==Qt::UserRole+7)
			{
               return infos.genre;
			}
			if(role ==Qt::UserRole+8)
			{
               return QString("%1").arg(infos.crc32, 8, 16, QLatin1Char('0 ')).toUpper();
			}
			if(role ==Qt::UserRole+9)
			{
              return infos.status;
			}
			if(role ==Qt::UserRole+10)
			{
              return infos.filesize;
			}
			if(role==Qt::UserRole+11)
			{
				return infos.gamenotes;
			}
			if(role==Qt::UserRole+12)//hmm probably can be done better but i am lazy :P
			{
				return infos.gamestatus;
			}
            /*if (role == Qt::TextAlignmentRole) 
            {
            if(index.column() == 0) {
            return (QVariant) ( Qt::AlignLeft);
            } else {
            return (QVariant) ( Qt::AlignRight | Qt::AlignVCenter);
            }
            }*/
            switch (index.column())
            {
            case 0: return (role == Qt::DisplayRole || role == Qt::EditRole) ? infos.title                                                        : QVariant();
            case 1: return (role == Qt::DisplayRole || role == Qt::EditRole) ? infos.id                                                           : QVariant();
            case 2: return (role == Qt::DisplayRole || role == Qt::EditRole) ? infos.region                                                       : (role == Qt::DecorationRole) ? QIcon(":/flags/" + infos.region + ".png") : QVariant();
            case 3: return (role == Qt::DisplayRole || role == Qt::EditRole) ? infos.firmware                                                     : QVariant();
            case 4: return (role == Qt::DisplayRole || role == Qt::EditRole) ? infos.company                                                      : QVariant();
			case 5: return (role == Qt::DisplayRole || role == Qt::EditRole) ? infos.gamestatus                                                   : QVariant();
            
			}
        }




        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const
    {
        if (role == Qt::DisplayRole || role == Qt::EditRole)
        {
            switch (section)
            {
            case 0: return "Title";
            case 1: return "Disc ID";
            case 2: return "Region";
            case 3: return "FW";
            case 4: return "Company";
			case 5: return "GameStatus";
            }
        }

        return QVariant();
    }
	bool setData(const QModelIndex &index,const QVariant &value, int role)
	{
       int row = index.row();
       if(index.isValid()) 
	   {
          UmdInfos &infos = m_infos[row];
		  infos.gamestatus = value.toInt();
		  emit dataChanged(index, index);
          return true;
	   }
	   return false;
	}

public:
    mutable QList< UmdInfos > m_infos;
};

#endif
