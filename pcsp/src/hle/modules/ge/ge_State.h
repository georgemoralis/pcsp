#pragma once

#include <string.h>

#include "hle/modules/ge/ge_Types.h"

extern int gUniformChanges[64];

struct GPUState
{
public:
	GPUState()
	{
        typedef char check_size[512*4 - sizeof(GPUState)];

		memset(this, 0, sizeof(GPUState));
		texture_matrix[ 0] = 1.0f;
        texture_matrix[ 5] = 1.0f;
        texture_matrix[10] = 1.0f;
        texture_matrix[15] = 1.0f;
		light_lv[0][3] = 1.0f;
        light_lv[1][3] = 1.0f;
        light_lv[2][3] = 1.0f;
        light_lv[3][3] = 1.0f;

        memset(gUniformChanges, 0, sizeof(gUniformChanges));
	}

    int UniformChanges(int location) const { return gUniformChanges[location]; } 
    void ChangeUniform(int location)       { ++gUniformChanges[location]; } 

	// State Enables   
    u32     clear_mode_enable        : 1;
    u32     clear_alpha_masked       : 1;
    u32     clear_color_masked       : 1;
    u32     clear_depth_masked       : 1;
    u32		object_culling_enable    : 1;
    u32		patch_culling_enable     : 1;
    u32		face_culling_enable      : 1;
    u32		antialiasing_enable      : 1;
    u32		gouraud_enable           : 1;
    u32		color_test_enable        : 1;
    u32		alpha_test_enable        : 1;
    u32		stencil_test_enable      : 1;
    u32		depth_test_enable        : 1;
    u32		alpha_blending_enable    : 1;
    u32		logical_operation_enable : 1;
    u32		fogging_enable           : 1;
    u32     lighting_enable          : 1;
    u32		texture_mapping_enable   : 1;
    u32     face_culling_direction   : 1;

    u32		clipping_enable;
	u32		dithering_enable;

	// Lights
	u32		light_enabled;
    u32     light_mode;
	int		light_type[4];
	int		light_kind[4];
	f32 	light_lv[4][4];
	f32 	light_ld[4][4];
    f32     light_lka[4][4];
    f32 	light_lac[4][4];
    f32 	light_ldc[4][4];
    f32 	light_lsc[4][4];
	f32 	light_lks[4];
	f32	    light_lko[4];
	f32 	light_ac[4];
    f32     light_mk;

	// Materials
	u32		material_flags;
    f32     material_mac[4];
    f32     material_mdc[4];
    f32     material_msc[4];
    f32     material_mec[4];

	// Textures
	u32		texture_filter;
	u32		texture_mapping_mode, texture_projection_mapping;
	u32		texture_base_pointer[8];
	u32		texture_buffer_width[8];
	f32     texture_matrix[16];
	u32		texture_height[8];
	u32		texture_width[8];
    u32		texture_size[8]; 
	u32		texture_wrap_mode_s;
	u32		texture_wrap_mode_t;
	f32 	texture_scale_u;
    f32     texture_scale_v;
	f32 	texture_offset_u;
    f32     texture_offset_v;
	u32		texture_num_mip_maps;
	u32		texture_swizzle;
	u32		texture_storage;
	u32		texture_storage_ext;
	u32		texture_mag_filter;
	u32		texture_min_filter;
	u32		texture_mipmap_mode;
    f32		texture_mipmap_bias;
    f32		texture_mipmap_slope;
    
    struct { u32 u, v;                              } texture_shade;
    struct { u32 txf; u32 tcc; u32 cd; f32 rgba[4]; } texture_function;

	// CLUT
	u32		texture_clut_address;
	bool	texture_clut_is_dirty;
	u32 	texture_clut_mode;
	u32		texture_clut_sft;
	u32		texture_clut_msk;
	u32		texture_clut_csa;
	u32		mipmap_share_clut;  
	u32		texture_clut_np;

	// Texture Transfer
    int textureTx_sourceAddress;
    int textureTx_sourceLineWidth;
    int textureTx_destinationAddress;
    int textureTx_destinationLineWidth;
    int textureTx_width;
    int textureTx_height;
    int textureTx_sx;
    int textureTx_sy;
    int textureTx_dx;
    int textureTx_dy;
    int textureTx_pixelSize;


	// Bezier & Spline & Patch
	u32		patch_div_u,patch_div_v;
	u32     patch_primitive;
    bool    patch_face;

	// Vertex
	u32		transform_mode;
	u32		vertex_address;
	u32		index_address;
	u32		base_address;
	bool	reverse_normals;
	u32		offset_address;
	
	// Matrix Numbers
	u32		matrix_world_num;
	u32		matrix_view_num;
	u32		matrix_projection_num;
	u32		matrix_texture_num;
	u32		matrix_bone_num;
	
	// Morphing
	float	morphing_weights[8];

	// FrameBuffer
	u32		fbp; 
	u32		fbw; 
	u32		zbp; 
	u32		zbw;

	// Fog
	f32     fog_far;
	f32     fog_dist;
	f32     fog_color[4];

    // Dither
	float	dither_matrix[16];

    // Logical operation
    u32     logical_operation_function;

    u32		region_width;
    u32		region_height;

    // Drawing region (Object/Patch Culling)
    u16		region[4];

    // Scissoring
    u16		scissor[4];

	// Z stuff
	f32     minz, maxz;

    // View port
    f32     viewport_sx;
    f32     viewport_sy;
    f32     viewport_sz;
    f32     viewport_tx;
    f32     viewport_ty;
    f32     viewport_tz;

    f32     offset_x;
    f32     offset_y;

	// Clear
	float	clearModeRgbScale;
	int		clearModeTextureEnvMode;
	u8		clearModeDepthFunc;

    // Color/Alpha test
    u32     color_test_color_ref[3];
    u32     alpha_test_color_ref;
    u32     color_test_color_msk[3];
    u32     alpha_test_color_msk;
    u32     color_test_function;
    u32     alpha_test_function;

    // Stencil test
    u8      stencil_test_ref;
    u8      stencil_test_msk;
    u8      stencil_test_function;
    u8      stencil_sfail;
    u8      stencil_zfail;
    u8      stencil_zpass;

    // Depth test
    u32     depth_test_function;

	// Alpha blending
    f32	    alpha_blending_fixa[4];
    f32	    alpha_blending_fixb[4];	
    u8      alpha_blending_a;
    u8      alpha_blending_b;
    u8      alpha_blending_equ;

    // Masking
    bool	color_mask[3];
    bool	alpha_mask;
    bool    depth_mask;
};

extern GPUState	theGPUState;

extern u8 current_palette[256*4];
