#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>

using namespace std;

int main()
{
	string s_in;
	unordered_map<char, int> freque;
	unordered_map<char, double> freque2;
	bool running = true;
	while (running)
	{
		s_in.clear();
		getline(cin, s_in);
		if (s_in == "0")
		{
			running = false;
		}
		else
		{
			for (auto& i : s_in)
			{
				if (!freque.count(i))
				{
					freque[i] = 0;
				}
				freque[i]++;
			}
			for (auto& i : freque)
			{
				freque2[i.first] = i.second / (double)s_in.length();
			}
			for (auto& i : freque2)
			{
				cout << i.first << ' ' << i.second << '\n';
			}
		}
	}
	return 0;
}