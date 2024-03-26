#pragma once
#include<unordered_map>
#include<functional>
#include<string>
#include<queue>

namespace CP
{
	class Huffman
	{
	public:
		template<typename Type, typename Arg>
		static inline std::unordered_map<Type, Arg> CreateDict(const Arg& input, std::function<Arg(int)> cvtFunc);

		template<typename Type, typename Arg>
		static inline Arg Encode(const Arg& input, const std::unordered_map<Type, Arg>& codeDict);

		template<typename Type, typename Arg>
		static inline Arg Decode(const Arg& input, const std::unordered_map<Type, Arg>& codeDict);
	public:
		static inline std::unordered_map<wchar_t, std::wstring> CreateDict(const std::wstring& input);
		static inline std::unordered_map<char, std::string> CreateDict(const std::string& input);
	private:
		template<typename Type, typename Arg>
		struct Elem
		{
			std::unordered_map<Type, Arg> Code;
			double Freq;
		public:
			inline Elem& operator=(const Elem& right) { Freq = right.Freq; Code = right.Code; return *this; }
			inline Elem(const Elem& right) { this->operator=(right); }
			inline Elem(): Freq(0.0) {}
		public:
			inline void insert(const Elem& right) { Code.insert(right.Code.begin(), right.Code.end()); }
			inline void clear() { Code.clear(); }
		public:
			inline bool operator==(const Elem& right) const { return Freq == right.Freq; }
			inline bool operator<=(const Elem& right) const { return Freq >= right.Freq; }
			inline bool operator>=(const Elem& right) const { return Freq <= right.Freq; }
			inline bool operator<(const Elem& right) const { return Freq > right.Freq; }
			inline bool operator>(const Elem& right) const { return Freq < right.Freq; }
		};
	};

	template<typename Type, typename Arg>
	inline std::unordered_map<Type, Arg> Huffman::CreateDict(const Arg& input, std::function<Arg(int)> cvtFunc)
	{
		std::priority_queue<Elem<Type, Arg> > result;
		std::unordered_map<Type, int> freq;
		Elem<Type, Arg> elem, left, right;
		for (auto& it : input)
			freq[it] += 1;

		for (auto& it : freq)
		{
			elem.Code[it.first] = Arg();
			elem.Freq = it.second;
			result.push(elem);
			elem.clear();
		}

		while (result.size() > 1)
		{
			left = result.top();
			result.pop();

			right = result.top();
			result.pop();

			for (auto& it : right.Code) it.second = cvtFunc(0) + it.second;
			for (auto& it : left.Code) it.second = cvtFunc(1) + it.second;

			elem.Freq = left.Freq + right.Freq;
			elem.insert(right);
			elem.insert(left);

			result.push(elem);
			elem.clear();
		}

		elem = result.top();
		return elem.Code;
	}

	template<typename Type, typename Arg>
	inline Arg Huffman::Encode(const Arg& input, const std::unordered_map<Type, Arg>& codeDict)
	{
		Arg result = Arg();

		for (auto& it : input)
		{
			auto ptr = codeDict.find(it);
			if (ptr == codeDict.end())
				continue;

			result += ptr->second;
		}

		return result;
	}

	template<typename Type, typename Arg>
	inline Arg Huffman::Decode(const Arg& input, const std::unordered_map<Type, Arg>& codeDict)
	{
		std::unordered_map<Arg, Type> inverted;
		Arg result = Arg();
		Arg temp = Arg();

		for (auto& it : codeDict) inverted[it.second] = it.first;
		for (auto& it : input)
		{
			temp += it;

			auto ptr = inverted.find(temp);
			if (ptr == inverted.end())
				continue;

			result += ptr->second;
			temp.clear();
		}

		return result;
	}

	inline std::unordered_map<wchar_t, std::wstring> Huffman::CreateDict(const std::wstring& input)
	{
		return Huffman::CreateDict<wchar_t, std::wstring>(
			input, static_cast<std::wstring(*)(int)>(
				std::to_wstring)
		);
	}

	inline std::unordered_map<char, std::string> Huffman::CreateDict(const std::string& input)
	{
		return Huffman::CreateDict<char, std::string>(
			input, static_cast<std::string(*)(int)>(
				std::to_string)
		);
	}
}
