/////////////////////////////////////////////////////////////////////
// Message.cpp  - Defines EndPoints and Messages                   //
// ver 2.0                                                         //
// Language:      Visual C++, 2008                                 //
// Platform:      Dell Dimension T7400, Win 7 Pro                  //
// Application:   Utility for CSE687 projects                      //
// Author:        Jim Fawcett, Syracuse University, CST 4-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////

#include "Message.h"
#include "..\Message\XmlReader.h"
#include "..\Message\XmlWriter.h"
#include <iostream>
#include <sstream>
using namespace SocketCommunicator;

/////////////////////////////////////////////////////////////
// converters to and from string

template <typename T>
std::string ToString(T t)
{
  std::ostringstream temp;
  temp << t;
  return temp.str();
}

template <typename T>
T FromString(const std::string& s)
{
  T t;
  std::istringstream temp(s);
  temp >> t;
  return t;
}
///////////////////////////////////////////////////////////////
// Manage endpoints

EndPoint::EndPoint(const std::string& address, long port)
{
  ep = address + ":" + ::ToString(port); 
}

EndPoint::EndPoint(const std::string& eps) : ep(eps) {}

std::string EndPoint::address()
{
  size_t pos = ep.find(":");
  return ep.substr(0,pos);
}
long EndPoint::port()
{
  size_t pos = ep.find(":");
  std::string pnum = ep.substr(pos+1);
  return FromString<long>(pnum);
}

std::string& EndPoint::ToString()
{
  return ep;
}

//std::string IEndPoint::MakeEndPoint(const std::string& ipaddr, long port)
//{
//  EndPoint ep(ipaddr,port);
//  return ep.ToString();
//}

///////////////////////////////////////////////////////////////
// Build Messages

Message::Message(const std::string& text) 
       : body_(text), returnAddr_(EndPoint("127.0.0.1",8000)), type_(Message::text) {}

Message::Message(const std::string& body, EndPoint returnAddr, MsgType type)
       : body_(body), returnAddr_(returnAddr), type_(type) {}

Message::Message(const Message& msg) 
       : body_(msg.body_), returnAddr_(msg.returnAddr_), type_(msg.type_) {}

std::string& Message::body() { return body_; }
  
EndPoint& Message::returnAddress() { return returnAddr_; }
  
Message::MsgType& Message::getMsgType() { return type_; }

std::string& Message::getEndPoint() { return returnAddr_.ToString(); }

//----< return string form of Message type >-----------------------------

std::string Message::TypeToString()
{
  switch(type_)
  {
  case text:
    return "text";
  case file:
    return "file";
  }
  return "unknown type";
}
//----< serialize message to string >------------------------------------

std::string Message::ToString()
{
  XmlWriter wrt, bwrt;
  wrt.start("msg")
    .addBody(bwrt
      .element("type",TypeToString())
      .element("rAddress",returnAddress().ToString())
      .element("body",body()).xml()
      ).end();
  return wrt.xml();
}
//----< remove quotes from quoted string >-------------------------------

std::string Message::trimQuotes(const std::string& s)
{
  if(s.size() > 0 && s[0] == '"')
    return s.substr(1,s.size()-2);
  if(s.size() > 0 && s[0] == '\'')
    return s.substr(1,s.size()-2);
  return s;
}
//----< deserialize message string into Message instance >---------------

Message Message::FromString(const std::string& xml)
{
  Message msg("");
  XmlReader rdr(xml);
  while(rdr.next())
  {
    std::string tag = rdr.tag();
    if(tag == "type")
    {
      if(rdr.body() =="\"text\"")
        msg.getMsgType() = Message::text;
      else
        msg.getMsgType() = Message::file;
    }
    else if(tag == "rAddress")
    {
      msg.returnAddress() = EndPoint(rdr.body());
    }
    else if(tag == "body")
    {
      msg.body() = trimQuotes(rdr.body());
    }
  }
  return msg;
}

//IMessage* IMessage::MakeMessage(const std::string& EndPoint, MsgType type, const std::string& body)
//{
//  return new Message(body, EndPoint, type);
//}

EndPoint testEndPoint()
{
  EndPoint ep("127.0.0.1", 8000);
  std::cout << "\n  EndPoint = " << ep.ToString();
  std::cout << "\n  Address  = " << ep.address();
  std::cout << "\n  Port     = " << ep.port();
  return ep;
}

Message testMessage(EndPoint ep)
{
  Message msg("This is a message", ep, Message::text);
  std::cout << "\n  Message body = " << msg.body();
  std::cout << "\n  Message return address = " << msg.returnAddress().ToString();
  std::cout << "\n  Message type = " << msg.TypeToString();
  std::cout << "\n";
  std::cout << "\n  Message:";
  std::cout << "\n  " << msg.ToString();
  return msg;
}

void testMessage(Message& msg)
{
  std::cout << "\n  Message body = " << msg.body();
  std::cout << "\n  Message return address = " << msg.returnAddress().ToString();
  std::cout << "\n  Message type = " << msg.TypeToString();
  std::cout << "\n";
}
//----< test stub >------------------------------------------------------

#ifdef TEST_MESSAGE

void main()
{
  std::cout << "\n  Demonstrating EndPoint and Message Operations";
  std::cout << "\n ===============================================\n";

  EndPoint ep = testEndPoint();
  std::cout << "\n";

  Message msg = testMessage(ep);
  std::cout << std::endl;

  Message msg2("// this is a C++ comment");
  msg2.getMsgType() = Message::MsgType::file;
  std::cout << "\n  " << msg2.ToString();
  testMessage(msg2);

  Message msg3("/* this is a C comment */");
  msg3.getMsgType() = Message::MsgType::text;
  std::cout << "\n  " << msg3.ToString();
  testMessage(msg3);

  Message msg4("std::cout << \"a string\"");
  std::cout << "\n  " << msg4.ToString();
  testMessage(msg4);

  std::cout << "\n\n";
}

#endif
