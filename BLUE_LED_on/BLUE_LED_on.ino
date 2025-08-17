#define led 2

void setup() {
  Serial.begin(115200);
  delay(1500);              
  Serial.println("turn ON led on esp32");
  pinMode(led, OUTPUT);
  digitalWrite(led,HIGH);
}

void loop() {
 
}
