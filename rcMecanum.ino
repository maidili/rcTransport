// === Pin Channel Receiver (PPM/RC input) ===
#define CH1_PIN 34  // X axis (kiri-kanan)
#define CH2_PIN 35  // Y axis (maju-mundur)
#define CH3_PIN 36  // Rotate (kiri-kanan)

// === Motor 1 (FL) ===
#define M1_IN1 2
#define M1_IN2 3
#define M1_PWM 4

// === Motor 2 (FR) ===
#define M2_IN1 5
#define M2_IN2 6
#define M2_PWM 7

// === Motor 3 (BL) ===
#define M3_IN1 8
#define M3_IN2 9
#define M3_PWM 10

// === Motor 4 (BR) ===
#define M4_IN1 11
#define M4_IN2 12
#define M4_PWM 13

const int PWM_MAX = 200;
const int DEADZONE = 50;

void setup() {
  Serial.begin(115200);

  // Set pin sebagai output
  pinMode(M1_IN1, OUTPUT); pinMode(M1_IN2, OUTPUT); pinMode(M1_PWM, OUTPUT);
  pinMode(M2_IN1, OUTPUT); pinMode(M2_IN2, OUTPUT); pinMode(M2_PWM, OUTPUT);
  pinMode(M3_IN1, OUTPUT); pinMode(M3_IN2, OUTPUT); pinMode(M3_PWM, OUTPUT);
  pinMode(M4_IN1, OUTPUT); pinMode(M4_IN2, OUTPUT); pinMode(M4_PWM, OUTPUT);
}

void loop() {
  int ch1 = getChannelValue(CH1_PIN); // kiri-kanan
  int ch2 = getChannelValue(CH2_PIN); // maju-mundur
  int ch3 = getChannelValue(CH3_PIN); // rotate

  Serial.print("CH1: "); Serial.print(ch1);
  Serial.print(" | CH2: "); Serial.print(ch2);
  Serial.print(" | CH3: "); Serial.println(ch3);

  moveMecanum(ch1, ch2, ch3);
  delay(20);
}

// === Fungsi utama gerak mecanum 8 arah + rotate ===
void moveMecanum(int x, int y, int rot) {
  if (abs(x) < DEADZONE && abs(y) < DEADZONE && abs(rot) < DEADZONE) {
    stopAll();
  } else if (abs(rot) > DEADZONE) {
    if (rot > 0) rotateRight();
    else rotateLeft();
  } else if (abs(x) < DEADZONE && y > DEADZONE) {
    moveForward();
  } else if (abs(x) < DEADZONE && y < -DEADZONE) {
    moveBackward();
  } else if (x > DEADZONE && abs(y) < DEADZONE) {
    moveRight();
  } else if (x < -DEADZONE && abs(y) < DEADZONE) {
    moveLeft();
  } else if (x > DEADZONE && y > DEADZONE) {
    moveForwardRight();
  } else if (x < -DEADZONE && y > DEADZONE) {
    moveForwardLeft();
  } else if (x > DEADZONE && y < -DEADZONE) {
    moveBackwardRight();
  } else if (x < -DEADZONE && y < -DEADZONE) {
    moveBackwardLeft();
  }
}

// === Fungsi-fungsi gerak dasar ===
void setMotor(int in1, int in2, int pwmPin, int speed, bool forward) {
  digitalWrite(in1, forward ? HIGH : LOW);
  digitalWrite(in2, forward ? LOW : HIGH);
  analogWrite(pwmPin, speed);
}

void stopAll() {
  analogWrite(M1_PWM, 0);
  analogWrite(M2_PWM, 0);
  analogWrite(M3_PWM, 0);
  analogWrite(M4_PWM, 0);
}

void moveForward() {
  setMotor(M1_IN1, M1_IN2, M1_PWM, PWM_MAX, true);
  setMotor(M2_IN1, M2_IN2, M2_PWM, PWM_MAX, true);
  setMotor(M3_IN1, M3_IN2, M3_PWM, PWM_MAX, true);
  setMotor(M4_IN1, M4_IN2, M4_PWM, PWM_MAX, true);
}

