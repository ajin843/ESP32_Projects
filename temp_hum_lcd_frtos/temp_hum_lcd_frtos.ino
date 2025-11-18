#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 4
#define DHTTYPE DHT11

// Create LCD and DHT objects
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);


float temperature = 0.0;
float humidity = 0.0;


// Task 1: Read DHT11 sensor every 2 seconds
void TaskReadSensorCode(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (!isnan(h) && !isnan(t)) {
      humidity = h;
      temperature = t;
    }

    //delay but it is non-blocking for other tasks
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

// Task 2: Display on LCD
void TaskDisplayLCDCode(void *pvParameters) {
  (void) pvParameters;
  for (;;) {
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print((char)223);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Humi: ");
    lcd.print(humidity);
    lcd.print("%");

    // Update display every second
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("ESP32");
  delay(1500);
  lcd.clear();

  // craeting FreeRTOS tasks
  xTaskCreate(
    TaskReadSensorCode,   // Function name
    "ReadSensor",         // Name of the task
    2048,                 // Stack size (bytes)
    NULL,                 // Task input parameter
    1,                    // Priority (higher = more CPU time)
    &TaskReadSensor       // Task handle
  );

  xTaskCreate(
    TaskDisplayLCDCode,   
    "DisplayLCD",
    2048,
    NULL,
    1,
    &TaskDisplayLCD
  );
}

void loop() {
  
}
