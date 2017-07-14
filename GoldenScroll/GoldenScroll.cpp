// GoldenScroll.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
using namespace std;
//==============================================================
/*83����һ�������嵥�������һ����Ч�㷨���������嵥�е�����ɵ�����Ӿ���Ҫ������е��к��ж����嵥�еĵ��ʡ�
����һ��string����dic���������嵥��ͬʱ�����嵥�Ĵ�Сn���뷵������Ӿ���������
��֤�����嵥�Ĵ�СС�ڵ���50����ĳһ���ȵĴ�������С�ڵ���12��
����������
["aaa","aaa","aaa","bb","bb"]
���أ�9*/
class AlphaMatrix {
public:
	int findAlphaMatrix(vector<string> dic, int n) {
		// ��ֻ��˵��ʲô���⡣�������������������ֶ���ô����Ӧ���������������ô��������ͷҲ�벻������ô��������
		map<string, int> m;
		int maxArea = 0, temp = 0;
		for (int i = 0; i < n; i++) {
			m[dic[i]]++;
			temp = dic[i].length() * m[dic[i]];
			maxArea = max(maxArea, temp);
		}
		return maxArea;
	}
};
//==============================================================
/*82����һ���������͸�������ɵ�NxN�������д�����ҳ�Ԫ���ܺ������Ӿ����볢��ʹ��һ����Ч�㷨��
����һ��int����mat�;���Ľ���n���뷵��Ԫ���ܺ������Ӿ����Ԫ��֮�͡���֤Ԫ�ؾ���ֵС�ڵ���100000���Ҿ������С�ڵ���200��
����������
[[1,2,-3],[3,4,-5],[-5,-6,-7]],3
���أ�10*/
class SubMatrix {
public:
	int sumOfSubMatrix(vector<vector<int> > mat, int n) {
		int maxsum = 0, submax = 0;
		for (int startRow = 0; startRow < n; startRow++) {
			vector<int> v(n, 0);
			for (int i = startRow; i < n; i++) {
				submax = 0;
				for (int j = 0; j < n; j++) {
					v[j] += mat[i][j];
					submax = max(v[j], v[j] + submax);
					maxsum = max(maxsum, submax);
				}
			}
		}
		return maxsum;
	}
};
//==============================================================
/*81����һ����������ÿ����Ԫ(����)�Ǻڼ���(��0��1)�������һ����Ч�㷨���ҵ���������ɫ��ͬ������ӷ���
����һ��01����mat��ͬʱ��������ı߳�n���뷵������ӷ���ı߳�����֤����߳�С�ڵ���100��
����������
[[1,1,1],[1,0,1],[1,1,1]],3
���أ�3*/
class SubMatrix {
public:
	int maxSubMatrix(vector<vector<int> > mat, int n) {
		vector<int> ones(n, 1);
		vector<vector<int>> left(n, ones);	//��ǰ�����������ͬ�ĵ����(���Լ�)
		vector<vector<int>> above(n, ones);	//��ǰ���ϱ�������ͬ�ĵ���������Լ���
		initail(mat, n, left, above);
		int maxLength = 1;
		for (int i = 1; i < n; i++) {
			for (int j = 1; j < n; j++) {
				if (mat[i][j] != mat[i][j - 1] || mat[i][j] != mat[i - 1][j]) {
					if (mat[i][j] != mat[i][j - 1] && mat[i][j] != mat[i - 1][j]) {
						left[i][j] = above[i][j] = 1;
					}
					else if (mat[i][j] != mat[i][j - 1]) {
						left[i][j] = 1;
						above[i][j] = above[i - 1][j] + 1;
					}
					else if (mat[i][j] != mat[i - 1][j]) {
						above[i][j] = 1;
						left[i][j] = left[i][j - 1] + 1;
					}
				}
				else {
					left[i][j] = left[i][j - 1] + 1;
					above[i][j] = above[i - 1][j] + 1;
					int minLength = min(left[i][j - 1], above[i - 1][j]);//�����Ƿ��󣬳���Ҫһ�£����ȡ������С���Ǹ�
					for (int length = minLength; length > 0 && length >= maxLength; length--) {	//����С�������
						if (left[i - length][j] >= minLength + 1 && above[i][j - length] >= minLength + 1) {//����Աߵĳ���
							maxLength = max(maxLength, length + 1);
						}
					}
				}
			}
		}
		return maxLength;
	}
	void initail(vector<vector<int>> mat, int n, vector<vector<int>> &left, vector<vector<int>> &above) {
		for (int i = 1; i < n; i++) {
			if (mat[0][i] == mat[0][i - 1]) {
				left[0][i] = left[0][i - 1] + 1;
			}
			if (mat[i][0] == mat[i - 1][0]) {
				above[i][0] = above[i - 1][0] + 1;
			}
		}
	}
};
//==============================================================
/*80������һ���ֵ䣬ͬʱ�����ֵ��е������ַ���s��t������һ���任��ÿ�ο��Ըı��ַ����е�����һ���ַ��������һ���㷨��
������s�任��t��������ٲ�����ͬʱ��Ҫ�����ڱ任�����е�ÿ���������ֵ��еĴ���
����һ��string����dic��ͬʱ���������Сn����s�ʹ�t���뷵����s��t�任��������ٲ�����
���޷��任��t�򷵻�-1����֤�ַ������Ⱦ�С�ڵ���10�����ֵ����ַ�������С�ڵ���500��
����������
["abc","adc","bdc","aaa��],4,��abc","bdc"
���أ�2*/
class Change {
public:
	bool path(string a, string b) {
		int lenA = a.length(), lenB = b.length();
		if (lenA != lenB) {
			return false;
		}
		int flag = 0;
		for (int i = 0; i < lenA; i++) {
			if (a[i] != b[i]) {
				if (flag == 0) {
					flag++;
				}
				else {
					return false;
				}
			}
		}
		return true;
	}
	int countChanges(vector<string> dic, int n, string s, string t) {
		int map[500][500];	//������ȷ˵�˲�����500����so
		int index_s, index_t;
		for (int i = 0; i < n; i++) {
			if (dic[i] == s) {
				index_s = i;
			}
			if (dic[i] == t) {
				index_t = i;
			}
			for (int j = i; j < n; j++) {
				if (i == j) map[i][j] = 0;
				else if (path(dic[i], dic[j])) {
					map[i][j] = map[j][i] = 1;
				}
				else {
					map[i][j] = map[j][i] = 500;	//ֻ��500��Ԫ�أ������벻��500
				}
			}
		}
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (map[i][k] + map[k][j] < map[i][j]) {
						map[i][j] = map[i][k] + map[k][j];
					}
				}
			}
		}
		return (map[index_s][index_t] == 500) ? -1 : map[index_s][index_t];
	}
};

//==============================================================
/*79������һЩ������ɵ�����Ҫ�������δ��룬�����һ����Ч�㷨������ÿ�δ���һ�����ֺ�
�����ǰ���д������ֵ���λ����(��������ż��������������λ��Ϊ��n/2С�����֣�nΪ�Ѵ������ָ���)��
����һ��int����A��Ϊ������������У�ͬʱ�������д�Сn���뷵��һ��int���飬����ÿ�δ�������λ������֤nС�ڵ���1000��
����������
[1,2,3,4,5,6],6
���أ�[1,1,2,2,3,3]*/
class Middle {
public:
	vector<int> getMiddle(vector<int> A, int n) {
		priority_queue<int, vector<int>, less<int>> small;
		priority_queue<int, vector<int>, greater<int>> big;
		vector<int> ans;

		for (int i = 0; i < A.size(); ++i) {
			if (small.empty() || A[i] <= small.top())
				small.push(A[i]);
			else
				big.push(A[i]);
			if (small.size() == big.size() + 2) {
				big.push(small.top());
				small.pop();
			}
			else if (small.size() == big.size() - 1) {
				small.push(big.top());
				big.pop();
			}
			ans.push_back(small.top());
		}
		return ans;
	}
};
//==============================================================
/*78������һ��СдӢ����ĸ��ɵ��ַ���s��һ�������϶�СдӢ���ַ���������p�������һ����Ч�㷨��
����p�е�ÿһ���϶��ַ������ж����Ƿ�Ϊs���Ӵ�������һ��string����p�����Ĵ�Сn��
ͬʱ����string s��Ϊĸ�����뷵��һ��bool���飬ÿ��Ԫ�ش���p�еĶ�Ӧ�ַ����Ƿ�Ϊs���Ӵ���
��֤p�еĴ�����С�ڵ���8����p�еĴ��ĸ���С�ڵ���500��ͬʱ��֤s�ĳ���С�ڵ���1000��
����������
["a","b","c","d"],4,"abc"
���أ�[true,true,true,false]*/
class Substr {
public:
	vector<bool> chkSubStr(vector<string> p, int n, string s) {
		//���޳ܵ�ʹ��find�ˣ������о�trie��
		vector<bool> ans;
		for (int i = 0; i < n; i++) {
			if (s.find(p[i]) != string::npos) ans.push_back(true);
			else ans.push_back(false);
		}
		return ans;
	}
};
//==============================================================
/*77����һ�鵥�ʣ����дһ���������������ҳ����������ַ�����ɵ���Ĵ�A����A��������������ɵ�(���ظ�)��ĵ��ʡ�
����һ��string����str��ͬʱ��������Ĵ�Сn���뷵������ʵĳ��ȣ���֤��������������ʴ��ڡ�
����������
["a","b","c","ab","bc","abc"],6
���أ�3*/
class LongestString {
public:
	bool cmp(string a, string b) {
		return a.length() > b.length();
	}
	int getLongest(vector<string> str, int n) {
		sort(str.begin(), str.end(), cmp);
		for (int i = 0; i < n; i++) {
			if (longest(str,str[i],i,n)) {
				return str[i].length();
			}
		}
		return 0;
	}
	bool longest(vector<string> str, string a, int begin, int end) {
		if (a.length() == 0) {
			return true;
		}
		for (int i = begin + 1; i < end; i++) {
			if (a.find(str[i]) == 0) {
				if (longest(str, a.substr(str[i].length()), begin, end)) {
					return true;
				}
			}
		}
		return false;
	}
};

//==============================================================
/*76����һƪ�����ں�������ʣ��ָ����������ʣ������һ����Ч�㷨���ҳ��������������ʵ���̾���
(����������ĵ�����,Ҳ��������������������λ�õĲ�ľ���ֵ)��
����һ��string����article�������������£�ͬʱ�������µĵ�����n�ʹ����ҵ���������x��y��
�뷵���������ʵ���̾��롣��֤�������ʾ������г����Ҳ���ͬ��ͬʱ��֤���µ�����С�ڵ���1000��*/
class Distance {
public:
	int getDistance(vector<string> article, int n, string x, string y) {
		int i_x = -1, i_y = -1;
		int ans = n;
		for (int i = 0; i < n; i++) {
			if (article[i] == x) {
				i_x = i;
			}
			if (article[i] == y) {
				i_y = i;
			}
			if (i_x != -1 && i_y != -1) {
				ans = min(ans, abs(i_x - i_y));
			}
		}
		return ans;
	}
};

