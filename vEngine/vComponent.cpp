#include "vComponent.h"
#include "vTime.h"

namespace vEngine {
	RTTI_DEFINITIONS(Component)

		Component::Component()
		: m_Engine(nullptr), m_Enabled(true)
	{
	}

	Component::Component(Engine& p_Engine)
		: m_Engine(&p_Engine), m_Enabled(true)
	{
	}

	Component::~Component()
	{
	}

	Engine* Component::GetEngine()
	{
		return m_Engine;
	}

	void Component::SetEngine(Engine& p_Engine)
	{
		m_Engine = &p_Engine;
	}

	bool Component::Enabled() const
	{
		return m_Enabled;
	}

	void Component::SetEnabled(bool p_Enabled)
	{
		m_Enabled = p_Enabled;
	}

	void Component::Initialize()
	{
	}

	void Component::Update(const Time& p_EngineTime)
	{
	}
}