#pragma once
#include<vector>
#include<string>

namespace CP
{
	class Hamming
	{
	public:
		template<typename Type>
		static inline std::vector<Type> ArraySum(std::vector<Type> left, Type target);
	};

	template<typename Type>
	inline std::vector<Type> Hamming::ArraySum(std::vector<Type> left, Type target)
	{
		auto sum = [](const std::vector<Type>& vec) {Type result = Type(); for (const Type& it : vec) result += it; return result; };
		if (target <= 0) return std::vector<Type>();
		std::vector<Type> result;
		size_t index = 0;
		
		for (const Type& it : left)
		{
			std::vector<Type> temp = Hamming::ArraySum({ left.begin() + index + 1, left.end() }, target - it);
			result.insert(result.end(), temp.begin(), temp.end());
			if ((sum(result) + it) == target) {
				result.push_back(it);
				break;
			}

			++index;
		}

		return result;
	}
}
