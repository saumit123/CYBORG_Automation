#include<EEPROM.h> 
#include <SPI.h> 
#include <MFRC522.h> 

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const char* ssid = "GUDDU BHAIYA SYSTUMM";
const char* password = "BeenaBauji@6969";

#define BOTtoken "6461335356:AAG8Bqbl1FsbFzZh5Mc09_OR1K-cJIo17M8"
#define CHAT_ID "-1001967160817"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
 
#define RST_PIN         22          
#define SS_PIN          5  
int sz;        
String tagid = ""; 
MFRC522 mfrc522(SS_PIN, RST_PIN);

String UID[100] = {"13 87 B3 43 ","13 B3 C0 43 ","93 89 DA 42 ","63 FD B9 43 "};
String names[100] = {"Raj Bhai","Monalisa Di","Sovit Bhai","Nipen Bhai"};
String status[100] = {"Room is closed","Room is open"};
int flag=0;
int cnt=0;
int sts=0;

void setup() { 
 Serial.begin(9600); 
 while (!Serial);  
 SPI.begin();   
 mfrc522.PCD_Init();  
 delay(4);    
 mfrc522.PCD_DumpVersionToSerial(); 
 //Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks...")); 
 WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting");
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 Serial.println(("Please Scan the card"));

}

 
void loop() {
  

  if(cnt == 1){
    flag=0;
  }
 
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
 
  sz = mfrc522.uid.size; 
  tagid.toUpperCase(); 
 
  //Serial.println(tagid); 
  mfrc522.PICC_HaltA();
  
  for(int j=0;j<4;j++){
    if(tagid==UID[j] && flag==1){
      //Serial.println(names[j]);
      Serial.print(names[j]+" has the key.");
      Serial.println();
      bot.sendMessage(CHAT_ID,names[j]+" Has the key");
      cnt = 1;
      //sts++;
    }else if(tagid=="B3 8A 4A 42 "){
      flag=1;
      cnt=0;
      Serial.println("Please scan personal card");
      mfrc522.PICC_HaltA();

    }
  }
  tagid="";
  // if(sts%2==0){
  //   Serial.println("Room is Closed");
  //   bot.sendMessage(CHAT_ID, "Room is CLOSED");
  //   sts+=1;

  // }else{
  //   Serial.println("Room is Open");
  //   bot.sendMessage(CHAT_ID, "Room is OPEN");
  // }
  //sts++;
  //flag=0; 
  
  //delay(1000); 
}


























