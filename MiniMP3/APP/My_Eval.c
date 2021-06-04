#include  <stm32f10x_conf.h>
//#include  <stm32f10x_lib.h>
#include  <stm32f10x.h>
//#include "stm32f10x.h"
//#include "stm32f10x_lib.h"
#include "..\GUIinc\GUI.h"

#include "my_eval.h"
#include "ili9320.h"
//#include "usb_lib.h"
//#include "hw_config.h"
//#include "stm32f10x_it.h"
//#include "stm32f10x_nvic.h"
//#include "GUIDEMO.h"
#include "stm32f10x.h"
#include "sdio_sdcard.h"
#include "integer.h"
#include "ff.h"
#include "ffconf.h"
#include "diskio.h"

#include "usb_regs.h"

#include "bmp.h"
//#include "bmp1.h"
#include "bmp2.h"
#include "bmp3.h"
//#include "bmp4.h"
#include "dazhen.h"
#include "ili9320.h"

extern unsigned short *pDataBuff;

#define ECG_BUFF_SIZE	320

#define M	900							//SD卡存储900个点

u8 SD_BUFF[M];							//SD卡存储数组

extern unsigned short temp[220];
extern unsigned short ECG_Buff[ECG_BUFF_SIZE];

//unsigned char buffer[512];     // 文件内容缓冲区
    
FATFS		fs;					 // 逻辑驱动器的标志
FRESULT		res;				 // FatFs 功能函数返回结果变量
UINT 		br;					 // 文件读/写计数器
FIL 		file;				 // 文件标志

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; 
SD_Error Status = SD_OK;
SD_CardInfo SDCardInfo;

int TouchX,TouchY;
u8 i=0,j=0,k=0,l=0;
u8 index=0;
	
void SD_TEST(void)
{
	Status = SD_Init();
    Status = SD_GetCardInfo(&SDCardInfo);
    Status = SD_SelectDeselect((uint32_t) (SDCardInfo.RCA << 16));
    Status = SD_EnableWideBusOperation(SDIO_BusWide_4b);
    Status = SD_SetDeviceMode(SD_DMA_MODE);  
// 	if (Status == SD_OK)
//  	{
//        // 从地址0开始读取512字节  
//    	Status = SD_ReadBlock(Buffer_Block_Rx, 0x00,  512); 
//  	}
  	if(Status == SD_OK)
    {	 
       // 返回成功的话，串口输出SD卡测试成功信息 
	   // USART_OUT(USART1,"\r\nSD 奋斗STM32开发板 SDIO-4bit模式 测试TF卡成功！ \n ");
//	   POINT_COLOR=BLUE;
//	   TFT_ShowString(10,10,"SDIO-4bit Mode TF Card test OK!");
	   ili9320_PutChar(20,50,'o',0xffff,0x0000);
    } 
}
void USB_SendString(u8 *str)
{
	UserToPMABufferCopy(str, GetEPTxAddr(ENDP1), 64);
	SetEPTxCount(ENDP1, 64);
	/* enable endpoint for transmission */
	SetEPTxValid(ENDP1);
}

void GPIO_Configuration1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;     
//	STM_EVAL_LEDInit(LED1);

	//PA0/1/2/3 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USB_DISCONNECT used as USB pull-up */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
//	GPIO_Init(USB_DISCONNECT, &GPIO_InitStructure);

