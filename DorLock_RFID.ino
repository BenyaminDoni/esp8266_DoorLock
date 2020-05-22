#include <SPI.h>
#include <MFRC522.h>           //Library RFID

//inisialisasi pin pada RFID
const int PIN_RST = 5;  
const int PIN_SS  = 4; 

String uidTag = "";     
const int pinrelay = D4; //inisialisasi pin relay
const int pinLED = D3; //LED Merah

// Pembuatan objek MFRC522 
MFRC522 mfrc(PIN_SS, PIN_RST); 

void setup() {
  Serial.begin(9600);
  SPI.begin();  
  mfrc.PCD_Init(); 

  pinMode (pinrelay, OUTPUT);
  pinMode (pinLED, OUTPUT);
  
//  // Cek versi software MFRC555
//  byte versi = mfrc.PCD_ReadRegister(mfrc.VersionReg);
//  if (versi == 0x00 || versi == 0xFF) {
//    Serial.println("Modul tidak ada!");
//    while (true); // Abaikan perintah-2 berikutnya   
//  }
}

void loop() {
  digitalWrite (pinrelay, HIGH);
  digitalWrite (pinLED, LOW);
  
  // Cek untuk kartu yang baru disisipkan 
  if (!mfrc.PICC_IsNewCardPresent())
    return;

  // Jika nomor tag tidak diperoleh
  if (!mfrc.PICC_ReadCardSerial())
    return;

  // Peroleh UID pada tag
  uidTag = "";
  for (byte j = 0; j < mfrc.uid.size; j++) {
    char teks[3];
    sprintf(teks, "%02X", mfrc.uid.uidByte[j]);
    uidTag += teks;
  }

// jika tag RFID sesuai dengan yang terdaftar
  if  (uidTag.substring(0) == "AA887889"){
    digitalWrite (pinrelay, LOW);
    Serial.println("ID:");
    Serial.println(uidTag);
    delay (1000);
    Serial.println(" Selamat Datang ");
    Serial.println(" Doni ");
    delay (5000);
  }

//ketika tag RFID tidak sesuai dengan data
  else {
  Serial.println("Akses ditolak !!");
  digitalWrite(pinLED,HIGH);
  delay (2000);
  }

  // Ubah status kartu ACTIVE ke status HALT
  mfrc.PICC_HaltA();
}
