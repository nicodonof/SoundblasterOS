#ifndef TYPES_H_
#define TYPES_H_
#pragma pack(1)
typedef unsigned char byte;
typedef short int word;
typedef int dword;
typedef long ddword;
typedef struct {
	word	offset_l, selector;
	byte	cero, access;
	word	offset_m;
	dword	offset_h, zero; 
} DESCR_INT;

typedef struct{
	char red;
	char green;
	char blue;
} color;

#endif