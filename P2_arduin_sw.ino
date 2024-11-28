//pin assignment - Common cathode for the 3 individual digits on 3*sevensegment display
const int DIGIT1 = 11;
const int DIGIT2 = 12;
const int DIGIT3 = 13;

//pin assignment - decimal point
const int DM_POINT = 6;

//pin assignment - binary values for digital output to BCD-encoder
const int BCD_A = 2;
const int BCD_B = 3;
const int BCD_C = 4;
const int BCD_D = 5;

//pin assignment - function selection
const int FUNCTION_1 = 7;
const int FUNCTION_2 = 8;
const int FUNCTION_3 = 9;
const int FUNCTION_4 = 10;

const int WAIT_TIME_MS = 10;

const int R1_LOW = 326;
const int U_REF = 5;

int hundratal = 0, tiotal=0, ental=0;
unsigned int counter = 0;

int fkn1 = 0;
int fkn2 = 0;
int fkn3 = 0;
int fkn4 = 0;
int function_select = 0;
int dp1 = 0, dp2 = 0, dp3 = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("starting program");
  
  pinMode(DIGIT1, OUTPUT);
  pinMode(DIGIT2, OUTPUT);
  pinMode(DIGIT3, OUTPUT);
  
  pinMode(DM_POINT, OUTPUT);

  pinMode(BCD_A, OUTPUT);
  pinMode(BCD_B, OUTPUT);
  pinMode(BCD_C, OUTPUT);
  pinMode(BCD_D, OUTPUT);

  pinMode(FUNCTION_1, INPUT);
  pinMode(FUNCTION_2, INPUT);
  pinMode(FUNCTION_3, INPUT);
  pinMode(FUNCTION_4, INPUT);

  //all digits off from start
  digitalWrite(DIGIT1, HIGH);
  digitalWrite(DIGIT2, HIGH);
  digitalWrite(DIGIT3, HIGH);
  digitalWrite(DM_POINT, HIGH);
}

void loop() {
  fkn1 = digitalRead(FUNCTION_1);
  fkn2 = digitalRead(FUNCTION_2);
  fkn3 = digitalRead(FUNCTION_3);
  fkn4 = digitalRead(FUNCTION_4);
  //Concatinate to one 4-bit word
  function_select = ((fkn4 << 3)) | (fkn3 << 2) | (fkn2 << 1) | (fkn1 << 0);

  switch (function_select) {
    //Voltage - low range
    case 0b0001:
      counter = (unsigned int)map(analogRead(A0),0,1023,0,500);
      dp1 = HIGH;
      dp2 = LOW;
      dp3 = LOW;
      break;
    case 0b0010:
      counter = 2;
      dp1 = LOW;
      dp2 = LOW;
      dp3 = LOW;
      break;
    //Resistance - low range
    case 0b0100:
      float U_in = map(analogRead(A2),0,1023,0,500);
      U_in = U_in/100;
      unsigned int r2 = (unsigned int)(U_in*R1_LOW)/(U_REF-U_in);
      //int r2 = (analogRead(A2));
      Serial.print("U_in: ");Serial.print(U_in);
      Serial.print(" r2: "); Serial.println(r2);
      counter = r2;
      dp1 = LOW;
      dp2 = LOW;
      dp3 = LOW;
      break;
    case 0b1000:
      counter = 8;
      dp1 = LOW;
      dp2 = LOW;
      dp3 = LOW;
      break;
    default:
      counter++;
      dp1 = LOW;
      dp2 = LOW;
      dp3 = LOW;
      break;
  }
  
  
  hundratal = (counter / 100) & 0xF; // Hundratal i BCD

  // Accessa och styra GPIO med enskilda bitar från hundratal
  digitalWrite(BCD_A, (hundratal >> 0) & 1); // Bit 0 av hundratal till GPIO 2
  digitalWrite(BCD_B, (hundratal >> 1) & 1); // Bit 1 av hundratal till GPIO 3
  digitalWrite(BCD_C, (hundratal >> 2) & 1); // Bit 2 av hundratal till GPIO 4
  digitalWrite(BCD_D, (hundratal >> 3) & 1); // Bit 3 av hundratal till GPIO 5
  digitalWrite(DM_POINT, dp1);
  digitalWrite(DIGIT1, LOW);
  delay(WAIT_TIME_MS);
  digitalWrite(DM_POINT, LOW);
  digitalWrite(DIGIT1, HIGH);

  tiotal = ((counter / 10) % 10)& 0xF; // Hundratal i BCD

  // Accessa och styra GPIO med enskilda bitar från hundratal
  digitalWrite(BCD_A, (tiotal >> 0) & 1); // Bit 0 av hundratal till GPIO 2
  digitalWrite(BCD_B, (tiotal >> 1) & 1); // Bit 1 av hundratal till GPIO 3
  digitalWrite(BCD_C, (tiotal >> 2) & 1); // Bit 2 av hundratal till GPIO 4
  digitalWrite(BCD_D, (tiotal >> 3) & 1); // Bit 3 av hundratal till GPIO 5
  digitalWrite(DM_POINT, dp2);
  digitalWrite(DIGIT2, LOW);
  delay(WAIT_TIME_MS);
  digitalWrite(DM_POINT, LOW);
  digitalWrite(DIGIT2, HIGH);
  
  ental = (counter % 10) & 0xF; // Hundratal i BCD

  // Accessa och styra GPIO med enskilda bitar från hundratal
  digitalWrite(BCD_A, (ental >> 0) & 1); // Bit 0 av hundratal till GPIO 2
  digitalWrite(BCD_B, (ental >> 1) & 1); // Bit 1 av hundratal till GPIO 3
  digitalWrite(BCD_C, (ental >> 2) & 1); // Bit 2 av hundratal till GPIO 4
  digitalWrite(BCD_D, (ental >> 3) & 1); // Bit 3 av hundratal till GPIO 5
  digitalWrite(DM_POINT, dp3);
  digitalWrite(DIGIT3, LOW);
  delay(WAIT_TIME_MS);
  digitalWrite(DM_POINT, LOW);
  digitalWrite(DIGIT3, HIGH);

}
