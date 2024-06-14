#define LEFT_BACK 5
#define LEFT 6
#define RIGHT_BACK 9
#define RIGHT 10

#define INDICATOR_RIGHT 4
#define INDICATOR_LEFT 8
#define BACKLIGHT A2
#define RIGHT_LIGHT A4
#define LEFT_LIGHT A5

#define INDICATOR_DELAY 200
#define TURN_SPEED 70

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

static bool backlight = false;
static bool frontlight = false;

void startup();
void set_speed(int speed);
void right_turn();
void left_turn();
void update_light();
void alert_indicator();
void start_indicator();

void setup()
{
    Serial.begin(19200);
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
        Dabble.processInput();
        start_indicator();
    }
}

void loop()
{
    Dabble.processInput();

    if (GamePad.isUpPressed())
    {
        set_speed(255);
    }
    else if (GamePad.isDownPressed())
    {
        set_speed(-255);
    }
    else if (GamePad.isLeftPressed())
    {
        while (GamePad.isLeftPressed())
        {
            Dabble.processInput();
            digitalWrite(LEFT_LIGHT, LOW);
            left_turn();
            update_light();
        }
    }
    else if (GamePad.isRightPressed())
    {
        while (GamePad.isRightPressed())
        {
            Dabble.processInput();
            digitalWrite(RIGHT_LIGHT, LOW);
            right_turn();
            update_light();
        }
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
}

void startup()
{
    delay(300);
    for (int i = 0; i < 5; i++)
    {
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
        analogWrite(LEFT_BACK, abs(speed));
    }
    else if (speed > 0)
    {
        analogWrite(RIGHT, speed);
        analogWrite(RIGHT_BACK, 0);
        analogWrite(LEFT, speed);
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

void right_turn()
{
    analogWrite(RIGHT, 0);
    analogWrite(RIGHT_BACK, TURN_SPEED);
    analogWrite(LEFT, TURN_SPEED);
    analogWrite(LEFT_BACK, 0);

    while (GamePad.isRightPressed())
    {
        Dabble.processInput();

        digitalWrite(INDICATOR_RIGHT, HIGH);
        delay(INDICATOR_DELAY / 2);

        if (!GamePad.isRightPressed())
            break;

        Dabble.processInput();

        delay(INDICATOR_DELAY / 2);

        if (!GamePad.isRightPressed())
            break;

        Dabble.processInput();

        if (!GamePad.isRightPressed())
            break;

        digitalWrite(INDICATOR_RIGHT, LOW);
        delay(INDICATOR_DELAY / 2);

        Dabble.processInput();

        delay(INDICATOR_DELAY / 2);

        if (!GamePad.isRightPressed())
            break;

        Dabble.processInput();
    }

    digitalWrite(INDICATOR_RIGHT, LOW);
}

void left_turn()
{
    analogWrite(RIGHT, TURN_SPEED);
    analogWrite(RIGHT_BACK, 0);
    analogWrite(LEFT, 0);
    analogWrite(LEFT_BACK, TURN_SPEED);

    while (GamePad.isLeftPressed())
    {
        Dabble.processInput();

        digitalWrite(INDICATOR_LEFT, HIGH);
        delay(INDICATOR_DELAY / 2);

        if (!GamePad.isLeftPressed())
            break;

        Dabble.processInput();

        delay(INDICATOR_DELAY / 2);

        if (!GamePad.isLeftPressed())
            break;

        Dabble.processInput();

        if (!GamePad.isLeftPressed())
            break;

        digitalWrite(INDICATOR_LEFT, LOW);
        delay(INDICATOR_DELAY / 2);

        Dabble.processInput();

        delay(INDICATOR_DELAY / 2);

        if (!GamePad.isLeftPressed())
            break;

        Dabble.processInput();
    }

    digitalWrite(INDICATOR_LEFT, LOW);
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

void start_indicator()
{
    delay(INDICATOR_DELAY);
    digitalWrite(INDICATOR_LEFT, HIGH);
    digitalWrite(INDICATOR_RIGHT, HIGH);
    delay(INDICATOR_DELAY);
    digitalWrite(INDICATOR_LEFT, LOW);
    digitalWrite(INDICATOR_RIGHT, LOW);
    delay(INDICATOR_DELAY);
}
