#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <Actor/Player.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <StatusEffect/StatusEffect.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionIronJaws : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionIronJaws() : Sapphire::ScriptAPI::ActionScript( 3560 )
  {
  }

  static constexpr auto Potency = 100;

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto playerAsChara = action.getSourceChara();
    auto targetAsChara = action.getHitChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pActionBuilder ) return;
    if( targetAsChara == nullptr ) return;

    action.enableGenericHandler();

    auto statusEffectMap = targetAsChara->getStatusEffectMap();

    //auto dmg = action.calcDamage( Potency );
    //pActionBuilder->damage( playerAsChara, targetAsChara, dmg.first, dmg.second );

    for( auto it = statusEffectMap.begin(); it != statusEffectMap.end(); it++ )
    {
      auto status = it->second;
      auto statusSrc = status->getSrcActor();
      if( statusSrc == nullptr ) continue;

      if( statusSrc == playerAsChara )
      {
        if( status->getId() == 124 )
        {
          status->resetStartTime();
          action.resnapshotStatusEffect( status );
          targetAsChara->sendStatusEffectUpdate();
        }

        if( status->getId() == 129 )
        {
          status->resetStartTime();
          action.resnapshotStatusEffect( status );
          playerAsChara->sendStatusEffectUpdate();
        }
      }
    }
  }
};

EXPOSE_SCRIPT( ActionIronJaws );