/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Dragonblight
SD%Complete: 100
SDComment:
SDCategory: Dragonblight
EndScriptData */

/* ContentData
npc_alexstrasza_wr_gate
EndContentData */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"

enum eEnums
{
    QUEST_RETURN_TO_AG_A    = 12499,
    QUEST_RETURN_TO_AG_H    = 12500,
    MOVIE_ID_GATES          = 14
};

#define GOSSIP_ITEM_WHAT_HAPPENED   "Alexstrasza, can you show me what happened here?"

class npc_alexstrasza_wr_gate : public CreatureScript
{
public:
    npc_alexstrasza_wr_gate() : CreatureScript("npc_alexstrasza_wr_gate") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestRewardStatus(QUEST_RETURN_TO_AG_A) || player->GetQuestRewardStatus(QUEST_RETURN_TO_AG_H))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_WHAT_HAPPENED, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        {
            player->CLOSE_GOSSIP_MENU();
            player->SendMovieStart(MOVIE_ID_GATES);
        }

        return true;
    }
};

/*######
## npc_hourglass_of_eternity
######*/
/*Support for 'Future you' is currently missing*/
enum HourglassData
{
    NPC_INFINITE_CHRONO_MAGUS    = 27898,
    NPC_INFINITE_ASSAILANT       = 27896,
    NPC_INFINITE_DESTROYER       = 27897,
    NPC_INFINITE_TIMERENDER      = 27900
};

class npc_hourglass : public CreatureScript
{
public:
    npc_hourglass() : CreatureScript("npc_hourglass") {}

    struct npc_hourglassAI : public ScriptedAI
    {
        npc_hourglassAI(Creature* creature) : ScriptedAI(creature) { Reset(); }

        uint64 uiWaveTimer;
        uint32 uiWaveCounter;

        void Reset()
        {
            uiWaveTimer = 5000;
            uiWaveCounter = 0;
        }

        void JustSummoned(Creature* pSummoned)
        {
            pSummoned->AI()->AttackStart(me);
        }

