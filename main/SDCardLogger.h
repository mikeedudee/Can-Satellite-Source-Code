// #ifndef SDCARDLOGGER_H
// #define SDCARDLOGGER_H

// #include <SdFat.h>
// #include "GlobalVariables.h"

// class SDCardLogger {
//     public:
//         /// Try to initialize the SD on SDIO up to MAX_ATTEMPTS times.
//         bool begin();

//         /// Append one double value (with 4 decimal places).
//         bool logValue(const String& value);

//         /// Current SD status
//         bool isReady() const { return _ready; }

//     private:
//         static constexpr int                MAX_ATTEMPTS        = 3;
//         static constexpr unsigned long      RETRY_DELAY_MS      = 2000UL;
//         static constexpr char               FILENAME[]          = "data.txt";

//         SdFs   _sd;
//         FsFile _file;
//         bool   _ready = false;
// };

// #endif  // SDCARDLOGGER_H
