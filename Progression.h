#ifndef DASTARDLY_DUNGEON_DWELLERS_PROGRESSION_H
#define DASTARDLY_DUNGEON_DWELLERS_PROGRESSION_H

class Progression
{
private:
  short unsigned int roomCount = 0;
  short unsigned int potionCount = 3;
  short unsigned int armorCount = 0;
  short unsigned int goldCount = 0;
  short unsigned int keyCount = 0;
  short unsigned int enemy = 0;

public:
  // Mutators
  void adjustRoomCount() { ++roomCount; }
  void adjustPotionCount(int potion) { potionCount += potion; }
  void adjustArmorCount(int armor) { armorCount += armor; }
  void adjustGoldCount(int gold) { goldCount += gold; }
  void adjustKeyCount() { ++keyCount; }
  void adjustEnemyProgression() { ++enemy; }

  // Accessors
  int getRoomCount() const { return roomCount; }
  int getPotionCount() const { return potionCount; }
  int getArmorCount() const { return armorCount; }
  int getGoldCount() const { return goldCount; }
  int getKeyCount() const { return keyCount; }
  int getEnemyProgression() const { return enemy; }
};

#endif //DASTARDLY_DUNGEON_DWELLERS_PROGRESSION_H