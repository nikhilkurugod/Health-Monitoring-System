// https://www.youtube.com/channel/UCaXI2PcsTlH5g0et67kdD6g  //
// HeartBeat / Pulse Monitoring Device //
// By MOHD SOHAIL //


#define USE_ARDUINO_INTERRUPTS true //--> Set-up low-level interrupts for most acurate BPM math.
#include <PulseSensorPlayground.h> //--> Includes the PulseSensorPlayground Library. 
#include <LiquidCrystal.h> //--> Includes the LiquidCrystal Library.

LiquidCrystal lcd(2, 3, 8, 9, 10, 11); //--> Initialize LiquidCrystal with "lcd". lcd(RS,E,D4,D5,D6,D7).


const int PulseWire = A0; //--> PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED_3 = 13; //--> LED to detect when the heart is beating. The LED is connected to PIN 3 on the Arduino UNO.
int Threshold = 550; //--> Determine which Signal to "count as a beat" and which to ignore.
                     //--> Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                     //--> Otherwise leave the default "550" value. 


//----------------------------------------Draw "Heart" on LCD.
/*
                     heart4 heart5
                       ===   ===
                             
              = 00011 11000 00011 11000 =                      11 11       11 11   
               00111 11100 00111 11100                      111 111     111 111  
               01111 11110 01111 11110                     1111 1111   1111 1111 
               11111 11111 11111 11111                    11111 11111 11111 11111
      heart3   11111 11111 11111 11111   heart6           11111 11111 11111 11111
               11111 11111 11111 11111                    11111 11111 11111 11111
               11111 11111 11111 11111                    11111 11111 11111 11111
              = 01111 11111 11111 11110 =                    1111 11111 11111 1111 
                                               ------->
              = 00011 11111 11111 11000 =                      11 11111 11111 11   
               00001 11111 11111 10000                        1 11111 11111 1    
               00000 11111 11111 00000                          11111 11111      
      heart2   00000 11111 11111 00000   heart7                 11111 11111      
               00000 01111 11110 00000                           1111 1111       
               00000 00111 11100 00000                            111 111        
               00000 00011 11000 00000                             11 11         
              = 00000 00001 10000 00000 =                             1 1           
                             
                       ===   ===
                     heart1 heart8

*/

byte heart1[8] = {B11111, B11111, B11111, B11111, B01111, B00111, B00011, B00001};
byte heart2[8] = {B00011, B00001, B00000, B00000, B00000, B00000, B00000, B00000};
byte heart3[8] = {B00011, B00111, B01111, B11111, B11111, B11111, B11111, B01111};
byte heart4[8] = {B11000, B11100, B11110, B11111, B11111, B11111, B11111, B11111};
byte heart5[8] = {B00011, B00111, B01111, B11111, B11111, B11111, B11111, B11111};
byte heart6[8] = {B11000, B11100, B11110, B11111, B11111, B11111, B11111, B11110};
byte heart7[8] = {B11000, B10000, B00000, B00000, B00000, B00000, B00000, B00000};
byte heart8[8] = {B11111, B11111, B11111, B11111, B11110, B11100, B11000, B10000};
//----------------------------------------

int Instructions_view = 500; //--> Variable for waiting time to display instructions on LCD.
                               
PulseSensorPlayground pulseSensor; //--> Creates an instance of the PulseSensorPlayground object called "pulseSensor"


void setup() {   
  Serial.begin(9600);//--> Set's up Serial Communication at certain speed.
  lcd.begin(16, 2); //--> Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  
  
  lcd.createChar(1, heart1);
  lcd.createChar(2, heart2);
  lcd.createChar(3, heart3);
  lcd.createChar(4, heart4);
  lcd.createChar(5, heart5);
  lcd.createChar(6, heart6);
  lcd.createChar(7, heart7);
  lcd.createChar(8, heart8);
  
 
  
  lcd.setCursor(0,0);
  lcd.print("Heart Beat/Pulse"); 
  lcd.setCursor(0,1);
  lcd.print(" Monitoring EIF ");
  delay(2000);

 
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED_3); //--> auto-magically blink Arduino's LED with heartbeat.
  pulseSensor.setThreshold(Threshold);   
 

 
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !"); //--> This prints one time at Arduino power-up,  or on Arduino reset.  
  }
  

  delay(2000);
  lcd.clear();
}



void loop() {
  int myBPM = pulseSensor.getBeatsPerMinute(); //--> Calls function on our pulseSensor object that returns BPM as an "int". "myBPM" hold this BPM value now.

 
  if (Instructions_view < 500) {
    Instructions_view++;
  }
  
  if (Instructions_view > 499) {
    lcd.setCursor(0,0);
    lcd.print("Put your finger ");
    lcd.setCursor(0,1);
    lcd.print(" on the sensor  "); 
    delay(1000);
    lcd.clear();
    delay(500);
  }

 
  if (pulseSensor.sawStartOfBeat()) { //--> If test is "true", then the following conditions will be executed.
    Serial.println("  A HeartBeat Happened ! "); //--> Print a message "a heartbeat happened".
    Serial.print("BPM: "); //--> Print phrase "BPM: " 
    Serial.println(myBPM); //--> Print the value inside of myBPM. 

   

    lcd.setCursor(1,1);
    lcd.write(byte(1));
    lcd.setCursor(0,1);
    lcd.write(byte(2));
    lcd.setCursor(0,0);
    lcd.write(byte(3));
    lcd.setCursor(1,0);
    lcd.write(byte(4));
    lcd.setCursor(2,0);
    lcd.write(byte(5));
    lcd.setCursor(3,0);
    lcd.write(byte(6));
    lcd.setCursor(3,1);
    lcd.write(byte(7));
    lcd.setCursor(2,1);
    lcd.write(byte(8));
 

   
    lcd.setCursor(5,0);
    lcd.print("Heart Rate");
    lcd.setCursor(5,1);
    lcd.print(": ");
    lcd.print(myBPM);
    lcd.print(" ");
    lcd.print("BPM     ");
  
    
    Instructions_view = 0; 
  }
 
  
  delay(20); //--> considered best practice in a simple sketch.
}