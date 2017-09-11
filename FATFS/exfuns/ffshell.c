/*
 * Copyright (c)  , PengtaoHe, All rights reserved. 
 * 
 * Author: PengtaoHe <hept@foxmail.com>
 *
 */

#include "stdio.h"
#include "string.h"

#include "ffshell.h"

char g_CurrentDir[255] = "1:";

void fatfs_prompt(void)
{
	printf("%s>", g_CurrentDir);
}

void fatfs_showdisk(void)
{
	printf("0:  SD_Card\r\n");
	printf("1:  Flash\r\n");
	printf("2:  USB_Disk\r\n");
}

void fatfs_cd(const char* path)
{
	char n;

	if(!strncmp(path, "./", 2)) /* sub dir of current */
	{
		strcpy(&g_CurrentDir[strlen(g_CurrentDir)], path + 1);
	}
	else if(!strncmp(path, "..", 2)) /* parent dir of current */
	{
		n = strlen(g_CurrentDir);
		while(n--)
		{
			if('/' == g_CurrentDir[n])
			{
				g_CurrentDir[n] = '\0';
				break;
			}
		}
		/*
		p = strrstr(g_CurrentDir, "/");
		if(p)
		{
			*p = '\0';
		}
		*/	
	}
	else /* absolute path */
	{
		strcpy(g_CurrentDir, path);
	}
}

void fatfs_ll(const char* path)
{
	DIR dir;
	FILINFO fileinfo;

	if(NULL == path)
	{
		path = g_CurrentDir;
	}
	
	if(FR_OK != f_opendir(&dir, path))
	{
		printf(" open dir failed.\r\n");
		return;
	}

	while(FR_OK == f_readdir(&dir, &fileinfo))
	{
		if(0 == fileinfo.fname[0]) break;
		
		printf("%4s %8d %-s\r\n",
			fileinfo.fattrib & (1 << 4) ? "Dir" : "File",
			fileinfo.fsize,
			*fileinfo.lfname ? fileinfo.lfname : fileinfo.fname);
	}

	f_closedir(&dir);
}

void fatfs_format(void)
{
	FRESULT res;
	
	printf("Flash Disk Formatting...");
	res=f_mkfs("1:",1,4096);
	if(res==0)
	{
		printf("OK\r\n");
		f_setlabel((const TCHAR *)"1:flash");
	}
	else
	{
		printf("Error.%2X\r\n", res);
	}

	fatfs_cd("1:");
}

