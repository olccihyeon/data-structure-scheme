#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<cstdlib>

using namespace std;

int j5 = 1;
int* freelist = &j5;
int freelist1 = 1;
int count22 = 0;
int count7 = 0;
int count1105 = 0;
int count0209 = 0;

template<class T >
class Stack
{
public:
	Stack(int stackCapacity = 30);
	~Stack()
	{
		delete[] stack;
	}
	bool IsEmpty() const;
	T& Top() const;
	void Push(const T& item);
	void Pop();
	int gettopvalue();
	int get_stack(int i);
private:
	T* stack; // array for stack elements
	int top; // position of top element
	int capacity; // capacity of stack array
};

template <class T >
Stack<T>::Stack(int stackCapacity) :capacity(stackCapacity)
{
	if (capacity < 1)
	{
		throw "Stack capacity must be >0";
	}
	stack = new T[capacity];
	top = -1;
}

template<class T>
int Stack<T>::gettopvalue()
{
	return top;
}

template<class T>
int Stack<T>::get_stack(int i)
{
	return stack[i];
}

template<class T >
inline bool Stack<T>::IsEmpty() const
{
	return top == -1;
}

template<class T >
inline T& Stack<T>::Top() const
{
	if (IsEmpty())
		throw "Stack is empty";
	return stack[top];
}



template<class T >
void Stack<T>::Push(const T& x)
{// Add x to the stack.
	if (top == capacity - 1)
	{
		//ChangeSize1D(stack, capacity, 2 * capacity);
		T* stack1 = new T[capacity];
		stack1 = stack;
		stack = new T[2 * capacity];
		stack = stack1;
		capacity *= 2;
	}
	// add at stack top
	stack[++top] = x;
}

template<class T >
void Stack<T>::Pop()
{
	if (IsEmpty())
	{
		throw  "Stack is empty. Cannot delete.";
	}
	stack[top--], ~T(); // destructor for T
}
Stack<int> st;

template<>
class hash<string>
{
public:
	size_t operator()(const string theKey) const
	{// Convert theKey to a nonnegative integer.
		//unsigned long hashValue = 0;
		int hashValue = 0;
		int length = (int)theKey.length();
		for (int i = 0; i < length; i++)
		{
			hashValue += theKey.at(i) * theKey.at(i);
		}
		return size_t(hashValue);
	}
};

int hash_f(int input)
{
	return (input % 1031);
}

class hash_table
{
public:
	int hashValue;
	int link_of_value;
	string Symbol;
	hash_table()
	{
		hashValue = NULL;
		Symbol = "";
		link_of_value = NULL;

	}

	void Set_hash(int myhashValue, string mySymbol)
	{
		Symbol = mySymbol;
		hashValue = myhashValue;
	}
	void Set_hash2(int mylink_of_value)
	{
		link_of_value = mylink_of_value;
	}
	void show_hash()const
	{

		cout << hashValue << "    " << Symbol << "    " << link_of_value << endl;

	}
	void print_hash()
	{
		cout << Symbol << " ";
	}
	string getsymbol()
	{
		return Symbol;
	}
};


class Memory
{
public:
	int lchild;
	int rchild;
	//int node;
	bool flag;
	Memory()
	{
		lchild = NULL;
		rchild = NULL;
		flag = false;
	}
	void Set_Memory(int myleft, int myright, int mynode, bool myflag)
	{
		lchild = myleft;
		rchild = myright;
		//node = mynode;
		//flag = myflag;
	}
	void init_Memory(int myright)
	{
		rchild = myright;
	}
	void Show_Memory()const
	{

		cout /*<< node*/ << "    " << lchild << "    " << rchild << "   "<<flag<<  endl;

	}

};


int GetHashValue(string str, hash_table arr[])
{
	int i = 0;
	while (i <= 1030)
	{
		if (str == arr[i].Symbol)
		{
			return arr[i].hashValue;
		}
		i++;
	}
	return 0;
}
string Delete(string str1, string str2)
{
	int i = 0;
	int count = 0;
	while (i < str1.length())
	{
		if (str1[i] == str2[0])
		{
			for (int j = 0; j < str2.length(); j++)
			{

				if (str1[i + j] == str2[j])
				{
					count++;
				}
				if (count == str2.length())
				{
					str1.erase(0, i + str2.length());
					int i = 0;
					while (str1[i] == ' ')
					{
						str1.erase(0, 1);

					}

					return str1;
				}
			}
		}
		i++;
	}

}


