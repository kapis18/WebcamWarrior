#include "SliderSFML.hpp"

SliderSFML::SliderSFML()
{
	xCord = 0;
	yCord = 0;
	axisHeight = 0;
	axisWidth = 0;
	sliderWidth = 0;
	sliderHeight = 0;

	if (!font.loadFromFile("Neon.ttf"))
		std::cout << "Error loading font\n";

	text.setFont(font);
	text.setFillColor(sf::Color::White);

	axis.setPosition(0, 0);
	axis.setOrigin(0, axisHeight / 2);
	axis.setSize(sf::Vector2f(axisWidth, axisHeight));
	axis.setFillColor(sf::Color(63, 63, 63));
	slider.setPosition(0, 0);
	slider.setOrigin(sliderWidth / 2, sliderHeight / 2);
	slider.setSize(sf::Vector2f(sliderWidth, sliderHeight));
	slider.setFillColor(sf::Color(192, 192, 192));
}

SliderSFML::SliderSFML(int x, int y, int length)
{
	xCord = x;
	yCord = y;
	axisHeight = 10;
	axisWidth = length;
	sliderWidth = 20;
	sliderHeight = 30;

	if (!font.loadFromFile("Neon.ttf"))
		std::cout << "Error loading font\n";

	text.setFont(font);
	text.setFillColor(sf::Color::White);

	axis.setPosition(x, y);
	axis.setOrigin(0, axisHeight / 2);
	axis.setSize(sf::Vector2f(axisWidth, axisHeight));
	axis.setFillColor(sf::Color(63, 63, 63));
	slider.setPosition(x, y);
	slider.setOrigin(sliderWidth / 2, sliderHeight / 2);
	slider.setSize(sf::Vector2f(sliderWidth, sliderHeight));
	slider.setFillColor(sf::Color(192, 192, 192));
}

void SliderSFML::setSlider(int x, int y, int length)
{
	xCord = x;
	yCord = y;
	axisHeight = 10;
	axisWidth = length;
	sliderWidth = 20;
	sliderHeight = 30;

	axis.setPosition(x, y);
	axis.setOrigin(0, axisHeight / 2);
	axis.setSize(sf::Vector2f(axisWidth, axisHeight));
	axis.setFillColor(sf::Color(63, 63, 63));
	slider.setPosition(x, y);
	slider.setOrigin(sliderWidth / 2, sliderHeight / 2);
	slider.setSize(sf::Vector2f(sliderWidth, sliderHeight));
	slider.setFillColor(sf::Color(192, 192, 192));
}

sf::Text SliderSFML::returnText(int x, int y, std::string z, int fontSize)
{
	text.setCharacterSize(fontSize);
	text.setPosition(x, y);
	text.setString(z);
	return text;
}

void SliderSFML::create(int min, int max)
{
	sliderValue = min;
	minValue = min;
	maxValue = max;
}
void SliderSFML::logic(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (sf::Mouse::getPosition(window).x >= xCord && sf::Mouse::getPosition(window).x <= xCord + axisWidth &&
			sf::Mouse::getPosition(window).y >= yCord - 100 && sf::Mouse::getPosition(window).y <= yCord + 100)
		{
			slider.setPosition(sf::Mouse::getPosition(window).x, yCord);
			sliderValue = (minValue + ((slider.getPosition().x - xCord) / axisWidth * (maxValue - minValue)));
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sliderValue > 0)
	{
		slider.setPosition(slider.getPosition().x - 1, yCord);
		sliderValue--;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sliderValue < 255)
	{
		slider.setPosition(slider.getPosition().x + 1, yCord);
		sliderValue++;
	}

}

float SliderSFML::getSliderValue()
{
	return sliderValue;
}

void SliderSFML::setSliderValue(float newValue)
{
	if (newValue >= minValue && newValue <= maxValue)
	{
		sliderValue = newValue;
		float diff = maxValue - minValue;
		float diff2 = newValue - minValue;
		float zzz = axisWidth / diff;
		float posX = zzz * diff2;
		posX += xCord;
		slider.setPosition(posX, yCord);
	}
}

void SliderSFML::setSliderPercentValue(float newPercentValue)
{
	if (newPercentValue >= 0 && newPercentValue <= 100)
	{
		sliderValue = newPercentValue / 100 * maxValue;
		slider.setPosition(xCord + (axisWidth * newPercentValue / 100), yCord);
	}
}

void SliderSFML::draw(sf::RenderWindow& window)
{
	logic(window);
	window.draw(returnText(xCord - 10, yCord + 5, std::to_string(minValue), 20));
	window.draw(axis);
	window.draw(returnText(xCord + axisWidth - 10, yCord + 5, std::to_string(maxValue), 20));
	window.draw(slider);
	window.draw(returnText(slider.getPosition().x - sliderWidth, slider.getPosition().y - sliderHeight,
		std::to_string((int)sliderValue), 15));
}
