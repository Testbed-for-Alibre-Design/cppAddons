; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=3
Class1=CSampleAddOnApp
LastClass=CDefineAnimationDialog
NewFileInclude2=#include "SampleAddOn.h"
ResourceCount=2
NewFileInclude1=#include "stdafx.h"
Class2=CDefineAnimationDialog
LastTemplate=CDialog
Resource1=IDD_DEFINE_ANIMATION
Class3=CStartAnimationDialog
Resource2=IDD_START_ANIMATION

[CLS:CSampleAddOnApp]
Type=0
HeaderFile=SampleAddOn.h
ImplementationFile=SampleAddOn.cpp
Filter=N
LastObject=CSampleAddOnApp

[DLG:IDD_DEFINE_ANIMATION]
Type=1
Class=CDefineAnimationDialog
ControlCount=4
Control1=IDC_APPLY,button,1342242816
Control2=IDC_FRAMES,edit,1350631424
Control3=IDC_STATIC,static,1342308353
Control4=IDC_STATIC,static,1342308353

[CLS:CDefineAnimationDialog]
Type=0
HeaderFile=CDefineAnimationDialog.h
ImplementationFile=CDefineAnimationDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_APPLY
VirtualFilter=dWC

[DLG:IDD_START_ANIMATION]
Type=1
Class=CStartAnimationDialog
ControlCount=6
Control1=IDC_EXIT,button,1342242816
Control2=IDC_ANIMATE,button,1342242816
Control3=IDC_STATIC,static,1342308353
Control4=IDC_SPEED,edit,1350631424
Control5=IDC_STATIC,static,1342308353
Control6=IDC_STATIC,static,1342308353

[CLS:CStartAnimationDialog]
Type=0
HeaderFile=CStartAnimationDialog.h
ImplementationFile=CStartAnimationDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_ANIMATE
VirtualFilter=dWC