void moveBackward() {
  setMotor(M1_IN1, M1_IN2, M1_PWM, PWM_MAX, false);
  setMotor(M2_IN1, M2_IN2, M2_PWM, PWM_MAX, false);
  setMotor(M3_IN1, M3_IN2, M3_PWM, PWM_MAX, false);
  setMotor(M4_IN1, M4_IN2, M4_PWM, PWM_MAX, false);
}

void moveRight() {
  setMotor(M1_IN1, M1_IN2, M1_PWM, PWM_MAX, true);
  setMotor(M2_IN1, M2_IN2, M2_PWM, PWM_MAX, false);
  setMotor(M3_IN1, M3_IN2, M3_PWM, PWM_MAX, false);
  setMotor(M4_IN1, M4_IN2, M4_PWM, PWM_MAX, true);
}

void moveLeft() {
  setMotor(M1_IN1, M1_IN2, M1_PWM, PWM_MAX, false);
  setMotor(M2_IN1, M2_IN2, M2_PWM, PWM_MAX, true);
  setMotor(M3_IN1, M3_IN2, M3_PWM, PWM_MAX, true);
  setMotor(M4_IN1, M4_IN2, M4_PWM, PWM_MAX, false);
}

void moveForwardRight() {
  setMotor(M1_IN1, M1_IN2, M1_PWM, 0, true);
  setMotor(M2_IN1, M2_IN2, M2_PWM, PWM_MAX, true);
  setMotor(M3_IN1, M3_IN2, M3_PWM, PWM_MAX, true);
  setMotor(M4_IN1, M4_IN2, M4_PWM, 0, true);
}

void moveForwardLeft() {
  setMotor(M1_IN1, M1_IN2, M1_PWM, PWM_MAX, true);
  setMotor(M2_IN1, M2_IN2, M2_PWM, 0, true);
  setMotor(M3_IN1, M3_IN2, M3_PWM, 0, true);
  setMotor(M4_IN1, M4_IN2, M4_PWM, PWM_MAX, true);
}

void moveBackwardRight() {
  setMotor(M1_IN1, M1_IN2, M1_PWM, PWM_MAX, false);
  setMotor(M2_IN1, M2_IN2, M2_PWM, 0, true);
  setMotor(M3_IN1, M3_IN2, M3_PWM, 0, true);
  setMotor(M4_IN1, M4_IN2, M4_PWM, PWM_MAX, false);
}

void moveBackwardLeft() {
  setMotor(M1_IN1, M1_IN2, M1_PWM, 0, true);
  setMotor(M2_IN1, M2_IN2, M2_PWM, PWM_MAX, false);
  setMotor(M3_IN1, M3_IN2, M3_PWM, PWM_MAX, false);
  setMotor(M4_IN1, M4_IN2, M4_PWM, 0, true);
}

void rotateRight() {
  setMotor(M1_IN1, M1_IN2, M1_PWM, PWM_MAX, true);
  setMotor(M2_IN1, M2_IN2, M2_PWM, PWM_MAX, false);
  setMotor(M3_IN1, M3_IN2, M3_PWM, PWM_MAX, true);
  setMotor(M4_IN1, M4_IN2, M4_PWM, PWM_MAX, false);
}

void rotateLeft() {
  setMotor(M1_IN1, M1_IN2, M1_PWM, PWM_MAX, false);
  setMotor(M2_IN1, M2_IN2, M2_PWM, PWM_MAX, true);
  setMotor(M3_IN1, M3_IN2, M3_PWM, PWM_MAX, false);
  setMotor(M4_IN1, M4_IN2, M4_PWM, PWM_MAX, true);
}

// === Fungsi baca sinyal PWM receiver ===
int getChannelValue(int pin) {
  int dur = pulseIn(pin, HIGH, 25000);
  return map(dur, 1000, 2000, -255, 255);
}
