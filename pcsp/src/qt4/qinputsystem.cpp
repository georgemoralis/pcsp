#include "stdafx.h"
#include "common/types.h"
#include "qinputsystem.h"

QInputSystem *theInputSystem = 0;

/// InputController ///////////////////////////////

/// InputKeyboard /////////////////////////////////

void InputKeyboard::Update( unsigned int &buttons, unsigned char &lx, unsigned char &ly, bool amode )
{
    buttons = 0;
    lx = 128;
    ly = 128;
    int code;
    for (int i = 0; i < 30; ++i)
    {
        if ((code = m_codemap[i]) != -1 && IsButtonDown(code))
        {
            buttons |= 1<<i;
        }
    }

    if (amode)
    {
        lx = (buttons & 0x10000000 /* LEFT */) ? 0 : (buttons & 0x20000000 /* RIGHT */) ? 255 : 128;
        ly = (buttons & 0x04000000 /* UP   */) ? 0 : (buttons & 0x08000000 /* DOWN  */) ? 255 : 128;
    }
}

bool InputKeyboard::IsButtonDown(int code)
{
    return theInputSystem->KeyDown(code);
}

QString InputKeyboard::GetTextButton(int code)
{
    static std::map< int, QString > key_text_map;

    // check if we need to initialize map first
    if (key_text_map.size() == 0)
    {
		key_text_map[-1]				 			= "<None>";
		key_text_map[Qt::Key_Escape]	 			= "Escape";
		key_text_map[Qt::Key_Tab]	 				= "Tab";
		key_text_map[Qt::Key_Backtab]	 			= "Backtab";
		key_text_map[Qt::Key_Backspace]	 		    = "Backspace";
		key_text_map[Qt::Key_Return]	 			= "Return";
		key_text_map[Qt::Key_Enter]	 			    = "Enter";
		key_text_map[Qt::Key_Insert]	 			= "Insert";
		key_text_map[Qt::Key_Delete]	 			= "Delete";
		key_text_map[Qt::Key_Pause]	 				= "Pause";
		key_text_map[Qt::Key_Print]	 				= "Print";
		key_text_map[Qt::Key_SysReq]	 			= "SysReq";
		key_text_map[Qt::Key_Clear]	 				= "Clear";
		key_text_map[Qt::Key_Home]	 				= "Home";
		key_text_map[Qt::Key_End]	 				= "End";
		key_text_map[Qt::Key_Left]	 			    = "Left";
		key_text_map[Qt::Key_Up]					= "Up";
		key_text_map[Qt::Key_Right]					= "Right";
		key_text_map[Qt::Key_Down]					= "Down";
		key_text_map[Qt::Key_PageUp]				= "PageUp";
		key_text_map[Qt::Key_PageDown]				= "PageDown";
		key_text_map[Qt::Key_Shift]					= "Shift";
		key_text_map[Qt::Key_Control]				= "Control";
		key_text_map[Qt::Key_Meta]					= "Meta";
		key_text_map[Qt::Key_AltGr]					= "AltGr";
		key_text_map[Qt::Key_CapsLock]				= "CapsLock";
		key_text_map[Qt::Key_NumLock]				= "NumLock";
		key_text_map[Qt::Key_ScrollLock]			= "ScrollLock";
		key_text_map[Qt::Key_F1]					= "F1";
		key_text_map[Qt::Key_F2]					= "F2";
		key_text_map[Qt::Key_F3]					= "F3";
		key_text_map[Qt::Key_F4]					= "F4";
		key_text_map[Qt::Key_F5]					= "F5";
		key_text_map[Qt::Key_F6]					= "F6";
		key_text_map[Qt::Key_F7]					= "F7";
		key_text_map[Qt::Key_F8]					= "F8";
		key_text_map[Qt::Key_F9]					= "F9";
		key_text_map[Qt::Key_F10]					= "F10";
		key_text_map[Qt::Key_F11]					= "F11";
		key_text_map[Qt::Key_F12]					= "F12";
		key_text_map[Qt::Key_F13]					= "F13";
		key_text_map[Qt::Key_F14]					= "F14";
		key_text_map[Qt::Key_F15]					= "F15";
		key_text_map[Qt::Key_F16]					= "F16";
		key_text_map[Qt::Key_F17]					= "F17";
		key_text_map[Qt::Key_F18]					= "F18";
		key_text_map[Qt::Key_F19]					= "F19";
		key_text_map[Qt::Key_F20]					= "F20";
		key_text_map[Qt::Key_F21]					= "F21";
		key_text_map[Qt::Key_F22]					= "F22";
		key_text_map[Qt::Key_F23]					= "F23";
		key_text_map[Qt::Key_F24]					= "F24";
		key_text_map[Qt::Key_F25]					= "F25";
		key_text_map[Qt::Key_F26]					= "F26";
		key_text_map[Qt::Key_F27]					= "F27";
		key_text_map[Qt::Key_F28]					= "F28";
		key_text_map[Qt::Key_F29]					= "F29";
		key_text_map[Qt::Key_F30]					= "F30";
		key_text_map[Qt::Key_F31]					= "F31";
		key_text_map[Qt::Key_F32]					= "F32";
		key_text_map[Qt::Key_F33]					= "F33";
		key_text_map[Qt::Key_F34]					= "F34";
		key_text_map[Qt::Key_F35]					= "F35";
		key_text_map[Qt::Key_Super_L]				= "Super_L";
		key_text_map[Qt::Key_Super_R]				= "Super_R";
		key_text_map[Qt::Key_Menu]					= "Menu";
		key_text_map[Qt::Key_Hyper_L]				= "Hyper_L";
		key_text_map[Qt::Key_Hyper_R]				= "Hyper_R";
		key_text_map[Qt::Key_Help]					= "Help";
		key_text_map[Qt::Key_Direction_L]			= "Direction_L";
		key_text_map[Qt::Key_Direction_R]			= "Direction_R";
		key_text_map[Qt::Key_Space]					= "Space";
		key_text_map[Qt::Key_Any]					= "Any";
		key_text_map[Qt::Key_Exclam]				= "Exclam";
		key_text_map[Qt::Key_QuoteDbl]				= "QuoteDbl";
		key_text_map[Qt::Key_NumberSign]			= "NumberSign";
		key_text_map[Qt::Key_Dollar]				= "Dollar";
		key_text_map[Qt::Key_Percent]				= "Percent";
		key_text_map[Qt::Key_Ampersand]				= "Ampersand";
		key_text_map[Qt::Key_Apostrophe]			= "Apostrophe";
		key_text_map[Qt::Key_ParenLeft]				= "ParenLeft";
		key_text_map[Qt::Key_ParenRight]			= "ParenRight";
		key_text_map[Qt::Key_Asterisk]				= "Asterisk";
		key_text_map[Qt::Key_Plus]					= "Plus";
		key_text_map[Qt::Key_Comma]				    = "Comma";
		key_text_map[Qt::Key_Minus]					= "Minus";
		key_text_map[Qt::Key_Period]				= "Period";
		key_text_map[Qt::Key_Slash]					= "Slash";
		key_text_map[Qt::Key_0]					    = "0";
		key_text_map[Qt::Key_1]						= "1";
		key_text_map[Qt::Key_2]					    = "2";
		key_text_map[Qt::Key_3]					    = "3";
		key_text_map[Qt::Key_4]						= "4";
		key_text_map[Qt::Key_5]					    = "5";
		key_text_map[Qt::Key_6]					    = "6";
		key_text_map[Qt::Key_7]						= "7";
		key_text_map[Qt::Key_8]						= "8";
		key_text_map[Qt::Key_9]					    = "9";
		key_text_map[Qt::Key_Colon]				    = "Colon";
		key_text_map[Qt::Key_Semicolon]			    = "Semicolon";
		key_text_map[Qt::Key_Less]				    = "Less";
		key_text_map[Qt::Key_Equal]				    = "Equal";
		key_text_map[Qt::Key_Greater]				= "Greater";
		key_text_map[Qt::Key_Question]			    = "Question";
		key_text_map[Qt::Key_At]					= "At";
		key_text_map[Qt::Key_A]					    = "A";
		key_text_map[Qt::Key_B]					    = "B";
		key_text_map[Qt::Key_C]						= "C";
		key_text_map[Qt::Key_D]					    = "D";
		key_text_map[Qt::Key_E]					    = "E";
		key_text_map[Qt::Key_F]						= "F";
		key_text_map[Qt::Key_G]						= "G";
		key_text_map[Qt::Key_H]					    = "H";
		key_text_map[Qt::Key_I]					    = "I";
		key_text_map[Qt::Key_J]						= "J";
		key_text_map[Qt::Key_K]						= "K";
		key_text_map[Qt::Key_L]						= "L";
		key_text_map[Qt::Key_M]					    = "M";
		key_text_map[Qt::Key_N]						= "N";
		key_text_map[Qt::Key_O]					    = "O";
		key_text_map[Qt::Key_P]					    = "P";
		key_text_map[Qt::Key_Q]					    = "Q";
		key_text_map[Qt::Key_R]					    = "R";
		key_text_map[Qt::Key_S]					    = "S";
		key_text_map[Qt::Key_T]					    = "T";
		key_text_map[Qt::Key_U]					    = "U";
		key_text_map[Qt::Key_V]					    = "V";
		key_text_map[Qt::Key_W]					    = "W";
		key_text_map[Qt::Key_X]					    = "X";
		key_text_map[Qt::Key_Y]					    = "Y";
		key_text_map[Qt::Key_Z]					    = "Z";
		key_text_map[Qt::Key_BracketLeft]			= "BracketLeft";
		key_text_map[Qt::Key_Backslash]			    = "Backslash";
		key_text_map[Qt::Key_BracketRight]		    = "BracketRight";
		key_text_map[Qt::Key_AsciiCircum]			= "AsciiCircum";
		key_text_map[Qt::Key_Underscore]			= "Underscore";
		key_text_map[Qt::Key_QuoteLeft]			    = "QuoteLeft";
		key_text_map[Qt::Key_BraceLeft]			    = "BraceLeft";
		key_text_map[Qt::Key_Bar]					= "Bar";
		key_text_map[Qt::Key_BraceRight]			= "BraceRight";
		key_text_map[Qt::Key_AsciiTilde]			= "AsciiTilde";
		key_text_map[Qt::Key_nobreakspace]		    = "nobreakspace";
		key_text_map[Qt::Key_exclamdown]			= "exclamdown";
		key_text_map[Qt::Key_cent]				    = "cent";
		key_text_map[Qt::Key_sterling]			    = "sterling";
		key_text_map[Qt::Key_currency]			    = "currency";
		key_text_map[Qt::Key_yen]				    = "yen";
		key_text_map[Qt::Key_brokenbar]			    = "brokenbar";
		key_text_map[Qt::Key_section]				= "section";
		key_text_map[Qt::Key_diaeresis]			    = "diaeresis";
		key_text_map[Qt::Key_copyright]			    = "copyright";
		key_text_map[Qt::Key_ordfeminine]			= "ordfeminine";
		key_text_map[Qt::Key_guillemotleft]		    = "guillemotleft";
		key_text_map[Qt::Key_notsign]				= "notsign";
		key_text_map[Qt::Key_hyphen]				= "hyphen";
		key_text_map[Qt::Key_registered]			= "registered";
		key_text_map[Qt::Key_macron]				= "macron";
		key_text_map[Qt::Key_degree]				= "degree";
		key_text_map[Qt::Key_plusminus]			    = "plusminus";
		key_text_map[Qt::Key_twosuperior]			= "twosuperior";
		key_text_map[Qt::Key_threesuperior]		    = "threesuperior";
		key_text_map[Qt::Key_acute]				    = "acute";
		key_text_map[Qt::Key_mu]					= "mu";
		key_text_map[Qt::Key_paragraph]			    = "paragraph";
		key_text_map[Qt::Key_periodcentered]		= "periodcentered";
		key_text_map[Qt::Key_cedilla]				= "cedilla";
		key_text_map[Qt::Key_onesuperior]			= "onesuperior";
		key_text_map[Qt::Key_masculine]			    = "masculine";
		key_text_map[Qt::Key_guillemotright]		= "guillemotright";
		key_text_map[Qt::Key_onequarter]			= "onequarter";
		key_text_map[Qt::Key_onehalf]				= "onehalf";
		key_text_map[Qt::Key_threequarters]		    = "threequarters";
		key_text_map[Qt::Key_questiondown]		    = "questiondown";
		key_text_map[Qt::Key_Agrave]				= "Agrave";
		key_text_map[Qt::Key_Aacute]				= "Aacute";
		key_text_map[Qt::Key_Acircumflex]			= "Acircumflex";
		key_text_map[Qt::Key_Atilde]				= "Atilde";
		key_text_map[Qt::Key_Adiaeresis]			= "Adiaeresis";
		key_text_map[Qt::Key_Aring]				    = "Aring";
		key_text_map[Qt::Key_AE]					= "AE";
		key_text_map[Qt::Key_Ccedilla]			    = "Ccedilla";
		key_text_map[Qt::Key_Egrave]				= "Egrave";
		key_text_map[Qt::Key_Eacute]				= "Eacute";
		key_text_map[Qt::Key_Ecircumflex]			= "Ecircumflex";
		key_text_map[Qt::Key_Ediaeresis]			= "Ediaeresis";
		key_text_map[Qt::Key_Igrave]				= "Igrave";
		key_text_map[Qt::Key_Iacute]				= "Iacute";
		key_text_map[Qt::Key_Icircumflex]			= "Icircumflex";
		key_text_map[Qt::Key_Idiaeresis]			= "Idiaeresis";
		key_text_map[Qt::Key_ETH]					= "ETH";
		key_text_map[Qt::Key_Ntilde]				= "Ntilde";
		key_text_map[Qt::Key_Ograve]				= "Ograve";
		key_text_map[Qt::Key_Oacute]				= "Oacute";
		key_text_map[Qt::Key_Ocircumflex]			= "Ocircumflex";
		key_text_map[Qt::Key_Otilde]				= "Otilde";
		key_text_map[Qt::Key_Odiaeresis]			= "Odiaeresis";
		key_text_map[Qt::Key_multiply]			    = "multiply";
		key_text_map[Qt::Key_Ooblique]			    = "Ooblique";
		key_text_map[Qt::Key_Ugrave]				= "Ugrave";
		key_text_map[Qt::Key_Uacute]				= "Uacute";
		key_text_map[Qt::Key_Ucircumflex]			= "Ucircumflex";
		key_text_map[Qt::Key_Udiaeresis]			= "Udiaeresis";
		key_text_map[Qt::Key_Yacute]				= "Yacute";
		key_text_map[Qt::Key_THORN]				    = "THORN";
		key_text_map[Qt::Key_ssharp]				= "ssharp";
		key_text_map[Qt::Key_division]			    = "division";
		key_text_map[Qt::Key_ydiaeresis]			= "ydiaeresis";
		key_text_map[Qt::Key_Multi_key]			    = "Multi_key";
		key_text_map[Qt::Key_Codeinput]			    = "Codeinput";
		key_text_map[Qt::Key_SingleCandidate]		= "SingleCandidate";
		key_text_map[Qt::Key_MultipleCandidate]	    = "MultipleCandidate";
		key_text_map[Qt::Key_PreviousCandidate]	    = "PreviousCandidate";
		key_text_map[Qt::Key_Mode_switch]			= "Mode_switch";
		key_text_map[Qt::Key_Kanji]				    = "Kanji";
		key_text_map[Qt::Key_Muhenkan]			    = "Muhenkan";
		key_text_map[Qt::Key_Henkan]				= "Henkan";
		key_text_map[Qt::Key_Romaji]				= "Romaji";
		key_text_map[Qt::Key_Hiragana]			    = "Hiragana";
		key_text_map[Qt::Key_Katakana]			    = "Katakana";
		key_text_map[Qt::Key_Hiragana_Katakana]	    = "Hiragana_Katakana";
		key_text_map[Qt::Key_Zenkaku]				= "Zenkaku";
		key_text_map[Qt::Key_Hankaku]				= "Hankaku";
		key_text_map[Qt::Key_Zenkaku_Hankaku]		= "Zenkaku_Hankaku";
		key_text_map[Qt::Key_Touroku]				= "Touroku";
		key_text_map[Qt::Key_Massyo]				= "Massyo";
		key_text_map[Qt::Key_Kana_Lock]			    = "Kana_Lock";
		key_text_map[Qt::Key_Kana_Shift]			= "Kana_Shift";
		key_text_map[Qt::Key_Eisu_Shift]			= "Eisu_Shift";
		key_text_map[Qt::Key_Eisu_toggle]			= "Eisu_toggle";
		key_text_map[Qt::Key_Hangul]				= "Hangul";
		key_text_map[Qt::Key_Hangul_Start]		    = "Hangul_Start";
		key_text_map[Qt::Key_Hangul_End]			= "Hangul_End";
		key_text_map[Qt::Key_Hangul_Hanja]		    = "Hangul_Hanja";
		key_text_map[Qt::Key_Hangul_Jamo]			= "Hangul_Jamo";
		key_text_map[Qt::Key_Hangul_Romaja]		    = "Hangul_Romaja";
		key_text_map[Qt::Key_Hangul_Jeonja]		    = "Hangul_Jeonja";
		key_text_map[Qt::Key_Hangul_Banja]		    = "Hangul_Banja";
		key_text_map[Qt::Key_Hangul_PreHanja]		= "Hangul_PreHanja";
		key_text_map[Qt::Key_Hangul_PostHanja]	    = "Hangul_PostHanja";
		key_text_map[Qt::Key_Hangul_Special]		= "Hangul_Special";
		key_text_map[Qt::Key_Dead_Grave]			= "Dead_Grave";
		key_text_map[Qt::Key_Dead_Acute]			= "Dead_Acute";
		key_text_map[Qt::Key_Dead_Circumflex]		= "Dead_Circumflex";
		key_text_map[Qt::Key_Dead_Tilde]			= "Dead_Tilde";
		key_text_map[Qt::Key_Dead_Macron]			= "Dead_Macron";
		key_text_map[Qt::Key_Dead_Breve]			= "Dead_Breve";
		key_text_map[Qt::Key_Dead_Abovedot]		    = "Dead_Abovedot";
		key_text_map[Qt::Key_Dead_Diaeresis]		= "Dead_Diaeresis";
		key_text_map[Qt::Key_Dead_Abovering]		= "Dead_Abovering";
		key_text_map[Qt::Key_Dead_Doubleacute]	    = "Dead_Doubleacute";
		key_text_map[Qt::Key_Dead_Caron]			= "Dead_Caron";
		key_text_map[Qt::Key_Dead_Cedilla]		    = "Dead_Cedilla";
		key_text_map[Qt::Key_Dead_Ogonek]			= "Dead_Ogonek";
		key_text_map[Qt::Key_Dead_Iota]			    = "Dead_Iota";
		key_text_map[Qt::Key_Dead_Voiced_Sound]		= "Dead_Voiced_Sound";
		key_text_map[Qt::Key_Dead_Semivoiced_Sound]	= "Dead_Semivoiced_Sound";
		key_text_map[Qt::Key_Dead_Belowdot]			= "Dead_Belowdot";
		key_text_map[Qt::Key_Dead_Hook]				= "Dead_Hook";
		key_text_map[Qt::Key_Dead_Horn]				= "Dead_Horn";
		key_text_map[Qt::Key_Back]					= "Back";
		key_text_map[Qt::Key_Forward]				= "Forward";
		key_text_map[Qt::Key_Stop]					= "Stop";
		key_text_map[Qt::Key_Refresh]				= "Refresh";
		key_text_map[Qt::Key_VolumeDown]			= "VolumeDown";
		key_text_map[Qt::Key_VolumeMute]			= "VolumeMute";
		key_text_map[Qt::Key_VolumeUp]				= "VolumeUp";
		key_text_map[Qt::Key_BassBoost]				= "BassBoost";
		key_text_map[Qt::Key_BassUp]				= "BassUp";
		key_text_map[Qt::Key_BassDown]				= "BassDown";
		key_text_map[Qt::Key_TrebleUp]				= "TrebleUp";
		key_text_map[Qt::Key_TrebleDown]			= "TrebleDown";
		key_text_map[Qt::Key_MediaPlay]				= "MediaPlay";
		key_text_map[Qt::Key_MediaStop]				= "MediaStop";
		key_text_map[Qt::Key_MediaPrevious]			= "MediaPrevious";
		key_text_map[Qt::Key_MediaNext]				= "MediaNext";
		key_text_map[Qt::Key_MediaRecord]			= "MediaRecord";
		key_text_map[Qt::Key_HomePage]				= "HomePage";
		key_text_map[Qt::Key_Favorites]				= "Favorites";
		key_text_map[Qt::Key_Search]				= "Search";
		key_text_map[Qt::Key_Standby]				= "Standby";
		key_text_map[Qt::Key_OpenUrl]				= "OpenUrl";
		key_text_map[Qt::Key_LaunchMail]			= "LaunchMail";
		key_text_map[Qt::Key_LaunchMedia]			= "LaunchMedia";
		key_text_map[Qt::Key_Launch0]				= "Launch0";
		key_text_map[Qt::Key_Launch1]				= "Launch1";
		key_text_map[Qt::Key_Launch2]				= "Launch2";
		key_text_map[Qt::Key_Launch3]				= "Launch3";
		key_text_map[Qt::Key_Launch4]				= "Launch4";
		key_text_map[Qt::Key_Launch5]				= "Launch5";
		key_text_map[Qt::Key_Launch6]				= "Launch6";
		key_text_map[Qt::Key_Launch7]				= "Launch7";
		key_text_map[Qt::Key_Launch8]				= "Launch8";
		key_text_map[Qt::Key_Launch9]				= "Launch9";
		key_text_map[Qt::Key_LaunchA]				= "LaunchA";
		key_text_map[Qt::Key_LaunchB]				= "LaunchB";
		key_text_map[Qt::Key_LaunchC]				= "LaunchC";
		key_text_map[Qt::Key_LaunchD]				= "LaunchD";
		key_text_map[Qt::Key_LaunchE]				= "LaunchE";
		key_text_map[Qt::Key_LaunchF]				= "LaunchF";
		key_text_map[Qt::Key_MediaLast]				= "MediaLast";
		key_text_map[Qt::Key_unknown]				= "<unknown>";
        key_text_map[Qt::Key_Call]					= "Call";
		key_text_map[Qt::Key_Context1]				= "Context1";
		key_text_map[Qt::Key_Context2]				= "Context2";
		key_text_map[Qt::Key_Context3]				= "Context3";
		key_text_map[Qt::Key_Context4]				= "Context4";
		key_text_map[Qt::Key_Flip]					= "Flip";
		key_text_map[Qt::Key_Hangup]				= "Hangup";
		key_text_map[Qt::Key_No]					= "No";
		key_text_map[Qt::Key_Select]				= "Select";
		key_text_map[Qt::Key_Yes]					= "Yes";
		key_text_map[Qt::Key_Execute]				= "Execute";
		key_text_map[Qt::Key_Printer]				= "Printer";
		key_text_map[Qt::Key_Play]					= "Play";
		key_text_map[Qt::Key_Sleep]					= "Sleep";
		key_text_map[Qt::Key_Zoom]					= "Zoom";
		key_text_map[Qt::Key_Cancel]				= "Cancel";
	}

    return key_text_map[code];
}

