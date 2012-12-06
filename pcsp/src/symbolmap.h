#pragma once

enum SymbolType
{
	ST_FUNCTION=1,
	ST_DATA=2
};

namespace SymbolMap
{
	extern bool load_symbol_map(const char *filename);
	extern void save_symbol_map(const char *filename);
	extern void add_symbol(const char *symbolname, unsigned int vaddress, size_t size, SymbolType symbol);
	extern void reset_symbol_map();
	extern void sort_symbols();
	extern int get_symbol_number(unsigned int address, SymbolType symmask=ST_FUNCTION);
	extern char *get_description(unsigned int address);
	extern int get_symbols_count();
	extern char *get_symbol_name(int i);
	extern void set_symbol_name(int i, const char *newname);
	extern u32 get_symbol_size(int i);
	extern u32 get_symbol_address(int i);
	extern int find_symbol(const char *name);
	extern u32 get_symbol_address(int num);
	extern void increase_run_count(int num);
	extern u32 get_run_count(int num);
};