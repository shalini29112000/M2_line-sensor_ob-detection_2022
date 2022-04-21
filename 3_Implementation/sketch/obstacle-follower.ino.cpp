#include <Arduino.h>
#line 1 "C:\\Users\\PERSONAL\\Documents\\Arduino\\obstacle-follower\\obstacle-follower.ino"
#include<avr/io.h>
#include<util/delay.h>
//MOTOR 'a' CONNECTIONS
const int enA = 5;

// MOTOR 'b' CONNECTIONS
const int enB = 10;

 
// Set the speed (0 = off and 255 = max speed)
// If your wheels are not moving, check your connections,
// or increase the speed.
const int motorSpeed = 60;
int in;  
/* Give a name to a constant value before
 * the program is compiled. The compiler will 
 * replace references to Trigger and Echo with 
 * 3 and 11, respectively, at compile time.
 */
#define Trigger 3
#define Echo 11
  /*   
 *  This setup code is run only once, when 
 */
#line 25 "C:\\Users\\PERSONAL\\Documents\\Arduino\\obstacle-follower\\obstacle-follower.ino"
void setup();
#line 57 "C:\\Users\\PERSONAL\\Documents\\Arduino\\obstacle-follower\\obstacle-follower.ino"
void loop();
#line 92 "C:\\Users\\PERSONAL\\Documents\\Arduino\\obstacle-follower\\obstacle-follower.ino"
int distDetect();
#line 145 "C:\\Users\\PERSONAL\\Documents\\Arduino\\obstacle-follower\\obstacle-follower.ino"
void go_forward();
#line 153 "C:\\Users\\PERSONAL\\Documents\\Arduino\\obstacle-follower\\obstacle-follower.ino"
void go_backwards();
#line 160 "C:\\Users\\PERSONAL\\Documents\\Arduino\\obstacle-follower\\obstacle-follower.ino"
void go_right();
#line 167 "C:\\Users\\PERSONAL\\Documents\\Arduino\\obstacle-follower\\obstacle-follower.ino"
void go_left();
#line 174 "C:\\Users\\PERSONAL\\Documents\\Arduino\\obstacle-follower\\obstacle-follower.ino"
void stop_all();
#line 25 "C:\\Users\\PERSONAL\\Documents\\Arduino\\obstacle-follower\\obstacle-follower.ino"
void setup(){
    
  // Set the baud rate to 9600. 9600 means that 
  // the serial port is capable of transferring 
  // a maximum of 9600 bits per second.
  Serial.begin(9600);
  
  // Motor control pins are outputs
  DDRD|=(1<<DDD5) | (1<<DDD6) | (1<<DDD7);
  DDRB|=(1<<DDB0) | (1<<DDB1) | (1<<DDB2);
  //Initially motor is turned OFF
  PORTD&=~(1<<DDD6) & ~(1<<DDD7);
  PORTB|=~(1<<DDB0) & ~(1<<DDB1);
 
  // Setting the motor speed
  DDD5 <= 0x3C;
  DDB3 <= 0X3C;
  
  // Define each pin as an input or output.
  DDRB&=~(1<<DDB3);// CLEAR IT AS 0
  PORTB|=(1<<DDB3);//  INPUT SET IT TO 1(TRIGGER)
  DDRD|=(1<<DDD3);// OUTPUT BIT(ECHO)
  // Initializes the pseudo-random number generator
  // Needed for the robot to wander around the room  
  go_forward();   // Go forward
  _delay_ms(5000);     // Pause 5 SECONDS    
}
  
/*
 * This is the main code that runs again and again while
 * the Arduino is connected to power.
 */
void loop(){
  int distance = distDetect();
  
  // If obstacle <= 16 inches away
  if(Serial.available()>=1){
    in = Serial.read();
    if((in ==1) ||(distance <= 16)){
      //Serial.println("Obstacle detected ahead");  
      go_backwards();   // Move in reverse
      _delay_ms(2000);
    } 
    /* Go left and right to avoid the obstacle*/
    if((in ==2)||(random(2)==0)){
      // Generates 0 or 1, randomly        
      go_right();  // Turn right
       _delay_ms(3000);
  }
    if((in==3)||(random(1)==0)){
      go_left();  // Turn left
       _delay_ms(3000);
    }
    if(in==4){
    go_forward();  // Move forward
    _delay_ms(500);
  }
  else{
    stop_all();
  }
}
}
  

/* Returns the distance to the obstacle as an integer
 */

int distDetect () {
  int distance = 0;
  int average = 0;
  
  // Grab four measurements of distance and calculate
  // the average.
  for (int i = 0; i < 4; i++) {
  
    // Make the Trigger LOW (0 volts) 
    // for 2 microseconds
    PORTB&=~(1<<DDB3);
    _delay_ms(2000);
  
      
    // Emit high frequency 40kHz sound pulse
    // (i.e. pull the Trigger) 
    // by making Trigger HIGH (5 volts) 
    // for 1 microseconds
    PORTB|=(1<<DDB3);
    _delay_ms(1000);
    PORTB&=~(1<<DDB3);
       
    // Detect a pulse on the Echo pin 8. 
    // pulseIn() measures the time in 
    // microseconds until the sound pulse
    // returns back to the sensor.    
    distance = pulseIn(Echo,1);
  
    // Speed of sound is:
    // 13511.811023622 inches per second
    // 13511.811023622/10^6 inches per microsecond
    // 0.013511811 inches per microsecond
    // Taking the reciprocal, we have:
    // 74.00932414 microseconds per inch 
    // Below, we convert microseconds to inches by 
    // dividing by 74 and then dividing by 2
    // to account for the roundtrip time.
    distance = distance / 74 / 2;
  
    // Compute running sum
    average += distance;
  
    // Wait 10 milliseconds between pings
    _delay_ms(10);
  }
  
  // Return the average of the four distance 
  // measurements
  return (average / 4);
}
/*   
 *  Forwards, backwards, right, left, stop.
 */
void go_forward() {
  PORTD|=(1<<DDD7);  //F1
  PORTD|=(1<<DDD6);   //B1
  PORTB|=(1<<DDB1);   //B2
  PORTB|=(1<<DDB0);   //F2

  
}
void go_backwards() {
  PORTD&=~(1<<DDD7);
  PORTD|=(1<<DDD6);
  PORTB&=~(1<<DDB1);
  PORTB|=(1<<DDB0);
 
}
void go_right() {
   PORTD|=(1<<DDD7);
  PORTD|=(1<<DDD6);
   PORTB&=~(1<<DDB1);
  PORTB&=~(1<<DDB0);
 
}
void go_left() {
  PORTD&=~(1<<DDD7);
  PORTD&=~(1<<DDD6);
  PORTB|=(1<<DDB1);
  PORTB|=(1<<DDB0);
  
}
void stop_all() {
  PORTD&=~(1<<DDD7);
   PORTD&=~(1<<DDD6);
   PORTB&=~(1<<DDD1);
    PORTB&=~(1<<DDD0);
    
}
