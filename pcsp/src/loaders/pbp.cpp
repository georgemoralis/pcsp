#include "stdafx.h"
#include "pbp.h"
#include "log.h"

pbp::pbp () :	pbpheader(NULL),
				readptr(NULL)
{
}

pbp::~pbp(void)
{
	delete[] readptr;
}

bool pbp::open (const char *readdata)
{
	FILE *f = fopen(readdata,"rb");

	if (!f)
		return false;

	fseek(f,0,SEEK_END);
	size_pbp = ftell(f);
	fseek(f,0,SEEK_SET);
	rewind(f);
	readptr = new u8[size_pbp];
	fread(readptr,1,size_pbp,f);
	fclose(f);
	read(readptr);

	return true;
}

void pbp::read(u8 *readdata)
{
   pbpheader = (PBP_Header *)readdata;
}
bool pbp::isValid()
{
	if(pbpheader->pmagic == 0x50425000)
	{
	   size_param_sfo = pbpheader->offset_icon0_png - pbpheader->offset_param_sfo;
       size_icon0_png = pbpheader->offset_icon1_pmf - pbpheader->offset_icon0_png;
       size_icon1_pmf = pbpheader->offset_pic0_png  - pbpheader->offset_icon1_pmf;
       size_pic0_png  = pbpheader->offset_pic1_png  - pbpheader->offset_pic0_png;
       size_pic1_png  = pbpheader->offset_snd0_at3  - pbpheader->offset_pic1_png;
       size_snd0_at3  = pbpheader->offset_psp_data  - pbpheader->offset_snd0_at3;
       size_psp_data  = pbpheader->offset_psar_data - pbpheader->offset_psp_data;
       size_psar_data = size_pbp - pbpheader->offset_psar_data;
	   //fixup for same sizes
	   if(size_pic0_png==0 && size_pic1_png!=0) size_pic0_png=size_pic1_png;

       return true;
	}
		
	else 
	{
	   size_param_sfo = 0;
       size_icon0_png = 0;
       size_icon1_pmf = 0;
       size_pic0_png  = 0;
       size_pic1_png  = 0;
       size_snd0_at3  = 0;
       size_psp_data  = 0;
       size_psar_data = 0;
		return false;
	}
}
void pbp::printHeader()
{
	    infof(loader,"----PBP Header-----");
   		infof(loader,"pmagic           %08x",pbpheader->pmagic);
		infof(loader,"pversion         %08x",pbpheader->pversion);
		infof(loader,"offset_param_sfo %08x",pbpheader->offset_param_sfo);
		infof(loader,"offset_icon0_png %08x",pbpheader->offset_icon0_png);
		infof(loader,"offset_icon1_pmf %08x",pbpheader->offset_icon1_pmf);
		infof(loader,"offset_pic0_png  %08x",pbpheader->offset_pic0_png);
		infof(loader,"offset_pic1_png  %08x",pbpheader->offset_pic1_png);
		infof(loader,"offset_snd0_at3  %08x",pbpheader->offset_snd0_at3);
		infof(loader,"offset_psp_data  %08x",pbpheader->offset_psp_data);
		infof(loader,"offset_psar_data %08x",pbpheader->offset_psar_data);
}

