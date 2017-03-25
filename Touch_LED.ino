/*
   Nikhil.P.Lokhande
   Project: ESP32 Touch Controled LED, using PWM
   Board: ESP32 Dev Module

   Touch Sensor Pin Layout
   T0 = GPIO4
   T1 = GPIO0
   T2 = GPIO2
   T3 = GPIO15
   T4 = GPIO13
   T5 = GPIO12
   T6 = GPIO14
   T7 = GPIO27
   T8 = GPIO33
   T9 = GPIO32 */
uint8_t led = 18;
void setup()
{
  ledcAttachPin(led, 1);                                                    //Configure variable led, pin 12 to channel 1
  ledcSetup(1, 12000, 8);                                                  // 12 kHz PWM and 8 bit resolution
  Serial.println("Testing ledc 12 channel 1");
  ledcWrite(1, 100);                                                       // Write a test value of 100 to channel 1
  Serial.begin(115200);



}

int buff(int pin)                                       //Function to handle the touch raw sensor data
{
  int prev = analogRead(pin);
  int curr = analogRead(pin);
  int out = abs(curr - prev);                           // Get the difference between current and previous values and scale by 50, value very sensitive currently
                                                        // change to adjust sensitivity as required
  if (out > 50)
  {
    return out;
  }
  else if (curr == 4095)                              // At peak, difference would be 0, hence a handler
  {
    return (curr / 50);
  }
  else
  {
    return 0;                                        //Else, return 0
  }

}
void loop()
{
  Serial.print("Touch sensor value:");
  Serial.println(buff(T0));


  if (buff(T0) == 0)
  {
    ledcWrite(1, 0);
  }
  else
  {
    ledcWrite(1, (buff(T0)));                 // Using T0 for touch data
  }

  delay(100);
}
