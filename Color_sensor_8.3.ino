
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


#define enA 10
#define in1 3
#define in2 5
#define enB 11
#define in3 6
#define in4 9
#define limSwitchPower 51
#define limSwitch 53
#define potentiometerPower 13
#define pot A1



int area;
int room_number;

static int ForwardSpeed = 150;
static int minSpeed = 90;
static int maxSpeed = 255;

boolean needTurn;
boolean EL; //error left - need to turn right.
boolean ER; //error right - need to turn left.
boolean EB; // error both - reverse.
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
else if(blueColor < 65 && greenColor < 95){
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
Serial.println("|BLACK||");
color2 = 0;
  }
else if(blueColor < 65 && greenColor < 95){
Serial.println("|WHITE||");
color2 = 4; 
  }
else if(blueColor < 112 && greenColor < 95){
Serial.println("|YELLOW||");
color2 = 3;
  }
else if(redColor < greenColor && redColor < blueColor && redColor < 200){
Serial.println("| RED ||");
color2 = 1;
  }
else if(blueColor < greenColor && blueColor < redColor && blueColor < 115){
Serial.println("| BLUE||");
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
if(area != color1)
ER = true;
else {
  ER = false;
}

if (area != color2)
EL = true;
else {
  EL = false;
}
  read_sensor1();
  read_sensor2();
  Serial.print("color1 is");
  Serial.println(color1);
  Serial.print("color 2 is");
  Serial.println(color2);
}
