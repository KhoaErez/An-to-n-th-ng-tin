#include <iostream>
#include <vector>
using namespace std;

int lengthChuoibandau = 0;

// Hàm tính định thức của ma trận n x n
int tinhDinhThuc(const vector<vector<int>>& mat, int n) {
    if (n == 1)
        return mat[0][0];
    if (n == 2)
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

    int det = 0;
    for (int i = 0; i < n; i++) {
        vector<vector<int>> subMat(n - 1, vector<int>(n - 1));
        for (int j = 1; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (k < i) {
                    subMat[j - 1][k] = mat[j][k];
                } else if (k > i) {
                    subMat[j - 1][k - 1] = mat[j][k];
                }
            }
        }
        det += (i % 2 == 0 ? 1 : -1) * mat[0][i] * tinhDinhThuc(subMat, n - 1);
        det = (det % 97 + 97) % 97;
    }
    return det;
}



// Hàm tìm số nghịch đảo của modulo
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1; // Không tồn tại số nghịch đảo
}

bool maTranNghichDao(vector<vector<int>>& kInverse, const vector<vector<int>>& k) {
    int n = k.size();
    int detK = tinhDinhThuc(k, n); // Tính định thức của ma trận k
    detK = (detK % 97 + 97) % 97; // Đảm bảo định thức trong khoảng [0, 96]

    int detKInverse = modInverse(detK, 97); // Sử dụng hàm modInverse
    if (detKInverse == -1) {
        cout << "Ma tran khong co nghich dao!" << endl;
        return false;
    }

    // Tính ma trận nghịch đảo cho n x n
    kInverse.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Tạo ma trận phụ
            vector<vector<int>> subMat(n - 1, vector<int>(n - 1));
            for (int row = 0; row < n; row++) {
                for (int col = 0; col < n; col++) {
                    if (row != i && col != j) {
                        subMat[row < i ? row : row - 1][col < j ? col : col - 1] = k[row][col];
                    }
                }
            }
            // Tính định thức của ma trận phụ
            int sign = (i + j) % 2 == 0 ? 1 : -1;
            kInverse[j][i] = (sign * tinhDinhThuc(subMat, n - 1) * detKInverse) % 97;
            kInverse[j][i] = (kInverse[j][i] + 97) % 97; // Đảm bảo không âm
        }
    }
    return true;
}

// Hàm mã hóa chuỗi ký tự
string thucHienMaHoa(string chuoiMaHoa, const vector<vector<int>>& k) {
    int n = k.size();
    string maHoa = "";
    // Đảm bảo chiều dài chuỗi là bội số của n
    if (chuoiMaHoa.length() % n != 0) {
        chuoiMaHoa.append(n - chuoiMaHoa.length() % n, 'X'); // Thêm ký tự 'X'
    }
	
    cout << "Ma hoa chuoi: " << chuoiMaHoa << endl; // In ra chuỗi gốc
	cout << "\n\t<Qua trinh ma hoa>" << endl;
    for (int i = 0; i < chuoiMaHoa.length(); i += n) {
        vector<int> msg(n);
        cout << "\n***Khoi du lieu: ";
        for (int j = 0; j < n; j++) {
            msg[j] = chuoiMaHoa[i + j] - 30; // Chuyển ký tự sang số
            cout << (char)(msg[j] + 30) << " "; 
        }
		cout << endl;
        for (int j = 0; j < n; j++) {
            int temp = 0;
            for (int k2 = 0; k2 < n; k2++) {
                temp += msg[k2] * k[k2][j];
            }
            char maHoaChar = (char)((temp % 97 + 97) % 97 + 30); // Chuyển số về ký tự
            maHoa += maHoaChar; // Thêm ký tự mã hóa vào chuỗi mã hóa
            cout << "Ky tu ma hoa: " << (char)(msg[j] + 30) << " -> " << maHoaChar << endl; // In ra ký tự mã hóa và mã số tương ứng
        }
    }
    return maHoa;
}

// Hàm giải mã chuỗi ký tự
string thucHienGiaiMa(string chuoiMaHoa, const vector<vector<int>>& k) {
    string giaiMa = "";
    vector<vector<int>> kInverse;

    if (!maTranNghichDao(kInverse, k)) {
        return ""; // Không thể giải mã nếu không có nghịch đảo
    }

    cout << "Ma tran nghich dao k^-1: " << endl;
    for (const auto& hang : kInverse) {
        for (const auto& cot : hang) {
            cout << cot << " ";
        }
        cout << endl;
    }

    int n = k.size();
    cout << "\n\t<Qua trinh giai ma>" << endl;
    for (int i = 0; i < chuoiMaHoa.length(); i += n) {
        vector<int> msg(n);
        cout << "\n***Khoi du lieu: ";
        for (int j = 0; j < n; j++) {
            msg[j] = chuoiMaHoa[i + j] - 30; // Chuyển ký tự sang số
            cout << (char)(msg[j] + 30) << " "; // In ra ký tự và giá trị số
        }
		cout << endl;
        for (int j = 0; j < n; j++) {
            int temp = 0;
            for (int k2 = 0; k2 < n; k2++) {
                temp += msg[k2] * kInverse[k2][j]; // Nhân với ma trận nghịch đảo
            }
            char giaiMaChar = (char)((temp % 97 + 97) % 97 + 30); // Chuyển số về ký tự
            giaiMa += giaiMaChar; // Thêm ký tự giải mã vào chuỗi giải mã
            cout << "Ky tu giai ma: " << (char)(msg[j] + 30) << " -> " << giaiMaChar << endl; // In ra ký tự giải mã và mã số tương ứng
        }
    }
    // Loại bỏ các ký tự 'X' thêm vào nếu có (nếu muốn khôi phục chuỗi ban đầu)
    if (giaiMa.length() > lengthChuoibandau) {
        for(int i = giaiMa.length() - 1; i >= 0; i--)
		{
			if((char)giaiMa[i] == 'X')
				giaiMa.pop_back(); // Loại bỏ ký tự thừa X them vao
		}
    }
    return giaiMa;
}

