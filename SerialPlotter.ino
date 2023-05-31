/*
 * This is a simple program to show how the plotter works.
 * The potentiometer reading will dynamically expand the ceiling and floor.  The ceiling can only increase, and the floor can only decrease.
 * If the target MCU us an ESP32, the built-in Hall sensor will be used as a 5th printed value.
 * The Hall sensor reading, like the potentiometer reading, will also expand the ceiling and floor.
 * Typical hall readings range from +335 (with a small neodymium magnet held very close above) to -213 (with a small neodymium magnet held moderately close below, to avoid contact with the MCU pins).
 */
int CEILING = 100;
int FLOOR = -100;
const unsigned int RAMP_INTERVAL = 1;
const unsigned int ANALOG_PIN = 24;
int potentiometer;
int ramp = 0;
int hall = 0;
unsigned long lastRampTime = 0;
bool increase = true;


void setup() 
{
  Serial.begin( 115200 );
}


void loop() 
{
  potentiometer = analogRead( ANALOG_PIN );
#ifdef ESP32
  hall = hallRead();
#endif

  // Change direction.
  if( ramp >= CEILING )
    increase = false;
  if( ramp <= FLOOR )
    increase = true;
  
  // Raise the ceiling.
  if( potentiometer > CEILING )
    CEILING = potentiometer;
  if( hall > CEILING )
    CEILING = hall;

  // Lower the floor
  if( potentiometer < FLOOR )
    FLOOR = potentiometer;
  if( hall < FLOOR )
    FLOOR = hall;

  if( lastRampTime == 0 || millis() - lastRampTime >= RAMP_INTERVAL )
  {
    // Increment or decrement.
    if( increase )
      ramp++;
    else
      ramp--;
    lastRampTime = millis();
  }

  Serial.print( "Potentiometer:" );
  Serial.print( potentiometer );
  Serial.print( "," );
  Serial.print( "Ceiling:" );
  Serial.print( CEILING );
  Serial.print( "," );
  Serial.print( "Floor:" );
  Serial.print( FLOOR );
  Serial.print( "," );
  Serial.print( "Ramp:" );
  Serial.print( ramp );
#ifdef ESP32
  Serial.print( "," );
  Serial.print( "Hall:" );
  Serial.print( hall );
#endif

  Serial.println();
}
