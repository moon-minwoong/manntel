#ifndef __XM_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#define __XM_H_F2DBDC40_6196_4E67_A689_D31A9310BEC0__
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <winsock2.h>
#include <mstcpip.h>
#include <winreg.h>
#include <iphlpapi.h>
#include <sys/timeb.h>
#include <process.h>
#include <time.h>
#include <CodeX.h>

#include <wtray.h>
#include <wcommon.h>
#include <mdbc.h>
#include <ssf-db.h>

#include "resource.h"



#define MAX_LINE           1024//(1<<0x0F)
#define XWM_CALLBACK       (WM_USER+0x0001)
#define XWM_TRANSFER       (WM_USER+0x0002)
#define MAX_BUF_SZ         1024



enum
{
  XM_STATIC1,
  XM_STATIC2,
  XM_STATIC3,
  XM_STATIC_TITLE1,
  XM_STATIC_TITLE2,
  XM_STATIC_TITLE3,
  XM_CHECK1,
  XM_CHECK2,
  XM_LIST1,
  XM_BUTTON1,
  MAX_XM_ITEM
};
#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  uint8_t b[1024];
  int32_t sz;
  uint32_t SR;
}ASyncParam;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif


#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  HDC                hdc;
  HBRUSH             hbrush;
  PAINTSTRUCT        ps;
  HWND               hwnd;
  WNDPROC            wproc;
  RECT               rct;
  COLORREF           color[2]; //0: Background, 1:Forground
  uint32_t           count;  
}XSubWnd;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif

#if (defined XWIN32 || defined WINCE)
#pragma pack(1)
#endif
typedef struct
{
  HINSTANCE          hinst[2];
  HWND               hdlg;

  XSubWnd            item[MAX_XM_ITEM];

  wLog               log;

  void*              h;
  CodeX              codeX;
  void*              hdbc;

  ASyncParam         aparam;

  uint32_t           SR;
  uint8_t            backbuf[MAX_BUF_SZ];
}XWND;
#if (defined XWIN32 || defined WINCE)
#pragma pack()
#endif


#endif
