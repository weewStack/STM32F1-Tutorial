#include "uart_drive.h"
#include "help_func.h"
#include "esp01_drive.h"


void esp_mgr(char USART_3_msg[],char USART_2_msg[],unsigned short uart_3_mgr[],unsigned short uart_2_mgr[])
{
	if(uart_2_mgr[1] == 1)
		{	
			esp_setup(USART_3_msg,USART_2_msg,uart_3_mgr,uart_2_mgr);
		}
		if(uart_3_mgr[1] == 1)
		{
			esp_server(USART_3_msg,uart_3_mgr);			
		}
}
/*************************************************************************************/
/*
-----------------------ESP01 Setup Menu------------------------------
*/
/*************************************************************************************/
// Menu init function
void esp_init(char USART_3_msg[],char USART_2_msg[],unsigned short uart_3_mgr[],unsigned short uart_2_mgr[])
{
	systick_init();
UART_init(2,115200);
UART_init(3,115200);
DelayMs(100);
	
	if(esp_master_cmd("AT\r\n","OK",0, 0, USART_3_msg, uart_3_mgr,1,"\nThe ESP is Detected\n","\nDetection failed\n"))
	{
		if(esp_master_cmd("AT+CIPSTATUS\r\n","STATUS:2",0,0, USART_3_msg, uart_3_mgr,1,"\nConnected to AP\n","\nNot connected\n")==0)
		{
			esp_net_connect(USART_3_msg, uart_3_mgr, Network,Password);
				
		}
		esp_menu();
	}
	else
	{
		UART_SEND(2,"\nSelect the next step: \nD: Detect the ESP01\n");
	}

}

// Menu setup function
void esp_setup(char USART_3_msg[],char USART_2_msg[],unsigned short uart_3_mgr[],unsigned short uart_2_mgr[])
{
	if(find_strL("D",USART_2_msg))
	{
		if(esp_master_cmd("AT\r\n","OK",0, 0, USART_3_msg, uart_3_mgr,1,"\nThe ESP is Detected\n","\nDetection failed\n"))
		{
		esp_menu();
		}
		else{UART_SEND(2,"\nSelect the next step: \nD: Detect the ESP01\n");}
	}
	else if(esp_master_cmd("AT\r\n","OK",0, 0, USART_3_msg, uart_3_mgr,0,"",""))
	{
		if(find_strL("M",USART_2_msg))
		{
			str_empty(USART_2_msg);
			uart_2_mgr[1] = 0;
			esp_man_mode(USART_3_msg,USART_2_msg,uart_3_mgr,uart_2_mgr);
		}
		else if(find_strL("R",USART_2_msg))
		{
			esp_master_cmd("AT+RESTORE\r\n","ready",0, 200, USART_3_msg, uart_3_mgr,1,"\nRestore succesful\n","\nRestore failed\n");
			esp_master_cmd("AT+CWMODE=1\r\n","OK",0, 0, USART_3_msg, uart_3_mgr,0,"","");
		}
		else if(find_strL("L",USART_2_msg))
		{
			esp_master_cmd("AT+CWLAP\r\n","OK",1,500, USART_3_msg, uart_3_mgr,1,"\nNetwork listed\n","\nscan failed\n");
		}
		else if(find_strL("A",USART_2_msg))
		{
			esp_net_connect(USART_3_msg, uart_3_mgr, Network,Password);
		}
		else if(find_strL("I",USART_2_msg))
		{
			str_empty(USART_2_msg);
			uart_2_mgr[1] = 0;
			esp_net_man_connect(USART_3_msg, uart_3_mgr, USART_2_msg,uart_2_mgr);
		}
		else if(find_strL("P",USART_2_msg))
		{
			esp_master_cmd("AT+CIFSR\r\n","OK",1,0, USART_3_msg, uart_3_mgr,0,"\n","\n");
		}
		else if(find_strL("C",USART_2_msg))
		{
			esp_master_cmd("AT+CIPSTATUS\r\n","STATUS:2",0,0, USART_3_msg, uart_3_mgr,1,"\nConnected to AP\n","\nNot connected\n");
		}
		else
		{
			UART_SEND(2,"\nThe input : \n");
			UART_SEND(2,USART_2_msg);
			UART_SEND(2,"\nis not an option in the Menu\n");
		}
		esp_menu();	
	}
	else
		{
			UART_SEND(2,"\nThe input : \n");
			UART_SEND(2,USART_2_msg);
			UART_SEND(2,"\nis not an option in the Menu\n");
		}
		uart_2_mgr[1] = 0;
		str_empty(USART_2_msg);
}

