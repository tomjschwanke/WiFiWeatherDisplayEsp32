// Look into settings.hpp!

#include "frames.hpp"
#include "settings.hpp"
#include "certificates.hpp"
#include "configLITTLEFS.hpp"
#include "credentials.hpp"
#include "html.hpp"
#include <LedController.hpp>
#include <LinkedList.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <FS.h>
#include <LITTLEFS.h>

#define CS        5
#define Segments  1

#define LED_CONN  26 // Red
#define LED_WARN  27 // Yellow

// For config mode
IPAddress configIp(192, 168, 4, 1);
DNSServer dnsServer;
WebServer server(80);

// For HTTP(S) requests
WiFiClientSecure client;
HTTPClient http;

LedController lc = LedController();

// Variables
int weatherId       = 0;
float currentTemp   = 0;
int humidity        = 0;
long currentTime    = 0;
long sunrise        = 0;
long sunset         = 0;
bool dataIsFresh    = false;
bool started        = false;

bool configMode;

char wifiScan[64][33];
int  wifiNr = 0;

LinkedList<uint8_t> buffer = LinkedList<uint8_t>();

void setup() {
  WiFi.disconnect();
  Serial.begin(115200);
  
  if(!LITTLEFS.begin()) {
    Serial.println("[FS] FS mount failed!");
    delay(1000);
    Serial.println("[FS] Formatting FS...");
    if(!LITTLEFS.format()) {
      Serial.println("[FS] Formatting failed!");
    }else {
      touchFile(PATH_FORMATTED);
    }
    delay(3500);
    ESP.restart();
  }
  if(!LITTLEFS.exists(PATH_FORMATTED)) {
    Serial.println("[FS] Formatting FS...");
    LITTLEFS.format();
    touchFile(PATH_FORMATTED);
  }

  configMode = LITTLEFS.exists(PATH_RESETFLAG);

  // Setup 8x8 matrix
  lc.init(CS, Segments);
  lc.setIntensity(0);

  if(configMode) {
    // We are in config mode
    LITTLEFS.remove(PATH_RESETFLAG);
    setupConfigMode();
    
  }else {
    // We are not in config mode
    
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(true);
    WiFi.setHostname(getDevicename().c_str());

    // Write flag to detect if config mode
    touchFile(PATH_RESETFLAG);
    displayImage(sandclock);
    delay(1000);
    LITTLEFS.remove(PATH_RESETFLAG);

    readFileConfig();

    Serial.printf("[Info] Devicename: %s\n\r", devicename.c_str());
    
    // Init LEDs
    pinMode(LED_CONN, OUTPUT);    // Red
    pinMode(LED_WARN, OUTPUT);    // Yellow

    // Prefill cloud buffer
    for (int i = 0; i < 8; i++)
      buffer.add(empty);

    setupWiFi();

    setupOta();

    int timeout = 0;
    while (!dataIsFresh) {
      requestData();
      if (dataIsFresh) {
        break;
      }
      for (int i = 0; i < 7; i++) {
        displayImage(reqData[i]);
        newDelay(50);
      }
      if (timeout > 100) {
        ESP.restart();
      }
      timeout++;
    }
    started = true;
  }
}

void loop() {
  if(configMode) {
    // We are in config mode
    loopConfigMode();
  }else {
    // We are not in config mode, main loop
    displayAnimation(weatherId);
    displayTemp(currentTemp);
    newDelay(5000);
    displayImage(HU);
    newDelay(2000);
    displayHumidity(humidity);
    newDelay(5000);
    requestData();
  }
}

void newDelay(unsigned long ms) {
  unsigned long currmillis = millis();
  unsigned long timeFuture = currmillis + ms;
  while (currmillis < timeFuture) {
    currmillis = millis();
    // Task that should be done while Arduino is idling
    if (started == true) {
      wifiLed();
      adjustBrightness();
      ArduinoOTA.handle();
    }
    delay(0);
  }
}

void wifiLed() {
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(LED_CONN, LOW);
  } else {
    digitalWrite(LED_CONN, HIGH);
  }
}

void adjustBrightness() {
  if ((currentTime >= sunrise) && (currentTime <= sunset))
    lc.setIntensity(2);
  else
    lc.setIntensity(0);
}

void displayTemp(int temp) {
  if (temp < 100 && temp > -1)
    displayUnderHundred(temp);
  else if (temp < 0 && temp > -10)
    displayNegative(temp);
  else
    displayOverHundred(temp);
}

