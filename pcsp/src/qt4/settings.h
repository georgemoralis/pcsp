#pragma once
#include <QtXml/QDomDocument>
#include <QFile>
#include <QMap>



class Settings
{    
public:
	Settings();
	~Settings();

    QMap<QString, int> logmap;

public:
    int LoadSettings();
	int SaveSettings();

	int ReadXmlData(QDomDocument &document);
	int WriteXmlData(QDomDocument &document);

	void WriteController(QDomElement &element, QDomDocument &document);
	void ReadController(QDomElement &element);

	void WriteGeneral(QDomElement &element);
	void ReadGeneral(QDomElement &element);

	void ReadLogging(QDomElement &element);
    void WriteLog(QDomElement &element);

    void LoadLoggingConfig(QString const &name, u32 &level);
	void SaveLogConfig(int index, const QString &name);

	bool          mAutoRun;	
	bool          mAlwaysOnTop;
	bool          mLogWindowShow;
	QString       mLastOpenFile;
	QString       mLastOpenUMD;
	QString       mMemcardPath;
    bool          mDisableMemStick;
    bool         &mEnableShaders;
	
    volatile bool mVsyncLimiter;
    volatile int  mSoundBufferCount;
	volatile bool mMuteSound;
	volatile bool mHackDisableAudioFunctions;
	volatile bool mEnableDecryptor;
    volatile bool mFullscreen;
};

extern Settings settings;
