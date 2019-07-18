/*!
 * @file DFRobot_PAJ7620U2.h
 * @brief 定义DFRobot_PAJ7620手势识别传感器类的基础结构
 * @n The PAC7620 integrates gesture recognition function with general I2C interface into a single chip forming an image analytic sensor system. It can recognize 9 human hand gesticulations such as moving up, down, left, right, forward, backward, circle-clockwise, circle-counter Key Parameters clockwise, and waving. It also offers built-in proximity detection in sensing approaching or departing object from the sensor. The PAC7620 is designed with great flexibility in power-saving mechanism, well suit for low power battery operated HMI devices. The PAJ7620 is packaged into module form in-built with IR LED and optics lens as a complete sensor solution
 
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Ouki](ouki.wang@dfrobot.com)
 * @version  V1.0
 * @date  2019-07-16
 * @https://github.com/DFRobot/DFRobot_PAJ7620U2
 */

#ifndef __DFROBOT_PAJ7620U2_H
#define __DFROBOT_PAJ7620U2_H

#include "Arduino.h"
#include <Wire.h>

//打开这个宏，可以看到程序的详细运行过程
//#define ENABLE_DBG

#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

// DEVICE ID
#define PAJ7620_IIC_ADDR  0x73
#define PAJ7620_PARTID  0x7620

// REGISTER BANK SELECT
#define PAJ7620_REGITER_BANK_SEL  (0xEF)	//W

// REGISTER BANK 0
#define PAJ7620_ADDR_PART_ID_LOW		0x00
#define PAJ7620_ADDR_PART_ID_HIGH		0x01
#define PAJ7620_ADDR_VERSION_ID			0x01
#define PAJ7620_ADDR_SUSPEND_CMD		0x03	//W
#define PAJ7620_ADDR_GES_PS_DET_MASK_0	0x41	//RW
#define PAJ7620_ADDR_GES_PS_DET_MASK_1	0x42	//RW
#define PAJ7620_ADDR_GES_PS_DET_FLAG_0	0x43	//R
#define PAJ7620_ADDR_GES_PS_DET_FLAG_1	0x44	//R
#define PAJ7620_ADDR_STATE_INDICATOR	0x45	//R
#define PAJ7620_ADDR_PS_HIGH_THRESHOLD	0x69	//RW
#define PAJ7620_ADDR_PS_LOW_THRESHOLD	0x6A	//RW
#define PAJ7620_ADDR_PS_APPROACH_STATE	0x6B	//R
#define PAJ7620_ADDR_PS_RAW_DATA		0x6C	//R

// REGISTER BANK 1
#define PAJ7620_ADDR_PS_GAIN			0x44	//RW
#define PAJ7620_ADDR_IDLE_S1_STEP_0		0x67	//RW
#define PAJ7620_ADDR_IDLE_S1_STEP_1		0x68	//RW
#define PAJ7620_ADDR_IDLE_S2_STEP_0		0x69	//RW
#define PAJ7620_ADDR_IDLE_S2_STEP_1		0x6A	//RW
#define PAJ7620_ADDR_OP_TO_S1_STEP_0	0x6B	//RW
#define PAJ7620_ADDR_OP_TO_S1_STEP_1	0x6C	//RW
#define PAJ7620_ADDR_OP_TO_S2_STEP_0	0x6D	//RW
#define PAJ7620_ADDR_OP_TO_S2_STEP_1	0x6E	//RW
#define PAJ7620_ADDR_OPERATION_ENABLE	0x72	//RW

#define PAJ7620_BANK0 0
#define PAJ7620_BANK1 1

// PAJ7620_ADDR_SUSPEND_CMD
#define PAJ7620_I2C_WAKEUP	0x01
#define PAJ7620_I2C_SUSPEND	0x00

// PAJ7620_ADDR_OPERATION_ENABLE
#define PAJ7620_ENABLE	0x01
#define PAJ7620_DISABLE	0x00

