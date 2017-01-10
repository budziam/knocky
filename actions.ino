#define LED8 8
#define LED9 9

void setupActions() 
{
  pinMode(LED8, OUTPUT);
  pinMode(LED9, OUTPUT);
  change230V(false);
}

void toggle230V()
{
  digitalWrite(LED8, !digitalRead(LED8));
}

void change230V(boolean value)
{
  digitalWrite(LED8, !value);
}

boolean get230VStatus()
{
  return !digitalRead(LED8);
}

void changeTimerIndicator(boolean value)
{
  digitalWrite(LED9, value);
}
