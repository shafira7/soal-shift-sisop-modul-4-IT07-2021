#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <ctype.h> 

static const char *dirpath = "/home/nanda/Downloads";

int z = 0;

void creteLog(int level,char *call,const char *info){
	FILE *log = fopen("/home/nanda/Documents/SinSeiFS.log" , "a");
	time_t now = time(0);
	struct tm tstruct = *localtime(&now);
	int tahun=0,bulan=0,hari=0,jam=0,menit=0,detik=0;
	tahun = tstruct.tm_year + 1900;
	bulan = tstruct.tm_mon + 1;
	hari = tstruct.tm_mday;
	jam = tstruct.tm_hour;
	menit = tstruct.tm_min;
	detik = tstruct.tm_sec;
	if(level == 1){
		fprintf(log, "WARNING::%02d%02d%d-%02d:%02d:%02d:%s::%s\n",hari,bulan,tahun,jam,menit,detik,call,info);
	}
	else{
		fprintf(log, "INFO::%02d%02d%d-%02d:%02d:%02d:%s::%s\n",hari,bulan,tahun,jam,menit,detik,call,info);
	}
	fclose(log);
}

void logcrypt(char *level,  char *from , char *to){
	FILE *log = fopen("/home/nanda/Documents/CryptFS.log" , "a");

	if(to != NULL){
		fprintf(log,"%s :\n %s -> %s\n",level,from,to);
	}
	else{
		fprintf(log,"%s :\n %s\n",level,from);
	}
	fclose(log);
}

char *getExt (char fspec[]) {
    char *e = strrchr (fspec, '.');
    if (e == NULL)
        e = "";
    return e;
}

void encriptAtbash(char *enc){
	if(!strcmp(enc,".") || !strcmp(enc,"..")) return;
	int b=0;
	b = strlen(getExt(enc));
	for ( int i = 0; i < strlen(enc)-b ;i++) {
		if(!((enc[i]>=0&&enc[i]<65)||(enc[i]>90&&enc[i]<97)||(enc[i]>122&&enc[i]<=127))){
			if(enc[i]>='A'&&enc[i]<='Z')
				enc[i] = 'Z'+'A'-enc[i];
			if(enc[i]>='a'&&enc[i]<='z')
				enc[i] = 'z'+'a'-enc[i];
		} 
		if(((enc[i]>=0&&enc[i]<65)||(enc[i]>90&&enc[i]<97)||(enc[i]>122&&enc[i]<=127))){
		enc[i] = enc[i];    
		}
	}
}

void decriptAtbash(char *enc){
	if(!strcmp(enc,".") || !strcmp(enc,"..")) return;
	int flag1=0,flag2=0;
	if(enc[0]=='A' && enc[1]=='t' && enc[2]=='o' && enc[3]=='Z' && enc[4]=='_'){
		flag1 = 1;
		flag2 = 1;
	}
	int b=0;
	b = strlen(getExt(enc));
	for ( int i = 0; i < strlen(enc)-b ;i++) {
		if(enc[i] == '/'){
			flag1=0;
		}
		if((flag1!=1 && enc[i] != '/') && flag2==1){
			if(!((enc[i]>=0&&enc[i]<65)||(enc[i]>90&&enc[i]<97)||(enc[i]>122&&enc[i]<=127))){
				if(enc[i]>='A'&&enc[i]<='Z')
					enc[i] = 'Z'+'A'-enc[i];
				if(enc[i]>='a'&&enc[i]<='z')
					enc[i] = 'z'+'a'-enc[i];
			} 
		}
		if(((enc[i]>=0&&enc[i]<65)||(enc[i]>90&&enc[i]<97)||(enc[i]>122&&enc[i]<=127))){
		enc[i] = enc[i];    
		}
	}

}

