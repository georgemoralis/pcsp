#include "stdafx.h"

#ifndef NO_LOGGING

#include "log.h"
#include <QObject>
#include <ctime>
#include "qt4/settings.h"

#include "debugger/debugger.h"

Log::Logs _logs;

//General
LogCategory Log::dList("dList");
LogCategory Log::Renderer("rasterizer");
LogCategory Log::interpreter("interpreter");
LogCategory Log::loader("loader");
LogCategory Log::syscalls("syscalls");

//HLE
LogCategory Log::kernel("kernel");
LogCategory Log::sceRtc("sceRtc");
LogCategory Log::SysMemUserForUser("SysMemUserForUser");
LogCategory Log::sceUmdUser("sceUmdUser");
LogCategory Log::sceSasCore("sceSasCore");
LogCategory Log::sceAudio("sceAudio");
LogCategory Log::sceGe_user("sceGe_user");
LogCategory Log::sceDisplay("sceDisplay");
LogCategory Log::IoFileMgrForUser("IoFileMgrForUser");
LogCategory Log::sceAtrac3plus("sceAtrac3plus");
LogCategory Log::ThreadManForUser("ThreadManForUser");
LogCategory Log::scePower("scePower");
LogCategory Log::sceUtility("sceUtility");
LogCategory Log::hlemisc("hlemisc");
LogCategory Log::hlestdout("hlestdout");
LogCategory Log::sceImpose("sceImpose");
LogCategory Log::sceMpeg("sceMpeg");
LogCategory Log::sceSuspendForUser("sceSuspendForUser");
LogCategory Log::InterruptManager("InterruptManager");
LogCategory Log::StdioForUser("StdioForUser");
LogCategory Log::sceDmac("sceDmac");
LogCategory Log::sceCtrl("sceCtrl");
LogCategory Log::UtilsForUser("UtilsForUser");
LogCategory Log::Kernel_Library("Kernel_Library");
LogCategory Log::LoadExecForUser("LoadExecForUser");
LogCategory Log::ModuleMgrForUser("ModuleMgrForUser");
LogCategory Log::scePsmf("scePsmf");
LogCategory Log::sceDeflt("sceDeflt");
LogCategory Log::scePsmfPlayer("scePsmfPlayer");
LogCategory Log::sceFont("sceFont");
LogCategory Log::sceMp3("sceMp3");

//FileSystems
LogCategory Log::isoFileSystem("isoFileSystem");
LogCategory Log::cardFileSystem("cardFileSystem");
LogCategory Log::metaFileSystem("metaFileSystem");


Log::Logs &Log::logs()
{
    return _logs;
}

void Log::init()
{
    Log::hlestdout.init();
    Log::kernel.init();
    Log::loader.init();
    Log::interpreter.init();
    Log::sceRtc.init();
    Log::SysMemUserForUser.init();
    Log::sceUmdUser.init();
    Log::sceSasCore.init();
    Log::sceAudio.init();
    Log::dList.init();
    Log::IoFileMgrForUser.init();
    Log::sceDisplay.init();
    Log::ThreadManForUser.init();
    Log::sceAtrac3plus.init();
    Log::scePower.init();
    Log::sceUtility.init();
    Log::sceGe_user.init();
    Log::hlemisc.init();
    Log::sceImpose.init();
    Log::sceMpeg.init();
    Log::Renderer.init();
    Log::isoFileSystem.init();
    Log::cardFileSystem.init();
    Log::metaFileSystem.init();
    Log::sceSuspendForUser.init();
    Log::InterruptManager.init();
    Log::StdioForUser.init();
    Log::sceDmac.init();
    Log::sceCtrl.init();
    Log::UtilsForUser.init();
    Log::Kernel_Library.init();
    Log::LoadExecForUser.init();
    Log::ModuleMgrForUser.init();
	Log::scePsmf.init();
	Log::sceDeflt.init();
	Log::scePsmfPlayer.init();
	Log::sceFont.init();
	Log::sceMp3.init();
}

