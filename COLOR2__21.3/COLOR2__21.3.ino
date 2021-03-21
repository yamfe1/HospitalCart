
// TC1_S2_130 or TC1_S3_1200 pins wiring to Arduino
#define S0_1 2
#define S1_1 3
#define S2_1 4
#define S3_1 5
#define sensorOut_1 6

// TC1_S2_130 or TC1_S3_1200 pins wiring to Arduino
#define S0_2 8
#define S1_2 9
#define S2_2 10
#define S3_2 11
#define sensorOut_2 12

int color1 = 4; //0 = black, 1 = red, 2 = blue, 3 = yellow, 4 = white.
int color2 = 4; //0 = black, 1 = red, 2 = blue, 3 = yellow, 4 = white.

// Stores the red. green and blue colors
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

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

  Serial.begin(9600);

}

void loop() {
  read_sensor1();
  read_sensor2();
  Serial.print("color1 is ");
  Serial.println(color1);
  Serial.print("color 2 is ");
  Serial.println(color2);
}

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
