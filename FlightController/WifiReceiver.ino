void ReadFromWifi() {
   if ( Serial.available() ) {
      String controll = Serial.readStringUntil(';');

      byte command = (int)controll[0] - 48;
      String paramUnConverted = "";
      for (byte i = 1; i <= controll.length(); i++) {
        paramUnConverted += controll[i];
      }
      short unsigned int speed = paramUnConverted.toInt();

      switch (command) {
        case 1: motorsSpeed[0] = speed; break;
        case 2: motorsSpeed[1] = speed; break;
        case 3: motorsSpeed[2] = speed; break;
        case 4: motorsSpeed[4] = speed; break;
        case 5: motorsSpeed[0] = speed; motorsSpeed[1] = speed; motorsSpeed[2] = speed; motorsSpeed[4] = speed; break;
        case 6: DeactivateMotors();
        case 7: ActivateMotors();
        if(SerialDebug) { Serial.print("All Motor Done"); } break;
      }
    }
}

