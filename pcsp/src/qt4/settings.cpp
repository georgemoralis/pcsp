#include "stdafx.h"
#include "settings.h"
#include <QFile>
#include <QtXml/QDomDocument>
#include <QTextStream>
#include <QMapIterator>
#include "qinputsystem.h"

extern bool use_shaders;

Settings settings;

Settings::Settings()
:   mEnableShaders(use_shaders)
{
}

Settings::~Settings()
{
}

int Settings::LoadSettings()
{
    QFile        file("settings.xml");
    QDomDocument document("Configure");

    if (!file.open(QIODevice::ReadOnly))
    {
        return -1;
    }
    
    bool isContentSet = document.setContent(&file);
    
    file.close();
    
    if (!isContentSet)
    {
        return -2;
    }
    
    return ReadXmlData(document);
}

int Settings::ReadXmlData(QDomDocument &document)
{
    QDomElement root = document.documentElement();

    if (root.tagName() != "settings")
    {
        return -3;	
    }

    QDomNode node = root.firstChild();
    
    while (!node.isNull())
    {
        QDomElement element = node.toElement();

        QString tagname = element.tagName();

        if (tagname == "general")
        {
            ReadGeneral(element);
        }
        else if (tagname == "controllers")
        {
            ReadController(element);
        }
        else if (tagname == "logging")
        {
            ReadLogging(element);
        }
        node = node.nextSibling();
    }

    return true;
}

void Settings::ReadGeneral(QDomElement &element)
{
    mAutoRun                   = QVariant(element.attribute("AutoRun")           ).toBool();
    mAlwaysOnTop               = QVariant(element.attribute("AlwaysOnTop")       ).toBool();
    mVsyncLimiter              = QVariant(element.attribute("VsyncLimiter")      ).toBool();
    mLogWindowShow             = QVariant(element.attribute("LogWindowShow")     ).toBool();
    mDisableMemStick           = QVariant(element.attribute("DisableMemStick")   ).toBool();
    mEnableShaders             = QVariant(element.attribute("EnableShaders")     ).toBool();
    mLastOpenFile              = QVariant(element.attribute("LastOpenFile")      ).toString();
    mLastOpenUMD               = QVariant(element.attribute("LastOpenUMD")       ).toString();
    mMemcardPath               = QVariant(element.attribute("MemCardPath")       ).toString();
    mSoundBufferCount          = QVariant(element.attribute("SoundBuffer")       ).toInt();
    mMuteSound                 = QVariant(element.attribute("MuteSound")         ).toBool();
    mHackDisableAudioFunctions = QVariant(element.attribute("HackDisableAudFunc")).toBool();
    mEnableDecryptor           = QVariant(element.attribute("EnableDecryptor")   ).toBool();
    mFullscreen                = QVariant(element.attribute("Fullscreen")        ).toBool();
}

void Settings::ReadController(QDomElement &element)
{
    QDomNode node = element.firstChild();

    while (!node.isNull())
    {
        QDomElement element = node.toElement();
        QString     tagname = element.tagName();

        if (tagname.compare("controller", Qt::CaseInsensitive))
        {
            qFatal("xml parsing failed: ReadController");
        }

        bool is_keyboard  = QVariant(element.attribute("keyboard")).toBool();
        bool is_current   = QVariant(element.attribute("current") ).toBool();

        InputController *controller = 0;

        if (is_keyboard)
        {
            controller = new InputKeyboard;
        }
        else
        {
            int id = element.attribute("joypad").toInt();
            controller = new InputJoypad(id);
            if (((InputJoypad *)controller)->Error())
            {
                delete controller;
                controller = 0;
            }
        }

        if (controller)
        {
            QString name = element.attribute("name");
            QString hash = element.attribute("hash");
            if (controller->GetName() == name && controller->GetHash() == hash)
            {
                //controller->SetName(theElement.attribute("name"));
                //controller->SetHash(theElement.attribute("hash"));

                if (element.elementsByTagName("mapping").size() > 1)
                {
                    qFatal("xml parsing failed: mapping");
                }

                QDomNode mapping_node  = element.elementsByTagName("mapping").item(0).firstChild();
                while (!mapping_node.isNull())
                {
                    QDomElement cur_mapping = mapping_node.toElement();
                    u32 code = cur_mapping.attribute("code", "-1").toUInt(0, 16);
                    if (cur_mapping.hasAttribute("button"))
                    {
                        u32 button = cur_mapping.attribute("button").toUInt();
                        controller->MapButton(button, code);
                    }
                    else if (cur_mapping.hasAttribute("axis"))
                    {
                        bool axis = cur_mapping.attribute("axis").toUInt() == 1;
                        controller->MapAxis(axis, code);
                    }
                    mapping_node = mapping_node.nextSibling();
                }

                theInputSystem->GetControllers().push_back(controller);

                if (is_current)
                {
                    theInputSystem->SetController(controller);
                }
            }
        }

        node = node.nextSibling();
    }
}

