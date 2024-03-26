#pragma once
#include<vector>
#include<cmath>

namespace CP
{
	class Hamming
	{
	public:
		template<typename Type>
		static inline std::vector<Type> ErrorCorrect(const std::vector<Type>& message, const Type& bitsParity);

		template<typename Type>
		static inline Type ErrorDetect(const std::vector<Type>& message, const Type& bitsParity);

		template<typename Type>
		static inline std::vector<Type> Encode(const std::vector<Type>& message, const Type& bitsParity);

		template<typename Type>
		static inline std::vector<Type> Decode(const std::vector<Type>& message, const Type& bitsParity);
	public:
		template<typename Type>
		static inline std::vector<Type> MatrixHt(const Type& bitsParity);

		template<typename Type>
		static inline std::vector<Type> MatrixH(const Type& bitsParity);

		template<typename Type>
		static inline std::vector<Type> MatrixR(const Type& bitsParity);

		template<typename Type>
		static inline std::vector<Type> MatrixG(const Type& bitsParity);

		template<typename Type>
		static inline std::vector<Type> MatrixP(const Type& bitsParity);

		template<typename Type>
		static inline std::vector<Type> MatrixI(const Type& width);
	public:
		template<typename Type>
		static inline std::vector<Type> MatrixMulti(const std::vector<Type>& left, const std::vector<Type>& right);

		template<typename Type>
		static inline std::vector<Type> ArraySum(std::vector<Type> left, Type target);

		template<typename Type>
		static inline bool InList(const std::vector<Type>& left, const Type& target);

		template<typename Type>
		static inline std::vector<Type> BitListParity(const Type& bitsTotal);

		template<typename Type>
		static inline std::vector<Type> BitListData(const Type& bitsTotal);

		template<typename Type>
		static inline Type CvtBinToDec(const std::vector<Type>& input);

		template<typename Type>
		static inline Type CvtParityToData(const Type& bitsParity);

		template<typename Type>
		static inline Type CvtDataToParity(const Type& bitsData);

		template<typename Type>
		static inline bool IsTwoPower(Type num);
	private:
		template<typename Type>
		static inline std::vector<Type> Mod2Multi(const std::vector<Type>& left, const std::vector<Type>& right);
	};

	template<typename Type>
	inline std::vector<Type> Hamming::ErrorCorrect(const std::vector<Type>& message, const Type& bitsParity)
	{
		Type location = Hamming::ErrorDetect(message, bitsParity);
		if (location <= Type()) return message;

		std::vector<Type> result(message.begin(), message.end());
		result.at(location - 1) ^= Type(1);
		return result;
	}

	template<typename Type>
	inline Type Hamming::ErrorDetect(const std::vector<Type>& message, const Type& bitsParity)
	{
		std::vector<Type> Ht = Hamming::MatrixHt(bitsParity);
		std::vector<Type> H(Ht.begin(), Ht.end());
		std::vector<Type> temp;

		Type bitsTotal = Hamming::CvtParityToData(bitsParity) + bitsParity;
		Type errIndex = Type(), result = Type();
		temp.reserve(bitsParity);

		std::vector<Type> errList = Hamming::Mod2Multi(H, message);
		errIndex = Hamming::CvtBinToDec(errList) - 1;
		if (errIndex < Type()) return Type(-1);

		for (Type it = Type(); it < bitsParity; ++it) {
			temp.push_back(Ht.at(errIndex + it * bitsTotal));
		}

		result = Hamming::CvtBinToDec(temp);
		return result;
	}

	template<typename Type>
	inline std::vector<Type> Hamming::Encode(const std::vector<Type>& message, const Type& bitsParity)
	{
		std::vector<Type> G = Hamming::MatrixG(bitsParity);
		return Hamming::Mod2Multi(G, message);
	}

	template<typename Type>
	inline std::vector<Type> Hamming::Decode(const std::vector<Type>& message, const Type& bitsParity)
	{
		std::vector<Type> R = Hamming::MatrixR(bitsParity);
		return Hamming::Mod2Multi(R, message);
	}

	template<typename Type>
	inline std::vector<Type> Hamming::MatrixHt(const Type& bitsParity)
	{
		return Hamming::MatrixH(bitsParity);
	}

	template<typename Type>
	inline std::vector<Type> Hamming::MatrixH(const Type& bitsParity)
	{
		Type bitsData = Hamming::CvtParityToData(bitsParity);
		Type bitsTotal = bitsData + bitsParity;
		Type iIndex = Type(), pIndex = Type();

		std::vector<Type> I = Hamming::MatrixI(bitsParity);
		std::vector<Type> P = Hamming::MatrixP(bitsParity);
		std::vector<Type> result;

		result.reserve(bitsParity * bitsTotal + 2);
		for (Type row = Type(); row < bitsParity; ++row)
		{
			for (Type column = Type(1); column <= bitsTotal; ++column)
			{
				if (Hamming::IsTwoPower(column))
				{
					result.push_back(I.at(iIndex + row * bitsParity));
					++iIndex;
				}
				else
				{
					result.push_back(P.at(pIndex + row * bitsData));
					++pIndex;
				}
			}

			iIndex = Type();
			pIndex = Type();
		}

		return result;
	}

	template<typename Type>
	inline std::vector<Type> Hamming::MatrixR(const Type& bitsParity)
	{
		Type bitsData = Hamming::CvtParityToData(bitsParity);
		Type bitsTotal = bitsData + bitsParity;
		Type index = Type();

		std::vector<Type> I = Hamming::MatrixI(bitsData);
		std::vector<Type> result;

		result.reserve(bitsData * bitsTotal + 2);
		for (Type row = Type(); row < bitsData; ++row)
		{
			for (Type column = Type(1); column <= bitsTotal; ++column)
			{
				if (Hamming::IsTwoPower(column))
					result.push_back(Type());
				else
				{
					result.push_back(I.at(index + bitsData * row));
					++index;
				}
			}

			index = Type(0);
		}

		return result;
	}

