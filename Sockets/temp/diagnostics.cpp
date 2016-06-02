/////////////////////////////////////////////////////////////////////
//  diagnostics.cpp - Tools to trace                               //
//  ver 1.0                                                        //
//                                                                 //
//  Language:       Visual C++, ver 7.1, SP 2                      //
//  Platform:       Dell Dimension 8300, Win XP, SP2               //
//  Application:    CSE687 - Object Oriented Design                //
//  Author:         Jim Fawcett, CST 2-187, Syracuse Univ          //
//                  (315) 443-3948, jfawcett@twcny.rr.com          //
//                                                                 //
/////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "diagnostics.h"

void diagnostics::ExceptionMsg(
       const std::string& msg, 
       const std::string& title
     )
{
  MessageBoxA(0, msg.c_str(), title.c_str(), MB_OK);
}

#ifdef TEST_DIAGNOSTICS

void main()
{
  Trace("  Testing Diagnostics Module");
  Trace(" ============================\n");

  diagnostics().ExceptionMsg("test message","diagnostics::ExceptionMsg");
  Trace("\n\n");
}

#endif
