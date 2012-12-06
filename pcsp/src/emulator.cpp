#include "stdafx.h"
#include "emulator.h"
#include "renderer.h"
#include "system.h"
#include "log.h"
#include "loaders/loaders.h"

volatile int vsync_limiter = 0;

extern void recompiler_test();

Emulator::Emulator()
:   m_needs_load(false)
,   m_needs_start(false)
,   m_loaded_game(false)
,   m_current_game_filename()
,   m_test_event_counter(0)
,   reschedule(false)
{
    m_current_state = EmuPausing;

    recompiler_test();
}

Emulator::~Emulator()
{
}

bool Emulator::StartUp()
{
	Log::reset();

    //m_me_thread.Start();
    //m_ge_thread.Start();
    
    m_sc_thread.Start();
    
	return true;
}

bool Emulator::ShutDown()
{
	m_current_state = EmuLeaving;

    m_sc_thread.Join();
    m_ge_thread.Join();
    m_me_thread.Join();

	return true;
}

void Emulator::LoadGame()
{
    m_loaded_game = true;

    EmuFileType result = loaders::LoadFile(m_current_game_filename);

    if (result == FILETYPE_ERROR)
    {
        Sc().Critical(Sc().tr("Loading Game..."), Sc().tr("Cannot load this game because there is a FILETYPE_ERROR."));
    }
    else if (result == FILETYPE_ENCRYPTED)
    {
        Sc().Critical(Sc().tr("Loading Game..."), Sc().tr("Cannot load this game because it is encrypted."));
    }
    else if (result == FILETYPE_UNKNOWN)
    {
        Sc().Critical(Sc().tr("Loading Game..."), Sc().tr("Cannot load this game because its type is unknown."));
    }
    else if (result == FILETYPE_NO_FILE)
    {
        Sc().Critical(Sc().tr("Loading Game..."), Sc().tr("Cannot load this game because the file does not exist."));
    }

    m_needs_load = false;
}

void Emulator::UnloadGame()
{
    if (m_loaded_game)
    {
        loaders::UnloadFile();
    }
    m_loaded_game = false;
}

Emulator theEmulator;