/// InputJoypad ///////////////////////////////

void InputJoypad::Update(unsigned int &buttons, unsigned char &lx, unsigned char &ly, bool amode)
{
    buttons = 0;
    lx = 128;
    ly = 128;

    if (!Error())
    {
        Read(&m_buttons, amode ? m_axis : 0);

        int code;
        for (int i = 0; i < 30; ++i)
        {
            if (((code = m_codemap[i]) != -1) && IsButtonDown(code))
            {
                buttons |= 1<<i;
            }
        }

        if (amode)
        {
            if ((code = m_codemap[30]) != -1) lx = u8(ReadAxis(code));
            if ((code = m_codemap[31]) != -1) ly = u8(ReadAxis(code));
        }
    }
}

QString InputJoypad::GetTextButton(int code)
{
    static std::map< int, QString > code_text_map;

    // check if we need to initialize map first
    if (code_text_map.size() == 0)
    {
        code_text_map[-1] = "<None>";

        for (int i = 0; i < 32; ++i)
        {
            code_text_map[i]  = QString("Button %1").arg(i);
        }
    }

    return code_text_map[code];
}

QString InputJoypad::GetTextAxis(int code)
{
    static std::map< int, QString > code_text_map;

    // check if we need to initialize map first
    if (code_text_map.size() == 0)
    {
        code_text_map[-1] = "<None>";

        for (int i = 0; i < 8; ++i)
        {
            code_text_map[i]  = QString("Axis %1").arg(i);
        }
    }

    return code_text_map[code];
}

