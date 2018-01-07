#pragma once
#include "vInclude.h"

namespace vEngine {
	class Service
	{
	public:
		Service();
	private:
		Service(const Service& p_Rhs);
		Service& operator=(const Service& p_Rhs);
	public:
		void AddService(UINT p_TypeID, void* p_Service);
		void RemoveService(UINT p_TypeID);
		void* GetService(UINT p_TypeID) const;
	private:
		std::map<UINT, void*> m_Services;
	};
}