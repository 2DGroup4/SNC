
// set  pin numbers:
const int in0 = A0;            // input for reading the sensor  output
const int mosfetPin = 9;
const int target_temp = 16;

// set constants:
const float vout0 = 480;   //  sensor output  voltage in mV at 0°C
const float tc = 19.5;   // mV for °C temperature constant  for the  MCP9701/A
const float T_ambient = 20.9;
const float e_positive = 0.1;
const float e_negative = -0.1;

// variables:
int i, f;
float voutA0, vout_avgA0, temp_A0, SensorA0, error;
bool TC_State;


// MAIN PROGRAM
void setup() {
  Serial.begin(9600);
  pinMode(mosfetPin, OUTPUT);
  TC_State = false;
}

void loop() {
  vout_avgA0 = 0;
  for (i = 0; i < 1024; i++) {
    SensorA0 = analogRead(in0);
    voutA0 = (float) SensorA0*5000/1023 ;
    vout_avgA0 = vout_avgA0 + voutA0;

  }

  voutA0 = vout_avgA0/ 1023;

  temp_A0 = (voutA0 - vout0) / tc;

  error = temp_A0-target_temp;


  Serial.print(T_ambient);
  Serial.print(" , ");
  Serial.print(temp_A0);
  Serial.print(" , ");
  Serial.print(error);
  Serial.print(" , ");
  
  //BASIC Bang-Bang
  Bang_Bang_BASIC();

  digitalWrite(mosfetPin, TC_State ? HIGH : LOW);   // Turn on the MOSFET to activate the TEC
  Serial.println(TC_State ? "5, ON" : "0, OFF");

  delay (1000);
}

void Bang_Bang_BASIC(){
  TC_State = error > 0;
}

