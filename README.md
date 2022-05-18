1.Hướng dẫn cài đặt<space><space>:
*Cách lấy chương trình về: 
  -Tải xuống các file trong repo này
*Cài đặt để chạy được chương trình
  -Cài đặt đồ họa C++: hướng dẫn https://pie-cheque-188.notion.site/C-i-t-h-a-C-Windows-ef0a99a8dcae4dae86a39dc1cbc35980 (hướng dẫn cô đọng, không thể rút ngắn thêm)
  -Các thư viện khác: tải về từ:
                  SDL_image-2.0.5 https://www.libsdl.org/projects/SDL_image/
                  SDL_mixer-2.0.4 https://www.libsdl.org/projects/SDL_mixer/
                  SDL_ttf-2.0.15  https://www.libsdl.org/projects/SDL_ttf/release/

2.Mô tả chung về trò chơi
*Luật chơi
  -Bảng ô vuông trống thể hiện "bãi mìn".
  -Click chuột vào một ô vuông trong bảng. Nếu không may trúng phải ô có mìn thì trò chơi kết thúc. Trường hợp khác là ô đó không có mìn và một vùng các ô sẽ được mở   ra cùng với những con số. Số trên một ô là lượng mìn trong 8 ô nằm quanh với ô đó.
  -Nếu chắc chắn một ô có mìn, người chơi đánh dấu vào ô đó bằng hình lá cờ (click chuột phải).
  -Trò chơi kết thúc với phần thắng dành cho người chơi nếu mở được tất cả các ô không có mìn.
  (Trích https://vi.wikipedia.org/wiki/D%C3%B2_m%C3%ACn_(tr%C3%B2_ch%C6%A1i))

3.Mô tả chức năng
 -Game dò mìn cổ điển kích thước 10x10 ô, rải 12 quả mìn
 -Chơi lại sau khi kết thúc
 -Có âm thanh 
*Video minh họa

4.Các kỹ thuật lập trình được sử dụng
-mảng: tạo bảng khởi đầu, tạo bảng hiển thị
-con trỏ: cho các đối tượng đồ họa 
-lớp: khai báo và viết các hàm thành viên để hiển thị/cập nhật
-đồ họa SDL

5.Kết luận
*Hướng phát triển: 
  -tạo bãi mìn hình tròn
*Điều tâm đắc:

  
