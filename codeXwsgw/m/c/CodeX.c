#include <CodeX.h>


void* codeXStatusSerial(void* h, void* msg, void* wparam, void* lparam)
{
	CodeX* p = (CodeX*)h;
	static uint32_t bpos = 0;

	switch( LOWORD((uint32_t)msg) )
	{
	default:
	  p->callback(p->obj, msg, wparam, lparam);
		break;
	}

	return 0;
}


void* codeXStatusSocket(void* h, void* msg, void* wparam, void* lparam)
{
	CodeX* p = (CodeX*)h;
	static uint32_t bpos = 0;

	switch( LOWORD((uint32_t)msg) )
	{
	case READ:
		//{
		//	uint8_t* p = (uint8_t*)wparam;
		//	uint8_t tmp[1024] = {0};
		//	int32_t i = 0, j=0;

		//	OutputDebugString(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
		//	for ( i=0, j=0 ; i<(int32_t)lparam ; i++, j+=3 )
		//		sprintf(&tmp[j], "%02X ", *(p+i));
		//	OutputDebugString(tmp);
		//	OutputDebugString("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		//}
		on_protocol_proc(shof_protocol_info, (int8_t*)wparam, (int32_t)lparam, p->buf, &bpos, on_shof_protocol_check, h);
		break;

	default:
	  p->callback(p->obj, msg, wparam, lparam);
		break;
	}

	return 0;
}

void* codeXStatusWebSocket(void* h, void* msg, void* wparam, void* lparam)
{
	CodeX* p = (CodeX*)h;
	switch( LOWORD((uint32_t)msg) )
	{
	default:
	  p->callback(p->obj, msg, wparam, lparam);
		break;
	}


	return 0;
}

void* codeXStatus(void* h, void* msg, void* wparam, void* lparam)
{
	CodeX* p = (CodeX*)h;
	switch( HIWORD((uint32_t)msg) )
	{
	case XSERIAL:
		codeXStatusSerial(h,msg,wparam,lparam);
		break;
	case XSOCKET:
		codeXStatusSocket(h,msg,wparam,lparam);
		break;
	case XWEBSOCKET:
		#if 0
		{
			uint8_t tmp[128];
			uint8_t msg[1024] = {0};
			int32_t i = 0;
			int32_t j = 0;
			uint8_t* p = (uint8_t*)wparam;
			uint32_t e = GetLastError();
			//OutputDebugString("**********************************************************************************\n");
			if ( e > 0 )
			{
				sprintf(tmp, "%08X %X %d\r\n", LOWORD((uint32_t)lparam), e,e);
				OutputDebugString(tmp);
			}
			#if 0
			if ( p != 0 )
			{
				for ( i=0 ; i<128 ; i++, j+=3 )
				{
					if ( i )
						if ( (i%128)==0 ) { msg[j]='\n'; j++;  }
						else if ( (i%16)== 0 ) { msg[j]=' '; j++; msg[j]=' '; j++;}
						else if ( (i%8)== 0 ) {msg[j]=' '; j++; }
					sprintf(&msg[j], "%02X ", *(p+i));
				}
				msg[j-1] = '\n';
				OutputDebugString(msg);
			}
			#endif
			//OutputDebugString("**********************************************************************************\n");
		}
		#endif
		codeXStatusWebSocket(h,msg,wparam,lparam);
		break;
	}


	return 0;
}



void* loadInterface(void* hdl)
{
  if ( hdl == 0 )	hdl = LoadLibrary(MODULE);

  *(FARPROC*)&get_hex_semaphore        = GetProcAddress(hdl,"get_hex_semaphore");
  *(FARPROC*)&set_hex_semaphore        = GetProcAddress(hdl,"set_hex_semaphore");
  *(FARPROC*)&check_hex_semaphore      = GetProcAddress(hdl,"check_hex_semaphore");
  *(FARPROC*)&thread_create            = GetProcAddress(hdl,"thread_create");
  *(FARPROC*)&thread_exit              = GetProcAddress(hdl,"thread_exit");
  *(FARPROC*)&get_curr_time            = GetProcAddress(hdl,"get_curr_time");
	*(FARPROC*)&log_write_ex             = GetProcAddress(hdl,"log_write_ex");

  return hdl;  
}














