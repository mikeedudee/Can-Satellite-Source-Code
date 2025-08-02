// REBOOT FUNCTIONALITY (SYSTEM)
#include <Arduino.h>
#include "imxrt.h"  // Teensy 4.1 specific header
#include <Wire.h>
#include <MS5611.h>
#include <SimpleKalmanFilter.h>
#include <TinyGPS++.h>  
#include <SoftwareSerial.h>
#include <Adafruit_BNO08x.h>
#include <SdFat.h>
#include <math.h>

// LOAD ALL THE GLOBAL VARIABLES AND DATA LOGGER
#include "GlobalVariables.h"
//#include "SDCardLogger.h"

/// GPS DECLARATION
#define   GPSSerial     Serial1
#define   GPSBaud       9600.

/// RADIO COMMUNICATION DECLARATION
#define   APC220        Serial2
#define   APC_BAUD      9600

//? BNO8X DECLARATION
#define   BNO08X_RESET  -1
  struct euler_t {
      float yaw;
      float pitch;
      float roll;
  } ypr;

Adafruit_BNO08x         bno08x(BNO08X_RESET);
sh2_SensorValue_t       sensorValue;

  #ifdef FAST_MODE
    // Top frequency is reported to be 1000Hz (but freq is somewhat variable)
    sh2_SensorId_t reportType = SH2_GYRO_INTEGRATED_RV; 
    long reportIntervalUs = 2000;
  #else
    // Top frequency is about 250Hz but this report is more accurate
    sh2_SensorId_t  reportType          = SH2_ARVR_STABILIZED_RV;
    long            reportIntervalUs    = 5000;
  #endif

  void setReports(sh2_SensorId_t reportType, long report_interval) {
    //print_data("Setting desired reports");
    
    if (! bno08x.enableReport(reportType, report_interval)) {
      //print_data("Could not enable stabilized remote vector");
    }
  }

// DECLARTION OF CLASSES TO VARIABLES
SdFs                  sd;
FsFile                file;
MS5611                ms5611;
TinyGPSPlus           gps;
//SDCardLogger          logger;

// PIN ASSIGNMENTS
// LED_BUILTIN: Teensy micro-controller LED
// Pin 23: Buzzer
// Pin 24: LED 1 [Upper Layer LED]
// Pin 25: LED 2 [Lower Layer LED]
// Pin 26: LED 3 [Lower Layer LED]
// Pin 38: LED 4 [Main Board LED]
static constexpr int      OUTPUT_PINS[]     = { LED_BUILTIN, 23, 24, 25, 26, 38 };                                                                                      // Array of deployment pins for charges
static constexpr size_t   NUM_OUTPUT_PINS   = sizeof(OUTPUT_PINS)/sizeof(OUTPUT_PINS[0]);  // Size of deployment and output pins for the loop

void setup() {
    Serial.begin(115200);
    while (!Serial) { delay(10); }
    APC220.begin(APC_BAUD);
    delay(100);
    analogReadResolution(12);

    for (size_t i = 0; i < NUM_OUTPUT_PINS; i++) {
        pinMode(OUTPUT_PINS[i], OUTPUT);
        digitalWrite(OUTPUT_PINS[0], 1); // Turn On BuiltIn LED
        //digitalWrite(OUTPUT_PINS[i], 0);
    }

    SDCard_Setup();

    // INITIALIZE THE SENSORS BY 100MS DELAY PER
    delay(100);
    MS5611_Init();
    delay(100);
    IMU_Init();
    delay(100);
    GPS_Init();
    
}

void loop() {
  present = millis();
  digitalWrite(OUTPUT_PINS[1], LOW);
// CALL THE SENSORS
    MS5611_CORE();
    IMU_CORE();
    GPS_CORE();
    THERMISTOR_CORE();

  // telemetry every 300 ms
  if (present - prevLogTime >= logGap) {
    prevLogTime = present;
    digitalWrite(OUTPUT_PINS[1], HIGH);
    doTelemetry();
  }
}

void doTelemetry() {
    
    

    Time_Elapsed      = millis() / 1000;
    Vertical_Velocity = ms5611.getVelocity(Altitude_Filtered, present);

    //String //designator_array[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M" };

    char buffer[128];
    sprintf(buffer, "%d %.4f %.4f %.4f %.6f %.6f %d %d %d %.6f %.6f %.6f %.4f %.4f", 
        realPressure,
        Altitude_Filtered,
        realTemperature, 
        Temperature_Therm,
        GPS_Latitude,
        GPS_Longitude,
        SDCard_Status,
        Time_Elapsed,
        sensorStatusValue,
        Yaw_Output,
        Pitch_Output,
        Roll_Output,
        Vertical_Velocity,
        absoluteAltitude
    );
    print_data(buffer);
    saveData(buffer);

    // double dataArray[] = {
    //     realPressure,
    //     Altitude_Filtered,
    //     realTemperature, 
    //     Temperature_Therm,
    //     GPS_Latitude,
    //     GPS_Longitude,
    //     SDCard_Status,
    //     Time_Elapsed,
    //     sensorStatusValue,
    //     Yaw_Output,
    //     Pitch_Output,
    //     Roll_Output,
    //     Vertical_Velocity,
    //     absoluteAltitude
    // };

    // for (int i = 0; i < sizeof(dataArray) / sizeof(dataArray[0]); ++i) {
    //     saveData(dataArray[i]);
    // }
    // Saving to Flash Memory
    
}