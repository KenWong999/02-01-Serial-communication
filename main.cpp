#include <Arduino.h>

/*
  ESP32 串口控制 LED 亮灭实验

  功能：
  串口助手发送字符串 "1"：切换 LED1 状态
  串口助手发送字符串 "2"：切换 LED2 状态
  串口助手发送字符串 "3"：切换 LED3 状态
  串口助手发送字符串 "4" 或其他内容：无对应指令，不执行动作

  接线：
  LED1：GPIO4  -> 220Ω电阻 -> LED长脚 -> LED短脚 -> GND
  LED2：GPIO16 -> 220Ω电阻 -> LED长脚 -> LED短脚 -> GND
  LED3：GPIO17 -> 220Ω电阻 -> LED长脚 -> LED短脚 -> GND
*/

// LED 引脚定义
const int LED1_PIN = 4;
const int LED2_PIN = 16;
const int LED3_PIN = 17;

// 记录 LED 当前状态
bool led1State = false;
bool led2State = false;
bool led3State = false;

void setup() {
  // 初始化串口，波特率需要和串口助手保持一致
  Serial.begin(115200);

  // 设置 LED 引脚为输出模式
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);

  // 初始状态：全部熄灭
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);

  // 缩短读取超时时间，避免无换行符时等待太久
  Serial.setTimeout(50);

  Serial.println("ESP32 串口控制 LED 实验已启动");
  Serial.println("发送字符串 1：切换 LED1");
  Serial.println("发送字符串 2：切换 LED2");
  Serial.println("发送字符串 3：切换 LED3");
  Serial.println("发送字符串 4：无对应指令，不执行动作");
}

void loop() {
  // 判断串口是否收到数据
  if (Serial.available() > 0) {
    // 读取串口收到的字符串
    String command = Serial.readStringUntil('\n');

    // 去掉字符串前后的空格、回车符等
    command.trim();

    // 如果收到的是空字符串，不处理
    if (command.length() == 0) {
      return;
    }

    Serial.print("收到指令：");
    Serial.println(command);

    // 判断收到的字符串内容
    if (command == "1") {
      led1State = !led1State;
      digitalWrite(LED1_PIN, led1State ? HIGH : LOW);

      if (led1State) {
        Serial.println("LED1亮");
      } else {
        Serial.println("LED1灭");
      }
    }
    else if (command == "2") {
      led2State = !led2State;
      digitalWrite(LED2_PIN, led2State ? HIGH : LOW);

      if (led2State) {
        Serial.println("LED2亮");
      } else {
        Serial.println("LED2灭");
      }
    }
    else if (command == "3") {
      led3State = !led3State;
      digitalWrite(LED3_PIN, led3State ? HIGH : LOW);

      if (led3State) {
        Serial.println("LED3亮");
      } else {
        Serial.println("LED3灭");
      }
    }
    else {
      Serial.println("无对应指令，不执行动作");
    }
  }
}