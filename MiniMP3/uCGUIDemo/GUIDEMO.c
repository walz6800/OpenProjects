/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              礐/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUIDEMO.c
Purpose     : Several GUIDEMO routines
----------------------------------------------------------------------
*/

#include <stddef.h>
//#include "GUI.h"
#include "..\GUIinc\GUI.h"
#if GUI_WINSUPPORT
#include "..\GUIinc\PROGBAR.h"
#include "..\GUIinc\LISTBOX.h"
#include "..\GUIinc\FRAMEWIN.h"
#include "..\GUIinc\BUTTON.h"

#endif
#include "GUIDEMO.h"

unsigned short *pDataBuff;

#define ECG_BUFF_SIZE	320

unsigned short temp[220];
unsigned short ECG_Buff[ECG_BUFF_SIZE];

//#if GUI_SUPPORT_MEMDEV



/*Structure containing information for drawing routine*/
typedef struct {
  I16 * aY;
} PARAM;


/*Defines*/

#if GUIDEMO_LARGE
  #define YSIZE   (LCD_YSIZE - 100)
#else
  #define YSIZE   (LCD_YSIZE - 30)
#endif
/*
#if LCD_YSIZE > 120
  #define YSIZE   (LCD_YSIZE - 100)
#else
  #define YSIZE   20
#endif
*/

#define DEG2RAD (3.1415926f / 180)

#if LCD_BITSPERPIXEL == 1
  #define COLOR_GRAPH0 GUI_WHITE
  #define COLOR_GRAPH1 GUI_WHITE
#else
  #define COLOR_GRAPH0 GUI_GREEN
  #define COLOR_GRAPH1 GUI_YELLOW
#endif
/*********************************************************************
*
*       Static variables
*
**********************************************************************
*/

#if GUI_WINSUPPORT
  static BUTTON_Handle   _ahButton[2];
  static FRAMEWIN_Handle _ahFrameWin[2];
  static int             _ButtonSizeX,      _ButtonSizeY;
  #if GUIDEMO_LARGE
    static FRAMEWIN_Handle _ahInfoWin[2];
    static const char* _sInfo;
  #endif
#endif

static int         _iTest, _iTestMinor;
static char        _CmdNext;
static const char* _sExplain;

#define countof(Obj) (sizeof(Obj)/sizeof(Obj[0]))

/*********************************************************************
*
*       Routine table
*
**********************************************************************

  The routines to be called are listed here. The advantage to calling
  directly is that we can execute some code before and after.
*/

typedef void fVoidVoid(void);

static fVoidVoid * _apfTest[] = {
  
  
//  GUIDEMO_HardwareInfo,
//  GUIDEMO_Speed,
  #if GUI_SUPPORT_MEMDEV
    GUIDEMO_Graph,

  #endif
//  GUIDEMO_Bitmap,
//  GUIDEMO_Cursor,
//  GUIDEMO_ShowInternationalFonts,
//  GUIDEMO_ShowColorBar,
//  GUIDEMO_ShowColorList,
//   GUIDEMO_DemoLUT,
//  GUIDEMO_DemoPolygon,
//  GUIDEMO_Circle,
//  GUIDEMO_ShowMemoryDevice,
//  GUIDEMO_Automotive,
//  GUIDEMO_Navigation,

  #if GUI_WINSUPPORT
//    GUIDEMO_DemoProgBar,
//    GUIDEMO_DemoFrameWin,
//    GUIDEMO_Dialog,
//    GUIDEMO_WM,
    #if GUI_SUPPORT_TOUCH
//      GUIDEMO_Touch,
    #endif
  #endif
  0
};




/*********************************************************************
*
*       Static routines
*
**********************************************************************
*/

static void _UpdateCmdWin(void) {
  #if GUI_WINSUPPORT && GUIDEMO_LARGE
    WM_InvalidateWindow(_ahInfoWin[1]);
  #endif
}

