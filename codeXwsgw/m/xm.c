#include <xm.h>

#define COUNT_MOD           0x7FF
#define DB_COUNT_MOD        0x7FF

XWND wnd;


#define TOP_TITLE   "국립금오공과대학교 응용수학과 유원석, 신승혁   Powered by CODE X"


/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                      Definition of the action color                         */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
#define COLOR_SYSTEM_RUN                 RGB(0x00, 0x00, 0xFF)
#define COLOR_SYSTEM_DOWN                RGB(0xAA, 0x00, 0x00)
#define COLOR_CONNECTED                  RGB(0x00, 0xFF, 0x00)
#define COLOR_DISCONNECTED               RGB(0xFF, 0x00, 0x00)
#define COLOR_RCVD1                      RGB(0xFF, 0x99, 0x00)
#define COLOR_RCVD2                      RGB(0x33, 0xFF, 0x33)
#define COLOR_SENT1                      COLOR_RCVD1
#define COLOR_SENT2                      COLOR_RCVD2
#define COLOR_FAIL                       RGB(0xAA, 0xFF, 0x0F)
#define COLOR_IDLE                       (COLOR_SYSTEM_RUN|COLOR_CONNECTED)


/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                                 Control widget                              */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
//void* SetBackgroundColor(HWND hwnd, COLORREF color)
//{
//  HDC                hdc;
//  HBRUSH             hbrsh, obrsh;
//  PAINTSTRUCT        ps;
//
//  hdc = BeginPaint(hwnd, &ps);
//  hbrsh = CreateSolidBrush(color);
//  //obrsh = (HBRUSH)SelectObject(hdc, hbrsh);
//  SetBkColor(hdc, color);
//  //Ellipse(hdc, 0, 0, 5, 5);
//  //SelectObject(hdc, obrsh);
//  //DeleteObject(hbrsh);
//  EndPaint(hwnd, &ps);
//  return (void*)obrsh;
//}
//
//void* SetBackgroundColor(XSubWnd* p, COLORREF color)
//{
//  p->hdc = BeginPaint(p->hwnd, &p->ps);
//  if ( p->hbrush ) DeleteObject(p->hbrush);
//  p->hbrush = CreateSolidBrush(color);
//  SetBkColor(p->hdc, color);
//  EndPaint(p->hwnd, &p->ps);
//  return (void*)p->hbrush;
//}


void* SetBackgroundColor(XSubWnd* p, COLORREF color)
{
  HDC memdc;
  HBITMAP hbmp, obmp;

  if ( p == 0 ) return 0;
  if ( p->hwnd == 0 ) return 0;

  GetClientRect(p->hwnd, &p->rct);


  p->hdc = BeginPaint(p->hwnd, &p->ps);
  if ( p->hbrush ) DeleteObject(p->hbrush);
  p->hbrush = CreateSolidBrush(color);

  memdc = CreateCompatibleDC(p->hdc);
  hbmp = CreateCompatibleBitmap(p->hdc, (p->rct.right)-(p->rct.left), (p->rct.bottom)-(p->rct.top));

  obmp = SelectObject(memdc, hbmp);

  SetBkColor(memdc, color);

  SelectObject(memdc, obmp);

  DeleteObject(hbmp);
  DeleteObject(memdc);

  EndPaint(p->hwnd, &p->ps);
  return (void*)p->hbrush;
}
//
//void* SetBackgroundColor(XSubWnd* p, COLORREF color)
//{
//  HDC memdc;
//  HBITMAP hbmp, obmp;
//
//  if ( p == 0 ) return 0;
//  if ( p->hwnd == 0 ) return 0;
//
//  GetClientRect(p->hwnd, &p->rct);
//
//
//  p->hdc = GetDC(p->hwnd);
//  if ( p->hbrush ) DeleteObject(p->hbrush);
//  p->hbrush = CreateSolidBrush(color);
//
//  memdc = CreateCompatibleDC(p->hdc);
//  hbmp = CreateCompatibleBitmap(p->hdc, (p->rct.right)-(p->rct.left), (p->rct.bottom)-(p->rct.top));
//
//  obmp = SelectObject(memdc, hbmp);
//
//  SetBkColor(memdc, color);
//
//  SelectObject(memdc, obmp);
//
//  DeleteObject(hbmp);
//  DeleteObject(memdc);
//
//  ReleaseDC(p->hwnd, p->hdc);
//  return (void*)p->hbrush;
//}
//
//
//void* SetBackgroundColor(XSubWnd* p, COLORREF color)
//{
//  HDC memdc;
//  HBITMAP hbmp, obmp;
//
//  if ( p == 0 ) return 0;
//  if ( p->hwnd == 0 ) return 0;
//  p->hdc = GetDC(p->hwnd);
//  if ( p->hbrush ) DeleteObject(p->hbrush);
//  p->hbrush = CreateSolidBrush(color);
//
//
//  SetBkColor(p->hdc, color);
//
//  ReleaseDC(p->hwnd, p->hdc);
//  return (void*)p->hbrush;
//}


//void* SetBackgroundColor(XSubWnd* p, COLORREF color)
//{
//  p->hdc = BeginPaint(p->hwnd, &p->ps);
//  Ellipse(p->hdc, 0, 0, 50, 50);
//  EndPaint(p->hwnd, &p->ps);
//  return (void*)0;
//}


void* SetBkColorMessage(HWND hwnd, XSubWnd* p, COLORREF color)
{
  p->color[0] = color;
  PostMessage(hwnd, WM_CTLCOLORSTATIC, 0, color);
  InvalidateRect(hwnd, 0, TRUE);
  return 0;
}



