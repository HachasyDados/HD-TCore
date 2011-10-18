/* Copyright (C) 2008 - 2009 Trinity <http://www.trinitycore.org/>
*
 * Patch supported by ChaosUA & TCRU community http://trinity-core.ru/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "ScriptPCH.h"
#include "OutdoorPvPWG.h"
#include "OutdoorPvPMgr.h"
#include "Vehicle.h"

#define GOSSIP_HELLO_DEMO1  "Construir catapulta."
#define GOSSIP_HELLO_DEMO2  "Construir demoledor."
#define GOSSIP_HELLO_DEMO3  "Construir maquina de asedio."
#define GOSSIP_HELLO_DEMO4  "No puedo construir mas."

class npc_demolisher_engineerer : public CreatureScript
{
public:
    npc_demolisher_engineerer() : CreatureScript("npc_demolisher_engineerer") { }

bool OnGossipHello(Player* player, Creature* creature)
{
    if (creature->isQuestGiver())
        player->PrepareQuestMenu(creature->GetGUID());

    if (player->isGameMaster() || creature->GetZoneScript() && creature->GetZoneScript()->GetData(creature->GetDBTableGUIDLow()))
    {
        if (player->HasAura(SPELL_CORPORAL))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_DEMO1, GOSSIP_SENDER_MAIN,   GOSSIP_ACTION_INFO_DEF);
        else if (player->HasAura(SPELL_LIEUTENANT))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_DEMO1, GOSSIP_SENDER_MAIN,   GOSSIP_ACTION_INFO_DEF);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_DEMO2, GOSSIP_SENDER_MAIN,   GOSSIP_ACTION_INFO_DEF+1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_DEMO3, GOSSIP_SENDER_MAIN,   GOSSIP_ACTION_INFO_DEF+2);
        }
    }
    else
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HELLO_DEMO4, GOSSIP_SENDER_MAIN,   GOSSIP_ACTION_INFO_DEF+9);

    player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
    return true;
}

bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
{
    player->CLOSE_GOSSIP_MENU();
    if (player->isGameMaster() || creature->GetZoneScript() && creature->GetZoneScript()->GetData(creature->GetDBTableGUIDLow()))
    {
        switch(uiAction - GOSSIP_ACTION_INFO_DEF)
        {
            case 0: player->CastSpell(player, 56663, false, NULL, NULL, creature->GetGUID()); break;
            case 1: player->CastSpell(player, 56575, false, NULL, NULL, creature->GetGUID()); break;
            case 2: player->CastSpell(player, player->GetTeamId() ? 61408 : 56661, false, NULL, NULL, creature->GetGUID()); break;
        }
    }

    return true;
}

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_demolisher_engineererAI(creature);
    }

    struct npc_demolisher_engineererAI : public ScriptedAI
    {
        npc_demolisher_engineererAI(Creature* creature) : ScriptedAI(creature)
        {
            me->SetReactState(REACT_PASSIVE);
        }
    };

};

enum eWintergraspBattleMage
{
    SPELL_PORTAL_VISUAL      = 60223,
    GO_WINTERGRASP_PORTAL    = 193772
};

class npc_wg_ally_battle_mage : public CreatureScript
{
public:
    npc_wg_ally_battle_mage() : CreatureScript("npc_wg_ally_battle_mage") { }

    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_wg_ally_battle_mageAI(creature);
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (!sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED))
            return false;

        if (OutdoorPvPWG *pvpWG = (OutdoorPvPWG*)sOutdoorPvPMgr->GetOutdoorPvPToZoneId(4197))
        {
            if (pvpWG->isWarTime())
            {
                if (pvpWG->getDefenderTeam() == TEAM_HORDE)
                    player->SEND_GOSSIP_MENU(14777, creature->GetGUID());
                else
                    player->SEND_GOSSIP_MENU(14781, creature->GetGUID());
            }
            else
            {
                if (pvpWG->getDefenderTeam() == TEAM_HORDE)
                    player->SEND_GOSSIP_MENU(14775, creature->GetGUID());
                else
                    player->SEND_GOSSIP_MENU(14782, creature->GetGUID());
            }
        }
        return true;
    }

    struct npc_wg_ally_battle_mageAI : public ScriptedAI
    {
        npc_wg_ally_battle_mageAI(Creature* creature) : ScriptedAI(creature)
        {
            uiPortalTimer = 0;
            uiPortalPhase = 0;
            Check = true;
        }

        uint32 uiPortalTimer;
        uint8 uiPortalPhase;
        GameObject* WintergraspPortal;
        bool Player;
        bool Check;
        bool Check2;

        void UpdateAI(const uint32 diff)
        {
            // If WG is disabled, don't do anything.
            if (!sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED))
                return;

            if (OutdoorPvPWG *pvpWG = (OutdoorPvPWG*)sOutdoorPvPMgr->GetOutdoorPvPToZoneId(4197))
            {
                // Get playerlist if there is.
                if (pvpWG->isWarTime() && Check)
                {
                    Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    {
                        if (!PlayerList.isEmpty())
                        {
                            if (i->getSource()->GetDistance2d(me) <= 75)
                            {
                                Player = true;
                                Check = false;
                            }
                            else
                            {
                                Player = false;
                                Check = false;
                                Check2 = true;
                            }
                        }
                        else
                        {
                            Player = false;
                            Check = false;
                            Check2 = true;
                        }
                    }
                }

                if (!pvpWG->m_changeAlly) // If wg is switching (.wg switch)
                {
                    if (pvpWG->isWarTime())
                    {
                        if (Player) //(false) If there isn't any player, then, don't cast the portal spell. Just summon gameobject.
                        {
                            if (uiPortalTimer <= diff)
                            {
                                switch (uiPortalPhase)
                                {
                                case 0:
                                    me->SetOrientation(4.037271f);
                                    me->SendMovementFlagUpdate();
                                    ++uiPortalPhase;
                                    uiPortalTimer = 100;
                                    break;
                                case 1:
                                    me->AI()->DoCast(SPELL_PORTAL_VISUAL);
                                    ++uiPortalPhase;
                                    uiPortalTimer = 900;
                                    break;
                                case 2:
                                    WintergraspPortal = me->SummonGameObject(GO_WINTERGRASP_PORTAL, 5686.974609f, 773.303711f, 647.753235f, 5.572729f, 0, 0, 0.324484f, -0.945891f, 0);
                                    me->SetOrientation(5.515240f);
                                    me->SendMovementFlagUpdate();
                                    me->MonsterYell("Reinforcements are needed on the Wintergrasp battlefield! I have opened a portal for quick travel to the battle at The Silver Enclave.", LANG_UNIVERSAL, 0);
                                    ++uiPortalPhase;
                                    uiPortalTimer = 1000;
                                    break;
                                }
                            }
                            else
                                uiPortalTimer -= diff;
                        }
                        else
                        {
                            if (Check2) // If the portal isn't exist
                            {
                                WintergraspPortal = me->SummonGameObject(GO_WINTERGRASP_PORTAL, 5686.974609f, 773.303711f, 647.753235f, 5.572729f, 0, 0, 0.324484f, -0.945891f, 0);
                                Check2 = false;
                            }
                        }
                    }
                    else
                    {
                        if (pvpWG->getDefenderTeam() == TEAM_ALLIANCE)
                        {
                            if (pvpWG->m_timer <= 3600000) // An hour before battle begin, the portal will disappear.
                            {
                                uiPortalTimer = 0;
                                uiPortalPhase = 0;
                                Check = true;
                                Check2 = false;
                                if (GameObject* WintergraspPortal = me->FindNearestGameObject(GO_WINTERGRASP_PORTAL, 5.0f)) // If the portal is exist
                                    WintergraspPortal->RemoveFromWorld();
                            }
                        }
                        else
                        {
                            uiPortalTimer = 0;
                            uiPortalPhase = 0;
                            Check = true;
                            Check2 = false;
                            if (GameObject* WintergraspPortal = me->FindNearestGameObject(GO_WINTERGRASP_PORTAL, 5.0f)) // If the portal is exist
                                WintergraspPortal->RemoveFromWorld();
                        }
                    }
                }
            }
        }
    };
};

class npc_wg_horde_battle_mage : public CreatureScript
{
public:
    npc_wg_horde_battle_mage() : CreatureScript("npc_wg_horde_battle_mage") { }

    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_wg_horde_battle_mageAI(creature);
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (!sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED))
            return false;

        if (OutdoorPvPWG *pvpWG = (OutdoorPvPWG*)sOutdoorPvPMgr->GetOutdoorPvPToZoneId(4197))
        {
            if (pvpWG->isWarTime())
            {
                if (pvpWG->getDefenderTeam() == TEAM_HORDE)
                    player->SEND_GOSSIP_MENU(14777, creature->GetGUID());
                else
                    player->SEND_GOSSIP_MENU(14781, creature->GetGUID());
            }
            else
            {
                if (pvpWG->getDefenderTeam() == TEAM_HORDE)
                    player->SEND_GOSSIP_MENU(14775, creature->GetGUID());
                else
                    player->SEND_GOSSIP_MENU(14782, creature->GetGUID());
            }
        }
        return true;
    }

    struct npc_wg_horde_battle_mageAI : public ScriptedAI
    {
        npc_wg_horde_battle_mageAI(Creature* creature) : ScriptedAI(creature)
        {
            uiPortalTimer = 0;
            uiPortalPhase = 0;
            Check = true;
        }

        uint32 uiPortalTimer;
        uint8 uiPortalPhase;
        GameObject* WintergraspPortal;
        bool Player;
        bool Check;
        bool Check2;

        void UpdateAI(const uint32 diff)
        {
            // If WG is disabled, don't do anything.
            if (!sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED))
                return;

            if (OutdoorPvPWG *pvpWG = (OutdoorPvPWG*)sOutdoorPvPMgr->GetOutdoorPvPToZoneId(4197))
            {
                // Get playerlist if there is.
                if (pvpWG->isWarTime() && Check)
                {
                    Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    {
                        if (!PlayerList.isEmpty())
                        {
                            if (i->getSource()->GetDistance2d(me) <= 75)
                            {
                                Player = true;
                                Check = false;
                            }
                            else
                            {
                                Player = false;
                                Check = false;
                                Check2 = true;
                            }
                        }
                        else
                        {
                            Player = false;
                            Check = false;
                            Check2 = true;
                        }
                    }
                }

                if (!pvpWG->m_changeHorde) // If wg is switching (.wg switch)
                {
                    if (pvpWG->isWarTime())
                    {
                        if (Player) //(false) If there isn't any player, then, don't cast the portal spell. Just summon gameobject.
                        {
                            if (uiPortalTimer <= diff)
                            {
                                switch (uiPortalPhase)
                                {
                                case 0:
                                    me->SetOrientation(4.356160f);
                                    me->SendMovementFlagUpdate();
                                    ++uiPortalPhase;
                                    uiPortalTimer = 100;
                                    break;
                                case 1:
                                    me->AI()->DoCast(SPELL_PORTAL_VISUAL);
                                    ++uiPortalPhase;
                                    uiPortalTimer = 900;
                                    break;
                                case 2:
                                    WintergraspPortal = me->SummonGameObject(GO_WINTERGRASP_PORTAL, 5924.042969f, 570.354492f, 661.087280f, 5.930885f, 0, 0, 0.324484f, -0.945891f, 0);
                                    me->SetOrientation(6.003930f);
                                    me->SendMovementFlagUpdate();
                                    ++uiPortalPhase;
                                    uiPortalTimer = 1000;
                                    break;
                                }
                            }
                            else
                                uiPortalTimer -= diff;
                        }
                        else
                        {
                            if (Check2) // If the portal isn't exist
                            {
                                WintergraspPortal = me->SummonGameObject(GO_WINTERGRASP_PORTAL, 5686.974609f, 773.303711f, 647.753235f, 5.572729f, 0, 0, 0.324484f, -0.945891f, 0);
                                Check2 = false;
                            }
                        }
                    }
                    else
                    {
                        if (pvpWG->getDefenderTeam() == TEAM_HORDE)
                        {
                            if (pvpWG->m_timer <= 3600000) // An hour before battle begin, the portal will disappear.
                            {
                                uiPortalTimer = 0;
                                uiPortalPhase = 0;
                                Check = true;
                                Check2 = false;
                                if (GameObject* WintergraspPortal = me->FindNearestGameObject(GO_WINTERGRASP_PORTAL, 5.0f)) // If the portal is exist
                                    WintergraspPortal->RemoveFromWorld();
                            }
                        }
                        else
                        {
                            uiPortalTimer = 0;
                            uiPortalPhase = 0;
                            Check = true;
                            Check2 = false;
                            if (GameObject* WintergraspPortal = me->FindNearestGameObject(GO_WINTERGRASP_PORTAL, 5.0f)) // If the portal is exist
                                WintergraspPortal->RemoveFromWorld();
                        }
                    }
                }
            }
        }
    };
};

class go_wg_veh_teleporter : public GameObjectScript
{
public:
    go_wg_veh_teleporter() : GameObjectScript("go_wg_veh_teleporter") { }

    bool OnGossipHello(Player *player, GameObject * pGO)
    {
        if (GameObject* trigger = pGO->FindNearestGameObject(190375, 500)) // Wintergrasp Fortress Gate
            if (Vehicle * veh = player->GetVehicle())
            {
                Position triggerPos;
                trigger->GetPosition(&triggerPos);
                triggerPos.m_positionX -= 30;
                veh->Relocate(triggerPos);
            }

        return true;
    }
};

class npc_wg_relic_guardian : public CreatureScript
{
public:
    npc_wg_relic_guardian() : CreatureScript("npc_wg_relic_guardian") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wg_relic_guardianAI(creature);
    }

    struct npc_wg_relic_guardianAI  : public ScriptedAI
    {
        npc_wg_relic_guardianAI(Creature *c) : ScriptedAI(c) {}

        void MoveInLineOfSight(Unit* who)
        {
            if (!who || who->GetTypeId() != TYPEID_PLAYER)
                return;

            if (who->ToPlayer()->isGameMaster())
                return;

            Player* player = who->ToPlayer();

            if (OutdoorPvPWG *pvpWG = (OutdoorPvPWG*)sOutdoorPvPMgr->GetOutdoorPvPToZoneId(4197))
                if (me->IsWithinDistInMap(player, 18, false))
                    if (player->GetTeamId() == pvpWG->getAttackerTeam() && !pvpWG->MaingateDestroyed)
                        player->TeleportTo(571, 4608.08f, 2844.69f, 396.9f, 0.0f);
        }
    };

};

class npc_wg_cannon : public CreatureScript
{
public:
    npc_wg_cannon() : CreatureScript("npc_wg_cannon") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wg_cannonAI(creature);
    }

    struct npc_wg_cannonAI  : public ScriptedAI
    {
        npc_wg_cannonAI(Creature *c) : ScriptedAI(c) {}

        void Reset()
        {
            me->SetFlying(true);
        }
    };

};
void AddSC_wintergrasp()
{
    new npc_demolisher_engineerer();
    new npc_wg_ally_battle_mage();
    new npc_wg_horde_battle_mage();
    new go_wg_veh_teleporter();
    new npc_wg_relic_guardian();
    new npc_wg_cannon();
}
