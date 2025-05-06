#include "Bard.h"

#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <Actor/Player.h>
#include <Util/Util.h>
#include <StatusEffect/StatusEffect.h>
#include <Logging/Logger.h>
#include <Math/CalcStats.h>

using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::World::Action;

void Bard::onAction( Entity::Player& player, Action& action )
{
  switch( action.getId() )
  {
    case IronJaws:
    {
      handleIronJaws( player, action );
      break;
    }
  }
}

void Bard::handleIronJaws( Entity::Player& player, Action& action )
{
  auto playerAsChara = player.getAsChara();
  auto targetAsChara = action.getHitChara();
  auto pActionBuilder = action.getActionResultBuilder();

  auto applyVenom = false;
  auto applyWind = false;

  if( !pActionBuilder ) return;
  if (targetAsChara == nullptr) return;

  auto statusEffectMap = targetAsChara->getStatusEffectMap();
  

  for (auto it = statusEffectMap.begin(); it != statusEffectMap.end(); it++) {
    auto status = it->second;
    auto statusSrc = status->getSrcActor();

    if (status->getId() == VenomousBite) {
      if( statusSrc == playerAsChara )
      {
        status->resetStartTime();
        action.resnapshotStatusEffect( status );
        targetAsChara->updateStatusEffect(status);
      }
    }

    if( status->getId() == Windbite )
    {
      if( statusSrc == playerAsChara )
      {
        status->resetStartTime();
        action.resnapshotStatusEffect( status );
        targetAsChara->updateStatusEffect( status );
      }
    }
  }
}