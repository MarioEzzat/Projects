#define LIVINGROOM_LIGHTS 8
#define BATHROOM_LIGHTS 11
#define BEDROOM_LIGHTS 10
#define KITCHEN_LIGHTS 12

#include <Servo.h>
#include <SimpleDHT.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

/* -------------------------------------------------------------------------- */
/*                                KEYPAD DEFINE                               */
/* -------------------------------------------------------------------------- */

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'S', '0', 'H', 'D'}};
byte rowPins[ROWS] = {38, 36, 34, 32}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {30, 28, 26, 24}; // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
char CURRENT_PASSWORD[5] = {'1', '2', '3', '4'}; // DEFUALT PASSWORD
char ENTERED_PASSWORD[5] = "";                   //

/* -------------------------------------------------------------------------- */
/*                           ENTER PASSWORD FUNCTION                          */
/* -------------------------------------------------------------------------- */
void scan_password()
{
    int i = 0, COUNT = 0;
    lcd.setCursor(1, 0);
    lcd.print("Enter Password");
    while (i < 4)
    {
        char PASSWORD = keypad.getKey();
        if (PASSWORD != NULL)
        {
            ENTERED_PASSWORD[i] = PASSWORD;
            if (ENTERED_PASSWORD[i] == CURRENT_PASSWORD[i])
            { // CHECK THE PASSWORD
                COUNT++;
            }
            lcd.setCursor(i + 5, 1);
            lcd.print("*");
            i++;
        }
    }
    if (COUNT == 4)
    { // CORRECT PASSWORD
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Door Opening");
        delay(1500);
        open_door_function(); // OPEN DOOR FUNCTION
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Welcome Home");
        delay(1500);
        lcd.clear();
    }
    else
    {
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Wrong Password");
        delay(1500);
        lcd.clear();
    }
}
/* -------------------------------------------------------------------------- */
/*                          CHANGE PASSWORD FUNCTION                          */
/* -------------------------------------------------------------------------- */
void change_password()
{
    int i = 0, COUNT = 0;

    lcd.setCursor(2, 0);
    lcd.print("Old Password");
    while (i < 4)
    {
        char PASSWORD = keypad.getKey();
        if (PASSWORD != NULL)
        {
            ENTERED_PASSWORD[i] = PASSWORD;
            if (ENTERED_PASSWORD[i] == CURRENT_PASSWORD[i])
            {
                COUNT++;
            }
            lcd.setCursor(i + 5, 1);
            lcd.print("*");
            i++;
        }
    }
    lcd.clear();
    i = 0; // RESET FOR THE NEXT LOOP
    if (COUNT == 4)
    {
        while (i < 4)
        {
            char NEW_PASSWORD = keypad.getKey();
            lcd.setCursor(2, 0);
            lcd.print("New Password");
            if (NEW_PASSWORD != NULL)
            {
                CURRENT_PASSWORD[i] = NEW_PASSWORD;
                lcd.setCursor(i + 5, 1);
                lcd.print("*");
                i++;
            }
        }
        lcd.clear();
        delay(1000);
        lcd.setCursor(0, 0);
        lcd.print("Password Changed");
        delay(1000);
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Welcome Home");
        delay(1500);
        lcd.clear();
    }
}
/* -------------------------------------------------------------------------- */
/*                               WINDOW FUNCTION                              */
/* -------------------------------------------------------------------------- */
#define windowpin 6
Servo window_motor;
int window_position = 0;
void open_window_function()
{
    if (window_position == 177)
    {
        for (window_position = 177; window_position > 0; window_position--)
        {
            window_motor.write(window_position);
        }
    }
}
void close_window_function()
{
    if (window_position == 0)
    {
        for (window_position = 0; window_position < 177; window_position++)
        {
            window_motor.write(window_position);
        }
    }
}
/* -------------------------------------------------------------------------- */
/*                                DOOR FUNCTION                               */
/* -------------------------------------------------------------------------- */
#define doorpin 5
Servo door_motor;
int door_position = 0;

void open_door_function()
{
    if (door_position == 186)
    {
        for (door_position = 186; door_position > 0; door_position--)
        {
            door_motor.write(door_position);
        }
    }
}

void close_door_function()
{
    if (door_position == 0)
    {
        for (door_position = 0; door_position <= 185; door_position++)
        {
            door_motor.write(door_position);
        }
    }
}
/* -------------------------------------------------------------------------- */
/*                                FAN_FUNCTION                                */
/* -------------------------------------------------------------------------- */
#define FAN 9
void FAN_ON()
{
    digitalWrite(FAN, HIGH);
}
void FAN_OFF()
{
    digitalWrite(FAN, LOW);
}
/* -------------------------------------------------------------------------- */
/*                            TEMPERATURE FUNCTION                            */
/* -------------------------------------------------------------------------- */
#define pinDHT11 7
byte END_MOOD = 0;
SimpleDHT11 dht11;
byte temperature;
byte humidity;

void TEMPERATURE()
{
    if (dht11.read(pinDHT11, &temperature, &humidity, NULL))
    {
        return;
    }
    if (temperature >= 25)
    {
        FAN_ON();
        END_MOOD = 1;
    }
    if (temperature < 25 && END_MOOD == 1)
    {
        FAN_OFF();
        END_MOOD = 0;
    }
}
/* -------------------------------------------------------------------------- */
/*                                RAIN FUNCTION                               */
/* -------------------------------------------------------------------------- */
#define rain_drop_sensor_pin A7
int rain_drop_sensor;
void RAIN_FUNCTION()
{
    byte MOOD = 0;
    rain_drop_sensor = analogRead(rain_drop_sensor_pin);
    if (rain_drop_sensor < 900)
    {
        close_window_function();
    }
}

