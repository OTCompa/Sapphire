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

void Bard::conditionInit(Entity::Player& player, Action& action )
{
  auto src = player.getAsChara();
  if( src->hasStatusEffect( 865 ) )
    switch( action.getId() )
    {
      case HeavyShot:
      case StraightShot:
      case VenomousBite:
      case Windbite:
      case EmpyrealArrow:
      case IronJaws:
        action.setCastTime( Math::CalcStats::gcdSpeed( *src, 1500 ) );
        break;
    }
}

void Bard::onAction( Entity::Player& player, Action& action )
{
    switch (action.getId())
    {
      case HeavyShot:
      case StraightShot:
      case VenomousBite:
      case Windbite:
      case EmpyrealArrow:
      case IronJaws:
        handleBarrage( player, action );
    }
}


void Bard::handleBarrage(Entity::Player& player, Action& action) {
  if( !player.hasStatusEffect( 128 ) ) return;

  
  auto pActionBuilder = action.getActionResultBuilder();
  auto targetAsChara = action.getHitChara();

  if( !pActionBuilder ) return;
  if( targetAsChara == nullptr ) return;

  auto lut = ActionLut::getEntry( action.getId() );

  player.removeSingleStatusEffectById( 128 );
  auto dmg = action.calcDamage( lut.potency );
  pActionBuilder->damage( player.getAsChara(), targetAsChara, dmg.first, dmg.second );
  dmg = action.calcDamage( lut.potency );
  pActionBuilder->damage( player.getAsChara(), targetAsChara, dmg.first, dmg.second );
}