#include "Shared.h"

String toJson(vector<String> vec) {
    String response = "[";
    for(int i = 0; i < vec.size()-1; ++i) {
        response += vec[i] + ", ";
    }
    response += vec[vec.size()-1];
    response += "]";
    
    return response;
}