string Preprocessing(string* command)
{
	string newcommand;
	string str2;
	stringstream ss(*command);
	string* ptr = &str2;
	while (ss >> str2)
	{
		*ptr = str2;
		if (str2 == "define")
		{
			newcommand = newcommand + " " + str2;
			ss >> str2;

			if (str2 == "(")
			{
				ss >> str2;
				*ptr = str2;
				int m = str2.length();
				*command = (*command).substr((*command).find(*ptr) + m);
				newcommand = newcommand + " " + *ptr + " " + "( lambda (" + " " + Preprocessing(command) + " " + ")";
				break;
			}
			else
				newcommand = newcommand + " " + str2;

		}
		else if (str2 == "'")
		{
			newcommand = newcommand + " " + "( quote ";
			int number_of_left_paren = 0;
			do
			{
				ss >> str2;
				*ptr = str2;
				newcommand = newcommand + " " + str2;
				if (str2 == "(")
					number_of_left_paren = number_of_left_paren + 1;
				else if (str2 == ")")
					number_of_left_paren = number_of_left_paren - 1;
			} while (number_of_left_paren > 0);
			newcommand = newcommand + " " + ")";
		}
		else
			newcommand = newcommand + " " + str2;
	}
	return newcommand;
}

void set_true(int *root, Memory arr1[])
{
	//int i = *freelist;
	int j = *root;
		//if(arr[-arr1[j].lchild].link_of_value)
	
		if (arr1[j].lchild<=0&&arr1[j].rchild<=0)
		{
			arr1[j].flag = true;
			if (j == 30)
			{
				arr1[*root].rchild = -1;
			}
			
		}
		else if (arr1[j].lchild > 0)
		{
			arr1[j].flag = true;
			int* set1 = &(arr1[j].lchild);
			set_true(set1,  arr1);
		}
		if (arr1[j].rchild > 0)
		{
			arr1[j].flag = true;
		
			int* k2 = &(arr1[j].rchild);
			set_true(k2,arr1);
		}

	
}

void returnlist1(int* freelist, Memory arr[], int* listroot);
void garbage_collection(int freelist1, hash_table arr[], Memory arr1[])
{
	int ig = 0;

	int countg= 0;
	int kg = 1;
	int* k1g = &kg;
	int* k2g = &freelist1;
	for (int i = 0; i <= st.gettopvalue(); i++)
	{
		if (st.get_stack(i) >= 0)
		{
			arr1[st.get_stack(i)].flag = true;
		}
	}
	while (ig < 31)
	{
		
		if (arr1[ig].lchild == GetHashValue("define", arr))
		{
			if (arr[-arr1[arr1[ig].rchild].lchild].link_of_value > 0)
			{
				int* root5 = &arr[-arr1[arr1[ig].rchild].lchild].link_of_value;
				set_true(root5, arr1);
			}
			else
			{
				int* root6 = &arr1[ig].rchild;
				set_true(root6, arr1);
			}
		}
			ig++;
	}
	returnlist1(k2g, arr1, k1g);

}

