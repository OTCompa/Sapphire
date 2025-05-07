#include <Action/CommonAction.h>
#include <Actor/Player.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class StatusEffectDeliverance : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectDeliverance() : Sapphire::ScriptAPI::StatusEffectScript( 729 )
  {
  }

  void onExpire( Entity::Chara& actor ) override
  {
    actor.removeStatusEffectById( { Abandon, AbandonII, AbandonIII, AbandonIV, Uncontrollable } );
  }
};

EXPOSE_SCRIPT( StatusEffectDeliverance );