#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// Pin definitions for LCD display
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
//SoftwareSerial bluetooth(1, 0);

// Pin definitions for MQ2 gas sensor
const int mq2= A0;

const int relay = 8;
const int buzzer = 9;
int RLED= 12;
int YLED= 13;


void setup() {
  // Initialize the LCD display
  lcd.begin(16, 2);
  lcd.print("Smoke Detector");

  // Initialize the MQ2 gas sensor
  pinMode(mq2, INPUT);

  // Initialize the relay module, buzzer, LED, fan, and exhaust fan
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(RLED, OUTPUT);
  pinMode(YLED, OUTPUT);
  Serial.begin(9600);
  //bluetooth.begin(9600);
}

void loop() {
  // Read the analog value from the MQ2 gas sensor
  int sensor_value = analogRead(mq2); //read MQ2 analog outputs at A0 
  int smoke = map(sensor_value, 0, 1023, 0, 100);
  Serial.print("Smoke Level: ");  //print message in serail monitor
  Serial.println(smoke);            //print value of smoke level in serial monitor

  // Display the smoke density on the LCD display
  lcd.setCursor(0, 1);
  lcd.print("Smoke Level: ");
  lcd.print(smoke);

  // Check if the smoke density is above the threshold
  if (smoke > 12) {
    lcd.setCursor(1,1);         //jump here if smoke level is greater than threshold
    lcd.print("Alert: Fire");
    Serial.println("Alert: Fire");
    //bluetooth.write("Alert: Fire");
    //Activate the relay module, buzzer, and LED
    digitalWrite(relay, HIGH);
    digitalWrite(RLED, HIGH);
    digitalWrite(YLED, LOW);
    tone(buzzer, 1000, 200);
  } 
  else {
      
    lcd.print ("No Smoke Detected");
    //bluetooth.write("No Smoke Detected");
    Serial.println("No Smoke Detected");

    // Deactivate the relay module, buzzer, and LED
    digitalWrite(relay, LOW);
    digitalWrite(RLED, LOW);
    digitalWrite(YLED, HIGH);
    noTone(buzzer);
  }

  // Wait for half a second before checking again
delay(500);
}
