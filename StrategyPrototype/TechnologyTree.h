#pragma once
// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include"Platform.h"

enum class TechClass {
	TECH_CLASS_INVALID = -1,

	TECH_CLASS_CIVILIAN = 0,
	TECH_CLASS_MILITARY = 1,
	TECH_CLASS_MAGICK = 2,
	TECH_CLASS_TECHNICAL = 3
};

enum class TechTier {
	TECH_TIER_INVALID = -1,

	TECH_TIER_1 = 0,
	TECH_TIER_2 = 1,
	TECH_TIER_3 = 2
};


struct Technology {
	/*
						Definitions:
	
	Every technology can be associated with a tech-class and a tech-tier.

	Every technology of a tech-class has a parent, and only one tech is the root.
	Thus, every tech has a set of childer.

	Every tech has some sort of requirements, without which it cant be researced,
	and allows the player to do something special after it was researched.

	Every tech has some amount of research points that must be invested in order to research it.

	Every technology can be either researched only by a special race or by all races.

	As we associate a tech with a tech-class, only research points made in that tech-class can be invested to research this tech.
	*/

	TechTier m_TechTier = TechTier::TECH_TIER_INVALID;
	TechClass m_TechClass = TechClass::TECH_CLASS_INVALID;

	std::vector<std::string> m_TechChildren;
	std::string m_TechParent;

	std::vector<std::string> m_TechRequirements;

	int m_ResearchPointsNeeded = -1;
	int m_ResearchPointsCurrentlyIncested = -1;

	std::string m_TechRace;

	std::string m_TechName;
};


namespace technologies {

	// Technical
	struct TechSmelting;
	struct TechMetallurgy;
	struct TechIronWorking;
	struct TechBronzeWorking;
	struct TechMining;
	struct TechStoneWorking;
	struct TechMasonry;
	struct TechArchitecture;
	struct TechFortification;
	struct TechEngineering;
	struct TechWoodWorking;
	struct TechBrickMaking;
	struct TechToolMaking;

	// Military
	struct TechHonor;
	struct TechWarriorCode;
	struct TechWarfareTheory;
	struct TechDefensiveStrategy;
	struct TechMediumArmor;
	struct TechHeavyArmor;
	struct TechArchery;
	struct TechMasteryOfArchery;
	struct TechJustCause;
	struct TechCrossbow;
	struct TechAggressiveStrategy;
	struct TechSiegeCraft;
	struct TechBallista;
	struct TechCatapult;
	struct TechTrebuchet;
	struct TechMagicalWarfare;
	struct TechMasteryOfMagicalWarfare;
	struct TechEnchantedArmor;
	struct TechMountedWarfare;
	struct TechCavalry;
	struct TechHeavyCavalry;
	struct TechAntiCavalryCavalry;
	struct TechHeavyAntiCavalryCavalry;

	// Magickal
	struct TechMedicine;
	struct TechMedication;
	struct TechIllusion;
	struct TechRestoration;
	struct TechPolytheism;
	struct TechKnowledgeOfMagicka;
	struct TechMysticism;
	struct TechCeremony;
	struct TechElementalism;
	struct TechAlteration;
	struct TechDestruction;
	struct TechAlchemy;
	struct TechSorcery;
	struct TechConjuration;
	struct TechEnchantement;

	// Civilian
	struct TechWisemenCircle;
	struct TechCouncil;
	struct TechPhilosophy;
	struct TechMathematics;
	struct TechAlphabet;
	struct TechWriting;
	struct TechLiterature;
	struct TechBartering;
	struct TechCurrency;
	struct TechHunting;
	struct TechAnimalHusbandry;
	struct TechAnimalMounting;
	struct TechFishing;
	struct TechSailing;
	struct TechMapMaking;
	struct TechAstronomy;
	struct TechCodeOfLaws;
	struct TechDiplomaticService;
	struct TechGuilds;
	struct TechAlcoholBrewing;
	struct TechBeverageMaking;
	struct TechSalting;
	struct TechPottery;
	struct TechJewelryMaking;
	struct TechFarming;








	namespace military {

		struct TechHonor : public Technology {
			TechHonor() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = ""; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Warrior Code");
			}
		};


