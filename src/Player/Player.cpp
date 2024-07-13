#include "Player.h"

// Pre-condition: called by battleController(), passed potionCount
// Post-condition: returns an amount to heal the player and updates potionCount
int heal(int &potionCount)
{
  // If you have a potion, heal
  if (potionCount > 0)
  {
    // Picks a random number between 10 and 20 to return a heal amount
    int healValue = 10 + (rand() % 11);
    cout << "\tYou used a potion and healed for " << healValue << " health\n"
         << "\tYou now have " << --potionCount << " potions.\n\n";
    // Returns the amount the player will be healed
    return healValue;
  }

  // If the player doesn't have any potions
  else
  {
    cout << "\tYou don't have any potions!\n";
    return 0;
  }
}