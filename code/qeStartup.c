// Copyright (C) 2006 Joe Linhoff, All Rights Reserved
// qeStartup.c -- system startup file for project -- do not modify
// JFL 17 Aug 06
// JFL 24 Nov 06; qe uses Windows entry point
// *** this file is not meant to be modified ***

#include "qe.h" // QE include

// Forward declaration of the entry point function
GP_API int __stdcall qeEntryPointWindows(HINSTANCE hInstance,
   HINSTANCE hPrevInstance,LPSTR lpszCmdLine,int nCmdShow,
   fnc_iip fnc,uns hvers);

// application entry point
// JFL 24 Nov 06
int __stdcall WinMain(HINSTANCE hInst,HINSTANCE hPrev,LPSTR cmdLine,int show)
{
   return qeEntryPointWindows(hInst,hPrev,cmdLine,show,qeMain,QE_H_VERS);
} // WinMain()

// EOF


