#pragma once

#define BIT(x) (1 << x)

namespace PhysicsEngine
{
	enum class EventType 
	{
		// Window
		WindowClose, WindowResize, WindowFocus, WindowLostFocus,

		// Keyboard
		KeyPressed, KeyReleased, KeyTyped,

		// Mouse
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,

	};
		
	enum EventCategory
	{
		EventCategoryNone        = 0,
		EventCategoryWindow     = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4),
	};

	class Event
	{
	public:
		virtual ~Event() = default;

		virtual EventType GetEventType()     const = 0;
		virtual int       GetCategoryFlags() const = 0;

		bool IsInCategory(EventCategory category) const 
		{
			return GetCategoryFlags() & category;
		}

		bool IsHandled()  const { return m_IsHandled; }
		void SetHandled() { m_IsHandled = true; }

	private:
		bool m_IsHandled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event) : m_Event(event) {}

		template<typename T, typename F>
		bool Dispatch(const F& func) 
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				if (func(static_cast<T&>(m_Event)))
					m_Event.SetHandled();
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

}














