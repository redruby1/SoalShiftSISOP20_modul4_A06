# SoalShiftSISOP20_modul4_A06

## Soal 1
*Enkripsi versi 1 :*

Menggunakan caesar chiper dengan key 10

String : ``` 9(ku@AW1[Lmvgax6q`5Y2Ry?+sF!^HKQiBXCUSe&0M.b%rI'7d)o4~VfZ*{#:}ETt$3J-zpc]lnh8,GwP_ND|jO ```

**Jawab :**

Mount source (root) filesystem
```
static  const  char *dirpath = "/Users/Anisa Aurafitri/Documents";
```

Fungsi *enkripsi*
```
char *enkripsi(char code[100]) {
	
	for(i = 0; (i < strlen(code) && code[i] != '\0'); i++) {
		if(code[i] != '/') {
		      	titik = strchr(message, code[i]) - message;
		        code[i] = message[(titik + key) % strlen(message)];
	    	}
	}
	
	return code;
}
```

Fungsi *dekripsi*
```
char *dekripsi(char code[100]) {
	
	for(i = 0; (i < strlen(code) && code[i] != '\0'); i++) {
		if(code[i] != '/') {
			titik = strchr(message, code[i]) - message;
	        	code[i] = message[(titik + (strlen(message)-key)) % strlen(message)];
		}
	}
	
	return code;
}
```

Fungsi *get ekstensi*
```
char *get_eks(char code[100]) {
	const char *dot = strrchr(code, '.');
	if(!dot || dot == code) return "";
	return dot;
}
```
Ketentuan *caesar chiper*
```
char message[1000] = "9(ku@AW1[Lmvgax6q`5Y2Ry?+sF!^HKQiBXCUSe&0M.b%rI'7d)o4~VfZ*{#:}ETt$3J-zpc]lnh8,GwP_ND|jO";
int key = 10;
```
Memisahkan *encv1_* dan *encv2_*
```
if((de = readdir(dp)) != NULL && strstr(lokasi, "encv1_") != 0) {
	...
	...
}
```
Struct dari fuse 
```
static struct fuse_operations xmp_oper = {
	.getattr = xmp_getattr,
	.readdir = xmp_readdir,
	.read = xmp_read,
};
```
## Soal 2
*Enkripsi versi 2 :*

## Soal 3
*Sinkronisasi direktori otomatis*

## Soal 4
*Log system*
