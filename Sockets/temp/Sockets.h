#ifndef SOCKETS_H
#define SOCKETS_H
/////////////////////////////////////////////////////////////////////
// Sockets.h   -  Provides basic network communication services    //
// ver 1.0                                                         //
// Language:      Visual C++, 2005                                 //
// Platform:      Dell Dimension 9150, Windows XP Pro, SP 2.0      //
// Application:   Utility for CSE687 and CSE775 projects           //
// Author:        Jim Fawcett, Syracuse University, CST 2-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////
/*
   Module Operations:
   ==================
   This module provides network communication services, using 
   WinSock2, a nearly Berkley Sockets compliant implementation
   with extensions.  Three classes are provided:

   SocketSystem:
   -------------
   provides WinSock loading, unloading and a few program wide services.
   A recent change has ensured that the WinSock library is only loaded
   once, no matter how many times you construct SocketSystem objects.
   So now, the Socket class has a SocketSystem instance so you don't
   have to do an explicit creation of a SocketSystem object before
   creating a Socket.

   Socket:
   -------
   Provides connect request, string read, and string write service.
   
   SocketListener:
   ---------------
   Provides connection handling.
   
   Public Interface:
   =================
   SocketSystem sys;                          // load winsock lib
   SocketListener listener(2048);             // create listener
   Socket recvr = listener.waitForConnect();  // start listener listening
   Socket sendr;                              // create sending socket
   sender.connect("\\localhost",2048);        // request a connection
   const char* msg = "this is a message"; 
   sender.send(msg,strlen(msg)+1);            // send terminating null
   sender.send("quit",strlen("quit")+1);      // send another msg

   char* buffer[1024];                        // receive buffer
   recvr.recv(buffer,strlen(msg)+1);          // copy data when available
   std::cout << "\n  recvd: " << buffer;
   recvr.recv(buffer,strlen("quit")+1);       // get more data
   std::cout << "\n  recvd: " << buffer;

   recvr.disconnect();                        // graceful shutdown
   sender.disconnect();                       // graceful shutdown
*/
//
/*
   Build Process:
   ==============
   Required Files:
     Sockets.h, Sockets.cpp

   Compile Command:
   ================
   cl /EHsc /DTEST_SOCKETS Sockets.cpp wsock32.lib user32.lib

   Maintenance History:
   ====================
   This is a major rewrite of an earlier socket demo

   ver 1.0 : 11 Feb 07
   - first release

*/
//
#include <string>
#include <winsock2.h>

/////////////////////////////////////////////////////////////////////
// SocketSystem class loads and unloads WinSock library
// and provides a few system services

class SocketSystem
{
public:
  SocketSystem();
  ~SocketSystem();
  std::string getHostName();
  std::string getNameFromIp(const std::string& ip);
  std::string getIpFromName(const std::string& name);
  std::string GetLastMsg(bool WantSocketMsg=true);

private:
  static bool loaded;
  static int count;
};

/////////////////////////////////////////////////////////////////////
// Socket class provides basic connect, read, and write operations

class Socket
{
public:
  Socket();
  Socket(const std::string& url, int port);
  Socket(SOCKET s);
  ~Socket();
  operator SOCKET ();
  bool connect(std::string url, int port);
  void disconnect();
  bool error() { return (s_ == SOCKET_ERROR); }
  bool send(const char* block, size_t len);
  void recv(char* block, size_t len);
  std::string getRemoteIP();
  int getRemotePort();
  std::string getLocalIP();
  int getLocalPort();

private:
  SOCKET s_;
  SocketSystem ss_;
  std::string terminator_;
};
//
/////////////////////////////////////////////////////////////////////
// SocketListener class waits for connections, then delivers
// connected socket

class SocketListener
{
public:
  SocketListener(int port);
  ~SocketListener();
  Socket waitForConnect();
  void stop();
private:
  SOCKADDR_IN tcpAddr;
  Socket s_;
};

#endif