/// QIputSystem ///////////////////////////////////

QInputSystem::QInputSystem()
{
	theInputSystem = this;
	m_current_controller = 0;
}

QInputSystem::~QInputSystem()
{
}

void QInputSystem::Update(unsigned int &buttons, unsigned char &lx, unsigned char &ly, bool amode)
{
    InputController *controller = GetController();
    if (controller)
    {
        controller->Update(buttons, lx, ly, amode);
    }
}

bool QInputSystem::KeyDown(int key)
{
	return m_key_state[(Qt::Key)key];
}

void QInputSystem::WriteBufferKeyDown(int key)
{
	m_key_state[(Qt::Key)key] = true;
}

void QInputSystem::WriteBufferKeyUp(int key)
{
	m_key_state[(Qt::Key)key] = false;
}

int QInputSystem::GetFirstKey()
{
	for (std::map< Qt::Key, bool >::const_iterator it = m_key_state.begin(); it != m_key_state.end(); ++it)
	{
		if (it->second)
		{
			return it->first;
		}
	}
	return u32(-1);
}

void QInputSystem::UpdateControllers()
{
    AddFoundJoypads();
    AddDefaultKeyboard();
}

void QInputSystem::AddDefaultKeyboard()
{
	bool have_keyboard = false;
	for (int i = 0; i < m_controllers.size(); i++)
    {
		if (m_controllers[i]->IsKeyboard())
        {
            have_keyboard = true;
        }
    }
	
	if (!have_keyboard)
	{
		InputKeyboard *keyboard = new InputKeyboard();
		m_controllers.push_back(keyboard);

		// default key mapping
        keyboard->MapButton( 0 /* SELECT     */, Qt::Key_Shift);
        keyboard->MapButton( 1                 , -1);
        keyboard->MapButton( 2                 , -1);
        keyboard->MapButton( 3 /* START      */, Qt::Key_Return);
        keyboard->MapButton( 4 /* DPAD UP    */, Qt::Key_Up);
        keyboard->MapButton( 5 /* DPAD RIGHT */, Qt::Key_Right);
        keyboard->MapButton( 6 /* DPAD DOWN  */, Qt::Key_Down);
        keyboard->MapButton( 7 /* DPAD LEFT  */, Qt::Key_Left);
        keyboard->MapButton( 8 /* L          */, Qt::Key_1);
        keyboard->MapButton( 9 /* R          */, Qt::Key_2);
        keyboard->MapButton(10                 , -1);
        keyboard->MapButton(11                 , -1);
        keyboard->MapButton(12 /* TRIANGLE   */, Qt::Key_W);
        keyboard->MapButton(13 /* CIRCLE     */, Qt::Key_D);
        keyboard->MapButton(14 /* CROSS      */, Qt::Key_S);
        keyboard->MapButton(15 /* SQUARE     */, Qt::Key_Q);
        keyboard->MapButton(16 /* HOME       */, -1);
        keyboard->MapButton(17 /* HOLD       */, -1);
        keyboard->MapButton(18 /* SCREEN     */, -1);
        keyboard->MapButton(19 /* NOTE       */, -1);
        keyboard->MapButton(20 /* VOLUP      */, -1);
        keyboard->MapButton(21 /* VOLDOWN    */, -1);
        keyboard->MapButton(22 /* WLAN_UP    */, -1);
        keyboard->MapButton(23 /* REMOTE     */, -1);
        keyboard->MapButton(24 /* DISC       */, -1);
        keyboard->MapButton(25 /* MS         */, -1);
        keyboard->MapButton(26 /* APAD_UP    */, Qt::Key_I);
        keyboard->MapButton(27 /* APAD_DOWN  */, Qt::Key_K);
        keyboard->MapButton(28 /* APAD_LEFT  */, Qt::Key_J);
        keyboard->MapButton(29 /* APAD_RIGHT */, Qt::Key_L);
        keyboard->MapButton(30                 , -1);
        keyboard->MapButton(31                 , -1);

        //SetController(keyboard);
	}
}