void encriptRot(char *enc){
	if(!strcmp(enc,".") || !strcmp(enc,"..")) return;
	int b=0;
	b = strlen(getExt(enc));
	for ( int i = 0; i < strlen(enc)-b; i++) {
		if(!((enc[i]>=0&&enc[i]<65)||(enc[i]>90&&enc[i]<97)||(enc[i]>122&&enc[i]<=127))){
			if(enc[i]>='A'&&enc[i]<='Z') {
                enc[i] = 'Z'+'A'-enc[i];
                if (enc[i] >= 'N') enc[i] -= 13;
                else if (enc[i] < 'N') enc[i] += 13;
            }
			if(enc[i]>='a'&&enc[i]<='z') {
            enc[i] = 'z'+'a'-enc[i];
                if (enc[i] >= 'n') enc[i] -= 13;
                else if (enc[i] < 'n') enc[i] += 13;
            }
		} 
		if(((enc[i]>=0&&enc[i]<65)||(enc[i]>90&&enc[i]<97)||(enc[i]>122&&enc[i]<=127))){
		enc[i] = enc[i];    
		}
	}
}

void decriptRot(char *enc){
	if(!strcmp(enc,".") || !strcmp(enc,"..")) return;
	int flag1=0,flag2=0;
	if(enc[0]=='R' && enc[1]=='X' && enc[2]=='_'){
		flag1 = 1;
		flag2 = 1;
	}
	int b=0;
	b = strlen(getExt(enc));
	for ( int i = 0; i < strlen(enc)-b; i++) {
		if(enc[i] == '/'){
			flag1=0;
		}
		if((flag1!=1 && enc[i] != '/') && flag2==1){
			if(!((enc[i]>=0&&enc[i]<65)||(enc[i]>90&&enc[i]<97)||(enc[i]>122&&enc[i]<=127))){
				if(enc[i]>='A'&&enc[i]<='Z') {
					enc[i] = 'Z'+'A'-enc[i];
					if (enc[i] >= 'N') enc[i] -= 13;
					else if (enc[i] < 'N') enc[i] += 13;
				}
				if(enc[i]>='a'&&enc[i]<='z') {
				enc[i] = 'z'+'a'-enc[i];
					if (enc[i] >= 'n') enc[i] -= 13;
					else if (enc[i] < 'n') enc[i] += 13;
				}
			}
		} 
		if(((enc[i]>=0&&enc[i]<65)||(enc[i]>90&&enc[i]<97)||(enc[i]>122&&enc[i]<=127))){
		enc[i] = enc[i];    
		}
	}
}

void encriptVig(char* enc, char* k){
	
	int i;
	char cipher;
	int cipherValue;
	int len = strlen(k);
	int b=0;
	b = strlen(getExt(enc));

	encriptAtbash(enc);
	
	for(i=0; i<strlen(enc)-b; i++){
		if(islower(enc[i])){
			cipherValue = ( (int)enc[i]-97 + (int)tolower(k[i % len])-97 ) % 26 +97;
			cipher = (char)cipherValue;
		}
		else {
			cipherValue = ( (int)enc[i]-65 + (int)toupper(k[i % len])-65 ) % 26 +65;
			cipher = (char)cipherValue;
		}

		if(isalpha(enc[i])){
			enc[i] = cipher;
		}
		else{
			enc[i] = enc[i];
		}
	}
	
	
}

void decriptVig(char* enc, char* k){
	if(!strcmp(enc,".") || !strcmp(enc,"..")) return;
	int flag1=0,flag2=0;
	if(enc[0]=='R' && enc[1]=='X' && enc[2]=='_'){
		flag1 = 1;
		flag2 = 1;
	}
	int i;
	char cipher;
	int cipherValue;
	int len = strlen(k);
	int b=0;
	b = strlen(getExt(enc));

	decriptAtbash(enc);

	for(i=0; i<strlen(enc)-b; i++){
		if(enc[i] == '/'){
			flag1=0;
		}
		if((flag1!=1 && enc[i] != '/') && flag2==1){
			if(islower(enc[i])){
				cipherValue = ( (int)enc[i]-97 + (int)tolower(k[i % len])-97 ) % 26 +97;
				cipher = (char)cipherValue;
			}
			else{
				cipherValue = ( (int)enc[i]-65 + (int)toupper(k[i % len])-65 ) % 26 +65;
				cipher = (char)cipherValue;
			}

			if(isalpha(enc[i])){
				enc[i] = cipher;
			}
			else {
				enc[i] = enc[i];
			}
		}
	}
	
}
  
