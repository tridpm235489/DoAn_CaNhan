# 🗑️ Thùng Rác Thông Minh - ESP32

**Đồ án cá nhân**  
**Sinh viên:** Phan Minh Trí - DPM235489

---

## 📌 Giới thiệu

Dự án **Thùng Rác Thông Minh** sử dụng vi điều khiển **ESP32** kết hợp cảm biến siêu âm và động cơ servo để tự động mở/đóng nắp thùng khi phát hiện người lại gần, đồng thời cảnh báo khi thùng đã đầy.

---

## ✨ Tính năng chính

- 🖐️ **Tự động mở nắp** khi phát hiện vật thể trong khoảng cách < 20cm
- ⏱️ **Tự động đóng nắp** sau 3 giây
- 🔴 **Cảnh báo thùng đầy** bằng đèn LED đỏ + còi buzzer khi khoảng cách < 10cm
- 🟢 **Đèn LED xanh** báo hiệu đang mở nắp
- 📊 Hiển thị khoảng cách real-time trên Serial Monitor

---

## 🛠️ Phần cứng sử dụng

| Linh kiện              | Số lượng | Chân ESP32 |
|------------------------|----------|------------|
| ESP32 DevKit C V4      | 1        | -          |
| Cảm biến HC-SR04 (mở nắp) | 1     | Trig: 5, Echo: 18 |
| Cảm biến HC-SR04 (thùng đầy) | 1  | Trig: 23, Echo: 22 |
| Servo Motor            | 1        | 19         |
| LED xanh               | 1        | 2          |
| LED đỏ                 | 1        | 4          |
| Buzzer                 | 1        | 21         |

---

## 📁 Cấu trúc thư mục

---

## 🚀 Cách chạy dự án

### 1. Mô phỏng trên Wokwi (khuyến nghị)

1. Truy cập [Wokwi.com]([https://wokwi.com](https://wokwi.com/projects/478383958858055681))

https://wokwi.com/projects/478383958858055681

2. Tạo project mới → chọn **ESP32**
3. Copy nội dung file `diagram.json` và `sketch.ino` vào
4. Thêm thư viện **ESP32Servo**
5. Nhấn **Start Simulation**

### 2. Chạy trên phần cứng thật

1. Cài đặt **Arduino IDE** + board ESP32
2. Cài thư viện `ESP32Servo`
3. Mở file `sketch.ino` → chọn đúng board và cổng COM
4. Upload code lên ESP32
5. Mở **Serial Monitor** (baudrate 115200) để theo dõi

---

## ⚙️ Thông số cấu hình

```cpp
const int KHOANG_MO = 20;          // cm - khoảng cách mở nắp
const int KHOANG_DAY = 10;         // cm - khoảng cách coi là đầy
const int THOI_GIAN_GIU_MO = 3000; // ms - thời gian giữ nắp mở
