task pidController() {
	pidLastError  = 0;
	pidIntegral   = 0;
	while( true ) {
	  if( pidRunning ) {
	  	if (abs(nMotorEncoder[lW2]) > abs(nMotorEncoder[rW2])) {
	  		pidSensorCurrentValue = nMotorEncoder[rW2];
	  		secondary = -nMotorEncoder[lW2];
	  		difference = abs(secondary) - abs(pidSensorCurrentValue);
	  		driveL(-pidDrive + constant*difference);
	    	driveR(-pidDrive);
	  	}
	  	else {
	  		pidSensorCurrentValue = -nMotorEncoder[lW2];
	  		secondary = nMotorEncoder[rW2];
	  		difference = abs(secondary) - abs(pidSensorCurrentValue);
	  		driveL(-pidDrive);
	    	driveR(-pidDrive + constant*difference);
	  	}

	    pidError = pidSensorCurrentValue - pidRequestedValue;

	    if( pid_Ki != 0 ) {
		    if( abs(pidError) < PID_INTEGRAL_LIMIT )
		        pidIntegral = pidIntegral + pidError;
		    else
		        pidIntegral = 0;
	    }
	    else
	        pidIntegral = 0;

	    pidDerivative = pidError - pidLastError;
	    pidLastError  = pidError;

	    pidDrive = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);

	    if ( pidDrive > PID_DRIVE_MAX )
	        pidDrive = PID_DRIVE_MAX;
	    if ( pidDrive < PID_DRIVE_MIN )
	        pidDrive = PID_DRIVE_MIN;
	  }
	  else {
	  	pidError      = 0;
		  pidLastError  = 0;
		  pidIntegral   = 0;
		  pidDerivative = 0;
	  }

	  // Run at 50Hz
	  wait1Msec( 25 );
	}
}

void go(float inches, float s = 85) {
	resetMotorEncoder(lW2);
	resetMotorEncoder(rW2);

	pidRequestedValue = inches * ticksPerInch;
}

task driveTarget() {
	while (true) {
		if (abs(pidError) < dt)
			atTarget = true;
		else
			atTarget = false;
	}
}
