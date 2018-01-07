#include "vException.h"


namespace vEngine {
	Exception::Exception(const char* const& p_Message, HRESULT hr)
		: exception(p_Message), m_HR(hr)
	{
	}

	HRESULT Exception::HR() const
	{
		return m_HR;
	}

	std::wstring Exception::whatw() const
	{
		std::string whatString(what());
		std::wstring whatw;
		whatw.assign(whatString.begin(), whatString.end());

		return whatw;
	}
}