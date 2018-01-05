#include "vService.h"


namespace vEngine {
	Service::Service()
		: mServices()
	{
	}

	void Service::AddService(UINT typeID, void* service)
	{
		mServices.insert(std::pair<UINT, void*>(typeID, service));
	}

	void Service::RemoveService(UINT typeID)
	{
		mServices.erase(typeID);
	}

	void* Service::GetService(UINT typeID) const
	{
		std::map<UINT, void*>::const_iterator it = mServices.find(typeID);

		return (it != mServices.end() ? it->second : nullptr);
	}
}