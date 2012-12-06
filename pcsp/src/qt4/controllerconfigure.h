#ifndef CONTROLLERCONFIGURE_H
#define CONTROLLERCONFIGURE_H

#include <QDialog>
#include "ui_controllerconfigure.h"

class controllerConfigure : public QDialog
{
	Q_OBJECT

public:
	controllerConfigure(QWidget *parent = 0);
	~controllerConfigure();

	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

    void update_devices();
    void update_buttons();
    void check_clicked_button(int button);
    void check_clicked_axis(int button, int axis);

    void Revert();
    void Commit();
private slots:
	void click_button_L1();
	void click_button_L2();
	
	void click_button_up();
	void click_button_down();
	void click_button_left();
	void click_button_right();

	void click_button_Aup();
	void click_button_Adown();
	void click_button_Aleft();
	void click_button_Aright();

	void click_button_square();
	void click_button_triangle();
	void click_button_circle();
	void click_button_cross();
	
	void click_button_home();
	void click_button_select();
	void click_button_start();

	void click_button_save();
	void click_button_cancel();
	
    void changeDevice(int device);

private:
	Ui::controllerConfigureClass ui;

    QToolButton *mButtonToQToolButton[32];
    QToolButton *mAxisToQToolButton[2][2];
};

#endif // CONTROLLERCONFIGURE_H
