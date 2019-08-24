const char home_page[] PROGMEM = R"=====(
<style>
body {
  background-color: #000000;
  color: #ffffff;
  font-family: 'Roboto', sans-serif;
  margin: 20px;
  padding-top: 40px;
  background-size: cover;
  background-repeat: repeat-y;
}

main {
  background-color: #434343;
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
  font-family: 'courier', Arial, sans-serif;
  margin: 10px auto;
  list-style: none;
  padding-right: 10px auto;
  overflow-x:hidden;
  overflow-y:visible;
  height:230px;
}

li {
  padding-right: 20px auto;
  padding-left: -60px auto;
}

li:nth-child(odd){
  color: #A4A4A4;
}

ol {
  background-color: #434343;
  color: #f0f0f0;
  font-family: 'courier', Arial, sans-serif;
  margin: 00px auto;
  list-style: none;
}

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

.message {
  opacity: 1;
  font-family: 'courier', Arial;
}

.initials {
  opacity: 1;
  font-family: 'courier', Arial;
}

.history {
  height: 200px;
}
</style>

<!DOCTYPE html>
<link rel="stylesheet" href="style.css">

<main>
  <div style="width:420px;height:250px;line-height:1.6em; overflow-y: scroll; padding:0px;">
    <ul id="history">
    </ul>
  </div>
    <form method= id="messageForm" onsubmit="return false">
      <!-- <input id="initials" class="initials" maxlength="3" placeholder="Initials"> -->
      <input id="message" class="message" placeholder="Message">
      <button type="button" onclick="chatSent()">Send</button>
    </form>
</main>
<!-- <script src="app.js"></script> -->
<!-- <script src="https://code.jquery.com/jquery-3.1.1.js"></script> -->
<script>
  var userName = generateUserName();

  // $('#messageForm').submit(function () {
  //     chatSent();
  //     return false;
  //   });

  function chatSent() {
    var text = document.getElementById('message').value
    var message = userName + ": " + text
    var data = {
      name: userName,
      message: text
    }
    console.log(message, data)
    updateMessage(message)
    document.getElementById('message').value = ''
    // return false
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

  function updateMessage(name, id, message) {
    var xhr = new XMLHttpRequest();
    xhr.open('POST', 'commutr.com/messages');
    xhr.send(JSON.stringify({
      "name"    : name,
      "id"      : id,
      "message" : message
    }));
    var textBox = document.getElementById('history');
    var message = document.createTextNode(message);
    textBox.appendChild(message);
    textBox.scrollTop = textBox.scrollHeight
  }

  function getMessages() {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', 'commutr.com/messages');
    xhr.send();
  }

</script>

</html>
)=====";