int Read(string* str5, int* freelist, hash_table arr[], Memory arr1[],int freelist1,string* str6)
{
	//stringstream ss1(str3.substr(*str3.find(')') + 1));
	string str2;
	int readcount = 0;
	int readcount1;
	int temp;
	int token_hash_value;
	int Memory_root = NULL;
	int u=NULL;
	bool first = true;
	stringstream ss(*str5);
	ss >> str2;
	*str5 = Delete(*str5, str2);
	token_hash_value = GetHashValue(str2, arr);
	if (str2 == "(")
	{	// iterate until ‘)’ appears
		stringstream ss(*str5);
		ss >> str2;
		if (str2 == "define")
		{
			count1105++;
		}
		if (str2 != "(" && str2 != ")")
		{
			*str5 = Delete(*str5, str2);
		}
	
		do
		{

			if (first == true)
			{
				temp = *freelist;
				

				if (*freelist == -1&&count7==0&&count22==0)
				{
					cout << "----- garbage collecting1 -----" << endl;
					count7++;
					count22++;
					
				}
			//	else
				//{
				*freelist = arr1[*freelist].rchild;
					Memory_root = temp;
					first = false;
				//}
			}
			else
			{
				arr1[temp].rchild = *freelist;
			
				if (*freelist == -1&&count7 == 0 && count22 == 0)
				{
					cout << "----- garbage collecting2 -----" << endl;
					count7++;
					count22++;
			
				}
				//else
				//{
				*freelist = arr1[*freelist].rchild;
					temp = arr1[temp].rchild;
				//}
			}// if the nested list appears, do recursion
			if (count22 == 0)
			{
				if (str2 == "(")
				{

					readcount++;
					*str5 = (*str5).substr((*str5).find("("));
					arr1[temp].lchild = Read(str5, freelist, arr, arr1, freelist1, str6);
		
				
				}
				else
				{
				
					
					if (str2 == ")")
					{
						arr1[temp].lchild = 0;
					}
					else
						arr1[temp].lchild = GetHashValue(str2, arr);

				}
				if (readcount == 1)
				{

					arr1[temp].rchild = NULL;
					stringstream ss(*str5);
					ss >> str2;
					if (str2 != "(")
					{
						*str5 = Delete(*str5, str2);
					}
				

				}
				else
				{
					arr1[temp].rchild = NULL;
					stringstream ss(*str5);
					ss >> str2;
					if (str2 != "(")
					{
						*str5 = Delete(*str5, str2);
					}
				
				

				}
			}
		} while (str2 != ")"&& count22 == 0);
	
		if (count22 == 1&&readcount==1)
		{
			int ig = 0;
			int countg = 0;
			int kg = 1;
			int* k1g = &kg;
			int* k2g = &freelist1;
			for (int i = 0; i <= st.gettopvalue(); i++)
			{
				if (st.get_stack(i) >= 0)
				{
					arr1[st.get_stack(i)].flag = true;
				}
			}
			while (ig < 31)
			{

				if (arr1[ig].lchild == GetHashValue("define", arr) && count1105 == 0)
				{
					if (arr[-arr1[arr1[ig].rchild].lchild].link_of_value > 0)
					{
						int* root5 = &arr[-arr1[arr1[ig].rchild].lchild].link_of_value;
						set_true(root5, arr1);
					}
					else
					{
						int* root6 = &arr1[ig].rchild;
						set_true(root6, arr1);
					}
				}
				ig++;
			}
			returnlist1(k2g, arr1, k1g);
		
			for (int i = 1; i <= 30; i++)
			{
				if (arr1[i].flag == false)
				{
					*freelist = i;
					break;
				}
			}	
		}
		else if (count22 == 1)
		{
			int ig = 0;
			int countg = 0;
			int kg = 1;
			int* k1g = &kg;
			int* k2g = &freelist1;
			for (int i = 0; i <= st.gettopvalue(); i++)
			{
				if (st.get_stack(i) >= 0)
				{
					arr1[st.get_stack(i)].flag = true;
				}
			}
			while (ig < 31)
			{

				if (arr1[ig].lchild == GetHashValue("define", arr)&&count1105==0)
				{
					if (arr[-arr1[arr1[ig].rchild].lchild].link_of_value > 0)
					{
						int* root5 = &arr[-arr1[arr1[ig].rchild].lchild].link_of_value;
						set_true(root5, arr1);
					}
					else
					{
						int* root6 = &arr1[ig].rchild;
						set_true(root6, arr1);
					}
				}
				ig++;
			}
			returnlist1(k2g, arr1, k1g);
	
			for (int i = 1; i <= 30; i++)
			{
				if (arr1[i].flag == false)
				{
					*freelist = i;
					break;
				}
			}



		}
		if (count1105 == 1)
		{
			count1105--;
		}
		return Memory_root;
	}
	else
	{
		token_hash_value = GetHashValue(str2, arr);
		return token_hash_value;
	}

}
float GetVal(int hashvalue, hash_table arr[])
{
	int i = 0;
	if (hashvalue == 0)
	{
		return 1;
	}
	string str1;
	while (i <= 1030)
	{
		if (hashvalue == arr[i].hashValue)
		{
			if (arr[i].link_of_value != 0)
			{
				str1 = arr[-arr[i].link_of_value].Symbol;
				break;
			}
			str1 = arr[i].Symbol;
			break;
		}
		i++;
	}
	stringstream ss(str1);

	float f;
	ss >> f;
	return f;

}
//refer slide <stack> 슬라이드 참조


int countequal = 0;

