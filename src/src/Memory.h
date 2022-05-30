#pragma once

//#include "Video.h"

namespace Memory {

bool initialize();
void finalize();
void reset();

bool enableGuard(bool enable);
void enableExceptions(bool enable);

u8 *getPointer(u32 addr);
bool isValid(u32 addr);

u8 read8(u32 addr);
u16 read16(u32 addr);
u32 read32(u32 addr);

void write8(u32 addr, u8 value);
void write16(u32 addr, u16 value);
void write32(u32 addr, u32 value);

/*TODO*/// extern Log log;

extern u8 *scratchPad;
extern u8 *videoMemory;
extern u8 *mainMemory;

extern bool wasException;

const u32 PageShift = 12;
const u32 PageSize = 1 << PageShift;
const u32 PageMask = PageSize - 1;
const u32 PageCount = 1 << (32 - PageShift);

const u32 Mirror0 = 0x00000;
const u32 Mirror1 = 0x40000;
const u32 Mirror2 = 0x80000;

};  // namespace Memory
