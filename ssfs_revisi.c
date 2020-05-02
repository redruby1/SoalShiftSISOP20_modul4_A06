#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <pwd.h>
#include <grp.h>

static  const  char *dirpath = "/Users/Anisa_Aurafitri/Documents";

char str[1000];
int i, x;

char message[1000] = "9(ku@AW1[Lmvgax6q`5Y2Ry?+sF!^HKQiBXCUSe&0M.b%rI'7d)o4~VfZ*{#:}ETt$3J-zpc]lnh8,GwP_ND|jO";
int key = 10, titik;

char *enkripsi(char code[1000]) {
	
	for(i = 0; (i < strlen(code) && code[i] != '\0'); i++) {
		if(code[i] != '/') {
	      	titik = strchr(message, code[i]) - message;
	        code[i] = message[(titik + key) % strlen(message)];
    	}
	}
	
	return code;
}

char *dekripsi(char code[1000]) {
	
	for(i = 0; (i < strlen(code) && code[i] != '\0'); i++) {
		if(code[i] != '/') {
			titik = strchr(message, code[i]) - message;
        	code[i] = message[(titik + (strlen(message)-key)) % strlen(message)];
		}
	}
	
	return code;
}

char *get_eks(char code[1000]) {
	const char *dot = strrchr(code, '.');
    if(!dot || dot == code) return "";
    return dot;
}

static  int  xmp_getattr(const char *path, struct stat *stbuf) {
	int res;
	char lokasi[1000];
	char fpath[1000];

	sprintf(lokasi, "%s", path);
	enkripsi(lokasi);

	sprintf(fpath,"%s%s",dirpath,lokasi);
	res = lstat(fpath, stbuf);

	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, 
			off_t offset, struct fuse_file_info *fi) {
	
	char lokasi[1000];
	char fpath[1000];

	sprintf(lokasi, "%s", path);
	enkripsi(lokasi);
	
	if(strcmp(path,"/") == 0) {
		path = dirpath;
		sprintf(fpath,"%s",path);
	}
	else {
    	sprintf(fpath, "%s%s", dirpath, lokasi);
	}
	
	DIR *dp;
	struct dirent *de;
	
	(void) offset;
	(void) fi;

	dp = opendir(fpath);
	
	if(dp == NULL)
		return -errno;

	while((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
		
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		
		if(strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
			if(filler(buf, de->d_name, &st, 0))
				break;
		}
	}

	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
			struct fuse_file_info *fi) {

	char lokasi[1000];
	char fpath[1000];
	
	sprintf(lokasi, "%s", path);
	enkripsi(lokasi);
	
	if(strcmp(path,"/") == 0) {
		path = dirpath;
		sprintf(fpath,"%s",path);
	}
	else {
		sprintf(fpath, "%s%s",dirpath,path);
	}
	
	int res = 0;
	int fd = 0 ;
	
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

static struct fuse_operations xmp_oper = {
	.getattr = xmp_getattr,
	.readdir = xmp_readdir,
	.read = xmp_read,
};

int  main(int  argc, char *argv[]) {
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