void Log::reset()
{
    Log::hlestdout.reopen();
    Log::kernel.reopen();
    Log::loader.reopen();
    Log::interpreter.reopen();
    Log::sceRtc.reopen();
    Log::SysMemUserForUser.reopen();
    Log::sceUmdUser.reopen();
    Log::sceSasCore.reopen();
    Log::sceAudio.reopen();
    Log::dList.reopen();
    Log::IoFileMgrForUser.reopen();
    Log::sceDisplay.reopen();
    Log::ThreadManForUser.reopen();
    Log::sceAtrac3plus.reopen();
    Log::scePower.reopen();
    Log::sceUtility.reopen();
    Log::sceGe_user.reopen();
    Log::hlemisc.reopen();
    Log::sceImpose.reopen();
    Log::sceMpeg.reopen();
    Log::Renderer.reopen();
    Log::isoFileSystem.reopen();
    Log::cardFileSystem.reopen();
    Log::metaFileSystem.reopen();
    Log::sceSuspendForUser.reopen();
    Log::InterruptManager.reopen();
    Log::StdioForUser.reopen();
    Log::sceDmac.reopen();
    Log::sceCtrl.reopen();
    Log::UtilsForUser.reopen();
    Log::Kernel_Library.reopen();
	Log::LoadExecForUser.reopen();
    Log::ModuleMgrForUser.reopen();
	Log::scePsmf.reopen();
	Log::sceDeflt.reopen();
	Log::scePsmfPlayer.reopen();
	Log::sceFont.reopen();
	Log::sceMp3.reopen();
}


LogCategory::LogCategory(QString const &name)
:   m_name(name)
{
    m_level = E_OFF;
}

LogCategory::~LogCategory()
{
}

void LogCategory::init()
{
    Log::logs().insert(this);
}

void LogCategory::reset()
{
    unsigned int value = E_TRACE;
    value = 0; // if no found all levels are 0
    settings.LoadLoggingConfig(m_name, value);
    m_level = (LevelEnum) value;	
}

void LogCategory::reopen()
{
    unsigned int value = E_TRACE;
    value = 0; // if no found all levels are 0
    settings.LoadLoggingConfig(m_name, value);
    m_level = (LevelEnum) value;
    return;
}

LogCategory::LevelEnum LogCategory::getLevel()
{
    return m_level;
}

void LogCategory::setLevel(LogCategory::LevelEnum level)
{
    m_level = level;
}

bool LogCategory::checkLevel(LogCategory::LevelEnum level)
{
    return m_level >= level;
}

LogSubCategory::LogSubCategory(LogCategory &category, QString const &subname)
    : LogCategory(subname), m_category(category), m_subname(subname), m_inited(false)
{
}

void LogSubCategory::init()
{
    if (!m_inited)
    {
        LogCategory::init();
        m_name = m_category.getName() + ":" + m_subname;
        m_category.get_subcategories().insert(this);
        m_inited = true;
    }
}

LogSubCategory::LevelEnum LogSubCategory::getLevel()
{
    return m_category.getLevel();
}

bool LogSubCategory::checkLevel(LogCategory::LevelEnum level)
{
    return m_category.getLevel() >= level;
}

void LogCategory::printf(LevelEnum level, char const *fmt, va_list args)
{
    static char const * const level_name[] = { "E_OFF", "E_FATAL", "E_ERROR", "E_WARN", "E_INFO", "E_DEBUG", "E_TRACE" };

    static int const level_color[] = { 0, 1, 1, 3, 4, 2, 8 };

    if (!checkLevel(level))
        return;

    char tmp1[1024];
    char tmp2[1024];

    ::vsnprintf(tmp1, 1024, fmt, args);
    ::snprintf(tmp2, 1024, "%-63s|%-7s| %-10s -%s\n", m_name.toAscii().constData(), level_name[level], QTime::currentTime().toString(Qt::ISODate).toAscii().constData(), tmp1);
    Log::show(level_color[level], tmp2);
}

// this one should be defined somewhere else because it is platform-dependent
void Lang::printf(char *s, char const *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    ::vsnprintf(s, 1024, fmt, args);
    va_end(args);
}

// this one should be defined somewhere else because it is platform-dependent
void Lang::printf(char *s, char const *fmt, va_list args)
{
    ::vsnprintf(s, 1024, fmt, args);
}

namespace Log
{
    void show(int level, QString const &text)
    {
        (void)level;
        emit debugger.log(text);
    }
}
#endif

