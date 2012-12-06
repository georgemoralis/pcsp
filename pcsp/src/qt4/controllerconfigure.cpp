#include "stdafx.h"
#include "controllerconfigure.h"
#include "controllergetbutton.h"
#include <QTimer>
#include <QMessageBox>
#include <QKeyEvent>
#include "qinputsystem.h"



controllerConfigure::controllerConfigure(QWidget *parent)
:   QDialog(parent)
{
	ui.setupUi(this);


	//QTimer *timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(update_devices()));
    //timer->start(2000);	
	
	// make sure we add default keyboard if we did not already load the keyb
	// todo: remove this.
	theInputSystem->UpdateControllers();
	
	update_devices();
	Commit();
	update_buttons();
}

void controllerConfigure::keyPressEvent(QKeyEvent *event)
{
	theInputSystem->WriteBufferKeyDown(event->key());
}

void controllerConfigure::keyReleaseEvent(QKeyEvent * event)
{
	theInputSystem->WriteBufferKeyUp(event->key());
}

controllerConfigure::~controllerConfigure()
{
}

void controllerConfigure::click_button_L1()
{
	check_clicked_button(8);
}

void controllerConfigure::click_button_L2()
{
	check_clicked_button(9);
}

void controllerConfigure::click_button_up()
{
	check_clicked_button(4);
}

void controllerConfigure::click_button_down()
{
	check_clicked_button(6);
}

void controllerConfigure::click_button_left()
{
	check_clicked_button(7);
}

void controllerConfigure::click_button_right()
{
	check_clicked_button(5);
}

void controllerConfigure::click_button_Aup()
{
    check_clicked_axis(26, 1);
}

void controllerConfigure::click_button_Adown()
{
    check_clicked_axis(27, 1);
}

void controllerConfigure::click_button_Aleft()
{
    check_clicked_axis(28, 0);
}

void controllerConfigure::click_button_Aright()
{
    check_clicked_axis(29, 0);
}

void controllerConfigure::click_button_square()
{
	check_clicked_button(15);
}

void controllerConfigure::click_button_triangle()
{
	check_clicked_button(12);
}

void controllerConfigure::click_button_circle()
{
	check_clicked_button(13);
}

void controllerConfigure::click_button_cross()
{
	check_clicked_button(14);
}

void controllerConfigure::click_button_home()
{
	check_clicked_button(16);
}

void controllerConfigure::click_button_select()
{
	check_clicked_button(0);
}

void controllerConfigure::click_button_start()
{
	check_clicked_button(3);
}

//mButtonToQToolButton[ 0 /* SELECT     */] = ui.button_select;
//mButtonToQToolButton[ 3 /* START      */] = ui.button_start;
//mButtonToQToolButton[16 /* HOME       */] = ui.button_home;
//mButtonToQToolButton[17 /* HOLD       */] = ui.button_hold;
//mButtonToQToolButton[18 /* SCREEN     */] = ui.button_screen;
//mButtonToQToolButton[19 /* NOTE       */] = ui.button_soundtoggle;
//mButtonToQToolButton[20 /* VOLUP      */] = ui.button_soundplus;
//mButtonToQToolButton[21 /* VOLDOWN    */] = ui.button_soundmin;
//

void controllerConfigure::check_clicked_button(int button)
{
    theInputSystem->GetController();

    controllerGetButton *getButton = new controllerGetButton(button, this);
    getButton->exec();

    // have to delete otherwise the window still exists
    safe_delete(getButton);

    update_buttons();
}

void controllerConfigure::check_clicked_axis(int button, int axis)
{
    theInputSystem->GetController();

    controllerGetButton* getButton = new controllerGetButton(button, axis, this);
    getButton->exec();

    // have to delete otherwise the window still exists
    safe_delete(getButton);

    update_buttons();
}

