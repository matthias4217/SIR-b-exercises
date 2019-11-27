String sentence = "bip boup";

String resSentence = "";

int bits_rythm = 25;

// if signal > 90 : laser is off (else on)
int threshold = 84;//90;

// analog pin connected to the diode
int receiverPin = 3;

int len_loop = 5+5*8;

bool flagReceived = false;
int bitUpCount = 0;
boolean currentLetter[5];
int letterPointer = 0;

// TODO : add synchronization mechanism

// flags to add :
// MUST
//  * space
//  * a-z
//  * start transmission
//  * end transmission
// COULD
//  * ACK
//  * signal if transmission failure
String decodeIntToLetter(int i)
{
  switch(i)
  {
    case 0: return " ";
    case 1: return "a";
    case 2: return "b";
    case 3: return "c";
    case 4: return "d";
    case 5: return "e";
    case 6: return "f";
    case 7: return "g";
    case 8: return "h";
    case 9: return "i";
    case 10: return "j";
    case 11: return "k";
    case 12: return "l";
    case 13: return "m";
    case 14: return "n";
    case 15: return "o";
    case 16: return "p";
    case 17: return "q";
    case 18: return "r";
    case 19: return "s";
    case 20: return "t";
    case 21: return "u";
    case 22: return "v";
    case 23: return "w";
    case 24: return "x";
    case 25: return "y";
    case 26: return "z";
    case 30: return "SYNC";
    case 31: return "FLAG";
    default: return "UKNOWN";
  }
}

String decodeLetter(boolean beats[])
{
  int letterCode = beats[0] * 16 + beats[1] * 8 + beats[2] * 4 + beats[3] * 2 + beats[4] * 1;
  return decodeIntToLetter(letterCode);
  //Serial.println(letter);
}

void decodeMessage(boolean beats[], int size)
{
  int payload[] = {0, 0, 0, 0, 0};
  int payloadPointer = 0;
  String letter = " ";
  int upCount = 0;
  bool messageSending = false;
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

    if (messageSending)
    {
      payload[payloadPointer] = beats[i];
      if (payloadPointer == 4)
      {
        Serial.print(".");
        // compute letter index
        int letterCode = payload[0] * 16 + payload[1] * 8 + payload[2] * 4 + payload[3] * 2 + payload[4] * 1;
        letter = decodeIntToLetter(letterCode);
        Serial.println(letter);
        payloadPointer = 0;
      }
      else {
        payloadPointer++;
      }
    }
    
    if (upCount == 5)
    {
      upCount++;
      messageSending = !messageSending;
      Serial.println("FLAG");
    }
  }
}

void setup(){
  Serial.begin(9600);
  /*
  boolean t[] = {
  true, true, true, true, true,
  true, false, true, true, false,
  true, true, true, true, true
  };
  decodeMessage(t, 15);
  */

}

void loop() {
  //boolean beats[len_loop];
  int readValue = analogRead(receiverPin); // raw value from the light sensor
  //Serial.println(readValue);
  bool currentBit = readValue <= threshold; // bit read during this loop
  if (currentBit)
  {
    bitUpCount ++;
      Serial.print(1);
  } else {
    bitUpCount = 0;
      Serial.print(0);
  }

  if (flagReceived)
  {
    currentLetter[letterPointer] = currentBit;
    letterPointer++;
    if (letterPointer == 5)
    {
      Serial.print(".");
      String thisLetter = decodeLetter(currentLetter);
      resSentence += thisLetter;
      Serial.println(thisLetter);
      if (thisLetter == "FLAG")
      {
        flagReceived = !flagReceived;
        Serial.println(resSentence);
      }
      letterPointer = 0;
      bitUpCount=0;
      //Serial.println();
    }
  }
  
  // flag received, so we change the settings
  if (bitUpCount == 5)
  {
    Serial.println();
    flagReceived = !flagReceived;
    bitUpCount = 0;
    letterPointer = 0;
    if (flagReceived)
    {
      Serial.println("Decoding...");
    } else {
      Serial.println("Standby");
    }
  }
  delay(bits_rythm);
}
