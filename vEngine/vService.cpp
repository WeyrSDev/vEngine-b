#include "vService.h"


namespace vEngine {
	Service::Service()
		: m_Services()
	{
	}

	void Service::AddService(UINT p_TypeID, void* p_Service)
	{
		m_Services.insert(std::pair<UINT, void*>(p_TypeID, p_Service));
	}

	void Service::RemoveService(UINT p_TypeID)
	{
		m_Services.erase(p_TypeID);
	}

	void* Service::GetService(UINT p_TypeID) const
	{
		std::map<UINT, void*>::const_iterator it = m_Services.find(p_TypeID);

		return (it != m_Services.end() ? it->second : nullptr);
	}
}