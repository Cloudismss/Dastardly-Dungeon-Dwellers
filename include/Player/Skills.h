#ifndef DASTARDLY_DUNGEON_DWELLERS_SKILLS_H
#define DASTARDLY_DUNGEON_DWELLERS_SKILLS_H

#include <string>

using std::string;

class Skills
{
private:
  friend class Characters;

public:
  Skills(const string &className);
  ~Skills() { };

private:
  // Skill Variables
  string meleeName, magicName, rangedName;
  short unsigned int meleeCounter, magicCounter, rangedCounter;
  short unsigned int meleeSkill, rangedSkill, magicSkill;
  double critSkill;

public:
  // Accessors
  int getSkillTier(const string &battleMenuSelection);
  short unsigned int getMeleeSkill() { return meleeSkill; }
  short unsigned int getMagicSkill() { return magicSkill; }
  short unsigned int getRangedSkill() { return rangedSkill; }
  double getCritSkill() { return critSkill; }

  // Helper Functions
  void generateSkills(std::ofstream &defaultCharacterStats);
  void readSkills(const string &className);
  void initSkillNames(const string &className);
  void setSkillName(const string &skillType, string &upgradeMessage, const string &className, int tier);
  string getSkillName(const string &skillType);
  void useSkill(const string &battleMenuSelection, const string &className);
};

#endif //DASTARDLY_DUNGEON_DWELLERS_SKILLS_H