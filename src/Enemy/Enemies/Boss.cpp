#include "Boss.h"

#include <iostream>

#include "Globals.h"

using std::cout;

Boss::Boss(int playerLevel) : Enemy(playerLevel)
{
  rewardTier = 10;
  name = bosses[rand() % bosses.size()];
  boss = true;
  announceEnemy();
}

void Boss::announceEnemy()
{
  cout << "\nThe Earth trembles beneath you, a powerful foe is near...\n" << name << " has cornered you!\n\n";
}

string Boss::getNickname() const
{
  if (name == "Voidshaper Nihilus")
    return "Nihilus";
  else if (name == "Snarltooth the Feral")
    return "Snarltooth";
  else if (name == "Dreadlord Vorkar")
    return "Vorkar";
  else if (name == "Soulstealer Malgrimor")
    return "Malgrimor";
  else if (name == "King Rattleclaw")
    return "Rattleclaw";
  else if (name == "Ignatius the Infernal")
    return "Ignatius";
  else if (name == "Dreadmaw the Bonecrusher")
    return "Dreadmaw";
  else if (name == "Rotclaw the Pustulant")
    return "Rotclaw";
  else if (name == "Sludgeheart the Grotesque")
    return "Sludgeheart";
  else if (name == "Drak'thar the Trollking")
    return "Drak'thar";

  return "Error";
}

int Boss::attack(int playerArmor, int playerMaxHealth)
{
  if (1 + (rand() % 100) <= BASE_ENEMY_MISS_CHANCE * 100)
  {
    cout << "\t" << name << " missed!\n\n";
    return 0;
  }

  int damage = 0;
  int attackLow = 0;
  int attackHigh = 0;

  damage = BASE_BOSS_DAMAGE;

  attackLow = (-0.1 * playerMaxHealth) + (-0.1 * BASE_BOSS_DAMAGE);
  attackHigh = (0.1 * playerMaxHealth) + (0.1 * BASE_BOSS_DAMAGE);

  // Damage offset for fun variance
  damage += (attackLow + (rand() % ((attackHigh + 1) - attackLow)));

  // Flat damage reduction via armor
  int playerArmorProtection = 0;
  double percentBlocked = 1.0;
  for (int i = 0; i < playerArmor; ++i)
  {
    if (playerArmor == 1)
      playerArmorProtection = 1; // So we don't multiply by 0 below
    percentBlocked += 5;
  }
  playerArmorProtection *= percentBlocked;
  damage -= playerArmorProtection;

  // Player one-shot protection
  if (damage > playerMaxHealth)
    damage = playerMaxHealth - 1;

  // Stops players from healing when stacking a bunch of armor
  if (damage < 0)
    damage = 0;

  cout << "\t" << name << " dealt " << damage << " damage\n\n";
  return damage;
}
