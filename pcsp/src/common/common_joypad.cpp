#include "stdafx.h"
#include "common_joypad.h"

#if defined(__win32__)
#include <mmsystem.h>
#include <regstr.h>

struct JoypadOsSpecific
{
    JOYCAPSA     js_caps;
    JOYINFOEX    js_info;
    UINT         js_id;

    static bool getOEMProductName(Joypad &joypad, char *buffer, int size)
    {
        if (!joypad.Error())
        {
            union { char key[256]; char value[256]; };
            char OEMKey[256];

            HKEY  hKey;
            DWORD dwcb;
            LONG  lr;

            ::sprintf(key, "System\\CurrentControlSet\\Control\\MediaResources\\Joystick\\%s\\CurrentJoystickSettings", joypad.m_os->js_caps.szRegKey);
            lr = RegOpenKeyExA(HKEY_LOCAL_MACHINE, key, 0, KEY_QUERY_VALUE, &hKey);
            if (lr != ERROR_SUCCESS)
            {
                lr = RegOpenKeyExA(HKEY_CURRENT_USER, key, 0, KEY_QUERY_VALUE, &hKey);
                if (lr != ERROR_SUCCESS)
                {
                    return false;
                }
            }

            dwcb = sizeof(OEMKey);
            ::sprintf(value, "Joystick%dOEMName", joypad.m_os->js_id + 1);
            lr = RegQueryValueExA(hKey, value, 0, 0, (LPBYTE)OEMKey, &dwcb);
            RegCloseKey(hKey);
            if (lr == ERROR_SUCCESS)
            {
                ::sprintf(key, "System\\CurrentControlSet\\Control\\MediaProperties\\PrivateProperties\\Joystick\\OEM\\%s", OEMKey);
                lr = RegOpenKeyExA(HKEY_LOCAL_MACHINE, key, 0, KEY_QUERY_VALUE, &hKey);
				if(lr != ERROR_SUCCESS)
				{
                    lr = RegOpenKeyExA(HKEY_CURRENT_USER, key, 0, KEY_QUERY_VALUE, &hKey);
				}

                if (lr == ERROR_SUCCESS)
                {
                    dwcb = size;
                    lr = RegQueryValueExA(hKey, "OEMName", 0, 0, (LPBYTE)buffer, &dwcb);
                    RegCloseKey(hKey);
                }
            }

            return lr == ERROR_SUCCESS;
        }

        return false;
    }
};

void Joypad::Open()
{
    m_name[0] = '\0' ;

    m_os->js_info.dwFlags = JOY_RETURNALL;
    m_os->js_info.dwSize  = sizeof(m_os->js_info);

    ::memset(&(m_os->js_caps), 0, sizeof(m_os->js_caps));

    m_error = (joyGetDevCapsA(m_os->js_id, &(m_os->js_caps), sizeof(m_os->js_caps)) != JOYERR_NOERROR);
    m_num_buttons = m_os->js_caps.wNumButtons;
    if (m_os->js_caps.wNumAxes == 0)
    {
        m_num_axes = 0;
        SetError();
    }
    else
    {
        if (!m_os->getOEMProductName(*this, m_name, sizeof(m_name)))
        {
            ::strncpy(m_name, m_os->js_caps.szPname, sizeof(m_name));
        }

        if (m_os->js_caps.wCaps & JOYCAPS_HASPOV)
        {
            m_num_axes = 8;
            m_min[7] = -1.0; m_max[7] = 1.0;  // POV Y
            m_min[6] = -1.0; m_max[6] = 1.0;  // POV X
            if (m_num_buttons >= 28)
            {
               SetError();
            }
            m_num_buttons = 32;
        }
        else
        {
            m_num_axes = 6;
        }
        m_min[5] = (float)m_os->js_caps.wVmin; m_max[5] = (float)m_os->js_caps.wVmax;
        m_min[4] = (float)m_os->js_caps.wUmin; m_max[4] = (float)m_os->js_caps.wUmax;
        m_min[3] = (float)m_os->js_caps.wRmin; m_max[3] = (float)m_os->js_caps.wRmax;
        m_min[2] = (float)m_os->js_caps.wZmin; m_max[2] = (float)m_os->js_caps.wZmax;
        m_min[1] = (float)m_os->js_caps.wYmin; m_max[1] = (float)m_os->js_caps.wYmax;
        m_min[0] = (float)m_os->js_caps.wXmin; m_max[0] = (float)m_os->js_caps.wXmax;
    }

    for (int i = 0; i < m_num_axes; i++)
    {
        m_center[i] = (m_max[i] + m_min[i]) / 2.0f;
        m_dead_band[i] = 0.0f;
        m_saturate[i] = 1.0f;
    }
}

void Joypad::Close()
{
    delete m_os;
}

Joypad::Joypad(int id)
:   m_id(id)
,   m_os(new JoypadOsSpecific)
{
    if (id >= 0 && id < (int)joyGetNumDevs())
    {
        m_os->js_id = JOYSTICKID1 + id;
        Open();
    }
    else
    {
        m_num_axes = 0;
        SetError();
    }
}

