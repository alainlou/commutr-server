#include "Shared.h"

String toJson(vector<String> vec) {
  String response = "{\n\t\"messages\"\t:\t[";
  for (int i = 0; i < vec.size() - 1; ++i) {
    response += "\"" + vec[i] + "\", ";
  }
  response += "\"" + vec[vec.size() - 1] + "\"";
  response += "]}";

  return response;
}

String getMessage(String str) {
  int start = str.indexOf(':');
  String message = "";
  for (int i = start + 1; i < str.length(); ++i) {
    if (str.charAt(i) == '\"')
      break;
    else
      message += str.charAt(i);
  }
  return message;
}

// function to parse through data object
vector<String> getDataMessage(String str) {
  /*
    Data JSON Structure
    {
        "name" : "userName",
        "message": "message",
        "id": "id"
    }
  */
  // replaces ':' with ';'
  // should back up to text file before mutating string
  vector<String> resultMessage;
  for (int index = 0; index < 3; index++) {
    int start = str.indexOf(':');
    String message = "";
    for(int i = start+2; i < str.length(); ++i) {
        if(str.charAt(i) == '\"')
            break;
        else
            message += str.charAt(i);
    }
    return message;
}

// function to parse through data object
Message parseMessage(String str) {
  /*
    Data JSON Structure
    {
        "name" : "userName",
        "message": "message",
        "id": "id"
    }
  */
  // replaces ':' with ';'
  // should back up to text file before mutating string
  vector<String> result;
  for(int i = 0; i < str.length(); ++i) {
    if(str.charAt(i) == ':') {
      String data = "";
      for(int j = i+2; j < str.length(); ++j) {
        if(str.charAt(j) == '\"') {
          i = j;
          result.push_back(data);
          break;
        }
        data += str.charAt(j);
      }
    }
  }
  Message message(result[0], result[1], result[2]);
  return message;
}
