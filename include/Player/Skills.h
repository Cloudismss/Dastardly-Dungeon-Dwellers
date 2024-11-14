#ifndef DASTARDLY_DUNGEON_DWELLERS_SKILLS_H
#define DASTARDLY_DUNGEON_DWELLERS_SKILLS_H

#include <string>

using std::string;

class Skills
{
private:
  // The 'Skills' class is completely linked with the 'Characters' class 
  // All Accessors & Mutators exist within 'Characters' class
  friend class Characters;

public:
  Skills(const string &className);
  ~Skills() { };

private:
  // Skill Variables
  string meleeName, magicName, rangedName;
  short unsigned int meleeCounter, magicCounter, rangedCounter;
  short unsigned int meleeLevel, rangedLevel, magicLevel;
  double critLevel;

public:
  // Helper Functions
  void readSkills(const string &className);
  void generateSkills(std::ofstream &defaultCharacterStats);
  void initSkillNames(const string &className);
};

#endif // DASTARDLY_DUNGEON_DWELLERS_SKILLS_H