void* DrawCircle(HWND hwnd)
{
  HDC                hdc;
  RECT               rct;
  HDC                memdc;
  HGDIOBJ            oldobj;
  HBRUSH             hbrsh;
  PAINTSTRUCT        ps;


  hdc = GetDC(hwnd);
  hbrsh = CreateSolidBrush(RGB(0xFF, 0, 0));
  oldobj = SelectObject(hdc, hbrsh);

  //Ellipse(hdc, 0, 0, 230, 230);


  SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)hbrsh);

  
  SelectObject(hdc, oldobj);
  DeleteObject(hbrsh);
  ReleaseDC(hwnd, hdc);


  //GetClientRect(hwnd, &rct);
  //hdc = BeginPaint(hwnd, &ps);
  //hbrsh = CreateSolidBrush(RGB(0xFF, 0, 0));
  //odc = SelectObject(hdc, hbrsh);
  //
  //FillRect(hdc, &rct, hbrsh);
  ////Ellipse(hdc, rct.left, rct.top, rct.right, rct.bottom);
  //SelectObject(hdc, odc);
  //DeleteObject(odc);
  //EndPaint(hwnd, &ps);
  //DeleteObject(hbrsh);


  //hdc = GetDC(hwnd);
  ////memdc = CreateCompatibleDC(hdc);
  ////odc = SelectObject(memdc, memdc); 
  //Ellipse(hdc, 0, 0, 30, 30);

  ////SelectObject(hdc, odc);
  ////DeleteObject(memdc);
  //ReleaseDC(hwnd, hdc);
  //DeleteDC(hdc);

  return 0;
}






/*******************************************************************************/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*                                   DBC                                       */
/*                                                                             */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/

int32_t fxDBClose()
{
  return mdbcClose(&wnd.hdbc);
}




void* fxDBConnectorStatus(int32_t err)
{
  if ( err == -1 )
  {
    LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "DB", "Open (%s:%s:%s) Fail \r\n", DB_HOST, DB_PORT, DB_USER);
    SetBkColorMessage(wnd.item[XM_STATIC3].hwnd, &wnd.item[XM_STATIC3], COLOR_DISCONNECTED);
    //InvalidateRect(wnd.item[XM_STATIC3].hwnd, 0, TRUE);      
  }
  else if ( err == 1 )
  {
    LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "DB", "Open (%s:%s:%s) Connecting... \r\n", DB_HOST, DB_PORT, DB_USER);
    SetBkColorMessage(wnd.item[XM_STATIC3].hwnd, &wnd.item[XM_STATIC3], RGB(0xFF, 0xFF,0xFF));
    //SetBkColorMessage(wnd.item[XM_STATIC3].hwnd, RGB(0xFF, 0,0));
    //InvalidateRect(wnd.item[XM_STATIC3].hwnd, 0, TRUE);      
  }
  else
  {
    LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "DB", "Open (%s:%s:%s) Success \r\n", DB_HOST, DB_PORT, DB_USER);
    SetBkColorMessage(wnd.item[XM_STATIC3].hwnd, &wnd.item[XM_STATIC3], COLOR_CONNECTED);
    //SetBkColorMessage(wnd.item[XM_STATIC3].hwnd, RGB(0xFF, 0,0));
    //InvalidateRect(wnd.item[XM_STATIC3].hwnd, 0, TRUE);      
  }
  return 0;
}