int Eval(int root, Memory arr1[], hash_table arr[], int* freelist)
{

	int token_index = arr1[root].lchild;
	if (root < 0)
	{
		if (arr[-root].link_of_value != 0 && countequal == 0)
		{
			return arr[-root].link_of_value;
		}
		else
			return root;
	}
	else if (token_index > 0)
	{
		//return root;
		return Eval(token_index, arr1, arr, freelist);
	}
	else
	{

		int find1 = arr[-token_index].link_of_value; // 사용자 정의 함수 찾을때 사용
		if (token_index == GetHashValue("define", arr))
		{
			if (arr1[arr1[arr1[arr1[root].rchild].rchild].lchild].lchild == GetHashValue("lambda", arr))
			{
				arr[-arr1[arr1[root].rchild].lchild].link_of_value = arr1[arr1[arr1[root].rchild].rchild].lchild;
				return GetHashValue(" ", arr);
			}
			else
			{
				int i2 = arr1[arr1[root].rchild].lchild;
				arr[-i2].link_of_value = Eval(arr1[arr1[arr1[root].rchild].rchild].lchild, arr1, arr, freelist);
				return GetHashValue(" ", arr);
			}
		}

		else if (token_index == GetHashValue("+", arr))
		{
			int i = arr1[arr1[root].rchild].lchild;
			int j = arr1[arr1[arr1[root].rchild].rchild].lchild;
			float ans = GetVal(Eval(i, arr1, arr, freelist), arr) + GetVal(Eval(j, arr1, arr, freelist), arr);
			stringstream ss;
			ss << ans;
			string strchange = ss.str();
			hash<string> b;
			int input = b(strchange);
			int h = hash_f(input);
			if (arr[h].hashValue == NULL)
			{
				arr[h].Set_hash(-h, strchange);
			}
			else
			{
				while (1)
				{
					if (arr[h].Symbol == strchange)
					{
						break;
					}
					j++;
					if (arr[h].hashValue != NULL)
					{
						if (arr[h + j].Symbol == strchange)
						{
							break;
						}
						else
							arr[h + j].Set_hash(-(h + j), strchange);
						break;
					}
				}
			}
	
			return GetHashValue(strchange, arr);
		}
		else if (token_index == GetHashValue("-", arr))
		{
			int i = arr1[arr1[root].rchild].lchild;
			int j = arr1[arr1[arr1[root].rchild].rchild].lchild;
			float ans = GetVal(Eval(i, arr1, arr, freelist), arr) - GetVal(Eval(j, arr1, arr, freelist), arr);
			stringstream ss;
			ss << ans;
			string strchange = ss.str();
			hash<string> b;
			int input = b(strchange);
			int h = hash_f(input);
			if (arr[h].hashValue == NULL)
			{
				arr[h].Set_hash(-h, strchange);
			}
			else
			{
				while (1)
				{
					if (arr[h].Symbol == strchange)
					{
						break;
					}
					j++;
					if (arr[h].hashValue != NULL)
					{
						if (arr[h + j].Symbol == strchange)
						{
							break;
						}
						else
							arr[h + j].Set_hash(-(h + j), strchange);
						break;
					}
				}
			}
			return GetHashValue(strchange, arr);
		}
		else if (token_index == GetHashValue("*", arr))
		{
			int i = arr1[arr1[root].rchild].lchild;
			int j = arr1[arr1[arr1[root].rchild].rchild].lchild;
			float ans = GetVal(Eval(i, arr1, arr, freelist), arr) * GetVal(Eval(j, arr1, arr, freelist), arr);
			stringstream ss;
			ss << ans;
			string strchange = ss.str();
			hash<string> b;
			int input = b(strchange);
			int h = hash_f(input);
			if (arr[h].hashValue == NULL)
			{
				arr[h].Set_hash(-h, strchange);
			}
			else
			{
				while (1)
				{
					if (arr[h].Symbol == strchange)
					{
						break;
					}
					j++;
					if (arr[h].hashValue != NULL)
					{
						if (arr[h + j].Symbol == strchange)
						{
							break;
						}
						else
							arr[h + j].Set_hash(-(h + j), strchange);
						break;
					}
				}
			}
			return GetHashValue(strchange, arr);
		}
		else if (token_index == GetHashValue("eq?", arr))
		{
		if (Eval(arr1[arr1[root].rchild].lchild, arr1, arr, freelist)
			== Eval(arr1[arr1[arr1[root].rchild].rchild].lchild, arr1, arr, freelist))
		{
			return GetHashValue("#t", arr);
		}
		else
			return GetHashValue("#f", arr);
		}
		else if (token_index == GetHashValue("equal?", arr))
		{
		countequal++;
		if (Eval(arr1[arr1[root].rchild].lchild, arr1, arr, freelist) ==
			Eval(arr1[arr1[arr1[root].rchild].rchild].lchild, arr1, arr, freelist))
		{
			countequal--;
			return GetHashValue("#t", arr);
		}
		else
		{
			countequal--;
			return GetHashValue("#f", arr);
		}
		}
		else if (token_index == GetHashValue("number?", arr))
		{
			string s1 = arr[-Eval(arr1[arr1[root].rchild].lchild, arr1, arr, freelist)].getsymbol();

			if (s1.compare("0") == 0)
			{
				return GetHashValue("#t", arr);
			}

			else if (atof(s1.c_str()) == 0)
			{
				return GetHashValue("#f", arr);
			}
			else return GetHashValue("#t", arr);
		}
		else if (token_index == GetHashValue("symbol?", arr))
		{
			string s2 = arr[-Eval(arr1[arr1[root].rchild].lchild, arr1, arr, freelist)].getsymbol();
			if (s2.compare("0") == 0)
			{
				return GetHashValue("#f", arr);
			}
			else if (Eval(arr1[arr1[root].rchild].lchild, arr1, arr, freelist) != NULL && atoi(s2.c_str()) == 0 && atof(s2.c_str()) == 0)
			{
				return GetHashValue("#t", arr);
			}
			else return GetHashValue("#f", arr);
		}
		else if (token_index == GetHashValue("null?", arr))
		{

			if (arr1[arr1[root].rchild].lchild < 0 && arr[-arr1[arr1[root].rchild].lchild].link_of_value > 0)
			{
				int k = -1;
				for (int i = 0; i < 30; i++)
				{
					if (arr1[i].lchild == GetHashValue("quote", arr))
					{
						k = i;
					}
				}
				if (k != -1)
				{
					if (arr1[Eval(k, arr1, arr, freelist)].lchild == 0)
					{
						return GetHashValue("#t", arr);
					}
				}
				else
					return GetHashValue("#f", arr);
			}

			else if (arr1[root].rchild == NULL)
			{

				return GetHashValue("#t", arr);
			}
			else if (arr1[arr1[root].rchild].lchild == -242)
			{
				if (count0209 == 0)
				{
					return GetHashValue("#f", arr);
				}
				else 
					return GetHashValue("#t", arr);
			}
			else if (arr1[Eval(arr1[root].rchild, arr1, arr, freelist)].lchild == 0 ||
				Eval(arr1[root].rchild, arr1, arr, freelist) == 0)
			{
				return GetHashValue("#t", arr);
			}
			else
			{
				return GetHashValue("#f", arr);
			}
		}
		else if (token_index == GetHashValue("car", arr))
		{

			return arr1[Eval(arr1[arr1[root].rchild].lchild, arr1, arr, freelist)].lchild;


		}
		else if (token_index == GetHashValue("cdr", arr))
		{

			return arr1[Eval(arr1[arr1[root].rchild].lchild, arr1, arr, freelist)].rchild;


		}
		else if (token_index == GetHashValue("quote", arr))
		{
			return arr1[arr1[root].rchild].lchild;
		}
		else if (token_index == GetHashValue("cons", arr))
		{
			int newmemory = *freelist;
			*freelist = arr1[*freelist].rchild;
			if (*freelist == -1)
			{
				cout << "----- garbage collecting3 -----" << endl;
				int ig = 0;
				int countg = 0;
				int kg = 1;
				int* k1g = &kg;
				int* k2g = &freelist1;

				while (ig < 31)
				{

					if (arr1[ig].lchild == GetHashValue("define", arr) && count1105 == 0)
					{
						if (arr[-arr1[arr1[ig].rchild].lchild].link_of_value > 0)
						{
							int* root5 = &arr[-arr1[arr1[ig].rchild].lchild].link_of_value;
							set_true(root5, arr1);
						}
						else
						{
							int* root6 = &arr1[ig].rchild;
							set_true(root6, arr1);
						}
					}
					ig++;
				}
				returnlist1(k2g, arr1, k1g);
			  
				for (int i = 1; i <= 30; i++)
				{
					if (arr1[i].flag == false)
					{
						*freelist = i;
						break;
					}
				}
				return 1500;
			}
			
			arr1[newmemory].lchild = Eval(arr1[arr1[root].rchild].lchild, arr1, arr, freelist);
			arr1[newmemory].rchild = Eval(arr1[arr1[arr1[root].rchild].rchild].lchild, arr1, arr, freelist);
			return newmemory;
		}
		else if (token_index == GetHashValue("cond", arr))
		{

			while (arr1[arr1[root].rchild].rchild != 0)
			{
				root = arr1[root].rchild;
		
				if (Eval(arr1[arr1[root].lchild].lchild, arr1, arr, freelist) == GetHashValue("#t", arr))
				{
				
					return Eval(arr1[arr1[arr1[root].lchild].rchild].lchild, arr1, arr, freelist);
				
				}
			
			}
			if (arr1[arr1[arr1[root].rchild].lchild].lchild != GetHashValue("else", arr))
			{
				std::cout << "제대로 작동하지 않습니다." << endl;
				return -1;
			}
		
			return Eval(arr1[arr1[arr1[arr1[root].rchild].lchild].rchild].lchild, arr1, arr, freelist);
		}
		else if (arr1[find1].lchild == GetHashValue("lambda", arr))
		{

			int result;
			//int find1 = arr[-token_index].link_of_value;
			int newroot = arr1[arr1[find1].rchild].lchild;
			int remember = newroot;
			count0209++;
			int count = 0;
			st.Push(arr[-arr1[newroot].lchild].link_of_value);
			if (arr1[arr1[root].rchild].lchild > 0 || arr[-arr1[arr1[root].rchild].lchild].link_of_value != 0)
			{
				
				arr[-arr1[newroot].lchild].link_of_value = Eval(arr1[arr1[root].rchild].lchild, arr1, arr, freelist);
				//else
					//arr[-arr1[newroot].lchild].link_of_value = Eval(arr1[root].rchild, arr1, arr, freelist);
				if (Eval(arr1[arr1[root].rchild].lchild, arr1, arr, freelist) == NULL)
				{
					result = Eval(arr1[arr1[root].rchild].lchild, arr1, arr, freelist);
				}
				count++;
			}
			/*else if (arr[-arr1[arr1[root].rchild].lchild].link_of_value != 0)
			{

				arr[-arr1[newroot].lchild].link_of_value =
					arr[-arr1[arr1[root].rchild].lchild].link_of_value;
				count++;
			}*/
			else
			{
				
				arr[-arr1[newroot].lchild].link_of_value = arr1[arr1[root].rchild].lchild;
				count++;
			}
			if (arr1[newroot].rchild != 0)
			{
			
				while (arr1[newroot].rchild != 0)
				{

					newroot = arr1[newroot].rchild;
					root = arr1[root].rchild;
					st.Push(arr[-arr1[newroot].lchild].link_of_value);
					if (/*arr[-arr1[newroot].lchild].link_of_value != 0 */arr1[arr1[root].rchild].lchild > 0 || arr[-arr1[arr1[root].rchild].lchild].link_of_value != 0)
					{

						arr[-arr1[newroot].lchild].link_of_value =
							arr[-arr1[arr1[root].rchild].lchild].link_of_value;
						count++;
					}
					else
					{

						arr[-arr1[newroot].lchild].link_of_value = arr1[arr1[root].rchild].lchild;
						count++;

					}
				}
			}
			if (Eval(arr1[arr1[root].rchild].lchild, arr1, arr, freelist) != NULL)
			{
			
				result = Eval(arr1[arr1[arr1[find1].rchild].rchild].lchild, arr1, arr, freelist);
			}
			int i = 0;
	
			while (i < count)
			{
				arr[-arr1[newroot].lchild].link_of_value = st.Top();

				for (int i = find1 + 2; i < 31; i++)
				{
					if (newroot == arr1[i].rchild)
					{
						newroot = i;
						break;
					}
				}
				st.Pop();
				i++;
			}
	
			return result;
		}
		else
		{
			return root;
	
		}

	}

}


