#include<Arduino.h>

#define led1 22
#define led2 23

void Task1_blink(void *PvParameter){
  pinMode(led1,OUTPUT);
  for(;;){
    digitalWrite(led1,HIGH);
    vTaskDelay(500/portTICK_PERIOD_MS);
    digitalWrite(led1,LOW);
    vTaskDelay(500/portTICK_PERIOD_MS);
  }
}

void Task2_Blink(void *PvParameter){
  pinMode(led2,OUTPUT);
  for(;;){
    digitalWrite(led2,HIGH);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    digitalWrite(led2,LOW);
    vTaskDelay(1000/ portTICK_PERIOD_MS);
  }
}

void setup(){
    Serial.begin(115200);

    xTaskCreate(
      Task1_blink,
      "led1_Blink",
      1024,
      NULL,
      1,
      NULL
    );

    xTaskCreate(
      Task2_Blink,
      "led2_blink",
      1024,
      NULL,
      1,
      NULL
    );


}

void loop(){
 vTaskDelay(1000/portTICK_PERIOD_MS);
}