//	STM_EVAL_LEDInit(LED1);
//	STM_EVAL_LEDInit(LED2);
}
//系统中断管理
void NVIC_Configuration1(void)
{  
	NVIC_InitTypeDef NVIC_InitStructure;

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	//设置优先级分组：先占优先级0位,从优先级4位
	
	//设置向量表的位置和偏移
	#ifdef  VECT_TAB_RAM  
		NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 		//向量表位于RAM
	#else  /* VECT_TAB_FLASH  */
		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   //向量表位于FLASH
	#endif

	/* Enable the TIM3 global Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = 0x1d;  //TIM3_IRQn=29  TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

//	/* 优先级组1 */
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	  
//	
//	NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;			     //SDIO中断
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		 //抢先优先级0  范围：0或1
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			 //子优先级0	范围：0-7
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
}
void MY_ADC_Init(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	
	ADC_DeInit(ADC1);  		//将外设 ADC1 的全部寄存器重设为缺省值
	
	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;					//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;						//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;					//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;				//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;		//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);			//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器

	ADC_Cmd(ADC1, ENABLE);						//使能指定的ADC1		
	ADC_ResetCalibration(ADC1);					//重置指定的ADC1的校准寄存器
	while(ADC_GetResetCalibrationStatus(ADC1));	//获取ADC1重置校准寄存器的状态,设置状态则等待
	
	ADC_StartCalibration(ADC1);					//开始指定ADC1的校准状态
	while(ADC_GetCalibrationStatus(ADC1));		//获取指定ADC1的校准程序,设置状态则等待
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
	

}
void TIM3_Configuration(u16 timerval)
{
	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	
	/* ---------------------------------------------------------------
	TIM3CLK 即PCLK1=36MHz
	TIM3CLK = 36 MHz, Prescaler = 7200, TIM3 counter clock = 5K,即改变一次为5K,周期就为10K
	--------------------------------------------------------------- */
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = timerval; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	比如填入5000就是计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =(7200-1); //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	/* Enables the Update event for TIM3 */
	//TIM_UpdateDisableConfig(TIM3,ENABLE); 	//使能 TIM3 更新事件 
	
	/* TIM IT enable */
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM3, //TIM2
		TIM_IT_Update  |  //TIM 中断源
		TIM_IT_Trigger,   //TIM 触发中断源 
		ENABLE  //使能
		);
	
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
}
//配置系统时钟,使能各外设时钟
void RCC_Configuration1(void)
{
	SystemInit();
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP |
                           RCC_APB1Periph_TIM2, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIO_DISCONNECT |
//		       RCC_APB2Periph_SPI1 | RCC_APB2Periph_GPIOB, ENABLE); 

			 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //72M/6=12,ADC最大时间不能超过14M
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC 
  						| RCC_APB2Periph_GPIOD| RCC_APB2Periph_GPIOE , ENABLE);

}
//获得ADC值//ch:通道值 0~3
u16 Get_Adc(u8 ch)   
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道3,规则采样顺序值为1,采样时间为239.5周期	  			    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);			//使能指定的ADC1的软件转换启动功能
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));	//等待转换结束
	return ADC_GetConversionValue(ADC1);			//返回最近一次ADC1规则组的转换结果
}
/**********************************************************************
**函数功能：画一个标准ECG参考波形（用底层的LCD画线函数画的，俗了点，
**			因为用GUI函数画不到对话框里，也懒得去找原因了）
**函数参数：无      
**函数返回：无
***********************************************************************/
void ECG_Wave(void)
{
//--------------------------------------------------------------//
//	POINT_COLOR = 0x001F;
	GUI_Line(164, 45, 190, 45,0x001F);  //（起始列，起始行，结束列，结束行）直线
	GUI_Line(190, 45, 195, 50,0x001F);	 //P波
	GUI_Line(197, 52, 202, 24,0x001F);	 //QRS波1（左边）
	GUI_Line(202, 24, 206, 58,0x001F);	 //QRS波2（右边）
	GUI_Line(206, 58, 212, 45,0x001F);	 //ST段1
	GUI_Line(212, 45, 215, 40,0x001F);	 //ST段2
	
	GUI_Line(215, 40, 218, 38,0x001F);	 //T波1
	GUI_Line(218, 38, 221, 37,0x001F);	 //T波2
	GUI_Line(221, 37, 224, 37,0x001F);	 //T波3
	
	GUI_Line(224, 37, 228, 39,0x001F);	 //U波1
	GUI_Line(228, 39, 232, 41,0x001F);	 //U波2
	GUI_Line(232, 41, 236, 43,0x001F);	 //U波3
	GUI_Line(236, 43, 240, 45,0x001F);	 //U波4
	
	//----------------下面是整体右移波形------------------------------------------------//
	GUI_Line(164+76, 45, 190+66, 45,0x001F);  //（（起始列，起始行，结束列，结束行）直线
	GUI_Line(190+66, 45, 195+66, 50,0x001F);	 //P波
	GUI_Line(197+66, 52, 202+66, 24,0x001F);	 //QRS波1（左边）
	GUI_Line(202+66, 24, 206+66, 58,0x001F);	 //QRS波2（右边）
	GUI_Line(206+66, 58, 212+66, 45,0x001F);	 //ST段1
	GUI_Line(212+66, 45, 215+66, 40,0x001F);	 //ST段2
	
	GUI_Line(215+66, 40, 218+66, 38,0x001F);	 //T波1
	GUI_Line(218+66, 38, 221+66, 37,0x001F);	 //T波2
	GUI_Line(221+66, 37, 224+66, 37,0x001F);	 //T波3
	
	GUI_Line(224+66, 37, 228+66, 39,0x001F);	 //U波1
	GUI_Line(228+66, 39, 232+66, 41,0x001F);	 //U波2
	GUI_Line(232+66, 41, 236+66, 43,0x001F);	 //U波3
	GUI_Line(236+66, 43, 240+66, 45,0x001F);	 //U波4
	GUI_Line(240+66, 45, 250+66, 45,0x001F);

//-----------------------------------------------------------------------------------//
}
/**********************************************************************
**函数名：	ECG_Samp_Inf（void）（这对话框自己画的）
**函数功能：画一个对话框，里面有采样值，电压转换值，心率
**函数参数：无      
**函数返回：无
***********************************************************************/
void ECG_Samp_Inf(void)
{
	GUI_SetColor(GUI_BLACK);
	GUI_SetBkColor(GUI_WHITE);
	GUI_DrawRect(18, 0, 155, 76);							//画一个框（外框）(起始列，起始行，结束列，结束行)	
	GUI_ClearRect(21, 3, 152, 73);			 				//把这个区域清为背景颜色
	GUI_SetBkColor(GUI_DARKGRAY);
	GUI_ClearRect(21, 3, 152, 12);			 				//把这个区域清为背景颜色
	GUI_SetColor(GUI_WHITE);
	GUI_SetFont(&GUI_Font8_ASCII);			 				//设置字体
	GUI_DispStringAt("ECG Sampling Information", 22, 4);   	//("字符"，列，行)
	GUI_DrawRect(19, 1, 154, 75);							//画框（中间框）
	GUI_SetColor(GUI_GRAY);									//设置颜色
	GUI_DrawRect(20, 2, 153, 74);							//画框 （内框）
	GUI_SetColor(GUI_BLACK);
	GUI_SetBkColor(GUI_WHITE);
	GUI_SetFont(&GUI_Font13B_ASCII);
	GUI_DispStringAt("SAM_VAL:", 22, 15);   				//("字符"，列，行)
	GUI_DispStringAt("ADC_VAL:     .        V", 22, 30);	//显示转换好的电压值
	GUI_DispStringAt("Heart Rate:          p/min", 22, 45);	//显示心率

	GUI_DispStringAt("Wave num:",22, 60);					//显示波形个数
}
void Load_Sys_ICO(void)	  		//加载系统图标
{
	GUI_SetColor(GUI_BLUE);		 		//设置笔画颜色
	GUI_SetBkColor(GUI_WHITE);	 		//设置背景颜色
	GUI_Clear();
	Show_BMP(40,10,100,100,gImage_dd); 		//（起始列，起始行，图片的宽，图片的高）
	Show_BMP(180,10,100,100,gImage_cc);
	Show_BMP(40,130,100,100,gImage_dazhen);
	Show_BMP(180,130,100,100,gImage_bb);

	GUI_DrawRect(39, 9, 140, 110);		//画一个框（外框）(起始列，起始行，结束列，结束行)	
	GUI_DrawRect(38, 8, 141, 111);
	GUI_DrawRect(37, 7, 142, 112);
	GUI_DrawRect(36, 6, 143, 113);
}
void Show_ICO(void)
{
	GUI_SetColor(GUI_BLUE);		 		//设置笔画颜色
	GUI_SetBkColor(GUI_WHITE);	 		//设置背景颜色
	GUI_Clear();
	Show_BMP(40,10,100,100,gImage_dd); 		//（起始列，起始行，图片的宽，图片的高）
	Show_BMP(180,10,100,100,gImage_cc);
	Show_BMP(40,130,100,100,gImage_dazhen);
	Show_BMP(180,130,100,100,gImage_bb);
}
void Select_Menu(void)		   //选择桌面图标
{
	GUI_SetFont(&GUI_Font13B_ASCII);
	TouchX=GUI_TOUCH_X_MeasureX();
	TouchY=GUI_TOUCH_X_MeasureY();
//	GUI_DispDecAt(TouchX,92,50,5);
//	GUI_DispDecAt(TouchY,92,70,5);
	if(TouchX>2300&&TouchX<3670&&TouchY<1870&&TouchY>830)
	{
		GUI_DrawRect(39, 9, 140, 110);		//画一个框（外框）(起始列，起始行，结束列，结束行)	
		GUI_DrawRect(38, 8, 141, 111);
		GUI_DrawRect(37, 7, 142, 112);
		GUI_DrawRect(36, 6, 143, 113);
		GUI_SetColor(GUI_WHITE);		
		GUI_DrawRect(179, 9, 280, 110);
		GUI_DrawRect(178, 8, 281, 111);
		GUI_DrawRect(177, 7, 282, 112);
		GUI_DrawRect(176, 6, 283, 113);
		GUI_DrawRect(39, 129, 140, 230);
		GUI_DrawRect(38, 128, 141, 231);
		GUI_DrawRect(37, 127, 142, 232);
		GUI_DrawRect(36, 126, 143, 233);
		GUI_DrawRect(179, 129, 280, 230);
		GUI_DrawRect(178, 128, 281, 231);
		GUI_DrawRect(177, 127, 282, 232);
		GUI_DrawRect(176, 126, 283, 233);
		GUI_SetColor(GUI_BLUE);
		TouchX=4000;TouchY=4000;
		{++i;j=0;k=0;l=0;}
		if(i==2) {index=1;i=0;}
		GUI_Delay(300);		
	}
	if(TouchX>2300&&TouchX<3670&&TouchY<3430&&TouchY>2370)
	{
		GUI_SetColor(GUI_WHITE);		
		GUI_DrawRect(39, 9, 140, 110);		//画一个框（外框）(起始列，起始行，结束列，结束行)	
		GUI_DrawRect(38, 8, 141, 111);
		GUI_DrawRect(37, 7, 142, 112);
		GUI_DrawRect(36, 6, 143, 113);
		GUI_DrawRect(39, 129, 140, 230);
		GUI_DrawRect(38, 128, 141, 231);
		GUI_DrawRect(37, 127, 142, 232);
		GUI_DrawRect(36, 126, 143, 233);
		GUI_DrawRect(179, 129, 280, 230);
		GUI_DrawRect(178, 128, 281, 231);
		GUI_DrawRect(177, 127, 282, 232);
		GUI_DrawRect(176, 126, 283, 233);
		GUI_SetColor(GUI_BLUE);
		GUI_DrawRect(179, 9, 280, 110);
		GUI_DrawRect(178, 8, 281, 111);
		GUI_DrawRect(177, 7, 282, 112);
		GUI_DrawRect(176, 6, 283, 113);
		TouchX=4000;TouchY=4000;
		{i=0;j+=1;k=0;l=0;}
		if(j==2) {index=2;j=0;}
		GUI_Delay(300);
	}
	if(TouchX>450&&TouchX<1860&&TouchY<1870&&TouchY>830)
	{
		GUI_SetColor(GUI_WHITE);		
		GUI_DrawRect(39, 9, 140, 110);		//画一个框（外框）(起始列，起始行，结束列，结束行)	
		GUI_DrawRect(38, 8, 141, 111);
		GUI_DrawRect(37, 7, 142, 112);
		GUI_DrawRect(36, 6, 143, 113);
		GUI_DrawRect(179, 9, 280, 110);
		GUI_DrawRect(178, 8, 281, 111);
		GUI_DrawRect(177, 7, 282, 112);
		GUI_DrawRect(176, 6, 283, 113);
		GUI_DrawRect(179, 129, 280, 230);
		GUI_DrawRect(178, 128, 281, 231);
		GUI_DrawRect(177, 127, 282, 232);
		GUI_DrawRect(176, 126, 283, 233);
		GUI_SetColor(GUI_BLUE);		
		GUI_DrawRect(39, 129, 140, 230);
		GUI_DrawRect(38, 128, 141, 231);
		GUI_DrawRect(37, 127, 142, 232);
		GUI_DrawRect(36, 126, 143, 233);
		TouchX=4000;TouchY=4000;
		{i=0;j=0;k+=1;l=0;}
		if(k==2) {index=3;k=0;}
		GUI_Delay(300);
	}
	if(TouchX>450&&TouchX<1860&&TouchY<3430&&TouchY>2370)
	{
		GUI_SetColor(GUI_WHITE);		
		GUI_DrawRect(39, 9, 140, 110);		//画一个框（外框）(起始列，起始行，结束列，结束行)	
		GUI_DrawRect(38, 8, 141, 111);
		GUI_DrawRect(37, 7, 142, 112);
		GUI_DrawRect(36, 6, 143, 113);
		GUI_DrawRect(179, 9, 280, 110);
		GUI_DrawRect(178, 8, 281, 111);
		GUI_DrawRect(177, 7, 282, 112);
		GUI_DrawRect(176, 6, 283, 113);
		GUI_DrawRect(39, 129, 140, 230);
		GUI_DrawRect(38, 128, 141, 231);
		GUI_DrawRect(37, 127, 142, 232);
		GUI_DrawRect(36, 126, 143, 233);
		GUI_SetColor(GUI_BLUE);		
		GUI_DrawRect(179, 129, 280, 230);
		GUI_DrawRect(178, 128, 281, 231);
		GUI_DrawRect(177, 127, 282, 232);
		GUI_DrawRect(176, 126, 283, 233);
		TouchX=4000;TouchY=4000;
		{i=0;j=0;k=0;l+=1;}
		if(l==2) {index=4;l=0;}
		GUI_Delay(300);	
	}
	GUI_DispDecAt(index,310,50,1);
	GUI_DispDecAt(i,310,62,1);
	GUI_DispDecAt(j,310,74,1);
	GUI_DispDecAt(k,310,86,1);
	GUI_DispDecAt(l,310,98,1);
	switch(index)
	{
		case 1://分压式电阻测量
			Draw_ECG_Wave();
			Load_Sys_ICO();//重新加载系统菜单
			index=0; 				   
			break;
		case 2://自动控制测量	 
			Draw_Any_Graph();
//			LCD_Fill(0,0,239,319,WHITE);//清屏
			Load_Sys_ICO();//重新加载系统菜单
			index=0;
			break;
		case 3://自动测试曲线	 
//			Pen_Viewer();
//			LCD_Fill(0,0,239,319,WHITE);//清屏
//			Load_Sys_ICO();//重新加载系统菜单
			index=0;
			break; 
		case 4://时间模式	 
//			ECG_Viewer();
//			LCD_Fill(0,0,239,319,WHITE);//清屏
//			Load_Sys_ICO();//重新加载系统菜单
			index=0;
			break;
		case 5://	 

			break;
		default:break;

	}	
}
void Draw_ECG_Wave(void)
{

	unsigned int i,j,r=1;
	signed int SAM_VAL;
	unsigned short max1=0,max2=0;
	unsigned short c1=0,c2=0;
	u8 USB_BUFF[6];
	float temp1;
	
	pDataBuff = &ECG_Buff[0];
	GUI_SetColor(GUI_WHITE);
	GUIDEMO_Graph();						//开始画波形前的画面
	FrameWin();								//画一个GUI对话框
	ECG_Wave();								//画一个标准的ECG参考波形
	My_Return_Bottom();
	ECG_Samp_Inf();
//---------初始化文件系统-------------------------------------------//									  
	f_mount(0, &fs);			
	res=f_open(&file,"ECG_FILE1.TXT", FA_OPEN_ALWAYS|FA_WRITE ); 	//以读写方式打开不存在则建立
	f_close(&file);			 										//关闭文件
	f_open(&file,"ECG_FILE1.TXT", FA_OPEN_ALWAYS|FA_WRITE ); 	   	//以读写方式打开不存在则建立
	f_lseek(&file,file.fsize); 										//移动指针
	f_write(&file,"JDSLJFDJLJLSJFAL",10,&br);				   	//每次rest后分隔文件
	f_printf(&file,"\n");
	f_close(&file);			 //关闭文件
//------------------------------------------------------------------//		USB_BUFF[0]='_';
	USB_BUFF[5]='\0'; 
	while(1) 
	{	
		j=0;
		max1=1000,max2=1000,c1=1000,c2=1000;
//-----------打开文件开始写入数据------------------------//
		f_open(&file,"ECG_FILE1.TXT", FA_OPEN_ALWAYS|FA_WRITE );	//以读写方式打开不存在则建立
		f_lseek(&file,file.fsize); 								//移动指针
		f_write(&file,__TIME__,9,&br); 							//获得GUI时间并写到SD卡txt文件中
		f_write(&file," ",1,&br);  								//写空格
		f_printf(&file,"%d",r);	  								//写一个ECG波形序号
		f_printf(&file,"\n");	 								//换行

		GUI_SetColor(GUI_BLUE);		 		//设置笔画颜色
		GUI_SetBkColor(GUI_WHITE);	 		//设置背景颜色
		GUI_DispDecAt(r,92,60,5);			//在（115列，15行，数据长度为5为）显示波形个数
		for(i=0;i<ECG_BUFF_SIZE;i++) 		//ECG_BUFF_SIZE=320
		{
//			iir_reset();					//滤波器复位
			SAM_VAL=Get_Adc(ADC_Channel_0);	//获取ADC采样值
			GUI_DispDecAt(SAM_VAL,82,15,4);	//在（82列，15行，数据长度为4为）显示采样值
			ECG_Buff[i]=SAM_VAL;			//把采样值装入数组里
//			adcv=ECG_Buff[i];				//滤波
//			ECG_Buff[i]=iir_filter(adcv);	//iir滤波器
			USB_BUFF[1]=(ECG_Buff[i]-ECG_Buff[i]%1000)/1000+48;
			USB_BUFF[2]=(ECG_Buff[i]%1000-ECG_Buff[i]%1000%100)/100+48;
			USB_BUFF[3]=(ECG_Buff[i]%1000%100-ECG_Buff[i]%1000%100%10)/10+48;
			USB_BUFF[4]=ECG_Buff[i]%1000%100%10+48;
			USB_SendString(USB_BUFF);
//-----------把ADC采集到的数据写入SD卡------------------------//
			temp1=(float)SAM_VAL*(3.3/4096);
			SAM_VAL=temp1;
			GUI_DispDecAt(SAM_VAL,80,30,1);	  //(列，行，数据多少位)
			SD_BUFF[j]=(u8)(SAM_VAL)+48;
			temp1-=SAM_VAL;
			temp1*=1000;
			GUI_DispDecAt(temp1,96,30,3);
			SD_BUFF[j+1]=(u8)(temp1/100)+48;
			SD_BUFF[j+2]=' ';
			j=j+3;
			if(j>M) j=0;
			//delay_us(100);
			//delay_ms(1);
			GUI_Delay(4);
			TouchX=GUI_TOUCH_X_MeasureX();
			TouchY=GUI_TOUCH_X_MeasureY();
			if(TouchX<450&&TouchY>3500) 
			{
				Delete_Window();
				return;
			}
			else;
		}
//-----------把ADC采集到的数据写入SD卡------------------------//
		f_write(&file,SD_BUFF,M,&br);				   			//每次rest后分隔文件
		f_printf(&file,"\n");					//10个数据就换行一次
		f_printf(&file,"\n");	 //换行
		f_printf(&file,"\n");	 //换行
		f_close(&file);			 //关闭文件
//------------求数组中最大值------------------------//
		for(i=0;i<ECG_BUFF_SIZE;i++)
		{
		  if(ECG_Buff[i]>max1) {max1=ECG_Buff[i];c1=i;}		  
		}
//------------求数组中第二大值-----------------------//
		for(i=0;i<ECG_BUFF_SIZE;i++)
		{
		  if(max1>ECG_Buff[i]&&ECG_Buff[i]>max2) {max2=ECG_Buff[i];c2=i;}		  
		}
		c1=(60000000/((abs(c1-c2))*4650));			 //心率=两个QRS波周期的倒数 心率=60秒/（QRS_1-QRS-2)秒
		if(50<c1&&c1<100)
			GUI_DispDecAt(c1,93,45,3);				 //把心率显示出来

		if(pDataBuff)
		{
//			Filter(pDataBuff, DATA_BUFF_SIZE); //此语句原来为屏蔽,用于滤波
			ECG_Draw();
			//pDataBuff = 0;
			//GUI_Delay(10);
		}
		r++;			//一个ECG波形的序号加1
					

	}
}
void Draw_Any_Graph(void)
{
	GUI_SetColor(GUI_WHITE);		 		//设置笔画颜色
	My_Return_Bottom();
	My_GUIDEMO_Graph();						//开始画波形

	while(1)
	{
		TouchX=GUI_TOUCH_X_MeasureX();
		TouchY=GUI_TOUCH_X_MeasureY();
		if(TouchX<450&&TouchY>3500) 
		{
			Delete_Window();
			return;
		}
		else;
	}
}
