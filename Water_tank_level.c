#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x26, 16, 2);

// Pin Declarations
int trigPin = 10;
int echoPin = 9;
int motor_pin = 5;
int red_led = 2;
int yell_led = 3;
int green_led = 4;

// Variables
long duration;
float distance;

void ultrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Transmit 10us pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Calculate distance in cm
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0343 / 2.0;
  
  Serial.print("Distance: ");
  Serial.println(distance);
}

void level_check() {
  lcd.setCursor(0, 1); 
  
  if (distance > 200) {
    // Water level LOW (Distance high) -> Turn motor ON
    digitalWrite(red_led, HIGH);
    digitalWrite(yell_led, LOW);
    digitalWrite(green_led, LOW);
    digitalWrite(motor_pin, HIGH);
    lcd.print("Level: LOW     "); 
  } 
  else if (distance >= 120 && distance <= 200) {
    // Water level MEDIUM -> Turn motor ON
    digitalWrite(red_led, LOW);
    digitalWrite(yell_led, HIGH);
    digitalWrite(green_led, LOW);
    digitalWrite(motor_pin, HIGH);
    lcd.print("Level: MEDIUM  "); 
  } 
  else {
    // Water level HIGH (Distance low) -> Turn motor OFF
    digitalWrite(red_led, LOW);
    digitalWrite(yell_led, LOW);
    digitalWrite(green_led, HIGH);
    digitalWrite(motor_pin, LOW);
    lcd.print("Level: HIGH    "); 
  }
}

void setup() {
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motor_pin, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(yell_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  ultrasonic();
  
  // Display measured distance on first line
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(distance, 1);
  lcd.print(" cm   ");
  
  level_check();
  
  delay(500); // Small delay for stable readings
}
