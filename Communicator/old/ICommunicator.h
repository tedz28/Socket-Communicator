// ICommunicator.h


struct IMessage
{
  std::string& body()=0;
  IEndPoint
}
struct ICommunicator
{
  static void CreateComm(long port);
  PostMsg(Message msg)=0;
  Message GetMsg()=0;
};
