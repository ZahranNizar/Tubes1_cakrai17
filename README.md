# Tubes1_cakrai17
Repository ini dibuat untuk memenuhi tugas besar 1 ca-KRAI 17 Divisi Kontrol

# Penjelasan Umum Kode
FSM.cpp dikoding sedemikian rupa sehingga ketika main.cpp dilaksanakan, user dapat memberikan
perintah kepada robot dengan list command berikut :
1. IDLE
2. MOVEMENT
3. SHOOTING
4. CALCULATION
5. STOPPED
Note : Input user tidak dipengaruhi oleh huruf kapital

# Keteragan Tentang Kode
1. Robot akan berada dalam State : IDLE untuk menerima command dari user
2. Robot akan merekam semua perintah yang diberikan beserta waktu sejak inisialisasi robot
3. TIDAK ADA loop yang akan mengecek status robot setiap 1000 detik, karena kode std::cin akan menghentikan
program sampai user memberikan input. Penggunaan multi-threading pada FSM adalah salah satu solusi hal di atas, akan
tetapi saya masih noob (dalam programming) untuk mengerti cara kerjanya
4. Terdapat delay 2 detik (input oleh main.cpp) antar setiap pergantian state. Sehingga delay eksekusi kode kemungkinan besar
diakibatkan oleh fungsi delay daripada kesibukan program
5. Fungsi delay yang digunakan adalah sebuah loop dengan library <chrono>. Secara default fungsi yang digunakan untuk delay adalah
std::this_thread::sleep_for(waktu delay), akan tetapi karena laptop saya (windows) membenci saya, saya harus menggunakan loop <chrono>
(Kegagalan dalam compilasi)
6. Code dibuat di Visual Studio Code dengan bantuan AI Gemini

# Detail Kode
- FSM::FSM dan FSM::~FSM adalah konstruktor dan destruktor pada program ini.
- string StatusProgram(SystemState state) : Digunakan untuk mengubah tipe enum SystemState menjadi string
- void FSM::transitionToState(SystemState newState) : Terdapat update time dimana sistem mengalami perubahan state
- void FSM::setDelay(uint32_t delay) : Awalnya hanyalah fungsi untuk mengubah parameter delay FSM menjadi uint32_t delay, tetapi karena
fungsi ini tidak terpakai bagi saya, saya memodifikasi fungsi ini sehingga memberikan efek yang sama dengan perintah delay()
- void FSM::setLastHeartbeat(uint32_t heartbeat) : Waktu LastHeartbeat dihitung mulai sejak sistem inisialisasi. Sehingga saat sistem
inisialisasi, LastHeartbeat dari state ini adalah 0 ms.
- void FSM::start() : Program akan melakukan update pertama yaitu eksekusi prosedur inisialisasi. Setelah eksekusi prosedur inisialisasi atau
update pertama selesai, program akan memasuki loop dan melaksanakan semua perintah di loop tersebut secara berulang. Jika user memberikan command
STOPPED, loop akan berakhir dan sistem telah selesai bekerja. Konstruktor FSM juga akan dieksekusi pada prosedur ini
- void FSM::update() : Update Current State & LastHeartbeat serta merekam ke vektor StateHistory. Prosedur ini juga akan mengeksekusi command aksi
sesuai dengan state dari program ini berjalan
- void FSM::printStateHistory() : Modifikasi data pertama dan terakhir untuk menyesuaikan kondisi sistem
- void FSM::performProcess() : Sistem akan menunggu input user pada state IDLE. Input yang diberikan akan meng-update state dari sistem sehingga
memunculkan aksi command sesuai dengan command dari user
