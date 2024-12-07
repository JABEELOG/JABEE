// Define pin connections for ESP8266
#define S0 D1         // GPIO 5 (D1 on NodeMCU) white
#define S1 D2         // GPIO 4 (D2 on NodeMCU) black
#define S2 D3         // GPIO 0 (D3 on NodeMCU) blue
#define S3 D5         // GPIO 14 (D5 on NodeMCU) purple
#define sensorOut D6  // GPIO 12 (D5 on NodeMCU) green

// Color sensor Initialization
int red = 0;
int green = 0;
int blue = 0;

// Proximity sensor Initialization
int capacitiveSensor = 2;    // Define pin for capacitive sensor
int inductiveSensor = 15;    // Define pin for inductive sensor

void setup() {
  Serial.begin(115200);

  // Set the pins as OUTPUT/INPUT
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Set frequency scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Serial monitor messages
  Serial.println("Color sensor initialized!");
  Serial.println("NO MATERIAL DETECTED!!!");

  // Capacitive and inductive sensor INPUT/OUTPUT
  pinMode(capacitiveSensor, INPUT);  // Set capacitive sensor as input
  pinMode(inductiveSensor, INPUT);   // Set inductive sensor as input
}

void loop() {
  colorSensor();      // Read color sensor values
  proximitySensor();  // Read proximity sensor values
}

void colorSensor() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  red = pulseIn(sensorOut, LOW);
  delay(100);

  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  green = pulseIn(sensorOut, LOW);
  delay(100);

  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blue = pulseIn(sensorOut, LOW);

  // Printing the RGB frequency values to the Serial Monitor
  Serial.print("R = ");
  Serial.print(red);
  Serial.print(" G = ");
  Serial.print(green);
  Serial.print(" B = ");
  Serial.println(blue);
}

void proximitySensor() {
  // Read the data from the capacitive and inductive sensors
  int capacitiveState = digitalRead(capacitiveSensor); // Use digitalRead for reading input state
  int inductiveState = digitalRead(inductiveSensor);   // Use digitalRead for reading input state

  // Check color sensor values and capacitive sensor together
  if (red < 100 && green < 80 && blue < 70 && capacitiveState == HIGH) {
    Serial.println("PAPER DETECTED!!!");
  } else if (inductiveState == LOW && capacitiveState == HIGH) {
    Serial.println("METAL DETECTED!!!");
  } else if (inductiveState == HIGH && capacitiveState == HIGH) {
    Serial.println("PLASTIC DETECTED!!!");
  } else {
    Serial.println("NO MATERIAL DETECTED!!!");
  }

  delay(500);  // Wait for half a second before checking again
}
