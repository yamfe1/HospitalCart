#define enA 10
#define in1 3
#define in2 5
#define enB 11
#define in3 6
#define in4 9
#define limSwitch 1
#define pot A0


static int ForwardSpeed = 150;
static int minSpeed = 90;
static int maxSpeed = 255;

boolean needTurn;
boolean EL; //error left - need to turn right.
boolean ER; //error right - need to turn left.
boolean EB; //error both - reverse.
boolean inError;
int errors[10];



int LeftSpeed; //motor speed.
char LeftDirection; //motor direction. C for clockwise A for anti-clockwise.
String in1Val; // in1Val based off of other parameters.
String in2Val; // in2Val based off of other parameters.

int RightSpeed; //motor1 speed.
char RightDirection; //motor direction. C for clockwise A for anti-clockwise.
String in3Val; // in1Val based off of other parameters.
String in4Val; // in2Val based off of other parameters.

int potVal; // value of potentiometer
boolean limSwitchVal; // value of limSwitch
char dir = 1; // direction

void goForwards() {
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}


void setRightDir(char dir) { // sets right direction to forwards or backwards, C for clockwise A for anti-clockwise.
  if (dir == 'C') {
    in1Val = "HIGH";
    in2Val = "LOW";
  } else if (dir == 'A') {
    in1Val = "LOW";
    in2Val = "HIGH";
  } else {
    Serial.println("Error - Right dir is not C or A");
  }
}

void LeftDefaultState() { //activates on setup
  LeftSpeed = 0;
  LeftDirection = 'C';
}

void RightDefaultState() { //activates on setup
  RightSpeed = 0;
  RightDirection = 'C';
}

void changeRightSpeed(int x) { // chnages left speed by x amount
  RightSpeed = RightSpeed + x;
}

void changeLeftSpeed(int x) { // chnages left speed by x amount
  LeftSpeed = LeftSpeed + x;
}

void setLeftDir(char dir) { // sets left direction to clockwise or anti-clockwise, C for clockwise A for anti-clockwise.
  if (dir == 'C') {
    in3Val = "HIGH";
    in4Val = "LOW";
  } else if (dir == 'A') {
    in3Val = "LOW";
    in4Val = "HIGH";
  } else {
    Serial.println("Error - Left dir is not C or A");
  }
}



void MoveRightMotor() {
  analogWrite(enA, RightSpeed);
}

void MoveLeftMotor() {
  analogWrite(enB, LeftSpeed);
}


void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(pot, input);
  pinMode(limSwitch, input)

  // Set initial rotation direction
  RightDefaultState();
  LeftDefaultState();
  goForwards();
}

void loop() {
  potVal = analogRead(pot);
  limSwitchVal = digitalRead(limSwitch);
  int turningRatio = map(potVal, 0, 1023, -255, 255);

  if (limSwitchVal) {
    if (dir == 1) {
      dir = 2;
    }
    else if (dir == 2) {
      dir = 3;
    }
    else {
      dir = 1;

    }
  }

  if (dir ==  2)
    analogWrite(enA, 0);
  analogWrite(enB, 0);
}
else if (dir == 1) {
  turningRatio = map(turningRatio, -255, 255, 0, 255)
  analogWrite(enA, turningRatio);
  analogWrite(enB, turningRatio);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
else if (dir == 3) {
  turningRatio = map(turningRatio, -255, 255, 0, 255)
  analogWrite(enA, turningRatio);
  analogWrite(enB, turningRatio);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
}