void menu()
{
	cout << "\t=================<MENU>=================" << endl;
	cout << "\t1.Nhap khoa ma tran." << endl;
	cout << "\t2.Ma hoa bang ma hoa Hill." << endl;
	cout << "\t3.Giai ma bang ma hoa Hill." << endl;
	cout << "\t0.Thoat." << endl;
	cout << "\t=================<END!>=================" << endl;
}

int main() {
    string chuoiMaHoa;
    int size;
	string maHoa, giaiMa;
	vector<vector<int>> temp;
		
	int lc = -1;
	while(lc != 0)
	{
		menu();
		cout << "-> Nhap lua chon: "; cin >> lc;
		
		switch(lc)
		{
			case 0:
				{
					cout << "\t\t*Thoat thanh cong*";
					break;
				}
			case 1:
				{
					cout << "Nhap kich thuoc cho ma tran khoa: ";
				    cin >> size;
					if(cin.fail())
					{
						cout << "->Ki tu khong hop le, vui long nhap lai." << endl;
					    cin.clear(); // Xóa trạng thái lỗi của cin
					    cin.ignore(); // Bỏ qua phần nhập không hợp lệ
					}
					else if(size < 2)
					{
						cout << "->Ki tu khong hop le, vui long nhap lai." << endl;
				    	cin.clear(); // Xóa trạng thái lỗi của cin
					    cin.ignore(); // Bỏ qua phần nhập không hợp lệ
					}
				    else
				    {
				    	vector<vector<int>> k(size, vector<int>(size));				    
					    cout << "\nNhap ma tran khoa: " << endl;
					    for (int i = 0; i < size; i++) {
					        for (int j = 0; j < size; j++) {
					        	
					            int value;
					            
								cin >> value;
					            if(value < 0)
					            {
					            	cout << "->Khoa k vua nhap khong hop le, vui long nhap lai" << endl;
					            	--j;
								}
								else if(cin.fail())
								{
									cout << "->Khoa k vua nhap khong hop le, vui long nhap lai." << endl;
								    cin.clear(); // Xóa trạng thái lỗi của cin
								    cin.ignore(); // Bỏ qua phần nhập không hợp lệ
								    --j;
								}
								else {
								    k[i][j] = value;
								}
					        }
					    } 
					    cout << "Ma tran khoa vua nhap la: " << endl;
					    for(int i = 0; i < size; i++)
					    {
					    	for(int j = 0; j < size; j++)
					    	{
					    		cout << k[i][j] << " ";
							}
							cout << endl;
						}
						
						// Kiểm tra định thức của ma trận khóa
				        int detK = tinhDinhThuc(k, size);
				        if (detK <= 0) { // Kiểm tra cả định thức âm và bằng 0
						    cout << "->Dinh thuc cua ma tran la: "<< detK << " khong hop le! (Phai la so duong)" << endl;
						    break;
							} 
						else {
						    cout << "Dinh thuc cua ma tran la: " << detK << endl;
						}
					    temp = k;
					}break;
				}
			case 2:
				{
					if(!temp.empty())
					{
						cin.ignore();
					    cout << "Nhap chuoi can ma hoa: "; 
					    getline(cin, chuoiMaHoa);
					    bool flag = false;
						for(int i = 0; i < chuoiMaHoa.length(); i++)
						{
							if((chuoiMaHoa[i] < 30) || (chuoiMaHoa[i] > 126))
							{
								cout << "Chuoi ki tu vua nhap khong hop le, khong the ma hoa duoc!" << endl;
								flag = true;
								break;
							}
						}
						if(!flag)
						{
							maHoa = thucHienMaHoa(chuoiMaHoa, temp);
					    	cout << "->Chuoi sau khi duoc ma hoa: " << maHoa << endl;
						}
						else{
							break;
						}
					}
					else
					{
						cout << "\t*Vui long tao khoa truoc!" << endl;
					}
					break;
				}
			case 3:
				{
					if(!temp.empty())
					{
						if(!maHoa.empty())
						{
							giaiMa = thucHienGiaiMa(maHoa, temp);
    						cout << "->Chuoi sau khi duoc giai ma: " << giaiMa << endl;
						}
						else
						{
							cout << "\t*Vui long ma hoa ki tu truoc!" << endl;
						}
					}
					else
					{
						cout << "\t*Vui long tao khoa truoc!" << endl;
					}
					break;
				}
			default:
				{
					cout << "Lua chon khong hop le, Vui long nhap lai!" << endl;
					break;
				}
		}				
	}
    return 0;
}
