#define Network "***********"
#define Password "**********"










#define WebClient "<!DOCTYPE html>\
<html lang=\"en\">\
<head>\
<meta charset=\"UTF-8\">\
<title>ESP01 Client</title>\
</head>\
<body>\
<h1>Welcome WeeWs</h1>\
<h3>Click into the botton to toggle the LED</h3>\
<p>BLUE LED State <span id=\"BLED\">___ </span> </p>\
<p>RED LED State  <span id=\"RLED\">___ </span></p>\
<button id=\"1\" onclick = \"ledToggle(this.id)\">Blue LED</button>\
<button id=\"2\" onclick = \"ledToggle(this.id)\">Red LED</button>\
<p>The switch is <span id = \"SW\">___</span></p>\
<script>\
function ledToggle(clicked_id){\
var xhr = new XMLHttpRequest();\
var url = clicked_id;\
xhr.onreadystatechange = function(){\
if(this.readyState == 4 && this.status == 200)\
{\
if(this.responseText == \"10\")\
{\
document.getElementById(\"BLED\").innerHTML = \"OFF\";\
}else if(this.responseText == \"11\")\
{\
document.getElementById(\"BLED\").innerHTML = \"ON\";\
}else if(this.responseText == \"20\")\
{\
document.getElementById(\"RLED\").innerHTML = \"OFF\";\
}else if(this.responseText == \"21\")\
{\
document.getElementById(\"RLED\").innerHTML = \"ON\";\
}\
}\
};\
xhr.open(\"GET\",url,true);\
xhr.send();\
}\
document.addEventListener(\"DOMContentLoaded\",ledToggle,false);\
var myInterval = setInterval(dataStream,1000);\
function dataStream(){\
var xhr = new XMLHttpRequest();\
var url = \"0\";\
xhr.onreadystatechange = function(){\
if(this.readyState == 4 && this.status == 200)\
{\
if(this.responseText == \"00\")\
{\
document.getElementById(\"SW\").innerHTML = \"LOW\";\
}else if(this.responseText == \"01\")\
{\
document.getElementById(\"SW\").innerHTML = \"HIGH\";\
}\
}\
};\
xhr.open(\"GET\",url,true);\
xhr.send();\
}\
document.addEventListener(\"dataStream\",ledToggle,false)\
</script>\
</body>\
</html>\r\n"

void esp_mgr(char USART_3_msg[],char USART_2_msg[],unsigned short uart_3_mgr[],unsigned short uart_2_mgr[]);
// Menu init function
void esp_init(char USART_3_msg[],char USART_2_msg[],unsigned short uart_3_mgr[],unsigned short uart_2_mgr[]);
// Menu setup function
void esp_setup(char USART_3_msg[],char USART_2_msg[],unsigned short uart_3_mgr[],unsigned short uart_2_mgr[]);

// Menu display function
void esp_menu(void);
// Send Manual command to ESP
void esp_man_mode(char USART_3_msg[],char USART_2_msg[],unsigned short uart_3_mgr[],unsigned short uart_2_mgr[]);
// Core ESP01 function
int esp_core_cmd(char cmd[],char check_str[],short show, unsigned short int_time, char ESP_STR[], unsigned short ESP_mgr[]);
// Master ESP01 function
int esp_master_cmd(char cmd[],char check_str[],short show, unsigned short int_time, char ESP_STR[], unsigned short ESP_mgr[],unsigned short show_msg,char success[],char fail[]);
//Automatic connection using saved Network and password
int esp_net_connect(char ESP_STR[], unsigned short ESP_mgr[], char network[],char password[]);
//Input Network & Pass
int esp_net_man_connect(char ESP_STR[], unsigned short ESP_mgr[], char USER_STR[],unsigned short USER_mgr[]);

/*************************************************************************************/
/*
-----------------------ESP01 Server------------------------------
*/
/*************************************************************************************/
void esp_server(char USART_3_msg[],unsigned short uart_3_mgr[]);
char char_tracker(char str1[], char str2[]);
void esp_serv_send(char con_num[],char feedback_len[],int resp_time,char USART_3_msg[],unsigned short uart_3_mgr[]);
void esp_close_con(char con_num[]);