#if 0
int32_t fxDBWrite(int8_t* b, int32_t sz)
{
  int32_t  e = 0;
  int32_t  idx = 0;
  int32_t  i = 0;
  int32_t  gindex = 0;
  int8_t temp[32];
  int8_t qval[32][32];
  int8_t query[1024];
  uint8_t tm[32];

  time_t t = time(0);


  *(b + idx); idx++; //STX
  *(b + idx); idx++; //CMD
  *(b + idx); idx++; //LENGTH

  sprintf(qval[0], "%s", *(b + idx) == 0x00 ? STATUS_0 : *(b + idx) == 0x01 ? STATUS_1 : STATUS_2); idx++; //POWER ON/OFF
  sprintf(qval[1], "%d", ((*(b + idx) & 0xFF) * 256) + (*(b + idx + 1) & 0xFF)); idx += 2;
  sprintf(qval[2], "%d", ((*(b + idx) & 0xFF) * 256) + (*(b + idx + 1) & 0xFF)); idx += 2;
  sprintf(qval[3], "%d", ((*(b + idx) & 0xFF) * 256) + (*(b + idx + 1) & 0xFF)); idx += 2;
  *(b + idx); idx++; // 8
  *(b + idx); idx++; // 9
  *(b + idx); idx++; // 10
  *(b + idx); idx++; //Check SUM
  *(b + idx); idx++; //ETX


  gindex = get_gdinfo_index( *(b+1) );
  if ( gindex < 0 ) return 0;


  get_curr_time(tm, "-", "-", " ", ":", 0, 0, 0, 0, 0, 0, 0);

  if (wnd.hdbc != 0)
  {
    sprintf(query,
      "insert into Machine_Parameter_Out ( id, machine_code, parameter_code, status_log, date_time ) "
      "values "
      "("
      " (select machine_name from MACHINE where machine_code='%s'), '%s', '%s', '%s', '%s'"
      ")",
      gdinfo[gindex].did, gdinfo[gindex].did, gdinfo[gindex].rfactor[0], qval[0], tm);

    e = mdbcQuery(wnd.hdbc, 0, query, strlen(query));
    if (e == 0)
    {
      #if LVLOG_LEVEL_0
      if ( SendMessage(wnd.item[XM_CHECK2].hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
        LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "DB", "Query SUCCESS - %s \r\n", query);
      #endif
      wnd.item[XM_STATIC3].count++;
      if ( wnd.item[XM_STATIC3].count && ((wnd.item[XM_STATIC3].count%COUNT_MOD) == 0) )
      {
        wnd.item[XM_STATIC3].color[0] = (wnd.item[XM_STATIC3].color[0]==COLOR_SENT1?COLOR_SENT2:COLOR_SENT1);
        #if LVLOG_LEVEL_5
        LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "DB", "Query Success [%d] \r\n", wnd.item[XM_STATIC3].count+1);
        #endif
      }
      SetBkColorMessage(wnd.item[XM_STATIC3].hwnd, &wnd.item[XM_STATIC3], wnd.item[XM_STATIC3].color[0]);
    }
    else
    {
      #if LVLOG_LEVEL_0
      if ( SendMessage(wnd.item[XM_CHECK2].hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
        LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "DB", "Query FAIL - %s \r\n", query);
      #endif
      SetBkColorMessage(wnd.item[XM_STATIC3].hwnd, &wnd.item[XM_STATIC3], COLOR_FAIL);
    }

    //#if DEBUG_LOCAL
    //OutputDebugString(query);
    //OutputDebugString("\r\n");
    //#endif
  }
  else
  {
    fxDBOpen();
  }
  return e;
}
#endif

int32_t fxDBOpen()
{
  mdbcOpen(&wnd.hdbc, DB_HOST, DB_PORT, DB_USER, DB_PASS, DB_NAME, fxDBConnectorStatus);

  return 0;
}



/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/* WebSocket                                                                   */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/

int32_t fxWebSocketRouting(int8_t* b, int32_t sz)
{
  int32_t e = 0;
  int32_t idx = 0;
  int8_t  raw[1024];

  if ( wnd.codeX.modul[XWEBSOCKET].fdset == 0 ) return ;

  for(idx=0 ; idx<FD_SETSIZE ; idx++ )
  {
    if ( (wnd.codeX.modul[XWEBSOCKET].fdset+idx)->a[0] > 0 )
    {
      wnd.codeX.setMessage(wnd.codeX.h, (void*)MAKELONG(FDSCRPTR, XWEBSOCKET), (void*)(wnd.codeX.modul[XWEBSOCKET].fdset+idx)->a[0], 0);
      e = wnd.codeX.setMessage(wnd.codeX.h, (void*)MAKELONG(WRITE, XWEBSOCKET), (void*)b, (void*)sz);

      if ( e > 0 )
      {
        if ( SendMessage(wnd.item[XM_CHECK2].hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
        {
          raw_buffer(b, sz, raw);
          LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "WebSocket", "WebSocket Write to [%d] SUCCESS - %s\r\n", (wnd.codeX.modul[XWEBSOCKET].fdset+idx)->a[0], raw);
        }
      }
      else
      {
        if ( SendMessage(wnd.item[XM_CHECK2].hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
        {
          raw_buffer(b, sz, raw);
          LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "WebSocket", "WebSocket Write to [%d] Fail - %s\r\n", (wnd.codeX.modul[XWEBSOCKET].fdset+idx)->a[0], raw);
        }
      }



      wnd.item[XM_STATIC2].count++;
      if ( wnd.item[XM_STATIC2].count && ((wnd.item[XM_STATIC2].count%COUNT_MOD) == 0) )
      {
        wnd.item[XM_STATIC2].color[0] = (wnd.item[XM_STATIC2].color[0]==COLOR_SENT1?COLOR_SENT2:COLOR_SENT1);
        if ( e > 0 )
        {
          #if LVLOG_LEVEL_5
          raw_buffer(b, sz, raw);
          LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "WebSocket", "WebSocket Write to [%d] Success[%d] - %s\r\n", (wnd.codeX.modul[XWEBSOCKET].fdset+idx)->a[0], wnd.item[XM_STATIC2].count+1, raw);
          #endif
        }
        else
        {
          #if LVLOG_LEVEL_5
          raw_buffer(b, sz, raw);
          LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "WebSocket", "WebSocket Write to [%d] Fail[%d] - %s\r\n", (wnd.codeX.modul[XWEBSOCKET].fdset+idx)->a[0], wnd.item[XM_STATIC2].count+1, raw);
          #endif
        }
      }
      SetBkColorMessage(wnd.item[XM_STATIC2].hwnd, &wnd.item[XM_STATIC2], wnd.item[XM_STATIC2].color[0]);
    }
  }
  return e;
}


int32_t fxDBRouting(uint8_t* b, int32_t sz)
{
  int32_t e = 0;
  uint8_t query[4096] = {0};

  if (wnd.hdbc != 0)
  {
    e = fxSSFDBWrite(wnd.hdbc, (int8_t*)b, (int32_t)sz, query);

    if ( e == 0 )
    {
      if ( SendMessage(wnd.item[XM_CHECK2].hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
        LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "DB", "Query SUCCESS - %s \r\n", query);
    }
    else
    {
      if ( SendMessage(wnd.item[XM_CHECK2].hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
        LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "DB", "Query Fail - %s \r\n", query);
    }


    wnd.item[XM_STATIC3].count++;
    if ( wnd.item[XM_STATIC3].count && ((wnd.item[XM_STATIC3].count%DB_COUNT_MOD) == 0) )
    {
      if (e == 0)
      {
        #if LVLOG_LEVEL_0
        if ( SendMessage(wnd.item[XM_CHECK2].hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
          LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "DB", "Query SUCCESS - %s \r\n", query);
        #endif
        wnd.item[XM_STATIC3].color[0] = (wnd.item[XM_STATIC3].color[0]==COLOR_SENT1?COLOR_SENT2:COLOR_SENT1);
        #if LVLOG_LEVEL_5
        LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "DB", "Query Success [%d] \r\n", wnd.item[XM_STATIC3].count+1);
        #endif
        SetBkColorMessage(wnd.item[XM_STATIC3].hwnd, &wnd.item[XM_STATIC3], wnd.item[XM_STATIC3].color[0]);
      }
      else
      {
        #if LVLOG_LEVEL_0
        if ( SendMessage(wnd.item[XM_CHECK2].hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
          LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "DB", "Query FAIL - %s \r\n", query);
        #endif
        SetBkColorMessage(wnd.item[XM_STATIC3].hwnd, &wnd.item[XM_STATIC3], COLOR_FAIL);
      }
      wnd.item[XM_STATIC3].count = 0;
    }
  }
  else
  {
    fxDBOpen();
  }

  return e;
}

/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                                  ROUTING                                    */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/


void* asyncDBWrite(void* arg)
{
  int32_t e = 0;
  uint8_t query[4096] = {0};
  ASyncParam* p = (ASyncParam*)arg;


  p->SR |= 0x80000000;

  for ( ; ; )
  {
    if ( p->SR&0x00000001 )
    {
      if (wnd.hdbc != 0)
      {
        e = fxSSFDBWrite(wnd.hdbc, (int8_t*)p->b, (int32_t)p->sz, query);
        if (e == 0)
        {
          #if LVLOG_LEVEL_0
          if ( SendMessage(wnd.item[XM_CHECK2].hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
            LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "DB", "Query SUCCESS - %s \r\n", query);
          #endif
          wnd.item[XM_STATIC3].count++;
          if ( wnd.item[XM_STATIC3].count && ((wnd.item[XM_STATIC3].count%COUNT_MOD) == 0) )
          {
            wnd.item[XM_STATIC3].color[0] = (wnd.item[XM_STATIC3].color[0]==COLOR_SENT1?COLOR_SENT2:COLOR_SENT1);
            #if LVLOG_LEVEL_5
            LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "DB", "Query Success [%d] \r\n", wnd.item[XM_STATIC3].count+1);
            #endif
          }
          SetBkColorMessage(wnd.item[XM_STATIC3].hwnd, &wnd.item[XM_STATIC3], wnd.item[XM_STATIC3].color[0]);
        }
        else
        {
          #if LVLOG_LEVEL_0
          if ( SendMessage(wnd.item[XM_CHECK2].hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
            LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "DB", "Query FAIL - %s \r\n", query);
          #endif
          SetBkColorMessage(wnd.item[XM_STATIC3].hwnd, &wnd.item[XM_STATIC3], COLOR_FAIL);
        }
      }
      else
      {
        fxDBOpen();
      }

      p->SR &= 0xFFFFFFFE;
    }
    delay(1);
  }
  p->SR = 0;
  thread_exit(0, 0);
  return 0;
}



void fxTransfer(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t tid = 0;


  if ( wnd.aparam.SR == 0 )
  {
    wnd.aparam.SR |= 0x00000001;
    memcpy(wnd.aparam.b, wparam, (int32_t)lparam);
    wnd.aparam.sz = (int32_t)lparam;
    thread_create(asyncDBWrite, (void*)&wnd.aparam, (void*)&tid);
  }
  else
  {
    if ( (wnd.aparam.SR & 0x00000001) == 0 )
    {
      memcpy(wnd.aparam.b, wparam, (int32_t)lparam);
      wnd.aparam.sz = (int32_t)lparam;
      wnd.aparam.SR |= 0x00000001;
    }
  }

  #if 0
  if (wnd.hdbc != 0)
  {
    e = fxSSFDBWrite(wnd.hdbc, (int8_t*)wparam, (int32_t)lparam, query);
    if (e == 0)
    {
      #if LVLOG_LEVEL_0
      if ( SendMessage(wnd.item[XM_CHECK2].hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
        LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "DB", "Query SUCCESS - %s \r\n", query);
      #endif
      wnd.item[XM_STATIC3].count++;
      if ( wnd.item[XM_STATIC3].count && ((wnd.item[XM_STATIC3].count%COUNT_MOD) == 0) )
      {
        wnd.item[XM_STATIC3].color[0] = (wnd.item[XM_STATIC3].color[0]==COLOR_SENT1?COLOR_SENT2:COLOR_SENT1);
        #if LVLOG_LEVEL_5
        LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "DB", "Query Success [%d] \r\n", wnd.item[XM_STATIC3].count+1);
        #endif
      }
      SetBkColorMessage(wnd.item[XM_STATIC3].hwnd, &wnd.item[XM_STATIC3], wnd.item[XM_STATIC3].color[0]);
    }
    else
    {
      #if LVLOG_LEVEL_0
      if ( SendMessage(wnd.item[XM_CHECK2].hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
        LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "DB", "Query FAIL - %s \r\n", query);
      #endif
      SetBkColorMessage(wnd.item[XM_STATIC3].hwnd, &wnd.item[XM_STATIC3], COLOR_FAIL);
    }
  }
  else
  {
    fxDBOpen();
  }
  #endif
  fxWebSocketRouting((uint8_t*)wparam, (int32_t)lparam);


  ////GetComboText(gp->hitem[COMBO_DISPLAY_TYPE_WSGW], st);

  //fprint_raw_buffer(0, (char*)lparam, (int)wparam, vbuf);
  //LVLog(gp->hitem[LIST_WSGW_WS_LOG], gp->hitem[CHECK_WSGW_LOG], MAX_LINE, &gp->log, "log", "WebSocket", "%s", vbuf);
}


void* fxCheckerForDatabase(void* arg)
{
  XWND* p = (XWND*)arg;
  int32_t i = 0, j=0;

  set_hex_semaphore(&p->SR, 0x00000004, 0x00000004);
  for ( ; ; )
  {
    for ( i=0 ; i<MAX_BUF_SZ ; i+=20 )
    {
      if ( p->backbuf[i] == 0 ) break;
      fxDBRouting(&p->backbuf[i], 20);
    }
    delay(100);
  }
  set_hex_semaphore(&p->SR, 0x00000008, 0x00000000);

  return 0;
}

void* fxCheckerForWebSocket(void* arg)
{
  XWND* p = (XWND*)arg;
  int32_t i = 0, j=0;

  set_hex_semaphore(&p->SR, 0x00000001, 0x00000001);
  for ( ; ; )
  {
    for ( i=0 ; i<MAX_BUF_SZ ; i+=20 )
    {
      if ( p->backbuf[i] == 0 ) break;
      fxWebSocketRouting(&p->backbuf[i], 20);
    }
    delay(100);

    #if 0
    OutputDebugString("**************************************************\n");
    for ( i=0, j=0 ; i<1024 ; i++, j+=3 )
    {
      if ( i )
        if ( (i%40)==0 ) { tmp[j]='\n'; j++; }
        else if ( (i%20)==0 ) { tmp[j]=' '; j++; tmp[j]=' '; j++; }
        else if ( (i%10)==0 ) { tmp[j]=' '; j++; }
      sprintf(&tmp[j], "%02X ", p->backbuf[i]);
    }
    tmp[j-1]='\n';
    OutputDebugString(tmp);
    OutputDebugString("**************************************************\n");
    #endif
    delay(1);
  }
  set_hex_semaphore(&p->SR, 0x00000002, 0x00000000);

  return 0;
}



/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                                 CODE X                                      */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
void* fxDisplayFDSet(XWND* p, uint32_t id, int32_t fd, int8_t* title)
{
  uint8_t fds[FD_SETSIZE*8] = {0};
  uint32_t i =0;

  for ( i=0 ; i<FD_SETSIZE/4 ; i++ )
  {
    sprintf(&fds[i*6], "[%04d]", (uint32_t)(p->codeX.modul[id].fdset+i)->a[0]);
  }
  LVLog( p->item[XM_LIST1].hwnd, p->item[XM_CHECK1].hwnd, MAX_LINE, &p->log, "log", "Socket", "FDSet ->  %s %04d->(%s) \r\n", title, fd, fds);

  return 0;
}

void* fxStoreBuffer(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t idx = 1;
  int32_t ofst = 0;
  //uint8_t* p = (uint8_t*)wparam;
  //uint8_t tmp[1024] = {0};
  //int32_t i = 0, j=0;

  //OutputDebugString("=================================================\n");
  //for ( i=0, j=0 ; i<(int32_t)lparam ; i++, j+=3 )
  //  sprintf(&tmp[j], "%02X ", *(p+i));
  //OutputDebugString(tmp);
  //OutputDebugString("\r\n=================================================\n");


  fxWebSocketRouting((uint8_t*)wparam, (int32_t)lparam);
  fxDBRouting((uint8_t*)wparam, (int32_t)lparam);



  //
  #if 0
  for ( idx=1,ofst=0 ; ofst<MAX_BUF_SZ ; ofst+=20 )
  {
    if ( wnd.backbuf[idx+ofst]==0x00 || wnd.backbuf[idx+ofst]==*(uint8_t*)(wparam+idx) )
    {
      memcpy(&wnd.backbuf[ofst], (uint8_t*)wparam, (int32_t)lparam);
      break;
    }
  }
  #endif
  return 0;
}


void* fxCallbackSocket(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t fd=0;
  int8_t raw[8192];
	switch( LOWORD((uint32_t)msg) )
	{
	case FDSCRPTR:
    #if LVLOG_LEVEL_0
    if ( SendMessage(wnd.item[XM_CHECK2].hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      raw_buffer((int8_t*)wparam, (int32_t)lparam, raw);
      LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "Socket", "SOCKET FD - %d\r\n", (uint32_t)wparam);
    }
    #endif
		break;
	case READ:
    #if LVLOG_LEVEL_0
    if ( SendMessage(wnd.item[XM_CHECK2].hwnd, BM_GETCHECK, 0, 0) == BST_CHECKED )
    {
      raw_buffer((int8_t*)wparam, (int32_t)lparam, raw);
      LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "Socket", "SOCKET READ (%d) %s\r\n", (uint32_t)lparam, raw);
    }
    #endif
    /////SendMessage(wnd.hdlg, XWM_TRANSFER, (WPARAM)wparam, (LPARAM)lparam);
    fxStoreBuffer(hwnd, msg, wparam, lparam);
		break;

	default:
		if ( (uint32_t)lparam == 0xE000FD0A )
		{
      LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "Socket", "Socket Open Success (%d) \r\n", (uint32_t)wparam);
      SetBkColorMessage(wnd.item[XM_STATIC1].hwnd, &wnd.item[XM_STATIC1], COLOR_SYSTEM_RUN);
		}
		else if ( (uint32_t)lparam == 0xE000FD1A )
		{
      LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "Socket", "Socket Connected (%d) \r\n", (uint32_t)wparam);
      SetBkColorMessage(wnd.item[XM_STATIC1].hwnd, &wnd.item[XM_STATIC1], COLOR_CONNECTED);

      wnd.codeX.getMessage(wnd.codeX.h, MAKELONG(FDSCRPTR,  XSOCKET), &fd, sizeof(fd));
      wnd.codeX.getMessage(wnd.codeX.h, MAKELONG(FDSCRPTRS, XSOCKET), &wnd.codeX.modul[XSOCKET].fdset, sizeof(wnd.codeX.modul[XSOCKET].fdset));
      fxDisplayFDSet(&wnd, XSOCKET, fd, "Socket Client Connected");
		}
		else if ( ((uint32_t)lparam==0xE000FDFA) || ((uint32_t)lparam==0xE000101F) )
		{
      LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "Socket", "Socket Disconnected (%d) \r\n", (uint32_t)wparam);
      SetBkColorMessage(wnd.item[XM_STATIC1].hwnd, &wnd.item[XM_STATIC1], COLOR_DISCONNECTED);

      wnd.codeX.getMessage(wnd.codeX.h, MAKELONG(FDSCRPTR,  XSOCKET), &fd, sizeof(fd));
      wnd.codeX.getMessage(wnd.codeX.h, MAKELONG(FDSCRPTRS, XSOCKET), &wnd.codeX.modul[XSOCKET].fdset, sizeof(wnd.codeX.modul[XSOCKET].fdset));
      fxDisplayFDSet(&wnd, XSOCKET, fd, "Socket Client Disonnected");
      memclr(&wnd.backbuf, MAX_BUF_SZ);
		}
    else if ( (uint32_t)lparam == 0xE000101A )
    {
      wnd.item[XM_STATIC1].count++;
      if ( wnd.item[XM_STATIC1].count && ((wnd.item[XM_STATIC1].count%COUNT_MOD) == 0) )
      {
        wnd.item[XM_STATIC1].color[0] = (wnd.item[XM_STATIC1].color[0]==COLOR_RCVD1?COLOR_RCVD2:COLOR_RCVD1);
        #if LVLOG_LEVEL_5
        LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "Socket", "Socket Read Success[%d] \r\n", wnd.item[XM_STATIC1].count+1);
        #endif
      }
      SetBkColorMessage(wnd.item[XM_STATIC1].hwnd, &wnd.item[XM_STATIC1], wnd.item[XM_STATIC1].color[0]);
    }
		break;
	}
  return 0;
}

void* fxCallbackWebSocket(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t fd=0;
  int8_t raw[1024];


  #if LVLOG_LEVEL_0
  //LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "WebSocket", "WebSocket STATUS (%d) (%08X)\r\n", (uint32_t)wparam, (uint32_t)lparam);
  #endif

	switch( LOWORD((uint32_t)msg) )
	{
	//case READ:
 //   raw_buffer((int8_t*)wparam, (int32_t)lparam, raw);
 //   LVLog( wnd.hitem[XM_LIST1], wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "Socket", "SOCKET READ (%d) %s\r\n", (uint32_t)lparam, raw);
 //   PostMessage(wnd.hdlg, XWM_TRANSFER, (WPARAM)wparam, (LPARAM)lparam);
	//	break;

	default:
		if ( (uint32_t)lparam == 0xE000FD0A )
		{
      LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "WebSocket", "WebSocket Open Success (%d) \r\n", (uint32_t)wparam);
      SetBkColorMessage(wnd.item[XM_STATIC2].hwnd, &wnd.item[XM_STATIC2], COLOR_SYSTEM_RUN);
		}
		else if ( (uint32_t)lparam == 0xE000FD1A )
		{
      LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "WebSocket", "WebSocket Client Connected(%d) \r\n", (uint32_t)wparam);
      SetBkColorMessage(wnd.item[XM_STATIC2].hwnd, &wnd.item[XM_STATIC2], COLOR_CONNECTED);
      wnd.codeX.getMessage(wnd.codeX.h, MAKELONG(FDSCRPTR,  XWEBSOCKET), &fd, sizeof(fd));
      wnd.codeX.getMessage(wnd.codeX.h, MAKELONG(FDSCRPTRS, XWEBSOCKET), &wnd.codeX.modul[XWEBSOCKET].fdset, sizeof(wnd.codeX.modul[XWEBSOCKET].fdset));
      fxDisplayFDSet(&wnd, XWEBSOCKET, fd, "WebSocket Client Connected");
		}
		else if ( ((uint32_t)lparam == 0xE000FDFA) || ((uint32_t)lparam == 0xE000101F) )
		{
      LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "WebSocket", "WebSocket Client Disonnected(%d) %d\r\n", (uint32_t)wparam, GetLastError());
      SetBkColorMessage(wnd.item[XM_STATIC2].hwnd, &wnd.item[XM_STATIC2], COLOR_DISCONNECTED);
      wnd.codeX.getMessage(wnd.codeX.h, MAKELONG(FDSCRPTR,  XWEBSOCKET), &fd, sizeof(fd));
      wnd.codeX.getMessage(wnd.codeX.h, MAKELONG(FDSCRPTRS, XWEBSOCKET), &wnd.codeX.modul[XWEBSOCKET].fdset, sizeof(wnd.codeX.modul[XWEBSOCKET].fdset));
      fxDisplayFDSet(&wnd, XWEBSOCKET, fd, "WebSocket Client Disonnected");
		}
		else if ( ((uint32_t)lparam == 0xE000100A) || ((uint32_t)lparam == 0xE000ECDA) )
    {
      //wnd.item[XM_STATIC2].count++;
      //if ( wnd.item[XM_STATIC2].count && ((wnd.item[XM_STATIC2].count%COUNT_MOD) == 0) )
      //{
      //  wnd.item[XM_STATIC2].color[0] = (wnd.item[XM_STATIC2].color[0]==COLOR_SENT1?COLOR_SENT2:COLOR_SENT1);
      //  #if LVLOG_LEVEL_5
      //  LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "WebSocket", "WebSocket Write Success[%d] \r\n", wnd.item[XM_STATIC2].count+1);
      //  #endif
      //}
      //SetBkColorMessage(wnd.item[XM_STATIC2].hwnd, &wnd.item[XM_STATIC2], wnd.item[XM_STATIC2].color[0]);
    }



		//if ( (uint32_t)lparam == 0xE000FD0A )
		//{
  //    LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "WebSocket", "WebSocket Open Success (%d) \r\n", (uint32_t)wparam);
  //    SetBkColorMessage(wnd.item[XM_STATIC2].hwnd, &wnd.item[XM_STATIC2], COLOR_SYSTEM_RUN);
		//}
		//else if ( (uint32_t)lparam == 0xE000FD1A )
		//{
  //    LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "WebSocket", "WebSocket Connected (%d) \r\n", (uint32_t)wparam);
  //    SetBkColorMessage(wnd.item[XM_STATIC2].hwnd, &wnd.item[XM_STATIC2], COLOR_CONNECTED);
  //    wnd.codeX.getMessage(wnd.codeX.h, MAKELONG(FDSCRPTR,  XWEBSOCKET), &fd, sizeof(fd));
  //    wnd.codeX.getMessage(wnd.codeX.h, MAKELONG(FDSCRPTRS, XWEBSOCKET), &wnd.codeX.modul[XWEBSOCKET].fdset, sizeof(wnd.codeX.modul[XWEBSOCKET].fdset));
  //    fxDisplayFDSet(&wnd, XWEBSOCKET, fd, "WebSocket Client Connected");

		//}
		//else if ( (uint32_t)lparam == 0xE000FDFA )
		//{
  //    LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "WebSocket", "WebSocket Disconnected (%d) \r\n", (uint32_t)wparam);
  //    SetBkColorMessage(wnd.item[XM_STATIC2].hwnd, &wnd.item[XM_STATIC2], COLOR_DISCONNECTED);
  //    wnd.codeX.getMessage(wnd.codeX.h, MAKELONG(FDSCRPTR,  XWEBSOCKET), &fd, sizeof(fd));
  //    wnd.codeX.getMessage(wnd.codeX.h, MAKELONG(FDSCRPTRS, XWEBSOCKET), &wnd.codeX.modul[XWEBSOCKET].fdset, sizeof(wnd.codeX.modul[XWEBSOCKET].fdset));
  //    fxDisplayFDSet(&wnd, XWEBSOCKET, fd, "WebSocket Client Disconnected");

		//}
		break;
	}
  return 0;
}


