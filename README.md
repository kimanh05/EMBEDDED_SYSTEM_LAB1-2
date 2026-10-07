# Embedded Systems - Lab 1 & Lab 2

Repository lưu trữ mã nguồn và báo cáo **Lab 1 và Lab 2** của môn **Hệ thống Nhúng**.

## Thông tin

- Trường: Đại học Bách khoa - ĐHQG TP.HCM
- Khoa: Khoa học và Kỹ thuật Máy tính
- Môn học: Hệ thống Nhúng
- Lớp: TN01
- Học kỳ: 261
- GVHD: Trần Nguyễn Minh Duy
- Nhóm: 08

### Thành viên

| MSSV | Họ và tên |
|------|-----------|
| 2310123 | Nguyễn Thị Kim Anh |
| 2312318 | Phạm Thảo Ngọc |

## Phần cứng và công cụ

- Kit: BKIT ARM4
- Vi điều khiển: STM32F407ZGT6
- IDE: STM32CubeIDE
- Thư viện: STM32 HAL

---

# Lab 1 - General Purpose Input Output

Lab 1 tập trung vào cấu hình và điều khiển các chân GPIO Output trên kit BKIT ARM4.

### Bài tập 1 - Điều khiển LED3

Điều khiển LED3 theo chu kỳ:

- Sáng trong 2 giây
- Tắt trong 4 giây
- Lặp lại liên tục

### Bài tập 2 - Điều khiển LED với một lệnh delay

Thực hiện lại yêu cầu của Bài tập 1 nhưng chỉ sử dụng một lệnh `HAL_Delay()`.

Biến đếm được sử dụng để xác định trạng thái LED theo từng giây.

### Bài tập 3 - Mô phỏng đèn giao thông

Sử dụng ba LED để mô phỏng đèn giao thông:

| LED | Chức năng | Thời gian |
|-----|-----------|-----------|
| DEBUG_LED | Đèn đỏ | 5 giây |
| OUTPUT_Y0 | Đèn xanh | 3 giây |
| OUTPUT_Y1 | Đèn vàng | 1 giây |

Chu kỳ được lặp lại liên tục.

---

# Lab 2 - Timer Interrupt and LED Scanning

Lab 2 tập trung vào **Timer Interrupt**, **software timer** và kỹ thuật **quét LED 7 đoạn**.

TIM2 được cấu hình để tạo ngắt định kỳ **1 ms**, làm cơ sở cho các chức năng định thời.

### Bài tập 1 - Software Timer

Điều khiển đồng thời ba LED:

- `DEBUG_LED`: đảo trạng thái mỗi 2 giây
- `OUTPUT_Y0`: sáng 2 giây, tắt 4 giây
- `OUTPUT_Y1`: sáng 5 giây, tắt 1 giây

### Bài tập 2 - Đèn giao thông sử dụng Timer

Hiện thực lại mô hình đèn giao thông của Lab 1 bằng Timer thay cho `HAL_Delay()`.

Trình tự hoạt động:

`Đỏ (5s) -> Xanh (3s) -> Vàng (1s) -> Đỏ`

### Bài tập 3 - Thay đổi tần số quét LED 7 đoạn

Khảo sát hoạt động của LED 7 đoạn với các tần số quét:

- 1 Hz
- 25 Hz
- 100 Hz

### Bài tập 4 - Đồng hồ kỹ thuật số

Sử dụng bốn LED 7 đoạn để mô phỏng đồng hồ dạng:

`HH:MM`

Trong đó:

- Hai chữ số đầu hiển thị giờ
- Hai chữ số sau hiển thị phút
- Dấu `:` chớp tắt với tần số 2 Hz
- Thời gian được cập nhật bằng Timer

### Bài tập 5 - Hiệu ứng dịch số

Hiển thị bốn chữ số khác nhau trên LED 7 đoạn và dịch sang phải sau mỗi 1 giây.

Ví dụ:

`1234 -> 4123 -> 3412 -> 2341 -> 1234`

---

## Kiến thức đạt được

Sau Lab 1 và Lab 2, nhóm thực hành các nội dung:

- Cấu hình và điều khiển GPIO
- Sử dụng STM32 HAL
- Điều khiển LED bằng `HAL_GPIO_WritePin()`
- Sử dụng Timer Interrupt
- Xây dựng software timer
- Lập trình theo cơ chế non-blocking
- Giao tiếp SPI
- Quét LED 7 đoạn
- Xây dựng các ứng dụng định thời trên STM32
