// GoldenScroll.cpp : 定义控制台应用程序的入口点。
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
/*83、有一个单词清单，请设计一个高效算法，计算由清单中单词组成的最大子矩阵，要求矩阵中的行和列都是清单中的单词。
给定一个string数组dic，代表单词清单，同时给定清单的大小n，请返回最大子矩阵的面积。
保证单词清单的大小小于等于50，且某一长度的串的数量小于等于12。
测试样例：
["aaa","aaa","aaa","bb","bb"]
返回：9*/
class AlphaMatrix {
public:
	int findAlphaMatrix(vector<string> dic, int n) {
		// 我只能说，什么玩意。。。题意描述的是这种东西么？不应该是填词那种数独么？想破了头也想不到是这么个东西啊
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
/*82、有一个正整数和负整数组成的NxN矩阵，请编写代码找出元素总和最大的子矩阵。请尝试使用一个高效算法。
给定一个int矩阵mat和矩阵的阶数n，请返回元素总和最大的子矩阵的元素之和。保证元素绝对值小于等于100000，且矩阵阶数小于等于200。
测试样例：
[[1,2,-3],[3,4,-5],[-5,-6,-7]],3
返回：10*/
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
/*81、有一个方阵，其中每个单元(像素)非黑即白(非0即1)，请设计一个高效算法，找到四条边颜色相同的最大子方阵。
给定一个01方阵mat，同时给定方阵的边长n，请返回最大子方阵的边长。保证方阵边长小于等于100。
测试样例：
[[1,1,1],[1,0,1],[1,1,1]],3
返回：3*/
class SubMatrix {
public:
	int maxSubMatrix(vector<vector<int> > mat, int n) {
		vector<int> ones(n, 1);
		vector<vector<int>> left(n, ones);	//当前点左边连续相同的点个数(算自己)
		vector<vector<int>> above(n, ones);	//当前点上边连续相同的点个数（算自己）
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
					int minLength = min(left[i][j - 1], above[i - 1][j]);//由于是方阵，长宽要一致，因此取二者最小的那个
					for (int length = minLength; length > 0 && length >= maxLength; length--) {	//在最小中找最大
						if (left[i - length][j] >= minLength + 1 && above[i][j - length] >= minLength + 1) {//考察对边的长度
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
/*80、现有一个字典，同时给定字典中的两个字符串s和t，给定一个变换，每次可以改变字符串中的任意一个字符，请设计一个算法，
计算由s变换到t所需的最少步数，同时需要满足在变换过程中的每个串都是字典中的串。
给定一个string数组dic，同时给定数组大小n，串s和串t，请返回由s到t变换所需的最少步数。
若无法变换到t则返回-1。保证字符串长度均小于等于10，且字典中字符串数量小于等于500。
测试样例：
["abc","adc","bdc","aaa”],4,”abc","bdc"
返回：2*/
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
		int map[500][500];	//题中明确说了不超过500个，so
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
					map[i][j] = map[j][i] = 500;	//只有500个元素，最大距离不过500
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
/*79、现有一些随机生成的数字要将其依次传入，请设计一个高效算法，对于每次传入一个数字后，
算出当前所有传入数字的中位数。(若传入了偶数个数字则令中位数为第n/2小的数字，n为已传入数字个数)。
给定一个int数组A，为传入的数字序列，同时给定序列大小n，请返回一个int数组，代表每次传入后的中位数。保证n小于等于1000。
测试样例：
[1,2,3,4,5,6],6
返回：[1,1,2,2,3,3]*/
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
/*78、现有一个小写英文字母组成的字符串s和一个包含较短小写英文字符串的数组p，请设计一个高效算法，
对于p中的每一个较短字符串，判断其是否为s的子串。给定一个string数组p和它的大小n，
同时给定string s，为母串，请返回一个bool数组，每个元素代表p中的对应字符串是否为s的子串。
保证p中的串长度小于等于8，且p中的串的个数小于等于500，同时保证s的长度小于等于1000。
测试样例：
["a","b","c","d"],4,"abc"
返回：[true,true,true,false]*/
class Substr {
public:
	vector<bool> chkSubStr(vector<string> p, int n, string s) {
		//先无耻的使用find了，后续研究trie树
		vector<bool> ans;
		for (int i = 0; i < n; i++) {
			if (s.find(p[i]) != string::npos) ans.push_back(true);
			else ans.push_back(false);
		}
		return ans;
	}
};
//==============================================================
/*77、有一组单词，请编写一个程序，在数组中找出由数组中字符串组成的最长的串A，即A是由其它单词组成的(可重复)最长的单词。
给定一个string数组str，同时给定数组的大小n。请返回最长单词的长度，保证题意所述的最长单词存在。
测试样例：
["a","b","c","ab","bc","abc"],6
返回：3*/
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
/*76、有一篇文章内含多个单词，现给定两个单词，请设计一个高效算法，找出文中这两个单词的最短距离
(即最少相隔的单词数,也就是两个单词在文章中位置的差的绝对值)。
给定一个string数组article，代表所给文章，同时给定文章的单词数n和待查找的两个单词x和y。
请返回两个单词的最短距离。保证两个单词均在文中出现且不相同，同时保证文章单词数小于等于1000。*/
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
/*75、现在有一个数组，请找出数组中每个元素的后面比它大的最小的元素，若不存在则为-1。
给定一个int数组A及数组的大小n，请返回每个元素所求的值组成的数组。保证A中元素为正整数，且n小于等于1000。
测试样例：
[11,13,10,5,12,21,3],7
[12,21,12,12,21,-1,-1]*/
class NextElement {
public:
	vector<int> findNext(vector<int> A, int n) {
		// 上一题理解错了，就做成了这道题的要求
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
/*74、现在我们有一个int数组，请你找出数组中每个元素的下一个比它大的元素。
给定一个int数组A及数组的大小n，请返回一个int数组，代表每个元素比他大的下一个元素,若不存在则为-1。保证数组中元素均为正整数。
测试样例：
[11,13,10,5,12,21,3],7
返回：[13,21,12,12,21,-1,-1]*/
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
		/*这个理解错题意了，不过实现了找出A中元素之后比他大的最小元素，代码就留着吧
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
/*73、请编写一个方法，输出0到n(包括n)中数字2出现了几次。
给定一个正整数n，请返回0到n的数字中2出现了几次。
测试样例：
10
返回：1*/
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
/*72、请编写一个函数，将两个数字相加。不得使用+或其他算数运算符。
给定两个int A和B。请返回A＋B的值
测试样例：
1,2
返回：3*/
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
/*71、有一个类似结点的数据结构TreeNode，包含了val属性和指向其它结点的指针。其可以用来表示二叉查找树
(其中left指针表示左儿子，right指针表示右儿子)。请编写一个方法，将二叉查找树转换为一个链表，
其中二叉查找树的数据结构用TreeNode实现，链表的数据结构用ListNode实现。
给定二叉查找树的根结点指针root，请返回转换成的链表的头指针。*/
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
/*70、请设计一个高效算法，找出数组中两数之和为指定值的所有整数对。
给定一个int数组A和数组大小n以及需查找的和sum，请返回和为sum的整数对的个数。保证数组大小小于等于3000。
测试样例：
[1,2,3,4,5],5,6
返回：2*/
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
		// 排序
		sort(A.begin(), A.end());
		//
		int count = 0;
		for (int i = 0, j = n - 1; i < j;) {
			int s = A[i] + A[j];
			if (s == sum) {
				// 3 3 3这种情况
				if (A[i] == A[j]) {
					int x = j - i + 1;
					count += x*(x - 1) / 2;
					break;
				}//if
				// 2 2 3 4 4 4这种情况
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
        /*这里会出现一个问题，没办法处理负数，因此这个方法不行
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
/*69、请设计一个高效的方法，找出任意指定单词在一篇文章中的出现频数。
给定一个string数组article和数组大小n及一个待统计单词word，请返回该单词在文章中的出现频数。保证文章的词数小于等于1000。*/
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
/*68、对于一个有正有负的整数数组，请找出总和最大的连续数列。
给定一个int数组A和数组大小n，请返回最大的连续数列的和。保证n的大小小于等于3000。
测试样例：
[1,2,3,-6,1]
返回：6*/
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
/*67、有一个非负整数，请编写一个算法，打印该整数的英文描述。
给定一个int x，请返回一个string，为该整数的英文描述。
测试样例：
1234
返回："One Thousand,Two Hundred Thirty Four"*/
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

		//先去除左边的空格
		len = str.length();
		for (i = 0; i<len; i++) {
			if (str[i] != ' ') break;
		}
		str = str.substr(i, len - i + 1);

		//再去除右边的空格
		len = str.length();
		for (i = len - 1; i >= 0; i--) {
			if (str[i] != ' ') break;
		}
		str = str.substr(0, i + 1);

		return str;
	}
};
//===========================================================
/*66、有一个整数数组，请编写一个函数，找出索引m和n，只要将m和n之间的元素排好序，整个数组就是有序的。
注意：n-m应该越小越好，也就是说，找出符合条件的最短序列。
给定一个int数组A和数组的大小n，请返回一个二元组，代表所求序列的起点和终点。
(原序列位置从0开始标号,若原序列有序，返回[0,0])。保证A中元素均为正整数。
测试样例：
[1,4,6,5,9,10],6
返回：[2,3]*/
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
/*65、请设计一个算法，计算n的阶乘有多少个尾随零。
给定一个int n，请返回n的阶乘的尾零个数。保证n为正整数。
测试样例：
5
返回：1*/
class Factor {
public:
	int getFactorSuffixZero(int n) {
		//2*5就能得到1个零，就计算总共能分解出几个5即可
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
/*64、我们现在有四个槽，每个槽放一个球，颜色可能是红色(R)、黄色(Y)、绿色(G)或蓝色(B)。例如，
可能的情况为RGGB(槽1为红色，槽2、3为绿色，槽4为蓝色)，作为玩家，你需要试图猜出颜色的组合。比如，
你可能猜YRGB。要是你猜对了某个槽的颜色，则算一次“猜中”。要是只是猜对了颜色但槽位猜错了，则算一次“伪猜中”。注意，“猜中”不能算入“伪猜中”。
给定两个string A和guess。分别表示颜色组合，和一个猜测。请返回一个int数组，第一个元素为猜中的次数，第二个元素为伪猜中的次数。
测试样例：
"RGBY","GGRR"
返回：[1,1]*/
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
/*63、请编写一个方法，找出两个数字中最大的那个。条件是不得使用if-else等比较和判断运算符。
给定两个int a和b，请返回较大的一个数。若两数相同则返回任意一个。
测试样例：
1，2
返回：2*/
class Max {
public:
	int getMax(int a, int b) {
		b = a - b;
		a -= b&(b >> 31);
		return a;
	}
};
//===========================================================
/*62、对于一个给定的井字棋棋盘，请设计一个高效算法判断当前玩家是否获胜。
给定一个二维数组board，代表当前棋盘，其中元素为1的代表是当前玩家的棋子，为0表示没有棋子，为-1代表是对方玩家的棋子。
测试样例：
[[1,0,1],[1,-1,-1],[1,-1,0]]
返回：true*/
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
/*61、请编写一个函数，函数内不使用任何临时变量，直接交换两个数的值。
给定一个int数组AB，其第零个元素和第一个元素为待交换的值，请返回交换后的数组。
测试样例：
[1,2]
返回：[2,1]*/
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
/*60、有一组数，对于其中任意两个数组，若前面一个大于后面一个数字，则这两个数字组成一个逆序对。请设计一个高效的算法，计算给定数组中的逆序对个数。
给定一个int数组A和它的大小n，请返回A中的逆序对个数。保证n小于等于5000。
测试样例：
[1,2,3,4,5,6,7,0],8
返回：7*/
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
/*59、现在我们要读入一串数，同时要求在读入每个数的时候算出它的秩，即在当前数组中小于等于
它的数的个数(不包括它自身)，请设计一个高效的数据结构和算法来实现这个功能。
给定一个int数组A，同时给定它的大小n，请返回一个int数组，元素为每次加入的数的秩。保证数组大小小于等于5000。
测试样例：
[1,2,3,4,5,6,7],7
返回：[0,1,2,3,4,5,6]*/
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
/*58、叠罗汉是一个著名的游戏，游戏中一个人要站在另一个人的肩膀上。为了使叠成的罗汉更稳固，我们应该让上面的人比下面的人更轻一点。
现在一个马戏团要表演这个节目，为了视觉效果，我们还要求下面的人的身高比上面的人高。请编写一个算法，计算最多能叠多少人，注意这里所有演员都同时出现。
给定一个二维int的数组actors，每个元素有两个值，分别代表一个演员的身高和体重。同时给定演员总数n，请返回最多能叠的人数。保证总人数小于等于500。
测试样例：
[[1,2],[3,4],[5,6],[7,8]],4
返回：4*/
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
/*57、叠罗汉是一个著名的游戏，游戏中一个人要站在另一个人的肩膀上。同时我们应该让下面的人比上面的人更高一点。
已知参加游戏的每个人的身高，请编写代码计算通过选择参与游戏的人，我们多能叠多少个人。
注意这里的人都是先后到的，意味着参加游戏的人的先后顺序与原序列中的顺序应该一致。
给定一个int数组men，代表依次来的每个人的身高。同时给定总人数n，请返回最多能叠的人数。保证n小于等于500。
测试样例：
[1,6,2,5,3,4],6
返回：4*/
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
/*56、有一个NxM的整数矩阵，矩阵的行和列都是从小到大有序的。请设计一个高效的查找算法，查找矩阵中元素x的位置。
给定一个int有序矩阵mat，同时给定矩阵的大小n和m以及需要查找的元素x，请返回一个二元数组，代表该元素的行号和列号(均从零开始)。保证元素互异。
测试样例：
[[1,2,3],[4,5,6]],2,3,6
返回：[1,2]*/
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
/*55、有一个排过序的字符串数组，但是其中有插入了一些空字符串，请设计一个算法，找出给定字符串的位置。算法的查找部分的复杂度应该为log级别。
给定一个string数组str,同时给定数组大小n和需要查找的string x，请返回该串的位置(位置从零开始)。
测试样例：
["a","b","","c","","d"],6,"c"
返回：3*/
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
		//排过序的数组肯定有东西，不过这里还是加一个判断吧
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
/*54、有一个排过序的数组，包含n个整数，但是这个数组向左进行了一定长度的移位，例如，原数组为[1,2,3,4,5,6]，
向左移位5个位置即变成了[6,1,2,3,4,5],现在对于移位后的数组，需要查找某个元素的位置。请设计一个复杂度为log级别的算法完成这个任务。
给定一个int数组A，为移位后的数组，同时给定数组大小n和需要查找的元素的值x，请返回x的位置(位置从零开始)。保证数组中元素互异。
测试样例：
[6,1,2,3,4,5],6,6
返回：0*/
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
		/*数组不一定是连续的
		int offset = A[0] - 1;
		return (x - 1) - (offset % n);*/
	}
};

//===========================================================
/*53、请编写一个方法，对一个字符串数组进行排序，将所有变位词合并，保留其字典序最小的一个串。
这里的变位词指变换其字母顺序所构成的新的词或短语。例如"triangle"和"integral"就是变位词。
给定一个string的数组str和数组大小int n，请返回排序合并后的数组。保证字符串串长小于等于20，数组大小小于等于300。
测试样例：
["ab","ba","abc","cba"]
返回：["ab","abc"]*/
class SortString {
public:
	vector<string> sortStrings(vector<string> str, int n) {
		//描述的不是很清楚，返回的是原str，而不是变位词
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
/*52、约瑟夫问题是一个著名的趣题。这里我们稍稍修改一下规则。有n个人站成一列。
并从头到尾给他们编号，第一个人编号为1。然后从头开始报数，第一轮依次报1，2，1，2...然后报到2的人出局。
接着第二轮再从上一轮最后一个报数的人开始依次报1，2，3，1，2，3...报到2，3的人出局。以此类推直到剩下以后一个人。
现在需要求的即是这个人的编号。给定一个int n，代表游戏的人数。请返回最后一个人的编号
测试样例：
5
返回：5*/
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
/*51、约瑟夫问题是一个非常著名的趣题，即由n个人坐成一圈，按顺时针由1开始给他们编号。
然后由第一个人开始报数，数到m的人出局。现在需要求的是最后一个出局的人的编号。
给定两个int n和m，代表游戏的人数。请返回最后一个出局的人的编号。保证n和m小于等于1000。
测试样例：
5 3
返回：4*/
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
/*50、有一堆箱子，每个箱子宽为wi，长为di，高为hi，现在需要将箱子都堆起来，而且为了使堆起来的箱子不到，
上面的箱子的宽度和长度必须小于下面的箱子。请实现一个方法，求出能堆出的最高的高度，这里的高度即堆起来的所有箱子的高度之和。
给定三个int数组w,l,h，分别表示每个箱子宽、长和高，同时给定箱子的数目n。请返回能堆成的最高的高度。保证n小于等于500。
测试样例：
[1,1,1],[1,1,1],[1,1,1]
返回：1*/
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
/*49、请设计一种算法，解决著名的n皇后问题。这里的n皇后问题指在一个nxn的棋盘上放置n个棋子，
使得每行每列和每条对角线上都只有一个棋子，求其摆放的方法数。给定一个int n，请返回方法数，保证n小于等于15
测试样例：
1
返回：1*/
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
			chessBorad[row] = col;	//row是行，判断(row,chessBorad[row](== col))位置可否放旗子
			if (place(chessBorad, row)) {	//如果可以放置，就进行下一行的放置，不能就将row行棋子放到下一列
				count(chessBorad, row + 1, n, ans);
			}
		}
	}
	bool place(vector<int> &chessBorad, int currentRow) {
		for (int previousRow = 1; previousRow < currentRow; previousRow++) {	//枚举已放置的前previousRow行，看这一行能否放置
			if (chessBorad[previousRow] == chessBorad[currentRow] || //同一列
				chessBorad[previousRow] - chessBorad[currentRow] == previousRow - currentRow ||	//右对角线
				chessBorad[previousRow] - chessBorad[currentRow] == currentRow - previousRow) {	//左对角线
				return false;	//如果在同一列，右对角线，左对角线则不能放置
			}
		}
		return true;
	}
};

//===========================================================
/*48、有数量不限的硬币，币值为25分、10分、5分和1分，请编写代码计算n分有几种表示法。
给定一个int n，请返回n分有几种表示法。保证n小于等于100000，为了防止溢出，请将答案Mod 1000000007。
测试样例：
6
返回：2*/
class Coins {
public:
	int countWays(int n) {
		int *dp = new int[n + 1]();
		dp[0] = 1;
		int coin[4] = { 1, 5, 10, 25 };
		for (int i = 0; i < 4; i++) {
			for (int j = coin[i]; j <= n; j++) {
				dp[j] = (dp[j] + dp[j - coin[i]]) % 1000000007;	//按面值间隔累加
			}
		}
		return dp[n];
	}
};
//===========================================================
/*47、在一个nxm矩阵形状的城市里爆发了洪水，洪水从(0,0)的格子流到这个城市，在这个矩阵中有的格子有一些建筑，
洪水只能在没有建筑的格子流动。请返回洪水流到(n - 1,m - 1)
的最早时间(洪水只能从一个格子流到其相邻的格子且洪水单位时间能从一个格子流到相邻格子)。
给定一个矩阵map表示城市，其中map[i][j]表示坐标为(i,j)的格子，值为1代表该格子有建筑，
0代表没有建筑。同时给定矩阵的大小n和m(n和m均小于等于100)，请返回流到(n - 1,m - 1)的最早时间。保证洪水一定能流到终点。*/
class Flood {
public:
	/*struct position {
		int row, col;
	};
	int MyfloodFill(vector<vector<int>> map, int n, int m) {
		position offset[4];
		//为了最短路径，采取右下左上的顺序寻找路径
		offset[0].row = 0;	offset[0].col = 1;
		offset[1].row = 1;	offset[1].col = 0;
		offset[2].row = 0;	offset[2].col = -1;
		offset[3].row = -1;	offset[3].col = 0;
		//为了不对map边缘特殊处理，在外围加上不可到的围墙
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
		//初始化各项
		int pattern = 0;
		int lastPattern = 3;
		position here;	here.row = 1;	here.col = 1;
		maze[1][1] = 1;
		stack<position> path;
		//找路径
		while (here.row != n || here.col != m) {
			//还没到出口，找下一步
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
				//找到了一个可以走的方式
				maze[r][c] = maze[here.row][here.col] + 1;
				path.push(here);
				here.row = r;
				here.col = c;
				//	maze[r][c] = 1;
				pattern = 0;
			}
			else {
				//无路可走了，回溯一步
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
	//感觉是一样的啊，但是自己的算法步数比下面的多10
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
/*46、对于一个字符串，请设计一个算法，判断其是否为一个合法的括号串。
给定一个字符串A和它的长度n，请返回一个bool值代表它是否为一个合法的括号串。
测试样例：
"(()())",6
返回：true
测试样例：
"()a()()",7
返回：false
测试样例：
"()(()()",7
返回：false*/
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
/*45、编写一个方法，确定某字符串的所有排列组合。
给定一个string A和一个int n,代表字符串和其长度，请返回所有该字符串字符的排列，
保证字符串长度小于等于11且字符串中字符均为大写英文字符，排列中的字符串按字典序从大到小排序。(不合并重复字符串)
测试样例：
"ABC"
返回：["CBA","CAB","BCA","BAC","ACB","ABC"]*/
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
/*44、请编写一个方法，返回某集合的所有非空子集。
给定一个int数组A和数组的大小int n，请返回A的所有非空子集。保证A的元素个数小于等于20，
且元素互异。各子集内部从大到小排序,子集之间字典逆序排序，见样例。
测试样例：
[123,456,789]
返回：{[789,456,123],[789,456],[789,123],[789],[456 123],[456],[123]}*/
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
/*43、在数组A[0..n-1]中，有所谓的魔术索引，满足条件A[i]=i。给定一个不下降序列，元素值可能相同，
编写一个方法，判断在数组A中是否存在魔术索引。请思考一种复杂度优于o(n)的方法。
给定一个int数组A和int n代表数组大小，请返回一个bool，代表是否存在魔术索引。
测试样例：
[1,1,3,4,5]
返回：true*/

class MagicIndex {
public:
	bool findMagicIndex(vector<int> A, int n) {
		//二分法同样适用
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
/*42、在数组A[0..n-1]中，有所谓的魔术索引，满足条件A[i]=i。给定一个升序数组，元素值各不相同，
编写一个方法，判断在数组A中是否存在魔术索引。请思考一种复杂度优于o(n)的方法。
给定一个int数组A和int n代表数组大小，请返回一个bool，代表是否存在魔术索引。
测试样例：
[1,2,3,4,5]
返回：false*/
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
/*41、有一个XxY的网格，一个机器人只能走格点且只能向右或向下走，要从左上角走到右下角。
请设计一个算法，计算机器人有多少种走法。注意这次的网格中有些障碍点是不能走的。
给定一个int[][] map(C++ 中为vector >),表示网格图，若map[i][j]为1则说明该点不是障碍点，否则则为障碍。
另外给定int x,int y，表示网格的大小。请返回机器人从(0,0)走到(x - 1,y - 1)的走法数，为了防止溢出，
请将结果Mod 1000000007。保证x和y均小于等于50*/
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
/*40、有一个XxY的网格，一个机器人只能走格点且只能向右或向下走，要从左上角走到右下角。
请设计一个算法，计算机器人有多少种走法。
给定两个正整数int x,int y，请返回机器人的走法数目。保证x＋y小于等于12。
测试样例：
2,2
返回：2*/
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
/*39、有个小孩正在上楼梯，楼梯有n阶台阶，小孩一次可以上1阶、2阶、3阶。请实现一个方法，
计算小孩有多少种上楼的方式。为了防止溢出，请将结果Mod 1000000007
给定一个正整数int n，请返回一个数，代表上楼的方式数。保证n小于等于100000。
测试样例：
1
返回：1*/
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
/*38、有一些数的素因子只有3、5、7，请设计一个算法，找出其中的第k个数。
给定一个数int k，请返回第k个数。保证k小于等于100。
测试样例：
3
返回：7*/
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
/*37、在二维平面上，有一些点，请找出经过点数最多的那条线。
给定一个点集vector p和点集的大小n,没有两个点的横坐标相等的情况,请返回一个vector，代表经过点数最多的那条直线的斜率和截距。*/
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
		//之前好几次编译不过，问题原来出在这里。map的键值如果用自己数据结构，必须重载"<"运算符
		//因为map内部是一个红黑树，需要排序，如果不重载，就不能构造树，就会出问题
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
		//用第一个点遍历所有直线，map存，再第二个，第三个。。。没办法，最笨的办法，想不到其他的方式
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
/*36、在二维平面上，有两个正方形，请找出一条直线，能够将这两个正方形对半分。假定正方形的上下两条边与x轴平行。
给定两个vecotrA和B，分别为两个正方形的四个顶点。请返回一个vector，代表所求的平分直线的斜率和截距，保证斜率存在。
测试样例：
[(0,0),(0,1),(1,1),(1,0)],[(1,0),(1,1),(2,0),(2,1)]
返回：[0.0，0.5]*/
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
/*35、请编写一个方法，实现整数的乘法、减法和除法运算(这里的除指整除)。只允许使用加号。
给定两个正整数int a,int b,同时给定一个int type代表运算的类型，1为求a ＊ b，0为求a ／ b，-1为求a － b。
请返回计算的结果，保证数据合法且结果一定在int范围内。
测试样例：
1,2,1
返回：2*/
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
		case -1://减法
			ans = Sub(a, b);
			break;
		case 0://除法
			ans = Div(a, b);
			break;
		case 1://乘法
			ans = Mul(a, b);
			break;
		default:
			break;
		}
		return ans;
	}
};


//===========================================================
/*34、给定直角坐标系上的两条直线，确定这两条直线会不会相交。
线段以斜率和截距的形式给出，即double s1，double s2，double y1，double y2，
分别代表直线1和2的斜率(即s1,s2)和截距(即y1,y2)，请返回一个bool，代表给定的两条直线是否相交。这里两直线重合也认为相交。
测试样例：
3.14,3.14,1,2
返回：false*/
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
/*33、在n个顶点的多边形上有n只蚂蚁，这些蚂蚁同时开始沿着多边形的边爬行，
请求出这些蚂蚁相撞的概率。(这里的相撞是指存在任意两只蚂蚁会相撞)
给定一个int n(3<=n<=10000)，代表n边形和n只蚂蚁，请返回一个double，为相撞的概率。
测试样例：
3
返回：0.75*/
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
/*32、有一个单色屏幕储存在一维数组中，其中数组的每个元素代表连续的8位的像素的值，请实现一个函数，
将第x到第y个像素涂上颜色(像素标号从零开始)，并尝试尽量使用最快的办法。
给定表示屏幕的数组screen(数组中的每个元素代表连续的8个像素，
且从左至右的像素分别对应元素的二进制的从低到高位)，以及int x,int y，意义如题意所述，保证输入数据合法。
请返回涂色后的新的屏幕数组。
测试样例：
[0,0,0,0,0,0],0,47
返回：[255,255,255,255,255,255]*/
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
/*31、数组A包含了0到n的所有整数，但其中缺失了一个。对于这个问题，我们设定限制，
使得一次操作无法取得数组number里某个整数的完整内容。
唯一的可用操作是询问数组中第i个元素的二进制的第j位(最低位为第0位)，
该操作的时间复杂度为常数，请设计算法，在O(n)的时间内找到这个数。
给定一个数组number，即所有剩下的数按从小到大排列的二进制各位的值，
如A[0][1]表示剩下的第二个数二进制从低到高的第二位。同时给定一个int n，意义如题。请返回缺失的数。
测试样例：
[[0],[0,1]]
返回：1*/
class Finder {
public:
	/*简单点说，题目用数组A的一行元素表示一个整数，即A[0]～A[n-1]分别代表n个整数。
	记A[m]表示整数a,则第m行的第x列表示a的二进制表示时从低到高的第x位。样例中A[0]为[0]，
	即第1位为0，表示整数0；A[1]=[0,1],即第1位为0，第2位为1，表示整数2，因此缺失了整数1。
	样例中如果有其他整数，如A[5],则应该为[1,0,1]，依次类推。*/
	//思路就是检测连续的行，0列是不是0101交替的，还要考虑首尾数字
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
/*30、请编写程序交换一个数的二进制的奇数位和偶数位。（使用越少的指令越好）
给定一个int x，请返回交换后的数int。
测试样例：
10
返回：5*/
class Exchange {
public:
	int exchangeOddEven(int x) {
		return ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1);
	}
};

//===========================================================
/*29、编写一个函数，确定需要改变几个位，才能将整数A转变成整数B。
给定两个整数int A，int B。请返回需要改变的数位个数。
测试样例：
10,5
返回：4*/
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
/*28、有一个正整数，请找出其二进制表示中1的个数相同、且大小最接近的那两个数。(一个略大，一个略小)
给定正整数int x，请返回一个vector，代表所求的两个数（小的在前）。保证答案存在。
测试样例：
2
返回：[1,4]*/
class CloseNumber {
public:
	vector<int> getCloseNumber(int x) {
		vector<int> ans;
		int large = x, small = x, temp = x, c0 = 0, c1 = 0, p;
		//为了找最接近的小数，替换非拖尾1的第一个1为0，位置为p，然后填充p之前的位，从左到右优先填充1，为了最接近。
		while ((temp & 1) == 1)	//位操作一定要把他括起来！！要不然这个优先级的问题可能会造成不可预计的后果
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
		small &= ((~0) << (p + 1));	//~0为全1的数
		small |= (((1 << (c1 + 1)) - 1) << (c0 - 1));
		ans.push_back(small);
		//为了找最接近的大数，替换非拖尾0的第一个0为1，位置为p，然后填充p之前的位，从左到右优先填充0，为了最接近。
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
/*27、有一个介于0和1之间的实数，类型为double，返回它的二进制表示。
如果该数字无法精确地用32位以内的二进制表示，返回“Error”。
给定一个double num，表示0到1的实数，请返回一个string，代表该数的二进制表示或者“Error”。
测试样例：
0.625
返回：0.101*/
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
/*26、有两个32位整数n和m，请编写算法将m的二进制数位插入到n的二进制的第j到第i位,
其中二进制的位数从低位数到高位且以0开始。
给定两个数int n和int m，同时给定int j和int i，意义如题所述，请返回操作后的数，
保证n的第j到第i位均为零，且m的二进制位数小于等于i-j+1。
测试样例：
1024，19，2，6
返回：1100*/
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
/*25、输入一颗二叉树和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。
路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。*/
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
/*24、有一棵无穷大的满二叉树，其结点按根结点一层一层地从左往右依次编号，根结点编号为1。
现在有两个结点a，b。请设计一个算法，求出a和b点的最近公共祖先的编号。
给定两个int a,b。为给定结点的编号。请返回a和b的最近公共祖先的编号。注意这里结点本身也可认为是其祖先。
测试样例：
2，3
返回：1*/
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
/*23、请设计一个算法，寻找二叉树中指定结点的下一个结点（即中序遍历的后继）。
给定树的根结点指针TreeNode* root和结点的值int p，请返回值为p的结点的后继结点的值。
保证结点的值大于等于零小于等于100000且没有重复值，若不存在后继返回-1。*/
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
/*22、请实现一个函数，检查一棵二叉树是否为二叉查找树。
给定树的根结点指针TreeNode* root，请返回一个bool，代表该树是否为二叉查找树。*/
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
/*21、对于一棵二叉树，请设计一个算法，创建含有某一深度上所有结点的链表。
给定二叉树的根结点指针TreeNode* root，以及链表上结点的深度，请返回一个链表ListNode，
代表该深度上所有结点的值，请按树上从左往右的顺序链接，保证深度不超过树的高度，
树上结点的值为非负整数且不超过100000。*/
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
/*20、对于一个元素各不相同且按升序排列的有序序列，请编写一个算法，创建一棵高度最小的二叉查找树。
给定一个有序序列int[] vals,请返回创建的二叉查找树的高度。*/
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
/*19、对于一个有向图，请实现一个算法，找出两点之间是否存在一条路径。
给定图中的两个结点的指针UndirectedGraphNode* a,UndirectedGraphNode* b
(请不要在意数据类型，图是有向图),请返回一个bool，代表两点之间是否存在一条路径(a到b或b到a)。*/
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
/*18、实现一个函数，检查二叉树是否平衡，平衡的定义如下，
对于树中的任意一个结点，其两颗子树的高度差不超过1。
给定指向树根结点的指针TreeNode* root，请返回一个bool，代表这棵树是否平衡。*/
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
			if (currentNode->left != NULL)	//如果左子树不空
			{
				q.push(currentNode->left);
			}
			else  //如果左子树空
			{
				if (currentNode->right != NULL)	//考察右子树
				{
					if (currentNode->right->left != NULL || currentNode->right->right != NULL)	//如果右子树有子树，就不平衡
					{
						return false;
					}
				}
			}
			if (currentNode->right != NULL)	//如果右子树不空
			{
				q.push(currentNode->right);
			}
			else  //如果右子树空
			{
				if (currentNode->left != NULL)	//而左子树不空
				{
					if (currentNode->left->left != NULL || currentNode->left->right != NULL)	//且左子树还有子树，则不平衡
					{
						return false;
					}
				}
			}
			if (!q.empty())
			{
				currentNode = q.front();	//躲过了断定，按层遍历下一个节点
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
/*17、有家动物收容所只收留猫和狗，但有特殊的收养规则，收养人有两种收养方式，
第一种为直接收养所有动物中最早进入收容所的，第二种为选择收养的动物类型（猫或狗），并收养该种动物中最早进入收容所的。
给定一个操作序列int[][2] ope(C++中为vector<vector<int>>)代表所有事件。
若第一个元素为1，则代表有动物进入收容所，第二个元素为动物的编号，正数代表狗，负数代表猫；
若第一个元素为2，则代表有人收养动物，第二个元素若为0，则采取第一种收养方式，若为1，则指定收养狗，
若为-1则指定收养猫。请按顺序返回收养的序列。若出现不合法的操作，即没有可以符合领养要求的动物，则将这次领养操作忽略。
测试样例：
[[1,1],[1,-1],[2,0],[2,-1]]
返回：[1,-1]*/
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
				if (ope[i][1] == 0)//按照第一种方式选动物; 
				{
					for (int j = 0; j<i&&flag == 0; j++)
					{
						if (ope[j][0] == 1)//最早的动物; 
						{
							ans.push_back(ope[j][1]);
							ope[j][0] = -1;//表示已经选过; 
							flag = 1;
						}
					}
				}
				else  if (ope[i][1] == 1)//取第一个狗; 
				{
					for (int j = 0; j<i&&flag == 0; j++)
					{
						if (ope[j][0] == 1 && ope[j][1] >= 0)
						{
							ans.push_back(ope[j][1]);
							ope[j][0] = -1;//表示已经选过; 
							flag = 1;
						}
					}

				}
				else//取第一个猫; 
				{
					for (int j = 0; j<i&&flag == 0; j++)
					{
						if (ope[j][0] == 1 && ope[j][1]<0)
						{
							ans.push_back(ope[j][1]);
							ope[j][0] = -1;//表示已经选过; 
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
/*16、请编写一个程序，按升序对栈进行排序（即最大元素位于栈顶），
要求最多只能使用一个额外的栈存放临时数据，但不得将元素复制到别的数据结构中。
给定一个int[] numbers(C++中为vector&ltint>)，其中第一个元素为栈顶，请返回排序后的栈。
请注意这是一个栈，意味着排序过程中你只能访问到第一个元素。
测试样例：
[1,2,3,4,5]
返回：[5,4,3,2,1]*/
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
/*15、用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。*/
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
/*14、请实现一种数据结构SetOfStacks，由多个栈组成，其中每个栈的大小为size，
当前一个栈填满时，新建一个栈。该数据结构应支持与普通栈相同的push和pop操作。
给定一个操作序列int[][2] ope(C++为vector<vector<int>>)，
每个操作的第一个数代表操作类型，若为1，则为push操作，
后一个数为应push的数字；若为2，则为pop操作，后一个数无意义。
请返回一个int[][](C++为vector<vector<int>>)，为完成所有操作后的SetOfStacks，
顺序应为从下到上，默认初始的SetOfStacks为空。保证数据合法。*/
class SetOfStacks {
public:
	vector<vector<int>> setOfStacks(vector<vector<int>> ope, int size) {
		vector<vector<int> > st;
		vector<int> temp;
		for (int i = 0; i<ope.size(); i++){
			if (ope[i][0] == 1){//入栈
				if (temp.size() == size){//栈满，则新建一个栈，再入栈
					st.push_back(temp);
					temp.clear();
					temp.push_back(ope[i][1]);
				}
				else
					temp.push_back(ope[i][1]);
			}
			if (ope[i][0] == 2){//出栈
				if (temp.size() != 0)//当前栈不为空，直接出栈
					temp.pop_back();
				else if (st.size() != 0){//当前栈为空，则从上一个栈出
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
/*13、请编写一个函数，检查链表是否为回文。
给定一个链表ListNode* pHead，请返回一个bool，代表链表是否为回文。
测试样例：
{1,2,3,2,1}
返回：true
{1,2,3,2,3}
返回：false*/
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
/*12、有两个用链表表示的整数，每个结点包含一个数位。这些数位是反向存放的，
也就是个位排在链表的首部。编写函数对这两个整数求和，并用链表形式返回结果。
给定两个链表ListNode* A，ListNode* B，请返回A+B的结果(ListNode*)。
测试样例：
{1,2,3},{3,2,1}
返回：{4,4,4}*/
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
/*11、编写代码，以给定值x为基准将链表分割成两部分，所有小于x的结点排在大于或等于x的结点之前
给定一个链表的头指针 ListNode* pHead，请返回重新排列后的链表的头指针。注意：分割以后保持原来的数据顺序不变。*/
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
/*10、实现一个算法，删除单向链表中间的某个结点，假定你只能访问该结点。
给定带删除的节点，请执行删除操作，若该节点为尾节点，返回false，否则返回true*/
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
/*9、输入一个链表，输出该链表中倒数第k个结点。*/
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
		int num = 1;	//不为空起码有一个
		for (int i = 0; i < k; i++)
		{
			fast = fast->next;
			if (fast == NULL)	//这个终止条件是对于k个节点，输出倒数k个的保护，也是对k>num的保护
			{
				break;
			}
			num++;
		}
		if (k > num)	//测试案例有k大于节点数的情况
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
/*8、假定我们都知道非常高效的算法来检查一个单词是否为其他字符串的子串。
请将这个算法编写成一个函数，给定两个字符串s1和s2，请编写代码检查s2是否为s1旋转而成，要求只能调用一次检查子串的函数。
给定两个字符串s1,s2,请返回bool值代表s2是否由s1旋转而成。字符串中字符为英文字母和空格，区分大小写，字符串长度小于等于1000。
测试样例：
"Hello world","worldhello "
返回：false
"waterbottle","erbottlewat"
返回：true*/
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
/*7、请编写一个算法，若N阶方阵中某个元素为0，则将其所在的行与列清零。
给定一个N阶方阵int[][](C++中为vector>)mat和矩阵的阶数n，
请返回完成操作后的int[][]方阵(C++中为vector>)，保证n小于等于300，矩阵中的元素为int范围内。
测试样例：
[[1,2,3],[0,1,2],[0,0,1]]
返回：[[0,0,3],[0,0,0],[0,0,0]]*/
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
/*6、有一副由NxN矩阵表示的图像，这里每个像素用一个int表示，请编写一个算法，
在不占用额外内存空间的情况下(即不使用缓存矩阵)，将图像顺时针旋转90度。
给定一个NxN的矩阵，和矩阵的阶数N,请返回旋转后的NxN矩阵,保证N小于等于500，图像元素小于等于256。
测试样例：
[[1,2,3],[4,5,6],[7,8,9]],3
返回：[[7,4,1],[8,5,2],[9,6,3]]*/
class Transform {
public:
	vector<vector<int>> transformImage(vector<vector<int>> mat, int n) {
		if (n <= 1)
		{
			return mat;
		}
		//先转置,处理下三角
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < i; j++)
			{
				swap(mat[i][j], mat[j][i]);
			}
		}
		//再列逆序
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
/*5、利用字符重复出现的次数，编写一个方法，实现基本的字符串压缩功能。
比如，字符串“aabcccccaaa”经压缩会变成“a2b1c5a3”。若压缩后的字符串没有变短，则返回原先的字符串。
给定一个string iniString为待压缩的串(长度小于等于10000)，保证串内字符均由大小写英文字母组成，
返回一个string，为所求的压缩后或未变化的串。
测试样例
"aabcccccaaa"
返回："a2b1c5a3"
"welcometonowcoderrrrr"
返回："welcometonowcoderrrrr"*/
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
/*4、请编写一个方法，将字符串中的空格全部替换为“%20”。假定该字符串有足够的空间存放新增的字符，
并且知道字符串的真实长度(小于等于1000)，同时保证字符串由大小写的英文字母组成。
给定一个string iniString 为原始的串，以及串的长度 int len, 返回替换后的string。
测试样例：
"Mr John Smith”,13
返回："Mr%20John%20Smith"
”Hello  World”,12
返回：”Hello%20%20World”*/
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
/*3、给定两个字符串，请编写程序，确定其中一个字符串的字符重新排列后，能否变成另一个字符串。
这里规定大小写为不同字符，且考虑字符串重点空格。
给定一个string stringA和一个string stringB，请返回一个bool，代表两串是否重新排列后可相同。
保证两串的长度都小于等于5000。
测试样例：
"This is nowcoder","is This nowcoder"
返回：true
"Here you are","Are you here"
返回：false*/
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

		/*以下是单词重排，看了讨论说是字符可以重排，那就非常简单了，hash表就可以做
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
		else if (wordA.size() == wordB.size() && wordA.size() == 1)	//万一就一个单词呢
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
/*2、请实现一个算法，在不使用额外数据结构和储存空间的情况下，翻转一个给定的字符串(可以使用单个过程变量)。
给定一个string iniString，请返回一个string，为翻转后的字符串。保证字符串的长度小于等于5000。
测试样例：
"This is nowcoder"
返回："redocwon si sihT"*/
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
/*1、请实现一个算法，确定一个字符串的所有字符是否全都不同。这里我们要求不允许使用额外的存储结构。
给定一个string iniString，请返回一个bool值,True代表所有字符全都不同，False代表存在相同的字符。
保证字符串中的字符为ASCII字符。字符串的长度小于等于3000。
测试样例：
"aeiou"
返回：True
"BarackObama"
返回：False*/
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

