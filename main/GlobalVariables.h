// GlobalVariables.h
#ifndef GLOBALVARIABLES_H
#define GLOBALVARIABLES_H

// MS5611
extern double                       referencePressure;
extern double                       realTemperature;
extern long                         realPressure;
extern float                        absoluteAltitude;
extern float                        relativeAltitude;
extern double                       Altitude_Filtered;

// VELOCITY
extern float                        previousAltitude;
extern unsigned long                previousTime;
extern float                        Vertical_Velocity;

// THERMISTOR
static constexpr float              THERMISTOR_TEMP_INIT            = 298.15F;
static constexpr int                THERMISTOR_R0                   = 10000;        
static constexpr int                THERMISTOR_BETA                 = 3435;
extern float                        Analog_to_Voltage;
extern float                        Resistance_Therm;
extern float                        Temperature_Therm;

// GPS
static constexpr int                RXPin                           = 0;
static constexpr int                TXPin                           = 1;
extern float                        GPS_Latitude;
extern float                        GPS_Longitude;
extern float                        GPS_Altitude;       
extern float                        GPS_Latitude_Init;
extern float                        GPS_Longitude_Init;       
extern float                        GPS_DistanceBetween;     

// TIME
extern unsigned long                Time_Elapsed;
extern unsigned long                previous_millis;

// IMU (9-DoF)
extern double                       sensor_status;
extern double                       Yaw_Output;
extern double                       Pitch_Output;
extern double                       Roll_Output;
extern double                       nowLast;
extern int                          sensorStatusValue;

// KALMAN FILTER INSTANCE
extern double                       Altitude_kalt_Filtered;

// ALARM LIGHTS
extern int                          stateLED_MS5611;
extern int                          stateLED_BNO;
extern bool                         stateLED_Main;
extern bool                         state_Buzzer;
extern bool                         Manual_Override;
static constexpr unsigned long      TOGGLING_INTERVAL               = 250UL;

// SD CARD STATE
extern int                          SDCard_Status;
extern int                          save_data_state;
extern int                          show_data_state;
extern const char*                  filename;

// Non-blocking Iterator
extern unsigned long                prevLogTime;
static constexpr int                logGap                         = 300;
extern unsigned long                present;

#endif 