//==============================================================
/*75��������һ�����飬���ҳ�������ÿ��Ԫ�صĺ�����������С��Ԫ�أ�����������Ϊ-1��
����һ��int����A������Ĵ�Сn���뷵��ÿ��Ԫ�������ֵ��ɵ����顣��֤A��Ԫ��Ϊ����������nС�ڵ���1000��
����������
[11,13,10,5,12,21,3],7
[12,21,12,12,21,-1,-1]*/
class NextElement {
public:
	vector<int> findNext(vector<int> A, int n) {
		// ��һ�������ˣ���������������Ҫ��
		vector<int> ans;
		if (n <= 1) {
			ans.push_back(-1);
			return ans;
		}		
		for (int i = 0; i < n - 1; i++) {
			stack<int> s;
			for (int j = i + 1; j < n; j++) {
				if (s.empty()) {
					if (A[j] > A[i]) {
						s.push(A[j]);
					}
				}
				else {
					if (A[j] > A[i] && A[j] < s.top()) {
						s.push(A[j]);
					}
				}
			}
			int temp = (s.empty()) ? -1 : s.top();
			ans.push_back(temp);
		}
		ans.push_back(-1);
		return ans;
	}
};
//==============================================================
/*74������������һ��int���飬�����ҳ�������ÿ��Ԫ�ص���һ���������Ԫ�ء�
����һ��int����A������Ĵ�Сn���뷵��һ��int���飬����ÿ��Ԫ�ر��������һ��Ԫ��,����������Ϊ-1����֤������Ԫ�ؾ�Ϊ��������
����������
[11,13,10,5,12,21,3],7
���أ�[13,21,12,12,21,-1,-1]*/
class NextElement {
public:
	vector<int> findNext(vector<int> A, int n) {
		vector<int> ans;
		if (n <= 1) {
			ans.push_back(-1);
			return ans;
		}		
		queue<int> q;		
		for (int i = 0; i < n - 1; i++) {
			bool flag = true;
			for (int j = i + 1; j < n; j++) {
				if (A[j] > A[i]) {
					q.push(A[j]);
					flag = false;
					break;
				}
			}
			if (flag) {
				q.push(-1);
			}
		}
		while (!q.empty()) {
			ans.push_back(q.front());
			q.pop();
		}
		ans.push_back(-1);
		return ans;
		/*������������ˣ�����ʵ�����ҳ�A��Ԫ��֮����������СԪ�أ���������Ű�
		vector<int> ans;
		if (n <= 1) {
			ans.push_back(-1);
			return ans;
		}		
		for (int i = 0; i < n - 1; i++) {
			stack<int> s;
			for (int j = i + 1; j < n; j++) {
				if (s.empty()) {
					if (A[j] > A[i]) {
						s.push(A[j]);
					}
				}
				else {
					if (A[j] > A[i] && A[j] < s.top()) {
						s.push(A[j]);
					}
				}
			}
			int temp = (s.empty()) ? -1 : s.top();
			ans.push_back(temp);
		}
		ans.push_back(-1);
		return ans;*/
	}
};
//==============================================================
/*73�����дһ�����������0��n(����n)������2�����˼��Ρ�
����һ��������n���뷵��0��n��������2�����˼��Ρ�
����������
10
���أ�1*/
class Count2 {
public:
	int countNumberOf2s(int n) {
		int ans = 0;
		for (int i = 1; i <= n; i *= 10) {
			int high = n / i;
			int low = n % i;
			ans += ((high + 7) / 10) * i + (high % i == 2) * (low - 1);
		}
		return ans;
	}
};
//==============================================================
/*72�����дһ��������������������ӡ�����ʹ��+�����������������
��������int A��B���뷵��A��B��ֵ
����������
1,2
���أ�3*/
class UnusualAdd {
public:
	int addAB(int A, int B) {
		if (B == 0) {
			return A;
		}
		return addAB(A^B, (A^B) << 1);
	}
};

//==============================================================
/*71����һ�����ƽ������ݽṹTreeNode��������val���Ժ�ָ����������ָ�롣�����������ʾ���������
(����leftָ���ʾ����ӣ�rightָ���ʾ�Ҷ���)�����дһ�������������������ת��Ϊһ������
���ж�������������ݽṹ��TreeNodeʵ�֣���������ݽṹ��ListNodeʵ�֡�
��������������ĸ����ָ��root���뷵��ת���ɵ������ͷָ�롣*/
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Converter {
public:
	ListNode* head = new ListNode(0);
	ListNode* currentNode = head;
    ListNode* treeToList(TreeNode* root) {
		if (root != NULL) {
			treeToList(root->left);
			currentNode->next = new ListNode(root->val);
			currentNode = currentNode->next;
			treeToList(root->right);
		}
		return head->next;
    }
};

//==============================================================
/*70�������һ����Ч�㷨���ҳ�����������֮��Ϊָ��ֵ�����������ԡ�
����һ��int����A�������Сn�Լ�����ҵĺ�sum���뷵�غ�Ϊsum�������Եĸ�������֤�����СС�ڵ���3000��
����������
[1,2,3,4,5],5,6
���أ�2*/
/*FindPair C;
	vector<int> c = { 11,7,7,6,14,2,14,15,2,1,2,12,13,9,8,15,13,8,10,11,14,10,2,9,4,9,3,7,6,10,15,4,7,6,15,3,9,13,5,2,6,10,10,1,12,4,3,3,8,8,1,4,7,11,13,5,13,15,4,3,1,11,6,11,9,9,11,15,12,10,13,3,11,4,8,9,7,3,13,9,11,3,2,11,10,1,4,2,3,3,14,11,5,10,1,14,8,1,11,3,1,9,14,6,1,7,15,10,14,6,4,12,11 };
	cout << C.countPairs(c, 113, 16) << endl;*/
class FindPair {
public:
	int countPairs(vector<int> A, int n, int sum) {
		int size = A.size();
		if (size == 0 || n <= 0) {
			return 0;
		}//if
		// ����
		sort(A.begin(), A.end());
		//
		int count = 0;
		for (int i = 0, j = n - 1; i < j;) {
			int s = A[i] + A[j];
			if (s == sum) {
				// 3 3 3�������
				if (A[i] == A[j]) {
					int x = j - i + 1;
					count += x*(x - 1) / 2;
					break;
				}//if
				// 2 2 3 4 4 4�������
				else {
					int k = i + 1;
					while (k <= j && A[i] == A[k]) {
						++k;
					}//while
					int k2 = j - 1;
					while (k2 >= i && A[j] == A[k2]) {
						--k2;
					}//while
					count += (k - i)*(j - k2);
					i = k;
					j = k2;
				}//else
			}//if
			else if (s < sum) {
				++i;
			}//else
			else {
				--j;
			}//else
		}//for
		return count;
        /*��������һ�����⣬û�취����������������������
        int *hash = new int[100000]();
        int ans = 0;
        for (int i = 0; i < n; i++) {
            hash[A[i]]++;
        }
        for (int i = 0; i < n; i++) {
            if (A[i] == sum) {
                ans += hash[A[i]];
                hash[A[i]] = 0;
            }
            else if (A[i] == sum / 2) {
                ans += hash[A[i]] * (hash[A[i]] - 1) / 2;
                hash[A[i]] = 0;
            }
            else if (hash[sum - A[i]] != 0) {
                int a = hash[A[i]], b = hash[sum - A[i]];
                ans += a*b;
                hash[A[i]] = 0;
                hash[sum - A[i]] = 0;
            }
        }
        return ans;*/
	}
};
//==============================================================
/*69�������һ����Ч�ķ������ҳ�����ָ��������һƪ�����еĳ���Ƶ����
����һ��string����article�������Сn��һ����ͳ�Ƶ���word���뷵�ظõ����������еĳ���Ƶ������֤���µĴ���С�ڵ���1000��*/
class Frequency {
public:
	int getFrequency(vector<string> article, int n, string word) {
		map<string, int> m;
		for (int i = 0; i < n; i++) {
			m[article[i]]++;
		}
		return m[word];
	}
};
//==============================================================
/*68������һ�������и����������飬���ҳ��ܺ������������С�
����һ��int����A�������Сn���뷵�������������еĺ͡���֤n�Ĵ�СС�ڵ���3000��
����������
[1,2,3,-6,1]
���أ�6*/
class MaxSum {
public:
	int getMaxSum(vector<int> A, int n) {
		if (n == 1) return A[0];
		int sum;
		int ans = 0;
		for (int i = 0; i < A.size() - 1; i++) {
			sum = A[i];
			ans = max(ans, sum);
			for (int j = i + 1; j < A.size(); j++) {
				sum += A[j];
				ans = max(ans, sum);
			}
		}
		return ans;
	}
};
//==============================================================
/*67����һ���Ǹ����������дһ���㷨����ӡ��������Ӣ��������
����һ��int x���뷵��һ��string��Ϊ��������Ӣ��������
����������
1234
���أ�"One Thousand,Two Hundred Thirty Four"*/
class ToString {
public:
	string belowTen[10] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" };
	string belowTwenty[10] = { "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
	string belowHundred[10] = { "", "Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
	string toString(int x) {
		if (x == 0) return "Zero";
		return helper(x);
	}
	string helper(int num) {
		string result = "";
		if (num < 10) result = belowTen[num];
		else if (num < 20) result = belowTwenty[num - 10];
		else if (num < 100) result = belowHundred[num / 10] + " " + helper(num % 10);
		else if (num < 1000) result = helper(num / 100) + " Hundred " + helper(num % 100);
		else if (num < 1000000) result = helper(num / 1000) + " Thousand" + (num % 1000 > 0 ? "," : " ") + helper(num % 1000);
		else if (num < 1000000000) result = helper(num / 1000000) + " Million" + (num % 1000000 > 0 ? "," : " ") + helper(num % 1000000);
		else result = helper(num / 1000000000) + " Billion " + helper(num % 1000000000);
		return Trim(result);
	}
	string Trim(string &str) {
		int i, len;

		//��ȥ����ߵĿո�
		len = str.length();
		for (i = 0; i<len; i++) {
			if (str[i] != ' ') break;
		}
		str = str.substr(i, len - i + 1);

		//��ȥ���ұߵĿո�
		len = str.length();
		for (i = len - 1; i >= 0; i--) {
			if (str[i] != ' ') break;
		}
		str = str.substr(0, i + 1);

		return str;
	}
};
//===========================================================
/*66����һ���������飬���дһ���������ҳ�����m��n��ֻҪ��m��n֮���Ԫ���ź������������������ġ�
ע�⣺n-mӦ��ԽСԽ�ã�Ҳ����˵���ҳ�����������������С�
����һ��int����A������Ĵ�Сn���뷵��һ����Ԫ�飬�����������е������յ㡣
(ԭ����λ�ô�0��ʼ���,��ԭ�������򣬷���[0,0])����֤A��Ԫ�ؾ�Ϊ��������
����������
[1,4,6,5,9,10],6
���أ�[2,3]*/
class Rearrange {
public:		
	vector<int> findSegment(vector<int> A, int n) {
		int start = 0, end = n - 1;
		vector<int> B = A;
		sort(A.begin(), A.end());
		bool flag = true;
		for (int i = 0; i < n; i++) {
			if (A[i] != B[i]) {
				if (flag) {
					start = i;
					flag = false;
				}
				else end = i;
			}
		}
		if (start == 0 && end == n - 1) {
			start = 0; end = 0;
		}
		vector<int> ans = { start, end };
		return ans;
	}
};
//===========================================================
/*65�������һ���㷨������n�Ľ׳��ж��ٸ�β���㡣
����һ��int n���뷵��n�Ľ׳˵�β���������֤nΪ��������
����������
5
���أ�1*/
class Factor {
public:
	int getFactorSuffixZero(int n) {
		//2*5���ܵõ�1���㣬�ͼ����ܹ��ֽܷ������5����
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			int ele = i;
			if (ele % 5 == 0) {
				ans++;
				ele /= 5;
			}
		}
		return ans;
	}
};
//===========================================================
/*64�������������ĸ��ۣ�ÿ���۷�һ������ɫ�����Ǻ�ɫ(R)����ɫ(Y)����ɫ(G)����ɫ(B)�����磬
���ܵ����ΪRGGB(��1Ϊ��ɫ����2��3Ϊ��ɫ����4Ϊ��ɫ)����Ϊ��ң�����Ҫ��ͼ�³���ɫ����ϡ����磬
����ܲ�YRGB��Ҫ����¶���ĳ���۵���ɫ������һ�Ρ����С���Ҫ��ֻ�ǲ¶�����ɫ����λ�´��ˣ�����һ�Ρ�α���С���ע�⣬�����С��������롰α���С���
��������string A��guess���ֱ��ʾ��ɫ��ϣ���һ���²⡣�뷵��һ��int���飬��һ��Ԫ��Ϊ���еĴ������ڶ���Ԫ��Ϊα���еĴ�����
����������
"RGBY","GGRR"
���أ�[1,1]*/
class Result {
public:
	vector<int> calcResult(string A, string guess) {
		int real = 0, fake = 0;
		map<char, int> m;
		for (int i = 0; i < A.length(); i++) {
			if (A[i] == guess[i]) {
				real++;
			}
			m[A[i]]++;
		}
		for (int i = 0; i < guess.length(); i++) {
			if (m[guess[i]] != 0) {
				fake++;
				m[guess[i]]--;
			}
		}
		vector<int> ans = { real, fake - real };
		return ans;
	}
};
//===========================================================
/*63�����дһ���������ҳ����������������Ǹ��������ǲ���ʹ��if-else�ȱȽϺ��ж��������
��������int a��b���뷵�ؽϴ��һ��������������ͬ�򷵻�����һ����
����������
1��2
���أ�2*/
class Max {
public:
	int getMax(int a, int b) {
		b = a - b;
		a -= b&(b >> 31);
		return a;
	}
};
//===========================================================
/*62������һ�������ľ��������̣������һ����Ч�㷨�жϵ�ǰ����Ƿ��ʤ��
����һ����ά����board������ǰ���̣�����Ԫ��Ϊ1�Ĵ����ǵ�ǰ��ҵ����ӣ�Ϊ0��ʾû�����ӣ�Ϊ-1�����ǶԷ���ҵ����ӡ�
����������
[[1,0,1],[1,-1,-1],[1,-1,0]]
���أ�true*/
class Board {
public:
	bool checkWon(vector<vector<int> > board) {
		if (board[0][0] + board[1][1] + board[2][2] == 3) return true;
		if (board[0][2] + board[1][1] + board[2][0] == 3) return true;
		for (int i = 0; i<3; i++) {
			if (board[i][0] + board[i][1] + board[i][2] == 3) return true;
			if (board[0][i] + board[1][i] + board[2][i] == 3) return true;
		}
		return false;
	}
};
//===========================================================
/*61�����дһ�������������ڲ�ʹ���κ���ʱ������ֱ�ӽ�����������ֵ��
����һ��int����AB��������Ԫ�غ͵�һ��Ԫ��Ϊ��������ֵ���뷵�ؽ���������顣
����������
[1,2]
���أ�[2,1]*/
class Exchange {
public:
	vector<int> exchangeAB(vector<int> AB) {
		AB[0] = AB[0] ^ AB[1];
		AB[1] = AB[0] ^ AB[1];
		AB[0] = AB[0] ^ AB[1];
		return AB;
	}
};
//===========================================================
/*60����һ�������������������������飬��ǰ��һ�����ں���һ�����֣����������������һ������ԡ������һ����Ч���㷨��������������е�����Ը�����
����һ��int����A�����Ĵ�Сn���뷵��A�е�����Ը�������֤nС�ڵ���5000��
����������
[1,2,3,4,5,6,7,0],8
���أ�7*/
class AntiOrder {
public:
	int ans = 0;
	void countNum(vector<int> &A, int start, int end, vector<int> &temp) {
		if (end - start == 1) {
			if (A[start] > A[end]) {
				ans++;
				swap(A[start], A[end]);
			}
			return;
		}
		else if (start == end) {
			return;
		}
		else {
			int mid = start + (end - start) / 2;
			countNum(A, start, mid, temp);
			countNum(A, mid + 1, end, temp);
			merge(A, start, end, temp);
			for (int i = start; i <= end; i++) {
				A[i] = temp[i];
			}
		}
	}
	void merge(vector<int> &A, int start, int end, vector<int> &temp) {
		int mid = start + (end - start) / 2;
		int leftIndex = start;
		int rightIndex = mid + 1;
		int index = start;
		while (leftIndex <= mid && rightIndex <= end) {
			if (A[leftIndex] > A[rightIndex]) {
				temp[index] = A[rightIndex];
				index++; rightIndex++;
				ans += mid - leftIndex + 1;
			}
			else {
				temp[index++] = A[leftIndex++];
			}
		}
		while (leftIndex <= mid) {
			temp[index++] = A[leftIndex++];
		}
		while (rightIndex <= end) {
			temp[index++] = A[rightIndex++];
		}
	}
	int count(vector<int> A, int n) {
		vector<int> temp(n,0);
		countNum(A, 0, n - 1, temp);
		return ans;
	}
};
//===========================================================
/*59����������Ҫ����һ������ͬʱҪ���ڶ���ÿ������ʱ����������ȣ����ڵ�ǰ������С�ڵ���
�������ĸ���(������������)�������һ����Ч�����ݽṹ���㷨��ʵ��������ܡ�
����һ��int����A��ͬʱ�������Ĵ�Сn���뷵��һ��int���飬Ԫ��Ϊÿ�μ���������ȡ���֤�����СС�ڵ���5000��
����������
[1,2,3,4,5,6,7],7
���أ�[0,1,2,3,4,5,6]*/
class Rank {
public:
	vector<int> getRankOfNumber(vector<int> A, int n) {
		vector<int> rank(n,0);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i; j++) {
				if (A[i] >= A[j]) {
					rank[i]++;
				}
			}
		}
		return rank;
	}
};

