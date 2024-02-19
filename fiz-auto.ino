#define TRIGGER 2
#define ECHO 3
#define RIGHT_INDICATOR 4
#define RIGHT_BACK 5
#define RIGHT 6
#define LEFT 9
#define LEFT_BACK 10
#define FRONTLIGHT 11
#define LEFT_INDICATOR 12
#define BACKLIGHT 13

void right_turn();
void left_turn();
void indicator(int count, uint8_t light);
void set_speed(int speed);
long distance();

void setup()
{
    Serial.begin(115200);

    // Motors
    pinMode(RIGHT, OUTPUT);
    pinMode(RIGHT_BACK, OUTPUT);
    pinMode(LEFT, OUTPUT);
    pinMode(LEFT_BACK, OUTPUT);

    // ultrasonic sensor
    pinMode(TRIGGER, OUTPUT);
    pinMode(ECHO, INPUT);

    // car lights
    pinMode(RIGHT_INDICATOR, OUTPUT);
    pinMode(FRONTLIGHT, OUTPUT);
    pinMode(LEFT_INDICATOR, OUTPUT);
    pinMode(BACKLIGHT, OUTPUT);

    digitalWrite(FRONTLIGHT, HIGH);
}

void loop()
{
    long dis = distance();

    if (dis < 21)
    {
        digitalWrite(BACKLIGHT, HIGH);
        set_speed(0);
        delay(100);
        digitalWrite(BACKLIGHT, LOW);
        indicator(5, RIGHT_INDICATOR);
        right_turn();
        delay(500);
    }
    else
    {
        set_speed(255 / 3);
    }
}

void right_turn()
{
    analogWrite(RIGHT, 255 / 3.5);
    analogWrite(RIGHT_BACK, 0);
    analogWrite(LEFT, 0);
    analogWrite(LEFT_BACK, 255 / 3.5);
    delay(500);
    analogWrite(RIGHT, 0);
    analogWrite(LEFT_BACK, 0);
}

void left_turn()
{
    analogWrite(RIGHT, 0);
    analogWrite(RIGHT_BACK, 255 / 3);
    analogWrite(LEFT, 255 / 3);
    analogWrite(LEFT_BACK, 0);
    delay(500);
    analogWrite(LEFT, 0);
    analogWrite(RIGHT_BACK, 0);
}

void indicator(int count, uint8_t light)
{
    for (int i = 0; i < count; i++) {
        digitalWrite(light, HIGH);
        delay(500);
        digitalWrite(light, LOW);
        delay(500);
    }
}

void set_speed(int speed)
{
    if (speed < 0)
    {
        analogWrite(RIGHT, 0);
        analogWrite(RIGHT_BACK, abs(speed));
        analogWrite(LEFT, 0);
        analogWrite(LEFT_BACK, abs(speed) - abs(speed) / 10);
    }
    else if (speed > 0)
    {
        analogWrite(RIGHT, speed);
        analogWrite(RIGHT_BACK, 0);
        analogWrite(LEFT, speed - speed / 10);
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