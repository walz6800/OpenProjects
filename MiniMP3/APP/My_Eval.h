#ifndef __MY_EVAL_H
#define __MY_EVAL_H

//#include "stm32f10x_lib.h"
#include "GUI.h"
//#include "GUIDEMO.h"




//#define LEDn                        2
//#define LED1_GPIO_PORT              GPIOA
//#define LED1_GPIO_CLK               RCC_APB2Periph_GPIOA  
//#define LED1_GPIO_PIN               GPIO_Pin_8
//  
//#define LED2_GPIO_PORT              GPIOA
//#define LED2_GPIO_CLK               RCC_APB2Periph_GPIOA  
//#define LED2_GPIO_PIN               GPIO_Pin_9
//
//#define ECG_BUFF_SIZE             320
//#define DATA_BUFF_SIZE            (ECG_BUFF_SIZE/2)
//#define AVERAGE_BIN               2
//#define DISPLAY_BUFF_SIZE         120
//#define DISPLAY_BUFF_INCREMENT    (DATA_BUFF_SIZE/AVERAGE_BIN)
//
//
//
//typedef enum 
//	{
//	LED1 = 0,
//	LED2 = 1
//	} Led_TypeDef;
//
//#endif
//
//void STM_EVAL_LEDOn(Led_TypeDef Led);
//void STM_EVAL_LEDOff(Led_TypeDef Led);
//void STM_EVAL_LEDToggle(Led_TypeDef Led);
//void STM_EVAL_LEDInit(Led_TypeDef Led);


u16 Get_Adc(u8 ch);
void RCC_Configuration1(void);
void NVIC_Configuration1(void);
void GPIO_Configuration1(void);
void TIM3_Configuration(u16 timerval);
void MY_ADC_Init(void);

void ECG_Samp_Inf(void);
void ECG_Wave(void);

//void USB_SendString(u8 *str);
void SD_TEST(void);

void Load_Sys_ICO(void);     //加载系统图标
void Select_Menu(void);		   //选择桌面图标
void Show_ICO(void);
void Draw_ECG_Wave(void);
void Draw_Any_Graph(void);


#endif

