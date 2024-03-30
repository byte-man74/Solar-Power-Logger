#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define analog inputs
#define ANALOG_VOLT_IN_PIN A0
#define ANALOG_CURRENT_IN_PIN A1
#define BUZZER_PIN 9  // Connect the buzzer to digital pin 9

// Floats for ADC voltage & input voltagee
float adc_voltage = 0.0;
float in_voltage = 0.0;
int sensorValue = 0;
float current;

// Floats for resistor values in divider (in ohms)
float R1 = 30000.0;
float R2 = 7500.0;

// Float for Reference Voltage
float ref_voltage = 5.0;

// Integer for ADC value
int adc_value = 0;

// Sensitivity for current sensor (adjust as needed)
float sensitivity = 185.0;  // Replace with your actual sensitivity value

// LCD configuration
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change the address (0x27) if needed

void setup() {
  // Setup Serial Monitor
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  Serial.println("Voltage, Current, Power, and Temperature Test");

  // Setup LCD
  lcd.begin(16, 2);
  lcd.print("Voltage: ");
  lcd.setCursor(0, 1);
  lcd.print("Current: ");
}

void loop() {
  // Read the Analog Inputs
  adc_value = analogRead(ANALOG_VOLT_IN_PIN);
  sensorValue = analogRead(ANALOG_CURRENT_IN_PIN);
  
  // Determine voltage at ADC input
  adc_voltage = (adc_value * ref_voltage) / 1024.0;

  // Calculate voltage at divider input
  in_voltage = adc_voltage / (R2 / (R1 + R2));
  current = sensorValue * (5.0 / 1023) / sensitivity;

  // Calculate power
  float power = in_voltage * current;

  // Print results to Serial Monitor
  Serial.print("Input Voltage = ");
  Serial.println(in_voltage, 2);

  Serial.print("Current: ");
  Serial.print(current, 2);
  Serial.println(" A");

  Serial.print("Power: ");
  Serial.print(power, 2);
  Serial.println(" W");

  // Update LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Voltage: ");
  lcd.print(in_voltage, 2);
  
  lcd.setCursor(0, 1);
  lcd.print("Current: ");
  lcd.print(current, 2);
  lcd.setCursor(9, 1);
  lcd.print("Power: ");
  lcd.print(power, 2);

  // Check temperature and activate buzzer if it's above 50 degrees Celsius
  if (power > 50.0) {
    tone(BUZZER_PIN, 1000);  /
  } else {
    noTone(BUZZER_PIN);  // Turn off the buzzer
  }

  // Short delay
  delay(500);
}
