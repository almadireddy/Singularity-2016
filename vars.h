// Flywheel
float kp = 0.02;
float ki = 0.195;
float kd = 0.3;
float FlyRPM;
float Value;
float Error;
float Target;
float speed;
float LastError;
float Derivative;
float Integral;
float CurrentValue;
int integralCap = 200;
int tolerance = 5;

int maxSpeed = 127;
int minSpeed = 20;

int tone;
int tm = 6;
// End Flywheel

// Auton Selection
const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;

int count = 0;
// End Auton Selection

// Drive Straight
float ticksPerRevolution = 261.33333;
float ticksPerInch = ticksPerRevolution / (4 * PI);

#define PID_DRIVE_MAX       80
#define PID_DRIVE_MIN     (-127)

#define PID_INTEGRAL_LIMIT  50

float  pid_Kp = 0.1;
float  pid_Ki = 0.04;
float  pid_Kd = 0.0;

static int   pidRunning = 1;
static float pidRequestedValue;

float  pidSensorCurrentValue;

float  pidError;
float  pidLastError;
float  pidIntegral;
float  pidDerivative;
float  pidDrive;

float  secondary;
float  difference;
float  constant;

bool   atTarget = false;
int    dt = 5;
// End Drive Straight

// Gyroscope
float currentValueGyro;
float currentValueGyro2;
float targetGyro = 0;
float errorGyro;
float speedGyro;
float kpGyro = 0.075;
float kiGyro = 0.07;
float kdGyro = 0.12;
float integralGyro;
float lastErrorGyro;
float derivativeGyro;

float estimate = 1; //current estimate
float Gestimate = 0.001; //current estimate
float G2estimate = 0.001; //current estimate
float G3estimate = 0.001; //current estimate
float gyroAvg;

// end gyroscope

// User Control
string mainBattery, backupBattery;
int chainSpeed = 127;
int t = 15;
float ch3, ch1, ch2;