        void SummonWave()
        {
        switch(uiWaveCounter)
            {
            case 0: me->SummonCreature(NPC_INFINITE_CHRONO_MAGUS, me->GetPositionX()+5,me->GetPositionY(),me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                    me->SummonCreature(NPC_INFINITE_ASSAILANT, me->GetPositionX()-5,me->GetPositionY(),me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                    break;
            case 1: me->SummonCreature(NPC_INFINITE_CHRONO_MAGUS, me->GetPositionX()+5,me->GetPositionY(),me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                    me->SummonCreature(NPC_INFINITE_CHRONO_MAGUS, me->GetPositionX()-5,me->GetPositionY(),me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                    break;
            case 2: me->SummonCreature(NPC_INFINITE_CHRONO_MAGUS, me->GetPositionX()+5,me->GetPositionY(),me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                    me->SummonCreature(NPC_INFINITE_ASSAILANT, me->GetPositionX()-5,me->GetPositionY(),me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                    me->SummonCreature(NPC_INFINITE_DESTROYER, me->GetPositionX()+5,me->GetPositionY()+5 ,me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                    break;
            case 3: me->SummonCreature(NPC_INFINITE_CHRONO_MAGUS, me->GetPositionX()+5,me->GetPositionY(),me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                    me->SummonCreature(NPC_INFINITE_ASSAILANT, me->GetPositionX()-5,me->GetPositionY(),me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                    me->SummonCreature(NPC_INFINITE_DESTROYER, me->GetPositionX()+5,me->GetPositionY()+5 ,me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
                    break;
            case 4: me->SummonCreature(NPC_INFINITE_TIMERENDER, me->GetPositionX()+5,me->GetPositionY(),me->GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);
                    break;
            }
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (uiWaveTimer <= uiDiff)
            {
                if(uiWaveCounter<=4)
                {
                    SummonWave();
                    uiWaveTimer = 15000;
                    uiWaveCounter++;
                }
                else me->DespawnOrUnsummon();

            } else uiWaveTimer -= uiDiff;
        }

        void JustDied()
        {
            if(Player* player = me->GetOwner()->ToPlayer())
            {
                player->FailQuest(12470);
                player->FailQuest(13343);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hourglassAI(creature);
    }
};

/*#######################
# npc_ws_battle_standard
########################*/

enum
{
    NPC_ANUBAR_AMBUSHER      = 26402,
    QUEST_MIGHT_OF_THE_HORDE = 12053
};

class npc_ws_battle_standard : public CreatureScript
{
public:
    npc_ws_battle_standard() : CreatureScript("npc_ws_battle_standard") {}

    struct npc_ws_battle_standardAI : public ScriptedAI
    {
        npc_ws_battle_standardAI(Creature* creature) : ScriptedAI(creature) { Reset(); }

        uint64 uiWaveTimer;
        uint32 uiWaveCounter;

        void Reset()
        {
            uiWaveTimer = 5000;
            uiWaveCounter = 0;
        }

        void JustSummoned(Creature* pSummoned)
        {
            pSummoned->AI()->AttackStart(me);
        }

        void SummonWave()
        {
        switch(uiWaveCounter)
            {
            case 0: me->SummonCreature(NPC_ANUBAR_AMBUSHER, me->GetPositionX()+3,me->GetPositionY(),me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 60000);
                    break;
            case 1: me->SummonCreature(NPC_ANUBAR_AMBUSHER, me->GetPositionX()+3,me->GetPositionY(),me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 60000);
                    break;
            case 2: me->SummonCreature(NPC_ANUBAR_AMBUSHER, me->GetPositionX()+3,me->GetPositionY(),me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 60000);
                    me->SummonCreature(NPC_ANUBAR_AMBUSHER, me->GetPositionX()-3,me->GetPositionY(),me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 60000);
                    break;
            case 3: me->SummonCreature(NPC_ANUBAR_AMBUSHER, me->GetPositionX()+3,me->GetPositionY(),me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 60000);
                    me->SummonCreature(NPC_ANUBAR_AMBUSHER, me->GetPositionX()-3,me->GetPositionY(),me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 60000);
                    me->SummonCreature(NPC_ANUBAR_AMBUSHER, me->GetPositionX()+3,me->GetPositionY()+3 ,me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 60000);
                    break;
            case 4: if (Player *player = me->GetOwner()->ToPlayer())
                    {
                        if (player->GetQuestStatus(QUEST_MIGHT_OF_THE_HORDE) == QUEST_STATUS_INCOMPLETE)
                        {
                            player->GroupEventHappens(QUEST_MIGHT_OF_THE_HORDE,me);
                            me->DespawnOrUnsummon();
                        }
                    }
                    break;
            }
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (uiWaveTimer <= uiDiff)
            {
                if(uiWaveCounter<=4)
                {
                    SummonWave();
                    uiWaveTimer = 15000;
                    uiWaveCounter++;
                }
                else me->DespawnOrUnsummon();

            } else uiWaveTimer -= uiDiff;
        }

        void JustDied()
        {
            if(Player *player = me->GetOwner()->ToPlayer())
            {
                if (player->GetQuestStatus(QUEST_MIGHT_OF_THE_HORDE) == QUEST_STATUS_INCOMPLETE)
                    player->FailQuest(QUEST_MIGHT_OF_THE_HORDE);
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ws_battle_standardAI(creature);
    }
};

/*###################################
# item_emblazoned_battle_horn (36864)
####################################*/

class item_emblazoned_battle_horn : public ItemScript
{
    public:

        item_emblazoned_battle_horn() : ItemScript("item_emblazoned_battle_horn") { }

        bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/)
        {
            if (player->GetQuestStatus(12151) == QUEST_STATUS_INCOMPLETE)
                player->SummonCreature(27002,2713.821045f,445.447998f,67.814095f,5.241539f,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT,30000);
                return true;
        }
};


void AddSC_dragonblight()
{
    new npc_alexstrasza_wr_gate;
    new npc_hourglass;
    new npc_ws_battle_standard;
    new item_emblazoned_battle_horn;
}
