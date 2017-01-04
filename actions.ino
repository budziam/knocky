#define LED 8

void setupActions() 
{
  pinMode(LED, OUTPUT);     
}

void toggle230V()
{
  digitalWrite(LED, !digitalRead(LED));
}

void change230V(boolean value)
{
  if (value) {
    Serial.print("On\n");
  } else {
    Serial.print("Off\n");    
  }
  
  digitalWrite(LED, value);
}

boolean get230VStatus()
{
  return !!digitalRead(LED);
}
