// Smart Home Monitoring System
// Integrates: Temperature Monitoring, Motion Detection, Smart Lighting, AC/Fan Control

// ---------- Pin map ----------
#define TEMP_PIN    A0   // TMP36 Vout
#define LDR_PIN     A1   // 10k (to 5V) + photoresistor (to GND) voltage divider
#define PIR_PIN     7    // PIR sensor OUT
#define FAN_PIN     5    // NPN transistor base (via 1k) -> DC motor (fan), PWM
#define ALERT_LED   2    // Red LED - motion alert
#define LIGHT_LED   3    // White LED - room light, PWM

// ---------- Thresholds ----------
#define FAN_ON_TEMP     30.0   // fan turns ON above this (C)
#define FAN_OFF_TEMP    28.0   // fan turns OFF below this (hysteresis)
#define FAN_HIGH_TEMP   35.0   // full speed above this
#define DARK_LEVEL      300    // LDR reading below this = dark (check Serial Monitor and adjust)
#define LIGHT_HOLD_MS   10000  // keep light ON for 10 s after last motion

bool fanOn = false;
unsigned long lastMotionMs = 0;
bool lastMotion = false;

float readTemperatureC() {
  int raw = analogRead(TEMP_PIN);
  float voltage = raw * 5.0 / 1023.0;
  return (voltage - 0.5) * 100.0;   // TMP36: 10 mV/C, 500 mV offset
}

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(ALERT_LED, OUTPUT);
  pinMode(LIGHT_LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("=== Smart Home Monitoring System ===");
}

void loop() {
  unsigned long now = millis();

  // ---- 1. Temperature monitoring + AC/Fan control ----
  float tempC = readTemperatureC();
  if (!fanOn && tempC > FAN_ON_TEMP) fanOn = true;
  else if (fanOn && tempC < FAN_OFF_TEMP) fanOn = false;

  int fanSpeed = 0;
  if (fanOn) fanSpeed = (tempC >= FAN_HIGH_TEMP) ? 255 : 150;  // HIGH / LOW speed
  analogWrite(FAN_PIN, fanSpeed);

  // ---- 2. Motion detection ----
  bool motion = digitalRead(PIR_PIN) == HIGH;
  if (motion) {
    lastMotionMs = now;
    digitalWrite(ALERT_LED, HIGH);
    if (!lastMotion) Serial.println("!! ALERT: Motion detected !!");
  } else {
    digitalWrite(ALERT_LED, LOW);
  }
  lastMotion = motion;

  // ---- 3. Smart lighting (LDR + occupancy) ----
  int lightLevel = 1023 - analogRead(LDR_PIN);   // invert: higher value = brighter
  bool dark = lightLevel < DARK_LEVEL;
  bool occupied = (now - lastMotionMs) < LIGHT_HOLD_MS && lastMotionMs != 0;
  int lightPwm;
  const char *lightState;
  if (!dark)         { lightPwm = 0;   lightState = "OFF (daylight)"; }
  else if (occupied) { lightPwm = 255; lightState = "ON (dark + occupied)"; }
  else               { lightPwm = 40;  lightState = "DIM (dark, no motion)"; }
  analogWrite(LIGHT_LED, lightPwm);

  // ---- 4. Status report ----
  Serial.print("Temp: ");      Serial.print(tempC, 1);
  Serial.print(" C | Fan: ");  Serial.print(fanSpeed == 0 ? "OFF" : (fanSpeed == 255 ? "ON-HIGH" : "ON-LOW"));
  Serial.print(" | LDR: ");    Serial.print(lightLevel);
  Serial.print(" | Light: ");  Serial.print(lightState);
  Serial.print(" | Motion: "); Serial.println(motion ? "YES" : "NO");

  delay(1000);
}
