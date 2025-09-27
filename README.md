# BÀI TẬP 1:
# TÌM HIỂU CÁC PHƯƠNG PHÁP MÃ HOÁ CỔ ĐIỂN
Caesar
Affine
Hoán vị
Vigenère
Playfair

# Với mỗi phương pháp, hãy tìm hiểu:
Tên gọi
Thuật toán mã hoá, thuật toán giải mã
Không gian khóa
Cách phá mã (mà không cần khoá)
Cài đặt thuật toán mã hoá và giải mã bằng code C++ và bằng html+css+javascript

============================

# Tên : Mật mã Caesar
Thuật toán (mã / giải):
* Với chữ cái 
𝑥(0..25), khoá 𝑘∈{0..25}

* Mã hoá: 
𝐸(𝑥)=(𝑥+𝑘)mod26

* Giải mã: 
𝐷(𝑦)=(𝑦−𝑘) mod 26
Không gian khoá: 26 (k = 0..25)

* Phá mã (không cần khoá):
Brute-force thử 26 khoá; chọn kết quả có nghĩa/ngôn ngữ hợp lý.
Phân tích tần suất: so sánh tần suất ký tự với phân bố tiếng Anh.

# Ảnh minh họa :
* Mã hóa (Encrypt):
<img width="1221" height="857" alt="image" src="https://github.com/user-attachments/assets/9414849f-8441-441f-b113-252857c5ffff" />

* Giải mã (Decrypt):
<img width="1195" height="848" alt="image" src="https://github.com/user-attachments/assets/53aa7354-fdff-45c1-abff-66b12b957e7f" />

# Tên: Affine cipher

* Thuật toán:
Khoá là cặp (a,b) với a và 26 nguyên tố cùng nhau (gcd(a,26)=1), b∈{0..25}
Mã hoá: E(x)=(ax+b)mod26
Giải mã: cần a^−1 (mod 26) — nghịch đảo modulo: D(y)=a^−1(y−b)mod26

* Không gian khoá:
Có 12 giá trị khả dĩ cho a (số nguyên dương <26 và coprime với 26): 1,3,5,7,9,11,15,17,19,21,23,25
b có 26 giá trị → tổng 12∗26=312 khoá.

* Phá mã (không cần khoá):
Brute force 312 khả năng.
Nếu có plaintext-ngữ nghĩa, hoặc tần suất: chỉ cần xác định 2 cặp plaintext-ciphertext (two-letter frequency) để giải cho a,b.
Khi dùng cho chữ đơn (monoalphabetic), phân tích tần suất hữu dụng.


# Tên: Hoán vị / Columnar Transposition

* Thuật toán (mã hoá):
Khoá: một từ/chuỗi ký tự (ví dụ "ZEBRA") — suy ra thứ tự cột bằng cách sắp chữ cái theo bảng chữ cái.
Viết plaintext theo hàng, số cột = độ dài khoá (k). Bổ sung ký tự filler (ví dụ 'X') nếu cần.
Đọc ciphertext theo cột theo thứ tự cột đã sắp (từ nhỏ đến lớn theo chữ cái khoá).

* Giải mã:
Biết chiều dài khoá k → tính số hàng r = ceil(len/k)
Xác định số cột có 1 ô thiếu nếu plaintext không kín; chia ciphertext thành các cột theo thứ tự; sau đó tái điền bảng và đọc theo hàng.

* Không gian khoá:
Nếu dùng permutation dài n thì không gian khoá = n! (rất lớn). Với khoá là một từ có độ dài k: có nhiều hoán vị khác nhau (<=26^k nếu là chữ cái) nhưng thực tế là k! hoán vị vị trí.

* Phá mã (không cần khoá):
Thử tất cả các hoán vị của một độ dài k nhỏ (brute-force) hoặc dùng phân tích mẫu (ngắt thành từ) để xác định kích thước cột hợp lý.
Tấn công bằng phương pháp đo lường ngữ nghĩa: chọn hoán vị khiến kết quả có từ hợp lý.