/* -------------------------------------------------------------------------- */
/*                             GAS SENSOR FUNCTION                            */
/* -------------------------------------------------------------------------- */
#define buzzer 2
#define smoke 3
int gas_sensor;
void GAS_FUNCITON()
{
    gas_sensor = digitalRead(smoke);
    if (gas_sensor == 0)
    {
        tone(buzzer, 1000);
        delay(70);
        noTone(buzzer);
        delay(70);
    }
    else
    {
        noTone(buzzer);
    }
}
/* -------------------------------------------------------------------------- */
/*                            FLAME SENSOR FUNCTION                           */
/* -------------------------------------------------------------------------- */
#define flame 4
int flame_sensor;

void FIRE_FUNCTION()
{
    flame_sensor = digitalRead(flame);
    if (flame_sensor == 0)
    {
        tone(buzzer, 1000);
    }
    else
    {
        noTone(buzzer);
    }
}

/* -------------------------------------------------------------------------- */
/*                              FEEDBACK FUNCTION                             */
/* -------------------------------------------------------------------------- */
unsigned long previousTime = 0;
void FEEDBACK_FUNCTION()
{
    unsigned long currentTime = millis();
    if (currentTime - previousTime >= 3000)
    {
        previousTime = currentTime;
        Serial.print((int)temperature);
        Serial.print(" 'C");
        Serial.print("|");
        Serial.print((int)humidity);
        Serial.print(" %");
        Serial.print("|");
        if (gas_sensor == 0)
        {
            Serial.print("WARNING! Gas Leakage");
            Serial.print("|");
        }
        else
        {
            Serial.print(" ");
            Serial.print("|");
        }
        if (flame_sensor == 0)
        {
            Serial.print("WARNING! Fire");
        }
        else
        {
            Serial.print(" ");
        }
    }
}
/* -------------------------------------------------------------------------- */
/*                              CONTROL FUNCTION                              */
/* -------------------------------------------------------------------------- */
String value;
void CONTROL_FUNCTION()
{
    if (Serial.available() == 0)
    {
        value = Serial.readStringUntil('\n');
        if (value == "DOOR ON")
        {
            open_door_function();
        }
        else if (value == "DOOR OFF")
        {
            close_door_function();
        }
        else if (value == "BEDROOM LIGHTS ON")
        {
            digitalWrite(BEDROOM_LIGHTS, HIGH);
        }
        else if (value == "BEDROOM LIGHTS OFF")
        {
            digitalWrite(BEDROOM_LIGHTS, LOW);
        }
        else if (value == "KITCHEN LIGHTS ON")
        {
            digitalWrite(KITCHEN_LIGHTS, HIGH);
        }
        else if (value == "KITCHEN LIGHTS OFF")
        {
            digitalWrite(KITCHEN_LIGHTS, LOW);
        }
        else if (value == "BATHROOM LIGHTS ON")
        {
            digitalWrite(BATHROOM_LIGHTS, HIGH);
        }
        else if (value == "BATHROOM LIGHTS OFF")
        {
            digitalWrite(BATHROOM_LIGHTS, LOW);
        }
        else if (value == "LIVING ROOM LIGHTS ON")
        {
            digitalWrite(LIVINGROOM_LIGHTS, HIGH);
        }
        else if (value == "LIVING ROOM LIGHTS OFF")
        {
            digitalWrite(LIVINGROOM_LIGHTS, LOW);
        }
        else if (value == "FAN ON" && temperature < 25)
        {
            FAN_ON();
        }
        else if (value == "FAN OFF" && temperature < 25)
        {
            FAN_OFF();
        }
        else if (value == "WINDOW ON" && rain_drop_sensor > 500)
        {
            open_window_function();
        }
        else if (value == "WINDOW OFF" && rain_drop_sensor > 500)
        {
            close_window_function();
        }
    }
}
/****************************************************/
/********************PIR FUNCTION********************/
#define PIRPIN 50
#define LEADDOOR 52
unsigned long your_time = 0;
void PIR_FUNCTION()
{
    int val;
    unsigned long my_time = millis();
    val = digitalRead(PIRPIN);
    if (val == HIGH)
    {
        digitalWrite(LEADDOOR, HIGH);
        your_time = my_time;
    }
    if (val == LOW && my_time - your_time >= 5000)
    {
        digitalWrite(LEADDOOR, LOW);
    }
}
/***************************************************/

void setup()
{
    window_motor.attach(windowpin);
    door_motor.attach(doorpin);
    pinMode(FAN, OUTPUT);
    pinMode(smoke, INPUT);
    pinMode(flame, INPUT);
    pinMode(PIRPIN, INPUT);
    pinMode(LEADDOOR, OUTPUT);
    pinMode(LIVINGROOM_LIGHTS, OUTPUT);
    pinMode(KITCHEN_LIGHTS, OUTPUT);
    pinMode(BEDROOM_LIGHTS, OUTPUT);
    pinMode(BATHROOM_LIGHTS, OUTPUT);
    lcd.begin(16, 2);
    Serial.begin(9600);
}

void loop()
{
    lcd.setCursor(3, 0);
    lcd.print("Smart Home !");
    char key = keypad.getKey();
    if (key == 'A')
    {
        scan_password();
        key = NULL;
    }
    else if (key == 'C')
    {
        change_password();
        key = NULL;
    }
    else if (key == 'B')
    {
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Door Closing");
        close_door_function(); // CLOSE DOOR FUNCTION
        delay(1500);
        lcd.clear();
        key = NULL;
    }
    TEMPERATURE();
    GAS_FUNCITON();
    FIRE_FUNCTION();
    RAIN_FUNCTION();
    FEEDBACK_FUNCTION();
    CONTROL_FUNCTION();
    PIR_FUNCTION();
}