//===========================================================
/*58�����޺���һ����������Ϸ����Ϸ��һ����Ҫվ����һ���˵ļ���ϡ�Ϊ��ʹ���ɵ��޺����ȹ̣�����Ӧ����������˱�������˸���һ�㡣
����һ����Ϸ��Ҫ���������Ŀ��Ϊ���Ӿ�Ч�������ǻ�Ҫ��������˵���߱�������˸ߡ����дһ���㷨����������ܵ������ˣ�ע������������Ա��ͬʱ���֡�
����һ����άint������actors��ÿ��Ԫ��������ֵ���ֱ����һ����Ա����ߺ����ء�ͬʱ������Ա����n���뷵������ܵ�����������֤������С�ڵ���500��
����������
[[1,2],[3,4],[5,6],[7,8]],4
���أ�4*/
class Stack {
public:
	int getHeight(vector<vector<int> > actors, int n) {
		for (int i = 0; i < n; i++) {
			for (int j = n - 1; j > i; j--) {
				if (actors[j][0] > actors[j - 1][0]) {
					swap(actors[j], actors[j - 1]);
				}
			}
		}
		vector<int> sum(n, 1);
		int ans = 1;
		for (int i = 1; i < n; i++) {
			for (int j = i - 1; j >= 0; j--) {
				if (actors[i][0] < actors[j][0] && actors[i][1] < actors[j][1]) {
					sum[i] = max(sum[i], sum[j] + 1);
				}
			}
			ans = max(ans, sum[i]);
		}
		return ans;
	}
};
//===========================================================
/*57�����޺���һ����������Ϸ����Ϸ��һ����Ҫվ����һ���˵ļ���ϡ�ͬʱ����Ӧ����������˱�������˸���һ�㡣
��֪�μ���Ϸ��ÿ���˵���ߣ����д�������ͨ��ѡ�������Ϸ���ˣ����Ƕ��ܵ����ٸ��ˡ�
ע��������˶����Ⱥ󵽵ģ���ζ�Ųμ���Ϸ���˵��Ⱥ�˳����ԭ�����е�˳��Ӧ��һ�¡�
����һ��int����men��������������ÿ���˵���ߡ�ͬʱ����������n���뷵������ܵ�����������֤nС�ڵ���500��
����������
[1,6,2,5,3,4],6
���أ�4*/
class Stack {
public:
	int getHeight(vector<int> men, int n) {
		vector<int> ans(n, 1);
		int maxHigh = 1;
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < i; j++) {
				if (men[j] < men[i]) {
					ans[i] = max(ans[i], ans[j] + 1);
				}
			}
			maxHigh = max(maxHigh, ans[i]);
		}
		return maxHigh;
	}
};

//===========================================================
/*56����һ��NxM���������󣬾�����к��ж��Ǵ�С��������ġ������һ����Ч�Ĳ����㷨�����Ҿ�����Ԫ��x��λ�á�
����һ��int�������mat��ͬʱ��������Ĵ�Сn��m�Լ���Ҫ���ҵ�Ԫ��x���뷵��һ����Ԫ���飬�����Ԫ�ص��кź��к�(�����㿪ʼ)����֤Ԫ�ػ��졣
����������
[[1,2,3],[4,5,6]],2,3,6
���أ�[1,2]*/
class Finder {
public:
	vector<int> findElement(vector<vector<int> > mat, int n, int m, int x) {
		int row = 0, col = m - 1;
		while (row < n && col >= 0 && mat[row][col] != x) {
			if (mat[row][col] < x) {
				row++;
			}
			else {
				col--;
			}
		}
		vector<int> ans;
		if (row < n && col >= 0) {
			ans.push_back(row); ans.push_back(col);
			return ans;
		}
		else {
			ans.push_back(-1); ans.push_back(-1);
			return ans;
		}
	}
};

//===========================================================
/*55����һ���Ź�����ַ������飬���������в�����һЩ���ַ����������һ���㷨���ҳ������ַ�����λ�á��㷨�Ĳ��Ҳ��ֵĸ��Ӷ�Ӧ��Ϊlog����
����һ��string����str,ͬʱ���������Сn����Ҫ���ҵ�string x���뷵�ظô���λ��(λ�ô��㿪ʼ)��
����������
["a","b","","c","","d"],6,"c"
���أ�3*/
class Finder {
public:
	string minString(string A, string B) {
		int len = min(A.length(), B.length());
		int index = 0;
		while (index < len && A[index] == B[index]) {
			index++;
		}
		if (index == len) {
			return (index == A.length()) ? A : B;
		}
		else {
			return (A[index] > B[index]) ? B : A;
		}
	}
	int findIndex(vector<string> A, int start, int end, string x) {
		if (end - start == 1) {
			return (A[start] == x) ? start : end;
		}
		start += (A[start] == "") ? 1 : 0;
		end -= (A[end] == "") ? 1 : 0;
		//�Ź��������϶��ж������������ﻹ�Ǽ�һ���жϰ�
		if (start >= A.size() || end < 0 || ((start == end) && (A[start] != x))) {
			return -1;
		}
		int mid = start + (end - start) / 2;
		mid += (A[mid] == "") ? 1 : 0;
		if (A[mid] == x) {
			return mid;
		}
		else if (A[mid] == minString(x, A[mid])) {
			return findIndex(A, mid, end, x);
		}
		else if (x == minString(x, A[mid])) {
			return findIndex(A, start, mid, x);
		}
		return -1;
	}
	int findString(vector<string> str, int n, string x) {
		return findIndex(str, 0, n - 1, x);
	}
};

//===========================================================
/*54����һ���Ź�������飬����n����������������������������һ�����ȵ���λ�����磬ԭ����Ϊ[1,2,3,4,5,6]��
������λ5��λ�ü������[6,1,2,3,4,5],���ڶ�����λ������飬��Ҫ����ĳ��Ԫ�ص�λ�á������һ�����Ӷ�Ϊlog������㷨����������
����һ��int����A��Ϊ��λ������飬ͬʱ���������Сn����Ҫ���ҵ�Ԫ�ص�ֵx���뷵��x��λ��(λ�ô��㿪ʼ)����֤������Ԫ�ػ��졣
����������
[6,1,2,3,4,5],6,6
���أ�0*/
class Finder {
public:
	int findLast(vector<int> A, int start, int end) {
		if (end - start <= 1) {
			return (A[start] > A[end]) ? start : end;
		}
		int mid = start + (end - start) / 2;
		if (A[start]  > A[mid]) {
			return findLast(A, start, start + (end - start) / 2);
		}
		else {
			return findLast(A, mid, end);
		}
	}
	int find(vector<int> A, int start, int end, int x) {
		if (end - start <= 1) {
			return (A[start] == x) ? start : end;
		}
		int mid = start + (end - start) / 2;
		if (x == A[mid]) {
			return mid;
		}
		else if (x > A[mid]) {
			return find(A, mid, end, x);
		}
		else {
			return find(A, start, mid, x);
		}
	}
	int findElement(vector<int> A, int n, int x) {
		int last = findLast(A, 0, n - 1);
		if (x > A[n - 1]) {
			return find(A, 0, last, x);
		}
		else {
			return find(A, last, n - 1, x);
		}
		/*���鲻һ����������
		int offset = A[0] - 1;
		return (x - 1) - (offset % n);*/
	}
};

//===========================================================
/*53�����дһ����������һ���ַ�������������򣬽����б�λ�ʺϲ����������ֵ�����С��һ������
����ı�λ��ָ�任����ĸ˳�������ɵ��µĴʻ�������"triangle"��"integral"���Ǳ�λ�ʡ�
����һ��string������str�������Сint n���뷵������ϲ�������顣��֤�ַ�������С�ڵ���20�������СС�ڵ���300��
����������
["ab","ba","abc","cba"]
���أ�["ab","abc"]*/
class SortString {
public:
	vector<string> sortStrings(vector<string> str, int n) {
		//�����Ĳ��Ǻ���������ص���ԭstr�������Ǳ�λ��
		set<string> ans;
		sort(str.begin(), str.end());
		vector<string> result;
		for (int i = 0; i < n; i++) {
			string temp = str[i];
			sort(temp.begin(), temp.end());
			if (ans.count(temp) == 0) {
				ans.insert(temp);
				result.push_back(str[i]);
			}
		}
		return result;
	}
};
//===========================================================
/*52��Լɪ��������һ��������Ȥ�⡣�������������޸�һ�¹�����n����վ��һ�С�
����ͷ��β�����Ǳ�ţ���һ���˱��Ϊ1��Ȼ���ͷ��ʼ��������һ�����α�1��2��1��2...Ȼ�󱨵�2���˳��֡�
���ŵڶ����ٴ���һ�����һ���������˿�ʼ���α�1��2��3��1��2��3...����2��3���˳��֡��Դ�����ֱ��ʣ���Ժ�һ���ˡ�
������Ҫ��ļ�������˵ı�š�����һ��int n��������Ϸ���������뷵�����һ���˵ı��
����������
5
���أ�5*/
class Joseph {
public:
	int kickOut(vector<int> line, int space) {
		if (line.size() == 1) {
			return line[0];
		}
		vector<int> nextRound;
		int index = 0;
		while (index < line.size()) {
			nextRound.push_back(line[index]);
			index += (space + 1);
		}
		nextRound.insert(nextRound.begin(), nextRound.back());
		nextRound.erase(nextRound.end() - 1);
		return kickOut(nextRound, ++space);
	}
	int getResult(int n) {
		vector<int> line;
		for (int i = 0; i < n; i++) {
			line.push_back(i + 1);
		}
		return kickOut(line, 1);
	}
};

