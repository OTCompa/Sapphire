#include "Warrior.h"

#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <Actor/Player.h>
#include <Logging/Logger.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

const ActionStatus statusLut[ 5 ][ 2 ] =
{
  // Deliverance, Defiance
  { Abandon, Wrath },
  { AbandonII, WrathII },
  { AbandonIII, WrathIII },
  { AbandonIV, WrathIV },
  { Uncontrollable, Infuriated },
};

void Warrior::onAction( Entity::Player& player, Action& action )
{
  switch( action.getId() )
  {
    case Maim:
    case StormsEye:
    case StormsPath:
    case SkullSunder:
    case ButchersBlock:
    case Vengeance:
    case Berserk:
    {
      if( action.isComboAction() && !action.isCorrectCombo() && !action.isAbility() )
        break;

      if( player.hasStatusEffect( Defiance ) )
        handleWrathAbandon( player, action, 1 );
      else if( player.hasStatusEffect( Deliverance ) )
        handleWrathAbandon( player, action, 0 );
      break;
    }
  }
}

void Warrior::handleWrathAbandon( Entity::Player& player, Action& action, char isInDefiance )
{
  auto effectToApply = statusLut[ 0 ][ isInDefiance ];
  auto bonus = 2;
  auto asChara = player.getAsChara();

  auto pActionBuilder = action.getActionResultBuilder();
    
  if( !pActionBuilder )
    return;

  if( player.hasStatusEffect( statusLut[0][isInDefiance] ) )
  {
    player.replaceSingleStatusEffectById( statusLut[ 0 ][ isInDefiance ] );
    effectToApply = statusLut[ 1 ][ isInDefiance ];
    bonus = 4;
  }
  else if( player.hasStatusEffect( statusLut[ 1 ][ isInDefiance ] ) )
  {
    player.replaceSingleStatusEffectById( statusLut[ 1 ][ isInDefiance ] );
    effectToApply = statusLut[ 2 ][ isInDefiance ];
    bonus = 6;
  }
  else if( player.hasStatusEffect( statusLut[ 2 ][ isInDefiance ] ) )
  {
    player.replaceSingleStatusEffectById( statusLut[ 2 ][ isInDefiance ] );
    effectToApply = statusLut[ 3 ][ isInDefiance ];
    bonus = 8;
  }
  else if( player.hasStatusEffect( statusLut[ 3 ][ isInDefiance ] ) )
  {
    player.replaceSingleStatusEffectById( statusLut[ 3 ][ isInDefiance ] );
    effectToApply = statusLut[ 4 ][ isInDefiance ];
    bonus = 10;
  }

  if( !player.hasStatusEffect( statusLut[ 4 ][ isInDefiance ] ) )
  {
    auto modifier = { StatusModifier{ isInDefiance ? Common::ParamModifier::ParryPercent : Common::ParamModifier::CriticalHit, bonus } };
    pActionBuilder->applyStatusEffectSelf( effectToApply, 30000, 0, modifier, 0, false );
  }
  else {
    // refresh timer
  }
}