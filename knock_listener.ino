#define LED 13

void setupKnockListener() 
{
  pinMode(LED, OUTPUT);     
}

void onKnock()
{
  digitalWrite(LED, !digitalRead(LED));
}
