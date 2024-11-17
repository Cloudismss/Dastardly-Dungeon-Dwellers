#ifndef DASTARDLY_DUNGEON_DWELLERS_SKILLS_H
#define DASTARDLY_DUNGEON_DWELLERS_SKILLS_H

#include <string>
#include <unordered_map>

using std::unordered_map;

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
  short unsigned int meleeUpgradeTier = 0, magicUpgradeTier = 0, rangedUpgradeTier = 0;
  short unsigned int meleeCounter = 0, magicCounter = 0, rangedCounter = 0;
  short unsigned int meleeLevel = 0, rangedLevel = 0, magicLevel = 0;
  double critLevel = 1.0;

  // Map of skill names with array for indicating skill level - key is ability type [ Melee, Magic, or Ranged ]
  unordered_map<string, string [3]> skillNames;

private:
  // Helper Functions
  void readSkills(const string &className);
  void generateSkills(std::ofstream &defaultCharacterStats);
  void generateSkillNames(const string &className);
};

#endif // DASTARDLY_DUNGEON_DWELLERS_SKILLS_H
