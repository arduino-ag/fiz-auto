#define LEFT_BACK 5
#define LEFT 6
#define RIGHT_BACK 9
#define RIGHT 10

#define TRIGGER 7
#define ECHO 11

#define INDICATOR_RIGHT 4
#define INDICATOR_LEFT 8
#define BACKLIGHT A2
#define RIGHT_LIGHT A4
#define LEFT_LIGHT A5

#define INDICATOR_DELAY 300

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

static bool backlight = false;
static bool frontlight = false;

void startup();
void set_speed(int speed);
void right_turn();
void left_turn();
void set_light(bool status);
void set_frontlight(bool status);
void update_light();
void alert_indicator();
long distance();

void setup()
{
    Serial.begin(115200);
    Dabble.begin(9600);

    // Motors
    pinMode(RIGHT, OUTPUT);
    pinMode(RIGHT_BACK, OUTPUT);
    pinMode(LEFT, OUTPUT);
    pinMode(LEFT_BACK, OUTPUT);

    // light
    pinMode(INDICATOR_RIGHT, OUTPUT);
    pinMode(INDICATOR_LEFT, OUTPUT);
    pinMode(BACKLIGHT, OUTPUT);
    pinMode(RIGHT_LIGHT, OUTPUT);
    pinMode(LEFT_LIGHT, OUTPUT);

    Dabble.processInput();
    while (!GamePad.isStartPressed())
    {
        alert_indicator();
    }
}

void loop()
{
    Dabble.processInput();
    long dist = distance();

    if (GamePad.isUpPressed())
    {
        set_speed(100);
    }
    else if (GamePad.isDownPressed())
    {
        set_speed(-100);
    }
    else if (GamePad.isLeftPressed())
    {
        left_turn();
    }
    else if (GamePad.isRightPressed())
    {
        right_turn();
    }
    else if (GamePad.isCrossPressed())
    {
    }
    else if (GamePad.isCirclePressed())
    {
        backlight = !backlight;
        frontlight = !frontlight;
        update_light();
        delay(300);
    }
    else if (GamePad.isTrianglePressed())
    {
        alert_indicator();
    }
    else if (GamePad.isSquarePressed())
    {
        set_speed(-100);
        delay(300);
        set_speed(0);
    }
    else if (GamePad.isStartPressed())
    {
    }
    else if (GamePad.isSelectPressed())
    {
    }
    else 
    {
        set_speed(0);
    }

    if (dist < 20) {
        set_speed(0);
        alert_indicator();
    }
}

void startup() {
    delay(300);
    for (int i = 0; i < 5; i++) {
        frontlight = !frontlight;
        update_light();
        delay(200);
        frontlight = !frontlight;
        update_light();
        delay(200);
    }
}

void set_speed(int speed)
{
    if (speed < 0)
    {
        analogWrite(RIGHT, 0);
        analogWrite(RIGHT_BACK, abs(speed));
        analogWrite(LEFT, 0);
        analogWrite(LEFT_BACK, abs(speed) - abs(speed) / 11);
    }
    else if (speed > 0)
    {
        analogWrite(RIGHT, speed);
        analogWrite(RIGHT_BACK, 0);
        analogWrite(LEFT, speed - speed / 11);
        analogWrite(LEFT_BACK, 0);
    }
    else
    {
        analogWrite(RIGHT, 0);
        analogWrite(RIGHT_BACK, 0);
        analogWrite(LEFT, 0);
        analogWrite(LEFT_BACK, 0);
    }
}

void left_turn()
{
    analogWrite(RIGHT, 255 / 3.5);
    analogWrite(RIGHT_BACK, 0);
    analogWrite(LEFT, 0);
    analogWrite(LEFT_BACK, 255 / 3.5);

    digitalWrite(INDICATOR_LEFT, HIGH);
    delay(INDICATOR_DELAY);
    digitalWrite(INDICATOR_LEFT, LOW);
    delay(INDICATOR_DELAY);
}

void right_turn()
{
    analogWrite(RIGHT, 0);
    analogWrite(RIGHT_BACK, 255 / 3.5);
    analogWrite(LEFT, 255 / 3.5);
    analogWrite(LEFT_BACK, 0);

    digitalWrite(INDICATOR_RIGHT, HIGH);
    delay(INDICATOR_DELAY);
    digitalWrite(INDICATOR_RIGHT, LOW);
    delay(INDICATOR_DELAY);
}

long distance()
{
    digitalWrite(TRIGGER, LOW);
    delay(5);
    digitalWrite(TRIGGER, HIGH);
    delay(10);
    digitalWrite(TRIGGER, LOW);
    int duration = pulseIn(ECHO, HIGH);
    return (duration / 2) * 0.03432;
}

void update_light()
{
    digitalWrite(BACKLIGHT, backlight);

    digitalWrite(LEFT_LIGHT, frontlight);
    digitalWrite(RIGHT_LIGHT, frontlight);
}

void alert_indicator()
{
    while (GamePad.isTrianglePressed())
    {
        if (frontlight)
        {
            digitalWrite(LEFT_LIGHT, LOW);
            digitalWrite(RIGHT_LIGHT, LOW);
        }

        delay(INDICATOR_DELAY);
        digitalWrite(INDICATOR_LEFT, HIGH);
        digitalWrite(INDICATOR_RIGHT, HIGH);
        delay(INDICATOR_DELAY);
        digitalWrite(INDICATOR_LEFT, LOW);
        digitalWrite(INDICATOR_RIGHT, LOW);
        delay(INDICATOR_DELAY);

        Dabble.processInput();
    }

    if (frontlight)
    {
        digitalWrite(RIGHT_LIGHT, HIGH);
        digitalWrite(LEFT_LIGHT, HIGH);
    }
}
