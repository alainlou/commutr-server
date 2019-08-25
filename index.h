const char home_page[] PROGMEM = R"=====(
<!-- <!DOCTYPE html> -->
<meta charset="ISO-8859-1"> 
<style>
    ::-webkit-scrollbar {
        width: 5px;
    }

    ::-webkit-scrollbar-track {
        background: #696969;
        border-radius: 10px;
    }

    ::-webkit-scrollbar-thumb {
        background: #555;
        border-radius: 10px;
    }

    ::-webkit-scrollbar-thumb:hover {
        background: #434343;
    }

    body {
        background-color: #000;
        color: #434343;
        font-family: 'Roboto', sans-serif;
        background-size: cover;
    }

    main {
        background-color: #000;
        margin: 20px auto;
        max-width: 350px;
        /* padding: 20px; */
        border-radius: 8px;
        opacity: 0.8;
        color: #ffffff;
    }

    ul {
        background-color: #000;
        /* color: #008f11; */
        /* color: #00bfff; */
        font-family: monaco, Consolas, "Lucida Console", monospace;
        font-size: 18px;
        font-style: normal;
        font-variant: normal;
        font-weight: 400;
        line-height: 30px;
        padding-left: 10px;
        /* padding-top: 10px; */
        list-style: none;
        padding-right: 10px auto;
        overflow-x: hidden;
        /* overflow-y: hidden; */
        height: 480px;
    }

    li {
        padding-right: 20px auto;
        padding-left: -60px auto;
    }

    button {
        border: none;
        height: 75px;
        background-color: #4CAF50;
        text-align: center;
        text-decoration: none;
        border-radius: 4px;
    }

    .container {
        background-color: #434343;
        justify-content: space-between;
        flex-direction: column;
        height: 10px;
        display: flex;
    }

    .container .btn-holder {
        /* justify-content: flex-end; */
        display: flex;
    }

    button:hover {
        background-color: #3E8E41;
    }

    button:active {
        background-color: #3E8E41;
        transform: translateY(4px);
    }

    p {
        margin: 0px auto;
        color: #5fff00;
        font-family: monaco, Consolas, "Lucida Console", monospace;
        font-size: 18px;
        font-style: normal;
        font-variant: normal;
        font-weight: 400;
        line-height: 30px;
    }

    /* .initials {
        opacity: 1;
        font-family: Arial;
    } */

    .history {
        height: 300px;
    }
</style>

<script>
    var id = 0;
    var userName = generateUserName();
    var seen = [];
    var welcomeText = "Welcome to Commutr! Say hi to all the people you're travelling with!"
    var i = 0;
    var speed = 50;

    function setRandomColor() {
        let colors = ["#008f1", "#00bfff", "#af0000", "#af00af", "#afff00", "#d7ff00", "#d7ff00"]
        return colors[Math.floor(Math.random() * colors.length)]
    }

    function typewriter() {
        if (i < welcomeText.length) {
            document.getElementById("welcomeText").innerHTML += welcomeText.charAt(i);
            i++;
            setTimeout(typewriter, speed);
        }
    }

    window.onload = function () {
        typewriter();
    };

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
            seen.push(message.id);
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
<header><meta name='viewport' content='width=device-width, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0'></header>
<main>
    <div style="width: 100%;">
        <p id="welcomeText"></p>
        <ul id="history">
        </ul>
    </div>
    <div class="container" id="messageForm">
        <input id="message" class="message" onkeypress="checkKey(event)" placeholder="Type a message"
            autocomplete="off">
        <button type="button" onclick="chatSent()">Send</button>
    </div>
</main>

</html>

)=====";
