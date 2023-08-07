/*
Nhập vào một số nguyên n, tiếp theo là n số nguyên của một dãy số.
Hãy cài đặt nó vào một danh sách liên kết đơn và in ra màn hình danh sách đó,
sau mỗt phần tử có đúng một khoảng trắng.
*/
#include <iostream>
using namespace std;
struct node
{
	int data;
	node* next;
};
node* MakeNode(int x)
{
	node* newnode = new node();
	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}
void Push_Front(node*& head, int x)
{
	node* newnode = MakeNode(x);
	newnode->next = head;
	head = newnode;
}
void Push_Back(node*& head, int x)
{
	node* newnode = MakeNode(x);
	if (head == NULL)
	{
		head = newnode;
		return;
	}
	node* temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = newnode;
}
void duyet(node* head)
{
	while (head != NULL)
	{
		cout << head->data << " ";
		head = head->next;
	}
}
int main()
{
	node* head = NULL;
	while (true)
	{
		cout << "1.Them vao dau" << endl;
		cout << "2.Them vao cuoi" << endl;
		cout << "3.duyet" << endl;
		cout << "----------------------------" << endl;
		int lc;
		cout << "nhap lua chon cua ban: ";
		cin >> lc;
		if (lc == 1)
		{
			int n;
			cout << "nhap n= ";
			cin >> n;
			for (int i = 1; i <= n; i++)
			{
				int x;
				cout << "nhap x= ";
				cin >> x;
				Push_Front(head, x);
			}
			cout << endl;
		}
		else if (lc == 2)
		{
			int n;
			cout << "nhap n= ";
			cin >> n;
			for (int i = 1; i <= n; i++)
			{
				int x;
				cout << "nhap x= ";
				cin >> x;
				Push_Back(head, x);
			}
			cout << endl;
		}
		else if(lc == 3)
		{
			duyet(head);
			cout << endl;
		}
		else
		{
			break;
		}

	}
	return 0;
}