# Microsoft Developer Studio Project File - Name="libwasabi" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libwasabi - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libwasabi.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libwasabi.mak" CFG="libwasabi - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libwasabi - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libwasabi - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libwasabi - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../clipx" /I "src" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Yu"precomp.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libwasabi - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../clipx" /I "src" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Yu"precomp.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "libwasabi - Win32 Release"
# Name "libwasabi - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "system"

# PROP Default_Filter ""
# Begin Group "memory"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\bfc\foreach.cpp
# End Source File
# Begin Source File

SOURCE=.\src\bfc\memblock.cpp
# End Source File
# Begin Source File

SOURCE=.\src\bfc\ptrlist.cpp
# End Source File
# End Group
# Begin Group "parse"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\parse\pathparse.cpp
# End Source File
# End Group
# Begin Group "string"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\bfc\string\encodedstr.cpp
# End Source File
# Begin Source File

SOURCE=.\src\bfc\string\string.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\bfc\assert.cpp
# End Source File
# Begin Source File

SOURCE=.\src\bfc\guid.cpp
# End Source File
# Begin Source File

SOURCE=.\src\bfc\nsguid.cpp
# End Source File
# Begin Source File

SOURCE=.\src\bfc\std.cpp
# End Source File
# Begin Source File

SOURCE=.\src\bfc\std_mem.cpp
# End Source File
# Begin Source File

SOURCE=.\src\bfc\std_string.cpp
# End Source File
# End Group
# Begin Group "api"

# PROP Default_Filter ""
# Begin Group "service"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\api\service\waservicefactoryx.cpp
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\src\precomp.cpp
# ADD CPP /Yc"precomp.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\src\precomp.h
# End Source File
# End Group
# End Target
# End Project
