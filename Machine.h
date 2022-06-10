#pragma once
#include "BST.h"
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////file path and singli linked list class/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
class FilePath
{
public:
	string FP;
	FilePath* next;

	FilePath()
	{
		next = NULL;
	}
	FilePath(string fp)
	{
		FP = fp;
		next = NULL;
	}
};

template<typename T1>
class SingleList
{
public:
	T1* head;
	int size;

	SingleList()
	{
		size = 0;
		head = NULL;
	}

	void add(string fp)
	{
		size++;
		if (head == NULL)
		{
			head = new T1(fp);
		}
		else
		{
			T1* temp1 = head;
			while (temp1->next != NULL)
			{
				temp1 = temp1->next;
			}
			temp1->next = new T1(fp);
			temp1 = temp1->next;
		}
	}
	void Delete(string fp)
	{
		T1* temp1 = head;
		T1* temp2 = head;
		if (head->FP == fp)
		{
			head = head->next;
			delete temp1;
		}
		else
		{
			while (temp1->FP != fp)
			{
				temp2 = temp1;
				temp1 = temp1->next;
			}
			temp2->next = temp1->next;
			delete temp1;
		}
		size--;
	}
	void Display()
	{
		T1* temp = head;
		cout << endl;
		if (size == 0)
		{
			cout << "Empty";
		}
		else
		{
			while (temp != NULL)
			{
				cout << temp->FP << " ";
				temp = temp->next;
			}
		}
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////machine and circular linked list class//////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
class machine
{
public:
	int id;
	SingleList<FilePath> file;
	BSTree obj;
	machine* next;
	fstream fout;

	machine(int i)
	{
		id = i;
	}
	machine()
	{
		next = NULL;
	}
	void add(string KEY, int ID, string value)
	{
		FilePath* ptr = file.head;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		obj.add(KEY, ID, ptr->FP);	//giving values to nodes

		fout.open(ptr->FP, ios::out | ios::app);	//writing value in file
		fout << value << endl;
		fout.close();
	}
	void display()
	{
		cout << id << endl;
	}

};
template<typename T>
class CircularList
{
public:
	T* head;
	int size;

	CircularList()
	{
		size = 0;
		head = NULL;
	}

	void add(int ID)
	{
		size++;
		if (head == NULL)
		{
			head = new T(ID);
			head->next = head;
		}
		else if(head->id>ID)
		{
			T* temporary=head;
			T* temp=head;
			while(temp->next!=head)
			{
				temp=temp->next;
			}
			head=new T(ID);
			head->next=temporary;
			temp->next=head;
		}
		else
		{
			T* temp1 = head;
			while (temp1->next != head)
			{
				temp1 = temp1->next;
			}
			if(temp1->id<ID)
			{
				temp1->next = new T(ID);
				temp1 = temp1->next;
				temp1->next = head;
			}
			else
			{
				temp1=head;
				while(temp1->id>ID || temp1->next->id<ID)
				{
					temp1=temp1->next;
				}
				T* temporary=temp1->next;
				temp1->next=new T(ID);
				temp1=temp1->next;
				temp1->next=temporary;
			}
		}
	}
	void Delete(int ID)
	{
		T* temp1 = head;
		T* temp2 = head;
		if (head->id == ID)
		{
			if (size == 1)
			{
				head = NULL;
				delete temp1;
			}
			else
			{
				temp1 = head->next;
				while (temp1->next != head)
				{
					temp1 = temp1->next;
				}
				head = head->next;
				temp1->next = head;
				delete temp2;
			}
		}
		else
		{
			temp1 = temp1->next;
			while (temp1->id != ID)
			{
				temp2 = temp1;
				temp1 = temp1->next;
			}
			temp2->next = temp1->next;
			delete temp1;
		}
		size--;
	}
	void Display()
	{
		T* temp = head;
		cout << endl;
		if (size == 0)
		{
			cout << "Empty";
		}
		else
		{
			while (temp->next != head)
			{
				cout << temp->id << " ";
				temp = temp->next;
			}
			cout << temp->id;
		}
	}
};
