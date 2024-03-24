#pragma once
#include<vector>
#include<cmath>

namespace CP
{
	class Hamming
	{
	public:
		template<typename Type>
		static inline std::vector<Type> MatrixMultiplication(const std::vector<Type>& left, const std::vector<Type>& right);

		template<typename Type>
		static inline std::vector<Type> ArraySum(std::vector<Type> left, Type target);

		template<typename Type>
		static inline Type CvtBinToDec(const std::vector<Type>& input);

		template<typename Type>
		static inline bool IsTwoPower(Type num);
	};

	template<typename Type>
	inline std::vector<Type> Hamming::MatrixMultiplication(const std::vector<Type>& left, const std::vector<Type>& right)
	{
		if (left.empty() || right.empty()) return std::vector<Type>();
		size_t rightSize = right.size();
		size_t leftSize = left.size();

		if (leftSize % rightSize != 0) return std::vector<Type>();
		size_t round = leftSize / rightSize;
		std::vector<Type> result;

		for (size_t row = 0; row < round; row++)
		{
			Type temp = Type();

			for (size_t column = 0; column < rightSize; column++)
			{
				temp += left.at(column + row * rightSize) * right.at(column);
			}

			result.push_back(temp);
		}

		return result;
	}

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

	template<typename Type>
	inline Type Hamming::CvtBinToDec(const std::vector<Type>& input)
	{
		Type temp = Type(1);
		Type result = Type();
		for (auto& it : input) {
			result = result + it * temp;
			temp *= 2;
		}

		return temp;
	}

	template<typename Type>
	inline bool Hamming::IsTwoPower(Type num)
	{
		auto temp = log2(num);
		return (temp == static_cast<long long>(temp));
	}
}
