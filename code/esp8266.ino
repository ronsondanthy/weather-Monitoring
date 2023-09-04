/*
 *
 * Change SSID and PASS to match your WiFi settings.
 * The IP address is displayed to soft serial upon successful connection.
 *
 */

//Leonardo
//Serial_ & dbgTerminal = Serial;
//HardwareSerial & espSerial = Serial1;

////UNO & M328P
#include <SoftwareSerial.h>
SoftwareSerial dbgTerminal(10, 11); // RX, TX
HardwareSerial & espSerial = Serial;

//
////MEGA2560 & Due
//HardwareSerial & dbgTerminal = Serial;
//HardwareSerial & espSerial = Serial1;

#define BUFFER_SIZE 512

#define SSID  "abcd"      // change this to match your WiFi SSID
#define PASS  "12345678"  // change this to match your WiFi password
#define PORT_SERVER  "8080"           // using port 8080 by default

char buffer[BUFFER_SIZE];

// By default we are looking for OK\r\n
char OKrn[] = "OK\r\n";
byte wait_for_espSerial_respSerialonse(int timeout, char* term = OKrn) {
  unsigned long t = millis();
  bool found = false;
  int i = 0;
  int len = strlen(term);
  // wait for at most timeout milliseconds
  // or if OK\r\n is found
  while (millis() < t + timeout) {
    if (espSerial.available()) {
      buffer[i++] = espSerial.read();
      if (i >= len) {
        if (strncmp(buffer + i - len, term, len) == 0) {
          found = true;
          break;
        }
      }
    }
  }
  buffer[i] = 0;
  dbgTerminal.print(buffer);
  return found;
}

void setup() {
  espSerial.begin(9600);
  dbgTerminal.begin(9600);
  dbgTerminal.println("Begin...");
  setupWiFi();
  // print device IP address
  dbgTerminal.print("Device IP Address:");
  espSerial.println("AT+CIFSR");
  wait_for_espSerial_respSerialonse(1000);
}

bool read_till_eol() {
  static int i = 0;
  if (espSerial.available()) {
    buffer[i++] = espSerial.read();
    if (i == BUFFER_SIZE)  i = 0;
    if (i > 1 && buffer[i - 2] == 13 && buffer[i - 1] == 10) {
      buffer[i] = 0;
      i = 0;
      dbgTerminal.print(buffer);
      return true;
    }
  }
  return false;
}

void loop() {
  int ch_id, packet_len;
  char *pb;
  if (read_till_eol()) {
    if (strncmp(buffer, "+IPD,", 5) == 0) {
      // request: +IPD,ch,len:data
      sscanf(buffer + 5, "%d,%d", &ch_id, &packet_len);
      if (packet_len > 0) {
        // read serial until packet_len character received
        // start from :
        pb = buffer + 5;
        while (*pb != ':') pb++;
        pb++;
        if (strncmp(pb, "GET /", 5) == 0) {
          wait_for_espSerial_respSerialonse(1000);
          dbgTerminal.println("-> serve homepage");
          serve_homepage(ch_id);
        }
      }
    }
  }
}
void serve_homepage(int ch_id) {
  String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nConnection: close\r\n";
  String content = "";
  content += "Hello World!!!";

  header += "Content-Length:";
  header += (int)(content.length());
  header += "\r\n\r\n";
  espSerial.print("AT+CIPSEND=");
  espSerial.print(ch_id);
  espSerial.print(",");
  espSerial.println(header.length() + content.length());
  if (wait_for_espSerial_respSerialonse(2000, "> ")) {
    espSerial.print(header);
    espSerial.print(content);
  } else {
    espSerial.print("AT+CIPCLOSE=");
    espSerial.println(ch_id);
  }
}


void setupWiFi() {
  // try empty AT command
  espSerial.println("AT");
  wait_for_espSerial_respSerialonse(1000);

  // set mode 1 (client)
  espSerial.println("AT+CWMODE=1");
  wait_for_espSerial_respSerialonse(1000);

  // reset WiFi module
  espSerial.print("AT+RST\r\n");
  wait_for_espSerial_respSerialonse(1500);

  // join AP
  espSerial.print("AT+CWJAP=\"");
  espSerial.print(SSID);
  espSerial.print("\",\"");
  espSerial.print(PASS);
  espSerial.println("\"");
  // this may take a while, so wait for 5 seconds
  wait_for_espSerial_respSerialonse(5000);

  espSerial.println("AT+CIPSTO=30");
  wait_for_espSerial_respSerialonse(1000);

  // start server
  espSerial.println("AT+CIPMUX=1");
  wait_for_espSerial_respSerialonse(1000);

  espSerial.print("AT+CIPSERVER=1,"); // turn on TCP service
  espSerial.println(PORT_SERVER);
  wait_for_espSerial_respSerialonse(1000);

}