// Menu display function
void esp_menu(void)
{
	UART_SEND(2,"\nSelect the next step: \n\
	M: Manual input ESP\n\
	R: Reset\n\
	L: List Networks\n\
	P: Get IP address\n\
	A: Automatic connection using saved Network and password\n\
	I: Input Network & Pass\n\
	C: Check Network Connection\n");
}

// Send Manual command to ESP
void esp_man_mode(char USART_3_msg[],char USART_2_msg[],unsigned short uart_3_mgr[],unsigned short uart_2_mgr[])
{
	int keep = 1;
	UART_SEND(2,"\nStarting the manual input mode\n");
	UART_SEND(2,"\nQ: Quit manual mode\n");
	
	while(keep)
	{
		if(uart_2_mgr[1] == 1)
		{	
			if(find_strL("Q",USART_2_msg))
			{
				keep = 0;
			}
			else
			{
				Concatstr(USART_2_msg,"\r\n");
				UART_SEND(3,USART_2_msg);
				uart_2_mgr[1] = 0;
				str_empty(USART_2_msg);
			}
			
		}
		
		if(uart_3_mgr[1] == 1)
		{
			UART_SEND(2,USART_3_msg);
			uart_3_mgr[1] = 0;
			uart_3_mgr[5] = 10;
			str_empty(USART_3_msg);
		}
		
		
	}
	UART_SEND(2,"\nStotping the manual input mode\n");
}

// Core ESP01 function
int esp_core_cmd(char cmd[],char check_str[],short show, unsigned short int_time, char ESP_STR[], unsigned short ESP_mgr[])
{
	unsigned short result = 0;
	if(int_time)
	{
		ESP_mgr[5] = int_time;
	}
	UART_msg(3,cmd,ESP_mgr);
	if(show)
	{
		UART_SEND(2,ESP_STR);
	}
	
	if(find_str(check_str,ESP_STR))
	{
		result = 1;
	}
	
	str_empty(ESP_STR);
	return result;
	
	
}

// Master ESP01 function
int esp_master_cmd(char cmd[],char check_str[],short show, unsigned short int_time, char ESP_STR[], unsigned short ESP_mgr[],unsigned short show_msg,char success[],char fail[])
{
	int resutl = 0;
	if(esp_core_cmd(cmd, check_str,show,int_time, ESP_STR, ESP_mgr))
	{
		if(show_msg)
		{UART_SEND(2,success);}
		resutl = 1;
	}
else
	{
		if(show_msg)
		{UART_SEND(2,fail);}
	}
	return resutl;
}

//Automatic connection using saved Network and password
int esp_net_connect(char ESP_STR[], unsigned short ESP_mgr[], char network[],char password[])
{
	char esp_cmd[120]="AT+CWJAP=\"";
	int result = 0;
	int connect = 0;
	Concatstr(esp_cmd,network);
	Concatstr(esp_cmd,"\",\"");
	Concatstr(esp_cmd,password);
	Concatstr(esp_cmd,"\"\r\n");
	connect += esp_master_cmd(esp_cmd,"CONNECTED",0,500, ESP_STR, ESP_mgr,1,"\nConnected\n","\nConnection failed\n");
	connect += esp_master_cmd("AT+CIPMUX=1\r\n","OK",0,0, ESP_STR, ESP_mgr,0,"","");
	connect += esp_master_cmd("AT+CIPSERVER=1,80\r\n","OK",0,0, ESP_STR, ESP_mgr,0,"","");
	if(connect ==3)
	{result = 1;}
	return result;
}

//Input Network & Pass
int esp_net_man_connect(char ESP_STR[], unsigned short ESP_mgr[], char USER_STR[],unsigned short USER_mgr[])
{
	char esp_cmd[120]="AT+CWJAP=\"";
	int result = 0;
	int connect = 0;
	
	UART_msg(2,"\nInput the network name: \n",USER_mgr);
	Concatstr(esp_cmd,USER_STR);
	str_empty(USER_STR);
	Concatstr(esp_cmd,"\",\"");
	UART_msg(2,"\nInput the password: \n",USER_mgr);
	Concatstr(esp_cmd,USER_STR);
	str_empty(USER_STR);
	Concatstr(esp_cmd,"\"\r\n");
	
	
	connect += esp_master_cmd(esp_cmd,"CONNECTED",1,1000, ESP_STR, ESP_mgr,1,"Connected","Connection failed");
	connect += esp_master_cmd("AT+CIPMUX=1\r\n","OK",0,0, ESP_STR, ESP_mgr,0,"","");
	connect += esp_master_cmd("AT+CIPSERVER=1,80\r\n","OK",0,0, ESP_STR, ESP_mgr,0,"","");
	if(connect ==3)
	{result = 1;}
	return result;
}