void* fxCallbackSerial(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t fd=0;
  int8_t raw[1024];
	switch( LOWORD((uint32_t)msg) )
	{
	case READ:
    raw_buffer((int8_t*)wparam, (int32_t)lparam, raw);
    LVLog( wnd.item[XM_LIST1].hwnd, wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "Serial", "SERIAL READ (%d) %s\r\n", (uint32_t)lparam, raw);
		break;
  }
  return 0;
}


void* fxCallback(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
   //LVLog( wnd.hitem[XM_LIST1], wnd.item[XM_CHECK1].hwnd, MAX_LINE, &wnd.log, "log", "Socket", " codeXStatusSocket --->  %04X %04X %08X\r\n", 0x0000FFFF&(uint32_t)msg, (0xFFFF0000&(uint32_t)msg)>>16, (uint32_t)lparam );



  switch( HIWORD((uint32_t)msg) )
  {
	case XHTTP:
    break;
	case XHTTPD:
    break;
	case XPACKET:
    break;
	case XPROTOCOL:
    break;
	case XSERIAL:
    fxCallbackSerial(hwnd, msg, wparam, lparam);
    break;
	case XSOCKET:
    fxCallbackSocket(hwnd, msg, wparam, lparam);
    break;
	case XWEBSOCKET:
    fxCallbackWebSocket(hwnd, msg, wparam, lparam);
    break;
	case XXML:
    break;
  }

	return 0;
}




