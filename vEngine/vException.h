#pragma once
#include <exception>
#include <Windows.h>
#include <string>

namespace vEngine {
	class Exception : public std::exception
	{
	public:
		Exception(const char* const& p_Message, HRESULT hr = S_OK);
	public:
		HRESULT HR() const;
		std::wstring whatw() const;
	private:
		HRESULT m_HR;
	};
}