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

## Dokumentasi <a name="Dokumentasi"></a>

## Kendala <a name="Kendala"></a>

