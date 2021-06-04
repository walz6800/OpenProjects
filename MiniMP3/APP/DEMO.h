#include "includes.h"

#include  <stdio.h>
#include  <string.h>
#include  <ctype.h>
#include  <stdlib.h>
#include  <stdarg.h>
#include "misc.h"
#include "stm32f10x_gpio.h"	   
#include "stm32f10x_usart.h"
#include "stm32f10x_sdio.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"


#ifdef GLOBALS 
#define EXT
#else
#define EXT extern 
#endif

#define LED_LED1_ON()   GPIO_SetBits(GPIOB, GPIO_Pin_5 );  	       //LED1  ÁÁ
#define LED_LED1_OFF()  GPIO_ResetBits(GPIOB, GPIO_Pin_5 ); 	   //LED1  Ãð
EXT uint8_t TxBuffer1[400]; 
EXT uint8_t TxBuffer2[]; 
EXT uint8_t RxBuffer1[400];
EXT uint8_t RxBuffer2[];
EXT uint8_t TxCounter1;
EXT u16 TxCounter2,star_info[12][4],star_info_t[12][4],GPS_ATLI;
EXT volatile u16 RxCounter1; 
EXT volatile u16 RxCounter2;

EXT volatile uint8_t rec_f,tx_flag,flash_led;
EXT volatile uint32_t Rec_Len;
EXT uint8_t Hour,Min,Sec,Day,Mouth,Year,GPS_VA,weidu_dir,jingdu_dir,star_num,star_num_t,star_run[12],GPS_3D;
EXT float jingdu,weidu;
EXT OS_EVENT* NMEA_MBOX;

