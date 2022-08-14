#ifndef IO_H
#define IO_H
#include "criscv.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef unsigned long  long u64;

static inline u8  read8(u32 addr){
	return *((volatile u8*) addr);
}
static inline u16 read16(u32 addr){
	return *((volatile u16*) addr);
}
static inline u32 read32(u32 addr) {
	return *((volatile u32 *)addr);
}

static inline void write8(u32 addr, u8 data) {
	*((volatile u8*) addr) = data;
}
static inline void write16(u32 addr, u16 data) {
	*((volatile u16*) addr) = data;
}
static inline void write32(u32 addr, u32 data) {
	*((volatile u32 *)addr) = data;
}
#endif
