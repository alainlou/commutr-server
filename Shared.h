#ifndef Shared_h
#define Shared_h

#include <WString.h>
#include <vector>

#include "Message.h"

using std::vector;

String toJson(vector<Message> vec);
String getMessage(String str);
Message parseMessage(String str);

#endif
