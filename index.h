const char home_page[] PROGMEM = R"=====(
<meta charset="ISO-8859-1"> 

<style>
body {
  background-color: white;
  color: #ffffff;
  font-family: 'Roboto', sans-serif;
  margin: 20px;
  padding-top: 40px;
  background-size: cover;
  background-repeat: repeat-y;
}

main {
  background-color: white;
  margin: 20px auto;
  max-width: 450px;
  padding: 20px;
  border-radius: 8px;
  opacity: 0.8;
  color: #ffffff;
}

ul {
  background-color: #434343;
  color: #f0f0f0;
  font-family: Arial, sans-serif;
  margin: 10px auto;
  list-style: none;
  padding-right: 10px auto;
  overflow-x: hidden;
  overflow-y: visible;
  height:230px;
}

li {
  padding-right: 20px auto;
  padding-left: -60px auto;
}

li:nth-child(odd){
  color: #A4A4A4;
}

/* ol {
  background-color: #434343;
  color: #f0f0f0;
  font-family: 'courier', Arial, sans-serif;
  margin: 00px auto;
  list-style: none;
} */

h1 {
  margin: 0px auto;
  text-align: center;
  color: #ffffff;
  font-family: "Lucida Console", Monaco, monospace;
}

form {
  background-color: #434343;
  color: #ffffff;
  opacity: 1;
}

button {
  border: none;
  flex: 0 2 100px;
  height: 2.5rem;
  background-color:#4CAF50;
  padding: 1em 2em;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  box-shadow: 0 0.5rem #999;
}

button:hover {
  background-color: #3E8E41;
}

button:active {
  background-color: #3E8E41;
  box-shadow: 0 5px #666;
  transform: translateY(4px);
}


.initials {
  opacity: 1;
  font-family: Arial;
}

.history {
  height: 200px;
}
</style>

<script>
  var id = 0;
  var userName = generateUserName();
  var history = [];

  function checkKey(e) {
    if(e.keyCode == 13)
      chatSent();
  }

  function uuid() {
    return 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function(c) {
      var r = Math.random() * 16 | 0, v = c == 'x' ? r : (r & 0x3 | 0x8);
      return v.toString(16);
    });
  }

  function chatSent() {
    var text = document.getElementById('message').value
    document.getElementById('message').value = ''
    var message = userName + ": " + text
    var textBox = document.getElementById('history');
    var new_message = document.createElement("LI");
    new_message.innerHTML = message;
    textBox.appendChild(new_message);
    textBox.scrollTop = textBox.scrollHeight;
    updateMessage(userName, text, "0")
  }

  function generateUserName() {
    const adjs = ["autumn", "hidden", "bitter", "misty", "silent", "empty", "dry", "dark", "summer", "icy", "delicate", "quiet", "white", "cool", "spring", "winter", "patient", "twilight", "dawn", "crimson", "wispy", "weathered", "blue", "billowing", "broken", "cold", "damp", "falling", "frosty", "green", "long", "late", "lingering", "bold", "little", "morning", "muddy", "old", "red", "rough", "still", "small", "sparkling", "throbbing", "shy", "wandering", "withered", "wild", "black", "young", "holy", "solitary", "fragrant", "aged", "snowy", "proud", "floral", "restless", "divine", "polished", "ancient", "purple", "lively", "nameless"];
    const nouns = ["waterfall", "river", "breeze", "moon", "rain", "wind", "sea", "morning", "snow", "lake", "sunset", "pine", "shadow", "leaf", "dawn", "glitter", "forest", "hill", "cloud", "meadow", "sun", "glade", "bird", "brook", "butterfly", "bush", "dew", "dust", "field", "fire", "flower", "firefly", "feather", "grass", "haze", "mountain", "night", "pond", "darkness", "snowflake", "silence", "sound", "sky", "shape", "surf", "thunder", "violet", "water", "wildflower", "wave", "water", "resonance", "sun", "wood", "dream", "cherry", "tree", "fog", "frost", "voice", "paper", "frog", "smoke", "star"];
    return (
      adjs[Math.floor(Math.random() * adjs.length)] +
      "_" +
      nouns[Math.floor(Math.random() * nouns.length)]
    );
  }

  function updateMessage(name, text) {
    var xhr = new XMLHttpRequest();
    xhr.open('POST', '/messages');
    var new_id = uuid();
    history.push(new_id);
    xhr.send(JSON.stringify({
      "name"    : name,
      "message" : text,
      "id"      : new_id
    }));
  }

  function getMessages() {
    console.log("getMessages() was called");
    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
      if(this.readyState == XMLHttpRequest.DONE && this.status == 200) {
        var textBox = document.getElementById('history');
        let res = JSON.parse(this.response);
        console.log(res.messages);
        for(let message of res.messages) {
          if(!seen.includes(message.id)) {
            var new_message = document.createElement("LI");
            new_message.innerHTML = message.username + ": " + message.text;
            textBox.appendChild(new_message);
            textBox.scrollTop = textBox.scrollHeight;
          }
        }
      }
    }
    xhr.open('GET', '/messages');
    xhr.send();
    setTimeout(getMessages, 2000);
  }
  
  getMessages();
</script>

<!DOCTYPE html>
<main>
  <div style="width: 100%;">
    <ul id="history">
    </ul>
  </div>
  <div class="flex-container" id="messageForm">
    <input style="flex: 1 1 200px; height: 3em;" id="message" class="message" onkeypress="checkKey(event)" placeholder="Message">
    <button type="button" onclick="chatSent()">Send</button>
  </form>
</main>

</html>

)=====";
