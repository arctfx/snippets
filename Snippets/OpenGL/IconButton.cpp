#include "IconButton.hpp"

namespace sfg {

	IconButton::Ptr IconButton::Create(const sf::String& image) {
		auto ptr = Ptr(new IconButton);
		ptr->SetImage(image);
		ptr->SetAllocation(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(0, 0)));
		return ptr;
	}

	void IconButton::SetImage(const sf::String& name)
	{
		m_image.loadFromFile(name);
		UpdateImageColor(sf::Color::Color(160, 190, 240)); //160, 190, 240 - light blue //232, 58, 92 - light red
	}

	const std::string& IconButton::GetName() const {
		static const std::string name("IconButton");
		return name;
	}

	void IconButton::UpdateImageColor(sf::Color color)
	{
		for (unsigned int x = 0; x < m_image.getSize().x; x++)
			for (unsigned int y = 0; y < m_image.getSize().y; y++)
			{
				m_image.setPixel(x, y, sf::Color::Color(
					color.r,
					color.g,
					color.b,
					m_image.getPixel(x, y).a));
			}
	}

	std::unique_ptr<sfg::RenderQueue> IconButton::InvalidateImpl() const {
		auto border_color = sfg::Context::Get().GetEngine().GetProperty<sf::Color>("BorderColor", shared_from_this());
		auto border_color_shift = sfg::Context::Get().GetEngine().GetProperty<int>("BorderColorShift", shared_from_this());
		auto background_color = sfg::Context::Get().GetEngine().GetProperty<sf::Color>("BackgroundColor", shared_from_this());
		auto border_width = sfg::Context::Get().GetEngine().GetProperty<float>("BorderWidth", shared_from_this());
		const auto& font_name = sfg::Context::Get().GetEngine().GetProperty<std::string>("FontName", shared_from_this());
		auto font_size = sfg::Context::Get().GetEngine().GetProperty<unsigned int>("FontSize", shared_from_this());
		const auto& font = sfg::Context::Get().GetEngine().GetResourceManager().GetFont(font_name);

		auto m_texture = sfg::Renderer::Get().LoadTexture(m_image);

		if (GetState() == IconButton::State::ACTIVE) {
			border_color_shift = -border_color_shift;
		}

		std::unique_ptr<sfg::RenderQueue> queue(new sfg::RenderQueue);

		// Pane.
		queue->Add(
			sfg::Renderer::Get().CreatePane(
				sf::Vector2f(0.f, 0.f),
				sf::Vector2f(m_image.getSize().x, m_image.getSize().y),
				border_width,
				background_color,
				border_color,
				border_color_shift
			)
		);

		// Icon
		queue->Add(sfg::Renderer::Get().CreateSprite(
			sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(float(m_image.getSize().x), float(m_image.getSize().y))),
			m_texture,
			sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(float(m_image.getSize().x), float(m_image.getSize().y)))
		));



		return queue;
	}

	sf::Vector2f IconButton::CalculateRequisition() {
		auto requisition = sf::Vector2f(m_image.getSize().x, m_image.getSize().y);

		return requisition;
	}

	void IconButton::HandleMouseEnter(int x, int y) {
		if (GetState() == State::NORMAL) {
			SetState(State::PRELIGHT);
		}
	}

	void IconButton::HandleMouseLeave(int x, int y) {
		if (GetState() == State::PRELIGHT) {
			SetState(State::NORMAL);
		}
	}

	void IconButton::HandleMouseButtonEvent(sf::Mouse::Button button, bool press, int x, int y) {
		if (!IsMouseInWidget()) {
			if (GetState() == State::ACTIVE) {
				SetState(State::NORMAL);
			}

			return;
		}

		if (button == sf::Mouse::Left) {
			if (press) {
				SetState(State::ACTIVE);
			}
			else if (GetState() == State::ACTIVE) {
				SetState(State::PRELIGHT);
			}
		}
	}

}