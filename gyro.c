task gyroDrift() {
	int gyroError = 0;
	float lastGyro;
	while(true) {
		if ( abs(lastGyro - SensorValue[gyro]) < 2)
			gyroError += lastGyro - SensorValue[gyro];

		lastGyro = SensorValue[gyro];
		currentValueGyro = SensorValue[gyro] + gyroError;

		wait1Msec(100);
	}
}

task gyroTurn() {
	while(true) {
		errorGyro = targetGyro - currentValueGyro;
		derivativeGyro = errorGyro - lastErrorGyro;
		integralGyro = integralGyro + lastErrorGyro;
		lastErrorGyro = errorGyro;
		if(abs(integralGyro) > 380)
		{
			integralGyro = 0;
		}
		if(errorGyro == 0)
		{
			integralGyro = 0;
		}

		speedGyro = kpGyro * errorGyro + kiGyro * integralGyro + kdGyro * derivativeGyro;
		driveL(-speedGyro);
		driveR(speedGyro);

		wait1Msec(25);
	}
}

task kFilter() {
	float kG; //kalman gain
	float Eest = 10; // error in esitmate
	float Emea = 20; //error in measurement

	float lastEstimate; //last estimate
	float measurement;

	float GkG; //kalman gain
	float GEest = 10; // error in esitmate
	float GEmea = 20; //error in measurement

	float GlastEstimate; //last estimate
	float Gmeasurement;

	float G2kG; //kalman gain
	float G2Eest = 10; // error in esitmate
	float G2Emea = 20; //error in measurement

	float G2lastEstimate; //last estimate
	float G2measurement;

	float G3kG; //kalman gain
	float G3Eest = 10; // error in esitmate
	float G3Emea = 20; //error in measurement

	float G3lastEstimate; //last estimate
	float G3measurement;

	while(true) {
		lastEstimate = estimate;
		measurement = FlyRPM;

		kG = Eest / (Eest + Emea);

		estimate = lastEstimate + kG * (measurement - lastEstimate);
		Eest = (1 - kG) * (lastEstimate);

		GlastEstimate = Gestimate;
		Gmeasurement = currentValueGyro;

		GkG = GEest / (GEest + GEmea);

		Gestimate = GlastEstimate + GkG * (Gmeasurement - GlastEstimate);
		GEest = (1 - GkG) * (GlastEstimate);

		G2lastEstimate = G2estimate;
		G2measurement = currentValueGyro2;

		G2kG = G2Eest / (G2Eest + G2Emea);

		G2estimate = G2lastEstimate + G2kG * (G2measurement - G2lastEstimate);
		G2Eest = (1 - G2kG) * (G2lastEstimate);

		gyroAvg = (Gestimate + G2estimate) / 2;

		G3lastEstimate = G3estimate;
		G3measurement = gyroAvg;

		G3kG = G3Eest / (G3Eest + G3Emea);

		G3estimate = G3lastEstimate + G3kG * (G3measurement - G3lastEstimate);
		G3Eest = (1 - G3kG) * (G3lastEstimate);
		wait1Msec(25);
	}
}