void* asyncRun(void* arg)
{
  int32_t e = 0;
	CodeX* p = (CodeX*)arg;

  set_hex_semaphore(&p->SR, 0x00000001, 0x00000001);

	p->setMessage(p->h, (void*)MAKELONG(XM_DELAY_0 , XSOCKET),   (void*)"3000",            (void*)strlen("3000"));
	p->setMessage(p->h, (void*)MAKELONG(XM_IP      , XSOCKET),   (void*)"127.0.0.1",       (void*)strlen("127.0.0.1"));
	p->setMessage(p->h, (void*)MAKELONG(XM_PORT    , XSOCKET),   (void*)"7870",            (void*)strlen("7870"));
	p->setMessage(p->h, (void*)MAKELONG(XM_PROTO   , XSOCKET),   (void*)"TCP",             (void*)strlen("TCP"));
	p->setMessage(p->h, (void*)MAKELONG(XM_CSTYPE  , XSOCKET),   (void*)"SERVER",          (void*)strlen("SERVER"));
	p->setMessage(p->h, (void*)MAKELONG(XM_CASTTYPE, XSOCKET),   (void*)"UNICAST",         (void*)strlen("UNICAST"));
	p->setMessage(p->h, (void*)MAKELONG(XM_ECHOMODE, XSOCKET),   (void*)"0",               (void*)strlen("0"));
	p->setMessage(p->h, (void*)MAKELONG(ENABLE     , XSOCKET),  0,  0);
																 
	p->setMessage(p->h, (void*)MAKELONG(XM_DELAY_0 , XWEBSOCKET),   (void*)"3000",        (void*)strlen("3000"));
	p->setMessage(p->h, (void*)MAKELONG(XM_IP      , XWEBSOCKET),   (void*)"127.0.0.1",   (void*)strlen("127.0.0.1"));
	p->setMessage(p->h, (void*)MAKELONG(XM_PORT    , XWEBSOCKET),   (void*)"7810",        (void*)strlen("7810"));
	p->setMessage(p->h, (void*)MAKELONG(XM_CSTYPE  , XWEBSOCKET),   (void*)"SERVER",      (void*)strlen("SERVER"));
	p->setMessage(p->h, (void*)MAKELONG(XM_ECHOMODE, XWEBSOCKET),   (void*)"0",           (void*)strlen("0"));
	p->setMessage(p->h, (void*)MAKELONG(ENABLE     , XWEBSOCKET), 0, 0);

	p->setMessage(p->h, (void*)MAKELONG(XM_DELAY_0, XHTTPD),    (void*)"3000",             (void*)strlen("3000"));
	p->setMessage(p->h, (void*)MAKELONG(XM_IP     , XHTTPD),    (void*)"127.0.0.1",        (void*)strlen("127.0.0.1"));
	p->setMessage(p->h, (void*)MAKELONG(XM_PORT   , XHTTPD),    (void*)"80",               (void*)strlen("80"));
	p->setMessage(p->h, (void*)MAKELONG(XM_HOME   , XHTTPD),    (void*)"/usr/local/www",   (void*)strlen("/usr/local/www"));
	p->setMessage(p->h, (void*)MAKELONG(XM_INDEX  , XHTTPD),    (void*)"index.html",       (void*)strlen("index.html"));
	p->setMessage(p->h, (void*)MAKELONG(ENABLE    , XHTTPD), 0, 0);

  set_hex_semaphore(&p->SR, 0x00000002, 0x00000000);
  thread_exit(0, 0);
  return 0;
}


