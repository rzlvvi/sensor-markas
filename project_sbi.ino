#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6L40hkjSC"
#define BLYNK_TEMPLATE_NAME "PROJECTIOT"
#define BLYNK_AUTH_TOKEN "EuhjUN_PSNRNlctmMxYq2TTPxnFSt56V"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


char ssid[] = "OPPO A17";
char pass[] = "m4pc7yxi";

const int trigPin = 2;
const int echoPin = 15;
const int buzzerPin = 5;
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

BLYNK_WRITE(V1){
int pinValue=param.asInt();
digitalWrite(buzzerPin,pinValue);
}


BlynkTimer timer;

void sendSensor()
{
long duration;
float distanceCm;
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
  Serial.print("Jarak (cm): "); 
  Serial.println(distanceCm); 
 
if (distanceCm < 10 && distanceCm > 0) {
    // Buzzer on continuously
    digitalWrite(buzzerPin, LOW);
    Blynk.virtualWrite(V2, 255);
  } else if (distanceCm < 20 && distanceCm > 10) {
    // Buzzer beeps twice repeatedly with fast delay
      digitalWrite(buzzerPin, LOW);
      delay(100);
      digitalWrite(buzzerPin, HIGH);
      delay(100);
      Blynk.virtualWrite(V2, 0);
    }
   else if (distanceCm < 40 && distanceCm > 20) {
    // Buzzer beeps once repeatedly with fast delay
    digitalWrite(buzzerPin, LOW);
    delay(300);
    digitalWrite(buzzerPin, HIGH);
    delay(300); // Adjust the delay as necessary
    Blynk.virtualWrite(V2, 0);
  } else if (distanceCm > 40) { 
    // Buzzer off
    digitalWrite(buzzerPin, HIGH);
  }

  Blynk.virtualWrite(V0, distanceCm);
 }
 


void setup()
{
  //SetUp Serial
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzerPin, OUTPUT);

  //SetUp Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  //SetUp PIN
  pinMode(buzzerPin,OUTPUT);

 //SetUp Waktu Kirim
 timer.setInterval(100L, sendSensor);
}


void loop()
{
  Blynk.run();
  timer.run();
  delay(100);
}