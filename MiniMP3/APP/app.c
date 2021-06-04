#define GLOBALS
#include "includes.h"
#include "demo.h"

#include "my_eval.h"
//#include "usb_lib.h"
//#include "hw_config.h"
//#include "stm32f10x_it.h"

//#include "GUIDEMO.h"

#include "sdio_sdcard.h"
#include "integer.h"
#include "ff.h"
#include "ffconf.h"
#include "diskio.h"



extern void GUIDEMO_main(void);		

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  OS_STK App_TaskStartStk[APP_TASK_START_STK_SIZE];
static  OS_STK AppTaskUserIFStk[APP_TASK_USER_IF_STK_SIZE];
static  OS_STK AppTaskKbdStk[APP_TASK_KBD_STK_SIZE];


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void App_TaskCreate(void);

static  void App_TaskStart(void* p_arg);
static  void  AppTaskUserIF (void *p_arg);

static  void AppTaskKbd(void* p_arg);

void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,uint16_t Len);


/****************************************************************************
* 名    称：int main(void)
* 功    能：主函数入口
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
int main(void)
{
   CPU_INT08U os_err; 
   /* 禁止所有中断 */
   CPU_IntDis();
   
   /* ucosII 初始化 */
   OSInit();                                                  

   /* 硬件平台初始化 */
   BSP_Init();                               
   
   //建立主任务， 优先级最高  建立这个任务另外一个用途是为了以后使用统计任务
   os_err = OSTaskCreate((void (*) (void *)) App_TaskStart,               		    //指向任务代码的指针
                          (void *) 0,												//任务开始执行时，传递给任务的参数的指针
               		     (OS_STK *) &App_TaskStartStk[APP_TASK_START_STK_SIZE - 1],	//分配给任务的堆栈的栈顶指针   从顶向下递减
                         (INT8U) APP_TASK_START_PRIO);								//分配给任务的优先级
             
   OSTimeSet(0);			 //ucosII的节拍计数器清0    节拍计数器是0-4294967295  
   OSStart();                //启动ucosII内核   
   return (0);
}




/****************************************************************************
* 名    称：static  void App_TaskStart(void* p_arg)
* 功    能：开始任务建立
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
static  void App_TaskStart(void* p_arg)
{
 
  (void) p_arg;
   //初始化ucosII时钟节拍
   OS_CPU_SysTickInit();
                               
   //使能ucos 的统计任务
#if (OS_TASK_STAT_EN > 0)
   
   OSStatInit();                //----统计任务初始化函数                                 
#endif

   App_TaskCreate();			//建立其他的任务

   while (1)
   {  
      LED_LED1_ON();		      	  
	  OSTimeDlyHMSM(0, 0, 0, 100);

	  LED_LED1_OFF();
	  OSTimeDlyHMSM(0, 0, 0, 100);
   }
}

/****************************************************************************
* 名    称：static  void App_TaskCreate(void)
* 功    能：建立其余任务的函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
static  void App_TaskCreate(void)
{
  
   NMEA_MBOX=OSSemCreate(1);		                                           //建立NMEA指令解析的信号量
   /*  建立用户界面任务 */
   OSTaskCreateExt(AppTaskUserIF,											   //指向任务代码的指针
   					(void *)0,												   //任务开始执行时，传递给任务的参数的指针
   					(OS_STK *)&AppTaskUserIFStk[APP_TASK_USER_IF_STK_SIZE-1],  //分配给任务的堆栈的栈顶指针   从顶向下递减
					APP_TASK_USER_IF_PRIO,									   //分配给任务的优先级
					APP_TASK_USER_IF_PRIO,									   //预备给以后版本的特殊标识符，在现行版本同任务优先级
					(OS_STK *)&AppTaskUserIFStk[0],							   //指向任务堆栈栈底的指针，用于堆栈的检验
                    APP_TASK_USER_IF_STK_SIZE,									//指定堆栈的容量，用于堆栈的检验
                    (void *)0,													//指向用户附加的数据域的指针，用来扩展任务的任务控制块
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);					//选项，指定是否允许堆栈检验，是否将堆栈清0,任务是否要
					                                                            //进行浮点运算等等。
                    
   /*   建立触摸驱动任务 */
   OSTaskCreateExt(AppTaskKbd,
   					(void *)0,
					(OS_STK *)&AppTaskKbdStk[APP_TASK_KBD_STK_SIZE-1],
					APP_TASK_KBD_PRIO,
					APP_TASK_KBD_PRIO,
					(OS_STK *)&AppTaskKbdStk[0],
                    APP_TASK_KBD_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR);	
}