void displayNegative(int temp) {
  temp = -temp;
  lc.setRow(0, 0, 0b00001000);
  lc.setRow(0, 1, 0b00001000);
  lc.setRow(0, 2, 0b00001000);
  lc.setRow(0, 3, 0b00000000);

  for (unsigned int i = 0; i < 3 ; i++)
    lc.setRow(0, i + 4, numUnderHundred[temp][i]);

  lc.setRow(0, 7, 0b00000001);
}

void displayUnderHundred(int temp) {
  if (temp < 10) {
    if(leadingZero) {
      for(unsigned int i = 0; i < 3; i++) {
        lc.setRow(0, i, numUnderHundred[0][i]);
      }
    }else {
      for(unsigned int i = 0; i < 3; i++) {
        lc.setRow(0, i, 0b00000000);
      }
    }
  }else {
    for (unsigned int i = 0; i < 3 ; i++) {
      lc.setRow(0, i, numUnderHundred[temp / 10][i]);
    }
  }
    
  lc.setRow(0, 3, 0b00000000);

  for (unsigned int i = 0; i < 3 ; i++) {
    lc.setRow(0, i + 4, numUnderHundred[temp % 10][i]);
  }

  lc.setRow(0, 7, 0b00000001);
}

void displayOverHundred(int temp) {
  if (temp < 110)
    for (unsigned int i = 0; i < 5 ; i++)
      lc.setRow(0, i, hundredOnes[i]);
  else
    for (unsigned int i = 0; i < 5 ; i++)
      lc.setRow(0, i, hundredTeens[i]);
  for (unsigned int i = 0; i < 3 ; i++)
    lc.setRow(0, i + 5, numOverHundred[temp % 10][i]);
}

void displayAnimation(int code) {

  switch (code) {
    case 200:
    case 230:
    case 231:
    case 232:
      displayThunderstormRainLight();
      break;
    case 201:
      displayThunderstormRainModerate();
      break;
    case 202:
      displayThunderstormRainHeavy();
      break;
    case 210:
    case 211:
    case 212:
    case 221:
      displayLightning();
      break;
    case 300:
    case 301:
    case 302:
    case 310:
    case 311:
    case 312:
    case 313:
    case 314:
    case 321:
    case 500:
    case 520:
      displayRainLight();
      break;
    case 501:
    case 521:
      displayRainModerate();
      break;
    case 502:
    case 503:
    case 504:
    case 511:
    case 522:
    case 531:
    case 771:
      displayRainHeavy();
      break;
    case 801:
      cloudDriver(fewClouds);
      break;
    case 802:
      cloudDriver(scatteredClouds);
      break;
    case 803:
    case 804:
      cloudDriver(brokenClouds);
      break;
    case 600:
    case 601:
    case 611:
    case 612:
    case 613:
    case 615:
    case 616:
    case 620:
    case 621:
      displaySnowfall();
      break;
    case 602:
    case 622:
      displaySnowfallHeavy();
      break;
    case 701:
    case 711:
    case 721:
    case 731:
    case 741:
    case 751:
    case 761:
    case 762:
      cloudDriver(fog);
      break;
    case 800:
      dayOrNight();
      break;
    default:
      displayNotFound();
      break;
  }
  // TODO: tornado
}

void displayThunderstormRainLight() {
  for (unsigned int i = 0; i < 3; i++) {
    for (unsigned int j = 0; j < 3; j++) {
      displayImage(moderateRain[j]);
      newDelay(400);
    }

    for (unsigned int j = 0; j < 2; j++)
      for (unsigned int k = 1; k < 3; k++) {
        displayImage(lightning[k]);
        if (k == 1)
          newDelay(200);
        else
          newDelay(30);
      }
  }
}

void displayThunderstormRainModerate() {
  for (unsigned int i = 0; i < 4; i++) {
    for (unsigned int j = 0; j < 4; j++)
      for (unsigned int k = 0; k < 3; k++) {
        displayImage(moderateRain[k]);
        newDelay(100);
      }

    for (unsigned int j = 0; j < 2; j++)
      for (unsigned int k = 1; k < 3; k++) {
        displayImage(lightning[k]);
        if (k == 1)
          newDelay(200);
        else
          newDelay(30);
      }
  }
}

void displayThunderstormRainHeavy() {
  for (unsigned int i = 0; i < 4; i++) {
    for (unsigned int j = 0; j < 4; j++)
      for (unsigned int k = 0; k < 3; k++) {
        displayImage(heavyRain[k]);
        newDelay(100);
      }

    for (unsigned int j = 0; j < 2; j++)
      for (unsigned int k = 1; k < 3; k++) {
        displayImage(lightning[k]);
        if (k == 1)
          newDelay(200);
        else
          newDelay(30);
      }
  }
}

