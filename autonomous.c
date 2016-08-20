void allmotors(int s) {
	driveL(s);
	driveR(s);
}

void runIntakes() {
	motor[chn] = motor[rub] = 127;
}

void startGyroTasks() {
	startTask(kFilter);
	startTask(gyroTurn);
	startTask(gyroDrift);
}

void stopGyroTasks() {
	stopTask(kFilter);
	stopTask(gyroTurn);
	stopTask(gyroDrift);
}

task intakes() {
	while (true) {
		runIntakes();
	}
}

task autonomous() {
	bMotorReflected[rW2] = true;

	switch(count) {
		case 0: //midfield
			tolerance = 3;
			constant = 2;

			startTask(pidController);

			Target = 142;
			kp = 0.70;
		  ki = 0.36;
		  kd = 0.0;
		  chainSpeed = 127;
		  startFlywheelTasks(true);

			go(55, 50);
			wait1Msec(3000);


		  while (true) {
		  	motor[rub] = 127;

		    if (Error < tolerance && Error > -tolerance)
		      motor[chn] = chainSpeed;
		   	else
		   		motor[chn] = 0;
		  }
			break;

		case 1: //bar
			tolerance = 15;
			constant = 4;
			pid_Kp = 0.2;

			startTask(pidController);

			Target = 110;
			kp = 0.50;
		  ki = 0.36;
		  kd = 0.0;
		  chainSpeed = 127;
		  startFlywheelTasks(true);

			go(50);
			wait1Msec(3500);


		  while (true) {
		  	motor[rub] = 127;
		    motor[chn] = chainSpeed;
		  }
			break;

		case 2: // corner
			startFlywheelTasks(true);
			kp = 0.5;
		  ki = 0.75;
		  kd = 0.0;
		  chainSpeed = 127;

		  tolerance = 5;

		 	Target = 182;

		  while (true) {
		    if (Error < tolerance && Error > -tolerance) {
		      motor[chn] = chainSpeed;
		      motor[rub] = 127;
		    }
		   	else {
		   		motor[chn] = 0;
		   		motor[rub] = 0;
		   	}
		  }
			break;

		case 3:
			startTask(pidController);

			//startTask(RPM);
			//startTask(error);
			//switchToBangBang(120);

			pid_Kp = 0.1;
			pid_Ki = 0.04;
			pid_Kd = 0.0;

			go(50, 55);
			wait1Msec(2000);

			stopTask(pidController);

			startGyroTasks();

			targetGyro = 250;
			wait1Msec(1500);
			stopGyroTasks();

			startTask(pidController);
			go(-35);



			//allmotors(100);
			//wait1Msec(1500);
			//allmotors(0);

		break;
	}
}
