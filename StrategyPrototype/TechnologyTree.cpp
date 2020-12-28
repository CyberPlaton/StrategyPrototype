#include"TechnologyTree.h"

TechnologyTree* TechnologyTree::g_pTechTree = nullptr;

void TechnologyTree::_initMap() {

	m_TechnologiesMap.emplace("Smelting", new technologies::technical::TechSmelting());
	m_TechnologiesMap.emplace("Metallurgy", new technologies::technical::TechMetallurgy());
	m_TechnologiesMap.emplace("Iron Working", new technologies::technical::TechIronWorking());
	m_TechnologiesMap.emplace("Bronze Working", new technologies::technical::TechBronzeWorking());
	m_TechnologiesMap.emplace("Mining", new technologies::technical::TechMining());
	m_TechnologiesMap.emplace("Stone Working", new technologies::technical::TechStoneWorking());
	m_TechnologiesMap.emplace("Masonry", new technologies::technical::TechMasonry());
	m_TechnologiesMap.emplace("Fortification", new technologies::technical::TechFortification());
	m_TechnologiesMap.emplace("Architecture", new technologies::technical::TechArchitecture());
	m_TechnologiesMap.emplace("Engineering", new technologies::technical::TechEngineering());
	m_TechnologiesMap.emplace("Wood Working", new technologies::technical::TechWoodWorking());
	m_TechnologiesMap.emplace("Brick Making", new technologies::technical::TechBrickMaking());
	m_TechnologiesMap.emplace("Tool Making", new technologies::technical::TechToolMaking());



	m_TechnologiesMap.emplace("Honor", new technologies::military::TechHonor());
	m_TechnologiesMap.emplace("Warrior Code", new technologies::military::TechWarriorCode());
	m_TechnologiesMap.emplace("Warfare Theory", new technologies::military::TechWarfareTheory());
	m_TechnologiesMap.emplace("Defensive Strategy", new technologies::military::TechDefensiveStrategy());
	m_TechnologiesMap.emplace("Medium Armor", new technologies::military::TechMediumArmor());
	m_TechnologiesMap.emplace("Heavy Armor", new technologies::military::TechHeavyArmor());
	m_TechnologiesMap.emplace("Archery", new technologies::military::TechArchery());
	m_TechnologiesMap.emplace("Mastery Of Archery", new technologies::military::TechMasteryOfArchery());
	m_TechnologiesMap.emplace("Just Cause", new technologies::military::TechJustCause());
	m_TechnologiesMap.emplace("Crossbow", new technologies::military::TechCrossbow());
	m_TechnologiesMap.emplace("Aggressive Strategy", new technologies::military::TechAggressiveStrategy());
	m_TechnologiesMap.emplace("Siege Craft", new technologies::military::TechSiegeCraft());
	m_TechnologiesMap.emplace("Ballista", new technologies::military::TechBallista());
	m_TechnologiesMap.emplace("Catapult", new technologies::military::TechCatapult());
	m_TechnologiesMap.emplace("Trebuchet", new technologies::military::TechTrebuchet());
	m_TechnologiesMap.emplace("Magical Warfare", new technologies::military::TechMagicalWarfare());
	m_TechnologiesMap.emplace("Mastery Of Magical Warfare", new technologies::military::TechMasteryOfMagicalWarfare());
	m_TechnologiesMap.emplace("Enchanted Armor", new technologies::military::TechEnchantedArmor());
	m_TechnologiesMap.emplace("Mounted Warfare", new technologies::military::TechMountedWarfare());
	m_TechnologiesMap.emplace("Cavalry", new technologies::military::TechCavalry());
	m_TechnologiesMap.emplace("Anti-Cavalry Cavalry", new technologies::military::TechAntiCavalryCavalry());
	m_TechnologiesMap.emplace("Heavy Cavalry", new technologies::military::TechHeavyCavalry());
	m_TechnologiesMap.emplace("Heavy Anti-Cavalry Cavalry", new technologies::military::TechHeavyAntiCavalryCavalry());





	m_TechnologiesMap.emplace("Medicine", new technologies::magick::TechMedicine());
	m_TechnologiesMap.emplace("Medication", new technologies::magick::TechMedication());
	m_TechnologiesMap.emplace("Illusion", new technologies::magick::TechIllusion());
	m_TechnologiesMap.emplace("Restoration", new technologies::magick::TechRestoration());
	m_TechnologiesMap.emplace("Polytheism", new technologies::magick::TechPolytheism());
	m_TechnologiesMap.emplace("Knowledge Of Magicka", new technologies::magick::TechKnowledgeOfMagicka());
	m_TechnologiesMap.emplace("Mysticism", new technologies::magick::TechMysticism());
	m_TechnologiesMap.emplace("Ceremony", new technologies::magick::TechCeremony());
	m_TechnologiesMap.emplace("Elementalism", new technologies::magick::TechElementalism());
	m_TechnologiesMap.emplace("Alteration", new technologies::magick::TechAlteration());
	m_TechnologiesMap.emplace("Destruction", new technologies::magick::TechDestruction());
	m_TechnologiesMap.emplace("Alchemy", new technologies::magick::TechAlchemy());
	m_TechnologiesMap.emplace("Sorcery", new technologies::magick::TechSorcery());
	m_TechnologiesMap.emplace("Conjuration", new technologies::magick::TechConjuration());
	m_TechnologiesMap.emplace("Enchantement", new technologies::magick::TechEnchantement());



	m_TechnologiesMap.emplace("Wisemen Circle", new technologies::civilian::TechWisemenCircle());
	m_TechnologiesMap.emplace("Council", new technologies::civilian::TechCouncil());
	m_TechnologiesMap.emplace("Alphabet", new technologies::civilian::TechAlphabet());
	m_TechnologiesMap.emplace("Writing", new technologies::civilian::TechWriting());
	m_TechnologiesMap.emplace("Literature", new technologies::civilian::TechLiterature());
	m_TechnologiesMap.emplace("Bartering", new technologies::civilian::TechBartering());
	m_TechnologiesMap.emplace("Currency", new technologies::civilian::TechCurrency());
	m_TechnologiesMap.emplace("Hunting", new technologies::civilian::TechHunting());
	m_TechnologiesMap.emplace("Animal Husbandry", new technologies::civilian::TechAnimalHusbandry());
	m_TechnologiesMap.emplace("Animal Mounting", new technologies::civilian::TechAnimalMounting());
	m_TechnologiesMap.emplace("Fishing", new technologies::civilian::TechFishing());
	m_TechnologiesMap.emplace("Sailing", new technologies::civilian::TechSailing());
	m_TechnologiesMap.emplace("Map Making", new technologies::civilian::TechMapMaking());
	m_TechnologiesMap.emplace("Astronomy", new technologies::civilian::TechSailing());
	m_TechnologiesMap.emplace("Code Of Laws", new technologies::civilian::TechCodeOfLaws());
	m_TechnologiesMap.emplace("Diplomatic Service", new technologies::civilian::TechDiplomaticService());
	m_TechnologiesMap.emplace("Guilds", new technologies::civilian::TechGuilds());
	m_TechnologiesMap.emplace("Farming", new technologies::civilian::TechFarming());
	m_TechnologiesMap.emplace("Jewelry Making", new technologies::civilian::TechJewelryMaking());
	m_TechnologiesMap.emplace("Pottery", new technologies::civilian::TechPottery());
	m_TechnologiesMap.emplace("Salting", new technologies::civilian::TechSalting());
	m_TechnologiesMap.emplace("Beverage Making", new technologies::civilian::TechBeverageMaking());
	m_TechnologiesMap.emplace("Alcohol Brewing", new technologies::civilian::TechAlcoholBrewing());

}