void displayLightning() {
  for (unsigned int i = 0; i < 4; i++) {
    for (unsigned int j = 0; j < 3; j++) {
      displayImage(lightning[j]);
      if (j == 0)
        newDelay(700);
      else if (j == 1)
        newDelay(200);
      else
        newDelay(30);
    }

    for (unsigned int j = 1; j < 3; j++) {
      displayImage(lightning[j]);
      if (j == 1)
        newDelay(200);
      else
        newDelay(30);
    }
  }
}

void displayRainLight() {
  for (unsigned int i = 0; i < 5; i++)
    for (unsigned int j = 0; j < 3; j++) {
      displayImage(moderateRain[j]);
      newDelay(400);
    }
}

void displayRainModerate() {
  for (unsigned int i = 0; i < 20; i++)
    for (unsigned int j = 0; j < 3; j++) {
      displayImage(moderateRain[j]);
      newDelay(100);
    }
}

void displayRainHeavy() {
  for (unsigned int i = 0; i < 20; i++)
    for (unsigned int j = 0; j < 3; j++) {
      displayImage(heavyRain[j]);
      newDelay(100);
    }
}

void displaySnowfall() {
  for (unsigned int i = 0; i < 5; i++) {
    displayImage(snowfall[0]);
    newDelay(1000);
    displayImage(snowfall[1]);
    newDelay(1000);
  }
}

void displaySnowfallHeavy() {
  for (unsigned int i = 0; i < 5; i++) {
    for (unsigned int j = 0; j < 4; j++) {
      displayImage(heavySnowfall[j]);
      newDelay(500);
    }
  }
}

void displayNotFound() {
  for (unsigned int i = 0; i < 5; i++) {
    displayImage(notFound[0]);
    newDelay(500);
    displayImage(notFound[1]);
    newDelay(500);
  }
}

void dayOrNight() {
  if ((currentTime >= sunrise) && (currentTime <= sunset))
    displayClearDay();
  else
    displayClearNight();
}

void displayClearDay() {
  // display clear day
  for (unsigned int i = 0; i < 5; i ++)
    for (unsigned int j = 0; j < 3; j ++) {
      displayImage(clearDay[j]);
      newDelay(400);
    }
}

void displayClearNight() {
  // display clear night
  for (unsigned int i = 0; i < 5; i ++)
    for (unsigned int j = 0; j < 2; j ++) {
      displayImage(clearNight[j]);
      newDelay(600);
    }
}

void cloudDriver(uint8_t b[]) {
  for (unsigned int i = 0; i < 2; i++) {
    for (unsigned int j = 0 ; j < 16; j++) {
      passInByte(b[j]);
      displayBuffer();
      newDelay(187);  // ??
    }
    passInByte(empty);
    displayBuffer();
    newDelay(187);
  }
  clearBuffer();
}

void passInByte(uint8_t b) {
  buffer.shift();
  buffer.add(b);
}

void displayBuffer() {
  for (unsigned int i = 0; i < 8; i++) {
    lc.setRow(0, i, buffer.get(i) );
  }
}

void clearBuffer() {
  for (unsigned int i = 0; i < 16; i++) {
    buffer.shift();
    buffer.add(0b00000000);
  }
}

void displayHumidity(int h) {
  if (h == 100)
    displayImage(maxHumidity);
  else {
    if (h < 10 && leadingZero)
      for (unsigned int i = 0; i < 3 ; i++)
        lc.setRow(0, i, numUnderHundred[0][i]);
    else if (h == 10 || (h > 10 && h != 100))
      for (unsigned int i = 0; i < 3 ; i++)
        lc.setRow(0, i, numUnderHundred[h / 10][i]);

    lc.setRow(0, 3, 0b00000000);

    for (unsigned int i = 0; i < 3 ; i++)
      lc.setRow(0, i + 4, numUnderHundred[h % 10][i]);

    lc.setRow(0, 7, 0b00000000);
  }
}

