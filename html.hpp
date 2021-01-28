const char configHtml[] = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width">
    <title>WiFiWeatherDisplay Setup</title>
    <style>
      body {
        background-color: #121212;
        color: white;
        font-family: monospace;
        font-size: large;
      }
      input, button {
        background-color: #242424;
        color: white;
        border: none;
        width: 100%;
        padding: 12px 20px;
        margin: 8px 0;
        box-sizing: border-box;
        font-family: monospace;
        font-size: large;
      }
      input[type=radio], input[type=checkbox] {
        width: 50%;
      }
      input[type=submit], input[type=reset], button {
        transition: 0.5s;
      }
      input[type=submit]:hover {
        background-color: #03e9f4;
      }
      input[type=submit]:focus {
        background-color: #01787e;
      }
      #factoryresetbutton:hover {
        background-color: red;
      }
      #factoryresetbutton:focus {
        background-color: maroon;
      }
      @media screen and (min-width: 800px) {
        .config-box {
          margin: auto;
          width: 70%;
        }
        input {
          width: 100%;
        }
        input[type=radio], input[type=checkbox] {
        width: 50%;
        }
      }
    </style>
  </head>
  <body>
      <div class="config-box">
        <h2>WiFiWeatherDisplay configuration</h2>
        <form action="/configure" method="post" autocomplete="off" enctype="text/plain">

          <label for="ssids">WiFi SSID:</label><br>
          <input list="ssids" name="ssid" maxlength="32" required>
          <datalist id="ssids">)=====";
            /*
            <option value="IoT-net">
            <option value="Schwanke!Box 7590 WW">
            <option value="5G Corona Tower">
            <option value="wbgwlan">
            <option value="BND mobileBase #69">
            */
const char configHtml2[] = R"=====(
          </datalist><br>

          <label for="pass">WiFi Password:</label><br>
          <input type="password" id="pass" name="pass" minlength="8" maxlength="63" required><br>

          <label for="devicename">Device name:</label><br>
          <input type="text" id="devicename" name="devicename" maxlength="32"><br>

          <label for="location">Location (City [, State, Country]):</label><br>
          <input type="text" id="location" name="location" maxlength="32" required><br>

          <input type="radio" id="metric" name="units" value="metric" checked>
          <label for="metric">Metric</label><br>
          <input type="radio" id="imperial" name="units" value="imperial">
          <label for="imperial">Imperial</label><br>

          <input type="checkbox" id="lead0" name="leadzero" value="true" checked>
          <label for="leadzero"> Leading zero</label><br>

          <input type="submit" value="Save & Apply"><br>
          <input type="reset" value ="Clear" onclick="setTimeout(function(){document.getElementById('resetbutton').blur();},350);" id="resetbutton"><br>
        </form>
        <button class="factorybutton" id="factoryresetbutton">FACTORY RESET</button>
    </div>
    <div class="loader"></div>
  </body>
</html>
)=====";

const char successHtml[] = R"=====(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width">
    <title>WiFiWeatherDisplay Setup</title>
    <style>
      body {
        background-color: #121212;
        color: white;
        font-family: monospace;
        font-size: large;
        text-align: center;
      }
    </style>
  </head>
  <body>
    <h1>Success, device will reboot</h1>
  </body>
</html>
)=====";
