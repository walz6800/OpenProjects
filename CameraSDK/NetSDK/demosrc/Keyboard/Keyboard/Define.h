#ifndef _DEFINE_H
#define _DEFINE_H



#define		MAXWNDNUM		16		//最大窗口数

#define WM_MYCOMMAND		(WM_USER+1)
#define ID_ADD_DEVICE		(WM_USER+100)
#define ID_DELETE_DEVICE	(WM_USER+101)
#define ID_MODIFY_DEVICE	(WM_USER+4)
#define ID_CONNNECT			(WM_USER+5)
#define ID_DISCONNECT		(WM_USER+6)
#define ID_START_TALK		(WM_USER+7)
//设备信息
typedef struct _DEV_INFO 
{
	long lLoginID;			//登陆句柄
	long lID;				//唯一标志号
	char szDevName[60];		//设备名
	char szIpaddress[15];		//设备名
	char szUserName[8];		//用户名
	char szPsw[8];			//密码
	int nPort;				//端口
	int nTotalChannel;		//通道数
}DEV_INFO;


struct ModuleFileInfomations
{
	CString		strFullPath;
	CString		strPath;
	CString		strDrive;
	CString		strDir;
	CString		strName;
	CString		strExt;
};






#endif