/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                             WND Subclassing                                 */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
void* fxStatic1Proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(msg)
  {
    case WM_CTLCOLORSTATIC:
      return (BOOL)SetBackgroundColor(&wnd.item[XM_STATIC1], (COLORREF)lparam);
      break;

    case WM_PAINT:
      InvalidateRect(hwnd, 0, TRUE);
      break;
  }
  return CallWindowProc(wnd.item[XM_STATIC1].wproc, hwnd, msg, wparam, lparam);
}


void* fxStatic2Proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(msg)
  {
    case WM_CTLCOLORSTATIC:
      return (BOOL)SetBackgroundColor(&wnd.item[XM_STATIC2], (COLORREF)lparam);
      break;

    case WM_PAINT:
      InvalidateRect(hwnd, 0, TRUE);
      break;
  }
  return CallWindowProc(wnd.item[XM_STATIC2].wproc, hwnd, msg, wparam, lparam);
}

void* fxStatic3Proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(msg)
  {
    case WM_CTLCOLORSTATIC:
      return (BOOL)SetBackgroundColor(&wnd.item[XM_STATIC3], (COLORREF)lparam);
      break;

    case WM_PAINT:
      InvalidateRect(hwnd, 0, TRUE);
      break;
  }
  return CallWindowProc(wnd.item[XM_STATIC3].wproc, hwnd, msg, wparam, lparam);
}


