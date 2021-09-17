
  
#include "gp_drive.h"
#include "timer_drive.h"

int main(void)
{
		
	Digital_Output(PA,8);
	
	
	


	
while(1)
	{
		
		TDelay_Milli(500);
		toggle_GP(PA,8);
	
		
	}
}
