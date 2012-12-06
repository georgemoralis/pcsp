/*
* log.h
*
*  Created on: 13 dec. 2008
*      Author: hli
*/

#ifndef LOG_H_
#define LOG_H_

#include <QString>
#include <set>

class LogSubCategory;

class LogCategory
{
public:
    enum LevelEnum
    {
        E_OFF, E_FATAL, E_ERROR, E_WARN, E_INFO, E_DEBUG, E_TRACE
    };

    LogCategory(QString const &name);
    ~LogCategory();

    virtual void init();
    void reset();
    void reopen();
    void flush();

    static void useConsole(bool use);

    virtual LevelEnum getLevel() ;
    void setLevel(LevelEnum level);
    virtual bool checkLevel(LevelEnum level) ;

    void log(LevelEnum level, const char *fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        printf(level, fmt, args);
        va_end(args);
    }

    void fatal(const char *fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        printf(E_FATAL, fmt, args);
        va_end(args);
    }

    void error(const char *fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        printf(E_ERROR, fmt, args);
        va_end(args);
    }

    void warn(const char *fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        printf(E_WARN, fmt, args);
        va_end(args);
    }
    void info(const char *fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        printf(E_INFO, fmt, args);
        va_end(args);
    }

    void debug(const char *fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        printf(E_DEBUG, fmt, args);
        va_end(args);
    }

    void trace(const char *fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        printf(E_TRACE, fmt, args);
        va_end(args);
    }

    QString const &getName() const { return m_name; }

	std::set< LogSubCategory * > &get_subcategories() { return m_subcategories; }

protected:
    virtual void printf(LevelEnum level, const char *fmt, va_list args);

    LevelEnum           m_level;
    QString             m_name;

    FILE *file;
    bool in_list;

    std::set< LogSubCategory * > m_subcategories;

private:
    LogCategory(LogCategory const &);
    void operator = (LogCategory const &);
};


class LogSubCategory : public LogCategory
{
public:
	LogSubCategory(LogCategory &category, QString const &name);
	~LogSubCategory() {}

    void init();
	void reopen();

    LevelEnum getLevel() ;
    bool checkLevel(LevelEnum level) ;

	QString const &getShortName() const { return m_subname; }

protected:
    virtual void printf(LevelEnum level, const char *fmt, va_list args)
	{
        init();
		if (m_category.checkLevel(level)) LogCategory::printf(level, fmt, args);
	}

    LogCategory &m_category;
	QString m_subname;
    bool m_inited;

private:
	LogSubCategory(LogSubCategory const &);
	void operator = (LogSubCategory const &);
};

#undef NO_LOGGING
// #define STDERR_LOG

#ifdef NO_LOGGING
#define lprintf(name, level, fmt, ...)
#define fatalf(name, fmt, ...)
#define errorf(name, fmt, ...)
#define warnf(name, fmt, ...)
#define infof(name, fmt, ...)
#define debugf(name, fmt, ...)
#define tracef(name, fmt, ...)
#else
#ifdef STDERR_LOG
#define lprintf(name, level, fmt, ...) if (Log::name.checkLevel(level)) fprintf(stderr, fmt "\n", ## __VA_ARGS__)
#define fatalf(name, fmt, ...) if (Log::name.checkLevel(LogCategory::E_FATAL)) fprintf(stderr, fmt "\n", ## __VA_ARGS__)
#define errorf(name, fmt, ...) if (Log::name.checkLevel(LogCategory::E_ERROR)) fprintf(stderr, fmt "\n", ## __VA_ARGS__)
#define warnf(name, fmt, ...) if (Log::name.checkLevel(LogCategory::E_WARN)) fprintf(stderr, fmt "\n", ## __VA_ARGS__)
#define infof(name, fmt, ...) if (Log::name.checkLevel(LogCategory::E_INFO)) fprintf(stderr, fmt "\n", ## __VA_ARGS__)
#define debugf(name, fmt, ...) if (Log::name.checkLevel(LogCategory::E_DEBUG)) fprintf(stderr, fmt "\n", ## __VA_ARGS__)
#define tracef(name, fmt, ...) if (Log::name.checkLevel(LogCategory::E_TRACE)) fprintf(stderr, fmt "\n", ## __VA_ARGS__)
#else
#define lprintf(name, level, fmt, ...) if (Log::name.checkLevel(level)) Log::name.log(level, fmt, ## __VA_ARGS__)
#define fatalf(name, fmt, ...) if (Log::name.checkLevel(LogCategory::E_FATAL)) Log::name.fatal(fmt, ## __VA_ARGS__)
#define errorf(name, fmt, ...) if (Log::name.checkLevel(LogCategory::E_ERROR)) Log::name.error(fmt, ## __VA_ARGS__)
#define warnf(name, fmt, ...) if (Log::name.checkLevel(LogCategory::E_WARN)) Log::name.warn(fmt, ## __VA_ARGS__)
#define infof(name, fmt, ...) if (Log::name.checkLevel(LogCategory::E_INFO)) Log:: name .info(fmt, ## __VA_ARGS__)
#define debugf(name, fmt, ...) if (Log::name.checkLevel(LogCategory::E_DEBUG)) Log::name.debug(fmt, ## __VA_ARGS__)
#define tracef(name, fmt, ...) if (Log::name.checkLevel(LogCategory::E_TRACE)) Log::name.trace(fmt, ## __VA_ARGS__)
#endif
#endif

namespace Log
{
    void init();
    void show(int level, QString const &s);
    void reset();

    extern LogCategory interpreter;
    extern LogCategory loader;
    extern LogCategory sceUmdUser;
    extern LogCategory sceSasCore;
    extern LogCategory ThreadManForUser;
    extern LogCategory hlemisc;
    extern LogCategory sceRtc;
    extern LogCategory IoFileMgrForUser;
    extern LogCategory hlestdout;
    extern LogCategory sceAudio;

    extern LogCategory sceImpose;
    extern LogCategory kernel;
    extern LogCategory sceDisplay;
    extern LogCategory scePower;
    extern LogCategory sceUtility;
    extern LogCategory sceAtrac3plus;
    extern LogCategory sceGe_user;
    extern LogCategory dList;
    extern LogCategory Renderer;
    extern LogCategory SysMemUserForUser;
    extern LogCategory isoFileSystem;
    extern LogCategory cardFileSystem;
    extern LogCategory metaFileSystem;
    extern LogCategory sceMpeg;
    extern LogCategory sceSuspendForUser;
    extern LogCategory InterruptManager;
    extern LogCategory StdioForUser;
    extern LogCategory sceDmac;
    extern LogCategory sceCtrl;
    extern LogCategory UtilsForUser;
    extern LogCategory Kernel_Library;
	extern LogCategory LoadExecForUser;
	extern LogCategory ModuleMgrForUser;
	extern LogCategory scePsmf;
	extern LogCategory sceDeflt; 
	extern LogCategory scePsmfPlayer;
	extern LogCategory sceFont;
	extern LogCategory sceMp3;

    extern LogCategory syscalls;

    typedef std::set< LogCategory const * > Categories, Logs;
	typedef std::set< LogSubCategory * > SubCategories;

    Logs &logs();
}

namespace Lang
{
    void printf(char *s, char const *fmt, ...);
    void printf(char *s, char const *fmt, va_list args);
}

#endif /* LOG_H_ */