#if (GUI_WINSUPPORT && GUIDEMO_LARGE)
static void _cbCmdWin(WM_MESSAGE* pMsg) {
  switch (pMsg->MsgId) {
  case WM_PAINT:
    /* Update info in command window */
    GUI_SetBkColor(GUI_GRAY);
    GUI_Clear();
    GUI_DispStringAt("Demo ", 0, 0);
    GUI_DispDecMin(_iTest + 1);
    GUI_DispString(".");
    GUI_DispDecMin(_iTestMinor);
    GUI_DispString("/");
    GUI_DispDecMin(countof(_apfTest));
  default:
    WM_DefaultProc(pMsg);
  }
}
#endif

static void _UpdateInfoWin(void) {
	static const char* P="P";
	static const char* QRS="QRS";
	static const char* T="T";
	static const char* U="U";
  #if GUI_WINSUPPORT && GUIDEMO_LARGE
    GUI_RECT rClient;
    WM_HWIN hWin;
    GUI_CONTEXT ContextOld;
    GUI_SaveContext(&ContextOld);
    /* Update info  window */
    WM_ShowWindow(_ahInfoWin[0]);
    WM_ShowWindow(_ahFrameWin[0]);
    hWin = WM_SelectWindow(_ahInfoWin[0]);
    GUI_GetClientRect(&rClient);
    GUI_SetBkColor(GUI_WHITE);
    GUI_Clear();						  //把一个长方形填充为白色
    GUI_SetColor(GUI_BLACK);
    GUI_SetFont(&GUI_Font13_1);
    GUI_SetTextAlign(GUI_TA_HCENTER);
//    GUI_DispStringHCenterAt(_sInfo, (rClient.x1 - rClient.x0) / 2, 0);	  //在右上角的对话框里面显示“Drawing ECG graph”
    GUI_SetTextAlign(GUI_TA_LEFT);
//    GUI_SetFont(&GUI_Font8_ASCII);
//    GUI_DispStringAt(_sExplain, 0, 20);	 //在右上角的对话框里面显示“Optimized drawing routine for.....”
//-------------新添加的语句----------------------------------//
    GUI_SetFont(&GUI_Font8_ASCII);
	GUI_DispStringAt(P, 23, 23);
	GUI_DispStringAt(QRS, 30, 2);
	GUI_DispStringAt(T, 56, 14);
	GUI_DispStringAt(U, 78, 23);
//-------------------------------------------------------------//
	WM_SelectWindow(hWin);
    GUI_RestoreContext(&ContextOld);
  #endif
}

/*********************************************************************
*
*       Exported routines
*
**********************************************************************
*/

GUI_COLOR GUIDEMO_SetBkColor(GUI_COLOR Color) {
  GUI_COLOR r;
  if (GUI_ColorIsAvailable(GUI_RED)) {
    r = Color;
  } else {
    r = GUI_BLACK;
  }
  GUI_SetBkColor(r);
  return r;
}

GUI_COLOR GUIDEMO_SetColor(GUI_COLOR Color) {
  GUI_COLOR r;
  if (GUI_ColorIsAvailable(GUI_RED)) {
    r = Color;
  } else {
    r = GUI_WHITE;
  }
  GUI_SetColor(r);
  return r;
}

int GUIDEMO_Delay(int t) {

  int r = 0;
  #if GUI_WINSUPPORT
    int tm, value;
    #if GUIDEMO_LARGE
      PROGBAR_Handle hProg;
    #endif
    WM_SetForegroundWindow(_ahButton[0]);
    #if GUIDEMO_LARGE
      hProg = (t >100) ? PROGBAR_CreateAsChild(10, 10, 60, 7, _ahInfoWin[1], 0,
                                        WM_CF_SHOW | WM_CF_STAYONTOP| WM_CF_MEMDEV) : 0;
      PROGBAR_SetMinMax(hProg, 0, t);
    #endif
    tm = GUI_GetTime();
    do {
      value = GUI_GetTime() - tm;
      #if GUIDEMO_LARGE
        PROGBAR_SetValue(hProg, value);
        WM_ExecIdle();
      #endif
      GUI_Delay(10);
    } while ((value < t) && !GUIDEMO_CheckCancel());
    #if GUIDEMO_LARGE
      PROGBAR_Delete(hProg);
    #endif
    _UpdateCmdWin();
    WM_ExecIdle();
  #else
    GUI_Delay(t);
  #endif
  return r;

}

