// VIVAT INNOVATIONS ARDUINO KODE

// definerer pinNummer for LED_lyset for varm-kaldt lek
int lys1 = 2;
int lys2 = 3;
int lys3 = 4;
int lys4 = 5;
int lysvib = 6;  // vibrasjonslyset

// avstandsmaaleren
const int echoPin = 9;   // setter av pin for echo av avstandsmaaleren
const int trigPin = 10;  // Setter av pin for trig av avstandsmaaleren
long duration;           //definerer angittmal
int distance;            // definerer distanse

// piezo
const int buzzer = 11;  //buzzer pin

//vibrasjonssensor
int shocksensor = 8;        //input for aa faa info om den blir ristet paa
bool shocksensorstate = 0;  //ja eller nei

void setup() {
  //pinmode avstandsmaaleren
  pinMode(trigPin, OUTPUT);  // trigpin som output for aa sende ut lyd
  pinMode(echoPin, INPUT);   // tar imot echo // gjenstand paa avstand

  //pinmode LED for monitoren
  pinMode(lys1, OUTPUT);
  pinMode(lys2, OUTPUT);
  pinMode(lys3, OUTPUT);
  pinMode(lys4, OUTPUT);
  pinMode(lysvib, OUTPUT);

  //pinmode for piezo
  pinMode(buzzer, OUTPUT);

  //pinmode for vibrasjonssensor
  pinMode(shocksensor, INPUT);
  shocksensorstate = digitalRead(shocksensor);

  //for aa printe ut
  Serial.begin(9600);
}

void loop() {
  //Resetter avstandsmaaleren
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // setter trigpin paa maks state i 10 mikrosekunder
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Leser echopin, og returnerer tiden på lydbolgen i mikrosekunder
  duration = pulseIn(echoPin, HIGH);

  // kalkulerer avstand
  distance = duration * 0.034 / 2;

  // printer avstand i serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);


  //if sjekk for ulike avstand -- ulike LED-lys som lyser opp
  if (distance < 200 && distance > 0) {
    digitalWrite(lys1, HIGH);
  }

  if (distance < 150 && distance > 0) {
    digitalWrite(lys2, HIGH);
  }
  if (distance < 100 && distance > 0) {
    digitalWrite(lys3, HIGH);
  }

  if (distance < 50 && distance > 0) {
      digitalWrite(lys4, HIGH);
    //naar alle 4 lysene lyser opp (betyr noe er naerme nokk) vil vi vite om prototypen sanser vibrasjon for aa vite at noe dulter bort i den
      if (shocksensorstate == 1) {
        Serial.println("Vibrerer");
        digitalWrite(lysvib, HIGH);
        delay(1000);
        tone(buzzer, 1000);  // sender 1KHz lyd signal i 1 sek
        delay(1000);
        noTone(buzzer);  // stopper lyd
        delay(1000);
        shocksensorstate = 0;
        } 
        else{
        shocksensorstate = digitalRead(shocksensor);
        Serial.println("ikke naa lenger");
      }
  }

  //skrur av lyset hvis avstandsmaaleren ikke detekter noe på spesifikke avstander
  if (distance > 200) {
    digitalWrite(lys1, LOW);
    digitalWrite(lys2, LOW);
    digitalWrite(lys3, LOW);
    digitalWrite(lys4, LOW);
    digitalWrite(lysvib, LOW);
  }

  if (distance > 150) {
    digitalWrite(lys2, LOW);
    digitalWrite(lys3, LOW);
    digitalWrite(lys4, LOW);
    digitalWrite(lysvib, LOW);
    Serial.print("Prover å fjerne");
  }
  if (distance > 100) {
    digitalWrite(lys3, LOW);
    digitalWrite(lys4, LOW);
    digitalWrite(lysvib, LOW);
  }
  if (distance > 50) {
    digitalWrite(lys4, LOW);
    digitalWrite(lysvib, LOW);
  }
}
