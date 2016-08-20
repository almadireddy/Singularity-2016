task RPM() {
	float LastValue;
	while(true) {
		Value = SensorValue[flywheelEncoder];
		FlyRPM = Value - LastValue;
		LastValue = Value;
		wait1Msec(50);
	}
}

task error() {
	while (true) {
		CurrentValue = FlyRPM;
		Error = Target - CurrentValue;

		wait1Msec(50);

		LastError = Error;
	}
}

task Flywheel(){
	while(true) {
		Integral += 50 * ((Error + LastError)/2);

		if(Error == 0) {
			Integral = 0;
		}
		if(fabs(Integral) > integralCap) {
			Integral = integralCap;
		}

		Derivative = kd * (Error - LastError)/50;

		speed = kp * Error + ki * Integral + kd * Derivative;

    if(speed < 0)
  		speed = 45;
  	if (speed > 127)
  		speed = 127;
  	if (Error < 0)
  		speed = 20;
		wait1Msec(50);
	}
}

task bangBang() {
	while (true) {
		if (Error >= 0)
			speed = maxSpeed;
		else
			speed = minSpeed;
	}
}

task motorrun() {
	while(true) {
		motor[fly1] = speed;
		motor[fly2] = speed;
	}
}

task toneBack() {
	while (true) {
		tone = FlyRPM * tm;
		playTone (tone, 1);
	}
}

//task bangbang() {
//	while(true) {
//		while(flyTarget != 0) {
//			if(estimate < flyTarget) {
//				output = 127;
//			}

//			else if(estimate >= flyTarget) {
//				if(flyTarget < 440) {
//					output = 10;
//				}

//				if(flyTarget < 575 && flyTarget >= 440) {
//					output = 30;
//				}

//				if(flyTarget >= 575) {
//					output = 60;
//				}
//			}
//		}
//	}
//}
