	ĐẠI HỌC QUỐC GIA HÀ NỘI	CỘNG HÒA XÃ HỘI CHỦ NGHĨA VIỆT NAM
	TRƯỜNG ĐẠI HỌC CÔNG NGHỆ	Độc lập - Tự do - Hạnh phúc
		====================
BÁO CÁO BÀI TẬP LỚP MÔN LẬP TRÌNH NÂNG CAO
Sinh viên:….Phan Vũ Liêm	Sinh ngày:	15/11/2004
Ngành học:Mạng máy tính và truyền thông dữ liệu	 Lớp: INT2215 3
Tên game : Temptation
Link Github Repo: 
Lối chơi, logic của game: Trò chơi platformer 
Đồ họa, âm thanh: Đồ họa load bằng từ điển SDL2, các sprite em lấy từ nguồn opensource trên itch.io
-	https://pixelfrog-assets.itch.io/pixel-adventure-1 
Cấu trúc của project game: Tệp Assets chứa code điều khiển người chơi Player, và chứa code xử lý địa hình.
	                                Tệp Game chứa code xử lý SDL (initSDL, quitSDL, windows, renderer, v.v) và phần lớn logic của Game.
                                             Tệp Imgs chứa các ảnh được sử dụng cho game.
Các chức năng đã cài được cho game: 
           - InitSDL, quitSDL giống như trên lớp dạy + button và terrain để render bản đồ
- Hệ thống thay đổi level 
- Các nút thay đổi/thoát/back level, handle bộ nhớ không bị trào bộ nhớ
- Nhảy, chạy, code trọng lực
- Có các hộp có khả năng giết nhân vật (biến canKill)
- Nếu rơi ra khỏi map, giết người chơi và có biến respawn() để trả nhân vật về chỗ ban đầu
- Camera theo nhân vật, render bản đồ theo vị trí camera/những gì người chơi nhìn thầy được
- Animation pháo hoa khi thắng + trở về Menu

