#include "Shared.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

string toJson(vector<string> vec) {
    string response = "[";
    for(int i = 0; i < vec.size()-1; ++i) {
        response += vec[i] + ", ";
    }
    response += vec[vec.size()-1];
    response += "]";
    
    return response;
}