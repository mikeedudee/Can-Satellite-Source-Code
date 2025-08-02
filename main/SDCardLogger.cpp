// #include "SDCardLogger.h"

// bool SDCardLogger::begin() {
//     // Ensure any prior session is closed
//     _sd.end();

//     for (int attempt = 1; attempt <= MAX_ATTEMPTS; ++attempt) {
//         if (_sd.begin(SdioConfig(FIFO_SDIO))) {
//             _ready = true;
//             return true;
//         }
//         delay(RETRY_DELAY_MS);
//     }
//     SDCard_Status   = 0;
//     _ready          = false;

//     return false;
// }

// bool SDCardLogger::logValue(const String& value) {
//     if (!_ready) return false;

//     _file = _sd.open(FILENAME, FILE_WRITE);
//     if (!_file) {
//         Serial.println("[ERROR] Failed to open file for writing.");
//         _sd.errorPrint(&Serial);
//         SDCard_Status   = 0;
//         _ready          = false;
//         return false;
//     }

//     SDCard_Status = 1;
//     _file.println(value);
//     _file.sync();
//     _file.close();

//     return true;
// }
