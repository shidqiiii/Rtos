#include <Arduino.h>
#line 1 "E:\\Materi Kuliah\\Semester 6\\Sistem Operasi Waktu Nyata\\rtos fix\\rtos_fix\\rtos_fix.ino"
#include "LiquidCrystal.h"
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <BlynkSimpleStream.h>

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
TaskHandle_t TaskHandle_3;

const int rs=12, e=11, d4=4, d5=5, d6=6, d7=7;
LiquidCrystal lcd(rs,e,d4,d5,d6,d7);

int temp;
int fan = 2;
int led = 3;

#line 17 "E:\\Materi Kuliah\\Semester 6\\Sistem Operasi Waktu Nyata\\rtos fix\\rtos_fix\\rtos_fix.ino"
void setup();
#line 30 "E:\\Materi Kuliah\\Semester 6\\Sistem Operasi Waktu Nyata\\rtos fix\\rtos_fix\\rtos_fix.ino"
void TaskOne(void *pvParameters);
#line 46 "E:\\Materi Kuliah\\Semester 6\\Sistem Operasi Waktu Nyata\\rtos fix\\rtos_fix\\rtos_fix.ino"
void TaskTwo(void *pvParameters);
#line 75 "E:\\Materi Kuliah\\Semester 6\\Sistem Operasi Waktu Nyata\\rtos fix\\rtos_fix\\rtos_fix.ino"
void TaskThree(void *pvParameters);
#line 90 "E:\\Materi Kuliah\\Semester 6\\Sistem Operasi Waktu Nyata\\rtos fix\\rtos_fix\\rtos_fix.ino"
void temperature();
#line 110 "E:\\Materi Kuliah\\Semester 6\\Sistem Operasi Waktu Nyata\\rtos fix\\rtos_fix\\rtos_fix.ino"
void nyala();
#line 115 "E:\\Materi Kuliah\\Semester 6\\Sistem Operasi Waktu Nyata\\rtos fix\\rtos_fix\\rtos_fix.ino"
void mati();
#line 120 "E:\\Materi Kuliah\\Semester 6\\Sistem Operasi Waktu Nyata\\rtos fix\\rtos_fix\\rtos_fix.ino"
void loop();
#line 17 "E:\\Materi Kuliah\\Semester 6\\Sistem Operasi Waktu Nyata\\rtos fix\\rtos_fix\\rtos_fix.ino"
void setup(){
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(led, OUTPUT);
  pinMode(fan, OUTPUT);

  xTaskCreate(TaskOne, "One", 128, NULL, 2, &TaskHandle_1);
  xTaskCreate(TaskTwo, "Two", 128, NULL, 1, &TaskHandle_2);
  xTaskCreate(TaskThree, "Two", 128, NULL, 1, &TaskHandle_3);
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
       vTaskPrioritySet(TaskHandle_1,1);
       vTaskPrioritySet(TaskHandle_2,2);
       vTaskPrioritySet(TaskHandle_3,2);
    }
  }
}

void TaskTwo(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  {
    int Button1 = digitalRead(A3); //read the state of the button
    if (Button1 == 1) { //if is pressed
       digitalWrite(led, LOW);
       delay(1000);
    }

    int Button = digitalRead(A1); //read the state of the button
    if (Button == HIGH) { //if is pressed
       digitalWrite(fan, LOW);
       delay(1000);
    }

    lcd.setCursor(0,0);
    lcd.print("OFFLINE");

    int Button3 = digitalRead(A4); //read the state of the button
    if (Button3 == 1) { //if is pressed
       vTaskPrioritySet(TaskHandle_1,2);
       vTaskPrioritySet(TaskHandle_2,1);
    }
  }
}

void TaskThree(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  {
    int Button = digitalRead(A4); //read the state of the button
    if (Button == 1) { //if is pressed
       vTaskPrioritySet(TaskHandle_1,2);
       vTaskPrioritySet(TaskHandle_2,1);
       vTaskPrioritySet(TaskHandle_3,1);
    }
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

