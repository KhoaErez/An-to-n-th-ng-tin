#include <iostream>
using namespace std;

// Hàm kiểm tra nghịch đảo của a trong modulo 97
bool kiemTraNghichDao(int a, int &a_inv)
{
    int flag = 0; 
    a = a % 97; // chuyển a về giá trị trong khoảng từ 0 -> 96      
    for (int i = 0; i < 97; i++) {
        flag = (a * i) % 97;
        if (flag == 1) {
            a_inv = i;
            return true; // Có nghịch đảo
        }
    }
    return false; // Không có nghịch đảo
}

// Hàm kiểm tra ký tự có hợp lệ hay không
bool kiemTraChuoiHopLe(const string &chuoi)
{
    for (char c : chuoi) {
        if (c < 32 || c >= 129) { // Các ký tự hợp lệ nằm trong khoảng 32 - 128
            cout << "\n\t\t!!!Loi: Ky tu khong hop le '" << c << "'. Khong the ma hoa!" << endl;
            return false;
        }
    }
    return true;
}

void quaTrinhMaHoa(string chuoi, int a, int b)
{
	cout << "\n*Qua trinh ma hoa*" << endl;
	for (int i = 0; i < chuoi.length(); i++) {
        cout << chuoi[i] << " => " << (char)((((a * (chuoi[i] - 32)) + b) % 97) + 32) << "\t";
    }
}

string maHoaVanBan(string chuoi, int a, int b)
{
    string banRo = "";
    for (int i = 0; i < chuoi.length(); i++) {
        banRo = banRo + (char)((((a * (chuoi[i] - 32)) + b) % 97) + 32);
    }
    return banRo;
}

void quaTrinhGiaiMa(string chuoiMaHoa, int a, int b)
{
	int a_inv = 0;
	// Kiểm tra nghịch đảo của a trong modulo 97
    if (!kiemTraNghichDao(a, a_inv)) {
        cout << "khong co nghich dao trong modulo 97. Khong the giai ma!" << endl;
        return ;
    }
	
	cout << "\n*Qua trinh giai ma*" << endl;
	for (int i = 0; i < chuoiMaHoa.length(); i++) {
        cout << chuoiMaHoa[i] << " => " << (char)(((a_inv * (chuoiMaHoa[i] - 32 - b + 97)) % 97) + 32) << "\t";
    }
}

string giaiMaVanBan(string chuoiMaHoa, int a, int b)
{
    string giaiMa = "";
    int a_inv = 0;
    kiemTraNghichDao(a, a_inv);
    for (int i = 0; i < chuoiMaHoa.length(); i++) {
        giaiMa = giaiMa + (char)(((a_inv * (chuoiMaHoa[i] - 32 - b + 97)) % 97) + 32);
    }
    return giaiMa;
}

void menu()
{
    cout << "\n\t==================<MENU>==================";
    cout << "\n\t1.Ma hoa chuoi ki tu bang Affine.";
    cout << "\n\t2.Giai ma chuoi ki tu bang Affine.";
    cout << "\n\t0.Thoat!";
    cout << "\n\t==================<END!>==================\n";
}

void nhapSoNguyen(int &so, const string &tenBien)
{
    while (true) {
        cout << "\t\t+ Nhap " << tenBien << ": ";
        cin >> so;
        if (cin.fail()) // Kiểm tra nếu nhập sai (không phải số nguyên)
        {
            cin.clear();   // Xóa cờ lỗi
            fflush(stdin); // Xóa bỏ các ký tự thừa trong bộ đệm
            cout << "\n\t\t!!!Loi: Gia tri nhap vao khong hop le. Vui long nhap lai\n";
        } else {
            fflush(stdin);
            break;
        }
    }
}

void nhapKhoa(int &a, int &b)
{
    int a_inv;
    while (true) {
        nhapSoNguyen(a, "a");
        nhapSoNguyen(b, "b");

        if (kiemTraNghichDao(a, a_inv)) {
            break; // Nếu a có nghịch đảo, thoát khỏi vòng lặp
        } else {
            cout << "\n\t\t!!!Loi: Khong co nghich dao trong modulo 97. Vui long nhap lai a va b.\n";
        }
    }
}

int main()
{
    int a, b;
    int n = -1;
    while (n != 0) {
        menu();
        nhapSoNguyen(n, "lua chon");
        fflush(stdin);
        switch (n) {
            case 1: {
                string chuoi;
                cout << "\t\t+Nhap chuoi can ma hoa: ";
                getline(cin, chuoi);
                
                // Kiểm tra chuỗi có ký tự không hợp lệ hay không
                if (!kiemTraChuoiHopLe(chuoi)) {
                    break; // Nếu chuỗi có ký tự không hợp lệ, dừng lại
                }
                
                nhapKhoa(a, b); // Yêu cầu nhập a và b, sau đó kiểm tra nghịch đảo
                quaTrinhMaHoa(chuoi, a, b);
                cout << "\n\t->Chuoi ki tu sau khi duoc ma hoa la: " << maHoaVanBan(chuoi, a, b) << endl;
                break;
            }
            case 2: {
                string chuoi;
                cout << "\t\t+Nhap chuoi can giai ma: ";
                getline(cin, chuoi);
                
                // Kiểm tra chuỗi có ký tự không hợp lệ hay không
                if (!kiemTraChuoiHopLe(chuoi)) {
                    break; // Nếu chuỗi có ký tự không hợp lệ, dừng lại
                }
                
                nhapKhoa(a, b); // Yêu cầu nhập a và b, sau đó kiểm tra nghịch đảo
                quaTrinhGiaiMa(chuoi, a, b);               
                cout << "\n\t->Chuoi ki tu sau khi duoc giai ma la: " << giaiMaVanBan(chuoi, a, b) << endl;
                break;
            }
            case 0: {
                cout << "\t\t*Thoat thanh cong!*";
                break;
            }
            default: {
                cout << "\tLua chon khong hop le!";
                break;
            }
        }
    }
    return 0;
}
