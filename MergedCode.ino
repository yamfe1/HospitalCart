
// TC1_S2_130 or TC1_S3_1200 pins wiring to Arduino
#define S0_1 53
#define S1_1 51
#define S2_1 49
#define S3_1 47
#define sensorOut_1 45

// TC1_S2_130 or TC1_S3_1200 pins wiring to Arduino
#define S0_2 41
#define S1_2 39
#define S2_2 37
#define S3_2 35
#define sensorOut_2 33

#define enA 2
#define in1 3
#define in2 4
#define enB 7
#define in3 5
#define in4 6
#define myLimSwitch 10
#define limSwitchPower 13



int area;
int room_number;

static int ForwardSpeed = 150;
static int minSpeed = 90;
static int maxSpeed = 255;

boolean needTurn;
boolean EL = 0; //error left - need to turn right.
boolean ER = 0; //error right - need to turn left.
boolean inError;
int errors[10];

int color1 = 4; //0 = black, 1 = red, 2 = blue, 3 = yellow, 4 = white.
int color2 = 4; //0 = black, 1 = red, 2 = blue, 3 = yellow, 4 = white.

int LeftSpeed; //motor speed.
char LeftDirection; //motor direction. C for clockwise A for anti-clockwise.
String in1Val; // in1Val based off of other parameters.
String in2Val; // in2Val based off of other parameters.
 
int RightSpeed; //motor1 speed.
char RightDirection; //motor direction. C for clockwise A for anti-clockwise.
String in3Val; // in1Val based off of other parameters.
String in4Val; // in2Val based off of other parameters.



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
}

void errorCheck() {//prototype
  read_sensor1();
  read_sensor2();
  if (area != color1) {
    ER = true;
  } else {
    ER = false;
  }
  if (area != color2) {
    EL = true;
  } else {
    EL = false;
  }
  
  Serial.print("EL is   ");
  Serial.print(EL);
  Serial.print("    ER is   ");
  Serial.println(ER);
}

boolean errorCorrection() { // doesn't acturally return anything meaningful rhe return is just used to break out of the function
  errorCheck();
    if(EL && ER) { // both sensors off track
         Serial.println("correcting ER && EL");
    while(ER && EL) { // while both sensors are off track 
      errorCheck();
      move('l', -250);
      move('r', -250);
      if(!EL || !ER) 
      return true;
    }
  } else if(EL) { //only the left sensor is off track
       Serial.println("correcting EL");
     while(EL && !ER) { // while only the left sensor is off track
      errorCheck();
      move('l', 250);
      move('r', 0); 
    }
  } else if(ER) { //only the left sensor is off track
    Serial.println("correcting ER");
     while(!EL && ER) { // while only right sensor is off track
      errorCheck();s
     move('l', 0);
     move('r', 250); 
    }
  }
}

 void UI(){
Serial.println("Select An Area {1 - 3}");
Serial.println("Red - 1");
Serial.println("Blue - 2");
Serial.println("Green - 3");
 while (Serial.available() == 0) {} 
 area = Serial.parseInt();
 
 
if (area == 1){
  Serial.println("");
  Serial.println("Red Route Selected");
  delay(1000);
  Serial.println("");
  Serial.println("Select A Room Number {1 - 3}");
  Serial.println("First Room - 1");
  Serial.println("Second Room - 2");
  Serial.println("Third Room - 3");
  while (Serial.available() == 0) {} 
  room_number = Serial.parseInt();
    if (room_number == 1){
      Serial.println("");
      Serial.println("First Room Selected");
    }
    if (room_number == 2){
      Serial.println("");
      Serial.println("Second Room Selected");
    }
     if (room_number == 3){
      Serial.println("");
      Serial.println("Third Room Selected");
    }
    Serial.println("");
    Serial.println("");
    delay(5000);
}
if (area == 2){
  Serial.println("");
  Serial.println("Blue Route Selected");
  delay(1000);
  Serial.println("");
  Serial.println("Select A Room Number {1 - 3}");
  Serial.println("First Room - 1");
  Serial.println("Second Room - 2");
  while (Serial.available() == 0) {} 
  room_number = Serial.parseInt();
    if (room_number == 1){
      Serial.println("");
      Serial.println("First Room Selected");
    }
    if (room_number == 2){
      Serial.println("");
      Serial.println("Second Room Selected");
    }
    Serial.println("");
    Serial.println("");
    delay(5000);
}
if (area == 3){
  Serial.println("");
  Serial.println("Green Route Selected");
  delay(1000);
  Serial.println("");
  Serial.println("Select A Room Number {1 - 3}");
  Serial.println("First Room - 1");
  Serial.println("Second Room - 2");
  Serial.println("Third Room - 3");
  while (Serial.available() == 0) {} 
  room_number = Serial.parseInt();
    if (room_number == 1){
      Serial.println("");
      Serial.println("First Room Selected");
    }
    if (room_number == 2){
      Serial.println("");
      Serial.println("Second Room Selected");
    }
     if (room_number == 3){
      Serial.println("");
      Serial.println("Third Room Selected");
    }
    Serial.println("");
    Serial.println("");
    delay(5000);
}
 }
 
 


