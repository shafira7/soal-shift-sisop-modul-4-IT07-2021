# soal-shift-sisop-modul-4-IT07-2021

Anggota Kelompok IT07:<br>
  Kevin Nathaniel (05311940000032)<br>
  Shafira Firdausi (05311940000040)<br>
  Prananda Nur Widiastara (05311940000048)<br>
  

# Soal SinSei <a name="Soal_SinSei"></a>

Soal SinSei modul 4 ini terbagi menjadi beberapa bagian soal:

### 1. Enkripsi direktori berawalan Atoz_
  a. Jika direktori dibuat, direktori tsb menjadi direktori ter-encode (atbash) <br>
  b. Jika direktori direname, direktori tsb menjadi direktori ter-encode (atbash) <br>
  c. Jika direktori yang terenkripsi direname jadi tidak terencode, maka isinya menjadi terdecode <br>
  d. Setiap pembuatan direktori diatas tadi akan tercatat dalam sebuah log (beserta method) <br>
  e. Metode encode berlaku rekursif terhadap direktori yang ada di dalamnya <br>
  
### 2. Enkripsi direktori berawalan RX_
  a. Jika direktori dibuat, direktori tsb menjadi direktori terencode (atbash+ROT13) <br>
  b. Jika direktori direname, direktori tsb menjadi direktori terencode (Case-sensitive, atbash+vigenere{key:SISOP}) <br>
  c. Jika direktori yang terencode dihilangkan “RX_”nya, maka direktori tsb akan terdecode berdasarkan nama aslinya <br>
  d. Setiap pembuatan direktori diatas tadi akan tercatat dalam sebuah log (beserta method)<br>
  e. File-file yang ada di direktori asli akan menjadi terpecah menjadi masing-masing 1024 bytes per filenya. Namun, jika diakses melalui filesystem nanti akan menjadi normal kembali.<br>

### 3. Enkripsi direktori berawalan A_is_a_
  a. Jika direktori dibuat, direktori tsb menjadi direktori spesial<br>
  b. Jika direktori direname, direktori tsb menjadi direktori spesial<br>
  c. Jika direktori yang terencode dihilangkan "A_is_a_”nya, maka direktori tsb akan menjadi direktori normal<br>
  d. Direktori spesial ini akan mengembalikan enkripsi pada direktori “AtoZ_” maupun “RX_” namun sifat rekursif kedua direktori tetap berjalan pada subdirektori<br>
  e. Semua nama file pada fuse akan berubah menjadi lowercase pada direktori spedial, dengan tambahan ekstensi nilai desimal dari biner perbedaan nama.<br>

### 4. Log system
  a. Nama file log berupa “SinSeiFS.log” pada direktori home user<br>
  b. Terbagi menjadi 2 level: `INFO` & `WARNING`<br>
  c. Level `WARNING` digunakan untuk log syscall, rmdir, dan unlink<br>
  d. Selain 3 log diatas, log akan tercatat pada level `INFO`<br>
  e. Format log:
    `[Level]::[dd][mm][yyyy]-[HH]:[MM]:[SS]:[CMD]::[DESC :: DESC]`

## Source Code <a name="Source_Code"></a>

### Soal 1 <a name="Soal1"></a>
Secara singkat Atbash Cipher adalahcipher substitusi  sederhana  dengan  cara  membalikkan  alfabet sehingga setiap huruf dipetakan ke huruf di posisi yang sama kebalikan dari abjad. 

#### Enkripsi Atbash Cipher <a name="Atbash"></a>
```c
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
```
Enkripsi Atbash ini digunakan jika kita menjalankan command ```mkdir``` dan ```rename``` dimana fungsi ini akan menerima nama direktorinya dan mengecek apakah dalam membuat direkrtori dengan command ```mkdir``` terdapat ```AtoZ_```, apabila ada maka pada saat membuat file didalam direktori itu , nama file tersebut kan terencode dengan atbash cipher. Begitu pula saat melakukan rename folder dengan nama ```AtoZ_```, nama file didalam folder tersebut akan terencode dengan Atbash Cipher ini. Algoritma ini menerima inputan data berupa filepath.

#### Enkripsi Atbash Cipher <a name="Atbash"></a>
```c
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
```
Algoritma ini berfungsi untuk melakukan rekursif enkripsi atbash kedalam file yang namanya sudah memiliki awalan ```AtoZ_``` dan ketika file sudah tidak memiliki nama ```AtoZ_``` maka isi dari file tersebut juga akan kembali seperti semula 

### Soal 4 <a name="Soal_4"></a>
  #### 4.1 CreateLog
  Pertama akan dibuka direktori untuk menyimpan file log nantinya. lalu dideklarasikan semua format tanggal bulan tahun dan waktu. Lalu dibuat if else untuk pembagian 2 level (WARNING & INFO)<br>
  ```c
  void creteLog(int level,char *call,const char *info){
	FILE *log = fopen("/home/nanda/SinSeiFS.log" , "a");
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
```

## Kendala <a name="Kendala"></a>
  Untuk saat ini kami masih belum bisa menyelesaikan bagian:
  ### 1. Soal 2<br>
  Kami sudah menyelesaikan enkripsi kombinasi untuk bagian soal no 2, namun saat dijalankan antara mkdir dan rename, enkripsi mereka saling menimpa satu sama lain. <br>
  Kami juga mengalami kendala untuk bagian soal no 2.e. Pembagian file berhasil dilakukan, namun saat kami mengakses melalui filesystem, file belum bisa menjadi normal kembali.<br>
  ### 2. Soal 3<br>
  Kami belum dapat menyelesaikan bagian soal ini.<br>
  ![image](https://user-images.githubusercontent.com/60997606/120894980-31792c80-c645-11eb-8ab5-314fdab179cb.png)

<br>
  

## Terima Kasih

