#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H
/////////////////////////////////////////////////////////////////////
//  diagnostics.h - Tools to trace                                 //
//  ver 1.0                                                        //
//                                                                 //
//  Language:       Visual C++, ver 7.1, SP 2                      //
//  Platform:       Dell Dimension 8300, Win XP, SP2               //
//  Application:    CSE687 - Object Oriented Design                //
//  Author:         Jim Fawcett, CST 2-187, Syracuse Univ          //
//                  (315) 443-3948, jfawcett@twcny.rr.com          //
//                                                                 //
/////////////////////////////////////////////////////////////////////
/*
   Module Operations:
   ==================
   This module provides a Trace function

   Public Interface:
   =================
   #define TRACE  // normally you define this in C++/preprocessor defs
   Trace("some message");

*/
/*
   Build Process:
   ==============
   Required Files:
     diagnostics.h, diagnostics.cpp, locks.h, locks.cpp

   Compile Command:
   ================
   cl /EHa /DTEST_DIAGNOSTICS

   Maintenance History:
   ====================
   ver 1.0 : 25 Apr 06
   - first release

*/
//

#include "locks.h"

class diagnostics
{
public:
  virtual ~diagnostics() {}
  virtual void ExceptionMsg(
    const std::string& msg, const std::string& title
  );
};

#ifdef TRACE
#include <iostream>
#endif

inline void Trace(const std::string& msg)
{
#ifdef TRACE
  sout << locker << "\n  " << msg.c_str() << unlocker;
  sout.flush();
#endif
#ifdef TRACEMB
  diagnostics().ExceptionMsg(msg,"");
#endif
}

inline void EnterKeyToWait()
{
  sout << locker << "\n  Enter key to quit: ";
  std::cin.get();
  sout << unlocker;
}

#endif
