/*
Viết chương trình trong ngôn ngữ C thực hiện các yêu cầu sau:

Khai báo cấu trúc dữ liệu để tổ chức danh sách liên kết đơn quản lý các tỉnh/thành phố của Việt Nam.
Thông tin của mỗi tỉnh/thành phố bao gồm: Mã tỉnh, tên tỉnh, diện tích, dân số.
Cài đặt các thao tác cơ bản (thêm ở vị trí bất kỳ; sửa, xóa theo mã (code), duyệt danh sách).
Tính tổng diện tích của tất cả các tỉnh thành.
Tìm vị trí của node của tỉnh có diện tích lớn nhất.
Tìm tỉnh/thành phố có dân số lớn nhất.
Sắp xếp danh sách theo mã tỉnh/thành phố.
Sắp xếp danh sách tăng dần theo diện tích.
Yêu cầu:
Viết chương trình cụ thể hóa các chức năng trên, người dùng có thể tương tác qua menu cho phép lựa chọn chức năng mà họ muốn.
Ban đầu, danh sách tỉnh/thành phố được nhập tự động từ 1 tập tin (Text file .txt) cho trước
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;
struct Province
{
	int ID;
	string Name;
	double Area;
	long long Population;
};
Province* Read_One_Province(ifstream& File_Province_In, Province*& Pro)
{
	File_Province_In >> Pro->ID;
	File_Province_In.ignore();
	getline(File_Province_In, Pro->Name, ',');
	File_Province_In >> Pro->Area;
	File_Province_In.seekg(1, 1);
	File_Province_In >> Pro->Population;
	return Pro;
}
Province* Input_One_Province( Province*& Pro)
{
	cout << "nhap ID tinh: ";
	cin >> Pro->ID;
	cout << "nhap ten tinh: ";
	cin.ignore();
	getline(cin, Pro->Name);
	cout << "nhap dien tich: ";
	cin >> Pro->Area;
	cout << "nhap so dan: ";
	cin >> Pro->Population;
	return Pro;

}
struct node
{
	Province data;
	node* next;
};
node* MakeNode(Province Pro)
{
	node* newnode = new node();
	newnode->data = Pro;
	newnode->next = NULL;
	return newnode;
}
void Push_Front(node*& head, Province Pro)
{
	node* newnode = MakeNode(Pro);
	newnode->next = head;
	head = newnode;
}
void Push_Back(node*& head, Province Pro)
{
	node* newnode = MakeNode(Pro);
	node* temp = head;
	if (head == NULL)
	{
		head = newnode;
		return;
	}
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newnode;
}
void Read_List_Province(node*& head, Province*& Pro)
{
	ifstream File_Province_In;
	File_Province_In.open("Province.txt", ios_base::in);
	if (!File_Province_In.is_open())
	{
		cerr << "Fail to open file province.txt" << endl;
		return;
	}
	while (!File_Province_In.eof())
	{
		Pro = new Province();
		Pro = Read_One_Province(File_Province_In, Pro);
		Push_Back(head, *Pro);
	}
	File_Province_In.close();
}
void duyet(node* head)
{
	while (head != NULL)
	{
		cout << head->data.ID << ", " << head->data.Name << ", " << head->data.Area << ", " << head->data.Population << endl;
		head = head->next;
	}
}
int count(node* head)
{
	int cnt = 0;
	while (head != NULL)
	{
		cnt++;
		head = head->next;
	}
	return cnt;
}
void Insert(node*& head, int x, Province*& Pro)
{
	Pro = Input_One_Province(Pro);
	int n = sizeof(head);
	if (x < 1 || x> n + 1)return;
	if (x == 1)
	{
		Push_Front(head, *Pro);
	}
	else
	{
		node* temp = head;
		for (int i = 1; i < x - 1; i++)
		{
			temp = temp->next;
		}
		node* newnode = MakeNode(*Pro);
		newnode->next = temp->next;
		temp->next = newnode;
	}
}
void Edit_ID(node*& head)
{
	int x;
	cout << "Nhap ma ban muon sua: ";
	cin >> x;
	int tmp;
	for (node* temp = head; temp != NULL; temp = temp->next)
	{
		if (temp->data.ID == x)
		{
			int index;
			cout << "nhap ma sau khi sua: ";
			cin >> index;
			tmp = index;
			temp->data.ID = index;
		}
		
	}
}
void Edit_Name(node*& head)
{
	string name;
	cout << "nhap ten tinh ban muon sua: ";
	cin.ignore();
	getline(cin, name);
	for (node* temp = head; temp != NULL; temp = temp->next)
	{
		if (temp->data.Name == name)
		{
			string NewName;
			cout << "Nhap ten moi: ";
			getline(cin, NewName);
			temp->data.Name = NewName;
		}
	}
}
void Edit_Area(node*& head)
{
	string name;
	cout << "nhap ten tinh ban muon sua dien tich: ";
	cin.ignore();
	getline(cin, name);
	for (node* temp = head; temp != NULL; temp = temp->next)
	{
		if (temp->data.Name == name)
		{
			double NewArea;
			cout << "nhap dien tich moi cua tinh: ";
			cin >> NewArea;
			temp->data.Area = NewArea;
		}
	}
}
void Edit_Population(node*& head)
{
	string name;
	cout << "nhap ten tinh ban muon sua dan so: ";
	cin.ignore();
	getline(cin, name);
	for (node* temp = head; temp != NULL; temp = temp->next)
	{
		if (temp->data.Name == name)
		{
			long long NewPopulation;
			cout << "Nhap dan so moi cua tinh: ";
			cin >> NewPopulation;
			temp->data.Population = NewPopulation;
		}
	}
}
void Edit(node*& head)
{
	while (true)
	{
		cout << "\t\t\t===================================================" << endl;
		cout << "\t\t\t= 1. Sua ma tinh" << endl;
		cout << "\t\t\t= 2. Sua ten tinh" << endl;
		cout << "\t\t\t= 3. Sua dien tich" << endl;
		cout << "\t\t\t= 4. Sua dan so" << endl;
		cout << "\t\t\t===================================================" << endl;
		int choose;
		cout << "nhap lua chon cua ban: ";
		cin >> choose;
		if (choose == 1)
		{
			Edit_ID(head);
			cout << "Sua thanh cong " << endl;
		}
		else if (choose == 2)
		{
			Edit_Name(head);
			cout << "Sua thanh cong" << endl;
		}
		else if (choose == 3)
		{
			Edit_Area(head);
			cout << "Sua thanh cong" << endl;
		}
		else if (choose == 4)
		{
			Edit_Population(head);
			cout << "Sua thanh cong" << endl;
		}
		else
		{
			break;
		}
	}
}
void Pop_Front(node*& head)
{
	if (head == NULL)return;
	node* temp = head;
	head = head->next;
	delete(temp);
}
void Earse_code(node*& head, int index)
{
	int n = sizeof(head);
	if (index <1 || index >n + 1) return;
	if (index == 1)Pop_Front(head);
	else
	{
		node* temp = head;
		for (int i = 1; i <= index - 2; i++)
		{
			temp = temp->next;
		}
		node* kth = temp->next;
		temp->next = kth->next;
		delete(kth);
	}
}
int Sum_Area(node* head)
{
	long long sum = 0;
	while (head != NULL)
	{
		sum += head->data.Area;
		head = head->next;
	}
	return sum;
}
void Search_max_node(node* head)
{
	double max = head->data.Area;
	for (node* temp = head; temp != NULL; temp = temp->next)
	{
		if (temp->data.Area > max)
		{
			max = temp->data.Area;
		}
	}
	for (node* temp = head; temp != NULL; temp = temp->next)
	{
		if (temp->data.Area == max)
		{
			cout << "dia chi cua node co dien tich lon nhat la: " << & temp->data.Area << endl;
		}
	}
}
long long Search_Province_max_popolation(node* head)
{
	long long max = head->data.Population;
	for (node* temp = head; temp != NULL; temp = temp->next)
	{
		if (temp->data.Population > max)
		{
			max = temp->data.Population;
		}
	}
	return max;	
}
node* Last_node(node* head)
{
	node* temp = head;
	while (temp!=NULL && temp->next != NULL)
	{
		temp = temp->next;
	}
	return temp;

}
void swap(Province*& a, Province*& b)
{
	Province* temp = a;
	a = b;
	b = temp;
}
node* Partition_ID(node*& First, node*& Last)
{
	node* Pivot = First;
	node* Front = First;
	while (Front != NULL && Front != Last)
	{
		if (Front->data.ID < Last->data.ID)
		{
			Pivot = First;
			swap(First->data, Front->data);
			First = First->next;
		}
		Front = Front->next;
	}
	if (First != NULL && Front != NULL)
	{
		swap(First->data, Front->data);
	}
	return Pivot;
}

void Quick_Sort_ID(node* First, node* Last)
{
	if (First == Last)
	{
		return;
	}
	node* Pivot = Partition_ID(First, Last);
	if (Pivot != NULL && Pivot->next != NULL)
	{
		Quick_Sort_ID(Pivot->next, Last);
	}
	if (Pivot != NULL && First != Pivot)
	{
		Quick_Sort_ID(First, Pivot);
	}
}
node* Partition_Area(node*& First, node*& Last)
{
	node* Pivot = First;
	node* Front = First;
	while (Front != NULL && Front != Last)
	{
		if (Front->data.Area < Last->data.Area)
		{
			Pivot = First;
			swap(First->data, Front->data);
			First = First->next;
		}
		Front = Front->next;
	}
	if (First != NULL && Front != NULL)
	{
		swap(First->data, Front->data);
	}
	return Pivot;
}
void Quick_Sort_Area(node* First, node* Last)
{
	if (First == Last)
	{
		return;
	}
	node* Pivot = Partition_Area(First, Last);
	if (Pivot != NULL && Pivot->next != NULL)
	{
		Quick_Sort_ID(Pivot->next, Last);
	}
	if (Pivot != NULL && First != Pivot)
	{
		Quick_Sort_ID(First, Pivot);
	}
}
void Menu()
{
	node* head = NULL;

	while (true)
	{
		cout << "\t\t\t===================================================" << endl;
		cout << "\t\t\t= 1. Them 1 tinh vao dau danh sach lien ket" << endl;
		cout << "\t\t\t= 2. Them 1 tinh vao cuoi danh sach lien ket" << endl;
		cout << "\t\t\t= 3. Doc du lieu tinh tu file" << endl;
		cout << "\t\t\t= 4. Them 1 tinh vao vi tri bat ky" << endl;
		cout << "\t\t\t= 5. Sua Thong tin tinh" << endl;
		cout << "\t\t\t= 6. Xoa tinh o vi tri bat ky: " << endl;
		cout << "\t\t\t= 7. Tinh tong dien tich cac tinh thanh" << endl;
		cout << "\t\t\t= 8. Dia chi node co dien tich lon nhat" << endl;
		cout << "\t\t\t= 9. Tinh co dan so lon nhat" << endl;
		cout << "\t\t\t= 10. Sap xep tang dan theo ma tinh" << endl;
		cout << "\t\t\t= 11. Sap xep tang danh theo dien tich" << endl;
		cout << "\t\t\t= 12. Duyet" << endl;
		cout << "\t\t\t= 0. Thoat" << endl;
		cout << "\t\t\t===================================================" << endl;
		int luachon;
		cout << "nhap lua chon cua ban: ";
		cin >> luachon;
		if (luachon == 1)
		{
			Province* Pro = new Province();
			Pro = Input_One_Province(Pro);
			Push_Front(head, *Pro);
			cout << "Them thanh cong" << endl;
			system("pause");
			system("cls");
		}
		else if (luachon == 2)
		{
			Province* Pro = new Province();
			Pro = Input_One_Province(Pro);
			Push_Back(head, *Pro);
			cout << "Them thanh cong " << endl;
			system("pause");
			system("cls");
		}
		else if (luachon == 3)
		{
			Province* Pro = new Province();
			Read_List_Province(head, Pro);
			cout << "Doc thanh cong" << endl;
			system("pause");
			system("cls");
		}
		else if (luachon == 4)
		{

			int x;
			cout << "nhap vi tri muon them: ";
			cin >> x;
			Province* Pro = new Province();
			Insert(head, x, Pro);
		}
		else if (luachon == 5)
		{
			Edit(head);
			system("cls");
		}
		else if (luachon == 6)
		{
			int index;
			cout << "nhap vi tri ban muon xoa: ";
			cin >> index;
			Earse_code(head, index);
			cout << "Xoa thanh cong" << endl;

		}
		else if (luachon == 7)
		{
			cout << "Tong dien tich nuoc Viet Nam la: " << Sum_Area(head) << endl;
			system("pause");
			system("cls");
		}
		else if (luachon == 8)
		{
			Search_max_node(head);
		}
		else if (luachon == 9)
		{
			cout << "Tinh co dan so lon nhat la: " << Search_Province_max_popolation(head) << endl;
			system("pause");
			system("cls");
		}
		else if (luachon == 10)
		{
			Quick_Sort_ID(head, Last_node(head));
			cout << "Sap xep thanh cong" << endl;
			system("pause");
			system("cls");
		}
		else if (luachon == 11)
		{
			Quick_Sort_Area(head, Last_node(head));
			cout << "Sap xep thanh cong" << endl;
			system("pause");
			system("cls");
		}
		else if (luachon == 12)
		{
			duyet(head);
			system("pause");
			system("cls");
		}
		
		else
		{
			break;
		}
	}
}
int main()
{
	Menu();
	return 0;
}