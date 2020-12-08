#include "GUI.h"
#include "Settings.h"
#include "Player.h"
#include "Game.h"

using namespace tgui;
using namespace sf;

void GUI::createGUI() {
	this->createResourceBar();
	this->createSelectionWindow();
}

void GUI::createResourceBar() {

	sf::Texture goldTexture;
	if (!goldTexture.loadFromFile("images/icon_gold.png")) {
		std::cout << "Can't load image" << std::endl;
	}

	sf::Texture scienceTexture;
	if (!scienceTexture.loadFromFile("images/icon_science.png")) {
		std::cout << "Can't load image" << std::endl;
	}

	sf::Texture cultureTexture;
	if (!cultureTexture.loadFromFile("images/icon_culture.png")) {
		std::cout << "Can't load image" << std::endl;
	}

	auto pnlResources = Panel::create({ "100%","3%" });
	pnlResources->getRenderer()->setBackgroundColor(sf::Color(60, 60, 60, 220));
	this->gui.add(pnlResources, "pnlResources");

	auto lblGold = Label::create("0 G");
	pnlResources->add(lblGold, "lblGold");
	lblGold->getRenderer()->setTextColor(sf::Color(255, 215, 0));
	lblGold->getRenderer()->setTextStyle(TextStyle::Bold);
	lblGold->setOrigin(0.0f, 0.5f);
	lblGold->setPosition("3%", "50%");
	lblGold->setTextSize(Settings::screenHeight * 0.02f);
	lblGold->setVerticalAlignment(Label::VerticalAlignment::Center);
	lblGold->setHorizontalAlignment(Label::HorizontalAlignment::Center);

	auto goldIcon = Picture::create(goldTexture);
	pnlResources->add(goldIcon, "icoGold");
	goldIcon->setOrigin(0.5f, 0.5f);
	goldIcon->setPosition("2%", "50%");

	auto scienceIcon = Picture::create(scienceTexture);
	pnlResources->add(scienceIcon, "icoScience");
	scienceIcon->setOrigin(0.5f, 0.5f);
	scienceIcon->setPosition("24%", "50%");

	auto cultureIcon = Picture::create(cultureTexture);
	pnlResources->add(cultureIcon, "icoCulture");
	cultureIcon->setOrigin(0.5f, 0.5f);
	cultureIcon->setPosition("14%", "50%");

	auto lblCulture = Label::create("0 C");
	pnlResources->add(lblCulture, "lblCulture");
	lblCulture->getRenderer()->setTextColor(sf::Color(191, 0, 230));
	lblCulture->getRenderer()->setTextStyle(TextStyle::Bold);
	lblCulture->setOrigin(0.0f, 0.5f);
	lblCulture->setPosition("15%", "50%");
	lblCulture->setTextSize(Settings::screenHeight * 0.02f);
	lblCulture->setVerticalAlignment(Label::VerticalAlignment::Center);
	lblCulture->setHorizontalAlignment(Label::HorizontalAlignment::Center);

	auto lblScience = Label::create("0 S");
	pnlResources->add(lblScience, "lblScience");
	lblScience->getRenderer()->setTextColor(sf::Color(0, 175, 255));
	lblScience->getRenderer()->setTextStyle(TextStyle::Bold);
	lblScience->setOrigin(0.0f, 0.5f);
	lblScience->setPosition("25%", "50%");
	lblScience->setTextSize(Settings::screenHeight * 0.02f);
	lblScience->setVerticalAlignment(Label::VerticalAlignment::Center);
	lblScience->setHorizontalAlignment(Label::HorizontalAlignment::Center);
}

void GUI::createSelectionWindow() {
	auto pnlSelection = Panel::create({ "15%","90%" });
	pnlSelection->getRenderer()->setBackgroundColor(sf::Color(60, 60, 60, 220));
	pnlSelection->setPosition("84%", "5%");
	this->gui.add(pnlSelection, "pnlSelection");

	auto lblPosition = Label::create("x: y:");
	pnlSelection->add(lblPosition, "lblPosition");
	lblPosition->setOrigin(0.0f, 0.5f);
	lblPosition->getRenderer()->setTextColor(sf::Color(255, 255, 255));
	lblPosition ->setTextSize(Settings::screenHeight * 0.02f);
	lblPosition->setPosition("5%", "10%");
	lblPosition->setVerticalAlignment(Label::VerticalAlignment::Center);
	lblPosition->setHorizontalAlignment(Label::HorizontalAlignment::Center);

	auto lblOwner = Label::create("Owned by: ");
	pnlSelection->add(lblOwner, "lblOwner");
	lblOwner->setOrigin(0.0f, 0.5f);
	lblOwner->getRenderer()->setTextColor(sf::Color(255, 255, 255));
	lblOwner->setTextSize(Settings::screenHeight * 0.02f);
	lblOwner->setPosition("5%", "15%");
	lblOwner->setVerticalAlignment(Label::VerticalAlignment::Center);
	lblOwner->setHorizontalAlignment(Label::HorizontalAlignment::Center);
}

void GUI::update() {
	this->updateResourceLabels();
	this->updateSelection();
}

void GUI::updateResourceLabels() {

	if (Game::getCurrentPlayer()) {
		auto gold = this->gui.get<Label>("lblGold");
		gold->setTextSize(Settings::screenHeight * 0.02f);
		gold->setText(std::to_string(Game::getCurrentPlayer()->getGold()) + " G");

		auto culture = this->gui.get<Label>("lblCulture");
		culture->setTextSize(Settings::screenHeight * 0.02f);
		culture->setText(std::to_string(Game::getCurrentPlayer()->getCulture()) + " C");

		auto science = this->gui.get<Label>("lblScience");
		science->setTextSize(Settings::screenHeight * 0.02f);
		science->setText(std::to_string(Game::getCurrentPlayer()->getScience()) + " S");
	}

	auto goldIcon = this->gui.get<Picture>("icoGold");
	goldIcon->setHeight("100%");
	goldIcon->setWidth(goldIcon->getSize().y);

	auto scienceIcon = this->gui.get<Picture>("icoScience");
	scienceIcon->setHeight("100%");
	scienceIcon->setWidth(scienceIcon->getSize().y);

	auto cultureIcon = this->gui.get<Picture>("icoCulture");
	cultureIcon->setHeight("100%");
	cultureIcon->setWidth(cultureIcon->getSize().y);

}

void GUI::updateSelection() {
	auto pnlSelection = this->gui.get<Panel>("pnlSelection");
	auto lblPosition = pnlSelection->get<Label>("lblPosition");
	lblPosition->setTextSize(Settings::screenHeight * 0.02f);

	auto lblOwner = pnlSelection->get<Label>("lblOwner");
	lblOwner->setTextSize(Settings::screenHeight * 0.02f);

	if (Game::getSelectedHex()) {
		pnlSelection->setVisible(true);
		Hex& hex = *Game::getSelectedHex();
		lblPosition->setText("x: " + std::to_string(hex.getX()) + "\t y: " + std::to_string(hex.getZ()));
		std::string owner;
		if (hex.getOwner())
			owner = hex.getOwner()->getName();
		else
			owner = "None";
		lblOwner->setText("Owned by: " + owner);
	}
	else {
		pnlSelection->setVisible(false);
	}
}