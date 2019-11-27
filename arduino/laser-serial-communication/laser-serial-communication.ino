String sentence = "bip boup";

int bits_rythm = 1000;

// analog pin connected to the diode
int receiverPin = 3;

// flags to add :
// MUST
//  * space
//  * a-z
//  * start transmission
//  * end transmission
// COULD
//  * ACK
//  * signal if transmission failure
char decodeLetter(int i)
{
  switch(i)
  {
    case 0: return ' ';
    case 1: return 'a';
    case 2: return 'b';
    case 3: return 'c';
    case 4: return 'd';
    case 5: return 'e';
    case 6: return 'f';
    case 7: return 'g';
    case 8: return 'h';
    case 9: return 'i';
    case 10: return 'j';
    case 11: return 'k';
    case 12: return 'l';
    case 13: return 'm';
    case 14: return 'n';
    case 15: return 'o';
    case 16: return 'p';
    case 17: return 'q';
    case 18: return 'r';
    case 19: return 's';
    case 20: return 't';
    case 21: return 'u';
    case 22: return 'v';
    case 23: return 'w';
    case 24: return 'x';
    case 25: return 'y';
    case 26: return 'z';
    default: return '0';
  }
}

void decodeMessage(boolean beats[], int size)
{
  int upCount = 0;
  for (int i=0;i<size;i++)
  {
    if (beats[i])
    {
      upCount++;
      Serial.print("1");
    }
    else
    {
      upCount = 0;
      Serial.print("0");
    }
    
    if (upCount == 5)
    {
      upCount++;
      Serial.println("FLAG");
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  boolean t[] = {
  true, true, true, true, true,
  true, false, true, true, false,
  true, true, true, true, true
  };
  decodeMessage(t, 15);

}

void loop() {
  //sendMessage(sentence);
}
