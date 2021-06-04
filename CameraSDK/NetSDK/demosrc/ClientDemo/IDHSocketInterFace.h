// IDHSocketInterFace.h: interface for the IDHSocketInterFace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IDHSOCKETINTERFACE_H__8E1F686D_E4D7_475A_A228_E5D7FCB4CF86__INCLUDED_)
#define AFX_IDHSOCKETINTERFACE_H__8E1F686D_E4D7_475A_A228_E5D7FCB4CF86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"

//处理网络传送的视频数据回调
typedef int (__stdcall * CallbackFuncRealData )( long lRealHandle, 
												long dwDataType, unsigned char *pBuffer,
												long lbufsize,long dwUser);

//语音对讲回调
typedef void (CALLBACK *callbackFuncTalkData)(LONG lTalkHandle, char *pDataBuf, long dwBufSize, char byAudioFlag, long dwUser);

//设备断开回调
typedef void (__stdcall *fDevDisconnectCallback)(int nSvrType, long lLoginID, long lDevID, DWORD dwUser);

//录像查询数据回调
typedef void (__stdcall *fRecordQueryCallback)(H264_DVR_FILE_DATA* pRecFileInfo, int nNum, DWORD dwUser);

//通知应用层( display )设备报警信息
typedef void( CALLBACK* CallbackAlarmInfo )( long lDevcID , unsigned char* pBuf , DWORD dwLen , DWORD dwUser );


class IDHSocketInterFace  
{
public:

	IDHSocketInterFace();
	virtual ~IDHSocketInterFace();
	static IDHSocketInterFace* CreateObject(VENDOR_TYPE nMode);
	static void DeleteObject(VENDOR_TYPE nMode);


//以下接口函数	

