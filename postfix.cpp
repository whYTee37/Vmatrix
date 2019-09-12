#include<iostream>
#include<map>
#include<string>
using namespace std;


template<typename Stack_entry>
class Stack {
public:
	Stack(int size) :count(0), stacksize(size), entry(new Stack_entry[size]) {}
	~Stack() { delete[] entry; }
	bool empty() const
	{
		return (count == 0);
	}
	bool pop()
	{
		bool outcome = true;
		if (empty())
			outcome = false;
		else
			count--;
		return outcome;
	}
	bool push(const Stack_entry & item)
	{
		bool outcome = true;
		if (count >= stacksize)
			outcome = false;
		else
			entry[count++] = item;
		return outcome;
	}
	bool top(Stack_entry & item) const
	{
		bool outcome = true;
		if (empty())
			outcome = false;
		else
			item = entry[count - 1];
		return outcome;
	}


private:
	int count;
	int stacksize;
	Stack_entry* entry;
};

bool eval_BE(const string & exp, map<char, bool> f)
{
	Stack<int> S(1000);
	int i = 0;
	while (i != exp.length())
	{
		if (exp[i] != '+' && exp[i] != '*' && exp[i] != '-')//不是符号而是数字(常量、变量)时 
		{
			if (exp[i] == '0' || exp[i] == '1')
				S.push(exp[i] - '0');

			else//变量的情况 
			{
				bool x;
				map<char, bool>::iterator iter = f.find(exp[i]);
				if (iter != f.end())
					x = iter->second;
				S.push(x);

			}
		}
		else if (exp[i] == '-')
		{
			int x;
			if (S.top(x))
				x = !x;
			S.pop();
			S.push(x);
		}
		else if (exp[i] == '+')
		{
			int right, left, x;
			S.top(right);
			S.pop();
			S.top(left);
			S.pop();
			x = right | left;
			S.push(x);
		}
		else if (exp[i] == '*')
		{
			int right, left, x;
			S.top(right);
			S.pop();
			S.top(left);
			S.pop();
			x = right & left;
			S.push(x);
		}

		i++;
	}
	int answer;
	S.top(answer);
	return answer;
}

int main()
{
	map<char, bool> f;

	cout << eval_BE("01+", f);
}


