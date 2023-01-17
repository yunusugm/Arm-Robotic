void networkConnection() {
  // Reset the network connection
  WiFi.disconnect();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
    if (millis() - ms >= 7500) {
      Serial.println(" failed! too long connect wifi");
      return;
    }
  }
  Serial.println();
  Serial_Printf("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void configFirebase() {
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("signUp ok");
    is_signup = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
    Serial.println("failed sign up");
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}


void firebaseCRUD() {
  if (Firebase.ready() && is_signup && (millis() - sendDataPrevMillis > 500 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();

    if (Firebase.RTDB.getInt(&fbdo, "mode/arm")) {
      if (fbdo.dataType() == "int") {
        mode = fbdo.intData();
      }
    } else {
      Serial.println(fbdo.errorReason());
    }

    if (mode == 0) {
      modeManual();
    }
    if (mode == 1) {
      modeAuto();
    }
  }
}


void modeManual() {
  if (Firebase.RTDB.getInt(&fbdo, "angle/grip")) {
    if (fbdo.dataType() == "int") {
      gripFrom = fbdo.intData();
      grip.write(gripFrom);
      Serial.print("Grip: ");
      Serial.println(gripFrom);
    }
  } else {
    Serial.println(fbdo.errorReason());
  }

  if (Firebase.RTDB.getInt(&fbdo, "angle/base")) {
    if (fbdo.dataType() == "int") {
      baseFrom = fbdo.intData();
      base.write(baseFrom);
      Serial.print("Base: ");
      Serial.println(baseFrom);
    }
  } else {
    Serial.println(fbdo.errorReason());
  }

  if (Firebase.RTDB.getInt(&fbdo, "angle/shoulder")) {
    if (fbdo.dataType() == "int") {
      shoulderFrom = fbdo.intData();
      shoulder.write((shoulderFrom * -1) + 180);
      Serial.print("Shoulder: ");
      Serial.println((shoulderFrom * -1) + 180);
    }
  } else {
    Serial.println(fbdo.errorReason());
  }

  if (Firebase.RTDB.getInt(&fbdo, "angle/wrist")) {
    if (fbdo.dataType() == "int") {
      wristFrom = fbdo.intData();
      wrist.write(wristFrom);
      Serial.print("Wrist: ");
      Serial.println(wristFrom);
    }
  } else {
    Serial.println(fbdo.errorReason());
  }

  if (Firebase.RTDB.getInt(&fbdo, "angle/elbow")) {
    if (fbdo.dataType() == "int") {
      elbowFrom = fbdo.intData();
      elbow.write(elbowFrom);
      Serial.print("Elbow: ");
      Serial.println(elbowFrom);
    }
  } else {
    Serial.println(fbdo.errorReason());
  }
}

void modeAuto() {
  if (Firebase.RTDB.getInt(&fbdo, "mode/task")) {
    if (fbdo.dataType() == "int") {
      tasks = fbdo.intData();
    }
  } else {
    Serial.println(fbdo.errorReason());
  }

  if (tasks == 1) {
    firstTask();
    Firebase.RTDB.setInt(&fbdo, "mode/task", -1);
  } else if (tasks == 0) {
    resetTask();
    Firebase.RTDB.setInt(&fbdo, "mode/task", -1);
  }
}