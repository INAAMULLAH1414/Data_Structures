#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;
template <typename Object>
class StackADT
{
public:
	virtual bool isEmpty() const = 0;
	virtual long sSize() const = 0;
	virtual Object peek() const = 0;
	virtual void push(const Object &) = 0;
	virtual Object pop() = 0;
};
template <typename Object>
class StackL : public StackADT<Object>
{
private:
	class ListNode
	{
	public:
		Object data;
		ListNode *next;
		ListNode(Object d)
		{
			data = d;
			next = NULL;
		}
	};
	ListNode *head;
	long top;

public:
	StackL()
	{
		head = NULL;
		top = 0;
	}
	~StackL()
	{
		while (head != NULL)
		{
			ListNode *junk = head;
			head = head->next;
			delete junk;
		}
		head = NULL;
	}
	bool isEmpty() const
	{
		return (head == NULL);
	}
	long sSize() const
	{
		return top;
	}
	Object peek() const
	{
		if (isEmpty())
		{
			return 'n';
		}
		return head->data;
	}
	void push(const Object &d)
	{
		top++;
		if (isEmpty())
		{
			head = new ListNode(d);
			return;
		}
		ListNode *tmp = new ListNode(d);
		tmp->next = head;
		head = tmp;
	}
	Object pop()
	{
		if (isEmpty())
		{
			throw 0;
		}
		ListNode *tmp = head;
		head = head->next;
		Object o = tmp->data;
		delete tmp;
		top--;
		return o;
	}
};
bool isOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')')
		return true;
	return false;
}
int preceDence(char op)
{
	if (op == '+' || op == '-')
		return 1;
	else if (op == '*' || op == '/')
		return 2;
	else if (op == '^')
		return 3;
	else
		return -1;
}
string makeZero(string inFix)
{
	int i = inFix.length() - 1;
	while (inFix[i] != '=' && i != 0)
	{
		if (inFix[i] >= 'A' && inFix[i] <= 'Z')
		{
			cout << inFix[i] << "=";
			inFix[i] = '0';
			cout << inFix[i] << ", ";
		}
		i--;
	}
	return inFix;
}
void infixToPostfix(const char *inFix, char *postFix)
{
	int k = 0;
	StackADT<char> *s = new StackL<char>;
	for (int i = 0; i < strlen(inFix); i++)
	{
		if (inFix[i] == ' ' || inFix[i] == '=')
			continue;
		else if (inFix[i] >= 'A' && inFix[i] <= 'Z')
			postFix[k++] = inFix[i];
		else if (!isOperator(inFix[i]) || inFix[i] == '~')
		{
			postFix[k++] = inFix[i];
		}
		else
		{
			if (preceDence(s->peek()) > preceDence(inFix[i]) && preceDence(inFix[i]) != -1)
			{
				postFix[k++] = s->pop();
				s->push(inFix[i]);
			}
			else
			{
				if (inFix[i] == ')')
				{
					while (s->peek() != '(')
					{
						postFix[k++] = s->pop();
					}
					s->pop();
				}
				else
				{
					s->push(inFix[i]);
				}
			}
		}
	}
	while (!s->isEmpty())
	{
		if (s->peek() != '(' || s->peek() != ')')
			postFix[k++] = s->pop();
		else
			s->pop();
	}
	postFix[k] = '\0';
}
double opeRation(double op1, double op2, char opr)
{
	if (opr == '+')
		return op1 + op2;
	else if (opr == '-')
		return op1 - op2;
	else if (opr == '*')
		return op1 * op2;
	else if (opr == '/')
	{
		if (opr == 0)
			throw 0;
		return op1 / op2;
	}
	else if (opr == '^')
		return pow(op1, op2);
	else
		throw 0;
}
double evaluatePostfix(const char *postFix)
{
	bool flag = false;
	StackADT<int> *s = new StackL<int>;
	string cr = "";
	bool b = true;
	for (int i = 0; i < strlen(postFix); i++)
	{
		if (postFix[i] >= 'A' && postFix[i] <= 'Z' && b)
		{
			cr += postFix[i];
			continue;
		}
		else if (postFix[i] >= 'A' && postFix[i] <= 'Z')
		{
			continue;
		}
		else if (postFix[i] == '~')
		{
			flag = true;
		}
		else if (!isOperator(postFix[i]))
		{
			if (flag)
			{
				s->push(-1 * (int(postFix[i]) - 48));
				flag = false;
			}
			else
				s->push(int(postFix[i]) - 48);
		}
		else
		{
			int op2 = s->pop(), op1 = s->pop();
			s->push(opeRation(op1, op2, postFix[i]));
		}
		b = false;
	}
	int i = 0;
	while (i < cr.length())
	{
		cout << cr[i] << "=";
		if (s->peek() < 0)
		{
			cout << '~';
			cout << -s->peek();
		}
		else
		{
			cout << s->peek();
		}

		cout << ",";
		i++;
	}

	cout << endl;
	return s->pop();
}
int main()
{
	ifstream inp("Input.txt");
	if (inp.fail())
	{
		cout << "Error in loading file" << endl;
	}
	else
	{
		string s;
		while (inp.peek() != EOF)
		{
			getline(inp, s);
			if (s == "#")
			{
				inp.close();
				return 0;
			}
			s = makeZero(s);
			char *s2 = new char[s.length()];
			infixToPostfix(s.c_str(), s2);
			evaluatePostfix(s2);
			delete[] s2;
		}
	}
}
