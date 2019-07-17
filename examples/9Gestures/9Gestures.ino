/*!
 * @file 9Gestures.ino
 * @brief 展示传感器内置支持的9种手势数据
 * @n 在传感器上方0-20cm的距离内挥手，传感器能识别到左滑动、右滑动。。。。等9种动作
 *
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [ouki](ouki.wang@dfrobot.com)
 * @version  V1.0
 * @date  2016-10-13
 * @https://github.com/DFRobot/DFRobot_PAJ7620
 */
 
#include <DFRobot_PAJ7620U2.h>

DFRobot_PAJ7620U2 paj;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("hello world");
  while(paj.begin() != 0){
    Serial.println("initial PAJ7620U2 failure! 请检查设备是否稳定连接，线序是否正确");
    delay(500);
  }
  paj.setGestureHighRate(false);
}

void loop()
{
  DFRobot_PAJ7620U2::eGesture_t ges = paj.getGesture();
  if(ges != paj.eGestureNone )
    DBG(ges);
}
