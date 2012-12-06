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

#include "types.h"

#include "../loaders.h"
#include "../UmdImageLoader.h"
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
    u32     crc32;

    QString icon0() { return (id.size() ? ("data/" + id) : ":/images") + "/icon0.png"; }
    QString pic1()  { return (id.size() ? ("data/" + id) : ":/images") + "/pic1.png"; }

    QString   absoluteFilePath;
    QDateTime lastModified;
    bool      autorename;

    UmdInfos(bool autorename = false)
    :   crc32(0)
    ,   autorename(autorename)
    {
    }

    bool operator != (QFileInfo const &entry) const
    {
        return absoluteFilePath != entry.absoluteFilePath() || lastModified != entry.lastModified();
    }

    UmdInfos(QFileInfo const &entry, bool autorename = false)
    :   crc32(0)
    ,   autorename(autorename)
    {
        *this = entry;
    }

    UmdInfos &operator =(QFileInfo const &entry)
    {
        if (*this != entry)
        {
            absoluteFilePath = entry.absoluteFilePath();
            lastModified     = entry.lastModified();

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

                    title    = QString::fromUtf8(psfinfo.title);
                    id       = QString::fromUtf8(psfinfo.disc_id);
                    firmware = QString::fromUtf8(psfinfo.psp_system_version);

                    QSettings ini("data/games.ini", QSettings::IniFormat);

                    ini.beginGroup(id);
                    
                    crc32 = ini.value("/umd/crc32", u32(0)).toUInt();

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

                    //QStringList values = entry.baseName().split(" - ");
                    //if (!crc32 && (values.size() == 2) && values.takeFirst() == id)
                    //{
                    //    bool ok = false;
                    //    int result = values.takeFirst().toInt(&ok, 16);
                    //    if (ok)
                    //    {
                    //        crc32 = result;
                    //    }
                    //}

                    ini.setValue("/umd/path", absoluteFilePath);
                    ini.setValue("/umd/id", id);
                    ini.setValue("/umd/title", title);
                    ini.setValue("/umd/firmware", firmware);
                    ini.setValue("/umd/crc32", crc32);

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

                    QPixmap pic1File(480, 272);
                    QString pic1FileName(pic1());
                    if (QFile::exists(pic1FileName))
                    {
                        pic1File.load(pic1FileName);
                    }
                    else
                    {
                        size = ISOFS_getfilesize("PSP_GAME/PIC1.PNG");
                        if (size)
                        {
                            data = new u8[size];
                            f = ISOFS_open("PSP_GAME/PIC1.PNG", 1);
                            ISOFS_read(f, (char *)data, size);
                            ISOFS_close(f);

                            pic1File.loadFromData(data, size);
                        }
                        else
                        {
                            data = 0;
                            pic1File.load(":/images/pic1.png");
                            //pic1File = icon0File.scaledToWidth(72,Qt::SmoothTransformation);
                            //pic1File = pic1File.scaledToWidth(144,Qt::SmoothTransformation);
                            //pic1File = pic1File.scaledToWidth(288,Qt::SmoothTransformation);
                            //pic1File = pic1File.scaledToWidth(480,Qt::SmoothTransformation);
                        }

                        pic1File.save(pic1FileName);

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

                    if (status.size())
                    {
                        ini.setValue("/umd/status", status);
                        return *this;
                    }
                    ini.endGroup();
                    ini.remove(id);

                    umdimageloader::shutdown();
                }
                title    = "";
                id       = "";
                firmware = "";
                status   = "";
                crc32    = 0;
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

    void updateModel(QString const &path, bool autorename)
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
    }

    virtual int columnCount(QModelIndex const &parent = QModelIndex()) const
    {
        return 7;
    }

    virtual int rowCount(QModelIndex const &parent = QModelIndex()) const
    {
        return m_infos.count();
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

            switch (index.column())
            {
            case 0: return (role == Qt::DecorationRole                     ) ? QPixmap(infos.icon0())                                             : QVariant();
            case 1: return (role == Qt::DisplayRole || role == Qt::EditRole) ? infos.id                                                           : QVariant();
            case 2: return (role == Qt::DisplayRole || role == Qt::EditRole) ? infos.title                                                        : QVariant();
            case 3: return (role == Qt::DisplayRole || role == Qt::EditRole) ? infos.pic1()                                                       : QVariant();
            case 4: return (role == Qt::DisplayRole || role == Qt::EditRole) ? infos.firmware                                                     : QVariant();
            case 5: return (role == Qt::DisplayRole || role == Qt::EditRole) ? infos.status                                                       : QVariant();
            case 6: return (role == Qt::DisplayRole || role == Qt::EditRole) ? QString("%1").arg(infos.crc32, 8, 16, QLatin1Char('0 ')).toUpper() : QVariant();
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
            case 0: return "ICON0";
            case 1: return "Disk ID";
            case 2: return "Title";
            case 3: return "PIC1";
            case 4: return "Firmware";
            case 5: return "Status";
            case 6: return "CRC32";
            }
        }

        return QVariant();
    }

private:
    mutable QList< UmdInfos > m_infos;
};

#endif