# soal-shift-sisop-modul-4-IT07-2021

Anggota Kelompok IT07:
  Kevin Nathaniel (05311940000032)
  Shafira Firdausi (05311940000040)
  Prananda Nur Widiastara (05311940000048)
  

# Soal SinSei <a name="Soal_SinSei"></a>

Soal SinSei modul 4 ini terbagi menjadi beberapa bagian soal:

### 1. Enkripsi direktori berawalan Atoz_
  #### a. Jika direktori dibuat, direktori tsb menjadi direktori ter-encode (atbash)
  #### b. Jika direktori direname, direktori tsb menjadi direktori ter-encode (atbash)
  #### c. Jika direktori yang terenkripsi direname jadi tidak terencode, maka isinya menjadi terdecode
  #### d. Setiap pembuatan direktori diatas tadi akan tercatat dalam sebuah log (beserta method)
  #### e. Metode encode berlaku rekursif terhadap direktori yang ada di dalamnya
  
### 2. Enkripsi direktori berawalan RX_
  #### a. Jika direktori dibuat, direktori tsb menjadi direktori terencode (atbash+ROT13)
  #### b. Jika direktori direname, direktori tsb menjadi direktori terencode (Case-sensitive, atbash+vigenere{key:SISOP})
  #### c. Jika direktori yang terencode dihilangkan “RX_”nya, maka direktori tsb akan terdecode berdasarkan nama aslinya
  #### d. Setiap pembuatan direktori diatas tadi akan tercatat dalam sebuah log (beserta method)
  #### e. File-file yang ada di direktori asli akan menjadi terpecah menjadi masing-masing 1024 bytes per filenya. Namun, jika diakses melalui filesystem nanti akan menjadi normal kembali.

### 3. Enkripsi direktori berawalan A_is_a_
  #### a. Jika direktori dibuat, direktori tsb menjadi direktori spesial
  #### b. Jika direktori direname, direktori tsb menjadi direktori spesial
  #### c. Jika direktori yang terencode dihilangkan "A_is_a_”nya, maka direktori tsb akan menjadi direktori normal
  #### d. Direktori spesial ini akan mengembalikan enkripsi pada direktori “AtoZ_” maupun “RX_” namun sifat rekursif kedua direktori tetap berjalan pada subdirektori
  #### e.Semua nama file pada fuse akan berubah menjadi lowercase pada direktori spedial, dengan tambahan ekstensi nilai desimal dari biner perbedaan nama.

### 4. Log system
  #### a. Nama file log berupa “SinSeiFS.log” pada direktori home user.
  #### b. Terbagi menjadi 2 level: `INFO` & `WARNING`
  #### c. Level `WARNING` digunakan untuk log syscall, rmdir, dan unlink.
  #### d. Selain 3 log diatas, log akan tercatat pada level `INFO`
  #### e. Format log:
    '[Level]::[dd][mm][yyyy]-[HH]:[MM]:[SS]:[CMD]::[DESC :: DESC]`

## Source Code <a name="Source_Code"></a>

## Dokumentasi <a name="Dokumentasi"></a>