void requestData() {
  dataIsFresh = false;
  checkWiFi();
  String uri  = "https://api.openweathermap.org/data/2.5/weather?q=" + location + "&appid=" + apikey + "&units=" + (metricUnits ? "metric" : "imperial") +"";

  client.setCACert(certUSERTrustRootCA);

  if (http.begin(client, uri)) {
    // Success connecting
    int httpCode = http.GET();
    if (httpCode > 0 && httpCode == HTTP_CODE_OK) {
      // Successful request
      String payload = http.getString();
      // Parse JSON
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);
      JsonObject weather_0  = doc["weather"][0];
      weatherId             = weather_0["id"];
      JsonObject main       = doc["main"];
      currentTemp           = main["temp"];
      humidity              = main["humidity"];
      currentTime           = doc["dt"];
      JsonObject sys        = doc["sys"];
      sunrise               = sys["sunrise"];
      sunset                = sys["sunset"];

      dataIsFresh = true;
      digitalWrite(LED_WARN, LOW);
    } else {
      // Fail
      digitalWrite(LED_WARN, HIGH);
    }
  } else {
    // Fail
    digitalWrite(LED_WARN, HIGH);
  }
  http.end();
  client.stop();
  return;
}

void checkWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    setupWiFi();
  }
}

void setupWiFi() {
  wifiLed();
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), wifipass.c_str());

    int timeout = 0;
    while (WiFi.status() != WL_CONNECTED) {
      for (int i = 0; i < 14; i++) {
        displayImage(wifi[i]);
        newDelay(50);
      }
      timeout++;
      if (timeout > 5) {
        break;
      }
    }
  }
  displayImage(wifi[14]);
  wifiLed();
}

void scanWiFi() {
  int n = WiFi.scanNetworks();
  int m = n;
  for(int i = 0; i < n && i < sizeof(wifiScan); i++) {
    if(i != 0 && strcmp(wifiScan[i - 1], WiFi.SSID(i).c_str()) == 0) {
      m--;
    }else {
      WiFi.SSID(i).toCharArray(wifiScan[i], 33);
    }
  }
  wifiNr = m;
}

void displayImage(uint8_t image[]) {
  for (unsigned int i = 0; i < 8; i++) {
    lc.setRow(0, i, image[i]);
  }
}

void displayImageOverlay(uint8_t image1[], uint8_t image2[]) {
  for (unsigned int i = 0; i < 8; i++) {
    lc.setRow(0, i, image1[i] | image2[i]);
  }
}

String generateDevicename() {
  // Generate devicename
    String mac = WiFi.macAddress();
    mac.toLowerCase();
    return("esp-weather-" + mac.substring(9, 11) + mac.substring(12, 14) + mac.substring(15));
}

String getDevicename() {
  if(devicename.equals("")) {
    return generateDevicename();
  }else {
    return devicename;
  }
}

void readFileConfig() {
  if(LITTLEFS.exists(PATH_VALIDCONFIG)) {
    ssid = readFileString(PATH_SSID);
    wifipass = readFileString(PATH_WIFIPASS);
    devicename = readFileString(PATH_DEVICENAME);
    location = readFileString(PATH_LOCATION);
    metricUnits = readFileBool(PATH_UNITS);
    leadingZero = readFileBool(PATH_LEAD0);
  }else {
    Serial.println("[Config] No valid config found");
    touchFile(PATH_RESETFLAG);
    ESP.restart();
  }
}

void writeFileConfig() {
  writeFileString(PATH_SSID, ssid);
  writeFileString(PATH_WIFIPASS, wifipass);
  writeFileString(PATH_DEVICENAME, devicename);
  writeFileString(PATH_LOCATION, location);
  writeFileBool(PATH_UNITS, metricUnits);
  writeFileBool(PATH_LEAD0, leadingZero);

  touchFile(PATH_VALIDCONFIG);
}

void touchFile(const char * path) {
  writeFileString(path, "");
}

void writeFileBool(const char * path, bool data) {
  if(data) {
    writeFileString(path, "1");
  }else {
    writeFileString(path, "0");
  }
}

void writeFileString(const char * path, String data) {
  File file = LITTLEFS.open(path, FILE_WRITE);
  if(!file) {
    Serial.printf("[FS] Failed to open file \"%s\" for writing!", path);
  }
  file.print(data);
  file.flush();
  file.close();
}

bool readFileBool(const char * path) {
  if(readFileString(path).equals("1")) {
    return true;
  }else {
    return false;
  }
}

String readFileString(const char * path) {
  String data = "";
  if(LITTLEFS.exists(path)) {
    File file = LITTLEFS.open(path, FILE_READ);
    if(!file) {
      Serial.printf("[FS] Failed to open file \"%s\" for reading!\n\r", path);
    }
    while(file.available()) {
      data += char(file.read());
    }
    file.close();
  }else {
    Serial.printf("[FS] File \"%s\" does not exist!\n\r", path);
  }
  return data;
}

