#include <Action/CommonAction.h>
#include <Actor/Player.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include "StatusEffect/StatusEffect.h"

#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlTargetPacket.h"
#include "Network/PacketWrappers/EffectPacket1.h"
#include "Network/PacketWrappers/HudParamPacket.h"
#include "Network/Util/PacketUtil.h"
#include <Network/CommonActorControl.h>
using namespace Sapphire;
using namespace Sapphire::World::Action;

class StatusEffectBerserk : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectBerserk() : Sapphire::ScriptAPI::StatusEffectScript( 86 )
  {
  }


  void onExpire( Entity::Chara& actor ) override
  {
    // add 5s pacification
    // temporary solution until i figure out a better way to do this
    auto effect = Sapphire::StatusEffect::make_StatusEffect( Pacification, actor.getAsPlayer(), actor.getAsPlayer(), 5000, 3000 );
    Network::Util::Packet::sendActorControl( actor.getInRangePlayerIds( actor.isPlayer() ), actor.getId(), Sapphire::Network::ActorControl::ActorControlType::StatusEffectGain, Pacification );
    actor.addStatusEffect(effect);
  }

private:
  const uint32_t Pacification = 6;
};

EXPOSE_SCRIPT( StatusEffectBerserk );