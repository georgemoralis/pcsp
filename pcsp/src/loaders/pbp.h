#pragma once

#include "psf.h"

class pbp
{
public:
	pbp ();
	virtual ~pbp();

	void read(u8 *readdata);
	bool open(const char *filename);
	bool isValid();
	void printHeader();

	typedef struct
    {
		unsigned int pmagic;
		unsigned int pversion;
		unsigned int offset_param_sfo;
		unsigned int offset_icon0_png;
		unsigned int offset_icon1_pmf;
		unsigned int offset_pic0_png;
		unsigned int offset_pic1_png;
		unsigned int offset_snd0_at3;
		unsigned int offset_psp_data;
		unsigned int offset_psar_data;
	} PBP_Header;

    PBP_Header *pbpheader;
    u8 *readptr;


	u32 size_pbp;
    u32 size_param_sfo;
    u32 size_icon0_png;
    u32 size_icon1_pmf;
    u32 size_pic0_png;
    u32 size_pic1_png;
    u32 size_snd0_at3;
    u32 size_psp_data;
    u32 size_psar_data;

};
