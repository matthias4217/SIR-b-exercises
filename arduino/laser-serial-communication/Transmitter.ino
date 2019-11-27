
String texts = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

boolean bitss[5];

float delayBit = 25;

int led = 13;



int encodeLetter(const char c){
  int mycharInt = (int) c;

  if(mycharInt >= 97 && mycharInt <= 123){
    return mycharInt - 96; 
  }
  else{
    return 0;  
  }
  /*switch(c){
    case ' ': return 0;
    case 'a': return 1;
    case 'b': return 2;
    case 'c': return 3;
    case 'd': return 4;
    case 'e': return 5;
    case 'f': return 6;
    case 'g': return 7;
    case 'h': return 8;
    case 'i': return 9;
    case 'j': return 10;
    case 'k': return 11;
    case 'l': return 12;
    case 'm': return 13;
    case 'n': return 14;
    case 'o': return 15;
    case 'p': return 16;
    case 'q': return 17;
    case 'r': return 18;
    case 's': return 19;
    case 't': return 20;
    case 'u': return 21;
    case 'v': return 22;
    case 'w': return 23;
    case 'x': return 24;
    case 'y': return 25;
    case 'z': return 26;
    default: return 0;
  }*/
}

void encodeIntTobitss(int a){
  if(a>=16){
    a-=16;
    bitss[4] = 1;
  }
  else{
    bitss[4] = 0;  
  }

  if(a>=8){
    a-=8;
    bitss[3] = 1;  
  }
  else{
    bitss[3] = 0;  
  }

  if(a>=4){
    a-=4;
    bitss[2] = 1;  
  }
  else{
    bitss[2] = 0;  
  }
  
  if(a>=2){
    a-=2;
    bitss[1] = 1;  
  }
  else{
    bitss[1] = 0;  
  }

  if(a>=1){
    a-=1;
    bitss[0] = 1;  
  }
  else{
    bitss[0] = 0;  
  }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter a message");
  texts = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
}

void sendMessage(){


  if(texts.length() == 0){
    return;
  }


  Serial.println("Sending the message: "+texts);
  
  Serial.println("FLAG");
  //Send FLAG.
  for(int i = 0; i< 5; i++){
    digitalWrite(led, HIGH);
    delay(delayBit);
    Serial.print("1");
  }

  Serial.println("");
  Serial.println("Message:");

  
  for(int i = 0; i < texts.length(); i++){
    encodeIntTobitss(encodeLetter(texts[i]));
    for(int j = 4; j>=0; j--){
      if(bitss[j]){
           digitalWrite(led,HIGH);  
          Serial.print("1");
      }
      else{
        digitalWrite(led,LOW); 
            Serial.print("0");
      }
      delay(delayBit);
    }
  }  
  Serial.println("");

  Serial.println("FLAG");

  //Send FLAG.

  for(int i = 0; i< 5; i++){
    digitalWrite(led, HIGH);
    delay(delayBit);
    Serial.print("1");
  }

  digitalWrite(led, LOW);

  texts = "";
  Serial.println("Enter a message");
}

char rx_byte = 0;

void loop() {
  

  /*if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();
    texts += rx_byte;  
  }
  else{*/
      sendMessage();
 // }
  
  // put your main code here, to run repeatedly:

}