		struct TechWarriorCode : public Technology {
			TechWarriorCode() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Honor"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Warfare Theory");
			}
		};




		struct TechWarfareTheory : public Technology {
			TechWarfareTheory() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Warrior Code"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("Bronze Working");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Defensive Strategy");
				m_TechChildren.push_back("Aggressive Strategy");
			}
		};



		struct TechDefensiveStrategy : public Technology {
			TechDefensiveStrategy() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Warfare Theory"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Medium Armor");
				m_TechChildren.push_back("Heavy Armor");
			}
		};



		struct TechMediumArmor : public Technology {
			TechMediumArmor() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Defensive Strategy"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("Iron Working");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};



		struct TechHeavyArmor : public Technology {
			TechHeavyArmor() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Defensive Strategy"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("Iron Working");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Just Cause");
			}
		};



		struct TechJustCause : public Technology {
			TechJustCause() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Heavy Armor"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("Enchanted Armor");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};




		struct TechArchery : public Technology {
			TechArchery() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Defensive Strategy"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("Hunting");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Mastery of Archery");
			}
		};




		struct TechMasteryOfArchery : public Technology {
			TechMasteryOfArchery() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Archery"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Crossbow");
			}
		};



		struct TechCrossbow : public Technology {
			TechCrossbow() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Mastery Of Archery"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};



		struct TechAggressiveStrategy : public Technology {
			TechAggressiveStrategy() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Warfare Theory"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Siege Craft");
				m_TechChildren.push_back("Magical Warfare");
				m_TechChildren.push_back("Mounted Warfare");

			}
		};




		struct TechSiegeCraft : public Technology {
			TechSiegeCraft() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Aggressive Strategy"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Ballista");

			}
		};




		struct TechBallista : public Technology {
			TechBallista() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Siege Craft"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("Archery");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Catapult");

			}
		};



		struct TechCatapult : public Technology {
			TechCatapult() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Ballista"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Trebuchet");

			}
		};



		struct TechTrebuchet : public Technology {
			TechTrebuchet() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Catapult"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("Mathematics");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");

			}
		};



		struct TechMagicalWarfare : public Technology {
			TechMagicalWarfare() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Aggressive Strategy"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("Knowledge Of Magicka");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Mastery Of Magickal Warfare");
				m_TechChildren.push_back("Enchanted Armor");


			}
		};



		struct TechMasteryOfMagicalWarfare : public Technology {
			TechMasteryOfMagicalWarfare() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Magical Warfare"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("Sorcery");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");

			}
		};



		struct TechEnchantedArmor : public Technology {
			TechEnchantedArmor() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Magical Warfare"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("Enchantement");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");

			}
		};




		struct TechMountedWarfare : public Technology {
			TechMountedWarfare() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Aggressive Strategy"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("Animal Mounting");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Cavalry");
				m_TechChildren.push_back("Anti-Cavalry Cavalry");

			}
		};



		struct TechCavalry : public Technology {
			TechCavalry() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Mounted Warfare"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Heavy Cavalry");
			}
		};



		struct TechAntiCavalryCavalry : public Technology {
			TechAntiCavalryCavalry() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Mounted Warfare"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Heavy Anti-Cavalry Cavalry");
			}
		};




		struct TechHeavyAntiCavalryCavalry : public Technology {
			TechHeavyAntiCavalryCavalry() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Anti-Cavalry Cavalry"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};



		struct TechHeavyCavalry : public Technology {
			TechHeavyCavalry() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MILITARY;

				m_TechParent = "Cavalry"; // It is the root.

				// Requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};
	}





	namespace civilian {

		struct TechPottery : public Technology {
			TechPottery() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = ""; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Salting");
			}
		};

		struct TechSalting : public Technology {
			TechSalting() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Pottery"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};

		struct TechBeverageMaking : public Technology {
			TechBeverageMaking() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Pottery"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Alcohol Brewing");
			}
		};

		struct TechAlcoholBrewing : public Technology {
			TechAlcoholBrewing() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Beverage Making"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};


		struct TechWisemenCircle : public Technology {
			TechWisemenCircle() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = ""; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Council");
			}
		};



		struct TechCouncil : public Technology {
			TechCouncil() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Wisemen Circle"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Philosophy");
			}
		};


		struct TechAlphabet : public Technology {
			TechAlphabet() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Wisemen Circle"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Writing");
			}
		};



		struct TechPhilosophy : public Technology {
			TechPhilosophy() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Council"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Mathematics");
			}
		};



		struct TechWriting : public Technology {
			TechWriting() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Alphabet"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Literature");
			}
		};




		struct TechMathematics : public Technology {
			TechMathematics() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Philosophy"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("Writing");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};




		struct TechLiterature : public Technology {
			TechLiterature() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Writing"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};



		struct TechCodeOfLaws : public Technology {
			TechCodeOfLaws() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Writing"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Diplomatic Service");
				m_TechChildren.push_back("Guilds");

			}
		};




		struct TechDiplomaticService : public Technology {
			TechDiplomaticService() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Code Of Laws"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};




		struct TechGuilds : public Technology {
			TechGuilds() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Code Of Laws"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};



		struct TechBartering : public Technology {
			TechBartering() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = ""; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Currency");
			}
		};




		struct TechCurrency : public Technology {
			TechCurrency() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Bartering"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Trade");
			}
		};


		struct TechJewelryMaking : public Technology {
			TechJewelryMaking() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Currency"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};


		struct TechTrade : public Technology {
			TechTrade() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Currency"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("Writing");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};



		struct TechHunting : public Technology {
			TechHunting() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = ""; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Animal Husbandry");
			}
		};

		struct TechClothing : public Technology {
			TechClothing() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Hunting"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};



		struct TechAnimalHusbandry : public Technology {
			TechAnimalHusbandry() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Hunting"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Animal Mounting");
			}
		};

		struct TechFarming : public Technology {
			TechFarming() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Animal Husbandry"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};

		struct TechAnimalMounting : public Technology {
			TechAnimalMounting() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Animal Husbandry"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};




		struct TechFishing : public Technology {
			TechFishing() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = ""; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Sailing");
			}
		};



		struct TechSailing : public Technology {
			TechSailing() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Fishing"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Map Making");
			}
		};


		struct TechMapMaking : public Technology {
			TechMapMaking() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Sailing"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("Writing");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};


		struct TechAstronomy : public Technology {
			TechAstronomy() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_CIVILIAN;

				m_TechParent = "Sailing"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};


	}






	namespace magick {

		struct TechCeremony : public Technology {
			TechCeremony() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MAGICK;

				m_TechParent = ""; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Mysticism");
			}
		};




		struct TechMysticism : public Technology {
			TechMysticism() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MAGICK;

				m_TechParent = "Ceremony"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Restoration");
				m_TechChildren.push_back("Elementalism");
				m_TechChildren.push_back("Knowledge Of Magicka");

			}
		};



		struct TechElementalism : public Technology {
			TechElementalism() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MAGICK;

				m_TechParent = "Mysticism"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Alteration");
				m_TechChildren.push_back("Destruction");
				m_TechChildren.push_back("Alchemy");

			}
		};



		struct TechAlteration : public Technology {
			TechAlteration() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MAGICK;

				m_TechParent = "Elementalism"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Sorcery");
			}
		};



		struct TechDestruction : public Technology {
			TechDestruction() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MAGICK;

				m_TechParent = "Elementalism"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Sorcery");
			}
		};



		struct TechAlchemy : public Technology {
			TechAlchemy() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MAGICK;

				m_TechParent = "Elementalism"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};




		struct TechRestoration : public Technology {
			TechRestoration() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MAGICK;

				m_TechParent = "Mysticism"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Medication");
			}
		};



		struct TechKnowledgeOfMagicka : public Technology {
			TechKnowledgeOfMagicka() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MAGICK;

				m_TechParent = "Mysticism"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Sorcery");
				m_TechChildren.push_back("Illusion");
				m_TechChildren.push_back("Polytheism");
			}
		};



		struct TechPolytheism : public Technology {
			TechPolytheism() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MAGICK;

				m_TechParent = "Knowledge Of Magicka"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};



		struct TechIllusion : public Technology {
			TechIllusion() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MAGICK;

				m_TechParent = "Knowledge Of Magicka"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Medication");
			}
		};


		struct TechMedication : public Technology {
			TechMedication() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MAGICK;

				m_TechParent = "Illusion"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Medicine");
			}
		};


		struct TechMedicine : public Technology {
			TechMedicine() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MAGICK;

				m_TechParent = "Medication"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};



		struct TechSorcery : public Technology {
			TechSorcery() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MAGICK;

				m_TechParent = "Destruction"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("Knowledge Of Magicka");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Conjuration");
			}
		};



		struct TechConjuration : public Technology {
			TechConjuration() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MAGICK;

				m_TechParent = "Sorcery"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};


		struct TechEnchantement : public Technology {
			TechEnchantement() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_MAGICK;

				m_TechParent = "Knowledge Of Magicka"; // It is the root.

				// Has no requirements.
				m_TechRequirements.push_back("");

				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			}
		};
		
	}

	namespace technical {

		struct TechWoodWorking : public Technology {
			TechWoodWorking() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_TECHNICAL;

				m_TechParent = ""; // It is the root.

				// Requierements...
				m_TechRequirements.push_back("");



				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Stone Working");
			};

		};




		struct TechStoneWorking : public Technology {
			TechStoneWorking() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_TECHNICAL;

				m_TechParent = "Wood Working"; // It is the root.

				// Requierements...
				m_TechRequirements.push_back("");



				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Masonry");
				m_TechChildren.push_back("Brick Making");
				m_TechChildren.push_back("Mining");

			};

		};



		struct TechBrickMaking : public Technology {
			TechBrickMaking() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_TECHNICAL;

				m_TechParent = "Stone Working"; // It is the root.

				// Requierements...
				m_TechRequirements.push_back("Pottery");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			};

		};




		struct TechMasonry : public Technology {
			TechMasonry() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_TECHNICAL;

				m_TechParent = "Stone Working"; // It is the root.

				// Requierements...
				m_TechRequirements.push_back("");



				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Architecture");
				m_TechChildren.push_back("Tool Making");

			};

		};


		struct TechToolMaking : public Technology {
			TechToolMaking() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_TECHNICAL;

				m_TechParent = "Masonry"; // It is the root.

				// Requierements...
				m_TechRequirements.push_back("");



				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");

			};

		};



		struct TechArchitecture : public Technology {
			TechArchitecture() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_TECHNICAL;

				m_TechParent = "Masonry"; // It is the root.

				// Requierements...
				m_TechRequirements.push_back("");



				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Fortification");
			};

		};




		struct TechFortification : public Technology {
			TechFortification() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_TECHNICAL;

				m_TechParent = "Architecture"; // It is the root.

				// Requierements...
				m_TechRequirements.push_back("Warfare Theory");



				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Engineering");
			};

		};





		struct TechEngineering : public Technology {
			TechEngineering() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_TECHNICAL;

				m_TechParent = "Fortification"; // It is the root.

				// Requierements...
				m_TechRequirements.push_back("Mathematics");



				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			};

		};





		struct TechMining : public Technology {
			TechMining() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_TECHNICAL;

				m_TechParent = "Stone Working"; // It is the root.

				// Requierements...
				m_TechRequirements.push_back("");



				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Bronze Working");
			};

		};



		struct TechBronzeWorking : public Technology {
			TechBronzeWorking() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_TECHNICAL;

				m_TechParent = "Mining"; // It is the root.

				// Requierements...
				m_TechRequirements.push_back("");


				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Iron Working");
			};

		};




		struct TechIronWorking : public Technology {
			TechIronWorking() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_TECHNICAL;

				m_TechParent = "Bronze Working"; // It is the root.

				// Requierements...
				m_TechRequirements.push_back("");



				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Metallurgy");
			};

		};



		struct TechMetallurgy : public Technology {
			TechMetallurgy() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_TECHNICAL;

				m_TechParent = "Iron Working"; // It is the root.

				// Requierements...
				m_TechRequirements.push_back("");



				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("Smelting");
			};

		};




		struct TechSmelting : public Technology {
			TechSmelting() {
				m_TechTier = TechTier::TECH_TIER_1;
				m_TechClass = TechClass::TECH_CLASS_TECHNICAL;

				m_TechParent = "Metallurgy"; // It is the root.

				// Requierements...
				m_TechRequirements.push_back("");



				m_ResearchPointsNeeded = 10;
				m_ResearchPointsCurrentlyIncested = 0;

				m_TechRace = "All"; // All races can research.

				// Children: what can be researched after it.
				m_TechChildren.push_back("");
			};

		};
	}


}


class TechnologyTree {
public:

	static TechnologyTree* Get() {

		if (g_pTechTree) return g_pTechTree;
		else {
			g_pTechTree = new TechnologyTree();
			return g_pTechTree;
		}
	}

	static void Del() {
		if (g_pTechTree) delete g_pTechTree;
	}


	std::map<std::string, Technology*> GetTechnologyMap() { return m_TechnologiesMap; }

private:
	static TechnologyTree* g_pTechTree;
	std::map<std::string, Technology*> m_TechnologiesMap;



private:
	TechnologyTree(){
		_initMap();
	}

	~TechnologyTree(){
		m_TechnologiesMap.clear();
	}

	void _initMap();
};