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
///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////project class///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
class project
{
public:
	int MachineNo;				//the number of machines the user choose
	int SpecifierNo;			//the number of bits user choose
	int totalNodes;				//total number of nodes made
	CircularList<machine> obj;			//an Circular list of machine,each node of this pointer is a machine and has a avl tree to it
	int* IDptr;					//an array of int,it has the id of all the machines
	int** routing_array;
	project()			//this constructor will make the whole skeleton
	{

		srand(time(NULL));
		////////////////////////////////////////////////
		////////////number of identifiers//////////////
		//////////////////////////////////////////////
		cout << "Specify number of identifiers(in bits):";
		cin >> SpecifierNo;
		totalNodes = pow(2, SpecifierNo);
		/////////////////////////////////////////////
		///////////number of machines///////////////
		///////////////////////////////////////////
		cout << "Specify number of machines:";
		cin >> MachineNo;
		while (MachineNo > totalNodes)
		{
			cout << "Number of machines is wrong,kindly input again:";
			cin >> MachineNo;
		}
		//////////////////////////////////////////
		////////giving machine id manually///////
		///////////////or random////////////////
		cout << "Press Y to manually assign ID to Machine:";
		char condition;
		cin >> condition;
		IDptr = new int[MachineNo];
		if (condition == 'Y')
		{
			for (int i = 0; i < MachineNo; i++)
			{
				cout << "Give ID to machine " << i + 1 << ":";
				cin >> IDptr[i];
				for (int j = 0; j < i; j++)
				{
					while (IDptr[j] == IDptr[i])
					{
						cout << endl << "This ID already exist,kindly choose another:";
						cin >> IDptr[i];
						j = 0;
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < MachineNo; i++)
			{
				IDptr[i] = rand() % totalNodes;
				for (int j = 0; j < i; j++)
				{
					while (IDptr[j] == IDptr[i])
					{
						IDptr[i] = rand() % totalNodes;
						j = 0;
					}
				}
			}
		}
		for (int i = 0; i < MachineNo; i++)
		{
			cout << IDptr[i] << " ";
		}
		////////////////////////////////////////////
		///////bubble sorting the machine key//////
		////////////////////////////////////////// 
		for (int i = 0; i < MachineNo - 1; i++)
		{
			for (int j = 0; j < MachineNo - 1; j++)
			{
				if (IDptr[j] > IDptr[j + 1])
				{
					int temp = IDptr[j];
					IDptr[j] = IDptr[j + 1];
					IDptr[j + 1] = temp;
				}
			}
		}
		//////////////////////////////////////////
		/////making machines and their avl///////
		////////////////////////////////////////
		for (int i = 0; i < MachineNo; i++)
		{
			obj.add(IDptr[i]);
		}
		//////////////////////////////////////////////////
		//making machines .txt files and assigning them//
		////////////////////////////////////////////////
		string c1 = "DataFile";
		string c2 = ".txt";
		string c3 = "_";
		machine* tempMach = obj.head;

		for (int i = 0; i < MachineNo; i++)
		{
			string c4 = to_string(tempMach->id);
			string c5 = to_string(tempMach->file.size + 1);

			string c6 = c1 + c4 + c3 + c5 + c2;
			tempMach->file.add(c6);
			tempMach = tempMach->next;
		}
		/////////////////////////////////////////////////
		//opening the files once(so,that they are made//
		///////////////////////////////////////////////
		for (int i = 0; i < MachineNo; i++)
		{
			fstream fout;
			tempMach = obj.head;
			c1 = tempMach->file.head->FP;
			fout.open(c1.c_str());
			fout << "";
			fout.close();

			tempMach = tempMach->next;
		}
	}
	///////////////////////////////////////////////////////
	///////will check if machine responsible or not///////
	/////////////////////////////////////////////////////
	string filepath;
	machine* responsible(int id, machine* ptr)
	{
		int tempID = IDptr[0];

		for (int i = 0; i < MachineNo - 1; i++)
		{
			if (id > IDptr[i] && id <= IDptr[i + 1])
			{

				tempID = IDptr[i + 1];



			}
		}


		while (ptr->id != tempID)
		{
			ptr = ptr->next;

		}
		filepath = "Machine" + to_string(ptr->id) + ".txt";
		//cout << "Machine "<<ptr->id<<" is responsible for id "<<id<<endl;
		return ptr;

	}
	/////////////////////////////////////////////////////////////
	////////////////////hash function///////////////////////////
	///////////////////////////////////////////////////////////
	int hashFunction(string s)
	{
		hash<string>myhash;
		int key = myhash(s);

		string str = to_string(key);
		key = 0;
		for (int i = 0; i < str.size(); i++)
		{
			key = key + str[i];
		}
		key = key % totalNodes;
		return key;
	}
	//////////////////////////////////////////////////////////////
	//will check if the .txt file has gotten 100 entries or not//
	////////////////////////////////////////////////////////////
	void full(machine* ptr)
	{
		if (ptr->obj.line == 100)
		{
			string c1 = "DataFile";
			string c2 = to_string(ptr->id);
			string c3 = "_";
			string c4 = to_string(ptr->file.size + 1);
			string c5 = ".txt";
			string c6 = c1 + c2 + c3 + c4 + c5;
			ptr->file.add(c6);
			ptr->obj.line = -1;
		}
	}
	/////////////////////////////////////////////////////
	/////////////////will insert in machine/////////////
	///////////////////////////////////////////////////
	void insertion()
	{
		string c;
		cout << endl << "Enter from which file you want to extract the data:";
		cin >> c;

		fstream myfile;
		myfile.open(c.c_str(), ios::in);
		while (!myfile.eof())
		{
			string str1 = "";
			string str2 = "";
			string str3 = "";
			int index = 0;

			getline(myfile, str1);

			for (int i = 0; str1[i] != 32; i++)
			{
				str2 += str1[i];
				index = i;
			}
			index++;
			index++;
			for (int i = index; str1[i] != '\0'; i++)
			{
				str3 += str1[i];
			}

			int key = hashFunction(str2);

			machine* temp1 = obj.head;
			machine* temp = responsible(key, temp1);
			full(temp);
			temp->add(str2, key, str3);
		}
		myfile.close();
	}
	////////////////////////////////////////////////////
	//////////////////royting//////////////////////////
	//////////////////////////////////////////////////
		void routing() {				//Takes the current machine ID
		routing_array = new int *[MachineNo];
		for (int i = 0; i < MachineNo; i++)
		{
			routing_array[i] = new int[MachineNo];
		}
		for (int h = 0; h < MachineNo; h++) {
			int k = 1;
			for (int i = 0; i < MachineNo; i++) {

				routing_array[h][i] = IDptr[h] + (pow(2, k - 1));
				for (int m = 0; m < MachineNo; m++) {
					if (routing_array[h][i] <= IDptr[m]) {
						routing_array[h][i] = IDptr[m];
						break;
					}
					if (routing_array[h][i] > IDptr[MachineNo - 1]) {

						if (routing_array[h][i] > totalNodes - 1) {
							routing_array[h][i] = routing_array[h][i] - totalNodes;
							for (int l = 0; l < MachineNo; l++) {
								if (routing_array[h][i] <= IDptr[l]) {
									routing_array[h][i] = IDptr[l];
									//cout << routing_array[h][i] << endl;
									break;
								}
							}
						}
						else if (routing_array[h][i] <= totalNodes-1) {
							routing_array[h][i] = IDptr[0];
							//cout << routing_array[h][i] << endl;
							break;
						}

						break;
					}
				}
				k++;
			}
			/*for (int i = 0; i < MachineNo; i++)
			{
				for (int j = 0; j < MachineNo; j++)
				{
					cout << routing_array[i][j] << " ";
				}
				cout << endl;
			}*/
		}
		for (int i = 0; i < MachineNo; i++)
		{
			for (int j = 0; j < MachineNo; j++)
			{
				cout << routing_array[i][j] << " ";
			}
			cout << endl;
		}
	}
	////////////////////////////////////////
	////////////adding machines////////////
	//////////////////////////////////////
	void addMachine()
	{
		int tempMachineID;
		int* temparr;
		char condition;
		MachineNo++;
		temparr = new int[MachineNo];

		cout << "Enter Y to give the machine ID manually:";
		cin >> condition;
		if (condition == 'Y')
		{
			cout << endl << "Give ID to new machine :";
			cin >> tempMachineID;
			for (int j = 0; j < MachineNo - 1; j++)
			{
				while (IDptr[j] == tempMachineID)
				{
					cout << endl << "This ID already exist,kindly choose another:";
					cin >> tempMachineID;
					j = 0;
				}
			}
		}
		else
		{
			tempMachineID = rand() % totalNodes;
			for (int j = 0; j < MachineNo - 1; j++)
			{
				while (IDptr[j] == tempMachineID)
				{
					tempMachineID = rand() % totalNodes;
					j = 0;
				}
			}
		}
		///////////////////////////////////////////////
		////////////////correcting IDptr//////////////
		/////////////////////////////////////////////
		for(int i=0;i<MachineNo-1;i++)
		{
			temparr[i]=IDptr[i];
		}
		temparr[MachineNo-1]=tempMachineID;
		
		IDptr=new int[MachineNo];
		for(int i=0;i<MachineNo;i++)
		{
			IDptr[i]=temparr[i];
		}
		////////////////////////////////////////////
		///////bubble sorting the machine key//////
		////////////////////////////////////////// 
		for (int i = 0; i < MachineNo - 1; i++)
		{
			for (int j = 0; j < MachineNo - 1; j++)
			{
				if (IDptr[j] > IDptr[j + 1])
				{
					int temp = IDptr[j];
					IDptr[j] = IDptr[j + 1];
					IDptr[j + 1] = temp;
				}
			}
		}
		obj.add(tempMachineID);

	}
	////////////////////////////////////////////////
	////////////will delete machine////////////////
	//////////////////////////////////////////////
	void DelMachine()
	{
		cout<<endl<<"Insert ID of machine to be deleted:";
		int ID;
		cin>>ID;
		MachineNo--;
		int j=0;
		int* temparr=new int[MachineNo];
		for(int i=0;i<MachineNo+1;i++)
		{
			if(IDptr[i]!=ID)
			{
				temparr[j]=IDptr[i];
				j++;
			}
		}
		IDptr=new int[MachineNo];
		for(int i=0;i<MachineNo;i++)
		{
			IDptr[i]=temparr[i];
		}
		obj.Delete(ID);
	}
	///////////////////////////////////////////////////
	/////////////will delete from machine/////////////
	/////////////////////////////////////////////////
	void deletion(string key)
	{
		cout << "Yeh key hai " << key << endl;
		BSNode* D;
		machine* temp0 = obj.head;
		machine* temp1 = NULL;
		while (temp0->next != obj.head)
		{
			if (!temp0->obj.find(key))
			{
				cout << endl << "NOT Found in machine:" << temp0->id;
			}
			else
			{
				cout << endl << "Found in machine:" << temp0->id;
				temp1 = temp0;
			}
			temp0 = temp0->next;
		}
		if (!temp0->obj.find(key))
		{
			cout << endl << "NOT Found in machine:" << temp0->id;
		}
		else
		{
			cout << endl << "Found in machine:" << temp0->id;
			temp1 = temp0;
		}
		if (temp1 == NULL)
		{
			cout << endl << "Not found in any machine";
			return;
		}


		D = temp1->obj.FindAndReturn(key);
		cout <<endl<< "line number is=" << D->line;
		cout <<endl<< "line number is=" << D->FilePath;
		//-------------------------------------	------------------
		ifstream is(D->FilePath);

		// open file in write mode or out mode 
		ofstream ofs;
		ofs.open("temp.txt", ofstream::out);

		// loop getting single characters 
		char c;
		int line_no = 1;
		while (is.get(c))
		{
			// if a newline character 
			if (c == '\n')
				line_no++;

			// file content not to be deleted 
			if (line_no != D->line)
				ofs << c;
			else if (line_no == D->line) {
				ofs<<' ';
				if (c == '\n')
				ofs << '\n';

			}
		}

		// closing output file 
		ofs.close();

		// closing input file 
		is.close();

		// remove the original file 
		remove(D->FilePath.c_str());

		// rename the file 
		rename("temp.txt", D->FilePath.c_str());
		temp1->obj.Delete(key);		///YaHAN HAI ISSUE
//--------------------------------------------------------
	}
	void DisplayMachine()
	{
		cout << endl << "Machines are:";
		obj.Display();
	}
	void Display()
	{
		machine* ptr = obj.head;
		for (int i = 0; i < MachineNo; i++)
		{
			cout << endl;
			cout << "AVL of Machine " << i + 1 << " having id " << IDptr[i] << ":" << endl;
			ptr->obj.Display(ptr->obj.head);
			ptr = ptr->next;
		}
	}
	void menu()
	{
		char condition = '\0';
		string k = "";
		cout << endl << "Welcome to the system menu";
		while (condition != 'E')
		{
			cout << endl << "To Display the IDs of machines Press(A)";
			cout << endl << "To Display the AVLs of machines Press(B)";
			cout << endl << "To add info in machine Press(C)";
			cout << endl << "To delete info from machine Press (D)";
			cout << endl << "To add a machine Press (F)";
			cout << endl << "To delete a machine Press (G)";
			cout << endl << "To exit the system Press (E)" << endl;

			cin >> condition;

			if (condition == 'A' || condition == 'a')
			{
				DisplayMachine();
			}
			else if (condition == 'B' || condition == 'b')
			{
				Display();
			}
			else if (condition == 'C' || condition == 'c')
			{
				insertion();
			}
			else if (condition == 'D' || condition == 'd')
			{
				cout << "Enter the key to be deleted" << endl;
				cin.ignore();
				getline(cin, k);
				deletion(k);
			}
			else if (condition == 'F' || condition == 'f')
			{
			//	routing();
				addMachine();
			}
			else if (condition == 'G' || condition == 'g')
			{
				DelMachine();
			}
			else if (condition == 'e' || condition == 'E') {
				exit(1);
			}
		}
	}


};
