#ifndef DASTARDLY_DUNGEON_DWELLERS_PROGRESSION_H
#define DASTARDLY_DUNGEON_DWELLERS_PROGRESSION_H

class Progression
{
private:
  float playerHealth = 20;
  short unsigned int roomCount = 0;
  short unsigned int potionCount = 3;
  short unsigned int armorCount = 0;
  short unsigned int goldCount = 0;
  short unsigned int keyCount = 0;
  short unsigned int enemyProgression = 0;

public:
  // Mutators
  void addHealth(float healthAdjust) { playerHealth += healthAdjust; }
  void attackPlayer(float healthAdjust) { playerHealth -= healthAdjust; }
  void addRoomCount() { ++roomCount; }
  void addPotionCount(int potion) { potionCount += potion; }
  void addArmorCount(int armor) { armorCount += armor; }
  void addGoldCount(int gold) { goldCount += gold; }
  void addKeyCount() { ++keyCount; }
  void addEnemyProgression() { ++enemyProgression; }

  // Accessors
  int getRoomCount() const { return roomCount; }
  int getPotionCount() const { return potionCount; }
  int getArmorCount() const { return armorCount; }
  int getGoldCount() const { return goldCount; }
  int getKeyCount() const { return keyCount; }
  int getEnemyProgression() const { return enemyProgression; }
};

#endif //DASTARDLY_DUNGEON_DWELLERS_PROGRESSION_H