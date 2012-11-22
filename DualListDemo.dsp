# Microsoft Developer Studio Project File - Name="DualListDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DualListDemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DualListDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DualListDemo.mak" CFG="DualListDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DualListDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "DualListDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "Perforce Project"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DualListDemo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /Oicf /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "DualListDemo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DualListDemo - Win32 Release"
# Name "DualListDemo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BankJiaoyi.cpp
# End Source File
# Begin Source File

SOURCE=.\BeijingIntroDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BitmapPicture.cpp
# End Source File
# Begin Source File

SOURCE=.\BossComeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=.\BuyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Curvefit.cpp
# End Source File
# Begin Source File

SOURCE=.\Digistring.cpp
# End Source File
# Begin Source File

SOURCE=.\DualListDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\DualListDemo.rc
# End Source File
# Begin Source File

SOURCE=.\DualListDemoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\EnterBank.cpp
# End Source File
# Begin Source File

SOURCE=.\Hispital.cpp
# End Source File
# Begin Source File

SOURCE=.\HouseDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\ListCtrlSortClass.cpp
# End Source File
# Begin Source File

SOURCE=.\NetworkClub.cpp
# End Source File
# Begin Source File

SOURCE=.\NewsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PostMoneyDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ReplayLoad.cpp
# End Source File
# Begin Source File

SOURCE=.\RichTop10.cpp
# End Source File
# Begin Source File

SOURCE=.\RijiDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SellDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetUpGame.cpp
# End Source File
# Begin Source File

SOURCE=.\ShengmingDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticCounter.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StoryDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Ticker.cpp
# End Source File
# Begin Source File

SOURCE=.\TipDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\TopPlayerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Wangba.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\BankJiaoyi.h
# End Source File
# Begin Source File

SOURCE=.\BeijingIntroDlg.h
# End Source File
# Begin Source File

SOURCE=.\BossComeDlg.h
# End Source File
# Begin Source File

SOURCE=.\BuyDlg.h
# End Source File
# Begin Source File

SOURCE=.\DualListDemo.h
# End Source File
# Begin Source File

SOURCE=.\DualListDemoDlg.h
# End Source File
# Begin Source File

SOURCE=.\EnterBank.h
# End Source File
# Begin Source File

SOURCE=.\Hispital.h
# End Source File
# Begin Source File

SOURCE=.\HouseDlg.h
# End Source File
# Begin Source File

SOURCE=.\ListCtrlSortClass.h
# End Source File
# Begin Source File

SOURCE=.\NetworkClub.h
# End Source File
# Begin Source File

SOURCE=.\NewsDlg.h
# End Source File
# Begin Source File

SOURCE=.\PostMoneyDlg.h
# End Source File
# Begin Source File

SOURCE=.\ReplayLoad.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RichTop10.h
# End Source File
# Begin Source File

SOURCE=.\RijiDlg.h
# End Source File
# Begin Source File

SOURCE=.\SelectionDlg.h
# End Source File
# Begin Source File

SOURCE=.\SetUpGame.h
# End Source File
# Begin Source File

SOURCE=.\ShengmingDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StoryDlg.h
# End Source File
# Begin Source File

SOURCE=.\TopPlayerDlg.h
# End Source File
# Begin Source File

SOURCE=.\Wangba.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\32x32x256_Hand.ico
# End Source File
# Begin Source File

SOURCE=.\res\32x32x256_Lamp.ico
# End Source File
# Begin Source File

SOURCE=.\res\bg.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cover.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DualListDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\DualListDemo.rc2
# End Source File
# Begin Source File

SOURCE=.\email.bmp
# End Source File
# Begin Source File

SOURCE=.\res\game1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\hand3.ico
# End Source File
# Begin Source File

SOURCE=.\res\hand4.ico
# End Source File
# Begin Source File

SOURCE=.\res\hand5.ico
# End Source File
# Begin Source File

SOURCE=.\res\hand6.ico
# End Source File
# Begin Source File

SOURCE=.\res\hand7.ico
# End Source File
# Begin Source File

SOURCE=.\res\hand8.ico
# End Source File
# Begin Source File

SOURCE=.\res\hand9.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\litebulb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mid1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mid2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mid3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mid4.bmp
# End Source File
# Begin Source File

SOURCE=.\news.bmp
# End Source File
# Begin Source File

SOURCE=.\riji.bmp
# End Source File
# Begin Source File

SOURCE=.\res\subway.bmp
# End Source File
# Begin Source File

SOURCE=.\res\tickerbkg2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TickerDragBar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\top1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\top2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\top3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\top4.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\html_source.html.htm
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
