/*!
 * @file MoreGestures.ino
 * @brief 在高速模式下，通过自己写算法，实现更多手势
 *
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [ouki](ouki.wang@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-16
 * @https://github.com/DFRobot/DFRobot_PAJ7620U2
 */
 
#include <DFRobot_PAJ7620U2.h>

DFRobot_PAJ7620U2 paj;

void setup()
{
  Serial.begin(115200);
  delay(300);
  Serial.println("Gesture recognition system base on PAJ7620U2");
  while(paj.begin() != 0){
    Serial.println("initial PAJ7620U2 failure! 请检查设备是否稳定连接，线序是否正确");
    delay(500);
  }
  Serial.println("PAJ7620U2初始化完成，可以开始测试手势识别功能了");
  
  /*设置快速挥手识别模式
   *参数填写false 模块进入慢速识别状态，每2秒识别一个动作，我们将一些扩展动作集成到库内部，方便基础用户使用
   *可以识别的动作包括向左滑动 向右滑动 向上滑动 向下滑动 向前滑动 向后滑动 逆时针 顺时针 快速挥手 9个基础动作
   *左右慢挥手 上下慢挥手 前后慢挥手 乱序慢挥手  4个扩展动作 
   *
   *
   *
   *参数填写true 模块进入快速识别状态
   *可以识别的动作包括向左滑动 向右滑动 向上滑动 向下滑动 向前滑动 向后滑动 逆时针 顺时针 快速挥手 9个动作
   *高级用户如果想要用这些动作的组合，需要在外部自己算法逻辑，比如左右快速挥手，手斜向下滑动，因为每个人用到的动作有限
   *在高速模式下，我们不计划将更多的扩展动作集在库中，需要用户在ino文件中自己完成算法逻辑
   */
  paj.setGestureHighRate(true);

}

void loop()
{
  DFRobot_PAJ7620U2::eGesture_t gesture = paj.getGesture();
  if(gesture != paj.eGestureNone ){
    String description  = paj.gestureDescription(gesture);//将手势号码转换为描述字符串
    Serial.println(description);
  }
}