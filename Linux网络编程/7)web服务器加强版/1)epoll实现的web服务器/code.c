/* ************************************************************************
 *       Filename:  code.c
 *    Description:  
 *        Version:  1.0
 *        Created:  2018年09月02日 15时52分51秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/


#include <stdio.h>
int main(int argc, char *argv[])
{

	char buf[128]="";
	buf[0]=0xe8;
	buf[1]=0x8b;
	buf[2]=0xa6;
	buf[3]=0xe7;
	buf[4]=0x93;
	buf[5]=0x9c;
	printf("buf=%s\n",buf);
	return 0;
}