void PRINT(int root, bool startList, hash_table arr[], Memory arr1[])
{
	if (root == NULL)
		cout << "()" << endl;
	else if (root < 0)
	{
		if (arr[-root].link_of_value != 0)
		{
			if (arr[-root].link_of_value > 0)
			{
				PRINT(Eval(arr[-root].link_of_value, arr1, arr, freelist), true, arr, arr1);
			}
			else
				arr[-arr[-root].link_of_value].print_hash();
		}
		else
			arr[-root].print_hash();
	}
	else if (root > 0)
	{
		if (startList == true)
		{
			cout << "(" << " ";
		}
		if (arr1[root].lchild != 0)
		{
			PRINT(arr1[root].lchild, true, arr, arr1);
		}
		if (arr1[root].rchild != NULL)
		{
			PRINT(arr1[root].rchild, false, arr, arr1);
		}
		else cout << ")" << " ";
	}
}

void returnlist1(int* freelist2, Memory arr[], int* listroot)
{

	//int i = *freelist;
	int j = *listroot;
	while (j<=30)
	{
		if (j == 30 && arr[j].flag == false)
		{
			arr[j].lchild = 0;
			arr[j].rchild = -1;
			break;
		}
		else if (j == 30&&arr[j].flag == true)
		{
			break;
		}
		else if (arr[j].flag == true)
		{
			j++;
		}
		else
		{
			if (arr[j].rchild == -1)
			{
				break;
			}
			if (j == 30)
			{
				arr[j].lchild = 0;
				break;
			}

			if (arr[j].lchild > 0 && arr[j].rchild != 0)
			{
			
				int* k1 = &(arr[j].lchild);
				returnlist1(freelist2, arr, k1);
				arr[j].lchild = 0;
				break;
		
			}
			if (arr[j].lchild > 0 && arr[j].rchild == 0)
			{

				for (int i = j + 1; i <= 31; i++)
				{
					if (i == 31)
					{
						arr[j].rchild = -1;
						break;
					}
					if (arr[i].flag == false&&i!=31)
					{
						arr[j].rchild = i;
						break;
					}
					
				}

				arr[j].lchild = 0;
				int* k3 = &(arr[j].rchild);
				returnlist1(freelist2, arr, k3);
				break;

			}
			else if (arr[j].rchild > 0)
			{
				if (arr[j].lchild = -16)
				{
					for (int i = j + 1; i <= 31; i++)
					{
						if (i == 31)
						{
							arr[j].rchild = -1;
							break;
						}
						if (arr[i].flag == false)
						{
							arr[j].rchild = i;
							break;
						}
						
					}

					arr[j].lchild = 0;
					int* k3 = &(arr[j].rchild);
					returnlist1(freelist2, arr, k3);
					break;
				}
				else
				{
					arr[j].lchild = 0;
					int* k2 = &(arr[j].rchild);
					returnlist1(freelist2, arr, k2);
					break;
				}
			}
			else if (arr[j].rchild == 0)
			{
				int k = 0;
				for (int i = j + 1; i <= 31; i++)
				{
					if (i == 31)
					{
						arr[j].rchild = -1;
						break;
					}
					if (arr[i].flag == false && i != 31)
					{
						arr[j].rchild = i;
						break;
					}
					
				}

				arr[j].lchild = 0;
				int* k3 = &(arr[j].rchild);
				returnlist1(freelist2, arr, k3);
				break;
			}
		
		
		}
	}
}