//===========================================================
/*51��Լɪ��������һ���ǳ�������Ȥ�⣬����n��������һȦ����˳ʱ����1��ʼ�����Ǳ�š�
Ȼ���ɵ�һ���˿�ʼ����������m���˳��֡�������Ҫ��������һ�����ֵ��˵ı�š�
��������int n��m��������Ϸ���������뷵�����һ�����ֵ��˵ı�š���֤n��mС�ڵ���1000��
����������
5 3
���أ�4*/
class Joseph {
public:
	int getResult(int n, int m) {
		if (n < 2) {
			return n;
		}
		vector<int> in;
		in.resize(n);
		for (int i = 0; i < n; i++) {
			in[i] = i + 1;
		}
		vector<int>::iterator i;
		int index = 0;
		while (in.size() != 1) {
			index = (index + m - 1) % in.size();
			i = in.begin() + index;
			in.erase(i);			
		}	
		return in[0];
	}
};
//===========================================================
/*50����һ�����ӣ�ÿ�����ӿ�Ϊwi����Ϊdi����Ϊhi��������Ҫ�����Ӷ�������������Ϊ��ʹ�����������Ӳ�����
��������ӵĿ�Ⱥͳ��ȱ���С����������ӡ���ʵ��һ������������ܶѳ�����ߵĸ߶ȣ�����ĸ߶ȼ����������������ӵĸ߶�֮�͡�
��������int����w,l,h���ֱ��ʾÿ�����ӿ����͸ߣ�ͬʱ�������ӵ���Ŀn���뷵���ܶѳɵ���ߵĸ߶ȡ���֤nС�ڵ���500��
����������
[1,1,1],[1,1,1],[1,1,1]
���أ�1*/
class Box {
public:
	int getHeight(vector<int> w, vector<int> l, vector<int> h, int n) {
		if (n == 0) return n;
		if (n == 1) return h[0];
		for (int i = 0; i < n; i++) {
			for (int j = n - 1; j > i; --j) {
				if (w[j] > w[j - 1]) {
					swap(w[j], w[j - 1]);
					swap(l[j], l[j - 1]);
					swap(h[j], h[j - 1]);
				}
			}
		}
		int *maxHigh = new int[n + 1]();
		maxHigh[0] = h[0];
		int ans = maxHigh[0];
		for (int i = 1; i < n; i++) {
			maxHigh[i] = h[i];
			int previousMaxHigh = 0;
			for (int j = i - 1; j >= 0; j--) {
				if (w[i] < w[j] && l[i] < l[j]) {
					previousMaxHigh = max(previousMaxHigh, maxHigh[j]);
				}
			}
			maxHigh[i] += previousMaxHigh;
			ans = max(ans, maxHigh[i]);
		}
		return ans;
	}
};

//===========================================================
/*49�������һ���㷨�����������n�ʺ����⡣�����n�ʺ�����ָ��һ��nxn�������Ϸ���n�����ӣ�
ʹ��ÿ��ÿ�к�ÿ���Խ����϶�ֻ��һ�����ӣ�����ڷŵķ�����������һ��int n���뷵�ط���������֤nС�ڵ���15
����������
1
���أ�1*/
class Queens {
public:
	int nQueens(int n) {
		int ans = 0;
		vector<int> chessBorad(n + 1);
		count(chessBorad, 1, n, ans);
		return ans;
	}
	void count(vector<int> &chessBorad, int row, int n, int &ans) {
		if (row > n) {
			ans++;
			return;
		}
		for (int col = 1; col <= n; col++) {
			chessBorad[row] = col;	//row���У��ж�(row,chessBorad[row](== col))λ�ÿɷ������
			if (place(chessBorad, row)) {	//������Է��ã��ͽ�����һ�еķ��ã����ܾͽ�row�����ӷŵ���һ��
				count(chessBorad, row + 1, n, ans);
			}
		}
	}
	bool place(vector<int> &chessBorad, int currentRow) {
		for (int previousRow = 1; previousRow < currentRow; previousRow++) {	//ö���ѷ��õ�ǰpreviousRow�У�����һ���ܷ����
			if (chessBorad[previousRow] == chessBorad[currentRow] || //ͬһ��
				chessBorad[previousRow] - chessBorad[currentRow] == previousRow - currentRow ||	//�ҶԽ���
				chessBorad[previousRow] - chessBorad[currentRow] == currentRow - previousRow) {	//��Խ���
				return false;	//�����ͬһ�У��ҶԽ��ߣ���Խ������ܷ���
			}
		}
		return true;
	}
};

//===========================================================
/*48�����������޵�Ӳ�ң���ֵΪ25�֡�10�֡�5�ֺ�1�֣����д�������n���м��ֱ�ʾ����
����һ��int n���뷵��n���м��ֱ�ʾ������֤nС�ڵ���100000��Ϊ�˷�ֹ������뽫��Mod 1000000007��
����������
6
���أ�2*/
class Coins {
public:
	int countWays(int n) {
		int *dp = new int[n + 1]();
		dp[0] = 1;
		int coin[4] = { 1, 5, 10, 25 };
		for (int i = 0; i < 4; i++) {
			for (int j = coin[i]; j <= n; j++) {
				dp[j] = (dp[j] + dp[j - coin[i]]) % 1000000007;	//����ֵ����ۼ�
			}
		}
		return dp[n];
	}
};
//===========================================================
/*47����һ��nxm������״�ĳ����ﱬ���˺�ˮ����ˮ��(0,0)�ĸ�������������У�������������еĸ�����һЩ������
��ˮֻ����û�н����ĸ����������뷵�غ�ˮ����(n - 1,m - 1)
������ʱ��(��ˮֻ�ܴ�һ���������������ڵĸ����Һ�ˮ��λʱ���ܴ�һ�������������ڸ���)��
����һ������map��ʾ���У�����map[i][j]��ʾ����Ϊ(i,j)�ĸ��ӣ�ֵΪ1����ø����н�����
0����û�н�����ͬʱ��������Ĵ�Сn��m(n��m��С�ڵ���100)���뷵������(n - 1,m - 1)������ʱ�䡣��֤��ˮһ���������յ㡣*/
class Flood {
public:
	/*struct position {
		int row, col;
	};
	int MyfloodFill(vector<vector<int>> map, int n, int m) {
		position offset[4];
		//Ϊ�����·������ȡ�������ϵ�˳��Ѱ��·��
		offset[0].row = 0;	offset[0].col = 1;
		offset[1].row = 1;	offset[1].col = 0;
		offset[2].row = 0;	offset[2].col = -1;
		offset[3].row = -1;	offset[3].col = 0;
		//Ϊ�˲���map��Ե���⴦������Χ���ϲ��ɵ���Χǽ
		vector<vector<int>> maze;
		maze.resize(n + 2);
		for (int i = 0; i < n + 2; i++) {
			maze[i].resize(m + 2, 1);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				maze[i + 1][j + 1] = map[i][j];
			}
		}
		//��ʼ������
		int pattern = 0;
		int lastPattern = 3;
		position here;	here.row = 1;	here.col = 1;
		maze[1][1] = 1;
		stack<position> path;
		//��·��
		while (here.row != n || here.col != m) {
			//��û�����ڣ�����һ��
			int r, c;
			while (pattern <= lastPattern) {
				r = here.row + offset[pattern].row;
				c = here.col + offset[pattern].col;
				if (maze[r][c] == 0) {
					break;
				}
				pattern++;
			}
			if (pattern <= lastPattern) {
				//�ҵ���һ�������ߵķ�ʽ
				maze[r][c] = maze[here.row][here.col] + 1;
				path.push(here);
				here.row = r;
				here.col = c;
				//	maze[r][c] = 1;
				pattern = 0;
			}
			else {
				//��·�����ˣ�����һ��
				position previous = path.top();
				path.pop();
				if (previous.row == here.row) {
					pattern = 2 + previous.col - here.col;
				}
				else {
					pattern = 3 + previous.row - here.row;
				}
				here = previous;
			}
		}
		return maze[n][m] - 1;
	}*/
	//�о���һ���İ��������Լ����㷨����������Ķ�10
	int floodFill(vector<vector<int> > map, int n, int m) {
		// write code here
		if (n == 0 || m == 0 || map[0][0]) return 0;
		queue<int> qRecord;
		int direction[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
		int x, y, next_x, next_y;
		int point;
		int k;
		qRecord.push(0);
		while (!qRecord.empty()) {
			point = qRecord.front();
			qRecord.pop();
			x = point / m;
			y = point%m;
			if ((x + 1) == n && (y + 1) == m) {
				return map[n - 1][m - 1];
			}
			for (k = 0; k<4; k++) {
				next_x = x + direction[k][0];
				next_y = y + direction[k][1];
				if (next_x >= 0 && next_x<n && next_y >= 0 && next_y<m && map[next_x][next_y] == 0) {
					qRecord.push(next_x*m + next_y);
					map[next_x][next_y] = map[x][y] + 1;
				}
			}
		}
	}
};

//===========================================================
/*46������һ���ַ����������һ���㷨���ж����Ƿ�Ϊһ���Ϸ������Ŵ���
����һ���ַ���A�����ĳ���n���뷵��һ��boolֵ�������Ƿ�Ϊһ���Ϸ������Ŵ���
����������
"(()())",6
���أ�true
����������
"()a()()",7
���أ�false
����������
"()(()()",7
���أ�false*/
class Parenthesis {
public:
	bool chkParenthesis(string A, int n) {
		if (A.length() <= 1) {
			return false;
		}
		stack<char> s;
		for (int i = 0; i < A.length(); i++) {
			if (A[i] != '(' && A[i] != ')') return false;
			if (A[i] == '(') {
				s.push('(');
			}
			if (A[i] == ')') {
				if (s.empty()) return false;
				s.pop();
			}
		}
		if (s.empty()) return true;
		return false;
	}
};
//===========================================================
/*45����дһ��������ȷ��ĳ�ַ���������������ϡ�
����һ��string A��һ��int n,�����ַ������䳤�ȣ��뷵�����и��ַ����ַ������У�
��֤�ַ�������С�ڵ���11���ַ������ַ���Ϊ��дӢ���ַ��������е��ַ������ֵ���Ӵ�С����(���ϲ��ظ��ַ���)
����������
"ABC"
���أ�["CBA","CAB","BCA","BAC","ACB","ABC"]*/
class Permutation {
public:
	vector<string> ans;
	void perm(string &A, int begin, int end) {
		if (begin == end) {
			ans.push_back(A);
		}
		for (int i = begin; i <= end; i++) {
			swap(A[i], A[begin]);
			perm(A, begin + 1, end);
			swap(A[i], A[begin]);
		}
	}
	vector<string> getPermutation(string A) {
		return	ans;
	}
};

//===========================================================
/*44�����дһ������������ĳ���ϵ����зǿ��Ӽ���
����һ��int����A������Ĵ�Сint n���뷵��A�����зǿ��Ӽ�����֤A��Ԫ�ظ���С�ڵ���20��
��Ԫ�ػ��졣���Ӽ��ڲ��Ӵ�С����,�Ӽ�֮���ֵ��������򣬼�������
����������
[123,456,789]
���أ�{[789,456,123],[789,456],[789,123],[789],[456 123],[456],[123]}*/
class Subset {
public:
	vector<vector<int>> getSubsets(vector<int> A, int n) {
		vector<vector<int>> ans;
		if (n == 1) {
			ans.push_back(A);
			return ans;
		}
		vector<int> B(A.begin(), A.end() - 1);
		vector<vector<int>> previous = getSubsets(B, n - 1);
		vector<int> temp;
		for (auto i : previous) {
			temp = i;
			temp.insert(temp.begin(), A[n - 1]);
			ans.push_back(temp);
		}
		temp.clear(); temp.push_back(A[n - 1]);
		ans.push_back(temp);
		for (auto i : previous) {
			ans.push_back(i);
		}
		return ans;
	}
};

//===========================================================
/*43��������A[0..n-1]�У�����ν��ħ����������������A[i]=i������һ�����½����У�Ԫ��ֵ������ͬ��
��дһ���������ж�������A���Ƿ����ħ����������˼��һ�ָ��Ӷ�����o(n)�ķ�����
����һ��int����A��int n���������С���뷵��һ��bool�������Ƿ����ħ��������
����������
[1,1,3,4,5]
���أ�true*/

class MagicIndex {
public:
	bool findMagicIndex(vector<int> A, int n) {
		//���ַ�ͬ������
		if (n / 2 == 0 && A[0] != 0) {
			return false;
		}
		if (A[n / 2] == n / 2) {
			return true;
		}
		else if (A[n / 2] > n / 2) {
			vector<int> leftA(A.begin(), A.begin() + n / 2);
			return findMagicIndex(leftA, n / 2);
		}
		else if (A[n / 2] < n / 2) {
			vector<int> rightA(A.begin(), A.begin() + n / 2);
			return findMagicIndex(rightA, n / 2);
		}
		return false;
	}
};

//===========================================================
/*42��������A[0..n-1]�У�����ν��ħ����������������A[i]=i������һ���������飬Ԫ��ֵ������ͬ��
��дһ���������ж�������A���Ƿ����ħ����������˼��һ�ָ��Ӷ�����o(n)�ķ�����
����һ��int����A��int n���������С���뷵��һ��bool�������Ƿ����ħ��������
����������
[1,2,3,4,5]
���أ�false*/
class MagicIndex {
public:
	bool findMagicIndex(vector<int> A, int n) {
		if (n/2 == 0 && A[0] != 0) {
			return false;
		}
		if (A[n/2] == n/2) {
			return true;
		}
		else if (A[n/2] > n/2) {
			vector<int> leftA(A.begin(), A.begin() + n / 2);
			return findMagicIndex(leftA, n / 2);
		}
		else if (A[n/2] < n/2) {
			vector<int> rightA(A.begin(), A.begin() + n / 2);
			return findMagicIndex(rightA, n / 2);
		}
		return false;
	}
};

//===========================================================
/*41����һ��XxY������һ��������ֻ���߸����ֻ�����һ������ߣ�Ҫ�����Ͻ��ߵ����½ǡ�
�����һ���㷨������������ж������߷���ע����ε���������Щ�ϰ����ǲ����ߵġ�
����һ��int[][] map(C++ ��Ϊvector >),��ʾ����ͼ����map[i][j]Ϊ1��˵���õ㲻���ϰ��㣬������Ϊ�ϰ���
�������int x,int y����ʾ����Ĵ�С���뷵�ػ����˴�(0,0)�ߵ�(x - 1,y - 1)���߷�����Ϊ�˷�ֹ�����
�뽫���Mod 1000000007����֤x��y��С�ڵ���50*/
class Robot {
public:
	int countWays(vector<vector<int>> map, int x, int y) {
		vector<vector<int>> dp(x, vector<int>(y, 0));
		for (int i = 0; i < x; i++){
			for (int j = 0; j < y; j++){
				if (map[i][j] != 1) continue;
				if (i == 0 && j == 0) dp[0][0] = 1;
				else if (i != 0 && j == 0) dp[i][0] = dp[i - 1][0];
				else if (i == 0 && j != 0) dp[0][j] = dp[0][j - 1];
				else{
					dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]) % 1000000007;
				}
			}
		}
		return dp[x - 1][y - 1];
	}
};


