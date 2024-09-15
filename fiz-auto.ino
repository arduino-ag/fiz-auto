constexpr int left_back = 5;
constexpr int left = 6;
constexpr int right_back = 9;
constexpr int right = 10;

constexpr int indicator_right = 4;
constexpr int indicator_left = 8;
constexpr int backlight = A2;
constexpr int right_light = A4;
constexpr int left_light = A5;

constexpr int indicator_delay = 200;
constexpr int turn_speed = 65;

constexpr bool sign(int x) {
    return ((x) < 0 ? -1 : ((x) > 0 ? 1 : 0));
}

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>

static bool backlight_status = false;
static bool frontlight_status = false;

void startup();
void set_speed(int speed);
void right_turn();
void left_turn();
void update_light();
void alert_indicator();
void start_indicator();
void drive(float x, float y);

void setup()
{
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
    while (!GamePad.isStartPressed())
    {
        Dabble.processInput();
        start_indicator();
    }
}

void loop()
{
    Dabble.processInput();

    if (GamePad.getXaxisData() != 0.0 || GamePad.getYaxisData() != 0.0) {
        drive(GamePad.getYaxisData(), GamePad.getXaxisData());
    } else if (GamePad.isUpPressed())
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
            digitalWrite(left_light, LOW);
            left_turn();
            update_light();
        }
    }
    else if (GamePad.isRightPressed())
    {
        while (GamePad.isRightPressed())
        {
            Dabble.processInput();
            digitalWrite(right_light, LOW);
            right_turn();
            update_light();
        }
    }
    else if (GamePad.isCrossPressed())
    {
    }
    else if (GamePad.isCirclePressed())
    {
        backlight_status = !backlight_status;
        frontlight_status = !frontlight_status;
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
        frontlight_status = !frontlight_status;
        update_light();
        delay(200);
        frontlight_status = !frontlight_status;
        update_light();
        delay(200);
    }
}

void set_speed(int speed)
{
    if (speed < 0)
    {
        analogWrite(right, 0);
        analogWrite(right_back, abs(speed));
        analogWrite(left, 0);
        analogWrite(left_back, abs(speed));
    }
    else if (speed > 0)
    {
        analogWrite(right, speed);
        analogWrite(right_back, 0);
        analogWrite(left, speed);
        analogWrite(left_back, 0);
    }
    else
    {
        analogWrite(right, 0);
        analogWrite(right_back, 0);
        analogWrite(left, 0);
        analogWrite(left_back, 0);
    }
}

void right_turn()
{
    analogWrite(right, 0);
    analogWrite(right_back, turn_speed);
    analogWrite(left, turn_speed);
    analogWrite(left_back, 0);

    while (GamePad.isRightPressed())
    {
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

void left_turn()
{
    analogWrite(right, turn_speed);
    analogWrite(right_back, 0);
    analogWrite(left, 0);
    analogWrite(left_back, turn_speed);


    while (GamePad.isLeftPressed())
    {
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


void update_light()
{
    digitalWrite(backlight, backlight_status);

    digitalWrite(left_light, frontlight_status);
    digitalWrite(right_light, frontlight_status);
}

void alert_indicator()
{
    while (GamePad.isTrianglePressed())
    {
        if (frontlight_status)
        {
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

    if (frontlight_status)
    {
        digitalWrite(right_light, HIGH);
        digitalWrite(left_light, HIGH);
    }
}

void start_indicator()
{
    delay(indicator_delay);
    digitalWrite(indicator_left, HIGH);
    digitalWrite(indicator_right, HIGH);
    delay(indicator_delay);
    digitalWrite(indicator_left, LOW);
    digitalWrite(indicator_right, LOW);
    delay(indicator_delay);
}

void drive(float x, float y)
{
    int speed = map(abs(x) * 100, 0, 700, 0, 255);
    int steering = map(abs(x) * 100, 0, 700, 0, 255);

    if (sign(x) == -1)
    {
        if (y == 0.0)
        {
            analogWrite(right, 0);
            analogWrite(right_back, speed);
            analogWrite(left, 0);
            analogWrite(left_back, speed);
        }
        else if (sign(y) == -1)
        {
            analogWrite(right, 0);
            analogWrite(right_back, speed - steering);
            analogWrite(left, 0);
            analogWrite(left_back, speed);
        }
        else if (sign(y) == 1)
        {
            analogWrite(right, 0);
            analogWrite(right_back, speed);
            analogWrite(left, 0);
            analogWrite(left_back, speed - steering);
        }
    }
    else if (sign(x) == 1)
    {
        if (y == 0.0)
        {
            analogWrite(right, speed);
            analogWrite(right_back, 0);
            analogWrite(left, speed);
            analogWrite(left_back, 0);
        }
        else if (sign(y) == -1)
        {
            analogWrite(right, speed - steering);
            analogWrite(right_back, 0);
            analogWrite(left, speed);
            analogWrite(left_back, 0);
        }
        else if (sign(y) == 1)
        {
            analogWrite(right, speed);
            analogWrite(right_back, 0);
            analogWrite(left, speed - steering);
            analogWrite(left_back, 0);
        }
    }
    else
    {
        analogWrite(right, 0);
        analogWrite(right_back, 0);
        analogWrite(left, 0);
        analogWrite(left_back, 0);
    }
}