/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*                                                                             */
/*                                                                             */
/*                                   WND                                       */
/*                                                                             */
/*                                                                             */
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
/*******************************************************************************/
void init_window(HWND hwnd, XWND* p)
{
  p->hdlg = hwnd;

  p->item[XM_LIST1].hwnd         = GetDlgItem(hwnd, IDC_LIST1);
  p->item[XM_STATIC1].hwnd       = GetDlgItem(hwnd, IDC_STATIC1);
  p->item[XM_STATIC2].hwnd       = GetDlgItem(hwnd, IDC_STATIC2);
  p->item[XM_STATIC3].hwnd       = GetDlgItem(hwnd, IDC_STATIC3);
  p->item[XM_STATIC_TITLE1].hwnd = GetDlgItem(hwnd, IDC_STATIC_TITLE1);
  p->item[XM_STATIC_TITLE2].hwnd = GetDlgItem(hwnd, IDC_STATIC_TITLE2);
  p->item[XM_STATIC_TITLE3].hwnd = GetDlgItem(hwnd, IDC_STATIC_TITLE3);
  p->item[XM_CHECK1].hwnd        = GetDlgItem(hwnd, IDC_CHECK1);
  p->item[XM_CHECK2].hwnd        = GetDlgItem(hwnd, IDC_CHECK2);
  p->item[XM_BUTTON1].hwnd       = GetDlgItem(hwnd, IDC_BUTTON1);

  InitListView(p->item[XM_LIST1].hwnd);

  p->item[XM_STATIC1].wproc = SetWindowLong(p->item[XM_STATIC1].hwnd, GWL_WNDPROC, (LONG)fxStatic1Proc);
  p->item[XM_STATIC2].wproc = SetWindowLong(p->item[XM_STATIC2].hwnd, GWL_WNDPROC, (LONG)fxStatic2Proc);
  p->item[XM_STATIC3].wproc = SetWindowLong(p->item[XM_STATIC3].hwnd, GWL_WNDPROC, (LONG)fxStatic3Proc);

  //SendMessage(p->item[XM_CHECK1].hwnd, BM_SETCHECK, BST_CHECKED, 0);
  //SendMessage(p->item[XM_CHECK2].hwnd, BM_SETCHECK, BST_CHECKED, 0);

  ShowWindow(p->item[XM_BUTTON1].hwnd, SW_HIDE);
}


