// A Keyset Keyboard with Buttons
// Requires USB keyboard bootloader from 
// http://mitchtech.net/arduino-usb-hid-keyboard/

// Keyboard report buffer
uint8_t buf[8] = { 0 };
  
// All the pin numbers in order from thumb to pinky
int buttons[] = { 12,11,10,9,8 };

// Base character
const int charbase = 96; // Value of character before a in ASCII table

// Store current chording total
int chord = 0;

// The character inputted
char pressed = 0;

// loop var
int i;

void setup () 
{
  for(i = 0;i < 5;i++)
  {
     pinMode(buttons[i],INPUT);
     // Apparently this enables internal pull-ups 
     digitalWrite(buttons[i],1); 
  }
  Serial.begin(9600);
  delay(200);
}

void loop ()
{  
  chord = 0;
  pressed = 0;
  for (i = 0;i < 5; i++)
  {
    if (digitalRead(buttons[i]) == HIGH) // The button has been pressed
    { 
      //Serial.println("A button has been pressed!");
      switch(i)
      {
         case 0: // thumb
           chord += 1;
           break;
         case 1: // first
           chord += 2;
           break;
         case 2: // middle
           chord += 4;
           break;
         case 3: // third
           chord += 8;
           break;
         case 4: // pinky
           chord += 16;
           break;
         default:
           break;
      }
    }
  }
  pressed = (char)(charbase + chord);
  if ((int)pressed > charbase)
    Serial.print(pressed);
  delay(120);
}
void keyboardsend(char inp) 
{
  // write key
  buf[2] = inp;
  Serial.write(buf,8);
  
  // release key
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf,8);
}
