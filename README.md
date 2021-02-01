# WiFiWeatherDisplay
Adapted jconenna's WiFi weather display for my own needs and ported it to the ESP8266. This is basically a complete recode, but I still wanna give him credit for the existing animations. [Original by jconenna](https://github.com/jconenna/WiFiWeatherDisplay) and my [first fork](https://github.com/tomjschwanke/WiFiWeatherDisplayEsp) for the ESP8266
Due to the limitations of the ESP8266 I have now ported it to the ESP32

## Shylily
This branch contains the neccessary code to interface with the Twitch API and I use it to check if [Shylily](https://www.twitch.tv/shylily) is live on Twitch and if she is, a little blinking shrimp is displayed after the humidity.

## What is this?
A WiFi weather station giving you a short animation on the current weather, the temperature and humidity.

## History.
A few years back I saw the video by jconenna where he showed off his WiFi weather station. It was an Arduino communicating with an ESP8266 via Serial. I built it and programmed it, however things didn't work as expected. The serial communication and JSON parsing was prone to errors and timeouts and things weren't made for metric units. That's why I decided to change a lot of stuff. I included negative temperatures etc, but in the end, the serial communication was a major issue. I kinda abandoned it. Recently however, I thought of how cool that thing was and decided I wanted it back. Unfortunately I fried my Arduino, so I decided for a rewrite, only using the ESP8266 and getting rid of a lot of unneccessary features I built in. That had the neat side-effect of solving the serial communications issue entirely and a new JSON library takes care of all the parsing now. Then when I implemented config mode I ran into issues as the ESP8266 wouldn't make reliable HTTP requests anymore as long as I had the WebServer for config mode defined. Because of this I have now switched to an ESP32 and it all works now.

## Features
### API
- Data requested from OpenWeatherMap API (you need your own key)
- Define location and units through config mode
### Weather animations
- clear day / night
- light / moderate / heavy rain
- lightning
- light / moderate / heavy thunderstorm
- moderate / heavy snowfall
- few / scattered / broken clouds
- fog
- if a condition is missing, there will be a blinking X
### Temperature
- -99° to 199°
- Celsius or Farenheit defined in config mode
### Humidity
- 0% to 100% RH
### Automatic dimming
- Dims after sunset (info from OpenWeatherMap API)
### OTA
- Set a hostname and password to update the ESP over WiFi without connecting the USB cable
- has its own neat progress animation (can be a bit laggy, but excuse the chip, its updating itself)
- I will actually change this as OTA is not encrypted when done through the IDE
#### Config mode
 - Easily configure the device after programming: Press reset and then press reset again while the sandclock is being displayed. The device should now be in config mode and can be configured from your phone by joining the "WiFiWeatherDisplay Setup" network with the password "12345678". Input your WiFi credentials and location data and hit apply. The device will save the data and reboot.
### LED indicators
- LED on 27 for indicating a failed request
- LED on 26 for indicating lost connectivity
### Should something fail
- If a request or the WiFi connection fails for whatever reason, it fails and returns to displaying the data it got before. The LED indicators will show the status.
### Requests
- After the display has cycled through all available data, it loads new data (you can change this in the code, though OpenWeatherMap allows up to 60 requests per minute / 1,000,000 per month, I haven't run into any limit yet)

## Parts
- 1 ESP32
- 1 8x8 LED Matrix + MAX7219 controller
- 2 LEDs + resistor
- Some sort of powersupply

## Connections
| ESP32   | Other part            |
|---------|-----------------------|
| GPIO 27 | Failed request LED    |
| GPIO 26 | Lost connectivity LED |
| GPIO 18 | MAX7219 CLK           |
| GPIO 23 | MAX7219 DIN           |
| GPIO 5  | MAX7219 CS            |

Power should be self-explanatory (VCC to 5V, GND to GND)