#define GES_REACTION_TIME		50	// You can adjust the reaction time according to the actual circumstance.
#define GES_ENTRY_TIME			500	// When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s). 
#define GES_QUIT_TIME			200

class DFRobot_PAJ7620U2
{
public:
  #define ERR_OK             0      //无错误
  #define ERR_DATA_BUS      -1      //数据总线错误
  #define ERR_IC_VERSION    -2      //芯片版本不匹配
  /*
   这里从数据手册上抄写关于这个寄存器的描述
  */
  typedef enum{
    eGestureNone = 0x00,    /**< 未探测到任何动作 */
    eGestureRight = 0x01<<0, /**< 从左向右运动探测 */
    eGestureLeft  = 0x01<<1, /**< 从右向左运动探测 */
    eGestureUp    = 0x01<<2, /**< 从下向上运动探测 */
    eGestureDown  = 0x01<<3, /**< 从上向下运动探测 */
    eGestureForward   = 0x01<<4, /**< 从远到近运动探测 */
    eGestureBackward  = 0x01<<5, /**< 从近到远运动探测 */
    eGestureClockwise = 0x01<<6, /**< 顺时针运动探测 */
    eGestureAntiClockwise = 0x01<<7, /**< 逆时针运动探测 */
    eGestureWave = 0x01<<8,          /**< 挥手运动探测 */
    eGestureAll = 0xff             /**< 支持所有动作，无实际意义，用于写程序抽象逻辑*/
  }eGesture_t;
  
  typedef enum {
    eBank0 = 0,
    eBank1 = 1,
  }eBank_t;
  
  typedef enum {
    eNormalRate = 0,
    eGamingRage,
  }eRateMode_t;

  typedef struct{
    eGesture_t gesture;
    const char * description;
  }sGestureDescription_t;

public:
  /**
   * @brief 构造函数
   * @param mode 构造设备时，可以指定它的默认工作模式
   */
  DFRobot_PAJ7620U2(TwoWire *pWire=&Wire);

  /**
   * @brief 初始化函数
   * @return 返回0表示初始化成功，返回其他值表示初始化失败
   */
  int begin(void);

  /**
   * @brief 配置用户想要识别的手势，减少要识别的手势个数，可以提高识别效率，提高识别精度
   * @return 返回0表示配置成功，返回其他值表示配置失败
   */
  int configGesture(uint8_t val);
  int setNormalOrGamingMode(eRateMode_t mode);
  void setGestureHighRate(bool b);
  String gestureDescription(eGesture_t gesture);
  /**
   * @brief 获取手势
   * @return 返回手势
   */
  eGesture_t getGesture(void);

private:
  /**
   * @brief 切换Bank
   * @param bank  要切换的Bank，可选 eBank0或eBank1
   * @return 返回0表示切换成功，返回其他值表示切换失败
   */
  int selectBank(eBank_t bank);

  /**
   * @brief 写寄存器函数
   * @param reg  寄存器地址 8bits
   * @param pBuf 要写入数据的存放缓存
   * @param size 要写入数据的长度
   */
  void writeReg(uint8_t reg, void* pBuf, size_t size);

  /**
   * @brief 读取寄存器函数
   * @param reg  寄存器地址 8bits
   * @param pBuf 要写入数据的存放缓存
   * @param size 要写入数据的长度
   * @return 返回实际读取的长度，返回0表示读取失败
   */
  uint8_t readReg(uint8_t reg, void* pBuf, size_t size);
  static const uint8_t /*PROGMEM*/ initRegisterArray[219][2];
  static const sGestureDescription_t gestureDescriptions[10];
private:
  TwoWire *_pWire;
  const uint8_t _deviceAddr = PAJ7620_IIC_ADDR;
  bool _gestureHighRate = true;
  eGesture_t _gesture;
  uint8_t _configuredGesture=(uint8_t)eGestureAll;

};

#endif
