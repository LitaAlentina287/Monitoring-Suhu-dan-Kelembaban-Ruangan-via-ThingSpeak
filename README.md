# Monitoring Suhu dan Kelembaban Ruangan via ThingSpeak

## Proyek Akhir Sistem Mikrokontroler

### Deskripsi
Proyek ini merupakan sistem monitoring suhu dan kelembaban ruangan berbasis Internet of Things (IoT) yang menggunakan sensor DHT22 sebagai perangkat sensor (input), mikrokontroler ESP32 sebagai pengendali utama, serta LCD 16×2 dan aktuator berupa LED dan buzzer sebagai perangkat keluaran (output). Sensor DHT22 membaca nilai suhu dan kelembaban secara real-time, kemudian data diproses oleh ESP32 untuk ditampilkan pada LCD. Berdasarkan nilai suhu yang terdeteksi, ESP32 mengendalikan aktuator berupa LED dan buzzer sebagai indikator kondisi ruangan. Selanjutnya, data suhu, kelembaban, dan status ruangan dikirim ke platform ThingSpeak menggunakan protokol HTTP melalui koneksi WiFi sehingga dapat dipantau secara online dan real-time.

---

## Latar Belakang

Suhu dan kelembaban ruangan merupakan faktor yang memengaruhi kenyamanan manusia serta kondisi peralatan elektronik di dalam ruangan. Monitoring secara manual kurang efisien karena harus dilakukan secara langsung dan berkala.

Dengan memanfaatkan teknologi Internet of Things (IoT), proses monitoring suhu dan kelembaban dapat dilakukan secara real-time melalui internet sehingga kondisi ruangan dapat dipantau dengan lebih mudah. Selain menampilkan data monitoring, sistem juga mengendalikan aktuator berupa LED dan buzzer sebagai indikator kondisi ruangan, sehingga pengguna dapat mengetahui kondisi ruangan baik secara lokal melalui perangkat maupun secara online melalui platform ThingSpeak.

---

## Tujuan

- Merancang sistem monitoring suhu dan kelembaban menggunakan sensor DHT22 dan ESP32.
- Menampilkan data sensor pada LCD secara real-time.
- Mengirim data ke ThingSpeak menggunakan protokol HTTP.
- Mengendalikan LED dan buzzer sebagai indikator kondisi ruangan.

---

## Hardware

- ESP32
- Sensor DHT22
- LCD I2C 16x2
- LED Hijau
- LED Kuning
- LED Merah
- Buzzer
- Resistor

---

## Software

- Wokwi Simulator
- ThingSpeak

---

## Protokol Komunikasi

HTTP (Hypertext Transfer Protocol)

HTTP digunakan untuk mengirimkan data suhu, kelembaban, dan status ruangan dari ESP32 menuju platform ThingSpeak melalui jaringan internet.

---

## Diagram Sistem

![Diagram Sistem](images/rangkaian.png)

---

## Flowchart Sistem

![Flowchart](images/flowchart.png)

---

## Hasil Simulasi

![Simulasi](images/hasil-simulasi.png)

---

## Hasil Monitoring Thingspeak

![ThingSpeak](images/thingspeak.png)

---


## Logika Program

| Suhu | Status |
|------|--------|
| < 25°C | Dingin |
| 25°C – 30°C | Normal |
| > 30°C | Panas |

### Indikator

| Status | LED | Buzzer |
|---------|-----|---------|
| Dingin | Hijau | Mati |
| Normal | Kuning | Mati |
| Panas | Merah | Aktif |

---

## Cara Kerja Sistem

1. ESP32 melakukan inisialisasi seluruh komponen.
2. ESP32 menghubungkan perangkat ke jaringan WiFi.
3. Sensor DHT22 membaca suhu dan kelembaban.
4. Data ditampilkan pada LCD.
5. ESP32 menentukan status ruangan.
6. LED dan buzzer bekerja sesuai kondisi suhu.
7. Data dikirim ke ThingSpeak menggunakan HTTP setiap 20 detik.
8. ThingSpeak menampilkan data dalam bentuk grafik secara real-time.

---

## Hasil Implementasi

Berdasarkan hasil pengujian:

- Sensor DHT22 berhasil membaca suhu dan kelembaban.
- LCD berhasil menampilkan data secara real-time.
- LED dan buzzer bekerja sesuai logika program.
- ESP32 berhasil mengirim data ke ThingSpeak menggunakan HTTP.
- Grafik monitoring berhasil ditampilkan pada ThingSpeak.

---

## Kesimpulan

- Sistem monitoring suhu dan kelembaban berhasil dibuat menggunakan ESP32 dan DHT22.
- Data dapat ditampilkan secara real-time pada LCD.
- Data berhasil dikirim ke ThingSpeak menggunakan protokol HTTP.
- LED dan buzzer berfungsi sebagai indikator kondisi ruangan.
- Sistem berjalan dengan baik pada simulator Wokwi.

---

## Author

Lita Alentina
23552011097
TIF K 23B
