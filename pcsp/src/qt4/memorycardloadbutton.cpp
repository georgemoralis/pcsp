#include "stdafx.h"
#include "memorycardloadbutton.h"

memoryCardLoadButton::memoryCardLoadButton(QWidget *parent)
	: QPushButton(parent)
{
  templist= new QListWidgetItem();
  
}

memoryCardLoadButton::~memoryCardLoadButton()
{

}
void memoryCardLoadButton::enableLoadButton(QListWidgetItem *item)
{
   QPushButton::setEnabled(true);
   templist = item;
}
void memoryCardLoadButton::click()
{
   QString ebootfile = templist->data(Qt::UserRole).toString();
   theEmulator.SetNewGame(ebootfile);
}