void QInputSystem::AddFoundJoypads()
{
    InputJoypad *joypads[8];

    ::memset(joypads, 0, sizeof(joypads));

    foreach (InputController *controller, m_controllers)
    {
        if (controller->IsJoypad())
        {
            InputJoypad *joypad = (InputJoypad *)controller;

            joypads[joypad->GetId()] = joypad;
        }
    }

    for (int i = 0; i < 8; ++i)
    {
        InputJoypad *joypad = joypads[i];
        
        if (!joypad)
        {
            joypad = new InputJoypad(i);

            // default button mapping
            joypad->MapButton( 0 /* SELECT     */,  9);
            joypad->MapButton( 1                 , -1);
            joypad->MapButton( 2                 , -1);
            joypad->MapButton( 3 /* START      */,  8);
            joypad->MapButton( 4 /* DPAD UP    */, 30);
            joypad->MapButton( 5 /* DPAD RIGHT */, 28);
            joypad->MapButton( 6 /* DPAD DOWN  */, 31);
            joypad->MapButton( 7 /* DPAD LEFT  */, 29);
            joypad->MapButton( 8 /* L          */,  4);
            joypad->MapButton( 9 /* R          */,  5);
            joypad->MapButton(10                 , -1);
            joypad->MapButton(11                 , -1);
            joypad->MapButton(12 /* TRIANGLE   */,  3);
            joypad->MapButton(13 /* CIRCLE     */,  2);
            joypad->MapButton(14 /* CROSS      */,  1);
            joypad->MapButton(15 /* SQUARE     */,  0);
            joypad->MapButton(16 /* HOME       */, -1);
            joypad->MapButton(17 /* HOLD       */, -1);
            joypad->MapButton(18 /* SCREEN     */, -1);
            joypad->MapButton(19 /* NOTE       */, -1);
            joypad->MapButton(20 /* VOLUP      */, -1);
            joypad->MapButton(21 /* VOLDOWN    */, -1);
            joypad->MapButton(22 /* WLAN_UP    */, -1);
            joypad->MapButton(23 /* REMOTE     */, -1);
            joypad->MapButton(24 /* DISC       */, -1);
            joypad->MapButton(25 /* MS         */, -1);
            joypad->MapButton(26 /* APAD_UP    */, -1);
            joypad->MapButton(27 /* APAD_DOWN  */, -1);
            joypad->MapButton(28 /* APAD_LEFT  */, -1);
            joypad->MapButton(29 /* APAD_RIGHT */, -1);
            joypad->MapButton(30                 , -1);
            joypad->MapButton(31                 , -1);
            joypad->MapAxis(0, 0);
            joypad->MapAxis(1, 1);
        }

        if (!joypad->Error())
        {
            if (!joypads[i]) m_controllers.push_back(joypad);
        }
        else
        {
            if (joypads[i]) m_controllers.removeOne(joypad);
            delete joypad;
        }
    }
}

