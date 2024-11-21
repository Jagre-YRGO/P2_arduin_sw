//Common cathode for the 3 individual digits on 3*sevensegment display
const int DIGIT1 = 11;
const int DIGIT2 = 12;
const int DIGIT3 = 13;

//binary values for digital output to BCD-encoder
const int BCD_A = 2;
const int BCD_B = 3;
const int BCD_C = 4;
const int BCD_D = 5;

const int WAIT_TIME_MS = 10;

int hundratal = 0, tiotal=0, ental=0;
int counter = 0;

void setup() {
  pinMode(DIGIT1, OUTPUT);
  pinMode(DIGIT2, OUTPUT);
  pinMode(DIGIT3, OUTPUT);
  
  pinMode(BCD_A, OUTPUT);
  pinMode(BCD_B, OUTPUT);
  pinMode(BCD_C, OUTPUT);
  pinMode(BCD_D, OUTPUT);

  //all digits off from start
  digitalWrite(DIGIT1, HIGH);
  digitalWrite(DIGIT2, HIGH);
  digitalWrite(DIGIT3, HIGH);
}

void loop() {
  hundratal = (counter / 100) & 0xF; // Hundratal i BCD

  // Accessa och styra GPIO med enskilda bitar från hundratal
  digitalWrite(BCD_A, (hundratal >> 0) & 1); // Bit 0 av hundratal till GPIO 2
  digitalWrite(BCD_B, (hundratal >> 1) & 1); // Bit 1 av hundratal till GPIO 3
  digitalWrite(BCD_C, (hundratal >> 2) & 1); // Bit 2 av hundratal till GPIO 4
  digitalWrite(BCD_D, (hundratal >> 3) & 1); // Bit 3 av hundratal till GPIO 5
  digitalWrite(DIGIT1, LOW);
  delay(WAIT_TIME_MS);
  digitalWrite(DIGIT1, HIGH);

  tiotal = ((counter / 10) % 10)& 0xF; // Hundratal i BCD

  // Accessa och styra GPIO med enskilda bitar från hundratal
  digitalWrite(BCD_A, (tiotal >> 0) & 1); // Bit 0 av hundratal till GPIO 2
  digitalWrite(BCD_B, (tiotal >> 1) & 1); // Bit 1 av hundratal till GPIO 3
  digitalWrite(BCD_C, (tiotal >> 2) & 1); // Bit 2 av hundratal till GPIO 4
  digitalWrite(BCD_D, (tiotal >> 3) & 1); // Bit 3 av hundratal till GPIO 5
  digitalWrite(DIGIT2, LOW);
  delay(WAIT_TIME_MS);
  digitalWrite(DIGIT2, HIGH);
  
  ental = (counter % 10) & 0xF; // Hundratal i BCD

  // Accessa och styra GPIO med enskilda bitar från hundratal
  digitalWrite(BCD_A, (ental >> 0) & 1); // Bit 0 av hundratal till GPIO 2
  digitalWrite(BCD_B, (ental >> 1) & 1); // Bit 1 av hundratal till GPIO 3
  digitalWrite(BCD_C, (ental >> 2) & 1); // Bit 2 av hundratal till GPIO 4
  digitalWrite(BCD_D, (ental >> 3) & 1); // Bit 3 av hundratal till GPIO 5
  digitalWrite(DIGIT3, LOW);
  delay(WAIT_TIME_MS);
  digitalWrite(DIGIT3, HIGH);

  counter++;
}
