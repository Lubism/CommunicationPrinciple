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

L"《西遊記》，又稱《西遊釋厄傳》，是中國古代第一部浪漫主义章回体长篇神魔小说，中國《四大名著》之一、《四大奇書》之一。成书于16世纪明朝中叶，一般认为作者是明朝的吳承恩。書中讲述唐三藏與徒弟孫悟空、豬八戒和沙悟淨等師徒四人前往西天取经的故事，表现了惩恶扬善的古老主题，也有观点认为西游记是暗諷权力场的諷刺小说。",

L"因《西遊記》的傳頌，明清之際吳元泰、吳政泰、余象斗等因而又據佛、道兩教之有關戲曲雜劇和神話傳說，撰寫《東遊記》、《南遊記》和《北遊記》等三遊記，再加上楊志和之另本《西遊記》，合稱《四遊記》。",

L"《西遊記》自问世以来，在中国及世界各地广为流傳，被翻译成多种语言。在中国，乃至亚洲部分地区《西遊記》家喻户晓，其中孙悟空、唐僧、猪八戒、沙僧等人物和「大闹天宫」、「三打白骨精」、「孙悟空三借芭蕉扇」等故事尤其為人熟悉。幾百年來，西遊記被改编成各种地方戏曲、电影、电视剧、动画片、漫畫等，版本繁多。"

};
template<typename Ty>
static inline void PrintVec(const std::vector<Ty>& vec) { for (auto& it : vec) std::cout << it << "\t"; std::cout << "\n"; }

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
	vector<int> vec;

	long long b = 256;
	for (auto it = 0LL; it < b; it++)
	{
		vec.push_back(it);
	}

	int a = 9;

	auto ret = ArraySum({ 1, 2, 4, 8, 16 }, a);
	auto ret1 = Hamming::ArraySum({ 1, 2, 4, 8, 16 }, a);

	return 0;
}
