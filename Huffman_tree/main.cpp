#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<limits>
#include<unordered_map>

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

void create_map(const vector<HUF_Tree>& v_HUF, unordered_map<char, string>& map,int i,string& s)
{
	if (v_HUF[i].left_t == -1 && v_HUF[i].right_t == -1)
	{
		map[v_HUF[i].c] = s;
		return;
	}
	if (v_HUF[i].left_t != -1)
	{
		s.push_back('0');
		create_map(v_HUF, map, v_HUF[i].left_t, s);
		s.pop_back();
	}
	if (v_HUF[i].right_t != -1)
	{
		s.push_back('1');
		create_map(v_HUF, map, v_HUF[i].right_t, s);
		s.pop_back();
	}
}

void coding(vector<HUF_Tree> v_HUF, unordered_map<char, string>& map)
{
	int j = 0;
	int c{}, f{};
	for (auto& i : v_HUF)
	{
		if (v_HUF[j].c == '0')
		{
			break;
		}
		j++;
	}
	for (int k = 0; k < j; k++)
	{
		c = k;
		f = v_HUF[k].parent;
		string code{};
		while (f!=-1)
		{
			if (c == v_HUF[f].left_t)
			{
				code += '0';
			}
			else if (c == v_HUF[f].right_t)
			{
				code += '1';
			}
			c = f;
			f = v_HUF[f].parent;
		}
		reverse(code.begin(), code.end());
		map[v_HUF[k].c]= code;
	}	
}

int main()
{
	string s_in;
	vector<HUF_Tree> v_HUF;
	unordered_map<char, string> map,comap;
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
			string s = "";
			create_map(v_HUF, map, v_HUF.size() - 1,s);
			coding(v_HUF, comap);
			for (auto& i : comap)
			{
				cout << i.first << ':' << i.second << '\n';
			}
			for (int i = 0; i < v_HUF.size(); i++)
			{
				if (v_HUF[i].c != '0')
				{
					cout << i + 1 << ':' << v_HUF[i].c << ' ';
				}
			}
			cout << '\n';
			for (int i = 0; i < v_HUF.size(); i++)
			{
				cout << i + 1 << ' ' << v_HUF[i].fre << ' ' << v_HUF[i].parent + 1 << ' '
					<< v_HUF[i].left_t + 1 << ' ' << v_HUF[i].right_t + 1 << '\n';
			}
			for (auto& i : map)
			{
				cout << i.first << ':' << i.second << '\n';
			}
			string result;
			for (auto& i : s_in)
			{
				result += map[i];
			}
			cout << result << '\n';
		}
	}
	return 0;
}