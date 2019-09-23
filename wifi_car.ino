#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// You should get Auth Token in the Blynk App.
char auth[] = "4agxxxxxxxxxxxxxxxxxxxxxxx"; //YourToken
// Your WiFi credentials.
char ssid[] = "XXXXX"; //YourNetworkName
char pass[] = "XXXXX"; //YourPassword


//Motor A
int motorABwd = 16;//D0
int motorAFwd = 5;//D1
int motorAEN = 14;//D5


//Motor B
int motorBFwd = 0;//D3
int motorBBwd = 4;//D2
int motorBEN = 12;//D6

int motorSpeed=500;


BLYNK_WRITE(V10){
  
  int x = param[0].asInt();
  int y = param[1].asInt();

  Serial.print("X = ");
  Serial.print(x);
  Serial.print("; Y = ");
  Serial.println(y);

  moveWheel(x,y);
}

BLYNK_WRITE(V11){
  
  motorSpeed = param.asInt();
  

  Serial.print("Speed=");
  Serial.println(motorSpeed);
  
  
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  pinMode(motorAEN, OUTPUT);
  pinMode(motorAFwd, OUTPUT);
  pinMode(motorABwd, OUTPUT);

  pinMode(motorBEN, OUTPUT);
  pinMode(motorBFwd, OUTPUT);
  pinMode(motorBBwd, OUTPUT);

  digitalWrite(motorAFwd, LOW);
  digitalWrite(motorABwd, LOW);
  analogWrite(motorAEN, motorSpeed); 

  digitalWrite(motorBFwd, LOW);
  digitalWrite(motorBBwd, LOW);
  analogWrite(motorBEN, motorSpeed);  

}

void moveWheel(int x, int y){

  
  if(x==0 && y==0){
    //Stop
    Serial.println("Stop the car");
    digitalWrite(motorAFwd, LOW);
    digitalWrite(motorABwd, LOW);
    digitalWrite(motorBFwd, LOW);
    digitalWrite(motorBBwd, LOW);
    analogWrite(motorAEN, 0); 
    analogWrite(motorBEN, 0);  
  }else if(x==0 && y==1){
    //move forward
    Serial.println("Move forward");
    digitalWrite(motorAFwd, HIGH);
    digitalWrite(motorABwd, LOW);
    digitalWrite(motorBFwd, HIGH);
    digitalWrite(motorBBwd, LOW);
    analogWrite(motorAEN, motorSpeed); 
    analogWrite(motorBEN, motorSpeed);  
  }else if(x==0 && y==-1){
    //move backward
    Serial.println("Move backward");
    digitalWrite(motorAFwd, LOW);
    digitalWrite(motorABwd, HIGH);
    digitalWrite(motorBFwd, LOW);
    digitalWrite(motorBBwd, HIGH);
    analogWrite(motorAEN, motorSpeed); 
    analogWrite(motorBEN, motorSpeed);  
  }else if(x==1 && y==1){
    //turn right
    Serial.println("Turn right");
    digitalWrite(motorAFwd, HIGH);
    digitalWrite(motorABwd, LOW);
    digitalWrite(motorBFwd, HIGH);
    digitalWrite(motorBBwd, LOW);
    analogWrite(motorBEN, motorSpeed); 
    analogWrite(motorAEN, 0);  
  }else if(x==-1 && y==1){
    //turn left
    Serial.println("Turn left");
    digitalWrite(motorAFwd, HIGH);
    digitalWrite(motorABwd, LOW);
    digitalWrite(motorBFwd, HIGH);
    digitalWrite(motorBBwd, LOW);
    analogWrite(motorBEN, 0); 
    analogWrite(motorAEN, motorSpeed);  
  }else if((x==1 ||x==2) && y==0){
    
    Serial.println("Turn right");
    digitalWrite(motorAFwd, HIGH);
    digitalWrite(motorABwd, LOW);
    digitalWrite(motorBFwd, HIGH);
    digitalWrite(motorBBwd, LOW);
    analogWrite(motorBEN, motorSpeed); 
    analogWrite(motorAEN, 0);  
  }else if((x==-1 ||x==-2) && y==0){
  
    Serial.println("Turn left");
    digitalWrite(motorAFwd, LOW);
    digitalWrite(motorABwd, LOW);
    digitalWrite(motorBFwd, HIGH);
    digitalWrite(motorBBwd, LOW);
    analogWrite(motorBEN, 0); 
    analogWrite(motorAEN, motorSpeed); 
  }
  else{
    Serial.println("Doing nothing");
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}
