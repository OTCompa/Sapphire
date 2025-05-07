#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <Actor/Player.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <StatusEffect/StatusEffect.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionInfuriate : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionInfuriate() : Sapphire::ScriptAPI::ActionScript( 52 )
  {
  }


  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pSource || !pActionBuilder )
      return;

    if (pSource->hasStatusEffect(Defiance)) {
      pSource->removeStatusEffectById( { Wrath, WrathII, WrathIII, WrathIV, Infuriated } );
      pActionBuilder->applyStatusEffectSelf( Infuriated, 30000, 0, true );
    }
    else if (pSource->hasStatusEffect(Deliverance)) {  // probably can just use else, but just to be sure
      pSource->removeStatusEffectById( { Abandon, AbandonII, AbandonIII, AbandonIV, Uncontrollable } );
      pActionBuilder->applyStatusEffectSelf( Uncontrollable, 30000, 0, true );
    }
  }
};

EXPOSE_SCRIPT( ActionInfuriate );