/****************************************************************************
* 名    称：static  void  AppTaskUserIF (void *p_arg)
* 功    能：用户界面任务
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
static  void  AppTaskUserIF (void *p_arg)
{											   
 	(void)p_arg;
								    
	RCC_Configuration1();					//系统时钟配置
	NVIC_Configuration1();					//中断配置
//	TIM3_Configuration(5000);
	GPIO_Configuration1();					//I/O口配置
	SD_TEST();               				//SD卡测试函数
//----------USB硬件初始化------------------// 硬件初始化一定要放在前面，不然就超时，电脑无法识别
	USB_Interrupts_Config();
	Set_USBClock();    
	USB_Init();
//-------------------------------------------//
//	delay_init(72);							//系统节拍初始化
	MY_ADC_Init();							//ADC配置初始化
  	GUI_Init();	                			//ucgui初始化 
//	GUIDEMO_main();	   						//开始显示GUI例程
	GUIDEMO_Intro();	   					//显示第一个画面，GUI信息
	GUIDEMO_DemoProgBar();					//进度条
	
		

	Load_Sys_ICO();
	while(1) 
	{	

		Select_Menu();
		GUI_CURSOR_Show();						   //显示光标
	}
}
/****************************************************************************
* 名    称：static  void  AppTaskKbd (void *p_arg)
* 功    能：触摸屏坐标获取任务
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
static  void  AppTaskKbd (void *p_arg)
{
  (void)p_arg;   
   while(1) 
   { 
   	  /* 延时10ms会读取一次触摸坐标	*/
      OSTimeDlyHMSM(0,0,0,10); 	               
	  GUI_TOUCH_Exec();    
   }
}


#if (OS_APP_HOOKS_EN > 0)
/*
*********************************************************************************************************
*                                      TASK CREATION HOOK (APPLICATION)
*
* Description : This function is called when a task is created.
*
* Argument : ptcb   is a pointer to the task control block of the task being created.
*
* Note     : (1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

void App_TaskCreateHook(OS_TCB* ptcb)
{
}

/*
*********************************************************************************************************
*                                    TASK DELETION HOOK (APPLICATION)
*
* Description : This function is called when a task is deleted.
*
* Argument : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note     : (1) Interrupts are disabled during this call.
*********************************************************************************************************
*/

void App_TaskDelHook(OS_TCB* ptcb)
{
   (void) ptcb;
}

/*
*********************************************************************************************************
*                                      IDLE TASK HOOK (APPLICATION)
*
* Description : This function is called by OSTaskIdleHook(), which is called by the idle task.  This hook
*               has been added to allow you to do such things as STOP the CPU to conserve power.
*
* Argument : none.
*
* Note     : (1) Interrupts are enabled during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 251
void App_TaskIdleHook(void)
{
}
#endif

/*
*********************************************************************************************************
*                                        STATISTIC TASK HOOK (APPLICATION)
*
* Description : This function is called by OSTaskStatHook(), which is called every second by uC/OS-II's
*               statistics task.  This allows your application to add functionality to the statistics task.
*
* Argument : none.
*********************************************************************************************************
*/

void App_TaskStatHook(void)
{
}

/*
*********************************************************************************************************
*                                        TASK SWITCH HOOK (APPLICATION)
*
* Description : This function is called when a task switch is performed.  This allows you to perform other
*               operations during a context switch.
*
* Argument : none.
*
* Note     : 1 Interrupts are disabled during this call.
*
*            2  It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                   will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the
*                  task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/

#if OS_TASK_SW_HOOK_EN > 0
void App_TaskSwHook(void)
{
}
#endif

/*
*********************************************************************************************************
*                                     OS_TCBInit() HOOK (APPLICATION)
*
* Description : This function is called by OSTCBInitHook(), which is called by OS_TCBInit() after setting
*               up most of the TCB.
*
* Argument : ptcb    is a pointer to the TCB of the task being created.
*
* Note     : (1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/

#if OS_VERSION >= 204
void App_TCBInitHook(OS_TCB* ptcb)
{
   (void) ptcb;
}
#endif

#endif

