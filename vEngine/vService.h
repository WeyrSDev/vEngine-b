#pragma once
#include "vInclude.h"

namespace vEngine {
	class Service
	{
	public:
		Service();
	private:
		Service(const Service& rhs);
		Service& operator=(const Service& rhs);
	public:
		void AddService(UINT typeID, void* service);
		void RemoveService(UINT typeID);
		void* GetService(UINT typeID) const;
	private:
		std::map<UINT, void*> mServices;
	};
}