//===========================================================
/*40����һ��XxY������һ��������ֻ���߸����ֻ�����һ������ߣ�Ҫ�����Ͻ��ߵ����½ǡ�
�����һ���㷨������������ж������߷���
��������������int x,int y���뷵�ػ����˵��߷���Ŀ����֤x��yС�ڵ���12��
����������
2,2
���أ�2*/
class Robot {
public:
	int countWays(int x, int y) {
		if (x == 1 || y == 1)
		{
			return 1;
		}
		if (x == 2 && y == 2)
		{
			return 2;
		}
		return countWays(x - 1, y) + countWays(x, y - 1);
	}
};

//===========================================================
/*39���и�С��������¥�ݣ�¥����n��̨�ף�С��һ�ο�����1�ס�2�ס�3�ס���ʵ��һ��������
����С���ж�������¥�ķ�ʽ��Ϊ�˷�ֹ������뽫���Mod 1000000007
����һ��������int n���뷵��һ������������¥�ķ�ʽ������֤nС�ڵ���100000��
����������
1
���أ�1*/
class GoUpstairs {
public:
	int countWays(int n) {
		long long f[100001] = { 0 };
		f[1] = 1;	f[2] = 2; f[3] = 4;
		if (n <= 3)
		{
			return f[n];
		}
		int index = 3;
		while (index != n)
		{
			index++;
			f[index] = f[index - 1] + f[index - 2] + f[index - 3];
			if (f[index] >= 1000000007)
				f[index] %= 1000000007;
		}
		return f[n];
	}
};

//===========================================================
/*38����һЩ����������ֻ��3��5��7�������һ���㷨���ҳ����еĵ�k������
����һ����int k���뷵�ص�k��������֤kС�ڵ���100��
����������
3
���أ�7*/
class KthNumber {
public:
	int minEle(queue<int> &q3, queue<int> &q5, queue<int> &q7){
		int minElement = min(q3.front(), q5.front());
		minElement = min(minElement, q7.front());
		if (minElement == q3.front()){
			q3.push(minElement * 3);
			q5.push(minElement * 5);
			q7.push(minElement * 7);
			q3.pop();
		}
		else if (minElement == q5.front()){
			q5.push(minElement * 5);
			q7.push(minElement * 7);
			q5.pop();
		}
		else if (minElement == q7.front()){
			q7.push(minElement * 7);
			q7.pop();
		}
		return minElement;
	}
	int findKth(int k) {
		switch (k)
		{
		case 0:
			return 0;
		case 1:
			return 3;
		case 2:
			return 5;
		case 3:
			return 7;
		default:
			break;
		}
		queue<int> q3, q5, q7;
		q3.push(3);
		q5.push(5);
		q7.push(7);
		vector<int> ans{ 1 };
		while (ans.size() != k + 1)
		{
			ans.push_back(minEle(q3, q5, q7));
		}
		return ans[k];
	}
};

//===========================================================
/*37���ڶ�άƽ���ϣ���һЩ�㣬���ҳ������������������ߡ�
����һ���㼯vector p�͵㼯�Ĵ�Сn,û��������ĺ�������ȵ����,�뷵��һ��vector��������������������ֱ�ߵ�б�ʺͽؾࡣ*/
struct Point {
	int x;
	int y;
	Point() :
		x(0), y(0) {
	}
	Point(int xx, int yy) {
		x = xx;
		y = yy;
	}
};
class DenseLine {
public:
	struct Line
	{
		double k;
		double b;
		Line() :k(0), b(0){

		}
		Line(double theK, double theB){
			k = theK;
			b = theB;
		}
		//֮ǰ�ü��α��벻��������ԭ���������map�ļ�ֵ������Լ����ݽṹ����������"<"�����
		//��Ϊmap�ڲ���һ�����������Ҫ������������أ��Ͳ��ܹ��������ͻ������
		bool operator<(const Line& theLine) const{
			if (this->k < theLine.k)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	};
	vector<double> getLine(vector<Point> p, int n) {
		//�õ�һ�����������ֱ�ߣ�map�棬�ٵڶ�����������������û�취����İ취���벻�������ķ�ʽ
		map<Line, int> lines;
		map<Line, int>::iterator it;
		Line temp;
		for (int i = 0; i < n; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				lines[getKB(p[i], p[j])]++;
			}
		}
		it = lines.begin();
		lines[temp] = 1;
		int max = it->second;
		Line mostPonitLine = it->first;
		it++;
		while (it != lines.end())
		{
			if (it->second > max)
			{
				max = it->second;
				mostPonitLine = it->first;
			}
			it++;
		}
		vector<double> ans;
		ans.push_back(mostPonitLine.k);
		ans.push_back(mostPonitLine.b);
		return ans;
	}
	Line getKB(Point a, Point b){
		Line line;
		line.k = (double)(a.y - b.y) / (double)(a.x - b.x);
		line.b = (double)a.y - (double)(line.k*a.x);
		return line;
	}
};

//===========================================================
/*36���ڶ�άƽ���ϣ������������Σ����ҳ�һ��ֱ�ߣ��ܹ��������������ζ԰�֡��ٶ������ε�������������x��ƽ�С�
��������vecotrA��B���ֱ�Ϊ���������ε��ĸ����㡣�뷵��һ��vector�����������ƽ��ֱ�ߵ�б�ʺͽؾ࣬��֤б�ʴ��ڡ�
����������
[(0,0),(0,1),(1,1),(1,0)],[(1,0),(1,1),(2,0),(2,1)]
���أ�[0.0��0.5]*/
struct Point {
	int x;
	int y;
	Point() :
		x(0), y(0) {
	}
	Point(int xx, int yy) {
		x = xx;
		y = yy;
	}
}; 
class Bipartition {
public:
	vector<double> getBipartition(vector<Point> A, vector<Point> B) {
		Point center1, center2;
		for (int i = 0; i < 4; i++){
			center1.x += A[i].x;
			center1.y += A[i].y;
			center2.x += B[i].x;
			center2.y += B[i].y;
		}
		double x1 = (double)center1.x / 4.000;
		double y1 = (double)center1.y / 4.000;
		double x2 = (double)center2.x / 4.000;
		double y2 = (double)center2.y / 4.000;

		double k = (y1 - y2) / (x1 - x2);
		double s = y1 - k*x1;
		vector<double> res;
		res.push_back(k);
		res.push_back(s);
		return res;
	}
};

//===========================================================
/*35�����дһ��������ʵ�������ĳ˷��������ͳ�������(����ĳ�ָ����)��ֻ����ʹ�üӺš�
��������������int a,int b,ͬʱ����һ��int type������������ͣ�1Ϊ��a �� b��0Ϊ��a �� b��-1Ϊ��a �� b��
�뷵�ؼ���Ľ������֤���ݺϷ��ҽ��һ����int��Χ�ڡ�
����������
1,2,1
���أ�2*/
class AddSubstitution {
public:
	int Add(int a, int b){
		if (a == 0)
		{
			return b;
		}
		return Add((a&b) << 1, a^b);
	}
	int Complement(int n){
		return Add(~n, 1);
	}
	int Sub(int a, int b)
	{
		return Add(a, Complement(b));
	}
	int Mul(int a, int b)
	{
		bool signA = true;
		bool signB = true;
		if (a < 0)
		{
			signA = false;
		}
		if (b < 0)
		{
			signB = false;
		}
		int ans = 0;
		for (int i = 1; i != 0; i <<= 1)
		{
			if ((b&i) != 0)
			{
				ans = Add(ans, a);
			}
			a <<= 1;
		}
		return (signA^signB) == 0 ? ans : Complement(ans);
	}
	int Div(int a, int b)
	{
		if (a < b || b == 0)
		{
			return 0;
		}
		bool signA = true;
		bool signB = true;
		if (a < 0)
		{
			signA = false;
		}
		if (b < 0)
		{
			signB = false;
		}
		int ans = 0;
		int copyB = b;
		while (a >= copyB)
		{
			copyB = Add(copyB, b);
			ans++;
		}
		return (signA^signB) == 0 ? ans : Complement(ans);
	}
	int calc(int a, int b, int type) {
		int ans;
		switch (type)
		{
		case -1://����
			ans = Sub(a, b);
			break;
		case 0://����
			ans = Div(a, b);
			break;
		case 1://�˷�
			ans = Mul(a, b);
			break;
		default:
			break;
		}
		return ans;
	}
};


//===========================================================
/*34������ֱ������ϵ�ϵ�����ֱ�ߣ�ȷ��������ֱ�߻᲻���ཻ��
�߶���б�ʺͽؾ����ʽ��������double s1��double s2��double y1��double y2��
�ֱ����ֱ��1��2��б��(��s1,s2)�ͽؾ�(��y1,y2)���뷵��һ��bool���������������ֱ���Ƿ��ཻ��������ֱ���غ�Ҳ��Ϊ�ཻ��
����������
3.14,3.14,1,2
���أ�false*/
class CrossLine {
public:
	bool checkCrossLine(double s1, double s2, double y1, double y2) {
		if (s1 != s2)
		{
			return true;
		}
		else
		{
			if (y1 == y2)
			{
				return true;
			}
		}
		return false;
	}
};

