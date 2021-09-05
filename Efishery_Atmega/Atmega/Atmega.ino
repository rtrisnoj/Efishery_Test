/***********************************
 * 
 * Name: Ryan Trisnojoyo
 * Date: 3 September 2021
 * 
 * Version: 1.0.0
 * 
 * Revision: - 
 * 
 ***********************************/
/* FYI:
 *  I don't have external button, motor, SD Card and 3.3V relay
 * Wiring
 * Metro M0 Express:
 * 
 * Powered by USB
 * Make sure all the GND are connected together
 * 
 *  
 *
 * Metro M0 (Arduino)
 * A0                     ->  Potentionmeter that with change speed of Motor
 * D2                     ->  ON/OFF relay
 * A2                     ->  Analog Output for Motor
 * 
 * TX (PIN1)              -> ESP32 (RX2) PIN    
 * GND                    -> ESP32 GND + GND Battery
 * 
 * Relay
 * NO                     -> VIN Motor
 * NC                     
 * COMMON                 -> +24V Battery
 */


const int potentiometerPin = A0;   // potentiometer connected to analog pin A0
const int relayPin = 2;     //connected to power 24V+
const int motorPin = A2; 

int val = 0;         // variable to store the read value
int val1 = 0; 
int valMotor = 0;
String data;
int dutyCycle;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  // put your setup code here, to run once:
  pinMode(potentiometerPin, INPUT);  // sets the pin as output
  pinMode(relayPin, OUTPUT);
  pinMode(motorPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  val =  analogRead(potentiometerPin);
  val = 500; //change this manually because I don't have potentiometer :(
  
  dutyCycle = map(val, 0, 4095, 0, 255);
  
  analogWrite(motorPin, val); // analogRead values go from 0 to 1023, analogWrite values from 0 to 255

  //digitalWrite(relayPin,1);//activate the relay 
  //delay(10000);     //activate the relay for 10 seconds
  /*
  Serial.print("Motor Analog value: ");
  Serial.println(val);
  */
  //digitalWrite(relayPin,0); //turn off the relay
  
  // berikut data yang dibaca dari serial monitor sendiri, kemudian dikirim ke perangkat lain
  while(Serial.available() > 0){
  delay(10);
  char d = Serial.read();
  data += d;
}
if (data.length() > 0){
  Serial1.print(data);
  data = "";
}

}