void controllerConfigure::update_buttons()
{
	ui.button_up->setText("<None>");
	ui.button_down->setText("<None>");
	ui.button_left->setText("<None>");
	ui.button_right->setText("<None>");
	ui.button_x->setText("<None>");
	ui.button_o->setText("<None>");
	ui.button_triangle->setText("<None>");
	ui.button_square->setText("<None>");
	ui.button_L1->setText("<None>");
	ui.button_R1->setText("<None>");
	ui.button_start->setText("<None>");
	ui.button_select->setText("<None>");
	ui.button_home->setText("<None>");
	ui.button_hold->setText("<None>");
	ui.button_AnalogDown->setText("<None>");
	ui.button_AnalogLeft->setText("<None>");
	ui.button_AnalogRight->setText("<None>");
	ui.button_AnalogUp->setText("<None>");

    InputController *current_controller = theInputSystem->GetController();

    if (current_controller)
    {
        mButtonToQToolButton[ 0 /* SELECT     */] = ui.button_select;
        mButtonToQToolButton[ 1                 ] = 0;
        mButtonToQToolButton[ 2                 ] = 0;
        mButtonToQToolButton[ 3 /* START      */] = ui.button_start;
        mButtonToQToolButton[ 4 /* DPAD UP    */] = ui.button_up;
        mButtonToQToolButton[ 5 /* DPAD RIGHT */] = ui.button_right;
        mButtonToQToolButton[ 6 /* DPAD DOWN  */] = ui.button_down;
        mButtonToQToolButton[ 7 /* DPAD LEFT  */] = ui.button_left;
        mButtonToQToolButton[ 8 /* L          */] = ui.button_L1;
        mButtonToQToolButton[ 9 /* R          */] = ui.button_R1;
        mButtonToQToolButton[10                 ] = 0;
        mButtonToQToolButton[11                 ] = 0;
        mButtonToQToolButton[12 /* TRIANGLE   */] = ui.button_triangle;
        mButtonToQToolButton[13 /* CIRCLE     */] = ui.button_o;
        mButtonToQToolButton[14 /* CROSS      */] = ui.button_x;
        mButtonToQToolButton[15 /* SQUARE     */] = ui.button_square;
        mButtonToQToolButton[16 /* HOME       */] = ui.button_home;
        mButtonToQToolButton[17 /* HOLD       */] = ui.button_hold;
        mButtonToQToolButton[18 /* SCREEN     */] = ui.button_screen;
        mButtonToQToolButton[19 /* NOTE       */] = ui.button_soundtoggle;
        mButtonToQToolButton[20 /* VOLUP      */] = ui.button_soundplus;
        mButtonToQToolButton[21 /* VOLDOWN    */] = ui.button_soundmin;
        mButtonToQToolButton[22                 ] = 0;
        mButtonToQToolButton[23                 ] = 0;
        mButtonToQToolButton[24                 ] = 0;
        mButtonToQToolButton[25                 ] = 0;
        mButtonToQToolButton[26 /* APAD_UP    */] = current_controller->IsKeyboard() ? ui.button_AnalogUp    : 0;
        mButtonToQToolButton[27 /* APAD_DOWN  */] = current_controller->IsKeyboard() ? ui.button_AnalogDown  : 0;
        mButtonToQToolButton[28 /* APAD_LEFT  */] = current_controller->IsKeyboard() ? ui.button_AnalogLeft  : 0;
        mButtonToQToolButton[29 /* APAD_RIGHT */] = current_controller->IsKeyboard() ? ui.button_AnalogRight : 0;
        mButtonToQToolButton[30                 ] = 0;
        mButtonToQToolButton[31                 ] = 0;

        mAxisToQToolButton[0][0] = current_controller->IsJoypad() ? ui.button_AnalogLeft  : 0;
        mAxisToQToolButton[0][1] = current_controller->IsJoypad() ? ui.button_AnalogRight : 0;
        mAxisToQToolButton[1][0] = current_controller->IsJoypad() ? ui.button_AnalogUp    : 0;
        mAxisToQToolButton[1][1] = current_controller->IsJoypad() ? ui.button_AnalogDown  : 0;

        for (int button = 0; button < 30; ++button)
        {
            int code = current_controller->GetMappedButton(button);

            QToolButton *tool_button = mButtonToQToolButton[button];
            if (tool_button)
            {
                tool_button->setText(current_controller->GetTextButton(code));
            }
        }

        for (int axis = 0; axis < 2; ++axis)
        {
            int code = current_controller->GetMappedAxis(axis);

            for (int i = 0; i < 2; ++i)
            {
                QToolButton *tool_button = mAxisToQToolButton[axis][i];
                if (tool_button)
                {
                    tool_button->setText(current_controller->GetTextAxis(code));
                }
            }
        }
    }
}

void controllerConfigure::update_devices()
{
	ui.comboBox->clear();
    foreach(InputController *controller, theInputSystem->GetControllers())
	{
        if (controller->IsKeyboard() || !((InputJoypad *)controller)->Error())
        {
            ui.comboBox->addItem(QIcon(QString(":/controllers/%1.png").arg(controller->IsKeyboard() ? "keyboard" : "joypad")), controller->GetName(), qVariantFromValue((void*)controller));
        }
	}

    int index = ui.comboBox->findData(qVariantFromValue((void *)theInputSystem->GetController()));
    if (index >= 0)
    {
        ui.comboBox->setCurrentIndex(index);
    }
}

void controllerConfigure::Revert()
{
    foreach(InputController *controller, theInputSystem->GetControllers())
    {
        controller->Revert();
    }
}

void controllerConfigure::Commit()
{
    foreach(InputController *controller, theInputSystem->GetControllers())
    {
        controller->Commit();
    }
}

void controllerConfigure::click_button_save()
{
	Commit();
	close();
}
	
void controllerConfigure::click_button_cancel()
{
    Revert();
    close();
}

void controllerConfigure::changeDevice(int device)
{
    theInputSystem->SetController(device);
    update_buttons();
}
