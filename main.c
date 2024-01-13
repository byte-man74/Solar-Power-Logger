#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define analog inputs
#define ANALOG_VOLT_IN_PIN A0
#define ANALOG_CURRENT_IN_PIN A1
#define ANALOG_TEMP_IN_PIN A2

// Floats for ADC voltage & input voltage
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
float sensitivity = 185.0; // Replace with your actual sensitivity value

// LCD configuration
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change the address (0x27) if needed

void setup() {
  // Setup Serial Monitor
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  Serial.println("Voltage, Current, and Temperature Test");

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
  int tempSensorValue = analogRead(ANALOG_TEMP_IN_PIN);

  // Determine voltage at ADC input
  adc_voltage = (adc_value * ref_voltage) / 1024.0;

  // Calculate voltage at divider input
  in_voltage = adc_voltage / (R2 / (R1 + R2));
  current = sensorValue * (5.0 / 1023) / sensitivity;

  // Convert temperature analog value to temperature in degrees Celsius
  float temperature = (tempSensorValue * 5.0 / 1024.0) * 100.0;

  // Print results to Serial Monitor
  Serial.print("Input Voltage = ");
  Serial.println(in_voltage, 2);

  Serial.print("Current: ");
  Serial.print(current, 2);
  Serial.println(" A");

  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.println(" °C");

  // Update LCD
  lcd.setCursor(9, 0);
  lcd.print(in_voltage, 2);
  lcd.setCursor(9, 1);
  lcd.print(current, 2);
  lcd.setCursor(0, 1);
  // lcd.print("Temperature: ");
  // lcd.print(temperature, 2);

  // Short delay
  delay(500);
}