//===========================================================
/*33����n������Ķ��������nֻ���ϣ���Щ����ͬʱ��ʼ���Ŷ���εı����У�
�������Щ������ײ�ĸ��ʡ�(�������ײ��ָ����������ֻ���ϻ���ײ)
����һ��int n(3<=n<=10000)������n���κ�nֻ���ϣ��뷵��һ��double��Ϊ��ײ�ĸ��ʡ�
����������
3
���أ�0.75*/
class Ants {
public:
	double antsCollision(int n) {
		double ans = 1.0;
		for (int i = 2; i <= n; i++)
		{
			ans *= 0.5;
		}
		return (1 - ans);
	}
};

//===========================================================
/*32����һ����ɫ��Ļ������һά�����У����������ÿ��Ԫ�ش���������8λ�����ص�ֵ����ʵ��һ��������
����x����y������Ϳ����ɫ(���ر�Ŵ��㿪ʼ)�������Ծ���ʹ�����İ취��
������ʾ��Ļ������screen(�����е�ÿ��Ԫ�ش���������8�����أ�
�Ҵ������ҵ����طֱ��ӦԪ�صĶ����ƵĴӵ͵���λ)���Լ�int x,int y��������������������֤�������ݺϷ���
�뷵��Ϳɫ����µ���Ļ���顣
����������
[0,0,0,0,0,0],0,47
���أ�[255,255,255,255,255,255]*/
class Render {
public:
	vector<int> renderPixel(vector<int> screen, int x, int y) {
		for (int i = x; i <= y; i++){
			int index = i / 8;
			int offset = i % 8;
			screen[index] |= (1 << offset);
		}
		return screen;
	}
};


//===========================================================
/*31������A������0��n������������������ȱʧ��һ��������������⣬�����趨���ƣ�
ʹ��һ�β����޷�ȡ������number��ĳ���������������ݡ�
Ψһ�Ŀ��ò�����ѯ�������е�i��Ԫ�صĶ����Ƶĵ�jλ(���λΪ��0λ)��
�ò�����ʱ�临�Ӷ�Ϊ������������㷨����O(n)��ʱ�����ҵ��������
����һ������number��������ʣ�µ�������С�������еĶ����Ƹ�λ��ֵ��
��A[0][1]��ʾʣ�µĵڶ����������ƴӵ͵��ߵĵڶ�λ��ͬʱ����һ��int n���������⡣�뷵��ȱʧ������
����������
[[0],[0,1]]
���أ�1*/
class Finder {
public:
	/*�򵥵�˵����Ŀ������A��һ��Ԫ�ر�ʾһ����������A[0]��A[n-1]�ֱ����n��������
	��A[m]��ʾ����a,���m�еĵ�x�б�ʾa�Ķ����Ʊ�ʾʱ�ӵ͵��ߵĵ�xλ��������A[0]Ϊ[0]��
	����1λΪ0����ʾ����0��A[1]=[0,1],����1λΪ0����2λΪ1����ʾ����2�����ȱʧ������1��
	�����������������������A[5],��Ӧ��Ϊ[1,0,1]���������ơ�*/
	//˼·���Ǽ���������У�0���ǲ���0101����ģ���Ҫ������β����
	int findMissing(vector<vector<int>> numbers, int n) {
		if (numbers.size() != n || n < 0)
		{
			return -1;
		}
		for (int i = 0; i < numbers.size() - 1; i++)
		{
			if ((numbers[i][0] ^ numbers[i + 1][0]) != 1)
				return i + 1;
		}
		return (numbers[0].size() == 1 && numbers[0][0] == 0) ? n : 0;
	}
};

//===========================================================
/*30�����д���򽻻�һ�����Ķ����Ƶ�����λ��ż��λ����ʹ��Խ�ٵ�ָ��Խ�ã�
����һ��int x���뷵�ؽ��������int��
����������
10
���أ�5*/
class Exchange {
public:
	int exchangeOddEven(int x) {
		return ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1);
	}
};

//===========================================================
/*29����дһ��������ȷ����Ҫ�ı伸��λ�����ܽ�����Aת�������B��
������������int A��int B���뷵����Ҫ�ı����λ������
����������
10,5
���أ�4*/
class Transform {
public:
	int calcCost(int A, int B) {
		int temp = A^B;
		int ans = 0;
		while (temp != 0)
		{
			if ((temp & 1) == 1)
			{
				ans++;
			}
			temp >>= 1;
		}
		return ans;
	}
};

//===========================================================
/*28����һ�������������ҳ�������Ʊ�ʾ��1�ĸ�����ͬ���Ҵ�С��ӽ�������������(һ���Դ�һ����С)
����������int x���뷵��һ��vector�������������������С����ǰ������֤�𰸴��ڡ�
����������
2
���أ�[1,4]*/
class CloseNumber {
public:
	vector<int> getCloseNumber(int x) {
		vector<int> ans;
		int large = x, small = x, temp = x, c0 = 0, c1 = 0, p;
		//Ϊ������ӽ���С�����滻����β1�ĵ�һ��1Ϊ0��λ��Ϊp��Ȼ�����p֮ǰ��λ���������������1��Ϊ����ӽ���
		while ((temp & 1) == 1)	//λ����һ��Ҫ��������������Ҫ��Ȼ������ȼ���������ܻ���ɲ���Ԥ�Ƶĺ��
		{
			c1++;
			temp >>= 1;
		}
		while (((temp & 1) == 0) && (temp != 0))
		{
			c0++;
			temp >>= 1;
		}
		p = c0 + c1;
		if (p == 31 || p == 0)
		{
			ans.push_back(-1);
		}
		small &= ((~0) << (p + 1));	//~0Ϊȫ1����
		small |= (((1 << (c1 + 1)) - 1) << (c0 - 1));
		ans.push_back(small);
		//Ϊ������ӽ��Ĵ������滻����β0�ĵ�һ��0Ϊ1��λ��Ϊp��Ȼ�����p֮ǰ��λ���������������0��Ϊ����ӽ���
		c0 = c1 = 0; temp = x;
		while (((temp & 1) == 0) && (temp != 0))
		{
			c0++;
			temp >>= 1;
		}
		while ((temp & 1) == 1)
		{
			c1++;
			temp >>= 1;
		}
		p = c1 + c0;
		if (p == 31 || p == 0)
		{
			ans.push_back(-1);
			return ans;
		}
		large |= (1 << p);
		large &= ~((1 << p) - 1);
		large |= (1 << (c1 - 1)) - 1;
		ans.push_back(large);

		return ans;
	}
};

//===========================================================
/*27����һ������0��1֮���ʵ��������Ϊdouble���������Ķ����Ʊ�ʾ��
����������޷���ȷ����32λ���ڵĶ����Ʊ�ʾ�����ء�Error����
����һ��double num����ʾ0��1��ʵ�����뷵��һ��string����������Ķ����Ʊ�ʾ���ߡ�Error����
����������
0.625
���أ�0.101*/
class BinDecimal {
public:
	string printBin(double num) {
		string ans = "0.";
		while (num != 1 || ans.length() >= 34)
		{
			ans += to_string((int)(num * 2.0));
			num = num*2.0 > 1 ? (num * 2.0 - (int)num) : num;
		}
		if (ans.length() >= 34)
		{
			return "Error";
		}
		return ans;
	}
};

//===========================================================
/*26��������32λ����n��m�����д�㷨��m�Ķ�������λ���뵽n�Ķ����Ƶĵ�j����iλ,
���ж����Ƶ�λ���ӵ�λ������λ����0��ʼ��
����������int n��int m��ͬʱ����int j��int i�����������������뷵�ز����������
��֤n�ĵ�j����iλ��Ϊ�㣬��m�Ķ�����λ��С�ڵ���i-j+1��
����������
1024��19��2��6
���أ�1100*/
class BinInsert {
public:
	int binInsert(int n, int m, int j, int i) {
		int index = j;
		int add = 0;
		while (m != 0 && index <= i)
		{
			add += (m % 2) == 1 ? pow(2, index) : 0;
			m /= 2;
			index++;
		}
		return (n + add);
	}
};

//===========================================================
/*25������һ�Ŷ�������һ����������ӡ���������н��ֵ�ĺ�Ϊ��������������·����
·������Ϊ�����ĸ���㿪ʼ����һֱ��Ҷ����������Ľ���γ�һ��·����*/
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
	val(x), left(NULL), right(NULL) {
	}
};
class Solution {
public:
	vector<int> path;
	vector<vector<int>> ans;
	vector<vector<int>> FindPath(TreeNode* root, int expectNumber) {
		if (root == NULL)
		{
			return ans;
		}
		path.push_back(root->val);
		if (0 == expectNumber - root->val && root->left == NULL && root->right == NULL)
		{
			ans.push_back(path);
		}
		FindPath(root->left, expectNumber - root->val);
		FindPath(root->right, expectNumber - root->val);
		path.pop_back();
		return ans;
	}
};

//===========================================================
/*24����һ���������������������㰴�����һ��һ��ش����������α�ţ��������Ϊ1��
�������������a��b�������һ���㷨�����a��b�������������ȵı�š�
��������int a,b��Ϊ�������ı�š��뷵��a��b������������ȵı�š�ע�������㱾��Ҳ����Ϊ�������ȡ�
����������
2��3
���أ�1*/
class LCA {
public:
	int getLCA(int a, int b) {
		int smaller = min(a, b);
		int larger = max(a, b);
		while (smaller != larger)
		{
			while (larger > smaller && smaller != larger)
			{
				larger /= 2;
			}
			while (larger < smaller && smaller != larger)
			{
				smaller /= 2;
			}
		}
		return smaller;
	}
};

//===========================================================
/*23�������һ���㷨��Ѱ�Ҷ�������ָ��������һ����㣨����������ĺ�̣���
�������ĸ����ָ��TreeNode* root�ͽ���ֵint p���뷵��ֵΪp�Ľ��ĺ�̽���ֵ��
��֤����ֵ���ڵ�����С�ڵ���100000��û���ظ�ֵ���������ں�̷���-1��*/
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {
	}
};
class Successor {
public:
	int findSucc(TreeNode* root, int p) {
		bool sign = 0;
		return findSucc1(root, p, sign);
	}
	int findSucc1(TreeNode* root, int p, bool &sign)
	{
		if (root == NULL)
			return -1;
		int left = findSucc1(root->left, p, sign);
		if (left != -1)
			return left;
		if (sign == true)
			return root->val;
		if (root->val == p)
			sign = true;
		return findSucc1(root->right, p, sign);
	}
};

//===========================================================
/*22����ʵ��һ�����������һ�ö������Ƿ�Ϊ�����������
�������ĸ����ָ��TreeNode* root���뷵��һ��bool����������Ƿ�Ϊ�����������*/
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {
	}
};
class Checker {
public:
	bool checkLeft(TreeNode* root, int valRoot){
		if (root == NULL)
		{
			return false;
		}
		TreeNode* currentNode;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty())
		{
			currentNode = q.front();
			q.pop();
			if (currentNode->left)
			{
				if (currentNode->left->val > currentNode->val || currentNode->left->val > valRoot)
				{
					return false;
				}
				q.push(currentNode->left);
			}
			if (currentNode->right)
			{
				if (currentNode->right->val < currentNode->val || currentNode->right->val > valRoot)
				{
					return false;
				}
				q.push(currentNode->right);
			}
		}
		return true;
	}
	bool checkRight(TreeNode* root, int valRoot){
		if (root == NULL)
		{
			return false;
		}
		TreeNode* currentNode;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty())
		{
			currentNode = q.front();
			q.pop();
			if (currentNode->left)
			{
				if (currentNode->left->val > currentNode->val || currentNode->left->val < valRoot)
				{
					return false;
				}
				q.push(currentNode->left);
			}
			if (currentNode->right)
			{
				if (currentNode->right->val < currentNode->val || currentNode->right->val < valRoot)
				{
					return false;
				}
				q.push(currentNode->right);
			}
		}
		return true;
	}
	bool checkBST(TreeNode* root) {
		if (root == NULL)
		{
			return false;
		}
		TreeNode* currentNode = root;
		bool ans;
		int valRoot = root->val;
		if (currentNode->left != NULL)
		{
			if (currentNode->left->val > currentNode->val)
			{
				return false;
			}
			ans = checkLeft(currentNode->left, valRoot);
		}
		if (currentNode->right != NULL)
		{
			if (currentNode->right->val < currentNode->val)
			{
				return false;
			}
			ans = checkRight(currentNode->right, valRoot);
		}
		return ans;
	}
};

