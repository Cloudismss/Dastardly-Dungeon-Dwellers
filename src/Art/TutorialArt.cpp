#include "TutorialArt.h"

#include <iostream>
#include <string>

namespace art
{
  namespace tutorial
  {
    void tutorialGame()
    {
      std::cout << ".-------------------------------------------------------------.\n"
                   "|                                                             |\n"
                   "|                      Game Information                       |\n"
                   "|                                                             |\n"
                   "|     Dastardly Dungeon Dwellers follows the story of         |\n"
                   "|     three brave adventurers. You've entered this dungeon    |\n"
                   "|     in search of glory and riches beyond your desires.      |\n"
                   "|                                                             |\n"
                   "|     Only the courageous prevail, this dungeon is crawling   |\n"
                   "|     with baddies. If you're lucky, you'll encounter a       |\n"
                   "|     friendly traveling merchant to aid in your exploits.    |\n"
                   "|                                                             |\n"
                   "|     Scour the dungeon for its valuables, and defeat         |\n"
                   "|     its fearsome protector, if you feel capable.            |\n"
                   "|     Once you find the Golden Key, you can exit the          |\n"
                   "|     dungeon with your riches. Be warned, a powerful         |\n"
                   "|     foe hopes to exploit your hubris.                       |\n"
                   "|                                                             |\n"
                   "'-------------------------------------------------------------'\n";

      std::cout << "\n\tPress enter to return to the main menu: ";
      std::string enterKey;
      getline(std::cin, enterKey);
    }

    void tutorialBattle()
    {
      std::cout << ".-------------------------------------------------------------.\n"
                   "|                                                             |\n"
                   "|                     Battle Information                      |\n"
                   "|                                                             |\n"
                   "|      1: Melee Attack         4: Consume a potion            |\n"
                   "|      2: Magic Attack         5: Attempt to run away         |\n"
                   "|      3: Ranged Attack        6: Attempt to switch character |\n"
                   "|                                                             |\n"
                   "|     Damage values scale based on class selection and        |\n"
                   "|     enemy type. For example, skeletons take much more       |\n"
                   "|     damage from Melee damage rather than Ranged damage.     |\n"
                   "|                                                             |\n"
                   "|     Melee attacks deal moderate damage overall, but         |\n"
                   "|     may perform very poorly against certain enemies.        |\n"
                   "|                                                             |\n"
                   "|     Magic attacks deal varied damage depending on           |\n"
                   "|     enemy type, and Magic has a higher chance to deal       |\n"
                   "|     critical damage.                                        |\n"
                   "|                                                             |\n"
                   "|     Ranged attacks deal a high amount of damage, but        |\n"
                   "|     they have a higher chance to miss.                      |\n"
                   "|                                                             |\n"
                   "|     Potions are finite and heal for a random amount,        |\n"
                   "|     you can acquire more potions in the dungeon.            |\n"
                   "|                                                             |\n"
                   "|     If a fight seems insurmountable, you can always         |\n"
                   "|     run away. Be careful though, there's a chance you'll    |\n"
                   "|     fail to get away!                                       |\n"
                   "|                                                             |\n"
                   "'-------------------------------------------------------------'\n";

      std::cout << "\n\tPress enter to return to the game: ";
      std::string enterKey;
      getline(std::cin, enterKey);
      std::cout << "\n";
    }
  }
}
