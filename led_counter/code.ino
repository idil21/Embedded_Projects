int ledPins[] = {6,5,4,3,2};
int WAIT_TIME = 1000;
int INCREMENT_VALUE = 1;
byte count;

void setup()
{
  for(int i = 0; i< 5 ; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
  count=0;
  
}

void loop()
{
  
  count += INCREMENT_VALUE;
  displayBinaryValue(count);
  delay(WAIT_TIME); // Wait for 1000 millisecond(s)
}

void displayBinaryValue(byte num)
{
  for (byte i = 0; i < 5; i++) {
    
    if (bitRead(num, i)==1)
    {
      digitalWrite(ledPins[i], HIGH); 
    }
    else
    {
      digitalWrite(ledPins[i], LOW); 
    }
   
  }
}
  