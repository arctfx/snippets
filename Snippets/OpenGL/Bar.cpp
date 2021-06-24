#include "Bar.hpp"

namespace sfg {

Bar::Ptr Bar::Create(const sf::String& label)
{
	auto ptr = Ptr(new Bar);
	ptr->SetLabel(label);
	ptr->SetAllocation(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(0, 0)));
	return ptr;
}

const std::string& Bar::GetName() const
{
	static const std::string name("Bar");
	return name;
}

void Bar::SetLabel(const sf::String& label)
{
	m_label = label;
	RequestResize();
	Invalidate();
}

const sf::String& Bar::GetLabel() const
{
	return m_label;
}

std::unique_ptr<sfg::RenderQueue> Bar::InvalidateImpl() const
{ ///Called by SFGUI
	auto background_color = sfg::Context::Get().GetEngine().GetProperty<sf::Color>("BackgroundColor", shared_from_this());
	const auto& font_name = sfg::Context::Get().GetEngine().GetProperty<std::string>("FontName", shared_from_this());
	auto font_size = sfg::Context::Get().GetEngine().GetProperty<unsigned int>("FontSize", shared_from_this());
	const auto& font = sfg::Context::Get().GetEngine().GetResourceManager().GetFont(font_name);
	auto border_width = sfg::Context::Get().GetEngine().GetProperty<float>("BorderWidth", shared_from_this());
	auto border_color_shift = sfg::Context::Get().GetEngine().GetProperty<int>("BorderColorShift", shared_from_this());
	auto border_color = sfg::Context::Get().GetEngine().GetProperty<sf::Color>("BorderColor", shared_from_this());

	std::unique_ptr<sfg::RenderQueue> queue(new sfg::RenderQueue);

	if (GetLabel().getSize() > 0) {
		auto metrics = sfg::Context::Get().GetEngine().GetTextStringMetrics(GetLabel(), *font, font_size);
		metrics.y = sfg::Context::Get().GetEngine().GetFontLineHeight(*font, font_size);


		queue->Add(
			sfg::Renderer::Get().CreatePane(
				sf::Vector2f(0.f, 0.f),
				sf::Vector2f(GetAllocation().width, GetAllocation().height),
				border_width,
				background_color,
				border_color,
				border_color_shift
			)
		);

		sf::Text text(GetLabel(), *font, font_size);

		/// Edit text color in engine
		text.setFillColor(sf::Color::White);
		text.setPosition(border_width, (GetAllocation().height - metrics.y) / 2);
		queue->Add(sfg::Renderer::Get().CreateText(text));
	}

	return queue;
}

sf::Vector2f Bar::CalculateRequisition()
{
	float padding(sfg::Context::Get().GetEngine().GetProperty<float>("Padding", shared_from_this()));
	float spacing(sfg::Context::Get().GetEngine().GetProperty<float>("Spacing", shared_from_this()));
	const std::string& font_name(sfg::Context::Get().GetEngine().GetProperty<std::string>("FontName", shared_from_this()));
	unsigned int font_size(sfg::Context::Get().GetEngine().GetProperty<unsigned int>("FontSize", shared_from_this()));
	const sf::Font& font(*sfg::Context::Get().GetEngine().GetResourceManager().GetFont(font_name));

	auto requisition = sfg::Context::Get().GetEngine().GetTextStringMetrics(m_label, font, font_size);
	requisition.y = sfg::Context::Get().GetEngine().GetFontLineHeight(font, font_size);

	requisition.x += 2 * padding;
	requisition.y += 2 * padding;

	return requisition;
}

void Bar::HandleMouseEnter(int x, int y)
{
	//SetLabel( sf::String( "Mouse Enter: " + std::to_string( x ) + "," + std::to_string( y ) ) );

	if (GetState() == State::NORMAL) {
		SetState(State::PRELIGHT);
	}
}

void Bar::HandleMouseLeave(int x, int y)
{
	//SetLabel( sf::String( "Mouse Leave: " + std::to_string( x ) + "," + std::to_string( y ) ) );

	if (GetState() == State::PRELIGHT) {
		SetState(State::NORMAL);
	}
}

void Bar::HandleMouseButtonEvent(sf::Mouse::Button button, bool press, int x, int y)
{
	if (!IsMouseInWidget()) {
		if (GetState() == State::ACTIVE) {
			SetState(State::NORMAL);
		}

		return;
	}

	if (button == sf::Mouse::Left) {
		if (press) {
			//SetLabel( sf::String( "Mouse Left Press: " + std::to_string( x ) + "," + std::to_string( y ) ) );
			SetState(State::ACTIVE);
		}
		else if (GetState() == State::ACTIVE) {
			SetState(State::PRELIGHT);
		}
	}
}

}