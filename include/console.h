#ifndef CONSOLE_H
#define CONSOLE_H

#include "tty.h"
#include "type.h"

// char fg attribute 
#define HRED 0xc
#define HGREEN 0xa
#define HBLUE 0x9
#define HWHITE 0xf

#define RED 4
#define GREEN 2
#define BLUE 1
#define WHITE 7

// char bg attribute 

// video ram is from 0xb8000 ~ 0xc0000
// need 4000 byte for 80X25 console

typedef struct Console_
{
  u32 vm_start; // video memory start
  u32 vm_end; // video memroy end
  u32 cur_vm;
  u32 cur_x, cur_y;
}Console;

#define CONSOLE_NUM 3
#define VIDEO_RAM_SIZE ((0xc0000-0xb8000) / CONSOLE_NUM)

extern Console console_table[];

void s32_print_char(u8 ch);
void s32_print_str(const u8* str);

void s32_set_text_color(u8 fg, u8 bg);

void set_cursor(u16 pos);
void set_video_start_addr(u16 addr);
void s32_console_print_char(Console *console, u8 ch);
int init_console();

#endif