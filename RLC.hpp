#pragma once
#include<functional>
#include<string>

namespace CP
{
	class RLC
	{
	public:
		template<typename Arg>
		static inline Arg Improved(const Arg& input, std::function<Arg(int)> cvtFunc);

		template<typename Arg>
		static inline Arg Basic(const Arg& input, std::function<Arg(int)> cvtFunc);
	public:
		static inline std::wstring Improved(const std::wstring& input);
		static inline std::string Improved(const std::string& input);
		static inline std::wstring Basic(const std::wstring& input);
		static inline std::string Basic(const std::string& input);
	};

	template<typename Arg>
	static inline Arg RLC::Improved(const Arg& input, std::function<Arg(int)> cvtFunc)
	{
		if (input.size() == 0) return Arg();
		auto before = input.at(0);
		Arg result = Arg();
		int count = 0;

		for (auto& it : input) {
			if (it != before) {
				if (count > 1) result += cvtFunc(count);
				result += before;
				count = 1;
			}
			else if (count < 9)
				++count;
			else
			{
				result += cvtFunc(count);
				result += before;
				count = 1;
			}

			before = it;
		}

		if (count > 1) result += cvtFunc(count);
		result += before;

		return result;
	}

	template<typename Arg>
	static inline Arg RLC::Basic(const Arg& input, std::function<Arg(int)> cvtFunc)
	{
		if (input.size() == 0) return Arg();
		auto before = input.at(0);
		Arg result = Arg();
		int count = 0;

		for (auto& it : input) {
			if (it != before) {
				result += cvtFunc(count);
				result += before;
				count = 1;
			}
			else if (count < 9)
				++count;
			else
			{
				result += cvtFunc(count);
				result += before;
				count = 1;
			}

			before = it;
		}

		result += cvtFunc(count);
		result += before;

		return result;
	}

	inline std::wstring RLC::Improved(const std::wstring& input)
	{
		return RLC::Improved<std::wstring>(input, static_cast<std::wstring(*)(int)>(
			std::to_wstring));
	}

	inline std::string RLC::Improved(const std::string& input)
	{
		return RLC::Improved<std::string>(input, static_cast<std::string(*)(int)>(
			std::to_string));
	}

	inline std::wstring RLC::Basic(const std::wstring& input)
	{
		return RLC::Improved<std::wstring>(input, static_cast<std::wstring(*)(int)>(
			std::to_wstring));
	}

	inline std::string RLC::Basic(const std::string& input)
	{
		return RLC::Improved<std::string>(input, static_cast<std::string(*)(int)>(
			std::to_string));
	}
}
