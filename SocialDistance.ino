const int trigPin = 0;  // Arduino pin tied to trigger pin on the ultrasonic sensor.
const int echoPin = 1;  // Arduino pin tied to echo pin on the ultrasonic sensor.
long duration; // length of return pulse
int range_in; // range in inches

const int redPin = 10;
const int greenPin = 9;
const int bluePin = 4;
//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE

boolean redOn = false; 

void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}

void loop()
{
  delay(250);                     // Wait 250ms between pings. 29ms should be the shortest delay between pings.
  // Want to get 5 readings, throw out out of range, then average.
  unsigned long avgDuration = 0;
  unsigned long pulse;
  int iterations = 5;
  for (int i = 0; i < iterations; ++i)
  {
   // Clears the trigPin
   digitalWrite(trigPin, LOW);
   delayMicroseconds(2);
   // Sets the trigPin on HIGH state for 10 micro seconds
   digitalWrite(trigPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin, LOW);
   // Reads the echoPin, returns the sound wave travel time in microseconds
   pulse = pulseIn(echoPin, HIGH); // timeout after 36 milliseconds
   Serial.println(pulse);
   avgDuration += pulse;
   delay(50); // Millisecond delay between pings.
  }
  // Calculating the distance
  avgDuration /= iterations;
  range_in = avgDuration * 0.0135039 / 2;
  
  Serial.print("Ping: ");
  Serial.print(range_in); // Send ping, get distance in inches and print result (0 = outside set distance range)
  Serial.println("in");
  Serial.print (avgDuration);
  Serial.print(" iterations: ");
  Serial.println(iterations);
  if (range_in == 0) // out of range
    {
      setColor(0, 0 , 0); 
      redOn = false;
    }
  if (range_in < 72)  // too close, < 6 feet
   {
    if (redOn == false) 
    {
      setColor(255, 0, 0);  // red
      redOn = true;
    }
    else
    {
      setColor(0, 0, 0); // turn off (we want it to blink)
      redOn = false;
    }
   }
  else if (range_in < 108) // 6-9 feet, warning
   {
    setColor(100, 255, 0);  // yellow
    redOn = false;
   }
  else if (range_in < 144) // less than max range
   {
    setColor(0, 255, 0);  // green
    redOn = false;
   }
  else // out of range
   {
    setColor(0, 0, 0); // off
    redOn = false;
   }
}
 
void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
