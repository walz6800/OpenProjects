# Microsoft Developer Studio Project File - Name="ClientDemo5" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ClientDemo5 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ClientDemo5.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ClientDemo5.mak" CFG="ClientDemo5 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ClientDemo5 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ClientDemo5 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ClientDemo5 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"../Bin/ConfigDemo.exe"

!ELSEIF  "$(CFG)" == "ClientDemo5 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"../bin/ConfigDemo.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ClientDemo5 - Win32 Release"
# Name "ClientDemo5 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AlarmInputDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmMotion.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmShelter.cpp
# End Source File
# Begin Source File

SOURCE=.\AlarmVLostDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AreaSelectDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientDemo5.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientDemo5.rc
# End Source File
# Begin Source File

SOURCE=.\ClientDemo5Dlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarm.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigChannel.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigComm.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigNetwork.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigPTZ.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigServer.cpp
# End Source File
# Begin Source File

SOURCE=.\motiondetect.cpp
# End Source File
# Begin Source File

SOURCE=.\multilanguage.cpp
# End Source File
# Begin Source File

SOURCE=.\PeriodTimeSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PtzLinkDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SysSettingCamera.cpp
# End Source File
# Begin Source File

SOURCE=.\TimeLineShowWnd.cpp
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ClientDemo5.ico
# End Source File
# Begin Source File

SOURCE=.\res\ClientDemo5.rc2
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AlarmInputDlg.h
# End Source File
# Begin Source File

SOURCE=.\AlarmMotion.h
# End Source File
# Begin Source File

SOURCE=.\AlarmShelter.h
# End Source File
# Begin Source File

SOURCE=.\AlarmVLostDlg.h
# End Source File
# Begin Source File

SOURCE=.\AreaSelectDlg.h
# End Source File
# Begin Source File

SOURCE=.\ClientDemo5.h
# End Source File
# Begin Source File

SOURCE=.\ClientDemo5Dlg.h
# End Source File
# Begin Source File

SOURCE=.\ConfigAlarm.h
# End Source File
# Begin Source File

SOURCE=.\ConfigChannel.h
# End Source File
# Begin Source File

SOURCE=.\ConfigComm.h
# End Source File
# Begin Source File

SOURCE=.\ConfigNetwork.h
# End Source File
# Begin Source File

SOURCE=.\ConfigPTZ.h
# End Source File
# Begin Source File

SOURCE=.\ConfigRecord.h
# End Source File
# Begin Source File

SOURCE=.\ConfigServer.h
# End Source File
# Begin Source File

SOURCE=.\Define.h
# End Source File
# Begin Source File

SOURCE=.\motiondetect.h
# End Source File
# Begin Source File

SOURCE=.\multilanguage.h
# End Source File
# Begin Source File

SOURCE=.\PeriodTimeSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\PtzLinkDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SysSettingCamera.h
# End Source File
# Begin Source File

SOURCE=.\TimeLineShowWnd.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
