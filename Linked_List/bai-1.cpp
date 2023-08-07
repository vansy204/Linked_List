/*
Trong bài tập này chúng ta sẽ thực hiện giải một bài toán như sau:
s(x,n) = x1 + x2 + x3 + ... + xn
Xây dựng danh sách liên kết đơn có pHead, pTail. 
Nhập x, n tạo thành danh sách liên kết( Mỗi nút có 2 giá trị x và i, i chạy từ 1 -> n),
dùng con trỏ để khai báo cho danh sách liên kết.Viết hàm xuất ra tổng các phần tử trong danh sách liên kết.
*/

#include <iostream>
#include <math.h>
using namespace std;
struct DuLieu
{
	int x;
	int i;
};
struct node
{
	DuLieu data;
	node* next;
};
node* MakeNode(DuLieu dl)
{
	node* newnode = new node();
	newnode->data = dl;
	newnode->next = NULL;
	return newnode;
}
void Push_Front(node*& head, DuLieu dl)
{
	node* newnode = MakeNode(dl);
	newnode->next= head;
	head = newnode;
}
void duyet(node* head)
{
	while (head != NULL)
	{
		cout << head->data.x << ", " << head->data.i << endl;
		head = head->next;
	}
}
int Tinh_S(node* head)
{
	int sum = 0;
	while (head != NULL)
	{
		sum += pow(head->data.x, head->data.i);
		head = head->next;
	}
	return sum;
}
int main()
{
	node* head = NULL;
	DuLieu dl;
	int n;
	cout << "nhap x = ";
	cin >> dl.x;
	cout << "nhap n= ";
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		dl.i = i;
		Push_Front(head, dl);
	}
	duyet(head);
	cout << "tong s= " << Tinh_S(head);

	return 0;
}