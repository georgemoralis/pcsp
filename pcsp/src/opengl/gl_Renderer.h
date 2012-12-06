#if 0
#pragma once

#define USE_SHADERS

#include "hle/modules/ge/ge_Matrix.h"
#include "hle/modules/ge/ge_Decoder.h"
#include "hle/modules/ge/ge_TextureDecoder.h"
#include "hle/modules/ge/ge_Constants.h"
#include "hle/modules/ge/ge_Types.h"

class gl_Renderer
{
public:
    gl_Renderer();
    ~gl_Renderer();

    bool            SaveScreenshot;
    void            saveImageToFile();
    bool			Initialize();
    void			Terminate();
    DeviceCaps		CheckDeviceCapabilities();

    void			Swap();
    bool			CalcFps();

    void            CalcSkinningPosition(float v[3], ge_DecodedVertex &outDecodedVertice);
    void            CalcSkinningNormal(float v[3], ge_DecodedVertex &outDecodedVertice);

    void			DrawArray(ge_VertexInfo &inInfo, u32 inType , u32 inCount, bool inRepeatDraw);
    void			DrawBezier(ge_VertexInfo &inInfo, u32 inUCount, u32 inVCount, bool inRepeatDraw);
    void			DrawSpline(ge_VertexInfo &inInfo, u32 inUCount, u32 inVCount, u32 inUFlag, u32 inVFlag, bool inRepeatDraw);

    void            SetTexFunc(u32, u32, u32);


    void			SetAmbientModelLight(float *inModel);
    void			SetEmmisiveModelLight(float *inModel);

    void			SetQuadricAtten(int inLight, float inData);
    void			SetLinearAtten(int inLight, float inData);
    void			SetConstantAtten(int inLight, float inData);

    void			SetLightColorAmbient(int inLight, float *inData);
    void			SetLightColorDiffuse(int inLight, float *inData);
    void			SetLightColorSpecular(int inLight, float *inData);
    void			SetSpecularPower(float *inPower);
    void			SetShadeModel(u32 inData);

    void			SetScissorTest(bool	inEnable);
    void			SetScissoringArea(u16 inScissor[4]);
    void            UpdateScissoringArea();

    void			SetCullDir(bool inDir);

    void			SetAlphaTest(int inFunc, int inRef);

    void			SetColorMask(bool inData[4]);

    void            SetDrawingRegion(u16 inRegion[4]);

    void            CullObject(ge_VertexInfo &inInfo, u32 inCount);
    bool            IsObjectCulled();

    inline float	GetLastFrameTime() { return mLastFrameTime; }
    inline float	GetCurrentFps() { return mCurrentFps; }

protected:
    template< bool tm, bool cm, bool ce, bool te >
    void BeginDraw(ge_VertexInfo* inInfo, u32 inType);
    template< bool tm, bool ce, bool te, bool we, bool ne >
    void Draw(ge_VertexInfo* inInfo, ge_DecodedVertex* outDecodedVertices, u32 inType, u32 inCount);
    template< bool tm, bool cm, bool ce, bool te >
    void EndDraw(ge_VertexInfo* inInfo, u32 inType);

    void DrawPrimitives(ge_VertexInfo &inInfo, ge_DecodedVertex *outDecodedVertices, u32 inType, u32 inCount, bool inRepeatDraw);
    void DrawPatches(ge_VertexInfo &inInfo, ge_DecodedVertex *outDecodedVertices, u32 inCount, bool inRepeatDraw);

    int texture_projection_map_mode;

private:
    u32         mVertexFlags;
    u32         mPixelFlags;
};
#endif