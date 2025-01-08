#define dir_pin 21
#define pwm_pin 23
const int encoder_pin_A = 27;
const int encoder_pin_B = 14;
// const int baseSpeed=50;
volatile int pulse_count = 0; 
const int ppr = 133;          
const int duration = 10;  
float rpm = 0;
unsigned long previousTime = 0;
double gear_ratio = 1/11.2 ;
double motorSpeed;
double output=0;
const float Kp = 0.8; 
const float Ki = 0.01;
const float Kd = 0.0;
int desired_rpm = 220;
int P,D;
static int I = 0;
int error;
int lastError = 0;   
void setup() {

  Serial.begin(115200);

  pinMode(encoder_pin_A, INPUT);
  pinMode(encoder_pin_B, INPUT);

  attachInterrupt(digitalPinToInterrupt(encoder_pin_A), StartInterruptA, RISING);
}


void loop() {
  // Serial.println(pulse_count);
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= duration) {
  previousTime = currentTime;
   noInterrupts(); 
  int pps = pulse_count;
  pulse_count = 0; 
  interrupts(); 
  // Serial.println(pps);
    rpm = pps*60000/ppr*gear_ratio;
    // Serial.println(rpm);
    error = desired_rpm - rpm;  
    P = error;
    I = I + error;
    D = error-lastError;
    output = Kp*P + Ki*I + Kd*D; 

    int motorSpeed = rpm + output;
    if(motorSpeed<0)
    {
      motorSpeed =0;
    }
    if(motorSpeed>255)
    {
      motorSpeed = 255;
    }
    Serial.printf("Curr rpm: %.5f   motorSpeed: %d\n",rpm,motorSpeed);
    digitalWrite(dir_pin,LOW);
    analogWrite(pwm_pin,abs(motorSpeed));
    
    lastError = error; 
  }
  
  }


void StartInterruptA() {

  if (digitalRead(encoder_pin_B)) {
    pulse_count++;
  } else {
    pulse_count--;
  }
}
