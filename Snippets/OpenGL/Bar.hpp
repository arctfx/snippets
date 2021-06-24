#pragma once
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFGUI/RenderQueue.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/String.hpp>
#include <memory>
#include <string>
#include <iostream>

namespace sfg {

class Bar : public Widget {
public:
	typedef std::shared_ptr<Bar> Ptr;
	typedef std::shared_ptr<const Bar> PtrConst;

	static Ptr Create(const sf::String& label = L"");
	const std::string& GetName() const override;
	void SetLabel(const sf::String& label);
	const sf::String& GetLabel() const;

protected:
	/// The widget constructor is usually protected so it can only be created through the Create() method.
	Bar() {}

	std::unique_ptr<RenderQueue> InvalidateImpl() const override;
	sf::Vector2f CalculateRequisition() override;

private:
	// This handler handles mouse enter events.
	void HandleMouseEnter(int x, int y) override;

	// This handler handles mouse leave events.
	void HandleMouseLeave(int x, int y) override;

	// This handler handles mouse button events
	void HandleMouseButtonEvent(sf::Mouse::Button button, bool press, int x, int y) override;

	sf::String m_label;
};

}