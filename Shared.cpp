#include "Shared.h"

String toJson(vector<String> vec) {
    String response = "{\n\t\"messages\"\t:\t[";
    for(int i = 0; i < vec.size()-1; ++i) {
        response += "\"" + vec[i] + "\", ";
    }
    response += "\"" + vec[vec.size()-1] + "\"";
    response += "]}";
    
    return response;
}

String getMessage(String str) {
    int start = str.indexOf(':');
    String message = "";
    for(int i = start+1; i < str.length(); ++i) {
        if(str.charAt(i) == '\"')
            break;
        else
            message += str.charAt(i);
    }
    return message;
}