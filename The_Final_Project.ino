
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

int currentPath = 0;
int counter = 0;
int roomCnt = 0;
boolean endPoint = 0;

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
 


void move(char motor, int Speed) {
  if(motor == 'l' || motor == 'L') {  
    if(Speed == 0) { 
     analogWrite(enB, 0);
    }
    else if (Speed < 0) {
    analogWrite(enB, (Speed * -1));
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);  
  } else {
    analogWrite(enB, Speed);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW); 
   
  }

}

if(motor == 'r' || motor == 'R') {
    if(Speed == 0) {
      analogWrite(enA, 0);
    }
    else if (Speed < 0) {
    analogWrite(enA, Speed * -1);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

  } else {
    analogWrite(enA, Speed);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
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
  

}

boolean errorCorrection() { // doesn't acturally return anything meaningful rhe return is just used to break out of the function
  errorCheck();
    if(EL && ER) { // both sensors off track
    while(ER && EL) { // while both sensors are off track 
      errorCheck();
      move('l', -250);
      move('r', -250);
      if(!EL || !ER) 
      return true;
    }
  } else if(EL) { //only the left sensor is off track
     while(EL && !ER) { // while only the left sensor is off track
      errorCheck();
      move('l', 250);
      move('r', 0); 
    }
  } else if(ER) { //only the left sensor is off track
     while(!EL && ER) { // while only right sensor is off track
      errorCheck();
     move('l', 0);
     move('r', 250); 
    }
  }
}



void goForwards() {
  analogWrite(enA, 100);
  analogWrite(enB, 100);
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

if(redColor > 400){
color1 = 0;
  }
else if(blueColor < 65 && greenColor < 95 && blueColor < greenColor && blueColor < redColor){
color1 = 4; 
  }
else if(blueColor < 112 && greenColor < 95){
color1 = 3;
  }
else if(redColor < greenColor && redColor < blueColor && redColor < 200){
color1 = 1;
  }
else if(blueColor < greenColor && blueColor < redColor && blueColor < 115){
color1 = 2;
}

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
color2 = 0;
  }
else if(blueColor < 65 && greenColor < 95 && blueColor < greenColor && blueColor < redColor){
color2 = 4; 
  }
else if(blueColor < 112 && greenColor < 95){
color2 = 3;
  }
else if(redColor < greenColor && redColor < blueColor && redColor < 200){
color2 = 1;
  }
else if(blueColor < greenColor && blueColor < redColor && blueColor < 115){
color2 = 2;
}

}// end void

void Path() {
  if(!endPoint) {
  if(counter == 0){
    if(color1 == area || color2 == area){
      currentPath = area; // update the current path
      counter = 1;
    }
  //}
 // if(counter == 1){
 //   if(color1 == 0 || color2 == 0){
 //     roomCnt += 1;
 //       while(color1 == 0 && color2 == 0){
 //         goForwards();
 //       }
 //   }
 // }
 // if(roomCnt == room_number){
 //   currentPath == 0; // update the current path
 //   counter = 2;
 // }
 // if(counter == 2){
 //   if(color1 == 1 && color2 == 1){
 //     move('r',0);
 //     move('l', 0);
 //     counter = 3;
 //     endPoint = true;
 //     while(digitalRead(9) == LOW) {
 //     }
 //  }
    }
  }
}

//void Back() {

//   if(counter == 0){
//    if(color1 == 1 && color2 == 1){
//      move('r',0);
//      move('l', 0);
//    }
//  if(counter == 1){
//     if(color1 == 0 || color2 == 0){
//        roomCnt -= 1;
//        while(color1 == 0 && color2 == 0){
//          goForwards();
//        }
//  }
//  }
//   if(roomCnt == 0){
//    currentPath == 0; // update the current path
//    counter = 0;
//   }
//  if(roomCnt == 2){
//   currentPath == 0; // update the current path
//      if(color1 == area || color2 == area){
//        currentPath == area; // update the current path
//        counter = 1;
//      }
//  }
//  if(counter == 3){
//      while (color1 != 0 && color2 != 0){
//    move('r', 255);
//    move('l', 0);
//  }
//  counter = 2;
//  }  
//}

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

  pinMode(9, INPUT);

 Serial.begin(9600);
UI();
}

void loop() {

goForwards();

errorCheck();
if(ER || EL)
errorCorrection();

Path();

//if(digitalRead(9) == HIGH){
//  Back(); 
//}

}
