#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

const int BEEP_PITCH = 502;
const int FEEDBACK_PITCH = 294;

const int BUZZER_PIN = 3; 
const int START_BUTTON_PIN = 2;
const int CONFIG_BUTTON_PIN = 9;

const long DURATIONS[] = {60000, 90000, 120000, 180000, 240000, 30000};
const int CONFIG_COUNT = sizeof(DURATIONS) / sizeof(DURATIONS[0]);
const long WARNING_DURATION = 30000;
const long READY_DURATION = 10000;

int configIndex = 0;
long startTime = 0;
long currentDuration = 0;

void showTimerSettingOnScreen(bool showPressStart = true){
  lcd.clear();
  lcd.print("Time: ");
  lcd.setCursor(13,0);
  lcd.print(DURATIONS[configIndex]/1000);

  if (showPressStart){
    lcd.setCursor(0,1);
    lcd.print("Press start");
  }
}

void setup() {
  lcd.begin(16, 2);
  // you can now interact with the LCD, e.g.:
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(START_BUTTON_PIN, INPUT);
  pinMode(CONFIG_BUTTON_PIN, INPUT);
  lcd.print("Hello");
}

int beep(int count, int frequency = BEEP_PITCH, int duration = 800, int delayBetweenBeeps = 1000){

  int delaySum = 0;
  tone(BUZZER_PIN, frequency, duration);
  for (int i=1; i<count; i++){
    delay(delayBetweenBeeps);
    delaySum += delayBetweenBeeps;
    tone(BUZZER_PIN, frequency, duration);
  }
  return delaySum;
}

void configButtonPressed()
{
  //move to next duration in duration array
  configIndex = (configIndex + 1) % CONFIG_COUNT;

  showTimerSettingOnScreen();

  delay(100);
}

void displayTime(long time)
{
    lcd.setCursor(7,1);
    lcd.print(time);
    lcd.print("    ");

}

bool timerLoop(long duration, long warningTime = -1)
{
  long start = millis();
  bool exitButtonPressed = false;
  long timer;
  if (warningTime >= duration)
  {
    warningTime = -1;
  }

  do 
  {
    delay(100);
    timer = duration - (millis() - start) ;
    long timeToShow = timer/1000 + 1;
    displayTime(timeToShow);
    if (timeToShow == warningTime/1000)
    {
      beep(1, BEEP_PITCH, 400);
      warningTime = -1;
    }

    int startButtonState = digitalRead(START_BUTTON_PIN);
    if (startButtonState == HIGH) {
      exitButtonPressed = true;
    }
    delay(100);
  }while(!exitButtonPressed && timer > 0);
  displayTime(0);
  return exitButtonPressed;
}
// the loop function runs over and over again forever
void loop() {
  showTimerSettingOnScreen();
  while(true){
    // wait for user's input for new round or configuration change    
    int startButtonState = digitalRead(START_BUTTON_PIN);
    if (startButtonState == HIGH) {
      currentDuration = DURATIONS[configIndex];
      showTimerSettingOnScreen(false);
      break;
    }

    int configButtonState = digitalRead(CONFIG_BUTTON_PIN);
    if (configButtonState == HIGH){
      configButtonPressed();
    }
  }

  beep(2);
  bool emergencyExit = timerLoop(READY_DURATION);
  if (!emergencyExit)
  {
    beep(1);
    emergencyExit = timerLoop(currentDuration, WARNING_DURATION);
  }
  beep(3);
}

