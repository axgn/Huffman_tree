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

int find_c(vector<HUF_Tree> v, char c)//�����ַ���Ӧ�����±�
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

void statis(vector<HUF_Tree>& v_HUF, const string& s_in)//ͳ�ƹ���������Ҷ�ӽ���Ƶ��ֵ
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

void find_two_min(const vector<HUF_Tree>& v, int& p_min, int& p_sec_min)//�ҵ���Сֵ�Լ��ڶ�С��ֵ����Ӧ���±�
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

void Extendv(vector<HUF_Tree>& v)//����̬������̬����������������
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
		v[p_min].parent = int(v.size() - 1);
		v[p_sec_min].parent = int(v.size() - 1);
	}
}

void create_map(const vector<HUF_Tree>& v_HUF, unordered_map<char, string>& map,int i,string& s)//�ݹ鷽ʽ�����ַ�����
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

void coding(vector<HUF_Tree> v_HUF, unordered_map<char, string>& map)//�ǵݹ鷽ʽ�����ַ�����
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

int cnt_num(const vector<HUF_Tree>& v)
{
	int cnt = 0;
	for (auto& i : v)
	{
		if (i.c != '0')
		{
			cnt++;
		}
	}
	return cnt;
}

void encoding(unordered_map<char,string>& map,const string& s_in, string& result)//���������ַ������б���
{
	for (auto& i : s_in)
	{
		result += map[i];
	}
}

void decoding(vector<HUF_Tree>& v, const string& src_str, string& des_str)//���������ַ������н���
{
	HUF_Tree temp = v.back();
	for (auto& i : src_str)
	{
		if (i == '0')
		{
			temp = v[temp.left_t];
		}
		else
		{
			temp = v[temp.right_t];
		}
		if (temp.c != '0')
		{
			des_str.push_back(temp.c);
			temp = v.back();
		}
	}
}

int main()
{
	string s_in;//������ַ���
	vector<HUF_Tree> v_HUF;//�洢��������������������
	unordered_map<char, string> map;//��ʾ�ַ����Ӧ����Ĺ�ϣ��
	bool running = true;//�������еĿ��Ʊ���
	string result{};//�������ַ���
	string decode_string{};//�������ַ���
	string s{};//�ݹ������ĳ�ʼ����
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
			create_map(v_HUF, map, int(v_HUF.size() - 1),s);//�ݹ鷽��
			//coding(v_HUF, map);//�ǵݹ鷽��
			encoding(map,s_in,result);
			decoding(v_HUF, result, decode_string);
			sort(v_HUF.begin(), v_HUF.begin() + cnt_num(v_HUF),
				[](HUF_Tree t1, HUF_Tree t2)->bool { return t1.c < t2.c; });//�Թ��������ڵ��ַ���������
			vector<pair<char, string>> temp(map.begin(),map.end());
			sort(temp.begin(), temp.end(),
				[](pair<char, string> m1, pair<char, string> m2)->bool {return m1.first < m2.first; });//������ַ���������
			for (int i = 0; i < v_HUF.size(); i++)
			{
				if (v_HUF[i].c != '0')
				{
					cout << v_HUF[i].c << ':' << v_HUF[i].fre << ' ';
				}
			}
			cout << '\n';
			for (int i = 0; i < v_HUF.size(); i++)
			{
				cout << i + 1 << ' ' << v_HUF[i].fre << ' ' << v_HUF[i].parent + 1 << ' '
					<< v_HUF[i].left_t + 1 << ' ' << v_HUF[i].right_t + 1 << '\n';
			}
			for (auto& i : temp)
			{
				cout << i.first << ':' << i.second << '\n';
			}
			cout << result << '\n';
			cout << decode_string << '\n';
		}
	}
	return 0;
}