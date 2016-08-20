void waitForPress() {
  while (nLCDButtons == 0){}
  wait1Msec(5);
}

void waitForRelease() {
  while (nLCDButtons != 0){}
  wait1Msec(5);
}

void autonSelection() {
  while(nLCDButtons != centerButton) {
    switch(count) {
      case 0:
        displayLCDCenteredString(0, "MidField");
        displayLCDCenteredString(1, "<        Enter        >");
        waitForPress();

        if (nLCDButtons == leftButton) {
          waitForRelease();
          count = 3;
        }
        else if (nLCDButtons == rightButton) {
          waitForRelease();
          count++;
        }
        break;

      case 1:
        displayLCDCenteredString(0, "Bar");
        displayLCDCenteredString(1, "<         Enter        >");
        waitForPress();

        if (nLCDButtons == leftButton) {
          waitForRelease();
          count--;
        }
        else if (nLCDButtons == rightButton) {
          waitForRelease();
          count++;
        }
        break;

      case 2:
        displayLCDCenteredString(0, "Corner");
        displayLCDCenteredString(1, "<         Enter        >");
        waitForPress();

        if (nLCDButtons == leftButton) {
          waitForRelease();
          count--;
        }
        else if (nLCDButtons == rightButton) {
          waitForRelease();
          count++;
        }
        break;

      case 3:
        displayLCDCenteredString(0, "Autonomous 4");
        displayLCDCenteredString(1, "<         Enter        >");
        waitForPress();
        if (nLCDButtons == leftButton) {
          waitForRelease();
          count--;
        }
        else if (nLCDButtons == rightButton) {
          waitForRelease();
          count = 0;
        }
        break;

      default:
        count = 0;
        break;
    }
  }
}
