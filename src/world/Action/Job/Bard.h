#pragma once

#include "ForwardsZone.h"
#include <Common.h>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

namespace Sapphire::World::Action
{
  class Bard
  {
  public:
    static void onAction( Entity::Player& player, Action& action );

  private:
    static void handleIronJaws( Entity::Player& player, Action& action );
  };
}// namespace Sapphire::World::Action