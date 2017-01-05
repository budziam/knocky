#define LED 8

void setupActions() 
{
  pinMode(LED, OUTPUT);
  change230V(false);
}

void toggle230V()
{
  digitalWrite(LED, !digitalRead(LED));
}

void change230V(boolean value)
{
  debug(2, "%s", value ? "On" : "Off");
  
  digitalWrite(LED, !value);
}

boolean get230VStatus()
{
  return !digitalRead(LED);
}
