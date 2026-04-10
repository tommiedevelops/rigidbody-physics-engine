#pragma once

#include "Event.h"

namespace PhysicsEngine
{
	class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(int button) : m_Button{ button } {}

		EventType GetEventType() const override
		{
			return EventType::MouseButtonPressed;
		}

		int GetCategoryFlags() const override
		{
			return EventCategory::EventCategoryMouseButton;
		}

		static EventType GetStaticType() 
		{
			return EventType::MouseButtonPressed;
		}
	private:
		int m_Button;
	};
}