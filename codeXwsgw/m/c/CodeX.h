#ifndef __CODEX_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __CODEX_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__

#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

#include <code.x.h>

#include <util.h>
#include <mprotocol.h>
#include <protocol_shof.h>

#define MODULE     "code.X.x86.dll"
#define delay(msec)    Sleep(msec)

#if defined XWIN32
#pragma pack(1)
#endif
typedef struct
#if defined LINUX
__attribute__((packed))
#endif
{
  int   a[4];  // fd sz  bp  fdp
} CodeXfdset;
#if defined XWIN32
#pragma pack()
#endif


#if defined XWIN32
#pragma pack(1)
#endif
typedef struct
#if defined LINUX
__attribute__((packed))
#endif
{
  CodeXfdset*  fdset;
} CodeXModule;
#if defined XWIN32
#pragma pack()
#endif


#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  uint32_t   SR;

	void* hdl;
	void* h;

  int8_t  rbuf[4096];
  int8_t  buf[4096];
  int32_t idx;

  //int32_t (*codeXInitia)(void** h, void* (*f)(void*,void*,void*,void*), void*);
  //int32_t (*codeXFinelia)(void** h);
  int32_t (*putMessage)(void* h, void* m, void* w, void* l);
  int32_t (*setMessage)(void* h, void* m, void* w, void* l);
  int32_t (*getMessage)(void* h, void* m, void* w, void* l);

  void* (*callback)(void*,void*,void*,void*);
  void*  obj;

  uint8_t wsck_buf[1024];
  uint8_t sck_buf[1024];



  CodeXModule modul[MAX_MODULES];
}CodeX;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif


void* loadInterface(void* hdl);
void* codeXmain(void* hdl, CodeX* p);
void* codeXend(CodeX* p);


int32_t (*get_hex_semaphore)(uint32_t* id, uint32_t h, uint32_t v, int32_t msec);
int32_t (*set_hex_semaphore)(uint32_t* id, uint32_t h, uint32_t v);
int32_t (*check_hex_semaphore)(uint32_t* id, uint32_t h, uint32_t v);
void*   (*thread_create)(void* (*f)(void*),void* arg, void* id);
void    (*thread_exit)(int32_t sid, void* id);
int8_t* (*get_curr_time)(int8_t*p, int8_t* arg0, int8_t* arg1, int8_t* arg2, int8_t* arg3, int32_t* YY, int32_t* MM, int32_t* DD, int32_t* hh, int32_t* mm, int32_t* ss, int32_t* us);
void*   (*log_write_ex)(int8_t* ppath, int8_t* fname, int8_t* pfname, void** pfp, int8_t* pfx, uint32_t mode, const int8_t* fmt, ...);


#endif

