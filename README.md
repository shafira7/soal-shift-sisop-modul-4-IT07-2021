# soal-shift-sisop-modul-4-IT07-2021

Anggota Kelompok IT07:
  Kevin Nathaniel (05311940000032)
  Shafira Firdausi (05311940000040)
  Prananda Nur Widiastara (05311940000048)
  

# Soal SinSei <a name="Soal_SinSei"></a>

Soal SinSei modul 4 ini terbagi menjadi beberapa bagian soal:

1. Enkripsi direktori berawalan Atoz_
  a. Jika direktori dibuat dan direname, direktori tsb menjadi direktori ter-encode (atbash)
  b. Jika direktori yang terenkripsi direname jadi tidak terencode, maka isinya menjadi terdecode, 
  c. Setiap pembuatan direktori diatas tadi akan tercatat dalam sebuah log (beserta method)
  d. Metode encode berlaku rekursif terhadap direktori yang ada di dalamnya
2. Enkripsi direktori berawalan RX_    
  a. Jika direktori dibuat, direktori tsb menjadi direktori terencode (atbash+ROT13)
  b. Jika direktori direname, direktori tsb menjadi direktori terencode (Case-sensitive, atbash+vigenere{key:SISOP})
  c. Jika direktori yang terencode dihilangkan “RX_”nya, maka direktori tsb akan terdecode berdasarkan nama aslinya.
  d. Setiap pembuatan direktori diatas tadi akan tercatat dalam sebuah log (beserta method)
  e. File-file yang ada di direktori asli akan menjadi terpecah menjadi masing-masing 1024 bytes per filenya. Namun, jika diakses melalui filesystem nanti akan menjadi normal kembali.
    

