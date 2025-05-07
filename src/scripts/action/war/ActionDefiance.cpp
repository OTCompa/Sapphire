#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <Actor/Player.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <StatusEffect/StatusEffect.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionDefiance : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionDefiance() : Sapphire::ScriptAPI::ActionScript( 48 )
  {
  }


  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pSource || !pActionBuilder )
      return;

    // still use the modifiers defined in players.json
    action.enableGenericHandler();

    if (pSource->hasStatusEffect(Abandon))
    {
      swapBuffWithDuration( pSource, Abandon, Wrath, pActionBuilder );
    }
    else if( pSource->hasStatusEffect( AbandonII ) )
    {
      swapBuffWithDuration( pSource, AbandonII, WrathII, pActionBuilder );
    }
    else if( pSource->hasStatusEffect( AbandonIII ) )
    {
      swapBuffWithDuration( pSource, AbandonIII, WrathIII, pActionBuilder );
    }
    else if( pSource->hasStatusEffect( AbandonIV ) )
    {
      swapBuffWithDuration( pSource, AbandonIV, WrathIV, pActionBuilder );
    }
    else if( pSource->hasStatusEffect( Uncontrollable ) )
    {
      swapBuffWithDuration( pSource, Uncontrollable, Infuriated, pActionBuilder );
    }

    pSource->removeSingleStatusEffectById( Deliverance );
  }

  // i don't really know where to put this function
  void swapBuffWithDuration(Entity::CharaPtr pSource, ActionStatus oldStatus, ActionStatus newStatus, ActionResultBuilderPtr pActionBuilder) {
    auto status = pSource->getStatusEffectById( oldStatus );
    if( status == nullptr ) return;

    pSource->replaceSingleStatusEffectById( oldStatus );
    pActionBuilder->applyStatusEffectSelf( newStatus, status->getRemainingDuration(), 0, {}, 0, false );
  }
};

EXPOSE_SCRIPT( ActionDefiance );