#include "Upgrade.h"

// Pre-condition: called by playerDamage() or roomMerchant(), the second argument (defaulted to -1) determines whether the function is being called to check upgradeCounter (playerDamage()) or to increment it (roomMerchant())
// Post-condition: returns upgradeCounter, if called by roomMerchant() - returns 0
int weaponUpgrade(int checkWeaponUpgrade, int upgradeThis)
{
  // Initialize upgrade array
  static int upgradeCounter[] = {1,1,1};
  const int MELEE_WEAPON = 0, MAGIC_WEAPON = 1, RANGED_WEAPON = 2;

  // Function was called to check upgradeCounter
  if (upgradeThis == -1)
  {
    switch (checkWeaponUpgrade)
    {
      case 0:
      {
        return upgradeCounter[MELEE_WEAPON];
      }
      case 1:
      {
        return upgradeCounter[MAGIC_WEAPON];
      }
      case 2:
      {
        return upgradeCounter[RANGED_WEAPON];
      }
    }
  }

  // Function was called to increment upgradeCounter indexes
  else
  {
    switch (upgradeThis)
    {
      // Melee is upgraded
      case 0:
      {
        ++upgradeCounter[MELEE_WEAPON];
        break;
      }
      // Magic is upgraded
      case 1:
      {
        ++upgradeCounter[MAGIC_WEAPON];
        break;
      }
      // Ranged is upgraded
      case 2:
      {
        ++upgradeCounter[RANGED_WEAPON];
        break;
      }
    }
  }
  return 0;
}