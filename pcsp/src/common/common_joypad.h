#ifndef common_joypad_h__
#define common_joypad_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Joypad
{
    friend struct JoypadOsSpecific;

public:
    enum 
    {
        MAX_AXES    = 16,
        MAX_BUTTONS = 32,
        MAX_HATS    = 4
    };

protected:
    struct JoypadOsSpecific *m_os;

    int   m_id;
    bool  m_error;
    char  m_name[128];
    int   m_num_axes;
    int   m_num_buttons;

    float m_dead_band[MAX_AXES];
    float m_saturate[MAX_AXES];
    float m_center[MAX_AXES];
    float m_max[MAX_AXES];
    float m_min[MAX_AXES];

    void  Open();
    void  Close();

    float FudgeAxis(float value, int axis)  const;

public:

    Joypad(int id = 0);
    ~Joypad() { Close (); }

    int         GetId         () const                { return m_id; }
    const char *GetName       () const                { return m_name; }
    int         GetNumAxes    () const                { return m_num_axes; }
    int         GetNumButtons () const                { return m_num_buttons; }
    bool        Error         () const                { return m_error; }
    void        SetError      ()                      { m_error = true; }

    float       GetDeadBand   (int axis) const        { return m_dead_band[axis]; }
    void        SetDeadBand   (int axis, float value) { m_dead_band[axis] = value; }

    float       GetSaturation (int axis) const        { return m_saturate[axis]; }
    void        SetSaturation (int axis, float value) { m_saturate[axis] = value; }

    void        SetMinRange   (float *axes)           { ::memcpy(m_min   , axes, m_num_axes * sizeof(float)); }
    void        SetMaxRange   (float *axes)           { ::memcpy(m_max   , axes, m_num_axes * sizeof(float)); }
    void        SetCenter     (float *axes)           { ::memcpy(m_center, axes, m_num_axes * sizeof(float)); }

    void        GetMinRange   (float *axes) const     { ::memcpy(axes, m_min   , m_num_axes * sizeof(float)); }
    void        GetMaxRange   (float *axes) const     { ::memcpy(axes, m_max   , m_num_axes * sizeof(float)); }
    void        GetCenter     (float *axes) const     { ::memcpy(axes, m_center, m_num_axes * sizeof(float)); }

    void        Read(int *buttons, float *axes);
    void        RawRead(int *buttons, float *axes);
};

#endif // common_joypad_h__

