#define enA 2
#define in1 3
#define in2 4
#define enB 7
#define in3 5
#define in4 6
#define myLimSwitch 10
#define limSwitchPower 13


int Mode;
unsigned long currentTime;
unsigned long lastPressedTime = 0;
boolean LimSwitch;

static int ForwardSpeed = 150;
static int minSpeed = 90;
static int maxSpeed = 255;

boolean needTurn;
boolean EL; //error left - need to turn right.
boolean ER; //error right - need to turn left.
boolean EB; //error both - reverse.
boolean inError;
int errors[10];

int potVal; // value of potentiometer
boolean myLimSwitchVal; // value of myLimSwitch
char dir = 1; // direction

void goForwards() {
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void move(char motor, int Speed) {
  if(motor == 'r' || motor == 'R') {  
    if(Speed == 0) { 
     analogWrite(enB, 0);
    }
    else if (Speed < 0) {
    analogWrite(enB, (Speed * -1));
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);  
  } else {
    analogWrite(enB, Speed);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH); 
   
  }

}
if(motor == 'l' || motor == 'L') {
    if(Speed == 0) {
      analogWrite(enA, 0);
    }
    else if (Speed < 0) {
    analogWrite(enA, Speed * -1);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

  } else {
    analogWrite(enA, Speed);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
} 
limSwitchCheck();

}

int limSwitchCheck() {
   
currentTime = millis();
LimSwitch = digitalRead(myLimSwitch);

if(LimSwitch == 0) {
  if ((currentTime - lastPressedTime) > 300) {  
    switch(Mode) {
      case 0:
      Mode = 1;
      EL = false;
      ER = false;
      break;
      
      case 1:
      Mode = 2;
      EL = true;
      ER = false;
      break;
      
      case 2:
      Mode = 3;
      EL = false;
      ER = true;
      break;
      
      case 3:
      Mode = 0;
      EL = true;
      ER = true;
      break;
      
    }
}
}
Serial.print("LimSwitch is  ");
Serial.print(LimSwitch);
Serial.print("   ");
Serial.print("mode is  ");
Serial.print(Mode);
Serial.println();
}

void Stop() {
    analogWrite(enA, 0);
    analogWrite(enB, 0);
}

boolean errorCorrection() { // doesn't acturally return anything meaningful rhe return is just used to break out of the function
    if(EL && ER) { // both sensors off track
    while(ER && EL) { // while both sensors are off track 
     move('l', -250);
     move('r', -250);
     if(!EL || !ER) 
     return true;
    }
  } else if(EL) { //only the left sensor is off track
     while(EL && !ER) { // while both sensors are off track 
     move('l', 250);
     move('r', 0); 
     if(!EL)
     return true;
    }
  } else if(ER) { //only the left sensor is off track
     while(!EL && ER) { // while both sensors are off track 
     move('l', 0);
     move('r', 250); 
     if(!ER)
     return true;
    }
  }
}

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(myLimSwitch, INPUT_PULLUP
  );
  pinMode(limSwitchPower, OUTPUT);

  goForwards();
  Serial.begin(9600);
}

void loop() {
limSwitchCheck();
errorCorrection();
}
