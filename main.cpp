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

template<typename Type>
inline std::ostream& operator<<(std::ostream& out, const std::vector<Type>& vec)
{
	for (const Type& it : vec)
		out << it << "\t";
	return out;
}

int main(void)
{
	vector<int> test = { 1, 1, 0, 0 };
	auto G = Hamming::MatrixG(3);
	auto R = Hamming::MatrixR(3);
	auto H = Hamming::MatrixH(3);

	auto encoded = Hamming::Encode(test, G);
	vector<int> error(encoded.begin(),
		encoded.end());

	error[3] ^= 1;

	auto correct = Hamming::ErrorCorrect(error, H);
	auto decoded = Hamming::Decode(correct, R);

	cout << "Original:  " << test << "\n\n";
	cout << "Encoded:   " << encoded << "\n\n";
	cout << "Error:     " << error << "\n\n";
	cout << "Corrected: " << correct << "\n\n";
	cout << "Decoded:   " << decoded << "\n\n";

	return 0;
}
