task preloads() {
	while (true) {
		if (Error < tolerance && Error > -tolerance) {
      motor[chn] = 127;
    }
   	else {
   		motor[chn] = 0;
   		motor[rub] = 127;
   	}
	}
}
