#include "Level.h"
#include "tinyxml2.h"
#include <sstream>
#include <string>

using namespace tinyxml2;
Level::Level(const char* levelFilePath, int screenWidth, int screenHeight) {

	loadXml(levelFilePath);

	brickwidth = screenWidth / colcount - colspacing;
	brickheight = (screenHeight / 3) / rowcount - rowspacing;
	bricksRemaining = 0;

	for (int i = 0; i < rowcount; i++) {
		std::vector<Brick> row;
		for (int j = 0; j < colcount; j++) {
			if (brickLayout[i][j] == '_')
				continue;
			row.push_back(Brick(&(brickTypes.find(brickLayout[i][j])->second), j * (brickwidth + colspacing),
				i * (brickheight + rowspacing), brickwidth, brickheight));
			bricksRemaining++;
		}
		bricks.push_back(row);
	}
}

Level::~Level() {
	al_destroy_bitmap(background);
	for (std::pair<char, BrickType> p : brickTypes) {
		al_destroy_bitmap(p.second.texture);
		// destroy hit sample
		al_destroy_sample(p.second.hitSample);
		// destroy break sample
		al_destroy_sample(p.second.breakSample);
	}
}

void Level::drawBackground(int screenWidth, int screenHeight) {
	al_draw_scaled_bitmap(background, 0, 0, bgWidth, bgHeight, 0, 0, screenWidth, screenHeight, 0);
}


void Level::drawBricks() {
	for (std::vector<Brick> row : bricks) {
		for (Brick b : row) {
			if (b.active) {
				b.Draw();
			}
		}
	}
}

void Level::loadXml(const char* levelFilePath) {
	XMLDocument doc;
	doc.LoadFile(levelFilePath);
	XMLElement* pLevel = doc.RootElement();
	if (NULL != pLevel) {
		pLevel->QueryIntAttribute("RowCount", &rowcount);
		pLevel->QueryIntAttribute("ColumnCount", &colcount);
		pLevel->QueryIntAttribute("RowSpacing", &rowspacing);
		pLevel->QueryIntAttribute("ColumnSpacing", &colspacing);

		background = al_load_bitmap(pLevel->Attribute("BackgroundTexture"));
		bgWidth = al_get_bitmap_width(background);
		bgHeight = al_get_bitmap_height(background);

		XMLElement* pBrickTypes = pLevel->FirstChildElement("BrickTypes");
		if (NULL != pBrickTypes) {
			XMLElement* pBrickType = pBrickTypes->FirstChildElement("BrickType");
			while (pBrickType) {
				BrickType bt;
				const char* id = pBrickType->Attribute("Id");
				bt.texture = al_load_bitmap(pBrickType->Attribute("Texture"));
				if (std::string(pBrickType->Attribute("HitPoints")) == "Infinite") {
					bt.hitPoints = 1;
					bt.indestructible = true;
				}
				else {
					pBrickType->QueryIntAttribute("HitPoints", &bt.hitPoints);
					bt.indestructible = false;
				}
				// hit sound
				if (const char* hitsound = pBrickType->Attribute("HitSound"))
					bt.hitSample = al_load_sample(hitsound);
				else
					bt.hitSample = al_load_sample(DEFAULT_HIT_SOUND);
				// break sound
				if (const char* brsound = pBrickType->Attribute("BreakSound"))
					bt.breakSample = al_load_sample(brsound);
				else 
					bt.breakSample = al_load_sample(DEFAULT_HIT_SOUND);

				pBrickType->QueryIntAttribute("BreakScore", &bt.breakScore);

				brickTypes.insert(std::pair<char, BrickType>(*id, bt));

				pBrickType = pBrickType->NextSiblingElement("BrickType");
			}
		}

		XMLElement* pBricks = pLevel->FirstChildElement("Bricks");
		if (NULL != pBricks) {
			std::istringstream layoutText(pBricks->GetText());
			std::string line;
			char brickId;
			std::getline(layoutText, line);
			while (std::getline(layoutText, line)) {
				std::istringstream row(line);
				std::vector<char> brickRow;
				while (row >> brickId) {
					brickRow.push_back(brickId);
				}
				brickLayout.push_back(brickRow);
			}
		}
	}
}