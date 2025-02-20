constexpr uint8_t left_back = 5;
constexpr uint8_t left = 6;
constexpr uint8_t right_back = 9;
constexpr uint8_t right = 10;

constexpr uint8_t indicator_right = 4;
constexpr uint8_t indicator_left = 8;
constexpr uint8_t backlight = A2;
constexpr uint8_t right_light = A4;
constexpr uint8_t left_light = A5;

constexpr unsigned long indicator_delay = 200;
constexpr uint8_t turn_speed = 65;
constexpr uint8_t max_speed = 255;
constexpr int16_t reverse_speed = -100;

constexpr uint8_t right_offset = 0;
constexpr uint8_t left_offset = 0;

constexpr bool sign(int x) {
  return ((x) < 0 ? -1 : ((x) > 0 ? 1 : 0));
}

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

static bool backlight_status = false;
static bool frontlight_status = false;

void startup();
void set_speed(int16_t speed);
void set_motors(uint8_t right_speed, uint8_t right_back_speed, uint8_t left_speed, uint8_t left_back_speed);
void set_offset();
void right_turn();
void left_turn();
void update_light();
void alert_indicator();
void start_indicator();
void drive(float x, float y);

void setup() {
  Serial.begin(19200);
  Dabble.begin(9600);

  // Motors
  pinMode(right, OUTPUT);
  pinMode(right_back, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(left_back, OUTPUT);

  // light
  pinMode(indicator_right, OUTPUT);
  pinMode(indicator_left, OUTPUT);
  pinMode(backlight, OUTPUT);
  pinMode(right_light, OUTPUT);
  pinMode(left_light, OUTPUT);

  Dabble.processInput();
  while (!GamePad.isStartPressed()) {
    Dabble.processInput();
    start_indicator();
  }
}

void loop() {
  Dabble.processInput();

  if (GamePad.getXaxisData() != 0.0 || GamePad.getYaxisData() != 0.0) {
    drive(GamePad.getYaxisData(), GamePad.getXaxisData());
  } else if (GamePad.isUpPressed()) {
    set_speed(max_speed);
  } else if (GamePad.isDownPressed()) {
    set_speed(max_speed);
  } else if (GamePad.isLeftPressed()) {
    digitalWrite(left_light, LOW);
    left_turn();
    update_light();
  } else if (GamePad.isRightPressed()) {
    digitalWrite(right_light, LOW);
    right_turn();
    update_light();
  } else if (GamePad.isCrossPressed()) {
  } else if (GamePad.isCirclePressed()) {
    backlight_status = !backlight_status;
    frontlight_status = !frontlight_status;
    update_light();
    delay(300);
  } else if (GamePad.isTrianglePressed()) {
    alert_indicator();
  } else if (GamePad.isSquarePressed()) {
    set_speed(-100);
    delay(300);
    set_speed(0);
  } else if (GamePad.isStartPressed()) {
  } else if (GamePad.isSelectPressed()) {
  } else {
    set_speed(0);
  }
}

void startup() {
  delay(300);
  for (int i = 0; i < 5; i++) {
    frontlight_status = !frontlight_status;
    update_light();
    delay(200);
    frontlight_status = !frontlight_status;
    update_light();
    delay(200);
  }
}

void set_speed(int16_t speed) {
  if (speed < 0) {
    set_motors(0, abs(speed), 0, abs(speed));
  } else if (speed > 0) {
    set_motors(speed, 0, speed, 0);
  } else {
    set_motors(0, 0, 0, 0);
  }
}

void set_motors(uint8_t right_speed, uint8_t right_back_speed, uint8_t left_speed, uint8_t left_back_speed) {
  analogWrite(right, right_speed);
  analogWrite(right_back, right_back_speed);
  analogWrite(left, left_speed);
  analogWrite(left_back, left_back_speed);
}

void right_turn() {
  set_motors(0, turn_speed, turn_speed, 0);

  while (GamePad.isRightPressed()) {
    Dabble.processInput();
    if (!GamePad.isRightPressed())
      break;

    digitalWrite(indicator_right, HIGH);

    delay(indicator_delay / 4);
    Dabble.processInput();
    if (!GamePad.isRightPressed())
      break;

    delay(indicator_delay / 4);
    Dabble.processInput();
    if (!GamePad.isRightPressed())
      break;

    delay(indicator_delay / 4);
    Dabble.processInput();
    if (!GamePad.isRightPressed())
      break;

    delay(indicator_delay / 4);
    Dabble.processInput();
    if (!GamePad.isRightPressed())
      break;

    digitalWrite(indicator_right, LOW);

    delay(indicator_delay / 4);
    Dabble.processInput();
    if (!GamePad.isRightPressed())
      break;

    delay(indicator_delay / 4);
    Dabble.processInput();
    if (!GamePad.isRightPressed())
      break;

    delay(indicator_delay / 4);
    Dabble.processInput();
    if (!GamePad.isRightPressed())
      break;

    delay(indicator_delay / 4);
    Dabble.processInput();
    if (!GamePad.isRightPressed())
      break;
  }

  digitalWrite(indicator_right, LOW);
}

void left_turn() {
  set_motors(turn_speed, 0, 0, turn_speed);

  while (GamePad.isLeftPressed()) {
    Dabble.processInput();
    if (!GamePad.isLeftPressed())
      break;

    digitalWrite(indicator_left, HIGH);

    delay(indicator_delay / 4);
    Dabble.processInput();
    if (!GamePad.isLeftPressed())
      break;

    delay(indicator_delay / 4);
    Dabble.processInput();
    if (!GamePad.isLeftPressed())
      break;

    delay(indicator_delay / 4);
    Dabble.processInput();
    if (!GamePad.isLeftPressed())
      break;

    delay(indicator_delay / 4);
    Dabble.processInput();
    if (!GamePad.isLeftPressed())
      break;

    digitalWrite(indicator_left, LOW);

    delay(indicator_delay / 4);
    Dabble.processInput();
    if (!GamePad.isLeftPressed())
      break;

    delay(indicator_delay / 4);
    Dabble.processInput();
    if (!GamePad.isLeftPressed())
      break;

    delay(indicator_delay / 4);
    Dabble.processInput();
    if (!GamePad.isLeftPressed())
      break;

    delay(indicator_delay / 4);
    Dabble.processInput();
    if (!GamePad.isLeftPressed())
      break;
  }

  digitalWrite(indicator_left, LOW);
}

void update_light() {
  digitalWrite(backlight, backlight_status);

  digitalWrite(left_light, frontlight_status);
  digitalWrite(right_light, frontlight_status);
}

void alert_indicator() {
  while (GamePad.isTrianglePressed()) {
    if (frontlight_status) {
      digitalWrite(left_light, LOW);
      digitalWrite(right_light, LOW);
    }

    delay(indicator_delay);
    digitalWrite(indicator_left, HIGH);
    digitalWrite(indicator_right, HIGH);
    delay(indicator_delay);
    digitalWrite(indicator_left, LOW);
    digitalWrite(indicator_right, LOW);
    delay(indicator_delay);

    Dabble.processInput();
  }

  if (frontlight_status) {
    digitalWrite(right_light, HIGH);
    digitalWrite(left_light, HIGH);
  }
}

void start_indicator() {
  delay(indicator_delay);
  digitalWrite(indicator_left, HIGH);
  digitalWrite(indicator_right, HIGH);
  delay(indicator_delay);
  digitalWrite(indicator_left, LOW);
  digitalWrite(indicator_right, LOW);
  delay(indicator_delay);
}

void drive(float x, float y) {
  int speed = map(abs(x) * 100, 0, 700, 0, 255);
  int steering = map(abs(x) * 100, 0, 700, 0, 255);

  if (sign(x) == -1) {
    if (y == 0.0) {
      set_motors(0, speed, 0, speed);
    } else if (sign(y) == -1) {
      set_motors(0, speed - steering, 0, speed);
    } else if (sign(y) == 1) {
      set_motors(0, speed, 0, speed - steering);
    }
  } else if (sign(x) == 1) {
    if (y == 0.0) {
      set_motors(speed, 0, speed, 0);
    } else if (sign(y) == -1) {
      set_motors(speed - steering, 0, speed, 0);
    } else if (sign(y) == 1) {
      set_motors(speed, 0, speed - steering, 0);
    }
  } else {
    set_speed(0);
  }
}
