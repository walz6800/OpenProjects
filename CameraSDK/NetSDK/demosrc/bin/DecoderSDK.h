#ifndef DECODERSDK_H
#define DECODERSDK_H

#ifdef DECODER_EXPORTS
#define H264_DEC_API  extern "C" __declspec(dllexport)
#else
#define H264_DEC_API  extern "C" __declspec(dllimport)   //VC ”√
#endif
#include "netsdk.h"

typedef struct 
{
	BYTE byEncoderIP[16];		//Server IP that decoder connected
	BYTE byEncoderUser[16];		//Server Username that decoder connected
	BYTE byEncoderPasswd[16];	//Server Password that decoder connected
	BYTE bySendMode;			//Server Connection Mode that decoder connected
	BYTE byEncoderChannel;		//Server Channel No. that decoder connected
	WORD wEncoderPort;			//Server Port that decoder connected
	BYTE reservedData[4];		//Reserved
}H264_DEC_DECODERINFO, *LPH264_DEC_DECODERINFO;

H264_DVR_API bool H264_DEC_Init();
H264_DVR_API bool H264_DEC_Cleanup();
H264_DVR_API long H264_DEC_Login(char *sDVRIP, unsigned short wDVRPort, char *sUserName, char *sPassword,
							   LPH264_DVR_DEVICEINFO lpDeviceInfo);
							   
H264_DEC_API bool H264_DEC_StartDecode(long lUserID, long lChannel, LPH264_DEC_DECODERINFO lpDecoderinfo);
H264_DEC_API bool H264_DEC_StopDecode(long lUserID, long lChannel);
//lChannel = -1, means all decoder channel info
H264_DEC_API bool H264_DEC_GetDecoderInfo(long lUserID, long lChannel, LPH264_DEC_DECODERINFO lpDecoderInfo);
//dwControl: 1- full screen; 2- restore
H264_DEC_API bool H264_DEC_DecCtrlScreen(long lUserID, long lChannel, DWORD dwControl);
H264_DEC_API bool H264_DEC_DecCtrlScreen(long lUserID, long lChannel, DWORD dwControl);
H264_DVR_API bool H264_DEC_PTZControl(long lLoginID,int nChannelNo, long lPTZCommand, bool bStop = false, long lSpeed = 4);

#endif