void GUIDEMO_Wait(void) {
  GUIDEMO_Delay(4000);
  GUIDEMO_NotifyStartNext();
}

int GUIDEMO_CheckCancel(void) {
  int c = GUI_GetKey();
  #if GUI_WINSUPPORT
    WM_ExecIdle();
  #endif
  if ((c == 'n') || (c=='N'))
    _CmdNext =1;
  if ((c == 's') || (c=='S')) {
    GUI_Delay(500);
    do {
      GUI_Delay(10);
      #if GUI_WINSUPPORT
        WM_ExecIdle();
      #endif
      c = GUI_GetKey();
    } while (!c);
  }
  return _CmdNext;
}

void GUIDEMO_ShowInfo(const char* s) {
  _sExplain = s;
  _UpdateInfoWin();
}

void GUIDEMO_HideInfoWin(void) {
  #if GUI_WINSUPPORT
    WM_HideWindow(_ahFrameWin[0]);
  #endif
}


void GUIDEMO_NotifyStartNext(void) {
  _CmdNext = 0;
  _UpdateCmdWin();
  _iTestMinor++;
}

int GUIDEMO_WaitKey(void) {
  int r = 0;
  int tMax = GUI_GetTime() + 4000;
  int tDiff; 
  #if GUI_WINSUPPORT
    PROGBAR_Handle hProg = PROGBAR_Create(LCD_GetXSize() - 70, 
                                          LCD_GetYSize() - 40, 
                                          80, 5, WM_CF_SHOW);
  #endif
  while (tDiff = tMax-GUI_GetTime(), (tDiff > 0) && !GUIDEMO_CheckCancel()) {
    if ((r = GUI_GetKey()) != 0)
      break;
  }
  #if GUI_WINSUPPORT
    PROGBAR_Delete(hProg);
    WM_ExecIdle();
  #endif
  return r;
}

void GUIDEMO_ShowIntro(const char * s, const char * sExp) {
  GUI_CONTEXT ContextOld;
  GUI_SaveContext(&ContextOld);
#if GUI_WINSUPPORT && GUIDEMO_LARGE
  _sInfo = s;
#endif
  _sExplain = sExp;
  GUI_SetDefault();
  GUIDEMO_HideInfoWin();
  GUI_SetBkColor(GUI_BLUE);
  GUI_SetColor(GUI_WHITE);
  GUI_Clear();
  GUI_SetFont(&GUI_FontComic18B_ASCII);
  GUI_DispStringHCenterAt(s, LCD_GET_XSIZE() / 2, LCD_GET_YSIZE() / 3 - 10);
  if (_sExplain) {
    GUI_SetFont(&GUI_Font8_ASCII);
    GUI_DispStringHCenterAt(_sExplain, LCD_GET_XSIZE() / 2, LCD_GET_YSIZE() / 2 - 10);
  }
  //GUIDEMO_Delay(_sExplain ? 2000 : 4000);
  GUI_Delay(_sExplain ? 2000 : 4000);
#if GUI_WINSUPPORT
  _UpdateInfoWin();
  _UpdateCmdWin();
#endif
  GUI_RestoreContext(&ContextOld);
  #if GUI_WINSUPPORT
    WM_ExecIdle();
  #endif
  GUIDEMO_NotifyStartNext();
  GUI_SetBkColor(GUI_RED);
  GUI_Clear();
}


