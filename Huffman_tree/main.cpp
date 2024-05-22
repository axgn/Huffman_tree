#include<iostream>
#include<vector>
#include<string>
#include<limits>

using namespace std;

struct HUF_Tree
{
	char c{'0'};
	int fre{0};
	int left_t{-1};
	int right_t{-1};
	int parent{-1};
};

int find_c(vector<HUF_Tree> v, char c)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].c == c)
		{
			return i;
		}
	}
	return -1;
}

void statis(vector<HUF_Tree>& v_HUF, const string& s_in)
{
	for (auto& i : s_in)
	{
		int pos = find_c(v_HUF, i);
		if (pos == -1)
		{
			v_HUF.push_back({ i, 1 });
		}
		else
		{
			v_HUF[pos].fre++;
		}
	}
}

void find_two_min(const vector<HUF_Tree>& v, int& p_min, int& p_sec_min)
{ 
	int min = INT_MAX;
	int sec_min = min;
	p_min = -1;
	p_sec_min = 0;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i].parent == -1)
		{
			if (v[i].fre < min)
			{
				sec_min = min;
				p_sec_min = p_min;
				min = v[i].fre;
				p_min = i;
			}
			else if (v[i].fre < sec_min)
			{
				sec_min = v[i].fre;
				p_sec_min = i;
			}
		}
	}
}

void Extendv(vector<HUF_Tree>& v)
{
	while (true)
	{
		int p_min = 0;
		int p_sec_min = 0;
		find_two_min(v, p_min, p_sec_min);
		if (p_sec_min == -1)
		{
			break;
		}
		v.push_back({ '0',v[p_min].fre + v[p_sec_min].fre,p_min,p_sec_min , -1});
		v[p_min].parent = v.size() - 1;
		v[p_sec_min].parent = v.size() - 1;
	}
}

int main()
{
	string s_in;
	vector<HUF_Tree> v_HUF;
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
			statis(v_HUF, s_in);
			Extendv(v_HUF);
			for (auto& i : v_HUF)
			{
				cout << i.c << ' ' << i.fre << ' ' << i.left_t + 1 << ' '
					<< i.right_t + 1 << ' ' << i.parent + 1 << '\n';
			}
		}
	}
	return 0;
}