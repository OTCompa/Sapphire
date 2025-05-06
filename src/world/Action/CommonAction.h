#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace Sapphire::World::Action
{
  enum ActionSkill
  {
    // Warrior
    SkullSunder = 35,
    Maim = 37,
    StormsPath = 42,
    StormsEye = 45,
    ButchersBlock = 47,

    // Bard
    HeavyShot = 97,
    StraightShot = 98,
    VenomousBite = 100,
    Windbite = 113,
    EmpyrealArrow = 3558,
    IronJaws = 3560
  };

  enum ActionStatus
  {
    Null = 0,
    // Warrior
    Defiance = 91,
    Unchained = 92,
    Wrath = 93,
    WrathII = 94,
    WrathIII = 95,
    WrathIV = 96,
    Infuriated = 97,
    InnerBeast = 411,
    Deliverance = 729,

    // Bard
    VenomousBiteStatus = 124,
    Barrage = 128,
    WindbiteStatus = 129
  };
}