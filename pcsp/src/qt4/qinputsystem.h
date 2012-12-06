#pragma once

#include <map>
#include <vector>
#include <QObject>
#include <QString>
#include <math.h>

#include "common/types.h"
#include "common/common_joypad.h"
#include "hle/modules/ctrl/sceCtrl.h"

class QBasicTimer;
class QTimerEvent;

class InputController
{
public:
    InputController() { ::memset(m_codemap, -1, sizeof(m_codemap)); Mirror(); }

    virtual void Update(unsigned int &UNUSED(buttons), unsigned char &UNUSED(lx), unsigned char &UNUSED(ly), bool UNUSED(amode)) {}

    void MapButton(int button, int code) { m_codemap[button] = code; }
    void MapAxis(bool axis, int code) { m_codemap[30+axis] = code; }
    int GetMappedButton(int button) { return m_codemap[button]; }
    int GetMappedAxis(int axis) { return m_codemap[30+axis]; }

    virtual bool IsButtonDown(int UNUSED(code)) { return false; }
    virtual float ReadAxis(int UNUSED(code)) { return 128.0f; }

    virtual bool IsKeyboard() const { return false; }
    virtual bool IsJoypad() const { return false; }

    void Mirror() { ::memcpy(m_savemap, m_codemap, sizeof(m_savemap)); }
    void Commit() { ::memcpy(m_savemap, m_codemap, sizeof(m_savemap)); }
    void Revert() { ::memcpy(m_codemap, m_savemap, sizeof(m_savemap)); }

    virtual QString GetTextButton(int UNUSED(code)) { return "<n/a>"; }
    virtual QString GetTextAxis(int UNUSED(code)) { return "<n/a>"; }

    QString const &GetName() const { return m_name; }
    QString const &GetHash() const { return m_hash; }

    void SetName(QString const &name) { m_name = name; }
    void SetHash(QString const &hash) { m_hash = hash; }

protected:
    void Update() {}

    QString	m_name;
    QString	m_hash;

    int m_codemap[32];
    int m_savemap[32];
};

class InputKeyboard
:   public InputController
{
public:
    InputKeyboard() { SetName("Keyboard"); }

    virtual void Update(unsigned int &UNUSED(buttons), unsigned char &UNUSED(lx), unsigned char &UNUSED(ly), bool UNUSED(amode));

    virtual bool IsKeyboard() const { return true; }

    virtual bool IsButtonDown(int code);

    virtual QString GetTextButton(int code);
};

class InputJoypad
:   public InputController
,   public Joypad
{
public:
    InputJoypad(int id = 0) : Joypad(id) { SetName(Joypad::GetName()); }

    virtual void Update(unsigned int &buttons, unsigned char &lx, unsigned char &ly, bool amode);

    virtual bool IsJoypad() const { return true; }

    virtual bool IsButtonDown(int code) { return m_buttons & (1 << code); }
    virtual float ReadAxis(int code) { return ceil(255.0f*(0.5f + m_axis[code]*0.5f)); }

    virtual QString GetTextButton(int code);
    virtual QString GetTextAxis(int code);

protected:
    int   m_buttons;
    float m_axis[MAX_AXES];
};


class QInputSystem
:   public QObject
{
    Q_OBJECT

public:
    QInputSystem();
    ~QInputSystem();

    void UpdateControllers();

    void Update(unsigned int &buttons, unsigned char &lx, unsigned char &ly, bool amode);

    inline InputController *GetController()	
    { 
        if (0 == m_current_controller)
        {
            AddDefaultKeyboard();
            m_current_controller = m_controllers[0];
        }

        return m_current_controller; 
    };

    QList< InputController * > &GetControllers() { return m_controllers; };

    bool KeyDown(int key);
    int GetFirstKey();

    QString GetTextButton(int code) { return GetController()->GetTextButton(code); }

    void WriteBufferKeyDown(int key);
    void WriteBufferKeyUp(int key);
    void DoneRead();

    void AddDefaultKeyboard();
    void AddFoundJoypads();

    void SetController(InputController *controller) { m_current_controller = controller; };
    void SetController(int i) { m_current_controller = m_controllers[i]; };

private:
    InputController           *m_current_controller;
    QList< InputController * > m_controllers;
    std::map< Qt::Key, bool >  m_key_state;
};

extern QInputSystem *theInputSystem;
