# LAPORAN PROYEK IoT MONITORING SUHU & KELEMBABAN

**NPM**: 5220411084  
**Nama**: Ahmas Sulaeman

---

## 📋 Overview Proyek

Sistem IoT real-time untuk memantau suhu & kelembaban menggunakan:

- **Sensor DHT22**
- **ESP32** (Modul WiFi)
- **Firebase Realtime Database**
- **Aplikasi Mobile Thunkable**

---

## 🎨 DESAIN UI

![Desain UI](https://i.imgur.com/VKwl66Y.png)

**Penjelasan**:
Berhubung pada thunkable ui nya terbatas sehingga saya menggunakan image agar tampilan lebih menarik. pada tampilan ini terdapat dua label yaitu Temperature dan Humidity yang berfungsi untuk menampilkan suhu dan kelembapan yang didapat dari sensor DHT22.

---

## 🛠 Sistem Design

![Diagram Rangkaian](https://i.imgur.com/2ZFpcKZ.png)
**Komponen**:

- ESP32 → Mikrokontroler utama
- DHT22 → Sensor suhu & kelembaban

**penjelasan**:

Saya membuat inisialisasi Cloud Variable dengan nama DHT22 karena data yang akan digunakan, seperti suhu dan kelembapan, akan diambil langsung dari cloud melalui variabel tersebut.

Selanjutnya, karena saya telah menyiapkan dua label yaitu Temperature dan Humidity, saya menambahkan blok "When Cloud Variable DHT22 changes" untuk mendeteksi perubahan data dari cloud. Ketika terdapat pembaruan pada variabel DHT22, maka label Temperature dan Humidity akan secara otomatis diperbarui. Nilai masing-masing label diatur menggunakan properti yang diambil dari objek cloud variable DHT22, yaitu get property "temperature" dan "humidity", sesuai dengan jenis data yang ditampilkan pada masing-masing label.

<!-- DATABASE REALTIME FIREBASE -->

### 🌐 DATABASE

<!-- IMAGE https://i.imgur.com/9L2Ph4k.png -->

![Database Realtime Firebase](https://i.imgur.com/9L2Ph4k.png)
**Penjelasan**:

- **Firebase**: Tempat penyimpanan data suhu & kelembaban
- **Realtime Database**: Memungkinkan pembaruan data secara langsung
- **Path**: `/DHT22/SUHU` dan `/DHT22/HUMIDITY`
- **Data Format**: JSON

Pada database firebase, saya mengunakan realtime agar data yang saya ambil dari sensor DHT22 dapat langsung diperbarui tanpa harus menunggu waktu tertentu. dengan database realtime, saya tidak perlu menggunakan websocket atau mqtt untuk mengupdate data, karena firebase sudah menyediakan fitur tersebut secara realtime.

**Format Data**: JSON

```json
{
  "DHT22": {
    "SUHU": 25,
    "HUMIDITY": 60
  }
}
```

## 📊 Hasil Pengujian

<!-- https://i.imgur.com/0GBm9lG.png foto perubahan temprator dan humidity pertama tempratur -5.9*C Humdity 32.5%
https://i.imgur.com/7OFS5SJ.png foto perubahan temprator dan humidity kedua tempratur -51.8*C Humdity 18.0% -->

![Hasil Pengujian Pertama](https://i.imgur.com/0GBm9lG.png)
**Penjelasan**:
Pada pengujian pertama, suhu yang ditampilkan adalah -5.9°C, dan kelembapan adalah 32.5%. Data ini diperoleh dari sensor DHT22 yang terhubung ke ESP32, kemudian dikirimkan ke Firebase Realtime Database. Aplikasi Thunkable mengambil data tersebut dan menampilkannya pada label Temperature dan Humidity.

![Hasil Pengujian Kedua](https://i.imgur.com/7OFS5SJ.png)
**Penjelasan**:
Pada pengujian kedua, suhu yang ditampilkan adalah -51.8°C, dan kelembapan adalah 18.0%. Proses pengambilan dan pengiriman data sama seperti pengujian pertama, yaitu melalui sensor DHT22, ESP32, Firebase Realtime Database, dan ditampilkan di aplikasi Thunkable.

## 📊 Analisis

- **Kelebihan**:

  - Data real-time
  - Mudah diakses melalui aplikasi mobile
  - Penggunaan Firebase memudahkan penyimpanan dan pengambilan data

- **Kekurangan**:
  - Ketergantungan pada koneksi internet
  - Sensor DHT22 memiliki batasan akurasi pada suhu ekstrem
  - Latensi dalam pembaruan data

## 📚 Penjelasan Perubahan Code

**Perubahan Library**

| Aspek                  | Kode Awal                             | Kode Akhir                                        |
| ---------------------- | ------------------------------------- | ------------------------------------------------- |
| Library yang digunakan | `DHT.h`                               | `DHTesp.h`                                        |
| Inisialisasi Sensor    | `DHT dht(DHTPIN, DHTTYPE);`           | `dht.setup(DHTPIN, DHTesp::DHT22);`               |
| Cara membaca data      | `readTemperature()`, `readHumidity()` | `getTempAndHumidity()`                            |
| Kelebihan              | Umum dan sederhana                    | Lebih stabil untuk ESP32 dan mendukung objek data |

**Perubahan Pengiriman Data ke Firebase**
| Aspek | Kode Awal | Kode Akhir |
| ----------------- | --------------------------------- | -------------------------------------------- |
| Metode kirim data | `Firebase.setFloat()` | `Firebase.setString()` |
| Format data | Angka (misal `25.6`) | String dengan satuan (misal `"25.6 *C"`) |
| Tujuan penggunaan | Mudah untuk perhitungan matematis | Lebih mudah ditampilkan langsung ke pengguna |
| Keunggulan | Ringan dan akurat | User-friendly dan informatif |

**Perubahan Konfigurasi Firebase**
| Aspek | Kode Awal | Kode Akhir |
| --------------------- | ---------------------------- | ----------------------------------------------- |
| Inisialisasi Firebase | `Firebase.begin(HOST, AUTH)` | Menggunakan `FirebaseConfig` dan `FirebaseAuth` |
| Format HOST | Tanpa `https://` | Dengan `https://` |
| Tipe token | Legacy token langsung | Token melalui objek konfigurasi |
| Kelebihan | Lebih cepat ditulis | Lebih fleksibel dan sesuai standar terbaru |

## 📜 Kesimpulan

Proyek **IoT Monitoring Suhu & Kelembaban** ini berhasil mengintegrasikan **sensor DHT22**, **mikrokontroler ESP32**, **Firebase Realtime Database**, dan **aplikasi mobile Thunkable** untuk menampilkan data suhu dan kelembapan secara real-time.

Dengan menggunakan Firebase sebagai backend, data dari sensor dapat dikirim dan ditampilkan secara langsung tanpa jeda yang signifikan. Aplikasi Thunkable mampu menampilkan informasi tersebut dengan antarmuka sederhana namun cukup informatif.

Beberapa poin penting dari proyek ini:

- Sistem bekerja **real-time** dan **otomatis**, mempermudah pemantauan dari jarak jauh.
- **Firebase Realtime Database** memberikan kemudahan dalam integrasi cloud tanpa perlu server tambahan.
- Perubahan kode yang dilakukan menjadikan sistem lebih stabil dan kompatibel untuk perangkat **ESP32**.
