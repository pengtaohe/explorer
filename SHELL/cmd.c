#include "shell.h"

#define ROOT       "\rroot"
#define DEBUG      "debug"
#define TEST	   "test"

extern CMD_TABLE cmdSetBaud;
extern CMD_TABLE cmdReset;

extern CMD_TABLE cmdTEST;

extern CMD_TABLE cmdSetIP;
extern CMD_TABLE cmdSetMask;
extern CMD_TABLE cmdSetGateWay;
extern CMD_TABLE cmdPing;

/* root 节点 */
DefShellCmd( cmdVersion, "ver", funcVersion, "show app version.", "", NULL, &cmdSetBaud ) 
{
	printf("\r\nversion: V01R10C01B001\r\n");
}	

DefShellCmd( cmdSetBaud, "setbaud", funcSetBaud, "set baud rate", "setbaud rate\n\rParameter: 9600|19200|38400|57600|115200", &cmdVersion, &cmdReset )
{
#if 0
	UINT32 baud;
	if((vty->argc == 0)||((strcmp(vty->argv[0],"?") == 0 )||(strcmp(vty->argv[0],"help") == 0 )))
	{
		printf( "setbaud rate\n\rParameter: 9600|19200|38400|57600|115200 \n\r" );
		return;
	}
	
	if( vty->argc != 1 ) vty_printf( "parameter error\n\r" );
	else
	{
		sscanf( vty->argv[0],"%ld",&baud );
		if(( 9600 == baud)||( 19200 == baud)||( 38400 == baud)||( 57600 == baud)||( 115200 == baud))
		{
			CONSOLE_BAUDRATE = baud;
			UART_Configure(CONSOLE_BAUDRATE, BOARD_MCK);
			printf("CONSOLE_BAUDRATE = %ld\r\n",CONSOLE_BAUDRATE);
		}
		else
		{
			printf( "setbaud rate\n\rParameter: 9600|19200|38400|57600|115200 \n\r" );
		}
	}	
#endif
}

DefShellCmd( cmdReset, "reset", funcReset, "reset. ", "", &cmdSetBaud, NULL )
{
#if 0
	if((strcmp(vty->argv[0],"?") == 0 )||(strcmp(vty->argv[0],"help") == 0 ))
	{
	    printf("reset local.\n\r");
		return;
	}
	else if( (vty->argc == 0 )||(strcmp(vty->argv[0],"local")==0)  )
	{
		printf("\n\rReset System...\n");
		reset_device();
	}   
	else
	{
		printf( "Parameter error!reset local.\n\r" );
	}
#endif
}


/* debug 节点 */
DefShellCmd( cmdShowMem, "read", funcShowMem, "show memory.", "", NULL, &cmdSetIP )
{}

DefShellCmd( cmdSetIP, "setip", funcmdSetIP, "set ip addr.", "", &cmdShowMem, &cmdSetMask )
{
	UINT32 addr;
	UINT8 ip_addr[4];
	extern void lwip_set_ipaddr(const char*);

	if( 1 != vty->argc )
	{
		printf("argument error\r\n");
		return;
	}

	if((strcmp(vty->argv[0],"?") == 0 )||(strcmp(vty->argv[0],"help") == 0 ))
	{
		printf(" eg: setip 192.168.1.1 \r\n");
		return;
	}
	else
	{
		addr = inet_addr(vty->argv[0]);
		if( INADDR_NONE == addr)
		{
			printf("IP address is incorrect, please retry\r\n");
			return;
		}
		ip_addr[0] = addr&0xff;		
		ip_addr[1] = addr>>8&0xff;
		ip_addr[2] = addr>>16&0xff;
		ip_addr[3] = addr>>24&0xff;

		lwip_set_ipaddr(ip_addr);
		
		return;
	}
}

DefShellCmd( cmdSetMask, "setmask", funcmdSetMask, "set subnet mask.", "", &cmdSetIP, &cmdSetGateWay )
{
	UINT32 addr;
	UINT8 ip_addr[4];
	extern void lwip_set_netmask(const char*);

	if( 1 != vty->argc )
	{
		printf("argument error\r\n");
		return;
	}

	if((strcmp(vty->argv[0],"?") == 0 )||(strcmp(vty->argv[0],"help") == 0 ))
	{
		printf(" eg: setmask 192.168.1.1 \r\n");
		return;
	}
	else
	{
		addr = inet_addr(vty->argv[0]);
		if( INADDR_NONE == addr)
		{
			printf("IP address is incorrect, please retry\r\n");
			return;
		}
		ip_addr[0] = addr&0xff;		
		ip_addr[1] = addr>>8&0xff;
		ip_addr[2] = addr>>16&0xff;
		ip_addr[3] = addr>>24&0xff;

		lwip_set_netmask(ip_addr);
		
		return;
	}
}

DefShellCmd( cmdSetGateWay, "setgateway", funcmdSetGateWay, "set gate way.", "", &cmdSetMask, &cmdPing )
{
	UINT32 addr;
	UINT8 ip_addr[4];
	extern void lwip_set_gw(const char*);

	if( 1 != vty->argc )
	{
		printf("argument error\r\n");
		return;
	}

	if((strcmp(vty->argv[0],"?") == 0 )||(strcmp(vty->argv[0],"help") == 0 ))
	{
		printf(" eg: setgateway 192.168.1.1 \r\n");
		return;
	}
	else
	{
		addr = inet_addr(vty->argv[0]);
		if( INADDR_NONE == addr)
		{
			printf("IP address is incorrect, please retry\r\n");
			return;
		}
		ip_addr[0] = addr&0xff;		
		ip_addr[1] = addr>>8&0xff;
		ip_addr[2] = addr>>16&0xff;
		ip_addr[3] = addr>>24&0xff;

		lwip_set_gw(ip_addr);
		
		return;
	}
}

DefShellCmd( cmdPing, "ping", funPing, "send ICMP ECHO_REQUEST to network hosts", "", &cmdSetGateWay, NULL )
{
#if 0
	UINT32 addr;
	UINT8 ip_addr[4];
	struct ip_addr dst;
	if((strcmp(vty->argv[0],"?") == 0 )||(strcmp(vty->argv[0],"help") == 0 ))
	{
		printf(" eg: ping 192.168.1.2 \r\n");
		return;
	}
	else if( 1 == vty->argc)
	{
		addr = inet_addr(vty->argv[0]);		
		if( INADDR_NONE == addr)
		{
			printf("Enter the IP address is incorrect, please re-enter\r\n");
			return;
		}

		struct netif *netif;
		
  		if ((netif = ip_route((struct ip_addr *)&addr)) == NULL) {
			return;
  		}
	}
#endif
}

/* TEST 节点 */
DefShellCmd( cmdTEST, "test1", funcTEST, "TEST-1", "", NULL, NULL )
{	
#if 0
	printf(" The is a test cmd!\n\r");
	return;		
#endif
}

extern NODE_TABLE node_test;
extern NODE_TABLE node_debug;
extern NODE_TABLE node_Root;

NODE_TABLE node_test = { NULL, &node_debug, NULL, NULL, &cmdTEST, TEST };
NODE_TABLE node_debug = { &node_test, &node_Root, NULL, NULL, &cmdShowMem, DEBUG };
NODE_TABLE node_Root = { &node_debug,NULL,NULL,NULL,&cmdVersion, ROOT };

