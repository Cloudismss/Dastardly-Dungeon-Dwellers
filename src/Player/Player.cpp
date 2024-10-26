#include "Player.h"

#include <iostream>

#include "Art.h"
#include "Validation.h"

using std::cin;
using std::cout;

Player::Player()
{
  health = 20.0;
  className = " ";
  gold = 0;
  potions = 3;
  armor = 0;
  keys = 0;
  meleeWeapon = 1;
  magicWeapon = 1;
  rangedWeapon = 1;
  rooms = 0;
  progression = 0;

  // Class selection menu
  classSelection();

  // Initialize skills
  skills = new Skills(className);

  // DEBUG Option - Extra potions, gold, keys
  if (debug)
  {
    health = 100.0;
    potions = 100;
    gold = 1000;
    keys = 10;
  }
}

// Pre-condition: passed className
// Post-condition: displays class selection menu and stores result in className
void Player::classSelection()
{
  bool loopFlag = true;
  do
  {
    short int classChoice = 0;
    cout << ".-------------------------------------------------------------.\n"
         << "|                                                             |\n"
         << "|           Please choose a class using numbers 1-3:          |\n"
         << "|                                                             |\n"
         << "|            1. Warrior             Skill: Melee              |\n"
         << "|            2. Mage                Skill: Magic              |\n"
         << "|            3. Archer              Skill: Ranged             |\n"
         << "|                                                             |\n"
         << "'-------------------------------------------------------------'\n";
    cin >> classChoice;
    if (validateInput(classChoice, 1, 999))
    {
      char confirmSelection = ' ';
      bool confirmLoop = true;
      switch (classChoice)
      {
        // Player chose Warrior
        case 1:
        {
          warriorArt();
          do
          {
            cout << "You have selected 'Warrior', continue?\n"
                 << "Y or N: ";
            cin >> confirmSelection;
            if (validateDecision(confirmSelection))
            {
              if (confirmSelection == 'Y' || confirmSelection == 'y')
              {
                className = "Warrior";
                cout << "\nYou've chosen the path of the Warrior\n\n";
                loopFlag = false;
              }
              confirmLoop = false;
            }
          } while (confirmLoop);
          break;
        }

          // Player chose Mage
        case 2:
        {
          mageArt();
          do
          {
            cout << "You have selected 'Mage', continue?\n"
                 << "Y or N: ";
            cin >> confirmSelection;
            if (validateDecision(confirmSelection))
            {
              if (confirmSelection == 'Y' || confirmSelection == 'y')
              {
                className = "Mage";
                cout << "\nYou've chosen the path of the Mage\n\n";
                loopFlag = false;
              }
              confirmLoop = false;
            }
          } while (confirmLoop);
          break;
        }

          // Player chose Archer
        case 3:
        {
          archerArt();
          do
          {
            cout << "You have selected 'Archer', continue?\n"
                 << "Y or N: ";
            cin >> confirmSelection;
            if (validateDecision(confirmSelection))
            {
              if (confirmSelection == 'Y' || confirmSelection == 'y')
              {
                className = "Archer";
                cout << "\nYou've chosen the path of the Archer\n\n";
                loopFlag = false;
              }
              confirmLoop = false;
            }
          } while (confirmLoop);
          break;
        }

          // Player chose an invalid number
        default:
        {
          className = "Bard";
          bardArt();
          cout << "That's wasn't an option >:(\n"
               << "Player has been punished and automatically assigned to class: 'Bard'\n\n";
          loopFlag = false;
          break;
        }
      }
    }
  } while (loopFlag);
}

// Pre-condition: called by battleController(), passed result of battleMenu(), skill variables, enemy variables, and characterStats
// Post-condition: returns a damage amount based on all passed variables
double Player::attack(Player *player, const double &enemyVulnerability, const string &battleMenuSelection)
{
  // Attack Variables
  double attackValue = 0;
  double critChance = BASE_CRIT_CHANCE * player->skills->getCritSkill();

  if (battleMenuSelection == "Melee")
    attackValue = BASE_MELEE_DAMAGE * player->skills->getMeleeSkill();
  else if (battleMenuSelection == "Magic")
    attackValue = BASE_MAGIC_DAMAGE * player->skills->getMagicSkill();
  else if (battleMenuSelection == "Ranged")
    attackValue = BASE_RANGED_DAMAGE * player->skills->getRangedSkill();

  // Get skill upgrade tier
  short unsigned int skillTier = player->skills->getSkillTier(battleMenuSelection);

  // Calculate attackValue
  attackValue *= skillTier * player->getWeaponLevel(battleMenuSelection);

  // Add a small offset to the damage for a touch of variability
  attackValue += skillTier * (-1 + (rand() % 3));

  // Calculate crit
  if (1 + (rand() % 100) <= critChance * 100)
  {
    attackValue *= 2;
    cout << "\tYou landed a critical hit!\n";
  }

  // Calculate vulnerability
  attackValue *= enemyVulnerability;

  // DEBUG OPTION - Max damage
  if (debug)
    attackValue = 1000.0;

  cout << "\t" << player->skills->getSkillName(battleMenuSelection) << " dealt " << static_cast<int>(attackValue) << " damage\n\n";

  // Increment skill counter and check for upgrade
  player->skills->useSkill(battleMenuSelection, player->getClass());

  return attackValue;
}

void Player::addKey()
{
  ++keys;
  displayMeInABox("GOLDEN KEY Acquired!");
}

void Player::upgradeWeapon(const string &weaponType)
{
  if (weaponType == "Melee")
    ++meleeWeapon;
  else if (weaponType == "Magic")
    ++magicWeapon;
  else if (weaponType == "Ranged")
    ++rangedWeapon;
}

int Player::getWeaponLevel(const string &weaponType)
{
  if (weaponType == "Melee")
    return meleeWeapon;
  else if (weaponType == "Magic")
    return magicWeapon;
  else if (weaponType == "Ranged")
    return rangedWeapon;

  // TODO: Implement clean fix for return in all control paths
  return -1;
}

// Pre-condition: called by battleController(), passed potionCount
// Post-condition: returns an amount to heal the player and updates potionCount
void Player::heal()
{
  if (potions > 0)
  {
    // Picks a random number between 10 and 20 to return a heal amount
    double healValue = 10 + (rand() % 11);
    cout << "\tYou used a potion and healed for " << healValue << " health\n"
         << "\tYou now have " << --potions << " potions.\n\n";
    health += healValue;
  }
  else
    cout << "\tYou don't have any potions!\n";
}