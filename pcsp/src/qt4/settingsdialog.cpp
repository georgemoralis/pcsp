#include "stdafx.h"
#include "settingsdialog.h"
#include "settings.h"

settingsDialog::settingsDialog(QWidget *parent)
: QDialog(parent)
{
    ui.setupUi(this);

    QListWidgetItem *videoButton = new QListWidgetItem(ui.optionsList);
    videoButton->setIcon(QIcon(":/../../Resources/Resources/video48x48.png"));
    videoButton->setText("Video Settings");
    videoButton->setTextAlignment(Qt::AlignHCenter);
    videoButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *soundButton = new QListWidgetItem(ui.optionsList);
    soundButton->setIcon(QIcon(":/../../Resources/Resources/sound48x48.png"));
    soundButton->setText("Sound Settings");
    soundButton->setTextAlignment(Qt::AlignHCenter);
    soundButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *memcardButton = new QListWidgetItem(ui.optionsList);
    memcardButton->setIcon(QIcon(":/../../Resources/Resources/memcard48x48.png"));
    memcardButton->setText("Stick Settings");
    memcardButton->setTextAlignment(Qt::AlignHCenter);
    memcardButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

	QListWidgetItem *hacksButton = new QListWidgetItem(ui.optionsList);
    hacksButton->setIcon(QIcon(":/../../Resources/Resources/settings48x48.png"));
    hacksButton->setText("Hack Settings");
    hacksButton->setTextAlignment(Qt::AlignHCenter);
    hacksButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    ui.optionsList->setCurrentRow(0);//always make sure it will start from first page
    if (settings.mDisableMemStick)
    {
        ui.disableMemStickCheck->setChecked(true);
    }
    if (settings.mEnableShaders)
    {
        ui.enableShadersCheck->setChecked(true);
    }
	if (!settings.mSoundBufferCount)
	{
        ui.SoundBufferSizeSlider->setValue(0);//default value
	}
	else
	{
       ui.SoundBufferSizeSlider->setValue(settings.mSoundBufferCount);
	}
	if(settings.mMuteSound)
	{
		ui.muteAudioCheckBox->setChecked(true);
	}
	if(settings.mHackDisableAudioFunctions)
	{
		ui.disableAudioFucCheckBox->setChecked(true);
	}
	if(settings.mEnableDecryptor)
	{
        ui.decryptorcheckBox->setChecked(true);
	}
}

settingsDialog::~settingsDialog()
{

}
void settingsDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    ui.pagesWidget->setCurrentIndex(ui.optionsList->row(current));
}

void settingsDialog::SaveAction()
{
    if (ui.disableMemStickCheck->isChecked())
    {
        settings.mDisableMemStick = true;
        settings.SaveSettings();

    }
    else
    {
        settings.mDisableMemStick = false;
        settings.SaveSettings();
    }

    if (ui.enableShadersCheck->isChecked())
    {
        settings.mEnableShaders = true;
        settings.SaveSettings();

    }
    else
    {
        settings.mEnableShaders = false;
        settings.SaveSettings();
    }
	if(ui.muteAudioCheckBox->isChecked())
	{
		settings.mMuteSound=true;
		settings.SaveSettings();
	}
	else
	{
		settings.mMuteSound=false;
		settings.SaveSettings();
	}
	if(ui.disableAudioFucCheckBox->isChecked())
	{
      settings.mHackDisableAudioFunctions=true;
	  settings.SaveSettings();
	}
	else
	{
      settings.mHackDisableAudioFunctions=false;
	  settings.SaveSettings();
	}
	if(ui.decryptorcheckBox->isChecked())
	{
      settings.mEnableDecryptor=true;
	  settings.SaveSettings();
	}
	else
	{
      settings.mEnableDecryptor=false;
	  settings.SaveSettings();
	}
	settings.mSoundBufferCount = ui.SoundBufferSizeSlider->value();
	settings.SaveSettings();

    close();
}
void settingsDialog::CancelAction()
{
    close();
}
void settingsDialog::soundBufferDefault()
{
	ui.SoundBufferSizeSlider->setValue(2);
}