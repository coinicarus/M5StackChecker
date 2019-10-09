#include <M5StickC.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
 
//Wifi details
char wifiSSID[] = "WIFI_NAME"; //case sensitive
char wifiPASS[] = "WIFI_PASS"; //case sensitive
 
const int httpsPort = 443;
float conversion;
 
String on_currency = "BTCUSD"; //currency can be changed here ie BTCUSD BTCGBP etc
String on_sub_currency = on_currency.substring(3);
 
void setup(void) {
  M5.begin();
  M5.lcd.setRotation(8);
 
   //connect to local wifi            
 WiFi.begin(wifiSSID, wifiPASS);   
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    if(i >= 5){
     M5.Lcd.setRotation (17); 
     M5.Lcd.fillScreen(BLACK);
     M5.Lcd.setCursor(15, 35);
     M5.Lcd.setTextSize(1);
     M5.Lcd.setTextColor(TFT_RED);
     M5.Lcd.println("WIFI NOT CONNECTED");
    }
    delay(1000);
    i++;
  }
}
 
void loop() {
 on_rates();
 display_price();
 delay(60000);
}
 
//Display the price
 
void display_price() //function for displaying the bitcoin price
{
  M5.lcd.setRotation (17);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(15, 35);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.println("1 BTC = "+ String(conversion) + " " + on_sub_currency);
}
 
void on_rates() //function for getting bitcoins price
{
  WiFiClientSecure client;
  if (!client.connect("api.opennode.co", httpsPort)) {
    return;
  }
 
  String url = "/v1/rates";
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: api.opennode.co\r\n" +
               "User-Agent: ESP32\r\n" +
               "Connection: close\r\n\r\n");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }
  String line = client.readStringUntil('\n');
    const size_t capacity = 169*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(168) + 3800;
    DynamicJsonDocument doc(capacity);
    deserializeJson(doc, line);
    conversion = doc["data"][on_currency][on_currency.substring(3)];
 
}
