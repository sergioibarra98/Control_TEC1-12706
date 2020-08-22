#define SENSOR 0          //Pin
#define N 5               //Average of temperature
#define TEMP_AVG 112      //22ºC * 255 / 50
#define DESVIATION 30     //6ΔºC * 255 / 50
#define ELONGATION 3      //Updating of the output
#define FRECUENCY 100     //Hz
#define TIMER 10          //Seconds

//Variables
int elongation_i = 1, vout = TEMP_AVG - DESVIATION, vread;

//Read the temperature N times and return the average
int readTemp() {
  int temp = 0, temp_k1 = 0;
  for (int i = 0; i < N ; i++) {
    temp = analogRead(SENSOR);
    temp += temp_k1;
    temp_k1 = temp;
  }
  return (temp / N);
}

void setup() {
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  randomSeed(98);

  Serial.print(TIMER * FRECUENCY);
  Serial.print(" Samples | ");
  Serial.print(1 * 1000 / FRECUENCY);
  Serial.println(" sampling rate");

  //Generate a PRBS sequence
  for (int ts = 0; ts < TIMER * FRECUENCY; ts++) {
    if (elongation_i == ELONGATION) {
      switch (random(0, 2)) {
        case 0: vout = TEMP_AVG - DESVIATION; break;
        case 1: vout = TEMP_AVG + DESVIATION; break;
        default: vout = -1; break;
      }
      elongation_i = 0;
    }

    elongation_i++;

    analogWrite(9, vout);
    vread = readTemp();
    Serial.print(vout);
    Serial.print(" ");
    Serial.println(vread);

    delay(1 * 1000 / FRECUENCY);
  }

  vout = 0;
  analogWrite(9, vout);
  Serial.println(vout);
  Serial.println("--------------------------------------");
}

void loop() {
}
