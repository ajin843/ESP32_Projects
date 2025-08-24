#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

typedef struct msg
{
  char a[50];
}msg_t;

msg_t Rdata;

void OnDataRecv(const uint8_t *RevMac , const uint8_t *incomingData , int len){
  memcpy(&Rdata,incomingData,sizeof(Rdata));
  Serial.print("character  received");
  Serial.println(Rdata.a);
}

void setup() {
  Serial.begin(115200);
  delay(1500);

  WiFi.mode(WIFI_STA);

  if(esp_now_init() != ESP_OK){
    Serial.println("esp_now_init fails");
  }

  esp_now_register_recv_cb(OnDataRecv);

}

void loop() {
  
}