//===========================================================
/*21������һ�ö������������һ���㷨����������ĳһ��������н�������
�����������ĸ����ָ��TreeNode* root���Լ������Ͻ�����ȣ��뷵��һ������ListNode��
�������������н���ֵ���밴���ϴ������ҵ�˳�����ӣ���֤��Ȳ��������ĸ߶ȣ�
���Ͻ���ֵΪ�Ǹ������Ҳ�����100000��*/
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
		val(x), left(NULL), right(NULL) {
	}
}; 
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class TreeLevel {
public:
	ListNode* getTreeLevel(TreeNode* root, int dep) {
		if (dep <= 0 || root == NULL)
		{
			return NULL;
		}
		queue<TreeNode*> currentFloor;
		currentFloor.push(root);
		queue<TreeNode*> nextFloor;
		int currentDep = 1;
		TreeNode* temp;
		while (currentDep != dep)
		{
			temp = currentFloor.front();
			currentFloor.pop();
			if (temp->left)
			{
				nextFloor.push(temp->left);
			}
			if (temp->right)
			{
				nextFloor.push(temp->right);
			}
			if (currentFloor.empty())
			{
				currentDep++;
				while (!nextFloor.empty())
				{
					currentFloor.push(nextFloor.front());
					nextFloor.pop();
				}
			}
		}
		ListNode* head = new ListNode(currentFloor.front()->val);
		currentFloor.pop();
		ListNode* currentNode = head;
		while (!currentFloor.empty())
		{
			currentNode->next = new ListNode(currentFloor.front()->val);
			currentFloor.pop();
			currentNode = currentNode->next;
		}
		currentNode->next = NULL;
		return head;
	}
};
//===========================================================
/*20������һ��Ԫ�ظ�����ͬ�Ұ��������е��������У����дһ���㷨������һ�ø߶���С�Ķ����������
����һ����������int[] vals,�뷵�ش����Ķ���������ĸ߶ȡ�*/
class MinimalBST {
public:
	int maxHigh(vector<int> vals, int start, int end){
		if (end <= start)
		{
			return 1;
		}
		int mid = (start + end) / 2;
		int leftHigh = maxHigh(vals, start, mid - 1) + 1;
		int rightHigh = maxHigh(vals, mid + 1, end) + 1;
		return max(leftHigh, rightHigh);
	}
	int buildMinimalBST(vector<int> vals) {
		if (vals.size() <= 2)
		{
			return vals.size();
		}
		return maxHigh(vals, 0, vals.size() - 1);
	}
};

//===========================================================
/*19������һ������ͼ����ʵ��һ���㷨���ҳ�����֮���Ƿ����һ��·����
����ͼ�е���������ָ��UndirectedGraphNode* a,UndirectedGraphNode* b
(�벻Ҫ�����������ͣ�ͼ������ͼ),�뷵��һ��bool����������֮���Ƿ����һ��·��(a��b��b��a)��*/
struct UndirectedGraphNode {
	int label;
	vector<struct UndirectedGraphNode *> neighbors;
	UndirectedGraphNode(int x) : label(x) {}
};
class Path {
public:
	bool checkPath(UndirectedGraphNode* a, UndirectedGraphNode* b) {
		return findPath(a, b) || findPath(b, a);
	}
	bool findPath(UndirectedGraphNode* a, UndirectedGraphNode* b){
		if (a == NULL || b == NULL)
		{
			return false;
		}
		if (a == b)
		{
			return true;
		}
		queue<UndirectedGraphNode*> q;
		q.push(a);
		UndirectedGraphNode* currentNode;
		while (!q.empty())
		{
			currentNode = q.front();
			currentNode->label = 1;
			for (int i = 0; i < currentNode->neighbors.size(); i++)
			{
				if ((currentNode->neighbors)[i] == b)
				{
					return true;
				}
				if ((currentNode->neighbors)[i] != NULL && (currentNode->neighbors)[i]->label != 1)
				{
					q.push((currentNode->neighbors)[i]);
				}
			}
			q.pop();
		}
		return false;
	}
};

//===========================================================
/*18��ʵ��һ�����������������Ƿ�ƽ�⣬ƽ��Ķ������£�
�������е�����һ����㣬�����������ĸ߶Ȳ����1��
����ָ����������ָ��TreeNode* root���뷵��һ��bool������������Ƿ�ƽ�⡣*/
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
	val(x), left(NULL), right(NULL) {
	}
};
class Balance {
public:
	bool isBalance(TreeNode* root) {
		if (root == NULL)
		{
			return false;
		}
		queue<TreeNode*> q;
		TreeNode* currentNode;
		currentNode = root;
		while (currentNode != NULL)
		{
			if (currentNode->left != NULL)	//�������������
			{
				q.push(currentNode->left);
			}
			else  //�����������
			{
				if (currentNode->right != NULL)	//����������
				{
					if (currentNode->right->left != NULL || currentNode->right->right != NULL)	//������������������Ͳ�ƽ��
					{
						return false;
					}
				}
			}
			if (currentNode->right != NULL)	//�������������
			{
				q.push(currentNode->right);
			}
			else  //�����������
			{
				if (currentNode->left != NULL)	//������������
				{
					if (currentNode->left->left != NULL || currentNode->left->right != NULL)	//��������������������ƽ��
					{
						return false;
					}
				}
			}
			if (!q.empty())
			{
				currentNode = q.front();	//����˶϶������������һ���ڵ�
				q.pop();
			}
			else
			{
				currentNode = NULL;
			}
		}
		return true;
	}
};

//===========================================================
/*17���мҶ���������ֻ����è�͹��������������������������������������ʽ��
��һ��Ϊֱ���������ж�������������������ģ��ڶ���Ϊѡ�������Ķ������ͣ�è�򹷣������������ֶ�������������������ġ�
����һ����������int[][2] ope(C++��Ϊvector<vector<int>>)���������¼���
����һ��Ԫ��Ϊ1��������ж���������������ڶ���Ԫ��Ϊ����ı�ţ�������������������è��
����һ��Ԫ��Ϊ2�������������������ڶ���Ԫ����Ϊ0�����ȡ��һ��������ʽ����Ϊ1����ָ����������
��Ϊ-1��ָ������è���밴˳�򷵻����������С������ֲ��Ϸ��Ĳ�������û�п��Է�������Ҫ��Ķ������������������ԡ�
����������
[[1,1],[1,-1],[2,0],[2,-1]]
���أ�[1,-1]*/
class CatDogAsylum {
public:
	vector<int> asylum(vector<vector<int> > ope) {
		vector<int> ans; 
		int flag;
		int len = ope.size();
		for (int i = 0; i<len; i++)
		{
			if (ope[i][0] == 2)
			{
				flag = 0;
				if (ope[i][1] == 0)//���յ�һ�ַ�ʽѡ����; 
				{
					for (int j = 0; j<i&&flag == 0; j++)
					{
						if (ope[j][0] == 1)//����Ķ���; 
						{
							ans.push_back(ope[j][1]);
							ope[j][0] = -1;//��ʾ�Ѿ�ѡ��; 
							flag = 1;
						}
					}
				}
				else  if (ope[i][1] == 1)//ȡ��һ����; 
				{
					for (int j = 0; j<i&&flag == 0; j++)
					{
						if (ope[j][0] == 1 && ope[j][1] >= 0)
						{
							ans.push_back(ope[j][1]);
							ope[j][0] = -1;//��ʾ�Ѿ�ѡ��; 
							flag = 1;
						}
					}

				}
				else//ȡ��һ��è; 
				{
					for (int j = 0; j<i&&flag == 0; j++)
					{
						if (ope[j][0] == 1 && ope[j][1]<0)
						{
							ans.push_back(ope[j][1]);
							ope[j][0] = -1;//��ʾ�Ѿ�ѡ��; 
							flag = 1;
						}
					}
				}
			}
		}
		return ans;
	}
};

//===========================================================
/*16�����дһ�����򣬰������ջ�������򣨼����Ԫ��λ��ջ������
Ҫ�����ֻ��ʹ��һ�������ջ�����ʱ���ݣ������ý�Ԫ�ظ��Ƶ�������ݽṹ�С�
����һ��int[] numbers(C++��Ϊvector&ltint>)�����е�һ��Ԫ��Ϊջ�����뷵��������ջ��
��ע������һ��ջ����ζ�������������ֻ�ܷ��ʵ���һ��Ԫ�ء�
����������
[1,2,3,4,5]
���أ�[5,4,3,2,1]*/
class TwoStacks {
public:
	vector<int> twoStacksSort(vector<int> numbers) {
		sort(numbers.begin(), numbers.end());
		stack<int> s;
		for (int i = 0; i < numbers.size(); i++)
		{
			s.push(numbers[i]);
		}
		for (int i = 0; i < numbers.size(); i++)
		{
			numbers[i] = s.top();
			s.pop();
		}
		return numbers;
	}
};

//===========================================================
/*15��������ջ��ʵ��һ�����У���ɶ��е�Push��Pop������ �����е�Ԫ��Ϊint���͡�*/
class Solution
{
public:
	void push(int node) {
		stack1.push(node);
	}

	int pop() {
		while(!stack1.empty())
		{
			stack2.push(stack1.top());
			stack1.pop();
		}
		int top =  stack2.top();
		stack2.pop();
		while (!stack2.empty())
		{
			stack1.push(stack2.top());
			stack2.pop();
		}
		return top;
	}

private:
	stack<int> stack1;
	stack<int> stack2;
};

//===========================================================
/*14����ʵ��һ�����ݽṹSetOfStacks���ɶ��ջ��ɣ�����ÿ��ջ�Ĵ�СΪsize��
��ǰһ��ջ����ʱ���½�һ��ջ�������ݽṹӦ֧������ͨջ��ͬ��push��pop������
����һ����������int[][2] ope(C++Ϊvector<vector<int>>)��
ÿ�������ĵ�һ��������������ͣ���Ϊ1����Ϊpush������
��һ����ΪӦpush�����֣���Ϊ2����Ϊpop��������һ���������塣
�뷵��һ��int[][](C++Ϊvector<vector<int>>)��Ϊ������в������SetOfStacks��
˳��ӦΪ���µ��ϣ�Ĭ�ϳ�ʼ��SetOfStacksΪ�ա���֤���ݺϷ���*/
class SetOfStacks {
public:
	vector<vector<int>> setOfStacks(vector<vector<int>> ope, int size) {
		vector<vector<int> > st;
		vector<int> temp;
		for (int i = 0; i<ope.size(); i++){
			if (ope[i][0] == 1){//��ջ
				if (temp.size() == size){//ջ�������½�һ��ջ������ջ
					st.push_back(temp);
					temp.clear();
					temp.push_back(ope[i][1]);
				}
				else
					temp.push_back(ope[i][1]);
			}
			if (ope[i][0] == 2){//��ջ
				if (temp.size() != 0)//��ǰջ��Ϊ�գ�ֱ�ӳ�ջ
					temp.pop_back();
				else if (st.size() != 0){//��ǰջΪ�գ������һ��ջ��
					temp = st[st.size() - 1];
					temp.pop_back();
					st.pop_back();
				}
			}
		}
		if (temp.size() != 0){
			st.push_back(temp);
		}
		return st;
	}
};

//===========================================================
/*13�����дһ����������������Ƿ�Ϊ���ġ�
����һ������ListNode* pHead���뷵��һ��bool�����������Ƿ�Ϊ���ġ�
����������
{1,2,3,2,1}
���أ�true
{1,2,3,2,3}
���أ�false*/
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
}; 
class Palindrome {
public:
	bool isPalindrome(ListNode* pHead) {
		vector<int> ans;
		vector<int> temp;
		while (pHead != NULL)
		{
			ans.push_back(pHead->val);
			pHead = pHead->next;
		}
		temp = ans;
		reverse(temp.begin(), temp.end());
		for (int i = 0; i < ans.size(); i++)
		{
			if (ans[i] != temp[i])
			{
				return false;
			}
		}
		return true;
	}
};

