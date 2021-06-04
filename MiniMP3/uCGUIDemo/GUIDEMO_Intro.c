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
File        : GUIDEMO_Intro.c
Purpose     : Introduction for 礐/GUI generic demo
              (This is also a good file to demo and explain basic
              uC/GUI features by setting breakpoints)
----------------------------------------------------------------------
*/

//#include "GUI.h"
//#include "GUIDEMO.h"
#include "..\GUIinc\GUI.h"
#include "..\uCGUIDemo\GUIDEMO.h"
#include <string.h>

/*********************************************************************
*
*       GUIDEMO_Intro
*
**********************************************************************
*/

#if GUIDEMO_LARGE

void GUIDEMO_Intro(void)
{
 int xCenter = LCD_GET_XSIZE() / 2;
  int y;
  char acText[50] = "Version of 礐/GUI: ";
  strcat(acText, GUI_GetVersionString());
  GUI_SetBkColor(GUI_BLUE);
  GUI_SetColor(GUI_YELLOW);	   //设置字体蓝色
  GUI_Clear();
//  GUI_SetFont(&GUI_Font24B_1);
  GUI_SetFont(&GUI_FontComic18B_1);	   
  GUI_DispStringHCenterAt("礐/GUI", xCenter, y= 15);	  //在(xCenter,y=15)这个位置显示"uc/GUI"
  GUI_SetColor(GUI_LIGHTRED);	//设置字体蓝色
//  GUI_SetColor(GUI_WHITE);		    
  GUI_DispStringHCenterAt("Universal graphic software"	   //通用图形软件
                          "\nfor embedded applications"	   //嵌入式 应用程序
                          , xCenter, y += 30);
  //GUI_SetColor(GUI_LIGHTRED);			  
  GUI_DispStringHCenterAt("Any CPU - Any LCD - Any Application"
                          , xCenter, y += 40);
  GUI_DispStringHCenterAt("Compiled " __DATE__ " "__TIME__, xCenter, y += 25); 	  //这里显示年月日 时间
  GUI_SetColor(GUI_YELLOW);
  GUI_DispStringHCenterAt("Xzezhen My_STM32", LCD_GET_XSIZE() / 2, LCD_GET_YSIZE() - 90);
//  GUI_DrawBitmap(&bmMicriumLogo, (LCD_GET_XSIZE() - bmMicriumLogo.XSize) / 2, 150);
//  GUI_SetColor(GUI_WHITE);
  GUI_SetColor(GUI_RED);			  
  GUI_SetFont(&GUI_Font10S_ASCII);
  GUI_DispStringAt("GUI_OS: ", 0,210); GUI_DispDecMin(GUI_OS);
  GUI_DispStringAt("GUI_ALLOC_SIZE: ",0, 220); GUI_DispDecMin(GUI_ALLOC_SIZE);
  GUI_DispStringAt("Compiler:"
  #ifdef _MSC_VER
    "Microsoft"
  #elif defined (NC308)
    "Mitsubishi NC308"
  #elif defined (NC30)
    "Mitsubishi NC30"
  #elif defined (__TID__)
    #if (((__TID__ >>8) &0x7f) == 48)            /* IAR MC80 */
      "IAR M32C"
    #elif (((__TID__ >>8) &0x7f) == 85)          /* IAR V850 */
      "IAR V850"
    #else                                        /* IAR MC16 */
      "IAR M32C"
    #endif
  #else
    "RealViewMDK 3.40"
  #endif
    ,0, 230);
	GUI_Delay(5000);
//  GUIDEMO_Delay(10000);	   //延迟10秒,包括了一个进度条，跟按键无关？
}

#else

void GUIDEMO_Intro(void) {
  int xCenter = LCD_GET_XSIZE() / 2;
  int y;
  char acText[50] = "Version of 礐/GUI: ";
  strcat(acText, GUI_GetVersionString());
  GUI_SetBkColor(GUI_BLUE);
  GUI_SetColor(GUI_YELLOW);
  GUI_Clear();
  GUI_SetFont(&GUI_Font13B_1);
  GUI_DispStringHCenterAt("礐/GUI", xCenter, y= 10);
  GUI_SetFont(&GUI_Font10_ASCII);
  GUI_SetColor(GUI_WHITE);
  GUI_DispStringHCenterAt("Universal graphic software"
                          "\nfor embedded applications"
                          , xCenter, y += 20);
  GUI_SetFont(&GUI_Font10S_ASCII);
  GUI_DispStringHCenterAt("Compiled " __DATE__ " "__TIME__, xCenter, y += 25);
  GUI_DispStringHCenterAt(acText, xCenter, y += 16);
  GUIDEMO_Delay(5000);

  GUI_Clear();
  GUI_DrawBitmap(&bmMicriumLogo, (LCD_GET_XSIZE() - bmMicriumLogo.XSize) / 2, 6);
  GUI_SetFont(&GUI_Font13B_1);
  GUI_DispStringHCenterAt("www.PowerAVR.com", LCD_GET_XSIZE() / 2, LCD_GET_YSIZE() - 50);
  GUIDEMO_Delay(5000);


}

#endif
