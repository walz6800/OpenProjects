#ifndef CONF_MOD_H
#define CONF_MOD_H



#ifdef CONF_MOD_EXPORTS
#define CONF_MOD_API  __declspec(dllexport) 
#else
#define CONF_MOD_API  __declspec(dllimport)   //VC 用
#endif

typedef enum _XM_CFG_TYPE
{
	    XM_CFG_ROOT = 1,
		//录像
		XM_CFG_RECORD,
		XM_CFG_RECSET,  //录像设置
		XM_CFG_PICSET,    //图片设置

		//报警
		XM_CFG_ALARM,
		XM_CFG_MOTION,  //移动侦测
		XM_CFG_INPUT,  //报警输入
		XM_CFG_OUTPUT,  //报警输出
		XM_CFG_VIDEOLOSS,  //视频丢失
		XM_CFG_BLIND,  //视频遮挡
		
		//系统设置
		XM_CFG_SYS,
		XM_CFG_NORMAL,   //普通设置
		XM_CFG_ENCODE,   //编码设置
		XM_CFG_NETWORK,  //网络设置
		XM_CFG_SERVER,   //网络服务
		XM_CFG_OUTMODE,  //输出模式
		XM_CFG_PTZ,    //云台设置
		XM_CFG_COMM,  //串口设置
		XM_CFG_TOUR,   //轮巡设置

		//管理工具
		XM_CFG_TOOLMANAGER,
		XM_CFG_HARDDISK,  //硬盘管理
		XM_CFG_ACCOUT,   //用户管理
		XM_CFG_AUTOMAIN,  //自动维护
		XM_CFG_DEFAULT,  //恢复默认
		XM_CFG_UPGRADE,  //系统升级
		XM_CFG_DEVINFO,  //设备信息
		XM_CFG_REBOOT,   //系统重启

		//系统信息
		XM_CFG_SYSINFO,
		XM_CFG_DISKINFO,   //硬盘信息
		XM_CFG_LOG,   //日志信息
		XM_CFG_VESION,  //版本信息

		XM_CFG_MAX	=   500,
}XM_CFG_TYPE;

// 参数一:设备信息，二、获取数据类型，三、用户参数.
typedef int (CALLBACK * GetParmBackCallFunc)(long ConfigType, int nChannel,char* pConfigBuf,DWORD dwBufSize, DWORD dwUserParam, DWORD *lpRet /*= NULL*/);
typedef int (CALLBACK * SaveParmBackCallFunc)(long ConfigType, int nChannel,char* pConfigBuf,DWORD dwBufSize,DWORD dwUserParam);



//初始化
CONF_MOD_API BOOL Config_Init(CWnd *pParent);

//反初始化
CONF_MOD_API BOOL Config_UnInit();


//初始化语言
//pLanguagePath 语言绝对路径，包含文件名
CONF_MOD_API BOOL Config_languageInit(TCHAR *pLanguagePath);


//设备获取数据和保存数据回调
CONF_MOD_API BOOL Config_SetCallback(void * getCalback, void * saveCallback, DWORD dwUser);

//移动窗体位置
CONF_MOD_API BOOL Config_MoveWindow(CRect *rect, BOOL bShow);


//设备更改，重新获取所有数据
CONF_MOD_API BOOL Config_Refush();



#endif