//#include <PING1D_CONSTANTS.h>
#include <T4_PING_1D.h>



const int ledpin = 13;

PING_1D_ *P1D;

#define UPDATE_DELAY_MS 100

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ledpin, OUTPUT);
  P1D = init_ping_1d_data_struct();

  Serial.printf("Initiated Data Struct: %08X\n", P1D);
  init_ping_1D_serial();

  delay(50);

  P1D_REQUEST_DISTANCE_SIMPLE();

  delay(50);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  static uint32_t mitim = millis();

  if(millis() > mitim + UPDATE_DELAY_MS){
    P1D_READ_DISTANCE_SIMPLE();
    
    P1D_REQUEST_DISTANCE_SIMPLE();
    mitim = millis();
    Serial.printf("Read Dist: %dmm\tConfidence: %3d%%\t%.6fm\n",
                        P1D->data.distance,
                        P1D->data.confidence,
                        (347.0f/1500.0f * (float)P1D->data.distance)/1000.0f);    // Convert to air measurements, very rough and bad
  }

}