//Get file attributes.
static int xmp_getattr(const char *path, struct stat *stbuf)
{
	int res;
	char fpath[1000];
	char* k = "SISOP";
	char *AtoZ = strstr(path,"AtoZ_");
	char *RX = strstr(path,"RX_");

	sprintf(fpath, "%s%s",dirpath,path);
	
	if(AtoZ != NULL){
        decriptAtbash(AtoZ);
        sprintf(fpath,"%s/%s",dirpath,AtoZ);
	}

	if(RX != NULL){
		if(z == 1) {
			decriptRot(RX);
			sprintf(fpath,"%s/%s",dirpath,RX);
		}
		else if (z == 2) {
			decriptVig(RX, k);
        	sprintf(fpath,"%s/%s",dirpath,RX);
		}

	}
	
	res = lstat(fpath, stbuf);
	
	if (res == -1)
		return -errno;
	
	return 0;
}


//Read the target of a symbolic link
static int xmp_readlink(const char *path, char *buf, size_t size)
{
	char ingfo[1000];
	strcpy(ingfo,path);
	creteLog(0, "READLINK" ,ingfo);
    int res;
	char fpath[1000];	
	sprintf(fpath, "%s%s",dirpath,path);
	
    	res = readlink(fpath, buf, size - 1);

	if (res == -1)
        return -errno;
    	buf[res] = '\0';
    	return 0;
}


//Read directory
static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
	char fpath[1000];
	char* k = "SISOP";
	char *AtoZ = strstr(path,"AtoZ_");
	char *RX = strstr(path,"RX_");
	sprintf(fpath, "%s%s",dirpath,path);
	if(strcmp(path,"/") == 0){
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
  	else{  		
		if(AtoZ != NULL ){
        	decriptAtbash(AtoZ);
        	sprintf(fpath,"%s/%s",dirpath,AtoZ);
        }

		if (RX != NULL){
			if(z == 1) {
				decriptRot(RX);
				sprintf(fpath,"%s/%s",dirpath,RX);
			}
			else if (z == 2) {
				decriptVig(RX, k);
				sprintf(fpath,"%s/%s",dirpath,RX);
			}

		}
  	}
	
	int res = 0;
	DIR *dp;
	struct dirent *de;
	(void) offset;
	(void) fi;
	dp = opendir(fpath);
	if (dp == NULL)
	return -errno;
	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		
		if(AtoZ != NULL){
			encriptAtbash(de->d_name);
		} 
		
		if (RX != NULL){
			if(z == 1) encriptRot(de->d_name);
			if (z == 2) {
				encriptVig(de->d_name, k);
			}
		}
		
		res = (filler(buf, de->d_name, &st, 0));
		if(res!=0) break;
	}
	closedir(dp);
	return 0;
}

//Rename a file
static int xmp_rename(const char *from, const char *to)
{
    int res;
	char from1[1000];
	char to1[1000];
	char* k = "SISOP";
	char *fratoz = strstr(from,"AtoZ_");
	char *ftatoz = strstr(to,"AtoZ_");
	char *frrx = strstr(from,"RX_");
	char *ftrx = strstr(to,"RX_");		
	sprintf(from1,"%s%s",dirpath,from);
	sprintf(to1,"%s%s",dirpath,to);
		
	if(fratoz != NULL && ftatoz == NULL){
		logcrypt("decrypt Atbash - RENAME", from1 , to1);
	}
	
	if(ftatoz != NULL && fratoz == NULL){
		logcrypt("encrypt Atbash - RENAME", from1 , to1);
		decriptAtbash(ftatoz);
		sprintf(to1,"%s/%s",dirpath,ftatoz);
	}

	if(frrx != NULL && ftrx == NULL){
		if (z == 2){
			logcrypt("decrypt Atbash & Vigenere - RENAME", from1 , to1);
		} else if ( z == 1) {
			logcrypt("decrypt Atbash & ROT13 - RENAME", from1 , to1);
		}
	}
		
	if(frrx == NULL && ftrx != NULL){
		logcrypt("encrypt Atbash & Vigenere - RENAME", from1 , to1);
		decriptVig(ftrx, k);
		sprintf(to1,"%s/%s",dirpath,ftrx);
		z = 2;
	}
		
        res = rename(from1, to1);
		char str[1000];
		sprintf(str,"%s::%s",from,to);
		creteLog(0,"RENAME",str);
        if (res == -1)
                return -errno;
        return 0;
}


