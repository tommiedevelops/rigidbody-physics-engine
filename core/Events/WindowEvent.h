#pragma once

#include "Event.h"

namespace PhysicsEngine
{
	class WindowResizedEvent : public Event
	{
	public:
		
		int GetWidth() 
		{
			return m_Width;
		}
		int GetHeight() 
		{
			return m_Height;
		}

		EventType GetEventType() const override 
		{
			return EventType::WindowResize;
		}

		int GetCategoryFlags() const override
		{
			return EventCategory::EventCategoryWindow;
		}

		static EventType GetStaticType()
		{
			return EventType::WindowResize;
		}

		WindowResizedEvent(int width, int height) : m_Width{ width }, m_Height{ height } {}
	private:
		int m_Width;
		int m_Height;
	};
}
