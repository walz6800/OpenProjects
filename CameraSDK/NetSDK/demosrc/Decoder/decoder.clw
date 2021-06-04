; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDecoderDlg
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "decoder.h"
LastPage=0

ClassCount=4
Class1=CDecoderApp
Class2=CAboutDlg
Class3=CDecoderDlg

ResourceCount=2
Resource1=IDD_DECODER_DIALOG
Class4=CColorButton
Resource2=IDD_ABOUTBOX (English (U.S.))

[CLS:CDecoderApp]
Type=0
BaseClass=CWinApp
HeaderFile=decoder.h
ImplementationFile=decoder.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=decoderDlg.cpp
ImplementationFile=decoderDlg.cpp

[CLS:CDecoderDlg]
Type=0
BaseClass=CDialog
HeaderFile=decoderDlg.h
ImplementationFile=decoderDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_COMBO_PTZ

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_DECODER_DIALOG]
Type=1
Class=CDecoderDlg
ControlCount=47
Control1=ID_BTN_START,button,1342242817
Control2=ID_BNT_STOP,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_DECODER_IP,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_DECODER_PORT,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_DECODER_USER,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_DECODER_PWD,edit,1350631584
Control11=IDC_STATIC,button,1342177287
Control12=IDC_BTN_LOGIN,button,1342242816
Control13=IDC_BTN_LOGOUT,button,1342242816
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT_ENCODER_IP,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EDIT_ENCODER_PORT,edit,1350631552
Control19=IDC_STATIC,static,1342308352
Control20=IDC_EDIT_ENDCODER_USER,edit,1350631552
Control21=IDC_STATIC,static,1342308352
Control22=IDC_EDIT_ENCODER_PWD,edit,1350631584
Control23=IDC_STATIC,static,1342308352
Control24=IDC_COMBO_DECODER,combobox,1344340226
Control25=IDC_STATIC,static,1342308352
Control26=IDC_COMBO_ENCODER,combobox,1344340226
Control27=IDC_BUTTONLEFTUP,button,1342242816
Control28=IDC_BUTTONLEFTDOWN,button,1342242816
Control29=IDC_BUTTONDOWN,button,1342242816
Control30=IDC_BUTTONUP,button,1342242816
Control31=IDC_BUTTONRIGHTUP,button,1342242816
Control32=IDC_BUTTONRIGHTDOWN,button,1342242816
Control33=IDC_BUTTONRIGHT,button,1342242816
Control34=IDC_BUTTONLEFT,button,1342242816
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,button,1342177287
Control37=IDC_BUTTONTJLEFT,button,1342242816
Control38=IDC_BUTTONGQLETF,button,1342242816
Control39=IDC_BUTTON1JJLEFT,button,1342242816
Control40=IDC_BUTTONTJRIGHT,button,1342242816
Control41=IDC_BUTTONGQRIGHT,button,1342242816
Control42=IDC_BUTTONJJRIGHT,button,1342242816
Control43=IDC_STATIC,static,1342308352
Control44=IDC_STATIC,static,1342308352
Control45=IDC_STATIC,static,1342308352
Control46=IDC_STATIC,static,1342308352
Control47=IDC_COMBO_PTZ,combobox,1344340226

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:CColorButton]
Type=0
HeaderFile=ColorButton.h
ImplementationFile=ColorButton.cpp
BaseClass=CButton
Filter=W