/**********************************************************************
**函数名：	void FrameWin(void)	 这函数是我自己增加的
**函数功能：液晶右上角的一个对话框（用GUI画的），里面画标准心电波形
**函数参数：无      
**函数返回：无
***********************************************************************/
void FrameWin(void)
{
	int xSize, ySize, xPos, yPos;
	WM_SetCreateFlags(WM_CF_MEMDEV);
/* Calculate position and size of FrameWin[0] */
    xSize = LCD_GetXSize() / 2;
    ySize = 65;
    xPos  = LCD_GetXSize() - xSize;
    yPos  = 0;
    /* Create info window and run the individual demos */
    _ahFrameWin[0] = FRAMEWIN_Create("ECG Standard Wave", NULL, WM_CF_STAYONTOP, 
                                     xPos, yPos, xSize, ySize);
//    _ahInfoWin[0] = WM_GetFirstChild(_ahFrameWin[0]);
    _ahInfoWin[0] = WM_CreateWindowAsChild(0, 0, 0, 0, WM_GetFirstChild(_ahFrameWin[0]), WM_CF_SHOW | WM_CF_STAYONTOP, 0, 0);
    _UpdateCmdWin();		//WM_InvalidateWindow(_ahInfoWin[1]);
	_UpdateInfoWin();						//右上角画一个长方形并填充为白色
	_UpdateCmdWin();	
	WM_ExecIdle();	 						//把对话框显示出来
}
void Delete_Window(void)
{
	WM_DeleteWindow(_ahFrameWin[0]);
	WM_DeleteWindow(_ahFrameWin[1]);
	WM_DeleteWindow(_ahInfoWin[0]);
	WM_DeleteWindow(_ahInfoWin[1]);
}
void My_Return_Bottom(void)
{
  #if GUI_WINSUPPORT
    int i;
    int xSize, ySize, xPos, yPos;
  #endif
  #if (GUI_SUPPORT_CURSOR|GUI_SUPPORT_TOUCH)
    GUI_CURSOR_Show();						   //显示光标
  #endif
//  GUI_Clear();
  #if GUI_WINSUPPORT
    #if LCD_NUM_DISPLAYS > 1
      FRAMEWIN_CreateAsChild(10, 10, 100, 100, WM_GetDesktopWindowEx(1), "Display 1", NULL, WM_CF_SHOW);
      WM_SetDesktopColorEx(GUI_RED, 1);
      GUI_Delay(1000);
    #endif
    //自动使用内存设备在所有windows
	WM_SetCreateFlags(WM_CF_MEMDEV);  /* Automatically use memory devices on all windows */
    /* Calculate position and size of FrameWin[1] */
    _ButtonSizeX = 30;			 //按键大小，宽30
    _ButtonSizeY = 20;			 //按键大小，高20
    /* Create the control window incl. buttons */
    _ahFrameWin[1] = FRAMEWIN_Create("Control", NULL, WM_CF_SHOW | WM_CF_STAYONTOP,
                                                LCD_GetXSize() - 80, LCD_GetYSize() - 60, 80, 60);
    _ahInfoWin[1] = WM_CreateWindowAsChild( 0, 0, 0, 0, WM_GetFirstChild(_ahFrameWin[1]), WM_CF_SHOW | WM_CF_STAYONTOP, &_cbCmdWin, 0);
    _ahButton[0] = BUTTON_CreateAsChild(4, 20, _ButtonSizeX, _ButtonSizeY, _ahInfoWin[1], 
                                        'S' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
    _ahButton[1] = BUTTON_CreateAsChild(40, 20, _ButtonSizeX, _ButtonSizeY, _ahInfoWin[1], 
                                        'N' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
    BUTTON_SetText(_ahButton[0], "Stop");
    BUTTON_SetText(_ahButton[1], "Next");
    _UpdateCmdWin();					 //
    WM_ExecIdle();
  #endif
}
/*********************************************************************
*
*       GUIDEMO_main(): Large version of the demo
*
**********************************************************************
*/

#if GUIDEMO_LARGE

void GUIDEMO_main(void) {
  #if GUI_WINSUPPORT
    int i;
    int xSize, ySize, xPos, yPos;
  #endif
  #if (GUI_SUPPORT_CURSOR|GUI_SUPPORT_TOUCH)
    GUI_CURSOR_Show();						   //显示光标
  #endif
  GUI_Clear();
  #if GUI_WINSUPPORT
    #if LCD_NUM_DISPLAYS > 1
      FRAMEWIN_CreateAsChild(10, 10, 100, 100, WM_GetDesktopWindowEx(1), "Display 1", NULL, WM_CF_SHOW);
      WM_SetDesktopColorEx(GUI_RED, 1);
      GUI_Delay(1000);
    #endif
    //自动使用内存设备在所有windows
	WM_SetCreateFlags(WM_CF_MEMDEV);  /* Automatically use memory devices on all windows */
    /* Calculate position and size of FrameWin[1] */
    _ButtonSizeX = 30;			 //按键大小，宽30
    _ButtonSizeY = 20;			 //按键大小，高20
    /* Create the control window incl. buttons */
    _ahFrameWin[1] = FRAMEWIN_Create("Control", NULL, WM_CF_SHOW | WM_CF_STAYONTOP,
                                                LCD_GetXSize() - 80, LCD_GetYSize() - 60, 80, 60);
    _ahInfoWin[1] = WM_CreateWindowAsChild( 0, 0, 0, 0, WM_GetFirstChild(_ahFrameWin[1]), WM_CF_SHOW | WM_CF_STAYONTOP, &_cbCmdWin, 0);
    _ahButton[0] = BUTTON_CreateAsChild(4, 20, _ButtonSizeX, _ButtonSizeY, _ahInfoWin[1], 
                                        'S' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
    _ahButton[1] = BUTTON_CreateAsChild(40, 20, _ButtonSizeX, _ButtonSizeY, _ahInfoWin[1], 
                                        'N' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
    BUTTON_SetText(_ahButton[0], "Stop");
    BUTTON_SetText(_ahButton[1], "Next");
    _UpdateCmdWin();					 //
    WM_ExecIdle();
  #endif
  /* Show Intro */
  GUIDEMO_Intro();		  //显示uC/GUI信息
  #if GUI_WINSUPPORT
    /* Calculate position and size of FrameWin[0] *///计算FrameWin[0]的位置与大小	
    xSize = LCD_GetXSize() / 2;
    ySize = 65;
    xPos  = LCD_GetXSize() - xSize;
    yPos  = 0;
    /* Create info window and run the individual demos *///创建信息窗口并运行个人演示
    _ahFrameWin[0] = FRAMEWIN_Create("礐/GUI Demo", NULL, WM_CF_STAYONTOP, 
                                     xPos, yPos, xSize, ySize);
//    _ahInfoWin[0] = WM_GetFirstChild(_ahFrameWin[0]);
    _ahInfoWin[0] = WM_CreateWindowAsChild(0, 0, 0, 0, WM_GetFirstChild(_ahFrameWin[0]), WM_CF_SHOW | WM_CF_STAYONTOP, 0, 0);
    WM_ExecIdle();
  #endif
  /* Run the individual demos !  */
  for (_iTest = 0; _apfTest[_iTest]; _iTest++)
  {
    GUI_CONTEXT ContextOld;
    GUI_SaveContext(&ContextOld);
    _iTestMinor = 0;
    _UpdateCmdWin();
    (*_apfTest[_iTest])();
    _CmdNext = 0;
    GUI_RestoreContext(&ContextOld);
  }
  /* Cleanup */
  #if GUI_WINSUPPORT
    for (i = 0; i < countof(_ahFrameWin); i++) {
      WM_DeleteWindow(_ahFrameWin[i]);
    }
    for (i = 0; i < countof(_ahInfoWin); i++) {
      WM_DeleteWindow(_ahInfoWin[i]);
    }
  #endif
}

#else /* GUIDEMO_LARGE */

/*********************************************************************
*
*       GUIDEMO_main(): Small version of the demo
*
**********************************************************************
*/
void GUIDEMO_main(void) {
  #if GUI_WINSUPPORT
    int i;
  #endif
  #if GUI_WINSUPPORT
    #if LCD_NUM_DISPLAYS > 1
      FRAMEWIN_CreateAsChild(10, 10, 100, 100, WM_GetDesktopWindowEx(1), "Display 1", NULL, WM_CF_SHOW);
      GUI_Delay(1000);
    #endif
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Automatically use memory devices on all windows */
    _ButtonSizeX = 27;
    _ButtonSizeY = 14;
    _ahButton[0] = BUTTON_Create(LCD_GetXSize() - _ButtonSizeX * 2 - 5,
                                 LCD_GetYSize() - _ButtonSizeY - 3,
                                 _ButtonSizeX, _ButtonSizeY, 
                                 'H' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
    _ahButton[1] = BUTTON_Create(LCD_GetXSize() - _ButtonSizeX - 3,
                                 LCD_GetYSize() - _ButtonSizeY - 3,
                                 _ButtonSizeX, _ButtonSizeY, 
                                 'N' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
    BUTTON_SetFont(_ahButton[0], &GUI_Font8_ASCII);
    BUTTON_SetFont(_ahButton[1], &GUI_Font8_ASCII);
    BUTTON_SetText(_ahButton[0], "Stop");
    BUTTON_SetText(_ahButton[1], "Next");
    _UpdateCmdWin();
    WM_ExecIdle();
  #endif
  /* Show Intro */
  GUIDEMO_Intro();
  /* Run the individual demos !  */
  for (_iTest = 0; _apfTest[_iTest]; _iTest++) {
    GUI_CONTEXT ContextOld;
    GUI_SaveContext(&ContextOld);
    _iTestMinor = 0;
    _UpdateCmdWin();
    (*_apfTest[_iTest])();
    _CmdNext = 0;
    GUI_RestoreContext(&ContextOld);
  }
  /* Cleanup */
  #if GUI_WINSUPPORT
    for (i = 0; i < countof(_ahButton); i++) {
      BUTTON_Delete(_ahButton[i]);
    }
  #endif
}

#endif /* GUIDEMO_LARGE */
/*********************************************************************
*
*       Draws the graph GUI画波形
*
***********************************************************************/
static void _Draw(void * p) {
  int i;
  PARAM * pParam = (PARAM *)p;
  GUI_SetBkColor(GUI_BLACK);
  GUI_SetColor(GUI_DARKGRAY);
  GUI_ClearRect(19, (LCD_YSIZE - 20) - YSIZE, (LCD_XSIZE - 2), (LCD_YSIZE - 21));
  for (i = 0; i < (YSIZE / 2); i += 20) {
    GUI_DrawHLine((LCD_YSIZE - 20) - (YSIZE / 2) + i, 19, (LCD_XSIZE - 2));
    if (i) {
      GUI_DrawHLine((LCD_YSIZE - 20) - (YSIZE / 2) - i, 19, (LCD_XSIZE - 2));  //画“横”的直线，在第50行画一条长度为（18-13）的横线
    }
  }
  for (i = 40; i < (LCD_XSIZE - 20); i += 40) {
    GUI_DrawVLine(18 + i, (LCD_YSIZE - 20) - YSIZE, (LCD_YSIZE - 21));		   //画“竖”的直线，在第50列画一条长度为（18-13）的竖线
  }
  GUI_SetColor(COLOR_GRAPH0);
  GUI_DrawGraph(pParam->aY, (LCD_XSIZE - 20), 19, ((LCD_YSIZE - 20) - YSIZE));
}

/**********************************************************************************/
  PARAM Param;//定义结构体变量Param
  //LCD_YSIZE=240  LCD_XSIZE=320
  //GUI_RECT为结构体类型，定义结构体变量Rect={ I16 x0,y0,x1,y1; }
  GUI_RECT Rect1 = {19, (LCD_YSIZE - 20) - YSIZE, (LCD_XSIZE - 2), (LCD_YSIZE - 21)};  //(起始列，起始行，结束列，结束行)
  //GUI_RECT Rect = {19, (LCD_YSIZE - 20) - YSIZE, (LCD_XSIZE - 2), 120};
/**********************************************************************************/

void ECG_Draw(void)
{
    unsigned int i;

	for(i=0;i<320;i++)    temp[i]=ECG_Buff[i]/34;//除以34，画出来的波形幅度刚好是-3~+3
    Param.aY = temp;//aY为结构体 Param 的成员
    //Param.aY = DisplayBuff;
    GUI_MEMDEV_Draw(&Rect1, _Draw, &Param, 0, 0);
//    GUI_DrawGraph(temp, (LCD_XSIZE - 20), 19, (LCD_YSIZE - 20) - YSIZE);
//    GUI_ClearRect(19, (LCD_YSIZE - 20) - YSIZE, (LCD_XSIZE - 2), (LCD_YSIZE - 21));
}


void MY_GUIDEMO_main(void) {
  #if GUI_WINSUPPORT
    int i;
    int xSize, ySize, xPos, yPos;
  #endif
  #if (GUI_SUPPORT_CURSOR|GUI_SUPPORT_TOUCH)
    GUI_CURSOR_Show();						   //显示光标
  #endif
  GUI_Clear();
  #if GUI_WINSUPPORT
    #if LCD_NUM_DISPLAYS > 1
      FRAMEWIN_CreateAsChild(10, 10, 100, 100, WM_GetDesktopWindowEx(1), "Display 1", NULL, WM_CF_SHOW);
      WM_SetDesktopColorEx(GUI_RED, 1);
      GUI_Delay(1000);
    #endif
    //自动使用内存设备在所有windows
	WM_SetCreateFlags(WM_CF_MEMDEV);  /* Automatically use memory devices on all windows */
    /* Calculate position and size of FrameWin[1] */
    _ButtonSizeX = 30;			 //按键大小，宽30
    _ButtonSizeY = 20;			 //按键大小，高20
    /* Create the control window incl. buttons */
    _ahFrameWin[1] = FRAMEWIN_Create("Control", NULL, WM_CF_SHOW | WM_CF_STAYONTOP,
                                                LCD_GetXSize() - 80, LCD_GetYSize() - 60, 80, 60);
    _ahInfoWin[1] = WM_CreateWindowAsChild( 0, 0, 0, 0, WM_GetFirstChild(_ahFrameWin[1]), WM_CF_SHOW | WM_CF_STAYONTOP, &_cbCmdWin, 0);
    _ahButton[0] = BUTTON_CreateAsChild(4, 20, _ButtonSizeX, _ButtonSizeY, _ahInfoWin[1], 
                                        'S' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
    _ahButton[1] = BUTTON_CreateAsChild(40, 20, _ButtonSizeX, _ButtonSizeY, _ahInfoWin[1], 
                                        'N' , WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV);
    BUTTON_SetText(_ahButton[0], "Stop");
    BUTTON_SetText(_ahButton[1], "Next");
    _UpdateCmdWin();					 //
    WM_ExecIdle();
  #endif
  /* Show Intro */
//  GUIDEMO_Intro();		  //显示uC/GUI信息
  #if GUI_WINSUPPORT
    /* Calculate position and size of FrameWin[0] *///计算FrameWin[0]的位置与大小	
    xSize = LCD_GetXSize() / 2;
    ySize = 65;
    xPos  = LCD_GetXSize() - xSize;
    yPos  = 0;
    /* Create info window and run the individual demos *///创建信息窗口并运行个人演示
    _ahFrameWin[0] = FRAMEWIN_Create("礐/GUI Demo", NULL, WM_CF_STAYONTOP, 
                                     xPos, yPos, xSize, ySize);
//    _ahInfoWin[0] = WM_GetFirstChild(_ahFrameWin[0]);
    _ahInfoWin[0] = WM_CreateWindowAsChild(0, 0, 0, 0, WM_GetFirstChild(_ahFrameWin[0]), WM_CF_SHOW | WM_CF_STAYONTOP, 0, 0);
    WM_ExecIdle();
  #endif
  /* Run the individual demos !  */
  for (_iTest = 0; _apfTest[_iTest]; _iTest++)
  {
    GUI_CONTEXT ContextOld;
    GUI_SaveContext(&ContextOld);
    _iTestMinor = 0;
    _UpdateCmdWin();
    (*_apfTest[_iTest])();
    _CmdNext = 0;
    GUI_RestoreContext(&ContextOld);
  }
  /* Cleanup */
  #if GUI_WINSUPPORT
    for (i = 0; i < countof(_ahFrameWin); i++) {
      WM_DeleteWindow(_ahFrameWin[i]);
    }
    for (i = 0; i < countof(_ahInfoWin); i++) {
      WM_DeleteWindow(_ahInfoWin[i]);
    }
  #endif
}
