#pragma once
#include "vInclude.h"

namespace vEngine {
	class Engine;
	class Time;
	class Component : public RTTI {
		RTTI_DECLARATIONS(Component, RTTI)
	public:
		Component();
		Component(Engine& p_Engine);
		virtual ~Component();
	private:
		Component(const Component& p_Rhs);
		Component& operator=(const Component& p_Rhs);
	public:
		Engine * GetEngine();
		void SetEngine(Engine& p_Engine);
		bool Enabled() const;
		void SetEnabled(bool p_Enabled);
		virtual void Initialize();
		virtual void Update(const Time& p_EngineTime);
	protected:
		Engine* m_Engine;
		bool m_Enabled;
	};
}