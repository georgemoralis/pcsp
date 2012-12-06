#ifndef sc_thread_h__
#define sc_thread_h__

#include "hle/kernel/kernel_timer.h"
#include "common_fiber.h"

using namespace std;

struct SceUtilityOskParam;
struct SceUtilityMsgDialogParam;
struct SceUtilitySavedataParam;

class sc_Thread
:   public JoinableThread
{
    friend class Emulator;
    template< typename Derived >
    friend class EmulatorFiber;

#ifdef QT_CORE_LIB
    Q_OBJECT
#endif

public:
    sc_Thread();
    ~sc_Thread();

    void Run();
#ifdef QT_CORE_LIB
    void Critical(QString const &caption, QString const &message) { EmitCritical(caption, message); }
    void Warning(QString const &caption, QString const &message)  { EmitWarning(caption, message); }
    void Osk(SceUtilityOskParam *param);
	void SavedataSave(SceUtilitySavedataParam *param);
	void SavedataLoad(SceUtilitySavedataParam *param);
    void MsgDialog(SceUtilityMsgDialogParam *param);
private:
    void ConnectSignals() const;
    void DisconnectSignals();

signals:
    void EmitCritical(QString const &caption, QString const &message);
    void EmitWarning(QString const &caption, QString const &message);

    void EmitOsk(SceUtilityOskParam *param);
	void EmitSavedataSave(SceUtilitySavedataParam *param);
	void EmitSavedataLoad(SceUtilitySavedataParam *param);
    void EmitMsgDialog(SceUtilityMsgDialogParam *param);

    void EmitShutDown();
#endif
};
#endif // sc_thread_h__
