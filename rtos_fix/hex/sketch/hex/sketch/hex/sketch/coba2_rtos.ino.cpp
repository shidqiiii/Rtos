#include <Arduino.h>
#line 1 "C:\\Users\\Shidqi\\Documents\\Arduino\\coba2_rtos\\coba2_rtos.ino"
#include "LiquidCrystal.h"
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <BlynkSimpleStream.h>

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

const int rs=12, e=11, d4=4, d5=5, d6=6, d7=7;
LiquidCrystal lcd(rs,e,d4,d5,d6,d7);

int temp;
int fan = 2;
int led = 3;

#line 16 "C:\\Users\\Shidqi\\Documents\\Arduino\\coba2_rtos\\coba2_rtos.ino"
void setup();
#line 28 "C:\\Users\\Shidqi\\Documents\\Arduino\\coba2_rtos\\coba2_rtos.ino"
void TaskOne(void *pvParameters);
#line 43 "C:\\Users\\Shidqi\\Documents\\Arduino\\coba2_rtos\\coba2_rtos.ino"
void TaskTwo(void *pvParameters);
#line 66 "C:\\Users\\Shidqi\\Documents\\Arduino\\coba2_rtos\\coba2_rtos.ino"
void temperature();
#line 86 "C:\\Users\\Shidqi\\Documents\\Arduino\\coba2_rtos\\coba2_rtos.ino"
void nyala();
#line 91 "C:\\Users\\Shidqi\\Documents\\Arduino\\coba2_rtos\\coba2_rtos.ino"
void mati();
#line 96 "C:\\Users\\Shidqi\\Documents\\Arduino\\coba2_rtos\\coba2_rtos.ino"
void loop();
#line 16 "C:\\Users\\Shidqi\\Documents\\Arduino\\coba2_rtos\\coba2_rtos.ino"
void setup(){
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(led, OUTPUT);
  pinMode(fan, OUTPUT);

  xTaskCreate(TaskOne, "One", 128, NULL, 2, &TaskHandle_1);
  xTaskCreate(TaskTwo, "Two", 128, NULL, 1, &TaskHandle_2);
  vTaskStartScheduler();
}

void TaskOne(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  {
    temperature();
    int Button = digitalRead(A2); //read the state of the button
    if (Button == 1) { //if is pressed
       vTaskPrioritySet(TaskHandle_1,0);
       vTaskPrioritySet(TaskHandle_2,2);
    }
  }
}

void TaskTwo(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  {
    int Button1 = digitalRead(A3); //read the state of the button
    if (Button1 == HIGH) { //if is pressed
       digitalWrite(led, HIGH);
       delay(1000);
    }

    int Button = digitalRead(A1); //read the state of the button
    if (Button == HIGH) { //if is pressed
       digitalWrite(fan, LOW);
       delay(1000);
    }

    lcd.setCursor(0,0);
    lcd.print("OFFLINE");
  }
}

void temperature(){
  temp = analogRead(A0);
    temp = temp* (5.0 * 100.0/1024.0);
    if(temp < 25){
      lcd.print("Normal");
      mati();
    }
    else if(temp >= 25){
      lcd.print("Heat");
      nyala();
    }
      
    lcd.setCursor(0,1);
    lcd.print("Suhu: ");
    lcd.print(temp);
    lcd.print(" C ");
    delay(200);
    lcd.clear();
}

void nyala(){
  digitalWrite(led, LOW);
  digitalWrite(fan, HIGH);
}

void mati(){
  digitalWrite(led, HIGH);
  digitalWrite(fan, LOW);
}
      
void loop(){
  // put your main code here, to run repeatedly:
}

