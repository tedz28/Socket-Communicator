# Socket-Communicator
Provides simple socket Sender and Receiver classes to easily implement text-based message passing.
1.	Uses message framing via markup
2.	 Defines Message that has properties:
  a.	Type (text, file)
  b.	returnAddress (ip:port)
  c.	text body
3.	Can send chunked binary by using base64 conversion
  a.	Not implemented but …
  b.	Base64 facility in course code folder
  c.	Need to collect all chunks and write to file before notifying receiver
