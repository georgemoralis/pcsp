#pragma once

#include "types.h"
#include "ge_TextureManager.h"

// Alignment of all different states
//----------------------------------

//GE_VTYPE_POSITION_NONE	0	0
//GE_VTYPE_POS_8BIT			1	3
//GE_VTYPE_POS_16BIT		2	6
//GE_VTYPE_POS_FLOAT		4	12
//GE_VTYPE_POS_MASK			4	12
//GE_VTYPE_POS_SHIFT		?	?
const u32 PositionAlignment[4]		= {0,1,2,4};
const u32 PositionSize[4]			= {0,3,6,12};

//GE_VTYPE_COL_NONE			0	0
//GE_VTYPE_COL_565			2	2
//GE_VTYPE_COL_5551			2	2
//GE_VTYPE_COL_4444			2	2
//GE_VTYPE_COL_8888			4	4
//GE_VTYPE_COL_MASK			4	4
//GE_VTYPE_COL_SHIFT		?	?
const u32 ColorAlignment[8]			= {0,0,0,0,2,2,2,4};
const u32 ColorSize[8]				= {0,0,0,0,2,2,2,4};

//GE_VTYPE_NRM_NONE			0	0
//GE_VTYPE_NRM_8BIT			1	3
//GE_VTYPE_NRM_16BIT		 2	6
//GE_VTYPE_NRM_FLOAT		4	12
//GE_VTYPE_NRM_MASK			4	12
//GE_VTYPE_NRM_SHIFT		?	?
const u32 NormalAlignment[4]		= {0,1,2,4};
const u32 NormalSize[4]				= {0,3,6,12};

//GE_VTYPE_TC_NONE  		0	0
//GE_VTYPE_TC_8BIT  		1	2
//GE_VTYPE_TC_16BIT 		2	4
//GE_VTYPE_TC_FLOAT 		4	8
//GE_VTYPE_TC_MASK  		4	8
//GE_VTYPE_TC_SHIFT 		?	?
const u32 TexturecoordAlignment[4]	= {0,1,2,4};
const u32 TexturecoordSize[4]	= {0,2,4,8};

//GE_VTYPE_WEIGHT_NONE		0	0
//GE_VTYPE_WEIGHT_8BIT		1	1
//GE_VTYPE_WEIGHT_16BIT		2	2
//GE_VTYPE_WEIGHT_FLOAT		4	4
//GE_VTYPE_WEIGHT_MASK		4	4
//GE_VTYPE_WEIGHT_SHIFT		?	?
const u32 WeighttypeAlignment[4]	= {0,1,2,4};
const u32 WeighttypeSize[4]			= {0,1,2,4};

const u32 size_mapping[4] = { 0, 1, 2, 4 };
const u32 size_padding[4] = { 0, 0, 1, 3 };
const u32 color_size_mapping[8] = { 0, 1, 1, 1, 2, 2, 2, 4 };
const u32 color_size_padding[8] = { 0, 0, 0, 0, 1, 1, 1, 3 };

class ge_VertexInfo
{
public:
	u32 param;

	u32 tt; // texture type
	u32 ct; // color type
	u32 nt; // normal type
	u32 vt; // vertex type
	u32 wt; // weight type (skinning)
	u32 it; // index type
	u32 wc; // weight count (skinning)
	u32 mc; // morphing count
	u32 tm; // through mode

	u32 vertex_size;
	u32 one_vertex_size;
	u32 texture_offset;
	u32 color_offset;
	u32 normal_offset;
	u32 position_offset;
	u32 alignment_size;

	ge_VertexInfo()
	{
		param = 0;
		
		tt  = 0;
		ct  = 0;
		nt  = 0;
		vt  = 0;
		wt  = 0;
		it  = 0;
		wc	= 0;
		mc	= 0;
		tm	= 0;

		vertex_size     = 0;
		one_vertex_size = 0;
		texture_offset  = 0;
		color_offset    = 0;
		normal_offset   = 0;
		position_offset = 0;
		alignment_size  = 0;
	}
};


class ge_DecodedVertex
{
public:
	float v[3];    
	float n[3]; 
	float t[2];     
	float c[4]; 
	float w[8];
};

class ge_Decoder
{
public:
	ge_Decoder();
	~ge_Decoder();

	void	DecodeVertices(     ge_VertexInfo &vertexInfo, ge_DecodedVertex *outVertices,              const void *inVertices, const void *inIndices, u32 inCount);
    void	DecodeBezierSurface(ge_VertexInfo &vertexInfo, ge_DecodedVertex *&outVertices, u32 &count, const void *inVertices, const void *inIndices, u32 ucount, u32 vcount);
	void	DecodeSplineSurface(ge_VertexInfo &vertexInfo, ge_DecodedVertex *&outVertices, u32 &count, const void *inVertices, const void *inIndices, u32 ucount, u32 vcount, u32 uf, u32 vf);

	void	SetVertexInfo(ge_VertexInfo &vertexInfo);

	void	ConvertToQuads(ge_DecodedVertex *inDecodedVertices, ge_DecodedVertex *outDecodedVertices, u32 inCount);

private:
};

extern	ge_Decoder	theDecoder;