void returnlist(int* freelist, Memory arr[], int* listroot)
{

	//int i = *freelist;
	int j = *listroot;
	while (1)
	{
		if (*freelist == 1)
		{
			break;
		}
		else if (arr[j].lchild > 0)
		{
			int* k1 = &(arr[j].lchild);
			returnlist(freelist, arr, k1);
		}
		if (arr[j].rchild == 0&&arr[j].flag==false)
		{
			arr[j].rchild = *freelist;
			*freelist = j;
			*listroot = 0;
			break;
		}
		else if (arr[j].rchild > 0)
		{
			int* k2 = &(arr[j].rchild);
			returnlist(freelist, arr, k2);
		}

	}
}



void printmemory(Memory arr[], int listroot)
{

	//int i = *freelist;
	int j = listroot;
	if (j < 0/*ㅓ<=0*/)
	{
		cout << "아무것도 할당되지 않음" << endl;
	}
	else
	{
		cout << j << " ";
		arr[j].Show_Memory();
		if (not(arr[j].lchild < 0 && arr[j].rchild == 0))
		{
			if (arr[j].lchild > 0)
			{
				printmemory(arr, arr[j].lchild);


			}
			if (arr[j].rchild > 0)
			{
				printmemory(arr, arr[j].rchild);
			}
		}



	}

}