//===========================================================
/*12���������������ʾ��������ÿ��������һ����λ����Щ��λ�Ƿ����ŵģ�
Ҳ���Ǹ�λ����������ײ�����д������������������ͣ�����������ʽ���ؽ����
������������ListNode* A��ListNode* B���뷵��A+B�Ľ��(ListNode*)��
����������
{1,2,3},{3,2,1}
���أ�{4,4,4}*/
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
}; 
class Plus {
public:
	ListNode* plusAB(ListNode* a, ListNode* b) {
		int carry = 0;
		int add;
		int aVal;
		int bVal;
		ListNode* sum = new ListNode(0);
		ListNode* head = sum;
		while (a != NULL || b != NULL || carry == 1)
		{
			aVal = (a != NULL ? a->val : 0);
			bVal = (b != NULL ? b->val : 0);
			sum->next = new ListNode(0);
			sum = sum->next;
			add = aVal + bVal + carry;
			carry = 0;
			if (add >= 10)
			{
				add %= 10;
				carry++;
			}
			sum->val = add;
			a = (a != NULL ? a->next : NULL);
			b = (b != NULL ? b->next : NULL);
		}
		return head->next;
	}
};
//===========================================================
/*11����д���룬�Ը���ֵxΪ��׼������ָ�������֣�����С��x�Ľ�����ڴ��ڻ����x�Ľ��֮ǰ
����һ�������ͷָ�� ListNode* pHead���뷵���������к�������ͷָ�롣ע�⣺�ָ��Ժ󱣳�ԭ��������˳�򲻱䡣*/
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Partition {
public:
	ListNode* partition(ListNode* pHead, int x) {
		if (pHead == NULL)
		{
			return NULL;
		}
		ListNode* small = new ListNode(0);
		ListNode* large = new ListNode(0);
		ListNode* smallHead = small;
		ListNode* largeHead = large;
		while (pHead){
			if (pHead->val<x){
				small->next = pHead;
				small = small->next;
			}
			else{
				large->next = pHead;
				large = large->next;
			}

			pHead = pHead->next;

		}
		large->next = NULL;
		small->next = largeHead->next;
		return smallHead->next;
	}
};

//===========================================================
/*10��ʵ��һ���㷨��ɾ�����������м��ĳ����㣬�ٶ���ֻ�ܷ��ʸý�㡣
������ɾ���Ľڵ㣬��ִ��ɾ�����������ýڵ�Ϊβ�ڵ㣬����false�����򷵻�true*/
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Remove {
public:
	bool removeNode(ListNode* pNode) {
		if (pNode->next == NULL)
		{
			return false;
		}
		ListNode* nextNode = pNode->next->next;
		pNode->val = pNode->next->val;
		pNode->next = nextNode;
		return true;
	}
};

//===========================================================
/*9������һ����������������е�����k����㡣*/
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
	val(x), next(NULL) {
	}
};
class Solution {
public:
	ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
		ListNode* fast = pListHead;
		ListNode* slow = pListHead;
		if (pListHead == NULL)
		{
			return NULL;
		}
		int num = 1;	//��Ϊ��������һ��
		for (int i = 0; i < k; i++)
		{
			fast = fast->next;
			if (fast == NULL)	//�����ֹ�����Ƕ���k���ڵ㣬�������k���ı�����Ҳ�Ƕ�k>num�ı���
			{
				break;
			}
			num++;
		}
		if (k > num)	//���԰�����k���ڽڵ��������
		{
			return NULL;
		}
		while (fast != NULL)
		{
			fast = fast->next;
			slow = slow->next;
		}
		return slow;
	}
};

//===========================================================
/*8���ٶ����Ƕ�֪���ǳ���Ч���㷨�����һ�������Ƿ�Ϊ�����ַ������Ӵ���
�뽫����㷨��д��һ�����������������ַ���s1��s2�����д������s2�Ƿ�Ϊs1��ת���ɣ�Ҫ��ֻ�ܵ���һ�μ���Ӵ��ĺ�����
���������ַ���s1,s2,�뷵��boolֵ����s2�Ƿ���s1��ת���ɡ��ַ������ַ�ΪӢ����ĸ�Ϳո����ִ�Сд���ַ�������С�ڵ���1000��
����������
"Hello world","worldhello "
���أ�false
"waterbottle","erbottlewat"
���أ�true*/
class ReverseEqual {
public:
	bool checkReverseEqual(string s1, string s2) {
		if (s1.length() != s2.length())
			return false;
		string temp = s2;
		temp += s2;
		string::size_type start = temp.find(s1);
		if (start == string::npos)
			return false;
		else
		{
			for (int i = 0; i < s1.length(); i++)
			{
				if (temp[(start+s1.length()+1+i) % s1.length()] != s1[i])
				{
					return false;
				}
			}
		}
		return true;
	}
};

//===========================================================
/*7�����дһ���㷨����N�׷�����ĳ��Ԫ��Ϊ0���������ڵ����������㡣
����һ��N�׷���int[][](C++��Ϊvector>)mat�;���Ľ���n��
�뷵����ɲ������int[][]����(C++��Ϊvector>)����֤nС�ڵ���300�������е�Ԫ��Ϊint��Χ�ڡ�
����������
[[1,2,3],[0,1,2],[0,0,1]]
���أ�[[0,0,3],[0,0,0],[0,0,0]]*/
class Clearer {
public:
	vector<vector<int> > clearZero(vector<vector<int> > mat, int n) {
		int *row = new int[n];
		int *col = new int[n];
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (mat[i][j] == 0)
				{
					row[i] = 1;
					col[j] = 1;
				}
			}
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (row[i] || col[j])
				{
					mat[i][j] = 0;
				}
			}
		}
		return mat;
	}
};

//===========================================================
/*6����һ����NxN�����ʾ��ͼ������ÿ��������һ��int��ʾ�����дһ���㷨��
�ڲ�ռ�ö����ڴ�ռ�������(����ʹ�û������)����ͼ��˳ʱ����ת90�ȡ�
����һ��NxN�ľ��󣬺;���Ľ���N,�뷵����ת���NxN����,��֤NС�ڵ���500��ͼ��Ԫ��С�ڵ���256��
����������
[[1,2,3],[4,5,6],[7,8,9]],3
���أ�[[7,4,1],[8,5,2],[9,6,3]]*/
class Transform {
public:
	vector<vector<int>> transformImage(vector<vector<int>> mat, int n) {
		if (n <= 1)
		{
			return mat;
		}
		//��ת��,����������
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < i; j++)
			{
				swap(mat[i][j], mat[j][i]);
			}
		}
		//��������
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n/2; j++)
			{
				swap(mat[i][j], mat[i][n - j - 1]);
			}
		}
		return mat;
	}
};

//===========================================================
/*5�������ַ��ظ����ֵĴ�������дһ��������ʵ�ֻ������ַ���ѹ�����ܡ�
���磬�ַ�����aabcccccaaa����ѹ�����ɡ�a2b1c5a3������ѹ������ַ���û�б�̣��򷵻�ԭ�ȵ��ַ�����
����һ��string iniStringΪ��ѹ���Ĵ�(����С�ڵ���10000)����֤�����ַ����ɴ�СдӢ����ĸ��ɣ�
����һ��string��Ϊ�����ѹ�����δ�仯�Ĵ���
��������
"aabcccccaaa"
���أ�"a2b1c5a3"
"welcometonowcoderrrrr"
���أ�"welcometonowcoderrrrr"*/
class Zipper {
public:
	string zipString(string iniString) {
		int length = iniString.length();
		stack<char> s;
		string ans = "";
		s.push(iniString[0]);
		for (int i = 1; i < length; i++)
		{
			if (iniString[i] != s.top())
			{
				ans += s.top();
				ans += to_string(s.size());
				while (!s.empty())
				{
					s.pop();
				}
			}
			s.push(iniString[i]);
		}
		ans += s.top();
		ans += to_string(s.size());
		if (ans.length() < length)
		{
			return ans;
		}
		else
		{
			return iniString;
		}
	}
};

//===========================================================
/*4�����дһ�����������ַ����еĿո�ȫ���滻Ϊ��%20�����ٶ����ַ������㹻�Ŀռ����������ַ���
����֪���ַ�������ʵ����(С�ڵ���1000)��ͬʱ��֤�ַ����ɴ�Сд��Ӣ����ĸ��ɡ�
����һ��string iniString Ϊԭʼ�Ĵ����Լ����ĳ��� int len, �����滻���string��
����������
"Mr John Smith��,13
���أ�"Mr%20John%20Smith"
��Hello  World��,12
���أ���Hello%20%20World��*/
class Replacement {
public:
	string replaceSpace(string iniString, int length) {
		int space = 0;
		int len = iniString.length();
		if (len == 0)
		{
			return iniString;
		}
		for (int i = 0; i < len; i++)
		{
			if (iniString[i] == ' ')
			{
				space++;
			}
		}
		if (len > length)
		{
			return iniString;
		}
		int newLenght = len + space * 2;
		iniString.resize(newLenght);
		for (int i = len-1; i >= 0; i--)
		{
			if (iniString[i] == ' ')
			{
				iniString[newLenght--] = '0';
				iniString[newLenght--] = '2';
				iniString[newLenght--] = '%';
			}
			else
			{
				iniString[newLenght--] = iniString[i];
			}
		}
		return iniString;
	}
};

//===========================================================
/*3�����������ַ��������д����ȷ������һ���ַ������ַ��������к��ܷ�����һ���ַ�����
����涨��СдΪ��ͬ�ַ����ҿ����ַ����ص�ո�
����һ��string stringA��һ��string stringB���뷵��һ��bool�����������Ƿ��������к����ͬ��
��֤�����ĳ��ȶ�С�ڵ���5000��
����������
"This is nowcoder","is This nowcoder"
���أ�true
"Here you are","Are you here"
���أ�false*/
class Same {
public:
	bool checkSam(string stringA, string stringB) {
		int sizeA = stringA.length();
		int sizeB = stringB.length();
		if (sizeA != sizeB)
		{
			return false;
		}
		int hashA[256] = { 0 };
		int hashB[256] = { 0 };
		for (int i = 0; i < sizeA; i++)
		{
			hashA[stringA[i]]++;
			hashB[stringB[i]]++;
		}
		for (int i = 0; i < 256; i++)	
		{
			if (hashA[i] != hashB[i])
			{
				return false;
			}
		}
		return true;

		/*�����ǵ������ţ���������˵���ַ��������ţ��Ǿͷǳ����ˣ�hash��Ϳ�����
		string temp = "";
		vector<string> wordA;
		vector<string> wordB;
		for (int i = 0; i < stringA.length(); i++)
		{
			if (stringA[i] == ' ')
			{
				wordA.push_back(temp);
				temp = "";
			}		
			else
			{
				temp += stringA[i];
			}			
		}
		wordA.push_back(temp);
		temp = "";

		for (int i = 0; i < stringB.length(); i++)
		{
			if (stringB[i] == ' ')
			{
				wordB.push_back(temp);
				temp = "";
			}
			else
			{
				temp += stringB[i];
			}
		}
		wordB.push_back(temp);
		temp = "";

		if (wordA.size() != wordB.size())
		{
			return false;
		}
		else if (wordA.size() == wordB.size() && wordA.size() == 1)	//��һ��һ��������
		{
			if (wordA[0].length() != wordB[0].length())
			{
				return false;
			}
			sort(wordA[0].begin(), wordA[0].end());
			sort(wordB[0].begin(), wordB[0].end());			
			for (int i = 0; i < wordA[0].length(); i++)
			{
				if (wordA[0][i] != wordB[0][i])
				{
					return false;
				}
			}
		}
		else
		{
			sort(wordA.begin(), wordA.end());
			sort(wordB.begin(), wordB.end());
			for (int i = 0; i < wordA.size(); i++)
			{
				if (wordA[i] != wordB[i])
				{
					return false;
				}
			}
		}
		return true;*/
	}
};

//===========================================================
/*2����ʵ��һ���㷨���ڲ�ʹ�ö������ݽṹ�ʹ���ռ������£���תһ���������ַ���(����ʹ�õ������̱���)��
����һ��string iniString���뷵��һ��string��Ϊ��ת����ַ�������֤�ַ����ĳ���С�ڵ���5000��
����������
"This is nowcoder"
���أ�"redocwon si sihT"*/
class Reverse {
public:
	string reverseString(string iniString) {
		for (int i = 0; i < iniString.length()/2; i++)
		{
			swap(iniString[i], iniString[iniString.length() - 1 - i]);
		}
		return iniString;
	}
};

//===========================================================
/*1����ʵ��һ���㷨��ȷ��һ���ַ����������ַ��Ƿ�ȫ����ͬ����������Ҫ������ʹ�ö���Ĵ洢�ṹ��
����һ��string iniString���뷵��һ��boolֵ,True���������ַ�ȫ����ͬ��False���������ͬ���ַ���
��֤�ַ����е��ַ�ΪASCII�ַ����ַ����ĳ���С�ڵ���3000��
����������
"aeiou"
���أ�True
"BarackObama"
���أ�False*/
class Different {
public:
	bool checkDifferent(string iniString) {
		sort(iniString.begin(), iniString.end());
		if (unique(iniString.begin(), iniString.end()) == iniString.end())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	
	system("pause");
	return 0;
}

