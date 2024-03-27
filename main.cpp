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
