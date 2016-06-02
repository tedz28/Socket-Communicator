/////////////////////////////////////////////////////////////////////
// SenderApp.cpp - Demonstrates simple use of SocketCommunicator   //
//                     Sends messages to ReceiverApp               //
// ver 2.1                                                         //
// Language:      Visual C++, 2008                                 //
// Platform:      Dell Dimension T7400, Win 7 Pro                  //
// Application:   Utility for CSE687 projects, Spring 2010         //
// Author:        Jim Fawcett, Syracuse University, CST 4-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////
/*
  Note:
  - This end starts sending then when done starts receiving.
  - Since we are running Sender and Receiver on same thread, we must 
    first do all our sending then do all our receiving.
  - There would be no such constraint if we ran sender and receiver on
    separate threads.
  - That is what you should do in Project #4.

  Maintenance History:
  ====================
  ver 2.1 : 24 Apr 11
  - Added namespace SocketCommunicator to Comm.h and Message.h which
    will allow you to avoid conflicts with the .Net Message type.
    That means you will need to declare "using namespace SocketCommunicator;"
    in some places in your code.
  - Fixed a bug discovered by Jingyi Ren in the Message type handling.
    She provided a solution, and that worked and has been incorporated.
  ver 2.0 : 23 Apr 11
  - Thanks to Amit Ahlawat, Himanshu Gupta, Kajal Kapoor, and Jingyi Ren
    for submitting bug reports.
  - added base64 encoding of message bodies when sending files to
    avoid problems with XML markup characters in the file's text.
  - you may wish to encode all messages to avoid switching back and
    forth (as I did below) when sending files.
  ver 1.1 : 17 Apr 11
  - added retry loop while connecting
  - added a Receiver section to demonstrate two-way communication
  ver 1.0 : 16 Apr 10
  - first release
*/
#include "../Communicator/Comm.h"
#include <iostream>
#include <sstream>
#include <conio.h>
#include <fstream>
#include "../Base64Encoding/Base64.h"

using namespace SocketCommunicator;

template <typename T>
std::string Convert(const T& t)
{
  std::ostringstream temp;
  temp << t;
  return temp.str();
}

void main()
{
  std::cout << "\n  Starting SenderApp";
  std::cout << "\n ====================\n";

  Sender sndr;

  ///////////////////////////////////////////////////////////////
  // - 127.0.0.1 is the loopback address, e.g., this machine.
  //   You can use any valid ip4 address or a network machine
  //   name.
  // - I recommend you use ports at or above 4048 to avoid
  //   conflicts with other applications on your machines.

  Message msg;
  int tryCount = 0, MaxTries = 5;
  std::string ip = "localhost";
  int port = 8000;
  while(++tryCount < MaxTries)
  {
    if(sndr.connect(EndPoint(ip,port)))
      break;
    Sleep(100);
    std::cout << "\n  failed attempt to connect to endpoint(" << ip.c_str() << ", " << port << ")";
  }
  // send 20 test messages

  if(tryCount < MaxTries)
  {
    for(int i=0; i<20; ++i)
    {
      std::string text = "msg #";
      text += Convert(i);
      text += " a message from SenderApp";
      msg.body() = text;
      std::cout << "\n  Posting msg: " << msg.body();
      sndr.PostMsg(msg);
    }
    // Send a file in 1024 byte blocks using base64 encoding
    // Encoding is needed to mask markup characters that may
    // be in a source code file's text.

    msg.body() = "file";
    sndr.PostMsg(msg);
    const int BlockSize = 1024;
    std::ifstream in("SenderApp.cpp");
    while(in.good())
    {
      std::string block;
      for(int i=0; i<BlockSize; ++i)
      {
        if(!in.good())
          break;
        block += in.get();
      }
      std::vector<char> vmsg(block.begin(), block.end());
      std::string msgbody = Base64::encode(vmsg);
      std::cout << "\n  Posting msg: " << block;
      msg.body() = msgbody;
      sndr.PostMsg(msg);
    }

    /////////////////////////////////////////////////////////////
    // done msg shuts down Sender thread after it empties queue
    // quit msg shuts down both the Sender and Receiver threads

    Message msg("quit");
    sndr.PostMsg(msg);
    std::cout << "\n  Posted msg: " << msg.body();

    ////////////////////////////////////////////////
    // don't wait until all thread's work is done
    //   sndr.wait();

    std::cout << "\n\n  Shutting down SenderApp Sender";
  }
  std::cout << "\n\n";
}