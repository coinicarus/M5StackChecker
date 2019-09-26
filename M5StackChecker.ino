#include <M5Stack.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

//Wifi details
char wifiSSID[] = "YOUR-WIFI";
char wifiPASS[] = "YOUR-PASS";
 
const int httpsPort = 443;
float conversion;
 
String on_currency = "BTCEUR"; //currency can be changed here ie BTCUSD BTCGBP etc
String on_sub_currency = on_currency.substring(3);
String memo = "Memo "; //memo suffix, followed by the price then a random number
 
void setup() {
  M5.begin();

  //connect to local wifi            
  WiFi.begin(wifiSSID, wifiPASS);  
  while (WiFi.status() != WL_CONNECTED) {
    delay(2000);
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
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(50, 80);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.println("1 BTC = " + String(conversion) + " " + on_sub_currency);
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
