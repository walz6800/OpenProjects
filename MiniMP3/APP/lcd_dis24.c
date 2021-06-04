

#include "fsmc_sram.h"

#define Bank1_LCD_D    ((uint32_t)0x60020000)    //disp Data ADDR
#define Bank1_LCD_C    ((uint32_t)0x60000000)	 //disp Reg ADDR



void LCD_Init1(void);
void LCD_WR_REG(unsigned int index);
void LCD_WR_CMD(unsigned int index,unsigned int val);

void LCD_WR_Data(unsigned int val);

void LCD_test(void);
void LCD_clear(unsigned int p);

void Delay(__IO uint32_t nCount);

unsigned short LCD_RD_data(void);
extern void lcd_rst(void);
extern void Delay(__IO uint32_t nCount);


/****************************************************************************
* 名    称：LCD_WR_REG(unsigned int index)
* 功    能：FSMC写显示器寄存器地址函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void LCD_WR_REG(unsigned int index)
{
	*(__IO uint16_t *) (Bank1_LCD_C)= index;

}			 

/****************************************************************************
* 名    称：void LCD_WR_CMD(unsigned int index,unsigned int val)
* 功    能：FSMC写显示器寄存器数据函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void LCD_WR_CMD(unsigned int index,unsigned int val)
{	
	*(__IO uint16_t *) (Bank1_LCD_C)= index;	
	*(__IO uint16_t *) (Bank1_LCD_D)= val;
}


/****************************************************************************
* 名    称：unsigned short LCD_RD_data(void)
* 功    能：FSMC读显示区16位数据函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
unsigned short LCD_RD_data(void){
	unsigned int a=0;
	a=*(__IO uint16_t *) (Bank1_LCD_D);   //空操作
	a=*(__IO uint16_t *) (Bank1_LCD_D);   //读出的实际16位像素数据	  
	return(a);	
}



/****************************************************************************
* 名    称：LCD_WR_Data(unsigned int val)
* 功    能：FSMC写16位数据函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void LCD_WR_Data(unsigned int val)
{   
	*(__IO uint16_t *) (Bank1_LCD_D)= val; 	
}


/****************************************************************************
* 名    称：void Delay(__IO uint32_t nCount)
* 功    能：延时函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

/****************************************************************************
* 名    称：void LCD_Init(void)
* 功    能：2.4 寸TFT 初始化函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void LCD_Init1(void)
{	unsigned int i;   
    GPIO_ResetBits(GPIOE, GPIO_Pin_1);
    Delay(0xAFFf);					   
    GPIO_SetBits(GPIOE, GPIO_Pin_1 );		 //V7	 
	Delay(0xAFFf);	


	LCD_WR_CMD(229,0x8000); /* Set the internal vcore voltage */
  LCD_WR_CMD(0,  0x0001); /* Start internal OSC. */
  LCD_WR_CMD(1,  0x0100); /* set SS and SM bit */
  LCD_WR_CMD(2,  0x0700); /* set 1 line inversion */
  LCD_WR_CMD(3,  0x1030); /* set GRAM write direction and BGR=1. */
  LCD_WR_CMD(4,  0x0000); /* Resize register */
  LCD_WR_CMD(8,  0x0202); /* set the back porch and front porch */
  LCD_WR_CMD(9,  0x0000); /* set non-display area refresh cycle ISC[3:0] */
  LCD_WR_CMD(10, 0x0000); /* FMARK function */
  LCD_WR_CMD(12, 0x0000); /* RGB interface setting */
  LCD_WR_CMD(13, 0x0000); /* Frame marker Position */
  LCD_WR_CMD(15, 0x0000); /* RGB interface polarity */

/* Power On sequence ---------------------------------------------------------*/
  LCD_WR_CMD(16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
  LCD_WR_CMD(17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
  LCD_WR_CMD(18, 0x0000); /* VREG1OUT voltage */
  LCD_WR_CMD(19, 0x0000); /* VDV[4:0] for VCOM amplitude */
  Delay(20);                 /* Dis-charge capacitor power voltage (200ms) */
  LCD_WR_CMD(16, 0x17B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
  LCD_WR_CMD(17, 0x0137); /* DC1[2:0], DC0[2:0], VC[2:0] */
  Delay(5);                  /* Delay 50 ms */
  LCD_WR_CMD(18, 0x0139); /* VREG1OUT voltage */
  Delay(5);                  /* Delay 50 ms */
  LCD_WR_CMD(19, 0x1d00); /* VDV[4:0] for VCOM amplitude */
  LCD_WR_CMD(41, 0x0013); /* VCM[4:0] for VCOMH */
  Delay(5);                  /* Delay 50 ms */
  LCD_WR_CMD(32, 0x0000); /* GRAM horizontal Address */
  LCD_WR_CMD(33, 0x0000); /* GRAM Vertical Address */

/* Adjust the Gamma Curve ----------------------------------------------------*/
  LCD_WR_CMD(48, 0x0006);
  LCD_WR_CMD(49, 0x0101);
  LCD_WR_CMD(50, 0x0003);
  LCD_WR_CMD(53, 0x0106);
  LCD_WR_CMD(54, 0x0b02);
  LCD_WR_CMD(55, 0x0302);
  LCD_WR_CMD(56, 0x0707);
  LCD_WR_CMD(57, 0x0007);
  LCD_WR_CMD(60, 0x0600);
  LCD_WR_CMD(61, 0x020b);
  
/* Set GRAM area -------------------------------------------------------------*/
  LCD_WR_CMD(80, 0x0000); /* Horizontal GRAM Start Address */
  LCD_WR_CMD(81, 0x00EF); /* Horizontal GRAM End Address */
  LCD_WR_CMD(82, 0x0000); /* Vertical GRAM Start Address */
  LCD_WR_CMD(83, 0x013F); /* Vertical GRAM End Address */

  LCD_WR_CMD(96,  0x2700); /* Gate Scan Line */
  LCD_WR_CMD(97,  0x0001); /* NDL,VLE, REV */
  LCD_WR_CMD(106, 0x0000); /* set scrolling line */

/* Partial Display Control ---------------------------------------------------*/
  LCD_WR_CMD(128, 0x0000);
  LCD_WR_CMD(129, 0x0000);
  LCD_WR_CMD(130, 0x0000);
  LCD_WR_CMD(131, 0x0000);
  LCD_WR_CMD(132, 0x0000);
  LCD_WR_CMD(133, 0x0000);

/* Panel Control -------------------------------------------------------------*/
  LCD_WR_CMD(144, 0x0010);
  LCD_WR_CMD(146, 0x0000);
  LCD_WR_CMD(147, 0x0003);
  LCD_WR_CMD(149, 0x0110);
  LCD_WR_CMD(151, 0x0000);
  LCD_WR_CMD(152, 0x0000);

  LCD_WR_CMD(3, 0x1018);

  LCD_WR_CMD(7, 0x0173); /* 262K color and display ON */ 

	*(__IO uint16_t *) (Bank1_LCD_C)= 34;
	for(i=0;i<76800;i++)
	{
	  LCD_WR_Data(0xffff);
	}
}

/******************* (C) COPYRIGHT 2011 奋斗STM32 *****END OF FILE****/