void Joypad::RawRead(int *buttons, float *axes)
{
    if (Error())
    {
        if (buttons)
        {
            *buttons = 0;
        }

        if (axes)
        {
            for (int i = 0; i < m_num_axes; ++i)
            {
                axes[i] = 0.0f;
            }
        }

        return;
    }

    MMRESULT status = joyGetPosEx(m_os->js_id, &(m_os->js_info));
    if (status != JOYERR_NOERROR)
    {
        SetError();
        return;
    }

    if (buttons)
    {
        *buttons = (int)m_os->js_info.dwButtons;
    }

    if (axes)
    {
        switch (m_num_axes)
        {
        case 8:
            if ((m_os->js_info.dwPOV & 0xFFFF) == 0xFFFF)
            {
                axes[6] = 0.0;
                axes[7] = 0.0;
            }
            else
            {
                float s = (float)sin((m_os->js_info.dwPOV & 0xFFFF) * (0.01 * 3.1415926535f / 180));
                float c = (float)cos((m_os->js_info.dwPOV & 0xFFFF) * (0.01 * 3.1415926535f / 180));

                bool d;

                if (fabs(s) < fabs(c))
                {
                    d = c < 0.0f;
                    axes[6] = d ? -s/c  : s/c;
                    axes[7] = d ? -1.0f : 1.0f;
                    *buttons |= 1 << (30 + d);
                }
                else
                {
                    d = s < 0.0f;
                    axes[6] = d ? -1.0f : 1.0f;
                    axes[7] = d ? -c/s  : c/s;
                    *buttons |= 1 << (28 + d);
                }
            }

        case 6: axes[5] = (m_os->js_caps.wCaps & JOYCAPS_HASV) ? (float)m_os->js_info.dwVpos : m_center[5];
        case 5: axes[4] = (m_os->js_caps.wCaps & JOYCAPS_HASU) ? (float)m_os->js_info.dwUpos : m_center[4];
        case 4: axes[3] = (m_os->js_caps.wCaps & JOYCAPS_HASR) ? (float)m_os->js_info.dwRpos : m_center[3];
        case 3: axes[2] = (m_os->js_caps.wCaps & JOYCAPS_HASZ) ? (float)m_os->js_info.dwZpos : m_center[2];
        case 2: axes[1] = (float)m_os->js_info.dwYpos;
        case 1: axes[0] = (float)m_os->js_info.dwXpos;
            break;

        default:
            break;
        }
    }
}

#elif defined(__APPLE__) || defined(__linux__)
#include <unistd.h>

Joypad::Joypad(int id)
{
    //TODO
}

void Joypad::Open()
{
    //TODO
}

void Joypad::Close()
{
    //TODO
}

void Joypad::RawRead(int *buttons, float *axes)
{
    //TODO
}

#elif defined(__linux__) || defined(__sgi) || defined(_AIX) || defined(SOLARIS) || defined(sun)
#include <unistd.h>
#include <dlfcn.h>
#include <fcntl.h>

#if (defined(__unix__) || defined(unix)) && !defined(USG)
#include <sys/param.h>
#endif

#endif

float Joypad::FudgeAxis(float value, int axis) const
{
    float result;

    if (value < m_center[axis])
    {
        result = (value - m_center[axis]) / (m_center[axis] - m_min[axis]);

        if (result < -m_saturate[axis])
        {
            return -1.0f;
        }

        if (result > -m_dead_band[axis])
        {
            return 0.0f;
        }

        result = (result + m_dead_band[axis]) / (m_saturate[axis] - m_dead_band[axis]);

        return (result < -1.0f) ? -1.0f : result;
    }

    result = (value - m_center[axis]) / (m_max[axis] - m_center[axis]);

    if (result > m_saturate[axis])
    {
        return 1.0f;
    }

    if (result < m_dead_band[axis])
    {
        return 0.0f;
    }

    result = (result - m_dead_band[axis]) / (m_saturate[axis] - m_dead_band[axis]);

    return (result > 1.0f) ? 1.0f : result;
}


void Joypad::Read(int *buttons, float *axes)
{
    if (Error())
    {
        if (buttons)
        {
            *buttons = 0;
        }

        if (axes)
        {
            for (int i = 0; i < m_num_axes; ++i)
            {
                axes[i] = 0.0f;
            }
        }

        return;
    }

    float raw_axes[MAX_AXES];

    RawRead(buttons, raw_axes);

    if (axes)
    {
        switch (m_num_axes)
        {
        case 8: axes[7] = FudgeAxis(raw_axes[7], 7);
        case 7: axes[6] = FudgeAxis(raw_axes[6], 6);
        case 6: axes[5] = FudgeAxis(raw_axes[5], 5);
        case 5: axes[4] = FudgeAxis(raw_axes[4], 4);
        case 4: axes[3] = FudgeAxis(raw_axes[3], 3);
        case 3: axes[2] = FudgeAxis(raw_axes[2], 2);
        case 2: axes[1] = FudgeAxis(raw_axes[1], 1);
        case 1: axes[0] = FudgeAxis(raw_axes[0], 0);
        }
    }
}
