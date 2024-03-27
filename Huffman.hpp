#pragma once
#include<unordered_map>
#include<functional>
#include<vector>
#include<queue>

namespace CP
{
	class Huffman
	{
	public:
		template<typename Key, typename Type>
		static inline std::vector<Type> Encode(const Key& input, const std::unordered_map<Key, std::vector<Type> >& codeDict);

		template<typename Key, typename Type>
		static inline Key Decode(const std::vector<Type>& input, const std::unordered_map<Key, std::vector<Type> >& codeDict);

		template<typename Key, typename Type>
		static inline std::unordered_map<Key, std::vector<Type> > CreateDict(const Key& input);
	private:
		template<typename Key, typename Type>
		struct Elem
		{
			std::unordered_map<Key, std::vector<Type> > Code;
			double Freq;
		public:
			inline Elem& operator=(const Elem& right) { Freq = right.Freq; Code = right.Code; return *this; }
			inline Elem(const Elem& right) { this->operator=(right); }
			inline Elem() : Freq(0.0) {}
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

	template<typename Key, typename Type>
	inline std::vector<Type> Huffman::Encode(const Key& input, const std::unordered_map<Key, std::vector<Type> >& codeDict)
	{
		std::vector<Type> result;
		Key temp = Key();

		for (auto& it : input)
		{
			temp = it;
			auto ptr = codeDict.find(temp);
			if (ptr == codeDict.end()) continue;

			result.insert(result.end(), ptr->second.begin(),
				ptr->second.end());
		}

		return result;
	}

	template<typename Key, typename Type>
	inline Key Huffman::Decode(const std::vector<Type>& input, const std::unordered_map<Key, std::vector<Type> >& codeDict)
	{
		auto seek = [&](const std::vector<Type>& vec) {
				for (auto& it : codeDict) {
					if (vec == it.second)
						return it.first;
				}
				return Key();
			};

		size_t maxSize = 0;
		for (auto& it : codeDict) {
			if (it.second.size() > maxSize) {
				maxSize = it.second.size();
			}
		}

		std::vector<Type> temp(maxSize + 2);
		Key retSeek = Key();
		Key result = Key();
		temp.clear();

		for (const Type& it : input)
		{
			temp.push_back(it);
			retSeek = seek(temp);
			if (retSeek.size() != 0) {
				result = result + retSeek;
				temp.clear();
			}
		}

		return result;
	}

	template<typename Key, typename Type>
	inline std::unordered_map<Key, std::vector<Type> > Huffman::CreateDict(const Key& input)
	{
		std::priority_queue<Elem<Key, Type> > result;
		std::unordered_map<Key, Type> freq;
		Elem<Key, Type> elem, left, right;
		Key temp = Key();

		for (auto& it : input) {
			temp = it;
			freq[temp] += 1LL;
		}

		for (auto& it : freq)
		{
			elem.Code[it.first] = std::vector<Type>();
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

			for (auto& it : right.Code) it.second.insert(it.second.begin(), Type(0));
			for (auto& it : left.Code) it.second.insert(it.second.begin(), Type(1));

			elem.Freq = left.Freq + right.Freq;
			elem.insert(right);
			elem.insert(left);

			result.push(elem);
			elem.clear();
		}

		elem = result.top();
		return elem.Code;
	}
}
