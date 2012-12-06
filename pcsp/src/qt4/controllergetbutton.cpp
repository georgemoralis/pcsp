#include "stdafx.h"
#include "controllergetbutton.h"
#include <QTimer>
#include <QMessageBox>
#include <QKeyEvent>
#include "qinputsystem.h"

controllerGetButton::controllerGetButton(int button, QWidget *parent)
:   QDialog(parent)
,   m_button(button)
,   m_mask(0)
,   m_axis(-1)
{
    InputController *current_controller = theInputSystem->GetController();
    if (current_controller->IsJoypad())
    {
        InputJoypad *joypad = (InputJoypad *)current_controller;
        joypad->Read(&m_mask, 0);
    }
    ui.setupUi(this);
    startTimer(100);
}

controllerGetButton::controllerGetButton(int button, int axis, QWidget *parent)
:   QDialog(parent)
,   m_button(button)
,   m_mask(0)
,   m_axis(axis)
{
    InputController *current_controller = theInputSystem->GetController();
    if (current_controller->IsJoypad())
    {
        InputJoypad *joypad = (InputJoypad *)current_controller;
        joypad->Read(&m_mask, 0);
    }
    ui.setupUi(this);
    startTimer(100);
}

controllerGetButton::~controllerGetButton()
{
}

void controllerGetButton::keyPressEvent(QKeyEvent *event)
{
    int code = event->key();
    InputController *current_controller = theInputSystem->GetController();
    if (current_controller->IsKeyboard())
    {
        current_controller->MapButton(m_button, code);
        done(0);
    }
}

void controllerGetButton::timerEvent(QTimerEvent *UNUSED(event))
{
    InputController *current_controller = theInputSystem->GetController();
    if (current_controller->IsJoypad())
    {
        InputJoypad *joypad = (InputJoypad *)current_controller;
        int buttons;
        float axis[8];
        joypad->Read(&buttons, axis);
        for (int code = 0; code < joypad->GetNumButtons(); ++code)
        {
            if ((buttons & ~m_mask) & (1 << code))
            {
                current_controller->MapButton(m_button, code);
                done(0);
                return;
            }
        }
        if (m_axis >= 0)
        {
            for (int code = 0; code < joypad->GetNumAxes(); ++code)
            {
                if (fabs(axis[code]) == 1.0f)
                {
                    current_controller->MapAxis(m_axis, code);
                    done(0);
                    break;
                }
            }
        }
    }
}
