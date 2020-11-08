#define ENABLE 5
#define DIRA 3
#define DIRB 4
 
void setup() {
  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  //FanOn();
  FanOff();
  
}

void FanOn()
{
  digitalWrite(ENABLE,HIGH); // enable on
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  delay(5000);
}

void FanOff()
{
  digitalWrite(ENABLE,HIGH);
  digitalWrite(DIRA,LOW); //fast stop
  digitalWrite(DIRB,LOW);
  delay(5000);
}
