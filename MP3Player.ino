#include <SoftwareSerial.h>
SoftwareSerial mp3modul(5,6);
#define nextMusik 0x01
#define prevMusik 0x02
#define volumeUp 0x04
#define volumeDown 0x05
#define reset 0x0C
#define play 0x0D
#define pause 0x0E
#define device 0x09
#define sdCard 0x02

void send_command(int8_t command, int8_t data){
  delay(20);
  mp3modul.write((int8_t) 0x7E);
  mp3modul.write((int8_t) 0xFF);
  mp3modul.write((int8_t) 0x06);
  mp3modul.write((int8_t) command);
  mp3modul.write((int8_t) 0x00);
  mp3modul.write((int8_t) data >> 8);
  mp3modul.write((int8_t) data);
  mp3modul.write((int8_t) 0xEF);
}

void setup(){
  Serial.begin(9600);
  mp3modul.begin(9600);
  delay(500);
  send_command(device,sdCard);
  delay(500);
}

void  loop(){
  char c;
  if (Serial.available ()){
    c = Serial.read();
    mp3command(c);
  }
  delay(1000);
}


void mp3command (char c) {
  switch(c){
    case 'm':
      Serial.println("Play musik");
      send_command(play,0);
      break;
    case 'p':
      Serial.println("musik berhenti");
      send_command(pause,0);
      break;
    case '>':
      Serial.println("next musik");
      send_command(nextMusik,0);
      break;
    case '<':
      Serial.println("previus musik");
      send_command(prevMusik,0);
      break;
    case '+':
      Serial.println("volume naikup");
      send_command(volumeUp,0);
      break;
    case '-':
      Serial.println("volume musik down");
      send_command(volumeDown,0);
      break;
    default:
      Serial.println("Instruksi Manajemen Musik");
      Serial.println("m = play musik");
      Serial.println("p = musik behenti");
      Serial.println("> = next musik");
      Serial.println("< = previus musik");
      Serial.println("+ = volume musik naik");
      Serial.println("- = volume musik turun");
      break;
  }
}