void handleRoot() {
  if(server.hostHeader().equals("setup.ip")) {
    // Handle requests
    String s = configHtml;
    for(int i = 0; i < wifiNr; i++) {
      s += "<option value=\"" + String(wifiScan[i]) + "\">";
    }
    s += configHtml2;
    server.send(200, "text/html", s);
  }else {
    // Request to other domain, redirect
    server.sendHeader("Location", "http://setup.ip", true);
    server.send(302, "text/plain", "");
  }
}

// TODO: validate input
void handleForm() {
  bool flagssid, flagpass, flaglocation;
  char response[128];
  server.arg("plain").toCharArray(response, 128);
  
  char *ptr1 = NULL;
  char *line;
  line = strtok_r(response, "\n", &ptr1);
  while(line != NULL) {
    char *ptr2 = NULL;
    char *key, *value;
    key = strtok_r(line, "=", &ptr2);
    value = strtok_r(NULL, "=", &ptr2);
    if(strcmp(key, "ssid") == 0 && strcmp(value, "") != 0) {
      ssid = value;
      ssid.trim();
      if(!ssid.equals("")) flagssid = true;
    }else if(strcmp(key, "pass") == 0) {
      wifipass = value;
      wifipass.trim();
      if(!wifipass.equals("")) flagpass = true;
    }else if(strcmp(key, "devicename") == 0) {
      devicename = value;
      devicename.trim();
    }else if(strcmp(key, "location") == 0) {
      location = value;
      location.trim();
      if(!location.equals("")) flaglocation = true;
    }else if(strcmp(key, "units") == 0) {
      String temp = value;
      temp.trim();
      if(strcmp(temp.c_str(), "imperial") == 0) {
        metricUnits = false;
      }else {
        metricUnits = true;
      }
    }else if(strcmp(key, "leadzero") == 0) {
      leadingZero = true;
    }
    
    line = strtok_r(NULL, "\n", &ptr1);
  }

  if(!flagssid || !flagpass || !flaglocation) {
    // Invalid config!
    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "");
    return;
  }
  
  if(devicename.equals("")) {
    devicename = generateDevicename();
  }
  writeFileConfig();
  
  server.send(200, "text/html", successHtml);
  delay(500);
  ESP.restart();
}

void handleFactoryReset() {
  if(server.hostHeader().equals("setup.ip")) {
    server.send(200, "text/html", successHtml);

    displayImage(sandclock);
    LITTLEFS.format();
    
    ESP.restart();
  }else {
    server.sendHeader("Location", "http://setup.ip", true);
    server.send(302, "text/plain", "");
  }
  
}

void handleNotFound() {
  if(server.hostHeader().equals("setup.ip")) {
    // Redirect to main page
    server.sendHeader("Location", "/", true);
    server.send(302, "text/plain", "");
  }else {
    server.sendHeader("Location", "http://setup.ip", true);
    server.send(302, "text/plain", "");
  }
  
}

void setupConfigMode() {
  Serial.println("[Boot] Entering config mode...");
  displayImage(sandclock);
  scanWiFi();
  displayImage(wrench);
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(configSsid, configPass);
  dnsServer.start(53, "*", configIp);
  server.on("/", handleRoot);
  server.on("/configure", handleForm);
  //server.on("/reset", handleFactoryReset);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("[Boot] Config mode ready");
}

void loopConfigMode() {
  dnsServer.processNextRequest();
  server.handleClient();
}

void setupOta() {
  char hostname[33];
  devicename.toCharArray(hostname, 32);
  ArduinoOTA.setHostname(hostname);
  ArduinoOTA.setPasswordHash(otapasshash);

  ArduinoOTA.onStart([] () {
    Serial.println("[OTA] OTA incoming, unmounting FS...");
    LITTLEFS.end();
    for (int i = 0; i < 12; i++) {
      displayImage(load[i]);
      newDelay(50);
    }
  });
  ArduinoOTA.onEnd([] () {
    displayImage(progressAni[20]);
    Serial.println("\n\r[OTA] OTA finished, rebooting...");
  });
  ArduinoOTA.onProgress([] (unsigned int progress, unsigned int total) {
    if (progress / (total / 100) == 100) {
      displayImage(progressAni[20]);
    } else {
      displayImageOverlay(progressAni[progress / (total / 20)], load[(millis() / 100) % 12]);
    }
    Serial.printf("\r[OTA] Transfer %d%% complete", progress / (total / 100));
  });
  ArduinoOTA.onError([] (ota_error_t error) {
    displayImage(notFound[0]);
  });
  ArduinoOTA.begin();
}
