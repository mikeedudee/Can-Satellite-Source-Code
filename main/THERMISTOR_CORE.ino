void THERMISTOR_CORE() {
    int                 raw         = analogRead(A0);
    constexpr float     VREF        = 5.0f;
    constexpr int       MAX_RAW     = (1 << 12) - 1;  // 4095
    float               Vtherm      = raw * (VREF / float(MAX_RAW));
    float               Rfixed      = THERMISTOR_R0;  // 10 kΩ
    float               Rtherm      = Rfixed * Vtherm / (VREF - Vtherm);
    float               invT        = (1.0f / THERMISTOR_TEMP_INIT) + (log(Rtherm / THERMISTOR_R0) / THERMISTOR_BETA);
    
    Temperature_Therm = (1.0f / invT - 273.15f) + 25;
}

