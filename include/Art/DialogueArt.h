#ifndef DIALOGUEART_H
#define DIALOGUEART_H

namespace art
{
  namespace dialogue
  {
    void roomEnemyMonologue(const bool ROOM_EXPLORED);
    void roomLootMonologue(const bool ROOM_EXPLORED);
    void roomMerchantMonologue(const bool ROOM_EXPLORED);
    void roomExitMonologue(const bool ROOM_EXPLORED);
  }
}

#endif // DIALOGUE_ART_H
