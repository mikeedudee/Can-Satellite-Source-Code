void MS5611_Init() {
    ms5611.begin(HIGH_RES);
    delay(500);
    ms5611.enableKalmanFilter(0.5, 0.5, 0.138);
    referencePressure = ms5611.readPressure();
}

void MS5611_CORE() {
    uint32_t rawTemperature = ms5611.readRawTemperature();
    uint32_t rawPressure    = ms5611.readRawPressure();
    realTemperature         = ms5611.readTemperature();
    realPressure            = ms5611.readPressure();
    absoluteAltitude        = ms5611.getAltitude(realPressure);
    relativeAltitude        = ms5611.getAltitude(realPressure, referencePressure);
    Altitude_Filtered       = ms5611.kalmanFilter(relativeAltitude);
  
}