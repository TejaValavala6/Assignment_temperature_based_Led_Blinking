#include<MyDelay.h>

MyDelay LEDTime1(250); //Creating object named LEDTime1 to the class MyDelay by setting the delay value as 250 ms
MyDelay LEDTime2(500); //Creating object named LEDTime2 to the class MyDelay by setting the delay value as 500 ms

float temp_value(void); //FUNCTION TO READ THE TEMPERATURE FROM THE LM35 SENSOR AND RETURNS THE TEMPERATURE IN DEGREES
void blink_led(void);  //FUNCTION TO BLINK THE LED BASED ON TEMPERATURE VALUE RETURN BY THE "temp_value()"

int LedState = LOW; //to store the LED state

void setup() 
{
  // Initialize the digital pin LED_BUILTIN as OUPTUT pin
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  LEDTime1.start();
  LEDTime2.start();
}

void loop() {
  blink_led(); //calling the blink_led function to make the led blink according to the temperature value
}

/*FUNCTION TO READ THE TEMPERATURE*/
float temp_value()
{
  float temp_Value; //variable to hold the value reading from the LM35 temperature sensor
  temp_Value = analogRead(A0); // Reading Temperature through Analog pin A0
  temp_Value =  temp_Value*0.48828; // converting ADC value to equivalent voltage (5/1024)
  // LM35 gives output of 10mv/ degree C
  return temp_Value;
}

/*FUNTION TO BLINK THE LED BASED ON temp_value*/
void blink_led()
{
  float temp_val;
  temp_val = temp_value(); //Collecting temperature value in degrees by calling the temp_value()
  if(temp_val<30)          //if temperature is <30 degrees delay than is 250 ms 
    {
    if(LEDTime1.update())
    {
      if(LedState == LOW)
        LedState=HIGH;
      else
        LedState=LOW;
    }
  }
  else if(temp_val>=30) //if temperature is  >=30 degrees than delay is 500 ms
  {
    if(LEDTime2.update())
    {
      if(LedState == LOW)
        LedState=HIGH;
      else
        LedState=LOW;
    }
  }
  digitalWrite(LED_BUILTIN,LedState);
}
