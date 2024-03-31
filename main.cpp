#include"Hamming.hpp"
#include"Huffman.hpp"
#include<string>

using namespace std;
using namespace CP;

// Sending the encoded message to outside
class Sender
{
public:
	inline Sender() { MatrixG = Hamming::MatrixG(5); }
	inline ~Sender() {}
public:
	inline void importText(const std::wstring& input) { Text.assign(input); }

	inline std::vector<int> sendMessage(const std::unordered_map<std::wstring, std::vector<int> >& codeDict) const
	{
		if (Text.empty() || codeDict.empty()) return std::vector<int>();
		std::vector<int> result;

		auto bitsFill = this->encodeMessage(codeDict, result);
		auto temp = this->cvtDecToBin(bitsFill);

		result.insert(result.end(), temp.begin(), temp.end());
		return result;
	}
private:
	inline int encodeMessage(const std::unordered_map<std::wstring, std::vector<int> >& codeDict,
		std::vector<int>& result) const
	{
		auto huffman = Huffman::Encode(Text, codeDict);
		size_t size = huffman.size();
		std::vector<int> hamming;
		std::vector<int> encoded;

		size_t capacity = (size / 26ULL + size % 26ULL) * 31ULL;
		result.reserve(capacity);

		auto itBefore = huffman.begin();
		int elemCount = 0;

		for (auto it = huffman.begin(); it != huffman.end(); ++it) {
			if (elemCount >= 26) { // Split the message and do hamming coding.
				hamming.assign(itBefore, it);
				encoded = Hamming::Encode(hamming, MatrixG);
				result.insert(result.end(), encoded.begin(), encoded.end());

				elemCount = 0;
				itBefore = it;
			}

			++elemCount;
		}

		// Padding the last part of message, and append the length of padding.

		hamming.assign(itBefore, huffman.end());
		while (hamming.size() < 26) hamming.push_back(0);

		encoded = Hamming::Encode(hamming, MatrixG);
		result.insert(result.end(), encoded.begin(), encoded.end());

		return 26 - elemCount;
	}

	inline std::vector<int> cvtDecToBin(int bitsFill) const
	{
		int currentIndex = 24 - static_cast<int>(std::log2(bitsFill));
		std::vector<int> result(26, 0);

		while (bitsFill > 0) {
			result.at(currentIndex) = bitsFill % 2;
			++currentIndex;
			bitsFill /= 2;
		}

		return Hamming::Encode(result, MatrixG);
	}
private:
	std::vector<int> MatrixG;
	std::wstring Text;
};

class Receiver
{
public:
	inline Receiver()
	{
		MatrixH = Hamming::MatrixH(5);
		MatrixR = Hamming::MatrixG(5);
	}
	inline ~Receiver() {}
public:
	inline void importMessage(const std::vector<int>& input) { Message = input; }

	inline std::wstring receiveMessage(const std::unordered_map<std::wstring, std::vector<int> >& codeDict) const
	{
		std::wstring result;
		auto temp = this->decodingMessage(Message);

		this->refusePadding(temp);

		result = Huffman::Decode(temp, codeDict);
		return result;
	}
private:
	inline std::vector<int> decodingMessage(const std::vector<int>& message) const
	{
		int elemCount = 0;
		std::vector<int> result;
		std::vector<int> decoded;
		std::vector<int> hamming;
		std::vector<int> recovered;
		size_t size = message.size();
		size_t capacity = (size / 31ULL + size % 31ULL) * 26ULL;

		hamming.reserve(capacity);
		auto itBefore = message.begin();
		for (auto it = message.begin(); it != message.end(); ++it) {
			if (elemCount >= 31) {
				hamming.assign(itBefore, it);
				recovered = Hamming::ErrorCorrect(hamming, MatrixH);

				decoded = Hamming::Decode(hamming, MatrixR);
				result.insert(result.end(), decoded.begin(), decoded.end());
			}

			++elemCount;
		}

		return result;
	}

	inline std::vector<int>& refusePadding(std::vector<int>& result) const
	{
		std::vector<int> temp(result.end() - 31, result.end());
		int bitsRemove = this->cvtBinToDec(temp) + 26;

		while (bitsRemove > 0) {
			result.erase(result.end());
			--bitsRemove;
		}

		return result;
	}

	inline int cvtBinToDec(const std::vector<int>& input) const
	{
		int result = 0;
		int temp = 1;

		for (auto it = input.rbegin(); it != input.rend(); ++it) {
			result = result + temp * (*it);
			temp <<= 1;
		}

		return result;
	}
private:
	std::vector<int> MatrixH;
	std::vector<int> MatrixR;
	std::vector<int> Message;
};

class ChapterFile
{
public:
	inline ChapterFile() {}
	inline ~ChapterFile() {}
public:

};

int main(void)
{
	std::vector<int> temp;
	int target = 13;

	while (target > 0) {
		temp.push_back(target % 2);
		target /= 2;
	}

	return 0;
}