void* fxWM_CTLCOLORSTATIC(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  if ( (HWND)lparam == wnd.item[XM_STATIC1].hwnd )
  {
    return SetBackgroundColor(&wnd.item[XM_STATIC1], wnd.item[XM_STATIC1].color[0]);
  }
  else if ( (HWND)lparam == wnd.item[XM_STATIC2].hwnd )
  {
    return SetBackgroundColor(&wnd.item[XM_STATIC2], wnd.item[XM_STATIC2].color[0]);
  }
  else if ( (HWND)lparam == wnd.item[XM_STATIC3].hwnd )
  {
    return SetBackgroundColor(&wnd.item[XM_STATIC3], wnd.item[XM_STATIC3].color[0]);
  }
  return 0;
}

void* fxWM_CREATE(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  return 0 ;
}

void* fxWM_DESTROY(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  codeXend(&wnd.codeX);
  return 0;
}

void* fxWM_INITDIALOG(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  int32_t _index = 0;
  int8_t _top_title[256];

  init_window(hwnd, &wnd);

  sprintf(_top_title, ("%s : (%d)) "), (TOP_TITLE), (int32_t)GetCurrentThreadId());
  SetWindowText(hwnd, (_top_title));

  init_tray(wnd.hinst[0], hwnd);

  loadInterface(wnd.h);
  fxDBOpen();
  codeXmain(wnd.h, &wnd.codeX);

  ////// create thread for websocket
  thread_create(fxCheckerForWebSocket, (void*)(&wnd), 0);
  get_hex_semaphore(&wnd.SR, 0x00000001, 0x00000001, 8192);

  ////// create thread for database
  thread_create(fxCheckerForDatabase, (void*)(&wnd), 0);
  get_hex_semaphore(&wnd.SR, 0x00000004, 0x00000004, 8192);

  return (void*)TRUE;
}


