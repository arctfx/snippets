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
	class IconButton : public sfg::Bin {
	public:
		typedef std::shared_ptr<IconButton> Ptr;
		typedef std::shared_ptr<const IconButton> PtrConst;

		static Ptr Create(const sf::String& image = L"");

		void SetImage(const sf::String& name = L"");

		const std::string& GetName() const override;

		void UpdateImageColor(sf::Color color);

	protected:
		IconButton() = default;

		std::unique_ptr<sfg::RenderQueue> InvalidateImpl() const override;

		sf::Vector2f CalculateRequisition() override;

	private:
		void HandleMouseEnter(int x, int y) override;

		void HandleMouseLeave(int x, int y) override;

		void HandleMouseButtonEvent(sf::Mouse::Button button, bool press, int x, int y) override;

		sf::Image m_image;
	};
}