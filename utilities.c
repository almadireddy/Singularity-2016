void driveL(float power) {
	motor[lW1] = motor[lW2] = motor[lW3] = power;
}

void driveR(float power) {
	motor[rW1] = motor[rW2] = motor[rW3] = power;
}

void setFlywheel(float p) {
	motor[fly1] = motor[fly2] = p;
}

void startFlywheelTasks(bool bang = false) {
	startTask(RPM);
	startTask(error);

	if (!bang)
		startTask(bangBang);
	else
		startTask(Flywheel);

	startTask(motorrun);
}

void switchToBangBang(int t, bool preload = false) {
	Target = t;

	stopTask(Flywheel);
	startTask(bangBang);
  startTask(motorrun);
  startTask(toneBack);

  if (preload)
  	startTask(preloads);
}

void switchToPID(int t, bool preload = false) {
	Target = t;

	stopTask(bangBang);
	startTask(Flywheel);
  startTask(motorrun);
  startTask(toneBack);

  if (preload)
  	startTask(preloads);
}

void stopFlywheelTasks() {
	stopTask(motorrun);
	stopTask(bangBang);
	stopTask(preloads);
	setFlywheel(0);
}
