struct Message {
  String user;
  String text;
  String id;

  Message(String u, String t, String i){
    user = u;
    text = t;
    id = i;
  }

  String toString() {
    return user + " " + text + " " + id;
  }

  String toJSON() {
    return "{ \"user\": " + '\"' + user + '\"' + ", "
           + "\"text\": " + '\"' + text + '\"' + ", "
           + "\"id\": " + '\"' + id + '\"' + "}";
  }
};
