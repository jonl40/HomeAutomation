#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11
#define ENABLE 5
#define DIRA 3
#define DIRB 4

static const int DHT_SENSOR_PIN = 2;
float TEMPERATURE_THRESHOLD = 25.0;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

void setup() {
  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  Serial.begin(9600);
}
void loop() {
  float temperature;
  float humidity;

  DisplayTemp(&temperature, &humidity);
  Controller(temperature, humidity);
  
}

void FanOn()
{
  digitalWrite(ENABLE,HIGH); // enable on
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
}

void FanOff()
{
  digitalWrite(ENABLE,HIGH);
  digitalWrite(DIRA,LOW); //fast stop
  digitalWrite(DIRB,LOW);
}

/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}

void DisplayTemp(float *temperature, float *humidity)
{
    /* Measure temperature and humidity.  If the functions returns
   true, then a measurement is available. */
  if( measure_environment( temperature, humidity ) == true )
  {
    Serial.print( "T = " );
    Serial.print( *temperature, 1 );
    Serial.print( " deg. C, H = " );
    Serial.print( *humidity, 1 );
    Serial.println( "%" );
  }
}

void Controller(float temperature, float humidity)
{
  if(temperature > TEMPERATURE_THRESHOLD)
  {
    FanOn();
  }
  else
  {
    FanOff();
  }
}
