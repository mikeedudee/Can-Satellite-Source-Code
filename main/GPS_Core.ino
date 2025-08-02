void GPS_Init() {
    GPSSerial.begin(GPSBaud);
    delay(2000);  // Give GPS module time to boot

    GPSSerial.println("$PMTK220,100*2F"); // Set update rate to 10Hz (100ms)

    unsigned long start = millis();
    while (millis() - start < 10000) { // wait up to 10 seconds for a fix
        while (GPSSerial.available()) {
            if (gps.encode(GPSSerial.read()) && gps.location.isValid()) {
                GPS_Latitude_Init  = gps.location.lat();
                GPS_Longitude_Init = gps.location.lng();
                return;
            }
        }
    }
    // If no fix, set default or raise error
    // Serial.println("GPS Fix not acquired during init.");
}


void GPS_CORE() {
    // This function processes incoming GPS data and displays info when a valid sentence is decoded.
    while (GPSSerial.available() > 0) {
        if (gps.encode(GPSSerial.read())) {
            displayInfo();
        }
    }

    // Check if no GPS characters were processed after 5 seconds
    static bool gpsWarningShown = false;
    if (millis() > 5000 && gps.charsProcessed() < 10 && !gpsWarningShown) {
        //Serial.println(F("[WARNING] No GPS detected: check wiring or baud rate."));
        gpsWarningShown = true; // Ensure the warning is shown only once
    }
}


void displayInfo() {
    bool validLoc = gps.location.isValid();
    if (validLoc) {
        GPS_Latitude  = gps.location.lat();
        GPS_Longitude = gps.location.lng();
    }

    // if (gps.altitude.isValid()) {
    //     GPS_Altitude = gps.altitude.meters();
    // }

    if (validLoc) {
        GPS_DistanceBetween = gps.distanceBetween(
            GPS_Latitude, GPS_Longitude,
            GPS_Latitude_Init, GPS_Longitude_Init
        );
        //GPS_Latitude_Init  = GPS_Latitude;
        //GPS_Longitude_Init = GPS_Longitude;
    }
}