void* fxIDC_BUTTON1(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  wnd.codeX.setMessage(wnd.codeX.h, (void*)MAKELONG(WRITE, XSERIAL), (void*)"1234", (void*)4);

  return (void*)TRUE;
}


void* fxWM_COMMAND(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(LOWORD(wparam))
  {
    case IDC_BUTTON1:
      fxIDC_BUTTON1(hwnd, msg, wparam, lparam);
      break;

    default:
      ontray_command(hwnd, msg, wparam, lparam);
      break;
  }

  return (void*)TRUE;
}



void* fxWM_NOTIFY(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  //#if defined USER_TAB

  //#else
  //int32_t idx = SendMessage(wnd.hitem[TAB_CONTROL], TCM_GETCURSEL, 0, 0);
  //int32_t i=0;


  //for ( i=0 ; i<MAX_TAB ; i++ )
  //{
  //  ShowWindow(wnd.htabwnd[i], (idx==i)?SW_SHOW:SW_HIDE);
  //}
  //#endif
  return (void*)TRUE;
}



void* fxWM_PAINT(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{

  InvalidateRect(hwnd, 0, TRUE);
  return (void*)0;
}

static uint8_t tmr = 0;

BOOL CALLBACK dlgproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  switch(msg)
  {
    case WM_INITDIALOG:
      //SetTimer(hwnd, 1, 1000, 0);
      return (BOOL)fxWM_INITDIALOG(hwnd, msg, wparam, lparam);

    case WM_CREATE:
      return (BOOL)fxWM_CREATE(hwnd, msg, wparam, lparam);

    case WM_COMMAND:
      return (BOOL)fxWM_COMMAND(hwnd, msg, wparam, lparam);

    case WM_NOTIFY:
      return (BOOL)fxWM_NOTIFY(hwnd, msg, wparam, lparam);

    case WM_PAINT:
      return (BOOL)fxWM_PAINT(hwnd, msg, wparam, lparam);
      break;


    case WM_CTLCOLORSTATIC:
      return (BOOL)fxWM_CTLCOLORSTATIC(hwnd, msg, wparam, lparam);
      break;


    case WM_TIMER:
      //if ( tmr%2 )
      //{
      //  SetBkColorMessage(hwnd, &wnd.item[XM_STATIC2], RGB(0, 0xFF,0));
      //}
      //else
      //{
      //  SetBkColorMessage(hwnd, &wnd.item[XM_STATIC2], RGB(0xFF, 0xFF,0));
      //}
      //tmr++;
      //InvalidateRect(hwnd, 0, TRUE);      
      break;




    case XWM_TRANSFER:
      fxTransfer(hwnd, msg, wparam, lparam);
      break;


    case WM_CLOSE:
    case WM_DESTROY:
    default:
      return ontray_proc(hwnd, msg, wparam, lparam);
      break;
  }

  return 0;
}



void setup(HINSTANCE hinst, HINSTANCE hpinst, LPSTR cmd, int32_t nshow)
{
  wnd.hinst[0] = hinst;
  wnd.hinst[1] = hpinst;

  memset(&wnd.codeX, 0, sizeof(CodeX));

  wnd.codeX.callback = fxCallback;
  wnd.codeX.obj = &wnd;
}


int32_t WINAPI WinMain(HINSTANCE hinst, HINSTANCE hpinst, LPSTR cmd, int32_t nshow)
{
  setup(hinst, hpinst, cmd, nshow);

  DialogBox(hinst, (LPCSTR)IDD_DIALOG1, HWND_DESKTOP, (DLGPROC)dlgproc);
  return TRUE;
}
