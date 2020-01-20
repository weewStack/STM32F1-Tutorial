/********************Hardware********************/

1 - AT// Detect ESP01 / ESP8266

2 - AT+RESTORE// Restore ESP01

/********************Wifi********************/

3 - AT+CWMODE=1// Setup as connection to access point: Station mode

4 - AT+CWLAP// Scan and List available AP / Networt

5 - AT+CWJAP ="Network","Password"// Connect to AP / network router

/********************Connection********************/

6 - AT+CIPSTATUS// Information about connection

7 - AT+CIPMUX=1//Enabe multiple connections

8 - AT+CIPSERVER=1,80// Configure as TCP server for port 80

9 - AT+CIFSR// Get the IP address & Information about connection



10 - AT+CIPSEND=0,5//Server data load function / Sending data

11 - AT+CIPCLOSE=0//Close connection

