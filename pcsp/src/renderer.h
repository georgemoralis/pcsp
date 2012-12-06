#ifndef renderer_h__
#define renderer_h__

#define USE_SHADERS last_use_shaders

#include "hle/modules/ge/ge_Matrix.h"
#include "hle/modules/ge/ge_Decoder.h"
#include "hle/modules/ge/ge_TextureDecoder.h"
#include "hle/modules/ge/ge_Constants.h"
#include "hle/modules/ge/ge_Types.h"

#include "opengl/gl_Core.h"

class theVertexBufferObject;
class IndexBufferObject;

class Renderer
:   public gl_Core
{
public:
	Renderer();
	~Renderer();

	bool            SaveScreenshot;
    bool            UseShaders;

	bool			Initialize();
	void			Terminate();

	void			Swap();
	bool			CalcFps();

    void			DrawArray(ge_VertexInfo &inInfo, u32 inType , u32 inCount, bool inRepeatDraw);
    void			DrawBezier(ge_VertexInfo &inInfo, u32 inUCount, u32 inVCount, bool inRepeatDraw);
    void			DrawSpline(ge_VertexInfo &inInfo, u32 inUCount, u32 inVCount, u32 inUFlag, u32 inVFlag, bool inRepeatDraw);

    void			CreateTexture(ge_DecodedTexture *inTexture);
	void			DeleteTexture(ge_DecodedTexture *inTexture);
    void			SetTexture(ge_DecodedTexture *inTexture);

	void            SetTexFunc(u32, u32, u32);

	u32     		TranslateStencilOp(u32 inOperation);

	void			SetMatrix(ge_matrix_type inType, ge_Matrix44 *inMatrix);
	ge_Matrix44    *GetMatrix(ge_matrix_type inType);

	void			SetAlphaBlending(u8 inSource, u8 inDest, u8 inFunc);

    void            SetDrawingRegion(u16 inRegion[4]);

    void            CullObject(ge_VertexInfo &inInfo, u32 inCount);
    bool            IsObjectCulled();

	inline float	GetLastFrameTime() { return mLastFrameTime; }
	inline float	GetCurrentFps() { return mCurrentFps; }

protected:
    template< bool tm, bool cm, bool ce, bool te >
    void PrepareDraw(ge_VertexInfo* inInfo, u32 inType);
    template< bool tm, bool ce, bool te, bool we, bool ne >
    void Draw(ge_VertexInfo* inInfo, ge_DecodedVertex* outDecodedVertices, u32 inType, u32 inCount);

    void DrawPrimitives(ge_VertexInfo &inInfo, ge_DecodedVertex *outDecodedVertices, u32 inType, u32 inCount, bool inRepeatDraw);
    void DrawPatches(ge_VertexInfo &inInfo, ge_DecodedVertex *outDecodedVertices, u32 inCount, bool inRepeatDraw);

    void CalcSkinningPosition(float v[3], ge_DecodedVertex &outDecodedVertice);
    void CalcSkinningNormal(float v[3], ge_DecodedVertex &outDecodedVertice);
    int texture_projection_map_mode;

    void SynchronizeShaders(u32 key);

private:
	ge_Matrix44	mWM;
	ge_Matrix44	mVM;
	ge_Matrix44	mPM;
	ge_Matrix44	mTM;
    ge_Matrix44	mBM[8];

	float		mCurrentFps;
	float		mLastFrameTime;

    bool        mIsScissorEnabled;
    int         mScissorX;
    int         mScissorY;
    int         mScissorW;
    int         mScissorH;

	bool		mInitialized;

    u32         mVertexFlags;
    u32         mPixelFlags;
};

extern Renderer	theRenderer;
#endif // renderer_h__
