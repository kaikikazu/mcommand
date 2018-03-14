#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define BUFSIZE (128)
#define ROW 3 //何列表記にするか

/*
個人的に使ってる自作lsコマンド
.c---------黄色
.py--------シアン
.exe-------水色
.js--------赤色
ディレクトリ----緑

固定3列で表示されます。
*/
int main(void)
{
	DIR *dir;
	struct dirent *dp;
	char *ret;
	int i = 0;
	struct stat buf;
	char dirname[256];

	if(getcwd(dirname, BUFSIZE) == 0){
		puts("FAILED");
	}

	dir=opendir(dirname);

	for(dp=readdir(dir);dp!=NULL;dp=readdir(dir)){
		if(dp->d_name[0] == '.'){
			continue;
		}
		stat(dp->d_name,&buf);

		if((buf.st_mode & S_IFMT) == S_IFDIR){
			printf("\x1b[32m");
			printf("%-25s",dp->d_name);
			printf("\x1b[39m");
		}else if((ret = strstr(dp->d_name,".py")) != NULL) {
			printf("\x1b[35m");
			printf("%-25s",dp->d_name);
			printf("\x1b[39m");
		}else if((ret = strstr(dp->d_name,".c")) != NULL) {
			printf("\x1b[33m");
			printf("%-25s",dp->d_name);
			printf("\x1b[39m");
		}else if((ret = strstr(dp->d_name,".exe")) != NULL) {
			printf("\x1b[36m");
			printf("%-25s",dp->d_name);
			printf("\x1b[39m");
		}else if((ret = strstr(dp->d_name,".js")) != NULL) {
			printf("\x1b[31m");
			printf("%-25s",dp->d_name);
			printf("\x1b[39m");
		}else{
			printf("%-25s",dp->d_name);
		}
		i++;
		//何列で表記するか
		if(i % ROW == 0){
			putchar('\n');
		}
	}
	closedir(dir);
	putchar('\n');
	return 0;
}
