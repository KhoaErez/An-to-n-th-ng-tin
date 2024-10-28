#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MOD = 97; 

bool kiemTra(const string &key) {
    for (char c : key) {
        // Kiểm tra ký tự có nằm ngoài khoảng 30 -> 126
        if (c < 30 || c > 126) {
            cout << "-> Ky tu '" << c << "' khong hop le!" << endl;
            return false;
        }
    }
    return true;
}

// mục đích sử dụng vector thay vì dùng mảng là bởi vì vector nó linh động hơn
//(có nghĩa là nếu khai báo a[100] thì nếu trường hợp người dùng nhập quá 100 kí tự sẽ xảy ra lỗi, còn vector nó sẽ tự động tăng kích thước ví dụ người dùng nhập 100 kí tự thì lúc đấy kích thước sẽ là 100(từ 0 -> 99))
void chuyenKeySangSo(const string& key, vector<int>& a) {
    // Chuyển đổi key từ ký tự sang số từ 0 đến 96 (dựa vào ASCII)
    // hàm resize được sử dụng trong vector, nó có mục đích là sẽ thay đổi kích thước của vector
    a.resize(key.length()); // ở đây nó sẽ có nghĩa là: kích thước của vector a sẽ bằng với độ dài của key(ví dụ như key nhập vào là: "abcx" => do dai sẽ la: 4)
    for (int i = 0; i < key.length(); i++) {
        a[i] = key[i] - 30; 
    }
}

void maHoa(const string& chuoiCanMaHoa, const vector<int>& a, int doDaiChuoiKhoa) {
    string chuoiMaHoa = "";
    cout << "\n*Qua trinh ma hoa*" << endl;
    for (int i = 0; i < chuoiCanMaHoa.length(); i++) {
        char ch = chuoiCanMaHoa[i];
        if (ch >= 30 && ch <= 126) {
            // Mã hóa ký tự
            char kyTuMaHoa = (ch - 30 + a[i % doDaiChuoiKhoa]) % MOD + 30;
            // giải thích dòng 36: 
            // ch - 30: trong bảng mã ascci mình sẽ lấy từ vị trí 30 -> 126, nên mình sẽ trừ đi 30 để trở thành vị trí 0->96 tương ứng với 97 kí tự
            // a[i % doDaiChuoiKhoa]: theo công thức vigenere ta sẽ thấy khi khóa hết thì sẽ quay lại từ ban đầu 
			//(ví dụ: 
			//Khóa k có độ dài là 3 với kí tự khóa tương ứng: "abc"
			//độ dài chuỗi cần mã hóa là: P = "HaNoiMuaThu"
			//                            K = "abcabcabcab" tức là nếu hết abc thì nó sẽ lặp lại
			// quay trở lại dòng 39 ta thấy: lấy vị trí của chuỗi cần mã hóa chia dư cho độ dài của khóa thì sẽ trở lại vị trí nằm trong khoảng từ 0->độ dài key - 1
			// (ch - 30 + a[i % doDaiChuoiKhoa]) % MOD: có nghĩa là sau khi cộng ch - 30 với a[i % doDaiChuoiKhoa] 
			// lại thì sẽ chia dư MOD(97) Để chắc chắn rằng kí tự sẽ nằm trong khoảng từ 0 -> 96 kí tự.
			// Cuối cùng + 30 để đem ký tự mã hóa xong trở lại vị trí của bảng mã Ascci
			
			// ->Phần giải thích này tương tự với phần giải mã nên mình sẽ không giải thích ở phần giải mã nữa
            cout << ch << "=>" << kyTuMaHoa << " ";
            chuoiMaHoa += kyTuMaHoa;
        } else {
            chuoiMaHoa += ch;
        }
    }
    cout << "\n-> Chuoi sau khi duoc ma hoa: " << chuoiMaHoa << endl;
}