	template<typename Type>
	inline std::vector<Type> Hamming::MatrixG(const Type& bitsParity)
	{
		Type bitsData = Hamming::CvtParityToData(bitsParity);
		Type bitsTotal = bitsData + bitsParity;
		Type pIndex = Type(), iIndex = Type();
		Type temp = Type();

		std::vector<Type> P = Hamming::MatrixP(bitsParity);
		std::vector<Type> I = Hamming::MatrixI(bitsData);
		std::vector<Type> result;

		result.reserve(bitsData * bitsTotal + 2);
		for (Type it = Type(1); it <= bitsTotal; ++it)
		{
			if (Hamming::IsTwoPower(it))
			{
				temp = bitsData * pIndex;

				for (Type elem = Type(0); elem < bitsData; elem++)
					result.push_back(P.at(elem + temp));

				++pIndex;
			}
			else
			{
				temp = bitsData * iIndex;

				for (Type elem = Type(0); elem < bitsData; elem++)
					result.push_back(I.at(elem + temp));

				++iIndex;
			}
		}

		return result;
	}

	template<typename Type>
	inline std::vector<Type> Hamming::MatrixP(const Type& bitsParity)
	{
		Type bitsData = Hamming::CvtParityToData(bitsParity);
		Type bitsTotal = bitsData + bitsParity;
		size_t index = 0LL;

		std::vector<Type> listParity = Hamming::BitListParity(bitsTotal);
		std::vector<Type> listData = Hamming::BitListData(bitsTotal);
		std::vector<Type> result;

		std::vector<std::vector<Type> > temp;
		result.reserve(bitsData * bitsParity + 2);
		for (const Type& it : listData) temp.push_back(Hamming::ArraySum(listParity, it));

		for (const Type& elem : listParity) {
			for (const Type& it : listData)
			{
				if (Hamming::InList(temp.at(index), elem))
					result.push_back(Type(1));
				else
					result.push_back(Type(0));

				++index;
			}

			index = 0;
		}

		return result;
	}

	template<typename Type>
	inline std::vector<Type> Hamming::MatrixI(const Type& width)
	{
		std::vector<Type> result;
		result.reserve(width * width + 2);
		for (Type row = Type(); row < width; ++row)
		{
			for (Type column = Type(); column < width; ++column)
			{
				if (row == column)
					result.push_back(Type(1));
				else
					result.push_back(Type(0));
			}
		}

		return result;
	}

	template<typename Type>
	inline std::vector<Type> Hamming::MatrixMulti(const std::vector<Type>& left, const std::vector<Type>& right)
	{
		if (left.empty() || right.empty()) return std::vector<Type>();
		size_t rightSize = right.size();
		size_t leftSize = left.size();

		if (leftSize % rightSize != 0) return std::vector<Type>();
		size_t round = leftSize / rightSize;
		std::vector<Type> result;

		result.reserve(round + 2);
		for (size_t row = 0; row < round; ++row)
		{
			Type temp = Type();

			for (size_t column = 0; column < rightSize; ++column)
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
	inline bool Hamming::InList(const std::vector<Type>& left, const Type& target)
	{
		for (const Type& it : left)
			if (it == target)
				return true;

		return false;
	}

	template<typename Type>
	inline std::vector<Type> Hamming::BitListParity(const Type& bitsTotal)
	{
		std::vector<Type> result;

		for (Type it = Type(1); it <= bitsTotal; ++it)
			if (Hamming::IsTwoPower(it))
				result.push_back(it);

		return result;
	}

	template<typename Type>
	inline std::vector<Type> Hamming::BitListData(const Type& bitsTotal)
	{
		std::vector<Type> result;

		for (Type it = Type(1); it <= bitsTotal; ++it)
			if (!Hamming::IsTwoPower(it))
				result.push_back(it);

		return result;
	}

	template<typename Type>
	inline Type Hamming::CvtBinToDec(const std::vector<Type>& input)
	{
		Type temp = Type(1);
		Type result = Type();
		for (auto it = input.rbegin(); it != input.rend(); ++it)
		{
			result = result + (*it) * temp;
			temp *= 2;
		}

		return result;
	}

	template<typename Type>
	inline Type Hamming::CvtParityToData(const Type& bitsParity)
	{
		long long numPow = static_cast<long long>(std::pow(2, bitsParity));
		return static_cast<Type>(numPow - bitsParity - 1);
	}

	template<typename Type>
	inline Type Hamming::CvtDataToParity(const Type& bitsData)
	{
		long long powNum = 0;
		long long maxBits = 1LL << 31;
		for (long long it = 0; it < maxBits; ++it)
		{
			powNum = static_cast<long long>(std::pow(2, it));
			if (powNum - it - 1 >= bitsData) {
				return static_cast<Type>(it);
			}
		}

		return Type();
	}

	template<typename Type>
	inline bool Hamming::IsTwoPower(Type num)
	{
		auto temp = log2(num);
		return (temp == static_cast<long long>(temp));
	}

	template<typename Type>
	inline std::vector<Type> Hamming::Mod2Multi(const std::vector<Type>& left, const std::vector<Type>& right)
	{
		std::vector<Type> result = Hamming::MatrixMulti(left, right);
		for (Type& it : result) it %= Type(2);
		return result;
	}
}
