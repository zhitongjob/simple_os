/*
 * kernel io function
 */

#include "syscall.h"
#include "console.h"
#include "k_stdio.h"
#include "k_stdlib.h"

int s32_printf(const char *fmt, ...)
{
  char buf[256];
  int i=1;
  char *p = buf;

  for (; *fmt ; ++fmt)
  {
    if (*fmt != '%')
    {
      *p++ = *fmt;
      continue;
    }
    ++fmt;
    u8 *arg = (u8 *)(&fmt + i); // nst argument address
    u32 arg_content = *((u32*)arg);

    switch (*fmt)
    {
      case 'd':
      {
        u8 str[12]="";
        s32_itoa(arg_content, str, 10);

        char *str_ptr = str;
        while(*str_ptr)
          *p++ = *str_ptr++;
        break;
      }
      case 'x':
      {
        u8 str[12]="";
        s32_itoa(arg_content, str, 16);

        char *str_ptr = str;
        while(*str_ptr)
          *p++ = *str_ptr++;
        break;
      }
      case 's':
      {
        char *str_ptr = (char *)arg_content;
        while(*str_ptr)
          *p++ = *str_ptr++;
        break;
      }
      default:
        break;
    }
    ++i; // point to next argument
 
  } // end for (char *p = buf; *fmt ; ++fmt, ++i)
  int len = p-buf;
  //buf[len]='\0';

  int write(char *buf, int len);
  write(buf, len);

  return 0;
}

int printx(const char *fmt, ...)
{
 // int printk(char *s);

  int i;
  char buf[256];
  char *arg = (char *)(&fmt+1);

  i = s32_vsprintf(buf, fmt, arg);
  printk(buf); // system call
  //while(1);
  return i;
}

