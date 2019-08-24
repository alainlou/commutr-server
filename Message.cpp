#include "Message.h"

Message::Message(String u, String t, String i) : username(u), text(t), id(i) {}

String Message::toJSON() {
  return "{ \"username\": \"" + username + "\","
        + "\"text\": \"" + text + "\","
        + "\"id\": \"" + id + "\""
        + " }";
}
