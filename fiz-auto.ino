#define TRIGGER 2
#define LEFT_BACK 3
#define ECHO 4
#define LEFT 5
#define RIGHT 6
#define RIGHT_BACK 9

void setup()
{
    pinMode(TRIGGER, OUTPUT);
    pinMode(LEFT_BACK, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(LEFT, OUTPUT);
    pinMode(RIGHT, OUTPUT);
    pinMode(RIGHT_BACK, OUTPUT);
}

void loop()
{
    if (distance() > 20) {
        set_speed(255/3, 0);
    } else {
        set_speed(0, 0);
    }
}

void set_speed(int speed, int direction)
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