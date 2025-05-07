#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <Actor/Player.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <StatusEffect/StatusEffect.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionDeliverance : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionDeliverance() : Sapphire::ScriptAPI::ActionScript( 3548 )
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

    if( pSource->hasStatusEffect( Wrath ) )
    {
      swapBuffWithDuration( pSource, Wrath, Abandon, pActionBuilder );
    }
    else if( pSource->hasStatusEffect( WrathII ) )
    {
      swapBuffWithDuration( pSource, WrathII, AbandonII, pActionBuilder );
    }
    else if( pSource->hasStatusEffect( WrathIII ) )
    {
      swapBuffWithDuration( pSource, WrathIII, AbandonIII, pActionBuilder );
    }
    else if( pSource->hasStatusEffect( WrathIV ) )
    {
      swapBuffWithDuration( pSource, WrathIV, AbandonIV, pActionBuilder );
    }
    else if( pSource->hasStatusEffect( Infuriated ) )
    {
      swapBuffWithDuration( pSource, Infuriated, Uncontrollable, pActionBuilder );
    }

    pSource->removeSingleStatusEffectById( Defiance );
  }

  // i don't really know where to put this function
  void swapBuffWithDuration( Entity::CharaPtr pSource, ActionStatus oldStatus, ActionStatus newStatus, ActionResultBuilderPtr pActionBuilder )
  {
    auto status = pSource->getStatusEffectById( oldStatus );
    if( status == nullptr ) return;

    pSource->replaceSingleStatusEffectById( oldStatus );
    pActionBuilder->applyStatusEffectSelf( newStatus, status->getRemainingDuration(), 0, {}, 0, false );
  }
};

EXPOSE_SCRIPT( ActionDeliverance );