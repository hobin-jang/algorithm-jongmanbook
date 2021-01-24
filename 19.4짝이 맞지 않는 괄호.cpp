#include<iostream>
#include<string>
#include<stack>
using namespace std;

bool matched(const string& formula) {

	const string opening("({["), closing(")}]");
	stack<char>openStack;

	for (int i = 0; i < formula.size(); i++) {
		if (opening.find(formula[i]) != -1)
			openStack.push(formula[i]);
		else {
			if (openStack.empty())
				return false;
			if (opening.find(openStack.top()) != closing.find(formula[i]))
				return false;
			openStack.pop();
		}
	}

	return openStack.empty();
}


int main()
{
	int C;
	cin >> C;
	while (C--) {
		string formula;
		cin >> formula;
		if (matched(formula))
			cout << "YES" << '\n';
		else
			cout << "NO" << '\n';
	}
}