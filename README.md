## BÀI TẬP 1:  
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

# Ảnh minh họa :  
* Mã hóa (Encrypt):
  <img width="1198" height="841" alt="image" src="https://github.com/user-attachments/assets/74039ae2-1e3c-4f51-b4cc-eb2fd455f8db" />  

* Giải mã (Decrypt):
  <img width="1202" height="833" alt="image" src="https://github.com/user-attachments/assets/2f0e72dc-0b68-4438-bdb8-079dfcc6cf24" />  

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

# Ảnh minh họa
* Mã hóa (Encrypt):  
  <img width="1186" height="836" alt="image" src="https://github.com/user-attachments/assets/475874bc-2a37-471f-bc00-732192a40373" />

* Giải mã (Decrypt):
  <img width="1187" height="829" alt="image" src="https://github.com/user-attachments/assets/66183511-4fcd-4e76-8748-b158e335169b" />

# Tên: Vigenère

* Thuật toán:  
Khoá: một chuỗi ký tự (khóa) dài m.
  
Mã hoá: dùng phép cộng theo từng ký tự: Với chữ cái pi và kj​ (chỉ số 0..25), ci	​= (pi + kimodm​)mod26

Giải mã:  
𝑝𝑖=(𝑐𝑖−𝑘𝑖 mod 𝑚+26) mod 26  

Không gian khoá:  
Nếu khóa dài m và mỗi ký tự 26 khả năng → 26^m. Thực tế khoá ngắn (m nhỏ) nên dễ tấn công.  

Phá mã (không cần khoá):  
Kasiski test: tìm khoảng cách giữa các cụm lặp → ước lượng độ dài khoá m.  
Index of Coincidence (IC): ước lượng m bằng cách phân chia và tính IC.  
Khi biết m, mỗi cột là Caesar cipher → dùng phân tích tần suất.  

# Ảnh minh họa :  
* Mã hóa (Encrypt):
  <img width="1192" height="843" alt="image" src="https://github.com/user-attachments/assets/bb264ad1-7d7c-4c32-af38-9d5faac45618" />

* Giải mã (Decrypt):
  <img width="1182" height="823" alt="image" src="https://github.com/user-attachments/assets/b312f073-9abb-4923-a0b6-abb03bbf270c" />

# Tên: Playfair cipher (mã cặp đôi, 5×5)

* Ý tưởng / Thuật toán:  
Tạo ma trận 5×5 từ khoá: ghi các chữ cái trong khoá (không trùng), tiếp theo các chữ còn lại (gộp J vào I).  

* Tiền xử lý plaintext:  
Loại bỏ ký tự không phải chữ, chuyển thành chữ hoa, thay J → I.  
Tách thành digraphs (cặp 2 chữ). Nếu hai chữ trong cặp giống nhau, chèn 'X' giữa.  
Nếu cuối cùng thiếu 1 chữ, thêm 'X'.  

* Mã hoá cho mỗi digraph (A,B):  
Nếu A và B cùng hàng → thay bằng chữ bên phải (wrap).  
Nếu cùng cột → thay bằng chữ dưới (wrap).  
Nếu khác hàng và cột → thay bằng hai chữ ở cùng hàng tương ứng nhưng cột tráo (hình chữ nhật).  

* Giải mã: ngược lại (bên trái / trên / tráo).  

* Không gian khoá:  
Số ma trận 5×5 sắp xếp 25 chữ = 25! ≈ 1.55×10^25 (rất lớn). Nhưng nhiều key khác nhau có cùng ma trận nếu khoá khác nhưng kết quả cuối cùng giống.  

* Phá mã (không cần khoá):  
Phân tích digraph tần suất; tấn công dựa trên mẫu từ (độ dài digraph, bigram frequencies).  
So với monoalphabetic, Playfair phức tạp hơn nhưng vẫn bị tấn công bằng kỹ thuật thống kê và brute-force/heuristic.  

# Ảnh minh họa :  
* Mã hóa (Encrypt):
  <img width="1193" height="837" alt="image" src="https://github.com/user-attachments/assets/50dae9f6-5626-4084-82d0-fd9feb24453b" />

* Giải mã (Decrypt):
  <img width="1193" height="846" alt="image" src="https://github.com/user-attachments/assets/6d5a589b-03d7-4179-9bcc-a79f26f9d65d" />
