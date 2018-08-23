// PWM Reciever
// THROTTLE CH5 (AUX switch)
// TURN CH2 (ROLL)

byte PWM_THROTTLE_PIN = 2;
byte PWM_TURN_PIN = 3;

const int stepPin_turn = 4; 
const int dirPin_turn = 5; 
const int stepPin_throttle = 6; 
const int dirPin_throttle = 7; 
 
int PWM_TURN_VALUE;
int PWM_THROTTLE_VALUE;

//Use to determin if throttle is on or off
bool THROTTLE_ON = false;
 
void setup() {
  // Set pins as Input
  pinMode(PWM_TURN_PIN, INPUT);
  pinMode(PWM_THROTTLE_PIN, INPUT);
  
  // Set pins as Outputs
  pinMode(stepPin_turn,OUTPUT); 
  pinMode(dirPin_turn,OUTPUT); 
  pinMode(stepPin_throttle,OUTPUT); 
  pinMode(dirPin_throttle,OUTPUT); 
     
  Serial.begin(115200);
}
 
void loop() {
  //Read pwm values
  PWM_TURN_VALUE = pulseIn(PWM_TURN_PIN, HIGH);
  PWM_THROTTLE_VALUE = pulseIn(PWM_THROTTLE_PIN, HIGH);

  //Move throttle (Ch5)
  if(PWM_THROTTLE_VALUE > 1200 && THROTTLE_ON == false){
    //Serial.println(PWM_THROTTLE_VALUE);
    Serial.println("Throttle on");
      digitalWrite(dirPin_throttle,HIGH); // Enables the motor to move in a particular direction
      // Makes 200 pulses for making one full cycle rotation
      for(int x = 0; x < 100; x++) {
       digitalWrite(stepPin_throttle,HIGH); 
       delayMicroseconds(500); 
       digitalWrite(stepPin_throttle,LOW); 
       delayMicroseconds(500); 
      }    
      THROTTLE_ON = true;
      
  }else if(PWM_THROTTLE_VALUE < 1200 && THROTTLE_ON == true){
    //Serial.println(PWM_THROTTLE_VALUE);
    Serial.println("Throttle off");
      digitalWrite(dirPin_throttle,LOW); // Enables the motor to move in a particular direction
      // Makes 200 pulses for making one full cycle rotation
      for(int x = 0; x < 100; x++) {
       digitalWrite(stepPin_throttle,HIGH); 
       delayMicroseconds(500); 
       digitalWrite(stepPin_throttle,LOW); 
       delayMicroseconds(500); 
      }        
      THROTTLE_ON = false;
  }


  //Move right/left (Ch2)
  while(PWM_TURN_VALUE > 1550){
       Serial.print("TurnRIGHT PWM: ");    
       Serial.print(PWM_TURN_VALUE);       
       Serial.println(" ");        
       digitalWrite(dirPin_turn,LOW); // Enables the motor to move in a particular direction
       digitalWrite(stepPin_turn,HIGH); 
       delayMicroseconds(500); 
       digitalWrite(stepPin_turn,LOW); 
       delayMicroseconds(500);
       PWM_TURN_VALUE = pulseIn(PWM_TURN_PIN, HIGH);
  }
  while(PWM_TURN_VALUE < 1450){
       Serial.print("TurnLEFT - PWM: ");    
       Serial.print(PWM_TURN_VALUE);
       Serial.println(" ");       
       digitalWrite(dirPin_turn,HIGH); // Enables the motor to move in a particular direction
       digitalWrite(stepPin_turn,HIGH); 
       delayMicroseconds(500); 
       digitalWrite(stepPin_turn,LOW); 
       delayMicroseconds(500);    
       PWM_TURN_VALUE = pulseIn(PWM_TURN_PIN, HIGH);
  }
  


  delay(100);
}
