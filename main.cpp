#include<unordered_map>
#include<algorithm>
#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<set>

#include"Hamming.hpp"
#include"Huffman.hpp"
#include"RLC.hpp"

using namespace std;
using namespace CP;

vector<wstring> message = 
{

L"�����[ӛ�����ַQ�����[ጶ���������Ї��Ŵ���һ�����������»��峤ƪ��ħС˵���Ї����Ĵ�������֮һ�����Ĵ������֮һ��������16����������Ҷ��һ����Ϊ�����������ąǳж������н����������cͽ�܌O��ա��i�˽��ɳ��Q�Ȏ�ͽ����ǰ������ȡ���Ĺ��£������˳Ͷ����ƵĹ������⣬Ҳ�й۵���Ϊ���μ��ǰ��SȨ�������S��С˵��",

L"�����[ӛ���Ă�힣�����֮�H��Ԫ̩������̩�����󶷵�����֓��𡢵��ɽ�֮���P�����s������Ԓ���f��׫�����|�[ӛ���������[ӛ���͡����[ӛ�������[ӛ���ټ��ϗ�־��֮�������[ӛ�����ϷQ�����[ӛ����",

L"�����[ӛ�����������������й���������ع�Ϊ������������ɶ������ԡ����й����������޲��ֵ��������[ӛ��������������������ա���ɮ����˽䡢ɳɮ������͡������칬����������׹Ǿ����������������Ž��ȡ��ȹ������������Ϥ���װ�������[ӛ���ı�ɸ��ֵط�Ϸ������Ӱ�����Ӿ硢����Ƭ�������ȣ��汾���ࡣ"

};
template<typename Ty>
static inline void PrintVec(const char* text, const std::vector<Ty>& vec)
{
	printf("%s", text);
	for (auto& it : vec) std::cout << it << "\t"; std::cout << "\n";
}

static inline vector<int> ArraySum(std::vector<int> left, int target)
{
	auto sum = [&](const vector<int>& vec) {int result = 0; for (auto& it : vec) result += it; return result; };
	if (target <= 0) return vector<int>();
	vector<int> result;
	size_t index = 0;

	for (auto& it : left)
	{
		auto temp = ArraySum({ left.begin() + index + 1, left.end() }, target - it);
		result.insert(result.end(), temp.begin(), temp.end());
		if ((sum(result) + it) == target) {
			result.push_back(it);
			break;
		}

		++index;
	}

	return result;
}

int main(void)
{

	return 0;
}