int main(void)
{
	hash_table arr[1031];
	Memory arr1[31];
	for (int i3 = 0; i3 < 31; i3++)
	{
		if (i3 != 30)
		{
			/*arr1[i3].node = i3+1;
			arr1[i3].flag = false;*/
			arr1[i3].rchild = i3 + 1;
		}
		else
			/*arr1[i3].node = i3+1;
			arr1[i3].flag = false;*/
			arr1[i3].rchild = -1;
	}


	while (1)
	{
		cout << ">";
		hash<string> b;
		string b2;
		int result;
		int j6 = 0;
		int* s = &j6;
		getline(cin, b2);
		if (b2 == "")
		{
			result = 0;
			cout << "] ";
			PRINT(result, true, arr, arr1);
			cout << endl;
		}
		else
		{
			for (int i = 0; i < b2.length(); i++)
			{
				if (b2[i] == '(')
				{
					if (i != 0)
					{
						if (b2[i - 1] != ' ')
						{
							b2.insert(i - 1, " ");
						}
						if (b2[i + 1] != ' ')
							b2.insert(i + 1, " ");
					}
					else if (b2[i + 1] != ' ')
						b2.insert(i + 1, " ");
				}
				else if (b2[i] == ')')
				{
					if (b2[i + 1] == NULL)
					{
						if (b2[i - 1] != ' ')
						{
							b2.insert(i, " ");
							break;
						}
					}
					else
					{
						if (b2[i + 1] != ' ')
						{
							b2.insert(i + 1, " ");
						}
						if (b2[i - 1] != ' ')
						{
							b2.insert(i, " ");
						}
					}
				}
			}

			string b3 = b2;

			int m = b3.length();
			for (int i = 0; i < m; i++)
			{
				if (b3[i] >= 'A' && b3[i] <= 'Z')
				{
					b3[i] = tolower(b3[i]);
				}
			}
			string* command = &b3;
			string newcommand = Preprocessing(command);
			stringstream ss(newcommand);
			string str;
			arr[1].Set_hash(-1, "(");
			arr[2].Set_hash(-2, ")");
			arr[3].Set_hash(-3, "#t");
			arr[4].Set_hash(-4, "#f");
			arr[18].Set_hash(-18, "lambda");
			arr[17].Set_hash(-17, "quote");
			arr[16].Set_hash(-16, "define");
			arr[15].Set_hash(-15, "cdr");
			arr[14].Set_hash(-14, "car");
			arr[13].Set_hash(-13, "else");
			arr[12].Set_hash(-12, "cond");
			arr[11].Set_hash(-11, "cons");
			arr[10].Set_hash(-10, "null?");
			arr[9].Set_hash(-9, "symbol?");
			arr[8].Set_hash(-8, "number?");
			arr[7].Set_hash(-7, "*");
			arr[6].Set_hash(-6, "-");
			arr[5].Set_hash(-5, "+");

			while (ss >> str)
			{
				if (str != "(" &&str != ")" && str != "#t" && str != "f" && str != "+" && str != "-" && str != "*" && str != "number?" && str != "symbol?"
					&& str != "null?" && str != "cons" && str != "cond" && str != "else" && str != "car" && str != "cdr" && str != "define"
					&& str != "quote" && str != "lambda")
				{
				int m = str.length();
				if (m >= 11)
				{
					cout << "error";
					return 0;
				}

				int input = b(str);
				int h = hash_f(input);
			
					if (arr[h].hashValue == NULL)
					{
						arr[h].Set_hash(-h, str);
					}
					else
					{
						while (1)
						{
							int j = 0;
							if (arr[h].Symbol == str)
							{
								break;
							}
							j++;
							if (arr[h].hashValue != NULL)
							{
								if (arr[h + j].Symbol == str)
								{
									break;
								}
								else
									arr[h + j].Set_hash(-(h + j), str);
								break;
							}
						}
					}
				}

			}
			string* str3 = &newcommand;
			string x = *str3;
			string* str4 = &x;
		
			int r=0;

			r = Read(str3, freelist, arr, arr1,freelist1,str4);
		
			if (count7== 1&&r==freelist1)
			{
				
				count22--;
				count7--;
			
				r = Read(str4, freelist, arr, arr1, freelist1, str4);
			}

			cout << "] ";
			if (r != 0)
			{
				result = Eval(r, arr1, arr, freelist);
				if (result == 1500)
				{
					r = Read(str4, freelist, arr, arr1, freelist1, str4);
					result = Eval(r, arr1, arr, freelist);
				}
			}
	
			if (r==0)
			{
				PRINT(r, true, arr, arr1);
			}
			else
				PRINT(result, true, arr, arr1);
			cout << endl;

			cout << "]" << "Free list's root =" << *freelist << endl;
			freelist1 = *freelist;
			cout << "List's root =" << r << endl;
			cout << endl;
			cout << "Tree Array : " << endl;
			cout << "node, left child, right child, flag" << endl;

			//printmemory(arr1, r);
			int k1 = 1;
			while (k1 <= 30)
			{
				cout << k1 << "   ";
				arr1[k1].Show_Memory();
				k1++;
			}
			cout << endl;
			cout << "Hash Table" << endl;
			cout << "hash value, symbol, link" << endl;
			int i = 0;
			while (i <= 1030)
			{
				if (arr[i].Symbol != "")
				{
					arr[i].show_hash();
				}

				i++;
			}



				//int* listroot = &r;

				//returnlist(freelist, arr1, listroot);

		}

	}


	system("pause");
	return 0;
}
