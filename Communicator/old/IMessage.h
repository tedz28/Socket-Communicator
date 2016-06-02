#ifndef IMESSAGE_H
#define IMESSAGE_H
/////////////////////////////////////////////////////////////////////
// IMessage.h  -  Defines Interfaces for EndPoints and Messages    //
// ver 1.0                                                         //
// Language:      Visual C++, 2008                                 //
// Platform:      Dell Dimension T7400, Win 7 Pro                  //
// Application:   Utility for CSE687 projects                      //
// Author:        Jim Fawcett, Syracuse University, CST 4-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////

#include <string>

struct IEndPoint
{
  static std::string MakeEndPoint(const std::string& ipaddr, long port);
  virtual std::string address()=0;
  virtual long port()=0;
};

struct IMessage
{
  enum MsgType { text, file };
  static IMessage* MakeMessage(const std::string& EndPoint, MsgType type, const std::string& body);
  virtual std::string& getEndPoint()=0;
  virtual MsgType& getMsgType()=0;
  virtual std::string& body()=0;
};

#endif

