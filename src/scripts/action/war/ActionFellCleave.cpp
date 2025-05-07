#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <Actor/Player.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <StatusEffect/StatusEffect.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionFellCleave : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionFellCleave() : Sapphire::ScriptAPI::ActionScript( 3549 )
  {
  }

  static constexpr auto Potency = 500;

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pTarget = action.getHitChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pSource || !pActionBuilder )
      return;

    // need to manually remove status 
    pSource->removeSingleStatusEffectById( Uncontrollable );
    auto dmg = action.calcDamage( Potency );
    pActionBuilder->damage( pSource, pTarget, dmg.first, dmg.second );
  }
};

EXPOSE_SCRIPT( ActionFellCleave );