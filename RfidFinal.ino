#include<EEPROM.h> 
#include <SPI.h> 
#include <MFRC522.h> 
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "realme 9 Pro 5G";
const char* password = "y66xxix5";

#define BOTtoken "6461335356:AAG8Bqbl1FsbFzZh5Mc09_OR1K-cJIo17M8"
#define CHAT_ID "-1001967160817"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
 
#define RST_PIN    22          
#define SS_PIN      5  
#define GREENLED1  25
#define GREENLED2  26
#define REDLED     27
#define buzzer     14

String tagid = ""; 
MFRC522 mfrc522(SS_PIN, RST_PIN);

String UID[100] = {"13 87 B3 43 ","13 B3 C0 43 ","93 89 DA 42 ","63 FD B9 43 ","B3 8A 4A 42 "};
String names[100] = {"Raj Bhai","Monalisa Di","Sovit Bhai","Nipen Bhai","Mrinal Bhai"};

byte flag=0;
byte count=0;

void setup() { 
  pinMode(GREENLED1,OUTPUT);
  pinMode(GREENLED2,OUTPUT);
  pinMode(REDLED,OUTPUT);
  pinMode(buzzer,OUTPUT);

 Serial.begin(9600); 
 while (!Serial);  
 SPI.begin();   
 mfrc522.PCD_Init();  
 delay(4);    
 mfrc522.PCD_DumpVersionToSerial(); 
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting");
    Serial.println("....");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(("Please Scan Master card"));
}

void loop() {
 if ( ! mfrc522.PICC_IsNewCardPresent()) { 
  return; 
 } 
 if ( ! mfrc522.PICC_ReadCardSerial()) { 
  return; 
 } 
  for(int i=0;i<mfrc522.uid.size;i++){ 
    tagid.concat(String(mfrc522.uid.uidByte[i],HEX)); 
    tagid.concat(" "); 
  }  
  tagid.toUpperCase(); 
  Serial.println(tagid); 
  mfrc522.PICC_HaltA();

  if(flag==1 && count ==0){
   for(int j=0;j<50;j++){
      if(tagid==UID[j]){
      Serial.print(names[j]+" opened Cyborg room.");
      Serial.println();
      bot.sendMessage(CHAT_ID,names[j]+" opened Cyborg room");
      Access();
      count = 1;
      flag= 0;
      mfrc522.PICC_HaltA();
    }}
  }
    else if(flag==1 && count ==1){
     for(int j=0;j<50;j++){
      if(tagid==UID[j]){
      Serial.print(names[j]+" closed Cyborg room.");
      Serial.println();
      bot.sendMessage(CHAT_ID,"Cyborg room closed: "+names[j]+" has the key");
      Access();
      count = 0;
      flag =0;
      mfrc522.PICC_HaltA();
     }}
    }
    else if(tagid=="7C 9C 1E 49 "){
      flag=1;
      masterkey();
      Serial.println("Please scan personal card");
      mfrc522.PICC_HaltA();
      }
      else{
        Serial.println("Access denied");
        Serial.println("Enter the master key first");
        denied();
      }
   tagid=""; 
}

void masterkey(){
  digitalWrite(GREENLED1,HIGH);
  digitalWrite(buzzer,HIGH);
  delay(1000);
  digitalWrite(GREENLED1,LOW);
  digitalWrite(buzzer,LOW);
}
void Access(){
  digitalWrite(buzzer,HIGH);
  digitalWrite(GREENLED2,HIGH);
  delay(1000);
  digitalWrite(buzzer,LOW);
  digitalWrite(GREENLED2,LOW);
}
void denied(){
  digitalWrite(REDLED,HIGH);
  digitalWrite(buzzer,HIGH);
  delay(4000);
  digitalWrite(REDLED,LOW);
  digitalWrite(buzzer,LOW);
}
