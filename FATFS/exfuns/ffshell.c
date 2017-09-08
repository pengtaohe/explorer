/*
 * Copyright (c)  , PengtaoHe, All rights reserved. 
 * 
 * Author: PengtaoHe <hept@foxmail.com>
 *
 */

#include "stdio.h"
#include "string.h"

#include "ffshell.h"

char g_CurrentDir[255] = "\0";

void fatfs_showdisk(void)
{
	printf("0:  SD_Card\r\n");
	printf("1:  Flash)\r\n");
	printf("2:  USB_Disk\r\n");
}

void fatfs_cd(const char* path)
{
	strcpy(&g_CurrentDir[strlen(g_CurrentDir)], path);
}

void fatfs_ll(const char* path)
{
	DIR dir;
	FILINFO fileinfo;
	WORD findex;

	if(NULL == path)
	{
		path = g_CurrentDir;
	}
	
	if(FR_OK != f_opendir(&dir, path))
	{
		printf(" open dir failed.\r\n");
		return;
	}

	findex = dir.index;

	while(FR_OK == f_readdir(&dir, &fileinfo))
	{

		printf("%4s %8d %-s\r\n",
			fileinfo.fattrib & (1 << 4) ? "Dir" : "File",
			fileinfo.fsize,
			*fileinfo.lfname ? fileinfo.lfname : fileinfo.fname);

		if(dir.index == findex)
		{
			break;
		}
	}

	f_closedir(&dir);
}

