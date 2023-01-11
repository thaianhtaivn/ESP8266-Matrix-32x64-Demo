## This project is a very simple demo for how to use P4/P5 display (32x64) with ESP8266

#

### Part 1: Digital clock with internet time update

-  Connect ESP8266 pinout as below diagram:

   ![Part 1](/images/Part1.png)

-  Connect PI and PO as follows:

   | PI  | PO  |
   | --- | --- |
   | R2  | R1  |
   | G1  | R2  |
   | G2  | G1  |
   | B1  | G2  |
   | B2  | B1  |

-  Connect panel input (PI) to the ESP8266 / ESP32 as follows:

   | PI  | ESP8266 GPIO (NodeMCU) |     |     | NOTE                                                                         |
   | --- | ---------------------- | --- | --- | ---------------------------------------------------------------------------- |
   | A   | 01 - (TX)              |     |     |
   | B   | 02 - (D4)              |     |     |
   | C   | 15 - (D8)              |     |     | only for 1/8, 1/16, 1/32 scan BINARY mux pattern or 1/4 STRAIGHT mux pattern |
   | D   | 12 - (D6)              |     |     | only for 1/16, 1/32 scan BINARY mux pattern or 1/4 STRAIGHT mux pattern      |
   | E   | N/A                    |     |     | only for 1/32 scan                                                           |
   | LAT | 00 - (D3)              |     |     |
   | OE  | 03 - (RX)              |     |     |
   | CLK | 14 - (D5)              |     |     |
   | R1  | 13 - (D7)              |     |     |

### Part 2: Digital clock with RTC module DS1307

-  Connect I2C and ESP8266 as follows:

   | I2C | ESP      |
   | --- | -------- |
   | SCL | 5 - (D1) |
   | SDA | 4 - (D2) |

-  Connect ESP8266 pinout as below diagram:

   ![Part 2](/images/Part2.png)
