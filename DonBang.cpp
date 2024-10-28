#include <iostream>
#include <ctime>
#include <map>
#include <set>
using namespace std;

// Hàm tạo khóa ngẫu nhiên không trùng lặp
map<char, char> taoKhoa()
{
    srand(time(NULL));
    map<char, char> mp;
    set<char> s; // Đảm bảo các ký tự không trùng lặp

    for (int i = 30; i <= 126; i++)
    {
        char k = (char)i;
        char v;
        do
        {
            v = (char)rand() % (126 - 30 + 1) + 30;
        } while (s.find(v) != s.end()); // Kiểm tra ký tự v có bị trùng lặp không
        mp.insert(make_pair(k, v));
        s.insert(v);
    }

    return mp;
}

// Hàm mã hóa chuỗi
string maHoaChuoi(const string &chuoi, const map<char, char> &mp)
{
    string chuoiMaHoa = "";
    cout << "\nQua trinh ma hoa: " << endl;

    for (int i = 0; i < chuoi.length(); i++)
    {
        if (chuoi[i] < 32 || chuoi[i] > 126) {
            cout << "Khong the ma hoa ki tu: " << chuoi[i] << " vi co ky tu co dau!" << endl;
            return "";
        }
    }

    for (int i = 0; i < chuoi.length(); i++)
    {
        for (auto x : mp)
        {
            if (chuoi[i] == x.first)
            {
                chuoiMaHoa += x.second;
                cout << chuoi[i] << " => " << x.second << "\t";
                break;
            }
        }
    }
    return chuoiMaHoa;
}

// Hàm giải mã chuỗi
string giaiMaChuoi(const string &chuoiMaHoa, const map<char, char> &mp)
{
    string chuoiGiaiMa = "";
    cout << "\nQua trinh giai ma: " << endl;

    for (int i = 0; i < chuoiMaHoa.length(); i++)
    {
        for (auto x : mp)
        {
            if (chuoiMaHoa[i] == x.second)
            {
                chuoiGiaiMa += x.first;
                cout << chuoiMaHoa[i] << " => " << x.first << "\t";
                break;
            }
        }
    }
    return chuoiGiaiMa;
}

// Hàm hiển thị khóa
void hienThiKhoa(const map<char, char> &mp)
{
    cout << "Khoa tu dong duoc sinh ra la: " << endl;
    int i = 0;
    for (auto x : mp)
    {
        cout << x.second << " ";
        i++;
    }
    cout << endl;
}

// Hàm hiển thị menu
void menu()
{
    cout << "\n\t==================<MENU>==================";
    cout << "\n\t1. Tao khoa tu dong.";
    cout << "\n\t2. Ma hoa chuoi ki tu.";
    cout << "\n\t3. Giai ma chuoi ki tu.";
    cout << "\n\t0. Thoat!";
    cout << "\n\t==================<END!>==================\n";
}

int main()
{
    int luaChon = -1;
    string maHoa; // Chuỗi đã mã hóa
    map<char, char> khoa; // Biến khóa

    while (luaChon != 0)
    {
        menu();
        cout << "\t\t+ Nhap lua chon: ";
        cin >> luaChon;
        cin.ignore(); // Xóa bộ đệm để nhập chuỗi

        switch (luaChon)
        {
            case 1:
            {
                // Tạo khóa ngẫu nhiên
                khoa = taoKhoa();
                hienThiKhoa(khoa);
                break;
            }
            case 2: {
                // Kiểm tra xem khóa đã được tạo chưa
                if (khoa.empty()) {
                    cout << "Vui long tao khoa tu dong truoc khi ma hoa!" << endl;
                    break;
                }

                // Nhập chuỗi cần mã hóa
                string chuoi;
                cout << "\nNhap chuoi can ma hoa: ";
                getline(cin, chuoi);

                // Mã hóa chuỗi
                string chuoiMaHoa = maHoaChuoi(chuoi, khoa);
                maHoa = chuoiMaHoa;
                if (!chuoiMaHoa.empty()) // Chỉ hiển thị kết quả nếu không có ký tự không hợp lệ
                {
                    cout << "\n\n-> Chuoi sau khi duoc ma hoa la: " << chuoiMaHoa << endl;
                }
                break;
            }
            case 3: {
                // Kiểm tra xem có chuỗi mã hóa không
                if (maHoa.empty()) {
                    cout << "Vui long ma hoa truoc khi giai ma!" << endl;
                    break;
                }

                // Giải mã chuỗi
                string chuoiGiaiMa = giaiMaChuoi(maHoa, khoa);
                cout << "\n\n-> Chuoi sau khi duoc giai ma la: " << chuoiGiaiMa << endl;
                break;
            }
            case 0: {
                cout << "\t\t*Thoat thanh cong!*";
                break;
            }
            default: {
                cout << "\tLua chon khong hop le! Vui long chon lai.\n";
                break;
            }
        }
    }
    return 0;
}