void Settings::ReadLogging(QDomElement &element)
{
    QDomNamedNodeMap attributeMap = element.attributes();
    for (int i = 0; i < attributeMap.count(); ++i) 
    {
        QDomNode attribute      = attributeMap.item(i);
        QString  attributename  = attribute.nodeName();
        int      attributevalue = attribute.nodeValue().toInt();
        
        logmap.insert(attributename, attributevalue);
    }

}
void Settings::LoadLoggingConfig(QString const &name, u32 &level)
{
    if (logmap.contains(name))
    {
        level = logmap.value(name);
    }
}
int Settings::SaveSettings()
{
    QFile        file("settings.xml");
    QDomDocument document("Configure");
    
    WriteXmlData(document);

    if (!file.open(QIODevice::WriteOnly))
    {
        return -1;
    }

    QTextStream text_stream(&file);
    text_stream << document.toString();
    file.close();

    return 1; 
}

int Settings::WriteXmlData(QDomDocument &document)
{
    QDomElement root        = document.createElement("settings");
    QDomElement general     = document.createElement("general");
    QDomElement controllers = document.createElement("controllers");
    QDomElement logging     = document.createElement("logging");

    WriteGeneral(general);
    WriteController(controllers, document);
    WriteLog(logging);

    document.appendChild(root);

    root.appendChild(general);
    root.appendChild(controllers);
    root.appendChild(logging);

    return true;
}

void Settings::WriteController(QDomElement &element, QDomDocument &document)
{
    QList< InputController * > &controllers = theInputSystem->GetControllers();
    foreach (InputController *input, controllers)
    {
        QDomElement controller = document.createElement("controller");
        element.appendChild(controller);

        bool is_current_controller = false;
        if (input == theInputSystem->GetController())
        {
            is_current_controller = true;
        }

        controller.setAttribute("name",     input->GetName());
        controller.setAttribute("hash",     input->GetHash());
        controller.setAttribute("current",  (is_current_controller ? "true" : "false"));
        controller.setAttribute("keyboard", (input->IsKeyboard() ? "true" : "false"));
        if (input->IsJoypad())
        {
            controller.setAttribute("joypad", QString("%1").arg(((InputJoypad *)input)->GetId()));
        }

        QDomElement mapping = document.createElement("mapping");
        for (int button = 0; button < 32; ++button)
        {
            int code = input->GetMappedButton(button);
            QDomElement map = document.createElement("map");
            map.setAttribute("button", QString("%1").arg(u32(button), 2, 10));
            map.setAttribute("code",   QString("%1").arg(u32(code), 8, 16, QLatin1Char('0')));
            map.setAttribute("text",   input->GetTextButton(code));
            mapping.appendChild(map);
        }
        for (int axis = 0; axis < 2; ++axis)
        {
            int code = input->GetMappedAxis(axis);
            QDomElement map = document.createElement("map");
            map.setAttribute("axis", QString("%1").arg(u32(axis), 1, 10));
            map.setAttribute("code", QString("%1").arg(u32(code), 8, 16, QLatin1Char('0')));
            map.setAttribute("text", input->GetTextAxis(code));
            mapping.appendChild(map);
        }
        controller.appendChild(mapping);
    }
}

void Settings::WriteGeneral(QDomElement &element)
{
    element.setAttribute("AutoRun",		       mAutoRun                   ? "true" : "false");
    element.setAttribute("AlwaysOnTop",	       mAlwaysOnTop               ? "true" : "false");
    element.setAttribute("VsyncLimiter",	   mVsyncLimiter              ? "true" : "false");
    element.setAttribute("LogWindowShow",	   mLogWindowShow             ? "true" : "false");
    element.setAttribute("DisableMemStick",    mDisableMemStick           ? "true" : "false");
    element.setAttribute("EnableShaders",      mEnableShaders             ? "true" : "false");
    element.setAttribute("LastOpenFile",       mLastOpenFile);
    element.setAttribute("LastOpenUMD",        mLastOpenUMD);
    element.setAttribute("MemCardPath",        mMemcardPath);
    element.setAttribute("SoundBuffer",        mSoundBufferCount);
    element.setAttribute("MuteSound",          mMuteSound                 ? "true" : "false");
    element.setAttribute("HackDisableAudFunc", mHackDisableAudioFunctions ? "true" : "false");
    element.setAttribute("EnableDecryptor",    mEnableDecryptor           ? "true" : "false");
    element.setAttribute("Fullscreen",         mFullscreen                ? "true" : "false");
}

void Settings::WriteLog(QDomElement &element)
{
    QMapIterator< QString, int > i(logmap);
    while (i.hasNext()) 
    {
        i.next();
        element.setAttribute(i.key(), i.value());
    }
}

void Settings::SaveLogConfig(int index, const QString &name)
{
    logmap.insert(name, index);
}
