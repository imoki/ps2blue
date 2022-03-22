#include <BleMouse.h>
#include <WiFi.h>
 
BleMouse bleMouse("ps2blue","Espressif",100);//其中“ps2blue”为键盘名称；"Espressif"为制造商

const int xPin = A4;     //X 接 A4
const int yPin = A5;     //Y 接 A5
const int btPin = 17;    //Bt 接 17
const float range = 102.0;  // 总长度
const float xCentre = 46.0; // x中心
const float yCentre = 47.0; // y中心
float xDeviation = 1.0; // x偏差积
const int xDeviationMin = 3;  // x细微偏差值
float yDeviation = 1.0; // y偏差积
const int yDeviationMin = 3;  // y细微偏差值
float x = 0;  // x位移
float y = 0;  // y位移
unsigned long startTime;

void setup()
{
  analogSetWidth(10);                  // 设置采样分辨率为10bit 范围可以是9-12之间
  pinMode(btPin,INPUT_PULLUP);         // 设置btpin为INPUT
  digitalWrite(btPin, HIGH);           // HIGH
  Serial.begin(115200);                  // 初始化串口
  Serial.println("Starting BLE work!");
  bleMouse.begin();
  xDeviation = (range - xCentre)/xCentre;
  yDeviation = (range - yCentre)/yCentre;
}

void loop()
{
  if(bleMouse.isConnected()){ // 蓝牙连接成功
    x = ((analogRead(xPin) + xDeviationMin)/10) - xCentre;
    startTime = millis();
    if( x < 0)
    {
      x *= xDeviation;
      while(millis() < startTime - (unsigned long)x) {
        bleMouse.move(1,0); // 向右移动
      }
    }else
    {
      while(millis() < startTime + (unsigned long)x) {
        bleMouse.move(-1, 0); // 向左移动
      }
    }

    y = ((analogRead(yPin) - yDeviationMin)/10) - yCentre;
    startTime = millis();
    if( y < 0)
    {
      y *= yDeviation;
      while(millis() < startTime - (unsigned long)y) {
        bleMouse.move(0,-1); // 向上移动
      }
    }else
    {
      while(millis() < startTime + (unsigned long)y) {
        bleMouse.move(0,1); // 向下移动
      }
    }

    if(digitalRead(btPin) == 0)
    {
      delay(200);
      bleMouse.click(MOUSE_LEFT); // 左键点击
    }
  }
  delay(50);
}