/*************************************************************************************/
/*
-----------------------ESP01 Server------------------------------
*/
/*************************************************************************************/

void esp_server(char USART_3_msg[],unsigned short uart_3_mgr[])
{
			/*
			Connection number
			Action_id
			Len_Feedback
			check "SEND"
			*/
	char esp_con[1];
	char esp_id[1];
	char actions[10] ="012";
	char feedback_len[6] = "\0\0\0\0\0\0";
	char feedback[2] = "\0\0";
	
	if(find_str("+IPD,",USART_3_msg))
	{
		/// Get the esp_con & esp_id
		esp_con[0] = char_tracker("+IPD,", USART_3_msg);
		esp_id[0] = char_tracker(":GET /", USART_3_msg);
		
		/*
		UART_SEND(2,"\nConnection number is :");
		UART_SEND(2,esp_con);
		UART_SEND(2,"\naction ID is :");
		UART_SEND(2,esp_id);
		UART_SEND(2,"\n");
		*/
		uart_3_mgr[1] = 0;		
		str_empty(USART_3_msg);
		if(esp_id[0] == ' ')
		{
			UART_SEND(2,"\nLoading page\n");
			int2char(len_str(WebClient),feedback_len);
			esp_serv_send(esp_con,feedback_len,10,USART_3_msg,uart_3_mgr);
			UART_SEND(3,WebClient);
			esp_core_cmd("\r\n","SEND",0,5,USART_3_msg,uart_3_mgr);
			esp_close_con(esp_con);	
		}
		else if(find_str(esp_id,actions))
		{
			if(esp_id[0] == '0')
			{
				feedback[0] = esp_id[0];
				feedback[1] = R_GP(PA,4) + 0x30;
				//UART_SEND(2,"Streamin...\n");
			}
			else if(esp_id[0] == '1')
			{
				toggle_GP(PA,1);
				feedback[0] = esp_id[0];
				feedback[1] = R_GP(PA,1) + 0x30;
			}else if(esp_id[0] == '2')
			{
				toggle_GP(PA,0);
				feedback[0] = esp_id[0];
				feedback[1] = R_GP(PA,0) + 0x30;
			}
			//UART_SEND(2,feedback);
			esp_serv_send(esp_con,"2",10,USART_3_msg,uart_3_mgr);
			UART_SEND(3,feedback);
			esp_core_cmd("\r\n","SEND",0,5,USART_3_msg,uart_3_mgr);
			esp_close_con(esp_con);	
		}
		else
		{
			esp_close_con(esp_con);	
		}
	}
	uart_3_mgr[1] = 0;		
	str_empty(USART_3_msg);

}

char char_tracker(char str1[], char str2[])
{
	int match = 0;
	/*
	1- First loop going through all the chars of STR2
	2- Nested loop inside the first to go through the STR1
	*/
	char target = '\0';
	int STRlen = len_str(str1);
	int i = 0;
	int j = 0;
	int test = 0;
	
	while((str2[i + STRlen-1] != '\0' | str2[i + STRlen] != '\0') & (match ==0))
	{
	for(j=0; j<= STRlen;j++)
		{
			if(str1[j] == str2[i+j])
			{
				test ++;
				if(test == STRlen+1)
				{
					match =1 ;
					target = str2[i+j+1];
				}
			}
		}
	test = 0;
	i++;
	}

	return target;
}

void esp_serv_send(char con_num[],char feedback_len[],int resp_time,char USART_3_msg[],unsigned short uart_3_mgr[])
{
	char cmd_send[50] = "AT+CIPSEND=\0\0\0\0\0\0\0\0\0";
	Concatstr(cmd_send,con_num);
	Concatstr(cmd_send,",");
	Concatstr(cmd_send,feedback_len);
	Concatstr(cmd_send,"\r\n");
	esp_core_cmd(cmd_send,">",0,resp_time,USART_3_msg,uart_3_mgr);

}

void esp_close_con(char con_num[])
{
char cmd_send[50] = "AT+CIPCLOSE=\0\0\0\0\0\0\0\0\0";
Concatstr(cmd_send,con_num);
Concatstr(cmd_send,"\r\n");
UART_SEND(3,cmd_send);
}
	

