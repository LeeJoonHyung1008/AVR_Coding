#define ANALOG_PIN_TIMER_INTERVAL 2 // milliseconds
unsigned long thisMillis_old;

static long analogPinTimer = 0; 
int fc = 20; // cutoff frequency 
double dt = ANALOG_PIN_TIMER_INTERVAL/1000.0; // sampling time
double lambda = 2*PI*fc*dt;
double x = 0.0;
double x_filter = 0.0;
double x_filter_old = 0.0;
double y = 0.0;
double y_filter = 0.0;
double y_filter_old = 0.0;
int z = 0;
  // 10부터 증가해서 test 할 것. 50이 적절했음.
  
char state_x = 0;
char state_y = 0;

void setup() 
{
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long deltaMillis = 0; // clear last result
  unsigned long thisMillis = millis();  
  if (thisMillis != thisMillis_old) 
  { 
    deltaMillis = thisMillis-thisMillis_old; // delta Millis를 구하고
    thisMillis_old = thisMillis;             // 현재의 Millis 값을 Old 값으로 Update 해준다.
  } 

  analogPinTimer -= deltaMillis; 
  if (analogPinTimer <= 0) {  
    analogPinTimer += ANALOG_PIN_TIMER_INTERVAL; 
 
    x = analogRead(A0); // 아날로그값 읽기
    x_filter = lambda/(1+lambda)*x+1/(1+lambda)*x_filter_old; //필터된 값
    x_filter_old = x_filter; // 센서 필터 이전값 업데이트

    y = analogRead(A1); // 아날로그값 읽기
    y_filter = lambda/(1+lambda)*y+1/(1+lambda)*y_filter_old; //필터된 값
    y_filter_old = y_filter; // 센서 필터 이전값 업데이트

    Serial.print(x);
    Serial.print(",");
    Serial.println(x_filter);

    Serial.print(y);
    Serial.print(",");
    Serial.println(y_filter);

 }
}

 
