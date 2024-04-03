/*
* The final project
* Keypoints:
* 
* Using huffman coding and hamming coding to archive the sending part and receiving part.
* Simulating the environment that can create an error on the whole bit stream.
* Reading the original file and spliting it depends on the keywords,
*	and then make them different chapters.
* 
* Offering the final result after the step of sending-receving, and giving the result of validation.
*/

#include"Hamming.hpp"
#include"Huffman.hpp"
#include<fstream>
#include<codecvt>
#include<locale>
#include<random>
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
	inline void importText(const std::string& input) { Text.assign(input); }

	inline std::vector<int> sendMessage(const std::unordered_map<std::string, std::vector<int> >& codeDict) const
	{
		if (Text.empty() || codeDict.empty()) return std::vector<int>();
		std::vector<int> result;

		auto bitsFill = this->encodeMessage(codeDict, result);
		auto temp = this->cvtDecToBin(bitsFill);

		result.insert(result.end(), temp.begin(), temp.end());
		return result;
	}
private:
	inline int encodeMessage(const std::unordered_map<std::string, std::vector<int> >& codeDict,
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
	std::string Text;
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

	inline std::string receiveMessage(const std::unordered_map<std::string, std::vector<int> >& codeDict) const
	{
		std::string result;
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

class Environment
{
public:
	inline Environment() {}
	inline ~Environment() {}
public:
	inline void createError(std::vector<int>& message)
	{
		std::random_device device;
		std::mt19937 seed(device());
		std::uniform_int_distribution<int> randGen(0, static_cast<int>(message.size()) - 1);

		message.at(randGen(seed)) ^= 1;
	}
};

// Convert the text from "utf-8 With BOM" to "GBK" before using this class.
// Other wise, this class will not run properly.
class FileSpliter
{
public:
	inline FileSpliter(const std::string& inputFile, const std::string& outputDir)
		:File(inputFile), Dir(outputDir){}
	inline ~FileSpliter() {}
public:
	inline bool engage() const
	{
		auto text = this->readFile();
		if (text.empty()) return false;
		auto chapter = this->splitChapter(text);

		this->writeFile(chapter);
		return true;
	}
private:
	inline void writeFile(const std::vector<std::string>& chapter) const
	{
		auto cvtNum = [](const int& num)
			{
				std::string result = "";
				if (num < 10) {
					result = result + "# 00" + std::to_string(num);
				}
				else if (num < 100) {
					result = result + "# 0" + std::to_string(num);
				}

				return result;
			};

		auto dir = Dir + ((Dir.back() == '\\') ? "" : "\\");
		int numCount = 1;

		for (auto& it : chapter)
		{
			ofstream writer(dir + cvtNum(numCount) + ".txt");
			writer << it;

			writer.close();
			++numCount;
		}
	}

	inline std::string readFile() const
	{
		ifstream reader(File);
		if (reader.fail()) return std::string();
		string text, temp;

		text.reserve(1ULL << 22);
		temp.reserve(1ULL << 22);

		while (reader) {
			reader >> temp;
			text += temp;
		}

		reader.close();
		return text;
	}

	inline std::vector<std::string> splitChapter(const std::string& text) const
	{
		std::vector<std::string> result(102);
		std::vector<long long> elem(6);
		auto size = text.size();
		long long right = 0;
		long long index = 0;
		result.clear();
		elem.clear();

		for (size_t it = 0; it < size; ++it) {
			index = this->findChapter(text, it);

			if (index >= 0) {
				elem.emplace_back(index);
				it = it + index;
			}
			else if (index == -1 && elem.size() == 1) {
				result.push_back(text.substr(
					elem.at(0))
				);

				break;
			}

			if (elem.size() >= 2) {
				result.push_back(text.substr(elem.at(0),
					elem.at(1) - elem.at(0))
				);

				elem.clear();
				elem.emplace_back(index);
			}
		}

		return result;
	}

	inline long long findChapter(const std::string& input, size_t offset) const
	{
		auto first = input.find(static_cast<char>('µÚ'), offset);
		if (first == string::npos)
			return -1LL;

		auto temp = input.substr(first, 6);
		auto second = temp.find(static_cast<char>('»Ø'));
		if (second == string::npos)
			return -2LL;

		return first;
	}
private:
	std::string File;
	std::string Dir;
};

// Read the target chapter file.
class ChapterReader
{
public:
	inline ChapterReader(const std::string& dir)
		:Dir(dir) {}
	inline ~ChapterReader() {}
public:
	inline std::string readChapter(int num) const
	{
		auto cvtNum = [](const int& num)
			{
				std::string result = "";
				if (num < 10) {
					result = result + "# 00" + std::to_string(num);
				}
				else if (num < 100) {
					result = result + "# 0" + std::to_string(num);
				}

				return result;
			};
		std::string result;
		auto dir = Dir + ((Dir.back() == '\\') ? "" : "\\") + cvtNum(num) + ".txt";

		ifstream reader(dir);
		if (reader.fail()) return std::string();

		reader >> result;
		return result;
	}
private:
	std::string Dir;
};

int main(void)
{
	return 0;
}
