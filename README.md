# 1.Hướng dẫn cài đặt: 
*Cài đặt để chạy được chương trình: hướng dẫn cho devc++, window



-Cài đặt đồ họa C++:(https://pie-cheque-188.notion.site/C-i-t-h-a-C-Windows-ef0a99a8dcae4dae86a39dc1cbc35980)




# Tóm tắt:
# 1. Downloads

1. MinGW-W64 GCC-7.3.0-SEH 
    
    https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-win32/seh/x86_64-7.3.0-release-win32-seh-rt_v5-rev0.7z
    
2. SDL2 MinGW
    
    https://www.libsdl.org/release/SDL2-devel-2.0.20-mingw.tar.gz
    
    


# 2. Setup MinGW-W64 (64bit)

- Giải nén file x86_64-7.3.0-release-win32-seh-rt_v5-rev0.7z
- Copy thư mục `mingw64` vào ROOTDIR
- Cài đặt đường dẫn PATH đến  ROOTDIR\mingw64\bin

# 3. Setup SDL2 (64bit)

- Giải nén file mingw.tar.gz
- Copy thư mục `SDL2-2.0.20` vào ROOTDIR
- Trong thư mục ROOTDIR\SDL2-2.0.20\x86_64-w64-mingw32 có 3 thư mục `bin, include, lib`
- Tạo 1 thư mục SRCDIR để chứa các file mã nguồn
- Tạo thư mục `src` trong SRCDIR
- *Copy thư mục* `include, lib` ở trên vào `src`
- *Copy các file* trong thư mục `bin` vào SRCDIR
  
  
  
  
# -Các thư viện sau đây làm tương tự như với SDL2
  
  
SDL_image-2.0.5 https://www.libsdl.org/projects/SDL_image/
  
  
  
  
  
SDL_mixer-2.0.4 https://www.libsdl.org/projects/SDL_mixer/ 
  
  
  
  
  
  
  
  
  
  
SDL_ttf-2.0.15 https://www.libsdl.org/projects/SDL_ttf/release/
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  # *Cách lấy chương trình về: 
-Tải xuống các file trong repo này trừ final.rar, copy tất cả vào ROOTDIR
  
  # Dịch chương trình
  
  
  Shift + chuột trái -> Windows PowerShell -> nhập mingw32-make
  
  
  
  # Run:
  
  
  
  trong cửa sổ windows powershell-> nhập .\main.exe
  
  
  
# 2.Mô tả chung về trò chơi 
  
  
  
*Luật chơi -Bảng ô vuông trống thể hiện "bãi mìn". 
  

  
  
  
-Click chuột vào một ô vuông trong bảng. Nếu không may trúng phải ô có mìn thì trò chơi kết thúc. Trường hợp khác là ô đó không có mìn và một vùng các ô sẽ được mở ra cùng với những con số. Số trên một ô là lượng mìn trong 8 ô nằm quanh với ô đó. 
  
  
  
  
-Nếu chắc chắn một ô có mìn, người chơi đánh dấu vào ô đó bằng hình lá cờ (click chuột phải). 
  
  
  
-Trò chơi kết thúc với phần thắng dành cho người chơi nếu mở được tất cả các ô không có mìn. (Wiki)
  
  
  
# 3.Mô tả chức năng 
  
  
  
  
-Game dò mìn cổ điển kích thước 10x10 ô, rải 12 quả mìn, có thời gian
  
  
  
-Chơi lại sau khi kết thúc 
  
  
  
  
-Có âm thanh 
  
  
  
*Video minh họa https://youtu.be/EM4ntd7xmqU
  
  
  
# 4.Các kỹ thuật lập trình được sử dụng 
  
  
  
-mảng, lớp, đồ họa SDL
  
  
  
# 5.Kết luận 
# *Hướng phát triển: 
  
  
  
  -phiên bản có bãi mìn hình tròn 
  
  
  
  -người chơi tự điều chỉnh số ô, bom, nhập tên người chơi khi bắt đầu và in ra tên khi thắng
  
  
  
  -
  
  
  
# *Điều tâm đắc:
  
  
  - hàm createPlayGround(), reveal() lúc đầu rất dài do chia nhỏ nhiều trường hợp, ở bản cuối cùng được rút ngắn, đưa về trường hợp bản chất
  
  
  
  


