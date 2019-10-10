# M5StackChecker
A simple Bitcoin price checker to get people started using the M5StickC module.

# Installing arduino + libraries + related software 

Windows Users, make sure you install java <br>
https://java.com/en/download/

Install the Arduino IDE,<br>
https://www.arduino.cc/en/Main/Software

Install the M5Stack and M5stick Libraries <br>
https://docs.m5stack.com/#/en/related_documents/Arduino_IDE?id=install-m5stack-library

Install the ESP32 hardware (this is optional, i would just install it)<br>https://docs.m5stack.com/#/en/related_documents/Arduino_IDE?id=install-esp32-board


From "Manage Libraries" install,<br>
- ArduinoJson
- M5StickC
- M5Stack (optional, but i did it)

![a](https://i.imgur.com/mCfnhZN.png)


![a](https://img.staticbg.com/images/oaupload/banggood/images/C7/D3/2543c2c1-2c1a-427d-818d-5ca57a696434.jpg)

Note:You need this, i've seen instances where Wifisecureclient cannot be found when compiliing. you may need to this to your working sketch harware libraries folder
https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFiClientSecure
