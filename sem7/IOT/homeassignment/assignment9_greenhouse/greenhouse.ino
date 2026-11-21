// Smart Greenhouse Monitoring System
// TMP36 used for temperature sensor, potentiometer for simulated humidity sensor (0-100 %RH)

// ---------- Pin map ----------
#define TEMP_PIN    A0   // TMP36 Vout
#define HUM_PIN     A1   // Potentiometer wiper (humidity)
#define GREEN_LED   2    // All conditions normal
#define RED_LED     3    // Temperature alert
#define YELLOW_LED  4    // Humidity alert

// ---------- Alert thresholds ----------
#define TEMP_LOW    15.0   // C  -> Heater ON
#define TEMP_HIGH   35.0   // C  -> Exhaust fan ON
#define HUM_LOW     40.0   // %RH -> Misting ON
#define HUM_HIGH    85.0   // %RH -> Ventilation ON

float readTemperatureC() {
  float voltage = analogRead(TEMP_PIN) * 5.0 / 1023.0;
  return (voltage - 0.5) * 100.0;   // TMP36: 10 mV/C, 500 mV offset
}

float readHumidity() {
  return analogRead(HUM_PIN) * 100.0 / 1023.0;   // 0-1023 -> 0-100 %RH
}

void setup() {
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("=== Smart Greenhouse Monitoring System ===");
  Serial.println("Safe range: 15-35 C, 40-85 %RH");
}

void loop() {
  float temp = readTemperatureC();
  float hum = readHumidity();

  Serial.print("Temp: ");        Serial.print(temp, 1);
  Serial.print(" C | Humidity: "); Serial.print(hum, 1);
  Serial.print(" % | Status: ");

  bool tempAlert = temp > TEMP_HIGH || temp < TEMP_LOW;
  bool humAlert = hum < HUM_LOW || hum > HUM_HIGH;
  int alerts = tempAlert + humAlert;

  if (alerts == 0) 		Serial.println("NORMAL");
  else if (alerts == 1) Serial.println("WARNING");
  else 					Serial.println("CRITICAL");

  if (temp > TEMP_HIGH)     Serial.println("  ALERT: HIGH TEMPERATURE -> Exhaust fan ON");
  else if (temp < TEMP_LOW)	Serial.println("  ALERT: LOW TEMPERATURE -> Heater ON");
  if (hum < HUM_LOW)        Serial.println("  ALERT: LOW HUMIDITY -> Misting ON");
  else if (hum > HUM_HIGH)  Serial.println("  ALERT: HIGH HUMIDITY -> Ventilation ON");

  digitalWrite(GREEN_LED, alerts == 0 ? HIGH : LOW);
  digitalWrite(RED_LED, tempAlert ? HIGH : LOW);
  digitalWrite(YELLOW_LED, humAlert ? HIGH : LOW);

  delay(1000);
}
