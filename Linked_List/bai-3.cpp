/*
Trên ngôn ngữ C/C++, viết chương trình thực hiện yêu cầu sau:

1. Định nghĩa một cấu trúc Sinh viên bao gồm các trường thông tin như sau:
	Mã Sinh viên (kiểu số nguyên),
	tên Sinh viên (kiểu chuỗi ký tự),
	lớp (kiểu chuỗi ký tự),
	điểm tổng kết (kiểu số thực),
	hạnh kiểm (Tốt, khá, trung bình, yếu).
2. Cài đặt một cấu trúc danh sách liên kết đơn cho kiểu dữ liệu Sinh viên, với các thao tác:
	1) Khởi tạo danh sách;
	2) kiểm tra rỗng
	3) thêm phần tử vào cuối (hoặc đầu) danh sách
	4) Tìm kiếm phần tử trong danh sách;
	5) Xóa phần tử cuối cùng khỏi danh sách;
	6) Duyệt danh sách;
	7) Sắp xếp danh sách	
3. Chương trình chính: Sử dụng cấu trúc danh sách liên kết đơn và các thao tác ở trên để:
– Nhập vào một danh sách liên kết đơn gồm n Sinh viên (n bất kỳ).
– Hiển thị danh sách đã nhập ra màn hình.
-Liệt kê ra màn hình danh sách tất cả những Sinh viên thuộc lớp “D13CNPM”.
– Sắp sếp danh sách sinh viên theo mã sinh viên tăng dần
– Xóa phần tử cuối cùng khỏi danh sách.
Hiển thị lại danh sách sau khi xóa ra màn hình.
*/

#include <iostream>
#include <string>
using namespace std;
struct SinhVien
{
	int ID;
	string Name;
	string Class;
	float Final_Score;
	string Conduct;
};
void Get_Conduct(SinhVien* SV)
{
	if (SV->Final_Score >= 8.0)
	{
		SV->Conduct = "TOT";
	}
	else if (SV->Final_Score >= 6.5 && SV->Final_Score < 8.0)
	{
		SV->Conduct = "KHA";
	}
	else if (SV->Final_Score >= 4.0 && SV->Final_Score < 65)
	{
		SV->Conduct = "TRUNG BINH";
	}
	else if(SV->Final_Score >= 0 && SV->Final_Score < 4.0)
	{
		SV->Conduct = "YEU";
	}
}
SinhVien* Nhap_1_Sinh_Vien(SinhVien* SV)
{
	cout << "Nhap ma sinh vien: ";
	cin >> SV->ID;
	cout << "Nhap ten sinh vien: ";
	cin.ignore();
	getline(cin, SV->Name);
	cout << "Nhap lop: ";
	getline(cin, SV->Class);
	cout << "Nhap diem: ";
	cin >> SV->Final_Score;
	Get_Conduct(SV);
	return SV;
}
void xuat(SinhVien *SV)
{
	cout << SV->ID << ", " << SV->Name << ", " << SV->Class << ", " << SV->Final_Score << ", " << SV->Conduct << endl;
}
struct node
{
	SinhVien data;
	node* next;
};
node* MakeNode(SinhVien SV)
{
	node* newnode = new node();
	newnode->data = SV;
	newnode->next = NULL;
	return newnode;
}
void Push_Front(node*& head, SinhVien* SV)
{
	node* newnode = MakeNode(*SV);
	newnode->next = head;
	head = newnode;
}
void Push_Back(node*& head, SinhVien* SV)
{
	node* temp = head;
	node* newnode = MakeNode(*SV);
	if (head == NULL)
	{
		head = newnode;
		return;
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = newnode;
	}
}
void duyet(node* head)
{
	while (head != NULL)
	{
		cout << head->data.ID << ", " << head->data.Name << ", " << head->data.Class << ", " << head->data.Final_Score << ", " << head->data.Conduct << endl;
		head = head->next;
	}
}
int Count(node* head)
{
	int cnt = 0;
	while (head != NULL)
	{
		cnt++;
		head = head->next;
	}
	return cnt;
}
bool Check_Empty(node* head)
{
	if (head == NULL)
	{
		return true;
	}
	return false;
}
void Swap(SinhVien& a, SinhVien& b)
{
	SinhVien temp = a;
	a = b;
	b = temp;
}
node* Last_Node(node* head)
{
	node* temp = head;
	while (temp != NULL && temp->next != NULL)
	{
		temp = temp->next;
	}
	return temp;
}

