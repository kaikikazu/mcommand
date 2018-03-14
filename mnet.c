#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 128
#define MAX 4

/*
個人的に使ってるコマンド。上に書いた順から接続を試み、接続する
何でもSUCCESS!!と返ってくるので修正案件。
動作自体は正常にしている。
*/
int main(void){
	//繋ぎたいWi-FiのSSID
	char ssid[MAX][BUF]={"ArchWireless-5G","elecom5g-24D600","Buffalo-A-7BC8","Rits-Webauth"};
	char disconnect[BUF]={"netsh wlan disconnect"};
	char cmd[BUF] = "netsh wlan connect name=";
	char cmdline[BUF];
	char buf[BUF];
	FILE *fp;
	int i;

	system(disconnect);
	for(i=0;i<MAX;i++){
		strcpy(cmdline,cmd);
		strcat(cmdline,ssid[i]);
		if((fp=popen(cmdline,"r")) ==NULL) {
			perror ("can not exec commad");
			exit(EXIT_FAILURE);
		}
		feof(fp);
		fgets(buf, sizeof(buf), fp);
		if(strstr(buf,ssid[i]) == NULL){
			printf("=>SUCCESS!! connect to %s\n",ssid[i]);
			(void) pclose(fp);
			return(0);
		}else{
			printf("=>FAIL. not connect to %s\n",ssid[i]);
			system(disconnect);
		}
		(void) pclose(fp);
	}

	exit (EXIT_SUCCESS);
}