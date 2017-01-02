#define LED 8

void setupActions() 
{
  pinMode(LED, OUTPUT);     
}

void toggle230V()
{
  digitalWrite(LED, !digitalRead(LED));
}
