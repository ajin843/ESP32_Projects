#include <DHT.h>

#define DHTPIN         10    // DHT data pin
#define DHTTYPE        DHT11 // DHT11 sensor
#define LED_PIN        13    // On‑board LED

const float TEMP_THRESHOLD = 30.0;  // °C

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Read temperature (°C)
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println("DHT read error");
    delay(2000);
    return;
  }

  // Check threshold
  if (t > TEMP_THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
    Serial.print("TEMP TOO HIGH! ");
    Serial.print(t, 1);
    Serial.println(" °C");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.print("Temp: ");
    Serial.print(t, 1);
    Serial.println(" °C");
  }

  delay(2000); // Read every 2 seconds
}
