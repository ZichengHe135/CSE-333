/*
 * Copyright ©2018 Hal Perkins.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Washington
 * CSE 333 for use solely during Summer Quarter 2018 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <stdint.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <map>
#include <string>
#include <vector>

#include "./HttpRequest.h"
#include "./HttpUtils.h"
#include "./HttpConnection.h"

using std::map;
using std::string;

namespace hw4 {

bool HttpConnection::GetNextRequest(HttpRequest *request) {
  // Use "WrappedRead" to read data into the buffer_
  // instance variable.  Keep reading data until either the
  // connection drops or you see a "\r\n\r\n" that demarcates
  // the end of the request header.
  //
  // Once you've seen the request header, use ParseRequest()
  // to parse the header into the *request argument.
  //
  // Very tricky part:  clients can send back-to-back requests
  // on the same socket.  So, you need to preserve everything
  // after the "\r\n\r\n" in buffer_ for the next time the
  // caller invokes GetNextRequest()!

  // MISSING:
  // check for end of request
  size_t end = buffer_.find("\r\n\r\n");
  if (end == string::npos) {
    int bytes_read;
    unsigned char buf[1024];

    while (1) {
      bytes_read = WrappedRead(fd_, buf, 1024);
      if (bytes_read == 0) {
        break;
      } else if (bytes_read == -1) {
        return false;
      } else {
        buffer_ += string(reinterpret_cast<char *>(buf), bytes_read);
        end = buffer_.find("\r\n\r\n");
        if (end != string::npos) {
          break;
        }
      }
    }
  }
  if (end == string::npos) {
    return false;
  }

  *request = ParseRequest(end + 4);
  if (request->URI == "BAD_") {
    request = NULL;
    return false;
  }
  buffer_ = buffer_.substr(end + 4);
  return true;
}

bool HttpConnection::WriteResponse(const HttpResponse &response) {
  std::string str = response.GenerateResponseString();
  int res = WrappedWrite(fd_,
                         (unsigned char *) str.c_str(),
                         str.length());
  if (res != static_cast<int>(str.length()))
    return false;
  return true;
}

HttpRequest HttpConnection::ParseRequest(size_t end) {
  HttpRequest req;
  req.URI = "/";  // by default, get "/".

  // Get the header.
  std::string str = buffer_.substr(0, end);

  // Split the header into lines.  Extract the URI from the first line
  // and store it in req.URI.  For each additional line beyond the
  // first, extract out the header name and value and store them in
  // req.headers (i.e., req.headers[headername] = headervalue).
  // You should look at HttpResponse.h for details about the HTTP header
  // format that you need to parse.
  //
  // You'll probably want to look up boost functions for (a) splitting
  // a string into lines on a "\r\n" delimiter, (b) trimming
  // whitespace from the end of a string, and (c) converting a string
  // to lowercase.

  // MISSING:
  std::vector<string> lines;
  boost::split(lines, str, boost::is_any_of("\r\n"),
               boost::token_compress_on);
  for (uint32_t i = 0; i < lines.size(); i++) {
    boost::trim(lines[i]);
  }
  std::vector<string> tokens;
  boost::split(tokens, lines[0], boost::is_any_of(" "),
               boost::token_compress_on);
  if (tokens.size() != 1 && tokens[1].find("HTTP") == string::npos) {
    req.URI = tokens[1];
  } else {
    req.URI = "BAD_";
    return req;
  }

  for (int i = 1; i < lines.size(); i++) {
    string now = lines[i];
    std::vector<string> pair;
    if (now.find(": ") == string::npos)
      continue;
    boost::split(pair, now, boost::is_any_of(": "),
                 boost::token_compress_on);
    string hname = pair[0];
    string hvalue = pair[1];
    boost::to_lower(hname);
    req.headers[hname] = hvalue;
  }

  return req;
}

}  // namespace hw4
