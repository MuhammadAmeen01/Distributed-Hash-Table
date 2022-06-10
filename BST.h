#pragma once
#include <iostream>
#include<cmath>
#include <stdlib.h>
#include<time.h>
#include<string>
#include <fstream>
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////avl fuctionality,BSNode and BST class////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
class BSNode
{
public:

	string key;
	int id;
	int line;
	string FilePath;

	BSNode* right;
	BSNode* left;

	BSNode()
	{
		right = NULL;
		left = NULL;
	}
	BSNode(string KEY, int ID)
	{
		key = KEY;
		id = ID;
		FilePath = "";

		right = NULL;
		left = NULL;
	}
	BSNode(BSNode& obj)
	{
		key = obj.key;
		id = obj.id;
		line = obj.line;

		FilePath = obj.FilePath;

		right = NULL;
		left = NULL;
	}
};

class BSTree
{
public:
	int size;
	int line;
	int index;

	BSNode* head;

	BSTree()
	{
		size = 0;
		line = -1;
		index = -1;
		head = NULL;
	}
	void add(BSNode& obj)
	{
		BSNode* temp = head;
		BSNode* temp1 = temp;
		if (head == NULL)
		{
			head = new BSNode(obj);
		}
		else
		{
			while (temp != NULL)
			{
				temp1 = temp;
				if (temp->key < obj.key)
				{
					temp = temp->right;
				}
				else
				{
					temp = temp->left;
				}
			}
			if (temp1->key < obj.key)
			{
				temp1->right = new BSNode(obj);
			}
			else
			{
				temp1->left = new BSNode(obj);
			}
		}
	}
	void add(string KEY, int ID, string fp)
	{
		size++;
		line++;
		BSNode* temp = head;
		BSNode* temp1 = temp;
		if (head == NULL)
		{
			head = new BSNode(KEY, ID);
			head->line = line;
			head->FilePath = fp;
		}
		else
		{
			while (temp != NULL)
			{
				temp1 = temp;
				if (temp->key < KEY)
				{
					temp = temp->right;
				}
				else
				{
					temp = temp->left;
				}
			}
			if (temp1->key < KEY)
			{
				temp1->right = new BSNode(KEY, ID);
				temp1->line = line;
				temp1->FilePath = fp;
			}
			else
			{
				temp1->left = new BSNode(KEY, ID);
				temp1->line = line;
				temp1->FilePath = fp;
			}
		}
		AVL();
	}
	void AVL()
	{
		BSNode* ptr = new BSNode[size];
		BSNode* temp = head;
		index = -1;
		give(ptr, temp);

		for (int i = 0; i < size - 1; i++)
		{
			for (int j = 0; j < size - 1; j++)
			{
				if (ptr[j].key > ptr[j + 1].key)
				{
					BSNode temp1 = ptr[j];
					ptr[j] = ptr[j + 1];
					ptr[j + 1] = temp1;
				}
			}
		}
		/*		cout<<endl;
				for(int i=0;i<size;i++)
				{
					cout<<ptr[i].key<<" ";
				}*/

		index = -1;
		BSNode* temp3 = new BSNode[size];
		this->insert(temp3, ptr, size - 1);
		/*		cout<<endl;
				for(int i=0;i<size;i++)
				{
					cout<<temp3[i].key<<" ";
				}*/
		head = NULL;
		for (int i = 0; i < size; i++)
		{
			this->add(temp3[i]);
		}
	}
	void insert(BSNode* temp, BSNode* ptr, int TSize)
	{
		if (TSize == 2)
		{
			index++;
			temp[index] = ptr[1];
			index++;
			temp[index] = ptr[0];
			index++;
			temp[index] = ptr[2];
		}
		else if (TSize == 1)
		{
			index++;
			temp[index] = ptr[0];
			index++;
			temp[index] = ptr[1];
		}
		else if (TSize == 0)
		{
			index++;
			temp[index] = ptr[0];
		}
		else if (TSize > 2)
		{
			index++;
			int TempSize = TSize / 2;
			int TempSize2;
			if (TSize % 2 == 0)
			{
				TempSize2 = TempSize;
			}
			else
			{
				TempSize2 = TempSize + 1;
			}
			temp[index] = ptr[TempSize];
			BSNode* temp1 = new BSNode[TempSize];
			BSNode* temp2 = new BSNode[TempSize2];

			for (int i = 0; i < TempSize; i++)
			{
				temp1[i] = ptr[i];
			}

			for (int i = 0; i < TempSize2; i++)
			{
				temp2[i] = ptr[TempSize + 1 + i];
			}
			this->insert(temp, temp1, TempSize - 1);
			this->insert(temp, temp2, TempSize2 - 1);
		}
	}
	void give(BSNode* ptr, BSNode* temp)
	{
		if (temp == NULL)
		{

		}
		else
		{
			index++;
			ptr[index] = *temp;
			give(ptr, temp->left);
			give(ptr, temp->right);
		}
	}

	//-----------------------------------------------------
	void Delete(string KEY)
	{
		if (find(KEY))
		{
			int j = 0;
			BSNode* temp = head;
			BSNode* ptr = new BSNode[size];
			BSNode* ptr1 = new BSNode[size - 1];
			index=-1;
			give(ptr, temp);
			for (int i = 0; i < size; i++)
			{
				if (ptr[i].key != KEY)
				{
					ptr1[j] = ptr[i];
					ptr1[j].right = NULL;
					ptr1[j].left = NULL;
					j++;
				}
			}
			size--;
			head = NULL;
			for (int i = 0; i < size; i++)
			{
				this->add(ptr1[i]);
			}
			AVL();
		}
		else
		{
			cout << endl << "This Machine does not have this key";
		}
	}


	bool find(string KEY)
	{
		BSNode* temp = head;
		while (temp != NULL)
		{
			if (temp->key == KEY)
			{
				return 1;
			}
			else if (temp->key < KEY)
			{
				temp = temp->right;
			}
			else
			{
				temp = temp->left;
			}
		}
		return 0;
	}
	BSNode* FindAndReturn(string KEY)
	{
		BSNode* temp = head;
		while (temp != NULL)
		{
			if (temp->key == KEY)
			{
				return temp;
			}
			else if (temp->key < KEY)
			{
				temp = temp->right;
			}
			else
			{
				temp = temp->left;
			}
		}
		return temp;
	}
	void Display(BSNode* Head)
	{
		if (Head == NULL)
		{

		}
		else
		{
			cout << endl << Head->key << " " << Head->line << " " << Head->FilePath;
			this->Display(Head->left);
			this->Display(Head->right);
		}
	}
};
