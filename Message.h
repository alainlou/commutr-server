#ifndef Message_h
#define Message_h

#include <WString.h>

struct Message {
  String username;
  String text;
  String id;

  Message(String u, String t, String i);
  String toJSON();
};

#endif
