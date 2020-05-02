#define FUSE_USE_VERSION 28

#include <fuse.h>

#include <stdio.h>

#include <string.h>

#include <unistd.h>

#include <fcntl.h>

#include <dirent.h>

#include <errno.h>

#include <sys/time.h>

char str[100];
int i, x;

char message[100] = "9(ku@AW1[Lmvgax6q`5Y2Ry?+sF!^HKQiBXCUSe&0M.b%rI'7d)o4~VfZ*{#:}ETt$3J-zpc]lnh8,GwP_ND|jO";
int key = 10, titik;

char *enkripsi(char code[100]) {
	
	for(i = 0; (i < strlen(code) && code[i] != '\0'); i++) {
		if(code[i] != '/') {
	      	titik = strchr(message, code[i]) - message;
	        code[i] = message[(titik + key) % strlen(message)];
    	}
	}
	
	return code;
}

char *dekripsi(char code[100]) {
	
	for(i = 0; (i < strlen(code) && code[i] != '\0'); i++) {
		if(code[i] != '/') {
			titik = strchr(message, code[i]) - message;
        	code[i] = message[(titik + (strlen(message)-key)) % strlen(message)];
		}
	}
	
	return code;
}

char *get_eks(char code[100]) {
	const char *dot = strrchr(code, '.');
    if(!dot || dot == code) return "";
    return dot;
}

static int xmp_mkdir(const char *path, mode_t x)
{
    int res;
    
    res = mkdir(path, x);
    if(res == -1)
    {
      return -errno;
    }
    
    return 0;
}

static int xmp_rename(const char *awal, const char *akhir)
{
     int res;
     
     res = rename(awal, akhir);
     if(res == -1)
     {
      return -errno;
     }
     
     return 0;
}

static  int  xmp_getattr(const char *path, struct stat *stbuf)

{

int res;

res = lstat(path, stbuf);

if (res == -1)

return -errno;

  

return 0;

}

  

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,

off_t offset, struct fuse_file_info *fi)

{

DIR *dp;

struct dirent *de;

  

(void) offset;

(void) fi;

  

dp = opendir(path);

if (dp == NULL)

return -errno;

  

while ((de = readdir(dp)) != NULL) {

struct stat st;

memset(&st, 0, sizeof(st));

st.st_ino = de->d_ino;

st.st_mode = de->d_type << 12;

if (filler(buf, de->d_name, &st, 0))

break;

}

  

closedir(dp);

return 0;

}

  

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,

struct fuse_file_info *fi)

{

int fd;

int res;

  

(void) fi;

fd = open(path, O_RDONLY);

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

.mkdir = xmp_mkdir,

.rename = xmp_rename

};

  

int  main(int  argc, char *argv[])

{

umask(0);

return fuse_main(argc, argv, &xmp_oper, NULL);

}
