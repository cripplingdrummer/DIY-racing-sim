#define ENCODER_CLK 2
#define ENCODER_DT 3

int lastClk = HIGH;
int lastDt = HIGH;
long encoderValue = 0;

const int MAX_ENCODER = 180;
const int DEADZONE = 0;

unsigned long lastChangeTime = 0;
const int debounceDelay = 200; // microseconds (0.2 ms)

void setup() {
  pinMode(ENCODER_CLK, INPUT_PULLUP);
  pinMode(ENCODER_DT, INPUT_PULLUP);
  Serial.begin(115200);
}

void loop() {
  int currentClk = digitalRead(ENCODER_CLK);
  int currentDt  = digitalRead(ENCODER_DT);

  if (currentClk != lastClk && currentClk == LOW) {
    if (micros() - lastChangeTime > debounceDelay) {
      if (currentDt != currentClk)
        encoderValue++;
      else
        encoderValue--;

      if (encoderValue > MAX_ENCODER) encoderValue = MAX_ENCODER;
      if (encoderValue < -MAX_ENCODER) encoderValue = -MAX_ENCODER;

      int steering = map(encoderValue, -MAX_ENCODER, MAX_ENCODER, -900, 900);
      Serial.println(steering);

      lastChangeTime = micros();
    }
  }

  lastClk = currentClk;
  lastDt  = currentDt;
}