	/*	$Function		:	ConnectServer
	==  ===============================================================
	==	Description		:	连接服务器
	==	Argument		:	szIP		地址
	==					:	nPort		端口
						:   szUserName	用户名
						:	szPassword	密码
	== 	Return			:	TRUE, FALSE
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int ConnectServer(char *szIP, int nPort, const char* szUserName , const char* szPassword) = 0;

	/*	$Function		:	DisconnectServer
	==  ===============================================================
	==	Description		:	断开服务器连接
	==	Argument		
	== 	Return			:	TRUE, FALSE
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual BOOL DisconnectServer() = 0;
	

	/*	$Function		:	ReuestDataFromCenter
	==  ===============================================================
	==	Description		:	从服务器获取信息
	==	Argument		:
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int RequestDataFromServer(XM_DataType nType = XM_Data_NULL) = 0;
		
	//检测原先是否处于语音对讲状态,会议功能使用
	//PC机器上语音对讲和会议功能只能有一个在使用
	virtual bool IsTalkingWithDevice() = 0;


	/*	$Function		:	SynchroDevice
	==  ===============================================================
	==	Description		:	设备时间同步
	==	Argument		:	lTSID	(对于商业版本,代表流媒体地址, 对于直连版本,代表SDK的设备句柄)
						:	lDevcID (设备ID, 对于直连版本无效)
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int SynchroDevice( long lTSID , long lDevcID ) = 0;


	/*	$Function		:	ConnectDevice
	==  ===============================================================
	==	Description		:	连接设备
	==	Argument		:	devcInfo		登陆的设备信息
						:	pOutDevcInfo	登陆后返回的设备信息
	== 	Return			:	对于商业版本,返回流媒体句柄, 直连版本返回设备登陆句柄
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int ConnectDevice( DEVICE_INFO devcInfo , DEVICE_INFO* const pOutDevcInfo ) = 0; 


	/*	$Function		:	DisconnectDevice
	==  ===============================================================
	==	Description		:	断开设备连接
	==	Argument		:	lTSID		(商业版本:流媒体句柄, 直连版本SDK登陆句柄)
						:	lDevcID		设备ID,直连版本无效
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int DisconnectDevice( long lTSID ,long lDevcID ) = 0;


	/*	$Function		:	ConnectChanel
	==  ===============================================================
	==	Description		:	连接通道
	==	Argument		:	lTSID		(商业版本:流媒体句柄, 直连版本SDK登陆句柄)
						:	pDevc		连接的设备信息
						:	lChannelNO	通道号
						:	type		监视类型(主辅码流,预览等)
	== 	Return			:	直连设备返回播放句柄, 商业版本返回设备的ID号, 在关闭时候使用
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int ConnectChanel( long lTSID , DEVICE_INFO* pDevc , LPH264_DVR_CLIENTINFO pInfo, CallbackFuncRealData func , DWORD dwUserParm ) = 0;
	//断开通道
	//lDevcID 在直连版本中就是播放句柄
	virtual long DisconnectChannel(long lLoginID, long lDevcID, CallbackFuncRealData func , DWORD dwUserParm) = 0;


	/*	$Function		:	StartTalking
	==  ===============================================================
	==	Description		:	开始语音对讲
	==	Argument		:	lLoginID		(商业版本:流媒体句柄, 直连版本SDK登陆句柄)
						:	nTalkFlag		对讲音频编码类型
	== 	Return			:	商业版本返回设备ID, 直连版本返回对讲句柄,供关闭和发送数据时候使用
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual long StartTalking(long lLoginID , int nTalkFlag, callbackFuncTalkData pCallback, DWORD dwUserData) = 0;


	/*	$Function		:	SendTalkData
	==  ===============================================================
	==	Description		:	发送语音对讲数据
	==	Argument		:	lTSID		(商业版本:流媒体句柄, 直连版本无效)
						:	lTalkhandle	(商业版本:设备ID, 直连版本SDK登陆句柄)
						:	pDataBuffer		对讲数据
						:	dwDataLength	音频长度
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int SendTalkData(long lTSID, long lTalkhandle, LPBYTE pDataBuffer,DWORD dwDataLength) =0 ;
	

	/*	$Function		:	StopTalking
	==  ===============================================================
	==	Description		:	停止语音对讲
	==	Argument		:	lTSID		(商业版本:流媒体句柄, 直连版本无效)
						:	lDevcID		商业版本设备ID,直连版本对讲句柄
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int StopTalking( long lTSID , long lDevcID ) = 0;


	/*	$Function		:	QueryPower
	==  ===============================================================
	==	Description		:	查询是否有权限, 这个函数对于直连的无效
	==	Argument		:	lTSID		(商业版本:流媒体句柄, 直连版本SDK登陆句柄)
						:	type		权限类型
						:	lDevcID
						:	lChannel
						:	PreviewType
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	//设备id和通道号同时传0时,表示该权限只和用户挂钩,和设备通道无关
	//virtual int QueryPower( POWER_TYPE type , long lDevcID , long lChannel , NET_RealPlayType PreviewType = NET_RType_Realplay ) = 0; 
	

	/*	$Function		:	PTZControl
	==  ===============================================================
	==	Description		:	云台控制
	==	Argument		:	lLoginID	(商业版本:流媒体句柄, 直连版本SDK登陆句柄)
						:	lDevcID
						:	lChannel
						:	dwPTZCommand
						:	lParam1
						:	lParam2
						:	lParam3
						:	dwStop		0 开始 , 1 停止
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int PTZControl( LONG lLoginID , long lDevcID , int nChannelID, DWORD dwPTZCommand, 
		long lParam1, long lParam2, long lParam3, BOOL dwStop ) = 0;


	/*	$Function		:	QueryDevSystemInfo
	==  ===============================================================
	==	Description		:	查询设备的配置信息,能力等
	==	Argument		:	lLoginID		(商业版本:流媒体句柄, 直连版本SDK登陆句柄)
						:	lDevcID
						:	lConfigType		查询配置类型
						:	nChannelNO		通道号(如果是设备的配置,通道号为-1, )
						:	pConfigBuf		查询结果缓冲
						:	dwBufSize		返回的结果长度
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int QueryDevSystemInfo(long lLonginID , long lDevID , long lConfigType , int nChannelNO, char* pConfigBuf, DWORD dwBufSize, DWORD *lpRet = NULL) = 0;
	//保存配置,参数同QueryDevSystemInfo
	virtual int SaveIOControlState( long lLonginID , long lDevID , long lConfigType , int nChannelNO, char* pConfigBuf, DWORD dwBufSize) = 0;
	

	/*	$Function		:	RebootDevice
	==  ===============================================================
	==	Description		:	重启DVR
	==	Argument		:	lTSID			(商业版本:流媒体句柄, 直连版本SDK登陆句柄)
						:	lDevcID			设备ID号,直连版本中无效
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int RebootDevice( long lTSID , long lDevcID) = 0;


	/*	$Function		:	RequestUserIsLogin
	==  ===============================================================
	==	Description		:	删除用户时候,验证当前用户是否已经登陆,如果已经登陆则无法删除
	==	Argument		:	szUserName		用户名
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual long RequestUserIsLogin(char *szUserName) = 0;
	


	/*	$Function		:	QueryRecordFile
	==  ===============================================================
	==	Description		:	查询录像记录
	==	Argument		:	lLoginID		商业版本代表流媒体对象,质量代表设备登陆句柄
						:	pRecQueryParam	查询录像条件
						:	nWaitTime		查询等待时间
						:	pRecQueryCallback	查询记录回调
						:	dwUser			回调对象
	== 	Return			:
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual int QueryRecordFile( long lLoginID,
								RECORD_QUERY_PARAM* pRecQueryParam, 
								int nWaitTime /* = 5000  */,
								void* pRecQueryCallback /*= NULL*/, 
								DWORD dwUser /*= 0*/) = 0;

	/*	$Function		:	PlayBackByRecordFile
	==  ===============================================================
	==	Description		:	回放录像记录
	==	Argument		:	lLoginID		商业版本代表流媒体对象,质量代表设备登陆句柄
						:	lDevID			设备ID,直连版本无效
						:	pRecFile		回放的文件信息
						:	pDownloadPosCallback	进度回调
						:	dwPosUser				进度回调对象
						:	pNetDataCallback		数据回调
						:	dwDataUser				数据回调对象
	== 	Return			:	商业版本流媒体对象,直连版本回放句柄
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual long PlayBackByRecordFile( long lLoginID, long lDevID, 
		void *pRecFile, 
		void *pDownloadPosCallback, DWORD dwPosUser, 
		void *pNetDataCallback, DWORD dwDataUser ) = 0;

	/*	$Function		:	PlayBackByTime
	==  ===============================================================
	==	Description		:	按时间回放录像
	==	Argument		:	lLoginID		商业版本代表流媒体对象,质量代表设备登陆句柄
						:	lDevID			设备ID,直连版本无效
						:	nChannelNO		通道号
						:	pTmStart		开始时间
						:	pTmEnd			结束时间
						:	pDownloadPosCallback	进度回调
						:	dwPosUser				进度回调对象
						:	pNetDataCallback		数据回调
						:	dwDataUser				数据回调对象
	== 	Return			:	商业版本流媒体对象,直连版本回放句柄
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual long PlayBackByTime( long lLoginID, long lDevID, int nChannelNO, 
		LPH264_DVR_TIME pTmStart, LPH264_DVR_TIME pTmEnd, 
		void *pDownloadPosCallback, DWORD dwPosUser, 
		void *pNetDataCallback, DWORD dwDataUser ) = 0;	



	/*	$Function		:	StopPlayBack  PausePlayBack SeekPlayBack
	==  ===============================================================
	==	Description		:	录像控制
	==	Argument		:	lLoginID		设备登陆句柄(商业版本:流媒体地址,  直连版本: 登陆句柄)
						:	lPlayHandle		PLAY返回值(商业版本:设备ID, 直连版本: 回放句柄)
						:	nChannelNO		通道号,直连版本无效
						:	offsetTime		时间偏移
						:	offsetByte		位置偏移
	== 	Return			:	TRUE, FALSE
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	//停止网络回放
	virtual BOOL StopPlayBack( long lLoginID, long lPlayHandle, int nChannelNO ) = 0;	
	//暂停网络回放
	virtual BOOL PausePlayBack( long lLoginID, long lPlayHandle, int nChannelNO, BOOL bPause ) = 0;	
	//设置播放位置
	virtual BOOL SeekPlayBack( long lLoginID, long lPlayHandle, int nChannelNO, 
		unsigned int offsetTime, unsigned int offsetByte ) = 0;



	/*	$Function		:	DownloadByRecordFile
	==  ===============================================================
	==	Description		:	录像下载
	==	Argument		:	lLoginID		设备登陆句柄(商业版本:流媒体地址,  直连版本: 登陆句柄)
						:	lDevID			设备ID号(直连版本无效)
						:	pRecFile		文件信息
						:	szFileName		保存的文件名
						:	pDownloadPosCallback		进度回调
						:	dwPosUser				
	== 	Return			:	TRUE, FALSE
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual long DownloadByRecordFile( long lLoginID, long lDevID, 
		H264_DVR_FILE_DATA* pRecFile, 
		char* szFileName,
		void *pDownloadPosCallback, 
		DWORD dwPosUser ) = 0;
	
	virtual long DownloadByTime( LONG lLoginID, 
						long lDevID,
						int nChannelNo, 
						int nRecordFileType, 
						LPNET_TIME tmStart, 
						LPNET_TIME tmEnd, 
						char *sSavedFileName, 
						void * cbTimeDownLoadPos, 
						DWORD dwUserData ) = 0;


	/*	$Function		:	StopDownload
	==  ===============================================================
	==	Description		:	停止录像下载
	==	Argument		:	lLoginID		设备登陆句柄(商业版本:流媒体地址,  直连版本: 登陆句柄)
						:	lPlayHandle		DownloadByRecordFile的返回值(商业版本:设备ID号 直连版本:下载句柄)
						:	nChannelNO		通道号(直连版本无效)	
	== 	Return			:	TRUE, FALSE
	==	Modification	:	2008-09-26     sunjie    Create
	==  ===============================================================
	*/	
	virtual BOOL StopDownload( long lLoginID, long lPlayHandle, int nChannelNO ) = 0;


	//回调注册函数
	virtual void RegisterAllCallback(CALLBACK_TYPE nCallbacjType, void* pCallback, DWORD dwUserData) = 0;
	
	//保存报警方案数据到中心
	virtual int SaveAlarmPlanToServer(int nType = 0) = 0; 
	virtual int ReuestLogFile( int nYear,int nMonth ,int nDay ,int nPage , const char* szFindData ) = 0; //szFindData为查询条件

	//发送心跳包
	virtual BOOL SendHeartbeet() = 0;
	virtual BOOL PostHeartbeetData() = 0;
	virtual int CheckHearbeet() = 0;
	virtual void RecvHeartbeetData(unsigned char* pbuf , DWORD dwlen) = 0;
	//查询存储服务的录像
	//成功返回录像条数，失败返回<0
	virtual int QueryRecordFileFromServer( H264_DVR_FILE_DATA* pRecFileInfo,
		RECORD_QUERY_PARAM* pRecQueryParam, 
		char* szIP, int nPort, long& lConnID,
		int nWaitTime /*= 5000*/,
		void* pRecQueryCallback /*= NULL*/, DWORD dwUser /*= 0*/) = 0;
	//查询存储服务列表
	virtual BOOL QuerySSvrList( void* pCallbackFunc, DWORD dwUser ) = 0;
	virtual BOOL FinishToSendConfig() = 0;
	virtual int SendConfigToServer( XM_DataType type, CString strFileName ) = 0;
	virtual BOOL NotifyLocalCenter() = 0;
	virtual DWORD GetRecNetplayBufferSize(long lPlayHandle, long lDevID, int nChannelNO) = 0;
	virtual int SetupAlarmChan(long lLoginID) = 0;
	virtual LONG GetLastError() = 0;
	//开始录像
	virtual BOOL StartDVRRecord(long lLoginID, int nChannelNo ,long lRecordType) = 0;
	//关闭录像
	virtual BOOL StopDVRRecord(long lLoginID, int nChannelNo) = 0;

	//232，485读写
	virtual BOOL SerialWrite(long lLoginID, SERIAL_TYPE nType, char *pBuffer, int nBufLen) = 0;
	virtual BOOL SerialRead(long lLoginID, SERIAL_TYPE nType, char *pBuffer, int nBufLen, int *pReadLen) = 0;

};

#endif // !defined(AFX_IDHSOCKETINTERFACE_H__8E1F686D_E4D7_475A_A228_E5D7FCB4CF86__INCLUDED_)
