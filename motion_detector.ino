#include <BleKeyboard.h>
#include <LiquidCrystal_I2C.h>

BleKeyboard bleKeyboard;

int lcdColumns = 16;
int lcdRows = 2;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  

const int trigPin = 5;
const int echoPin = 18;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034

long duration;
float distanceCm;
 

void setup() {
  lcd.init();                    
  lcd.backlight();
  Serial.begin(115200); // Starts the serial communication
  bleKeyboard.begin();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;

  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);

  lcd.setCursor(0, 0);
  lcd.print(distanceCm);
  
  //TODO: Checking for motion
  if(distanceCm < 50 ){
    if(bleKeyboard.isConnected()){
      Serial.println("Motion Detected");
      bleKeyboard.write(KEY_F8);
      delay(30000);
    }
  }
  
 delay(1000);
}
