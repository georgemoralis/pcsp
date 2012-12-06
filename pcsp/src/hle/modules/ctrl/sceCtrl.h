#ifndef sceCtrl_h__
#define sceCtrl_h__

namespace sceCtrl
{
    extern bool Reboot();
    extern bool ShutDown();

    /* Index for the two analog directions */
#define CTRL_ANALOG_X   0
#define CTRL_ANALOG_Y   1

    /* Button bit masks */
#define SCE_CTRL_SELECT        0x00000001
#define SCE_CTRL_START         0x00000008
#define SCE_CTRL_UP            0x00000010
#define SCE_CTRL_RIGHT         0x00000020
#define SCE_CTRL_DOWN          0x00000040
#define SCE_CTRL_LEFT          0x00000080
#define SCE_CTRL_L             0x00000100
#define SCE_CTRL_R             0x00000200
#define SCE_CTRL_TRIANGLE      0x00001000
#define SCE_CTRL_CIRCLE        0x00002000
#define SCE_CTRL_CROSS         0x00004000
#define SCE_CTRL_SQUARE        0x00008000
#define SCE_CTRL_HOME          0x00010000
#define SCE_CTRL_HOLD          0x00020000
#define SCE_CTRL_SCREEN        0x00040000
#define SCE_CTRL_NOTE          0x00080000
#define SCE_CTRL_VOLUP         0x00100000
#define SCE_CTRL_VOLDOWN       0x00200000
#define SCE_CTRL_WLAN_UP       0x00400000
#define SCE_CTRL_REMOTE        0x00800000
#define SCE_CTRL_DISC          0x01000000
#define SCE_CTRL_MS            0x02000000

    //make fake defines for analog
#define SCE_CTRL_ANALOG_UP     0x04000000
#define SCE_CTRL_ANALOG_DOWN   0x08000000
#define SCE_CTRL_ANALOG_LEFT   0x10000000
#define SCE_CTRL_ANALOG_RIGHT  0x20000000

    /* sampling state */
#define SCE_CTRL_MODE_DIGITALONLY	0
#define SCE_CTRL_MODE_DIGITALANALOG 1

    /* Returned control data */
    typedef struct SceCtrlData 
    {
        unsigned int TimeStamp;
        unsigned int Buttons;
        unsigned char Lx;
        unsigned char Ly;
        unsigned char Rsrv[6];
    } SceCtrlData;

    /* returned Latch data */
    typedef struct SceCtrlLatch 
    {
        unsigned int uiMake;
        unsigned int uiBreak;
        unsigned int uiPress;
        unsigned int uiRelease;
    } SceCtrlLatch;

    // Sampling modes
#define SCE_CTRL_MODE_DIGITALONLY	0
#define SCE_CTRL_MODE_DIGITALANALOG 1
    extern int sceCtrlGetSamplingMode(); 
    extern int sceCtrlPeekBufferNegative(); 
    extern int sceCtrlPeekLatch(); 
    extern int sceCtrl_AF5960F3(); 
    extern int sceCtrlSetIdleCancelThreshold(); 
    extern int sceCtrlClearRapidFire(); 
    extern int sceCtrlSetSamplingCycle(); 
    extern int sceCtrlGetIdleCancelThreshold(); 
    extern int sceCtrlSetRapidFire(); 
    extern int sceCtrlReadBufferNegative(); 
    extern int sceCtrlPeekBufferPositive(); 
    extern int sceCtrl_348D99D4(); 
    extern int sceCtrlReadBufferPositive(); 
    extern int sceCtrlSetSamplingMode(); 
    extern int sceCtrlReadLatch(); 
    extern int sceCtrlGetSamplingCycle(); 
}

#endif // sceCtrl_h__
