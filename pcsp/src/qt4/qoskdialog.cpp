#include "stdafx.h"
#include "qoskdialog.h"

#include "hle/modules/utility/sceUtility.h"
#include "hle/modules/utility/sceUtilityOSK.h"

static int utf16cpy(u16 *target, u16 const *source, int max)
{
    int size = 0;
    if (!max)
    {
        max = SCE_UTILITY_OSK_MAX_LENGTH;
    }
    for (; *source && size < max; ++source)
    {
        *target++ = *source;
        size++;
    }
    if (size < max)
    {
        *target = 0;
    }
    return size;
}

static int utf16cmp(u16 *target, u16 const *source, int max)
{
    int size = 0;
    int result = 0;
    if (!max)
    {
        max = SCE_UTILITY_OSK_MAX_LENGTH;
    }
    for (; *source && size < max; ++source)
    {
        result = *target++ - *source;
        if (result)
        {
            break;
        }
        size++;
    }
    return result;
}

static int utf16len(u16 const *source)
{
    int size = 0;
    for (; *source && size < SCE_UTILITY_OSK_MAX_LENGTH; ++source)
    {
        size++;
    }
    return size;
}

QOskDialog::QOskDialog(QWidget *parent, SceUtilityOskParam *param)
:   QDialog(parent)
,   m_form_layout(new QFormLayout)
,   m_param(param)
{
    QString initial_text; 
    QString label;
    for (u32 i = 0; i < param->num_input_fields; ++i)
    {
        SceUtilityOskInputFieldInfo *ifi = Memory::addr< SceUtilityOskInputFieldInfo >(param->input_field_info + i);
        if (ifi)
        {
            if (ifi->init_text)
            {
                initial_text = QString::fromUtf16(Memory::addrhu(ifi->init_text));
            }
            else
            {
                initial_text.clear();
            }

            if (ifi->message)
            {
                label = QString::fromUtf16(Memory::addrhu(ifi->message));
            }
            else
            {
                label = "TYPE";
            }

            int n = ifi->num_lines;
            if (n < 2)
            {
                AddLineEdit(ifi, label, initial_text); 
            }
            else
            {
                AddPlainTextEdit(ifi, label, initial_text); 
            }
        }
    }
}

bool QOskDialog::Show()
{
    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);
    m_form_layout->addRow(buttons);
    connect(buttons, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttons, SIGNAL(rejected()), this, SLOT(reject()));
    setLayout(m_form_layout);
    bool result = exec() == QDialog::Accepted;
    m_param->base.result = 0;
    return result;
}

void QOskDialog::lineEdited()
{
    QLineEdit *widget = (QLineEdit *)sender();
    SceUtilityOskInputFieldInfo *ifi = m_ifi[widget];
    if (ifi)
    {
        QString result = widget->text();
        ifi->result_text_buffer_size = utf16cpy(Memory::addrhu(ifi->result_text_buffer), result.utf16(), min(ifi->result_text_buffer_size, SCE_UTILITY_OSK_MAX_LENGTH));  
        ifi->result                  = SCE_UTILITY_OSK_INPUT_FIELD_RESULT_EDITED;
    }
}

void QOskDialog::plainTextEdited(bool modified)
{
    QPlainTextEdit *widget = (QPlainTextEdit *)sender();
    if (widget)
    {
        SceUtilityOskInputFieldInfo *ifi = m_ifi[widget];
        if (ifi)
        {
            QString result = widget->toPlainText();
            ifi->result_text_buffer_size = utf16cpy(Memory::addrhu(ifi->result_text_buffer), result.utf16(), min(ifi->result_text_buffer_size, SCE_UTILITY_OSK_MAX_LENGTH));  
            ifi->result                  = modified ? SCE_UTILITY_OSK_INPUT_FIELD_RESULT_EDITED : SCE_UTILITY_OSK_INPUT_FIELD_RESULT_UNEDITED;
        }
    }
}

void QOskDialog::AddLineEdit(SceUtilityOskInputFieldInfo *ifi, QString const &label, QString const &initial_text)
{
    QLineEdit *widget = new QLineEdit(initial_text);
    m_form_layout->addRow(label, widget); 
    connect(widget, SIGNAL(editingFinished()), this, SLOT(lineEdited()));
    m_ifi[widget] = ifi;
}

void QOskDialog::AddPlainTextEdit(SceUtilityOskInputFieldInfo *ifi, QString const &label, QString const &initial_text)
{
    QPlainTextEdit *widget = new QPlainTextEdit(initial_text);
    QBoxLayout *layout = new QBoxLayout(QBoxLayout::TopToBottom);
    layout->addWidget(widget, ifi->num_lines);
    m_form_layout->addRow(label, layout); 
    connect(widget, SIGNAL(modificationChanged(bool)), this, SLOT(plainTextEdited(bool)));
    m_ifi[widget] = ifi;
}

void QOskDialog::reject()
{
    for (u32 i = 0; i < m_param->num_input_fields; ++i)
    {
        SceUtilityOskInputFieldInfo *ifi = Memory::addr< SceUtilityOskInputFieldInfo >(m_param->input_field_info + i);
        if (ifi)
        {
            ifi->result = SCE_UTILITY_OSK_INPUT_FIELD_RESULT_CANCELED;
        }
    }
    QDialog::reject();
}