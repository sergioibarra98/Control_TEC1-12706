#define SENSOR 0          //Pin
#define N 3               //Average of temperature
#define ELONGATION 3      //Updating of the output
#define FRECUENCY 30      //Hz
#define TIMER 10          //Seconds

int elongation_i = 1, vout[TIMER * FRECUENCY], vread[TIMER * FRECUENCY];

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
  Serial.println(" delay");

  for (int ts = 0; ts < TIMER * FRECUENCY; ts++) {
    if (elongation_i == ELONGATION) {
      switch (random(0, 2)) {
        case 0: vout[ts] = 76; break;
        case 1: vout[ts] = 179; break;
        default: vout[ts] = -1; break;
      }
      elongation_i = 0;
    } else {
      vout[ts] = vout[ts - 1];
    }

    elongation_i++;

    analogWrite(9, vout[ts]);
    vread[ts] = readTemp();
    Serial.print(vout[ts]);
    Serial.print(" ");
    Serial.println(vread[ts]);

    delay(1 * 1000 / FRECUENCY);
  }

  vout[TIMER * FRECUENCY + 1] = 0;
  analogWrite(9, vout[TIMER * FRECUENCY + 1]);
  Serial.println(vout[TIMER * FRECUENCY + 1]);
  Serial.println("--------------------------------------");

  Serial.print("\n");
  for (int ts = 0; ts < TIMER * FRECUENCY; ts++) {
    Serial.print((float)vout[ts] * 5 / 255);
    Serial.print("V | ");
    Serial.print(readTemp() * 0.47);
    Serial.println(" ºC");
  }
}

void loop() {
}