void goForwards() {
  analogWrite(enA, 255);
  analogWrite(enB, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.println("moving");
}
  


// Stores the red. green and blue colors
int redColor = 0;
int greenColor = 0;
int blueColor = 0;


void read_sensor1(){
 // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2_1,LOW);
  digitalWrite(S3_1,LOW);
  
  // Reading the output frequency
  redColor = pulseIn(sensorOut_1, LOW);
  
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2_1,HIGH);
  digitalWrite(S3_1,HIGH);
  
  // Reading the output frequency
  greenColor = pulseIn(sensorOut_1, LOW);

 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2_1,LOW);
  digitalWrite(S3_1,HIGH);
  
  // Reading the output frequency
  blueColor = pulseIn(sensorOut_1, LOW);

  
Serial.println("|COLOR||sensor |   R   |   G   |   B    ");

if(redColor > 400){
Serial.print("|BLACK||");
color1 = 0;
  }
else if(blueColor < 65 && greenColor < 95 && blueColor < greenColor && blueColor < redColor){
Serial.print("|WHITE||");
color1 = 4; 
  }
else if(blueColor < 112 && greenColor < 95){
Serial.print("|YELLOW||");
color1 = 3;
  }
else if(redColor < greenColor && redColor < blueColor && redColor < 200){
Serial.print("| RED ||");
color1 = 1;
  }
else if(blueColor < greenColor && blueColor < redColor && blueColor < 115){
Serial.print("| BLUE||");
color1 = 2;
}
Serial.print("   1   |   ");
// Printing the RED (R) value
Serial.print(redColor);
  delay(100);
  Serial.print("     ");
   // Printing the GREEN (G) value  
  Serial.print(greenColor);
  delay(100);
  Serial.print("     ");
  // Printing the BLUE (B) value 
  Serial.print(blueColor);
  delay(100);
  Serial.print("      ");

Serial.println("");

}// end void



void read_sensor2(){
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2_2,LOW);
  digitalWrite(S3_2,LOW);
  
  // Reading the output frequency
  redColor = pulseIn(sensorOut_2, LOW);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2_2,HIGH);
  digitalWrite(S3_2,HIGH);
  
  // Reading the output frequency
  greenColor = pulseIn(sensorOut_2, LOW);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2_2,LOW);
  digitalWrite(S3_2,HIGH);
  
  // Reading the output frequency
  blueColor = pulseIn(sensorOut_2, LOW);
  
if(redColor > 400){
Serial.print("|BLACK||");
color2 = 0;
  }
else if(blueColor < 65 && greenColor < 95 && blueColor < greenColor && blueColor < redColor){
Serial.print("|WHITE||");
color2 = 4; 
  }
else if(blueColor < 112 && greenColor < 95){
Serial.print("|YELLOW||");
color2 = 3;
  }
else if(redColor < greenColor && redColor < blueColor && redColor < 200){
Serial.print("| RED ||");
color2 = 1;
  }
else if(blueColor < greenColor && blueColor < redColor && blueColor < 115){
Serial.print("| BLUE||");
color2 = 2;
}
Serial.print("   2   |   ");
// Printing the RED (R) value
Serial.print(redColor);
  delay(100);
  Serial.print("     ");
   // Printing the GREEN (G) value  
  Serial.print(greenColor);
  delay(100);
  Serial.print("     ");
  // Printing the BLUE (B) value 
  Serial.print(blueColor);
  delay(100);
  Serial.print("      ");

Serial.println("");
Serial.println("");

}// end void

void setup() {
  // Setting the outputs
  pinMode(S0_1, OUTPUT);
  pinMode(S1_1, OUTPUT);
  pinMode(S2_1, OUTPUT);
  pinMode(S3_1, OUTPUT);
  
  // Setting the 1sensorOut_1 as an input
  pinMode(sensorOut_1, INPUT);
  
 
  // Setting the outputs
  pinMode(S0_2, OUTPUT);
  pinMode(S1_2, OUTPUT);
  pinMode(S2_2, OUTPUT);
  pinMode(S3_2, OUTPUT);
  
  // Setting the sensorOut_1 as an input
  pinMode(sensorOut_2, INPUT);

 // Setting frequency scaling to 20%
  digitalWrite(S0_1,HIGH);
  digitalWrite(S1_1,LOW);
  digitalWrite(S0_2,HIGH);
  digitalWrite(S1_2,LOW);

 pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
 
  // Begins serial communication
  Serial.begin(9600);

  UI();
  Serial.print("area is ");
  Serial.println(area);
}

void loop() {

goForwards();

errorCheck();
if(ER || EL)
errorCorrection();

  Serial.print("color1 is ");
  Serial.println(color1);
  Serial.print("color 2 is ");
  Serial.println(color2);
  Serial.print("EL is  ");
  Serial.print(EL);
  Serial.print("       ER is  ");
  Serial.println(ER);
}