void* codeXmain(void* hdl, CodeX* p)
{
  int32_t e = 0;
  uint32_t tid;

  if ( hdl == 0 )	hdl = LoadLibrary(MODULE);

  //*(FARPROC*)&p->codeXInitia       = GetProcAddress(hdl,"codeXInitia");
  //*(FARPROC*)&p->codeXFinelia      = GetProcAddress(hdl,"codeXFinelia");
  *(FARPROC*)&p->getMessage        = GetProcAddress((HMODULE)hdl,"codeXGetMessage");
  *(FARPROC*)&p->setMessage        = GetProcAddress((HMODULE)hdl,"codeXSetMessage");
  *(FARPROC*)&p->putMessage        = GetProcAddress((HMODULE)hdl,"codeXPutMessage");

	//p->codeXInitia(&p->h, codeXStatus, p);

	//asyncRun((void*)p);
  //thread_create(asyncRun, (void*)p, (void*)&tid);
  //e = get_hex_semaphore(&p->SR, 0x00000001, 0x00000001, 8192);

	p->setMessage(&p->h, (void*)MAKELONG(INIT, CODEX), 0,0);
	p->setMessage( p->h, (void*)MAKELONG(SYSTEM_CALLBACK, CODEX), codeXStatus, p);


  #if 1
	p->setMessage(p->h, (void*)MAKELONG(XM_DELAY_0    , XWEBSOCKET),   (void*)"3000",               (void*)strlen("3000"));
	p->setMessage(p->h, (void*)MAKELONG(XM_BUFFER_PTR , XWEBSOCKET),   (void*)p->wsck_buf,          (void*)1024);
	p->setMessage(p->h, (void*)MAKELONG(XM_IP         , XWEBSOCKET),   (void*)"127.0.0.1",          (void*)strlen("127.0.0.1"));
	p->setMessage(p->h, (void*)MAKELONG(XM_PORT       , XWEBSOCKET),   (void*)"7810",               (void*)strlen("7810"));
	p->setMessage(p->h, (void*)MAKELONG(XM_CSTYPE     , XWEBSOCKET),   (void*)"SERVER",             (void*)strlen("SERVER"));
	p->setMessage(p->h, (void*)MAKELONG(XM_ECHOMODE   , XWEBSOCKET),   (void*)"0",                  (void*)strlen("0"));
	p->setMessage(p->h, (void*)MAKELONG(XM_KEY        , XWEBSOCKET),   (void*)"shinbaad@gmail.com", (void*)strlen("shinbaad@gmail.com"));
	p->setMessage(p->h, (void*)MAKELONG(XM_TIMEOUT    , XWEBSOCKET),   (void*)"0",                  (void*)strlen("0"));
	p->setMessage(p->h, (void*)MAKELONG(ENABLE        , XWEBSOCKET), 0, 0);


	p->setMessage(p->h, (void*)MAKELONG(XM_DELAY_0    , XSOCKET),   (void*)"3000",               (void*)strlen("3000"));
	p->setMessage(p->h, (void*)MAKELONG(XM_BUFFER_PTR , XSOCKET),   (void*)p->sck_buf,           (void*)1024);
	p->setMessage(p->h, (void*)MAKELONG(XM_IP         , XSOCKET),   (void*)"127.0.0.1",          (void*)strlen("127.0.0.1"));
	p->setMessage(p->h, (void*)MAKELONG(XM_PORT       , XSOCKET),   (void*)"7870",               (void*)strlen("7870"));
	p->setMessage(p->h, (void*)MAKELONG(XM_PROTO      , XSOCKET),   (void*)"TCP",                (void*)strlen("TCP"));
	p->setMessage(p->h, (void*)MAKELONG(XM_CSTYPE     , XSOCKET),   (void*)"SERVER",             (void*)strlen("SERVER"));
	p->setMessage(p->h, (void*)MAKELONG(XM_CASTTYPE   , XSOCKET),   (void*)"UNICAST",            (void*)strlen("UNICAST"));
	p->setMessage(p->h, (void*)MAKELONG(XM_ECHOMODE   , XSOCKET),   (void*)"0",                  (void*)strlen("0"));
	p->setMessage(p->h, (void*)MAKELONG(XM_KEY        , XSOCKET),   (void*)"shinbaad@gmail.com", (void*)strlen("shinbaad@gmail.com"));
	p->setMessage(p->h, (void*)MAKELONG(XM_TIMEOUT    , XSOCKET),   (void*)"7000",               (void*)strlen("7000"));
	p->setMessage(p->h, (void*)MAKELONG(ENABLE        , XSOCKET),  0, 0);


  //p->setMessage(p->h, (void*)MAKELONG(XM_ASYNC_START, XSOCKET), 0, 0);

	//p->setMessage(p->h, (void*)MAKELONG(XM_DELAY_0, XHTTPD),    (void*)"3000",             (void*)strlen("3000"));
	//p->setMessage(p->h, (void*)MAKELONG(XM_IP     , XHTTPD),    (void*)"127.0.0.1",        (void*)strlen("127.0.0.1"));
	//p->setMessage(p->h, (void*)MAKELONG(XM_PORT   , XHTTPD),    (void*)"80",               (void*)strlen("80"));
	//p->setMessage(p->h, (void*)MAKELONG(XM_HOME   , XHTTPD),    (void*)"/usr/local/www",   (void*)strlen("/usr/local/www"));
	//p->setMessage(p->h, (void*)MAKELONG(XM_INDEX  , XHTTPD),    (void*)"index.html",       (void*)strlen("index.html"));
	//p->setMessage(p->h, (void*)MAKELONG(XHTTPD    , XM_ENABLE), 0, 0);


//<CONFIG system="SERIAL" enable="0" port="/dev/ttyS0" baudrate="115200" databit="8" stopbit="1" paritybit="0" blockmode="0" echomode="1" delay="3000" />

	//p->setMessage(p->h, (void*)MAKELONG(XM_DELAY_0  , XSERIAL),   (void*)"3000",               (void*)strlen("3000"));
	//p->setMessage(p->h, (void*)MAKELONG(XM_PORT     , XSERIAL),   (void*)"COM11",              (void*)strlen("COM11"));
	//p->setMessage(p->h, (void*)MAKELONG(XM_BAUDRATE , XSERIAL),   (void*)"9600",               (void*)strlen("9600"));
	//p->setMessage(p->h, (void*)MAKELONG(XM_DATABIT  , XSERIAL),   (void*)"8",                  (void*)strlen("8"));
	//p->setMessage(p->h, (void*)MAKELONG(XM_STOPBIT  , XSERIAL),   (void*)"1",                  (void*)strlen("1"));
	//p->setMessage(p->h, (void*)MAKELONG(XM_PARITYBIT, XSERIAL),   (void*)"0",                  (void*)strlen("0"));
	//p->setMessage(p->h, (void*)MAKELONG(XM_KEY      , XSERIAL),   (void*)"shinbaad@gmail.com", (void*)strlen("shinbaad@gmail.com"));
	//p->setMessage(p->h, (void*)MAKELONG(XM_ENABLE      , XSERIAL), 0, 0);


  #endif

	//p->putMessage(p->h, (void*)MAKELONG(INIT, XXML), (void*)"config.xml", 0);
	//p->putMessage(p->h, (void*)MAKELONG(READ, XXML), 0, 0);

  #if 0
	p->putMessage(p->h, (void*)MAKELONG(XM_DELAY_0 , XSOCKET),   (void*)"3000",            (void*)strlen("3000"));
	p->putMessage(p->h, (void*)MAKELONG(XM_IP      , XSOCKET),   (void*)"127.0.0.1",       (void*)strlen("127.0.0.1"));
	p->putMessage(p->h, (void*)MAKELONG(XM_PORT    , XSOCKET),   (void*)"7870",            (void*)strlen("7870"));
	p->putMessage(p->h, (void*)MAKELONG(XM_PROTO   , XSOCKET),   (void*)"TCP",             (void*)strlen("TCP"));
	p->putMessage(p->h, (void*)MAKELONG(XM_CSTYPE  , XSOCKET),   (void*)"SERVER",          (void*)strlen("SERVER"));
	p->putMessage(p->h, (void*)MAKELONG(XM_CASTTYPE, XSOCKET),   (void*)"UNICAST",         (void*)strlen("UNICAST"));
	p->putMessage(p->h, (void*)MAKELONG(XM_ECHOMODE, XSOCKET),   (void*)"0",               (void*)strlen("0"));
	p->putMessage(p->h, (void*)MAKELONG(ENABLE     , XSOCKET),  0,                         0);

	p->putMessage(p->h, (void*)MAKELONG(XM_DELAY_0 , XWEBSOCKET),   (void*)"3000",        (void*)strlen("3000"));
	p->putMessage(p->h, (void*)MAKELONG(XM_IP      , XWEBSOCKET),   (void*)"127.0.0.1",   (void*)strlen("127.0.0.1"));
	p->putMessage(p->h, (void*)MAKELONG(XM_PORT    , XWEBSOCKET),   (void*)"7810",        (void*)strlen("7810"));
	p->putMessage(p->h, (void*)MAKELONG(XM_CSTYPE  , XWEBSOCKET),   (void*)"SERVER",      (void*)strlen("SERVER"));
	p->putMessage(p->h, (void*)MAKELONG(XM_ECHOMODE, XWEBSOCKET),   (void*)"0",           (void*)strlen("0"));
	p->putMessage(p->h, (void*)MAKELONG(ENABLE     , XWEBSOCKET), 0, 0);

	p->putMessage(p->h, (void*)MAKELONG(XM_DELAY_0, XHTTPD),    (void*)"3000",             (void*)strlen("3000"));
	p->putMessage(p->h, (void*)MAKELONG(XM_IP     , XHTTPD),    (void*)"127.0.0.1",        (void*)strlen("127.0.0.1"));
	p->putMessage(p->h, (void*)MAKELONG(XM_PORT   , XHTTPD),    (void*)"80",               (void*)strlen("80"));
	p->putMessage(p->h, (void*)MAKELONG(XM_HOME   , XHTTPD),    (void*)"/usr/local/www",   (void*)strlen("/usr/local/www"));
	p->putMessage(p->h, (void*)MAKELONG(XM_INDEX  , XHTTPD),    (void*)"index.html",       (void*)strlen("index.html"));
	p->putMessage(p->h, (void*)MAKELONG(XHTTPD    , XM_ENABLE), 0, 0);
  #endif


  return hdl;
}



void* codeXend(CodeX* p)
{
	p->putMessage(p->h, (void*)MAKELONG(DISABLE     , XSOCKET),  0,0);
	p->putMessage(p->h, (void*)MAKELONG(DISABLE     , XWEBSOCKET), 0, 0);

	return p->setMessage(&p->h, (void*)MAKELONG(RELEASE, CODEX), 0, 0 );
	//return p->codeXFinelia(&p->h);
}
