#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define global variables and arrays
int gateInput1, gateInput2, i, j, k;
bool inputTable[4][2] = {0, 0, 0, 1, 1, 0, 1, 1}; //To input the logical value
int outputTable[5][4] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5}; //Initializing the output array where output logical values will be stored
bool foundMatch, database[4][5] = {0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0}; //Database of all logic gate ICs output
String icName, icModel; // To store the IC name & model

void setup() {

  Serial.begin(9600); // Initialize the serial communication

  pinMode(A0, INPUT);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  
  // Initialize the LCD display with 16 columns and 2 rows
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PRESS BUTTON TO");
  lcd.setCursor(0, 1);
  lcd.print("SELECT TEST MODE");
  delay (1000);

  lcd.clear(); // Clear the LCD screen
  lcd.setCursor(0, 0);
  lcd.print("B1 NOT B2 NOR");
  lcd.setCursor(0, 1);
  lcd.print("B3 ANDORXORNAND");
  delay (1000);

  if (analogRead(A0) < 100) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Short Circuit");
        Serial.println(analogRead(A0));
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Open Circuit");
        Serial.println(analogRead(A0));
        }
    delay (1000);

}

void loop() 
{
  //MODE 1 NOT B1
  if(digitalRead(A1) == LOW)
  {
    pinMode(13, OUTPUT);
    pinMode(12, INPUT);
    pinMode(11, OUTPUT);
    pinMode(10, INPUT);
    pinMode(9, OUTPUT);
    pinMode(8, INPUT);
    pinMode(7, OUTPUT);
    pinMode(6, INPUT);
    pinMode(5, OUTPUT);
    pinMode(4, INPUT);
    pinMode(3, OUTPUT);
    pinMode(2, INPUT);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Testing......");
    delay(250);
    lcd.clear();

    digitalWrite(3, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(13, HIGH);

    int count=0;

    if(digitalRead(12) == LOW)
    {
      lcd.setCursor(0,0);
      lcd.print("1.NOT");
      delay(100);
      count++;
    }
    else
    {
      lcd.setCursor(0,0);
      lcd.print("1.BAD");
      delay(100);
    }
    if(digitalRead(10) == LOW)
    {
      lcd.setCursor(5,0);
      lcd.print("2.NOT");
      delay(100);
      count++;
    }
    else
    {
      lcd.setCursor(5,0);
      lcd.print("2.BAD");
      delay(100);
    }
    if(digitalRead(8) == LOW)
    {
      lcd.setCursor(10,0);
      lcd.print("3.NOT");
      delay(100);
      count++;
    }
    else
    {
      lcd.setCursor(10,0);
      lcd.print("3.BAD");
      delay(100);
    }
    if(digitalRead(6) == LOW)
    {
      lcd.setCursor(0,1);
      lcd.print("4.NOT");
      delay(100);
      count++;
    }
    else
    {
      lcd.setCursor(0,1);
      lcd.print("4.BAD");
      delay(100);
    }
    if(digitalRead(4) == LOW)
    {
      lcd.setCursor(5,1);
      lcd.print("5.NOT");
      delay(100);
      count++;
    }
    else
    {
      lcd.setCursor(5,1);
      lcd.print("5.BAD");
      delay(100);
    }
    if(digitalRead(2) == LOW)
    {
      lcd.setCursor(10,1);
      lcd.print("6.NOT");
      delay(100);
      count++;
    }
    else
    {
      lcd.setCursor(10,1);
      lcd.print("6.BAD");
      delay(100);
    }
    delay(1000);

    if(count==6)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("IC 7404");
      lcd.setCursor(0, 1);
      lcd.print("ALL GATES ARE OK");
      delay(1000);
    }
    else
    {
      lcd.setCursor(0, 0); // Set cursor to the second line
      lcd.clear();
      lcd.print("ALL GATES ARE");
      lcd.setCursor(0, 1);
      lcd.print("NOT FUNCTIONAL");
      delay(1000);
    }
  }

  //MODE 2 NOR B2
  else if(digitalRead(A2) == LOW)
  {
  // Configure various pins as input and output
    pinMode(13, INPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(10, INPUT);
    pinMode(9, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(7, INPUT);
    pinMode(6, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(4, INPUT);
    pinMode(3, OUTPUT);
    pinMode(2, OUTPUT);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Testing......");
  delay(250);
  lcd.clear();

  
  for (i = 0; i < 4; i++) {
    // Testing gate 1
    digitalWrite(11, inputTable[i][0]);
    digitalWrite(12, inputTable[i][1]);
    gateInput1 = digitalRead(13);
    outputTable[i][0] = gateInput1;

    // Testing gate 2
    digitalWrite(9, inputTable[i][0]);
    digitalWrite(8, inputTable[i][1]);
    gateInput2 = digitalRead(10);
    outputTable[i][1] = gateInput2;

    // Testing gate 3
    digitalWrite(6, inputTable[i][0]);
    digitalWrite(5, inputTable[i][1]);
    gateInput1 = digitalRead(7);
    outputTable[i][2] = gateInput1;

    // Testing gate 4
    digitalWrite(3, inputTable[i][0]);
    digitalWrite(2, inputTable[i][1]);
    gateInput2 = digitalRead(4);
    outputTable[i][3] = gateInput2;
  }

  for (k = 0; k < 4; k++) {
    for (i = 0; i < 5; i++) {
      foundMatch = true;
      for (j = 0; j < 4; j++) {
        // Compare outputTable values with the database
        if (outputTable[j][k] != database[j][i]) {
          foundMatch = false;
          break;
        }
      }
      if (foundMatch) {
        outputTable[4][k] = i; // Store the matching result
      }
    }
  }

 for (i = 0; i < 4; i++) {
    lcd.setCursor((i % 2) * 7, i / 2); // Set the LCD cursor position
    lcd.print(i+1); // Print gate number
    lcd.print('.'); // Add a period to separate the gate number and IC name
    switch (outputTable[4][i]) {
      case 4:
        icName = "NOR";
        break;
      default:
        icName = "BAD";
        break;
    }
    lcd.print(icName + "  ");
    delay(100);
}

  delay(1000);
  // Check if all IC names are the same
  bool allICsSame = true;
  for (i = 1; i < 4; i++) {
    if (outputTable[4][i] != outputTable[4][0]) {
      allICsSame = false;
      break;
    }
  }

  // Display a message based on whether all IC names are the same or not
  if (allICsSame) { //Showing the IC models
    if(icName=="NOR"){
    lcd.setCursor(0, 0); // Set cursor to the second line
    lcd.clear();
    lcd.print("IC 7402");
    lcd.setCursor(0,1);
    lcd.print("ALL GATES ARE OK");
    }else if(icName=="BAD"){
    lcd.setCursor(0, 0); // Set cursor to the second line
    lcd.clear();
    lcd.print("BAD IC OR NO");
    lcd.setCursor(0, 1); // Set cursor to the second line
    lcd.print("IC IS CONNECTED");
    } 
    delay(1000);
  }
  else {
    lcd.setCursor(0, 0); // Set cursor to the second line
    lcd.clear();
    lcd.print("ALL GATES ARE");
    lcd.setCursor(0, 1);
    lcd.print("NOT FUNCTIONAL");
    delay(1000);
    }
  }

  //MODE 3 AND OR NAND XOR
  else if(digitalRead(A3) == LOW)
  {
  // Configure various pins as input and output
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, INPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(8, INPUT);
    pinMode(7, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(5, INPUT);
    pinMode(4, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(2, INPUT);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Testing......");
  delay(250); 
  lcd.clear();

  
  for (i = 0; i < 4; i++) {
    // Testing gate 1
    digitalWrite(13, inputTable[i][0]);
    digitalWrite(12, inputTable[i][1]);
    gateInput1 = digitalRead(11);
    outputTable[i][0] = gateInput1;

    // Testing gate 2
    digitalWrite(10, inputTable[i][0]);
    digitalWrite(9, inputTable[i][1]);
    gateInput2 = digitalRead(8);
    outputTable[i][1] = gateInput2;

    // Testing gate 3
    digitalWrite(7, inputTable[i][0]);
    digitalWrite(6, inputTable[i][1]);
    gateInput1 = digitalRead(5);
    outputTable[i][2] = gateInput1;

    // Testing gate 4
    digitalWrite(4, inputTable[i][0]);
    digitalWrite(3, inputTable[i][1]);
    gateInput2 = digitalRead(2);
    outputTable[i][3] = gateInput2;
  }

  for (k = 0; k < 4; k++) {
    for (i = 0; i < 5; i++) {
      foundMatch = true;
      for (j = 0; j < 4; j++) {
        // Compare outputTable values with the database
        if (outputTable[j][k] != database[j][i]) {
          foundMatch = false;
          break;
        }
      }
      if (foundMatch) {
        outputTable[4][k] = i; // Store the matching result
      }
    }
  }

 for (i = 0; i < 4; i++) {
    lcd.setCursor((i % 2) * 7, i / 2); // Set the LCD cursor position
    lcd.print(i+1); // Print gate number
    lcd.print('.'); // Add a period to separate the gate number and IC name
    switch (outputTable[4][i]) {
      case 0:
        icName = "AND";
        break;
      case 1:
        icName = "OR";
        break;
      case 2:
        icName = "NAND";
        break;
      case 3:
        icName = "XOR";
        break;
      default:
        icName = "BAD";
        break;
    }
    lcd.print(icName + "  ");
    delay(100);
}

  delay(1000);
  // Check if all IC names are the same
  bool allICsSame = true;
  for (i = 1; i < 4; i++) {
    if (outputTable[4][i] != outputTable[4][0]) {
      allICsSame = false;
      break;
    }
  }

  // Display a message based on whether all IC names are the same or not with IC MODEL
  if (allICsSame) { 
    if(icName=="AND"){
    lcd.setCursor(0, 0); // Set cursor to the second line
    lcd.clear();
    lcd.print("IC 7408");
    lcd.setCursor(0,1);
    lcd.print("ALL GATES ARE OK");
    } else if(icName=="OR"){
    lcd.setCursor(0, 0); // Set cursor to the second line
    lcd.clear();
    lcd.print("IC 7432");
    lcd.setCursor(0,1);
    lcd.print("ALL GATES ARE OK");
    } else if(icName=="NAND"){
    lcd.setCursor(0, 0); // Set cursor to the second line
    lcd.clear();
    lcd.print("IC 7400");
    lcd.setCursor(0,1);
    lcd.print("ALL GATES ARE OK");
    } else if(icName=="XOR"){
    lcd.setCursor(0, 0); // Set cursor to the second line
    lcd.clear();
    lcd.print("IC 7486");
    lcd.setCursor(0,1);
    lcd.print("ALL GATES ARE OK");
    }else if(icName=="BAD"){
    lcd.setCursor(0, 0); // Set cursor to the second line
    lcd.clear();
    lcd.print("BAD IC OR NO");
    lcd.setCursor(0, 1); // Set cursor to the second line
    lcd.print("IC IS CONNECTED");
    }
    delay(1000); 
    }
    
    else {
    lcd.setCursor(0, 0); // Set cursor to the second line
    lcd.clear();
    lcd.print("ALL GATES ARE");
    lcd.setCursor(0, 1);
    lcd.print("NOT FUNCTIONAL");
    delay(1000);
  }
  }
  
  //Or Show INFO Again
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PRESS BUTTON TO");
    lcd.setCursor(0, 1);
    lcd.print("SELECT TEST MODE");
    delay (1000);

    lcd.clear(); // Clear the LCD screen
    lcd.setCursor(0, 0);
    lcd.print("B1 NOT B2 NOR");
    lcd.setCursor(0, 1);
    lcd.print("B3 ANDORNANDXOR");
    delay (1000);

    if (analogRead(A0) < 100) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Short Circuit");
        Serial.println(analogRead(A0));
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Open Circuit");
        Serial.println(analogRead(A0));
        }
    delay (1000);
    
  }

}
