#ifndef qoskdialog_h__
#define qoskdialog_h__

#include <QDialog>
#include <QFormLayout>
#include <QMap>
#include "modules/utility/sceUtilityOSK.h"

struct SceUtilityOskInputFieldInfo;

class QOskDialog : public QDialog
{
    Q_OBJECT

public:
    QOskDialog(QWidget *parent, SceUtilityOskParam *param);

    bool Show();

private slots:
    void lineEdited();
    void plainTextEdited(bool);
    void reject();

private:
    void AddLineEdit(SceUtilityOskInputFieldInfo *ifi, QString const &label, QString const &initial_text);
    void AddPlainTextEdit(SceUtilityOskInputFieldInfo *ifi, QString const &label, QString const &initial_text);

    QFormLayout                                     *m_form_layout;
    SceUtilityOskParam                              *m_param;
    QMap< QWidget *, SceUtilityOskInputFieldInfo * > m_ifi;
};

#endif // qoskdialog_h__
