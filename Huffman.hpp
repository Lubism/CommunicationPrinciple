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

		for (auto& it : codeDict) {

		}

		std::vector<Type> temp;
		Key retSeek = Key();
		Key result = Key();

		for (const Type& it : input)
		{
			temp.push_back(it);
			retSeek = seek(temp);
			if (retSeek.size() != 0) {
				result = result + retSeek;
			}
		}

		return result;
	}
}
