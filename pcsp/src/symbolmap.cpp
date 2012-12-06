#include "stdafx.h"
#include "symbolmap.h"

struct MapEntry
{
	u32 address;
	u32 vaddress;
	u32 size;
	u32 unknown;
	u32 runCount;
	SymbolType type;
	char name[128];
};

int numEntries;
MapEntry entries[65536*2];

int compareEntries(const void *p1, const void *p2)
{
	const MapEntry *e1 = (const MapEntry*)p1,
		*e2 = (const MapEntry*)p2;

	return e1->vaddress - e2->vaddress;
}

void SymbolMap::sort_symbols()
{
	::qsort(entries, numEntries, sizeof(MapEntry), compareEntries);
}

void SymbolMap::reset_symbol_map()
{
	numEntries=0;
}

void SymbolMap::add_symbol(const char *symbolname, unsigned int vaddress, size_t size, SymbolType st)
{
	MapEntry &e = entries[numEntries++];
	::strcpy(e.name, symbolname);
	e.vaddress = vaddress;
	e.size = size;
	e.type = st;
}
bool SymbolMap::load_symbol_map(const char *filename)
{
	reset_symbol_map();

	numEntries = 0;

	FILE *f = ::fopen(filename, "r");

	if (!f) return false;

	bool started = false;

	while (!::feof(f))
	{
		char line[512],temp[256];

		::fgets(line,511,f);

		if (::strlen(line) < 4)
			continue;

		::sscanf(line, "%s", temp);

		if (!::strcmp(temp, "UNUSED")) continue;
		if (!::strcmp(temp, ".text")) { started = true; continue;};
		if (!::strcmp(temp, ".init")) { started = true; continue;};
		if (!::strcmp(temp, "Starting")) continue;
		if (!::strcmp(temp, "extab")) continue;
		if (!::strcmp(temp, ".ctors")) break;
		if (!::strcmp(temp, ".dtors")) break;
		if (!::strcmp(temp, ".rodata")) continue;
		if (!::strcmp(temp, ".data")) continue;
		if (!::strcmp(temp, ".sbss")) continue;
		if (!::strcmp(temp, ".sdata")) continue;
		if (!::strcmp(temp, ".sdata2")) continue;
		if (!::strcmp(temp, "address"))  continue;
		if (!::strcmp(temp, "-----------------------"))  continue;
		if (!::strcmp(temp, ".sbss2")==0) break;
		if (temp[1]==']') continue;

		if (!started) continue;

		MapEntry &e = entries[numEntries++];

		::sscanf(line, "%08x %08x %08x %i %s", &e.address, &e.size, &e.vaddress, (int*)&e.type, e.name);

		if (e.type == ST_DATA && e.size==0)
			e.size=4;
		//e.vaddress|=0x80000000;
		if (!::strcmp(e.name,".text") || !::strcmp(e.name, ".init") || ::strlen(e.name) <= 1)
			numEntries--;
	}

	::fclose(f);

	sort_symbols();

	return true;
}
void SymbolMap::save_symbol_map(const char *filename)
{
	FILE *f = ::fopen(filename,"w");
	if (!f)
		return;
	::fprintf(f, ".text\n");

	for (int i = 0; i < numEntries; ++i)
	{
		MapEntry &e = entries[i];
		::fprintf(f, "%08x %08x %08x %i %s\n", e.address, e.size, e.vaddress, e.type, e.name);
	}

	::fclose(f);
}

int SymbolMap::get_symbol_number(unsigned int address, SymbolType symmask)
{
	int start = 0;

	int i;

	for (i = 0; i < numEntries; i += 100)
	{
		if (address >= entries[i].vaddress)
			start = i;
		else
			break;
	}

	if (start < 0) start = 0;

	for (i = start; i < numEntries; ++i)
	{
		unsigned int addr = entries[i].vaddress;

		if ((address >= addr))
		{
			if (address < addr+entries[i].size)
			{
				return (entries[i].type & symmask) ? i : -1;
			}
		}
		else
		{
			break;
		}
	}

	return -1;
}

char temp[256];

char *SymbolMap::get_description(unsigned int address)
{
	int fun = get_symbol_number(address);
	if (fun != -1)
	{
		return entries[fun].name;
	}
	else
	{
		::sprintf(temp, "(%08x)", address);
		return temp;
	}
}

int SymbolMap::get_symbols_count()
{
	return numEntries;
}

char *SymbolMap::get_symbol_name(int i)
{
	return entries[i].name;
}

void SymbolMap::set_symbol_name(int i, const char *newname)
{
	::strcpy(entries[i].name, newname);
}

u32 SymbolMap::get_symbol_address(int i)
{
	return entries[i].vaddress;
}

u32 SymbolMap::get_symbol_size(int i)
{
	return entries[i].size;
}

int SymbolMap::find_symbol(const char *name)
{
	for (int i = 0; i < numEntries; ++i)
		if (!::strcmp(entries[i].name, name))
			return i;
	return -1;
}

u32 SymbolMap::get_run_count(int num)
{
	return (num >= 0) ? entries[num].runCount : 0;
}