//Read data from an open file
static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
	char ingfo[1000];
	strcpy(ingfo,path);
	creteLog(0, "READ", ingfo);
	int fd;
	int res;
    	char fpath[1000];

	sprintf(fpath, "%s%s",dirpath,path);
	
	(void) fi;
	
	fd = open(fpath, O_RDONLY);

	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

//Create a file node.
static int xmp_mknod(const char *path, mode_t mode, dev_t rdev)
{
    int res;
	char fpath[1000];
	sprintf(fpath ,"%s%s",dirpath,path);
	char ingfo[1000];
	strcpy(ingfo,path);
	creteLog(0, "MKNOD", ingfo);

	if (S_ISREG(mode)) {
	res = open(fpath, O_CREAT | O_EXCL | O_WRONLY, mode);
	if (res >= 0)
		res = close(res);
	}
	else if (S_ISFIFO(mode)){
		res = mkfifo(fpath, mode);
	}
	else{
		res = mknod(fpath, mode, rdev);
	}
		
        if (res == -1)
                return -errno;
        return 0;
}

//Create a directory.
static int xmp_mkdir(const char *path, mode_t mode)
{
	creteLog(0,"MKDIR",path);
    int res;
	char fpath[1000];
	char *RX = strstr(path,"RX_");
	sprintf(fpath, "%s%s",dirpath,path);

	if(strstr(fpath,"AtoZ_") != NULL){
		logcrypt("encrypt Atbash - MKDIR", fpath, NULL);
	}
	if(strstr(fpath,"RX_") != NULL){
		logcrypt("encrypt Atbash & ROT13 - MKDIR", fpath , NULL);
		decriptRot(RX);
		sprintf(fpath,"%s/%s",dirpath,RX);
		z = 1;
	}
        res = mkdir(fpath, mode);
        if (res == -1)
                return -errno;
        return 0;
}

//Remove a file
static int xmp_unlink(const char *path)
{
	creteLog(1,"UNLINK",path);
        int res;
	char fpath[1000];
	sprintf(fpath,"%s%s",dirpath,path);
        res = unlink(fpath);

        if (res == -1)
                return -errno;
        return 0;
}

//Remove a directory
static int xmp_rmdir(const char *path)
{
	creteLog(1, "RMDIR" ,path);
        int res;
	char fpath[1000];
	sprintf(fpath,"%s%s",dirpath,path);
        res = rmdir(fpath);
        if (res == -1)
                return -errno;
        return 0;
}


static int xmp_symlink(const char *from, const char *to)
{
	char str[1000];
	sprintf(str,"%s::%s",from,to);
	creteLog(0,"SYMLINK",str);
        int res;
        res = symlink(from, to);

        if (res == -1)
                return -errno;
        return 0;
}


static int xmp_link(const char *from, const char *to)
{
		char str[1000];
		sprintf(str,"%s::%s",from,to);
		creteLog(0,"LINK",str);
        int res;
        res = link(from, to);
        if (res == -1)
                return -errno;
        return 0;
}

static struct fuse_operations xmp_oper = {
	
.getattr 		= xmp_getattr,
.readdir 		= xmp_readdir,
.readlink		= xmp_readlink,
.read 			= xmp_read,
.mkdir 			= xmp_mkdir,
.mknod 			= xmp_mknod,
.symlink 		= xmp_symlink,
.unlink 		= xmp_unlink,
.rmdir 			= xmp_rmdir,
.rename 		= xmp_rename,
.link 			= xmp_link,

};


int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
