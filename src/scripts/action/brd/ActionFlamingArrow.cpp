#include <Action/Action.h>
#include <Action/CommonAction.h>
#include <Actor/Player.h>
#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <StatusEffect/StatusEffect.h>

#include "Territory/Territory.h"
#include "Actor/BNpc.h"

#include "Manager/TaskMgr.h"
#include "Task/FadeBNpcTask.h"
#include "Task/RemoveBNpcTask.h"

#include "Network/Util/PacketUtil.h"
#include <Network/CommonActorControl.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionFlamingArrow : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionFlamingArrow() : Sapphire::ScriptAPI::ActionScript( 102 )
  {
  }

  static constexpr auto flamingArrowVfxId = 196;

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();
    auto pSource = action.getSourceChara();
    auto pActionBuilder = action.getActionResultBuilder();
    if( !pPlayer || !pActionBuilder )
      return;

    auto flamingArrowBuff = Sapphire::StatusEffect::make_StatusEffect( 249, pPlayer, pPlayer, 5000, 3000 );
    pSource->addStatusEffect( flamingArrowBuff );
    // this only sends a packet to the client to spawn it, there is no areaobject created that is tracked or will it despawn
    Network::Util::Packet::sendCreateAreaObject( ( *pPlayer ), 1, flamingArrowVfxId, 0, pPlayer->getId(), 5, 0x6EE0, 0xE3, 0x7F2799EC, 0x67ECADE8, action.getPos() );
    


  }

private:
  Entity::BNpcPtr spawnBNpc( Sapphire::World::Action::Action& action )
  {
    auto player = action.getSourceChara();
    auto bNpcTemplate = Sapphire::Entity::make_BNpcTemplate( 1, 1993, 0, 0, 0, 0, 0, 0, 4, 517, 0, nullptr, nullptr );

    auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();

    auto playerZone = teriMgr.getTerritoryByGuId( player->getTerritoryId() );
    auto pBNpc = std::make_shared< Entity::BNpc >( playerZone->getNextActorId(),
                                                   bNpcTemplate,
                                                   action.getPos().x,
                                                   action.getPos().y,
                                                   action.getPos().z,
                                                   player->getRot(),
                                                   1, 1000, playerZone );

    pBNpc->setTerritoryId( playerZone->getGuId() );
    pBNpc->setTerritoryTypeId( playerZone->getTerritoryTypeId() );

    pBNpc->setFlag( Entity::BNpcFlag::Immobile | Entity::BNpcFlag::Invincible | Entity::BNpcFlag::InvincibleRefill | Entity::BNpcFlag::Untargetable | Entity::BNpcFlag::TurningDisabled );
    pBNpc->setInvincibilityType( Common::InvincibilityRefill );
    playerZone->pushActor( pBNpc );

    return pBNpc->getAsBNpc();
  }
};

EXPOSE_SCRIPT( ActionFlamingArrow );