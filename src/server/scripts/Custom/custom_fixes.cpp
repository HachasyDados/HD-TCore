/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptPCH.h"
#include "Vehicle.h"

/*#####################
# go_not_a_bug (193939)
######################*/

class go_not_a_bug : public GameObjectScript
{
public:
    go_not_a_bug() : GameObjectScript("go_not_a_bug") { }

    enum SummoningStoneData
    {
        QUEST_NOT_A_BUG_A = 13342,
        QUEST_NOT_A_BUG_H = 13358,
        QUEST_NOT_A_BUG_A_D = 13344,
        QUEST_NOT_A_BUG_H_D = 13365,
        NPC_DARK_MESSENGER = 32316,
        NPC_NOT_A_BUG_KC = 32314
    };

    bool OnGossipHello(Player* player, GameObject* go)
    {
        if (player->GetQuestStatus(QUEST_NOT_A_BUG_A) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_NOT_A_BUG_H) == QUEST_STATUS_INCOMPLETE ||
            player->GetQuestStatus(QUEST_NOT_A_BUG_A_D) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_NOT_A_BUG_H_D) == QUEST_STATUS_INCOMPLETE)
        {
            go->SummonCreature(NPC_DARK_MESSENGER,8028.225098f,2077.155518f,499.729156f,3.947409f,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN,5000);
            player->KilledMonsterCredit(NPC_NOT_A_BUG_KC,0);
        }
        return true;
    }
};

/*#############################
# item_alumeths_remains (44480)
###############################*/

class item_alumeths_remains : public ItemScript
{
    public:

        item_alumeths_remains() : ItemScript("item_alumeths_remains") { }

        enum AlumethsRemainsData
        {
            QUEST_NO_REST_FOR_THE_WICKED_A = 13346,
            QUEST_NO_REST_FOR_THE_WICKED_H = 13367,
            QUEST_NO_REST_FOR_THE_WICKED_A_D = 13350,
            QUEST_NO_REST_FOR_THE_WICKED_H_D = 13368,
            NPC_ALUMETH = 32300
        };

        bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/)
        {
            if (player->GetQuestStatus(QUEST_NO_REST_FOR_THE_WICKED_A) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_NO_REST_FOR_THE_WICKED_H) == QUEST_STATUS_INCOMPLETE ||
                player->GetQuestStatus(QUEST_NO_REST_FOR_THE_WICKED_A_D) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_NO_REST_FOR_THE_WICKED_H_D) == QUEST_STATUS_INCOMPLETE)
                player->SummonCreature(NPC_ALUMETH,8229.606445f,2179.215820f,499.736694f,3.161045f,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,30000);
                return true;
        }
};

/*##################################
# npc_q13355_q13320_trigger (97001)
###################################*/

class npc_q13355_q13320_trigger : public CreatureScript
{
public:
    npc_q13355_q13320_trigger() : CreatureScript("npc_q13355_q13320_trigger") { }

    enum q13355q13320TriggerData
    {
        GO_TEMP_CULTISTS_CAULDRON = 300240,
        BLUE_CAULDRON_GUID = 99719,
        BLACK_CAULDRON_GUID = 99718,
        GREEN_CAULDRON_GUID = 99720,
        BLUE_SAMPLE_KC = 32242,
        BLACK_SAMPLE_KC = 32245,
        GREEN_SAMPLE_KC = 32244,
        SPELL_COLLECT_SAMPLE = 60256
    };

    struct npc_q13355_q13320_triggerAI : public ScriptedAI
    {
        npc_q13355_q13320_triggerAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() {}

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (caster->GetTypeId() != TYPEID_PLAYER)
                return;

            if (caster->GetTypeId() == TYPEID_PLAYER && spell->Id == SPELL_COLLECT_SAMPLE)
            {
                if (GameObject* go = me->FindNearestGameObject(GO_TEMP_CULTISTS_CAULDRON,10.0f))
                {
                    switch(go->GetGUIDLow())
                    {
                        case BLUE_CAULDRON_GUID: caster->ToPlayer()->KilledMonsterCredit(BLUE_SAMPLE_KC,0); break;
                        case BLACK_CAULDRON_GUID: caster->ToPlayer()->KilledMonsterCredit(BLACK_SAMPLE_KC,0); break;
                        case GREEN_CAULDRON_GUID: caster->ToPlayer()->KilledMonsterCredit(GREEN_SAMPLE_KC,0); break;
                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_q13355_q13320_triggerAI(creature);
    }
};

/*#################################
# npc_brokendown_shredders (27354)
##################################*/

class npc_brokendown_shredders : public CreatureScript
{
public:
    npc_brokendown_shredders() : CreatureScript("npc_brokendown_shredders") { }

    struct npc_brokendown_shreddersAI : public ScriptedAI
    {
        npc_brokendown_shreddersAI(Creature* creature) : ScriptedAI(creature) { }

        void UpdateAI(const uint32 /*diff*/)
        {
            Unit* player = me->GetVehicleKit()->GetPassenger(0);
                    if (!player && ((me->GetPositionX() != me->GetHomePosition().GetPositionX()) && (me->GetPositionY() != me->GetHomePosition().GetPositionY()) && (me->GetPositionZ() != me->GetHomePosition().GetPositionZ())))
            {
                me->DisappearAndDie();
                me->Respawn();
                return;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_brokendown_shreddersAI(creature);
    }
};

/*#################################
# npc_shredders_taker (27371, 2742)
##################################*/

class npc_shredders_taker : public CreatureScript
{
public:
    npc_shredders_taker() : CreatureScript("npc_shredders_taker") { }

    struct npc_shredders_takerAI : public ScriptedAI
    {
        npc_shredders_takerAI(Creature* creature) : ScriptedAI(creature) { }

        void MoveInLineOfSight(Unit* who)
        {
            if(!who)
                return;

            if (who->GetTypeId() != TYPEID_UNIT || who->GetEntry() != 27354 || !who->isCharmedOwnedByPlayerOrPlayer())
                return;

            Player* player = who->GetCharmerOrOwner()->ToPlayer();

            if (player && me->IsWithinDistInMap(who, 15.0f))
            {
                player->KilledMonsterCredit(27396, 0);
                player->ExitVehicle();
                who->ToCreature()->DisappearAndDie();
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_shredders_takerAI(creature);
    }
};

/*##########################
# item_writhing_mass (44304)
###########################*/

class item_writhing_mass : public ItemScript
{
    public:

        item_writhing_mass() : ItemScript("item_writhing_mass") { }

        enum WrithingMassData
        {
            QUEST_RETEST_NOW_A = 13321,
            QUEST_RETEST_NOW_H = 13356,
            QUEST_RETEST_NOW_A_D = 13322,
            QUEST_RETEST_NOW_H_D = 13357,
            NPC_RETEST_NOW_KC = 32266
        };

        bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/)
        {
            if (player->GetQuestStatus(QUEST_RETEST_NOW_A) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_RETEST_NOW_H) == QUEST_STATUS_INCOMPLETE ||
                player->GetQuestStatus(QUEST_RETEST_NOW_A_D) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_RETEST_NOW_H_D) == QUEST_STATUS_INCOMPLETE)
                player->KilledMonsterCredit(NPC_RETEST_NOW_KC,0);
                return true;
        }
};

void AddSC_custom_fixes()
{
    new go_not_a_bug;
    new item_alumeths_remains;
    new npc_q13355_q13320_trigger;
    new npc_brokendown_shredders;
    new npc_shredders_taker;
    new item_writhing_mass;
}
