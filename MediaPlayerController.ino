//A small sketch to control a media player, a Windows executable - supported functionalities are to pause/resume a song, skip to next song or previous song

int CMDSTOP = 8;
int CMDNEXT = 9;
int CMDPREVIOUS = 7;

void setup()
{
//the button pins
  pinMode(CMDSTOP, INPUT);
  pinMode(CMDNEXT, INPUT);
  pinMode(CMDPREVIOUS, INPUT);

//some LEDs for debugging  
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

//  
  digitalWrite(CMDSTOP, 1);
  digitalWrite(CMDNEXT, 1);
  digitalWrite(CMDPREVIOUS, 1);
  Serial.begin(9600);
  
}

void loop()
{
  int intPlayStop = digitalRead(CMDSTOP);
  int intNext = digitalRead(CMDNEXT);
  int intPrevious = digitalRead(CMDPREVIOUS);
  if(intPlayStop==0)
  {
   SendCommand("TogglePlay\n", 12); 
  }
  if(intNext==0)
  {
   SendCommand("Next\n", 13); 
  }
  if(intPrevious==0)
  {
    SendCommand("Previous\n", 11); 
  }
}

void SendCommand(char strCommand[], int intPin)
{
 Notify(intPin);
 Serial.write(strCommand); 
}


void Notify(int intPin)
{
  digitalWrite(intPin, 1);
  delay(500);
  digitalWrite(intPin, 0);
}