// Quick_Sort
node* Partition(node*&First, node*& Last)
{
	node* Pivot = First;
	node* Front = First;
	while (Front != NULL && Front != Last)
	{
		if (Front->data.Final_Score < Last->data.Final_Score)
		{
			Pivot = First;
			Swap(First->data, Front->data);
			First = First->next;
		}
		Front = Front->next;
	}
	if (First != NULL && Front != NULL)
	{
		Swap(First->data, Last->data);
	}
	return Pivot;
}
void Quick_Sort(node* First, node* Last)
{
	if (First == Last)
	{
		return;
	}
	node* Pivot = Partition(First, Last);
	if (Pivot != NULL && Pivot->next != NULL)
	{
		Quick_Sort(Pivot->next, Last);
	}
	if (Pivot != NULL && First != Pivot)
	{
		Quick_Sort(First, Pivot);
	}
}
void Search(node* head, string x)
{
	for (node* temp = head; temp != NULL; temp = temp->next)
	{
		if (x == temp->data.Class)
		{
			cout << temp->data.ID << ", " << temp->data.Name << ", " << temp->data.Class << ", " << temp->data.Final_Score << ", " << temp->data.Conduct << endl;
		}
	}
}
void Earse_Last_Node(node*& head)
{
	node* temp = head;
	if (temp == NULL)
	{
		cout << "Empty List" << endl;
		return;
	}
	if (temp->next == NULL)
	{
		head == NULL;
		delete(temp);
		return;
	}
	while (temp->next->next != NULL)
	{
		temp = temp->next;
	}
	node* last = temp->next;
	temp->next = NULL;
	delete(last);
}
void menu(node*& head)
{
	while (true)
	{
		cout << "===================================================" << endl;
		cout << "= 1. Them 1 sinh vien vao dau danh sach lien ket" << endl;
		cout << "= 2. Them 1 sinh vien vao cuoi danh sach lien ket" << endl;
		cout << "= 3. Them n sinh vien vao dau danh sach lien ket" << endl;
		cout << "= 4. Them n sinh vien vao cuoi danh sach lien ket" << endl;
		cout << "= 5. Kiem tra rong" << endl;
		cout << "= 6. Sap xep mang theo diem trung binh" << endl;
		cout << "= 7. Liet ke sinh vien o lop D13CNPM" << endl;
		cout << "= 8. Xoa phan tu cuoi cung trong danh sach lien ket" << endl;
		cout << "= 10. Duyet" << endl;
		cout << "= 0. Thoat" << endl;
		cout << "===================================================" << endl;
		int luachon;
		cout << "nhap lua chon cua ban: ";
		cin >> luachon;
		if (luachon == 1)
		{
			SinhVien* SV = new SinhVien();
			SV = Nhap_1_Sinh_Vien(SV);
			Push_Front(head, SV);
		}
		else if (luachon == 2)
		{
			SinhVien* SV = new SinhVien();
			SV = Nhap_1_Sinh_Vien(SV);
			Push_Back(head, SV);
		}
		else if (luachon == 3)
		{
			int n;
			cout << "ban muon them bao nhieu sinh vien vao dau danh sach lien ket: ";
			cin >> n;
			for (int i = 1; i <= n; i++)
			{
				SinhVien* SV = new SinhVien();
				SV = Nhap_1_Sinh_Vien(SV);
				Push_Front(head, SV);
			}
		}
		else if (luachon == 4)
		{
			int n;
			cout << "ban muon them bao nhieu sinh vien vao cuoi danh sach lien ket: ";
			cin >> n;
			for (int i = 1; i <= n; i++)
			{
				SinhVien* SV = new SinhVien();
				SV = Nhap_1_Sinh_Vien(SV);
				Push_Back(head, SV);
			}
		}
		else if (luachon == 5)
		{
			if (Check_Empty(head))
			{
				cout << "Danh sach lien ket cua ban rong" << endl;
			}
			else
			{
				cout << "Danh sach lien ket cua ban co " << Count(head) << " phan tu" << endl;
			}
		}
		else if (luachon == 6)
		{
			Quick_Sort(head, Last_Node(head));
			cout << "Sap xep thanh cong" << endl;
		}
		else if (luachon == 7)
		{
			Search(head, "D13CNPM");
		}
		else if (luachon == 8)
		{
			Earse_Last_Node(head);
		}
		else if (luachon == 10)
		{
			duyet(head);
		}
		else
		{
			break;
		}
	}
}
int main()
{
	node* head = NULL;
	menu(head);
	
	return 0;
}