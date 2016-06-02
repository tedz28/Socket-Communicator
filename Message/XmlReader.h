#ifndef XMLREADER_H
#define XMLREADER_H
///////////////////////////////////////////////////////////////////////
// XmlReader.h - Parse XML strings                                   //
// ver 2                                                             //
// Language:    Visual C++, Visual Studio 2010, SP1                  //
// platform:    Toshiba Portege R705, Windows 7, Home Premium, SP1   //
// Application: Summer 2011 Projects                                 //
// Author:      Jim Fawcett, Syracuse University, CST 4-187          //
//              www.lcs.syr.edu/faculty/fawcett, (315) 443-3948      //
///////////////////////////////////////////////////////////////////////
/*
 * Note: XmlReader and XmlWriter supercede both XmlTran and XmlParser.
 *
 * Package Operations:
 * ===================
 * This package contains a single class, XmlReader.  It provides a
 * simple interface to step from XML element to element and extract
 * constituent parts, e.g., tag, attributes, and body.  The package
 * does not support editing XML strings.  For that, you should use
 * the XmlDocument package.
 *
 * Exceptions will be thrown by element(), body(), and attributes()
 * if malformed XML is detected.
 *
 * Required Files:
 * ===============
 * XmlReader.h, XmlReader.cpp
 *
 * Build Process:
 * ==============
 * cl /Eha XmlReader.cpp
 *
 * Maintenance History:
 * ====================
 * ver 2 : 27 Jun 11
 * - moved #include<stack> to XmlReader.cpp
 * - moved #include<iostream> to test stub in XmlReader.cpp
 * ver 1 : 26 Jun 11
 * - first release
 */
#include <vector>

class XmlReader
{
public:
  typedef std::vector<std::pair<std::string,std::string>> attribElems;
  XmlReader(const std::string& xml);
  bool next();
  std::string tag();
  attribElems attributes();
  std::string body();
  std::string element();
  std::string extractIdentifier(size_t& pos);
  void reset();
private:
  // source string
  std::string _xml;
  size_t position;
  // current element parts
  std::string _tag;
  attribElems _attributes;
  size_t localposition;
};

inline void XmlReader::reset() { position = 0; }

#endif