void giaiMa(const string& chuoiMaHoa, const vector<int>& a, int doDaiChuoiKhoa) {
    string chuoiGiaiMa = "";
    cout << "\n*Qua trinh giai ma*" << endl;
    for (int i = 0; i < chuoiMaHoa.length(); i++) {
        char ch = chuoiMaHoa[i];
        if (ch >= 30 && ch <= 126) {
            // Giải mã ký tự
            char kyTuGiaiMa = (ch - 30 - a[i % doDaiChuoiKhoa] + MOD) % MOD + 30;
            cout << ch << "=>" << kyTuGiaiMa << " ";
            chuoiGiaiMa += kyTuGiaiMa;
        } else {
            chuoiGiaiMa += ch;
        }
    }
    cout << "\n-> Chuoi sau khi duoc giai ma: " << chuoiGiaiMa << endl;
}

void menu() {
    cout << "\n";
    cout << "\t\t=====================<MENU>=====================" << endl;
    cout << "\t\t1. Ma hoa chuoi ki tu bang thuat toan Vigenere" << endl;
    cout << "\t\t2. Giai ma chuoi ki tu bang thuat toan Vigenere" << endl;
    cout << "\t\t0. Thoat" << endl;
    cout << "\t\t=====================<END!>=====================" << endl;
}

int main() {
    string chuoi;
    string key;
    vector<int> a; // Sử dụng vector thay cho mảng tĩnh
    int n = -1;

    while (n != 0) {
        menu();
        cout << "Nhap lua chon: ";
        cin >> n;
        cin.ignore(); 
		// Khi bạn nhập 1 số nguyên sau đấy enter để tiếp tục nhập chuỗi với câu lệnh getline(cin, key) thì nó sẽ đọc ngay kí tự enter và kết thúc
		// vì vậy cin.ignore(); nhằm mục đích xóa kí tự Enter đấy đi
        switch (n) {
            case 0:
                cout << "Thoat thanh cong!" << endl;
                break;

            case 1: { // Mã hóa
                bool check = false;
                bool checkChuoi = false;
				do {
                    cout << "Nhap khoa (chuoi ki tu): ";
                    getline(cin, key);
                    check = kiemTra(key);
                    
                    if (!check)
                        cout << "*Vui long nhap lai!!!" << endl;
                	
                } while (!check);
                
                do{
                	cout << "Nhap chuoi can ma hoa: ";
                	getline(cin, chuoi);
                	checkChuoi = kiemTra(chuoi);
                	if (!checkChuoi)
                        cout << "*Vui long nhap lai!!!" << endl;
				}while(!checkChuoi);
                
                if (key.length() > chuoi.length()) {
                    cout << "!Canh bao: Khoa dai hon chuoi can ma hoa!" << endl;
                }

                chuyenKeySangSo(key, a); // Sử dụng vector a
                maHoa(chuoi, a, key.length());
                
                break;
            }

            case 2: { // Giải mã
                bool check = false;
                bool checkChuoi = false;
                do {
                    cout << "Nhap khoa (chuoi ki tu): ";
                    getline(cin, key);
                    check = kiemTra(key);
                    if (!check)
                        cout << "->*Vui long nhap lai!!!" << endl;        	
                } while (!check);
				
				do
				{
					cout << "Nhap chuoi can giai ma: ";
                	getline(cin, chuoi);
                	checkChuoi = kiemTra(chuoi);
                	if (!checkChuoi)
                        cout << "*Vui long nhap lai!!!" << endl;
				}while(!checkChuoi);
                
                if (key.length() > chuoi.length()) {
                    cout << "!Canh bao: Khoa dai hon chuoi can giai ma!" << endl;
                }

                chuyenKeySangSo(key, a); // Sử dụng vector a
                giaiMa(chuoi, a, key.length());                
                break;
            }

            default:
                cout << "** Lua chon sai, vui long nhap lai!" << endl;
                break;
        }
    }

    return 0;
}
