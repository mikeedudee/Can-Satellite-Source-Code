void SDCard_Setup() {
  sd.end(); // Force SD deinitialization
  delay(2000);

  for (int attempt = 0; attempt < 1; attempt++) {
    if (sd.begin(SdioConfig(FIFO_SDIO))) {
      SDCard_Status = 1;
      return;
    } else {
      delay(1000);
    }
  }

  // Final failure handling
  SDCard_Status = 0;
  digitalWrite(23, HIGH);
  delay(500);
  digitalWrite(23, LOW);
}

// Function to save data to the file
void saveData(double data) {
  file = sd.open(filename, O_RDWR | O_CREAT | O_AT_END);
  if (!file) {
    return;
  }
  file.println(data);
  file.close();
}

void saveData(const char* data) {
  file = sd.open(filename, O_RDWR | O_CREAT | O_AT_END);
  if (!file) {

    return;
  }
  file.println(data);
  file.close();
}

// Function to read data from the file
void readData() {
  if (!sd.exists(filename)) {
    return;
  }

  file = sd.open(filename, O_RDONLY);
  if (!file) {
    return;
  }
  APC220.println("File contents:");
  while (file.available()) {
    String line = file.readStringUntil('\n');
    APC220.println(line);
  }
  file.close();
  APC220.println("File read complete.");
}

// Function to erase the data file
void eraseData() {
  if (!sd.exists(filename)) {
    return;
  }

  if (sd.remove(filename)) {
    APC220.println("File deleted successfully!");
  } else {
    APC220.println("Failed to delete file.");
  }
}

void stopData() {
 // file.close();
  //Serial.print("Printing data only.");
//  delay(2000);
}