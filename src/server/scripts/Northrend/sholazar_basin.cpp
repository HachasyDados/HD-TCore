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

/* ScriptData
SDName: Sholazar_Basin
SD%Complete: 100
SDComment: Quest support: 12570, 12573, 12621.
SDCategory: Sholazar_Basin
EndScriptData */

/* ContentData
npc_injured_rainspeaker_oracle
npc_vekjik
avatar_of_freya
EndContentData */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"
#include "Vehicle.h"

/*######
## npc_injured_rainspeaker_oracle
######*/

#define GOSSIP_ITEM1 "I am ready to travel to your village now."

enum eRainspeaker
{
    SAY_START_IRO                       = -1571000,
    SAY_QUEST_ACCEPT_IRO                = -1571001,
    SAY_END_IRO                         = -1571002,

    QUEST_FORTUNATE_MISUNDERSTANDINGS   = 12570,
    FACTION_ESCORTEE_A                  = 774,
    FACTION_ESCORTEE_H                  = 775
};

class npc_injured_rainspeaker_oracle : public CreatureScript
{
public:
    npc_injured_rainspeaker_oracle() : CreatureScript("npc_injured_rainspeaker_oracle") { }

    struct npc_injured_rainspeaker_oracleAI : public npc_escortAI
    {
        npc_injured_rainspeaker_oracleAI(Creature* c) : npc_escortAI(c) { c_guid = c->GetGUID(); }

        uint64 c_guid;

        void Reset()
        {
            me->RestoreFaction();
            // if we will have other way to assign this to only one npc remove this part
            if (GUID_LOPART(me->GetGUID()) != 101030)
            {
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            }
        }

        void WaypointReached(uint32 i)
        {
            Player* player = GetPlayerForEscort();

            if (!player)
                return;

            switch (i)
            {
            case 1: SetRun(); break;
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
                me->RemoveUnitMovementFlag(MOVEMENTFLAG_SWIMMING);
                me->RemoveUnitMovementFlag(MOVEMENTFLAG_JUMPING);
                me->SetSpeed(MOVE_SWIM, 0.85f, true);
                me->AddUnitMovementFlag(MOVEMENTFLAG_SWIMMING | MOVEMENTFLAG_LEVITATING);
                break;
            case 19:
                me->SetUnitMovementFlags(MOVEMENTFLAG_JUMPING);
                break;
            case 28:
                if (Player* player = GetPlayerForEscort())
                    player->GroupEventHappens(QUEST_FORTUNATE_MISUNDERSTANDINGS, me);
              //  me->RestoreFaction();
                DoScriptText(SAY_END_IRO, me);
                SetRun(false);
                break;
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            if (!HasEscortState(STATE_ESCORT_ESCORTING))
                return;

            if (Player* player = GetPlayerForEscort())
            {
              if (player->GetQuestStatus(QUEST_FORTUNATE_MISUNDERSTANDINGS) != QUEST_STATUS_COMPLETE)
                player->FailQuest(QUEST_FORTUNATE_MISUNDERSTANDINGS);
            }
        }
    };

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_FORTUNATE_MISUNDERSTANDINGS) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        {
            CAST_AI(npc_escortAI, (creature->AI()))->Start(true, false, player->GetGUID());
            CAST_AI(npc_escortAI, (creature->AI()))->SetMaxPlayerDistance(35.0f);
            creature->SetUnitMovementFlags(MOVEMENTFLAG_JUMPING);
            DoScriptText(SAY_START_IRO, creature);

            switch (player->GetTeam()){
            case ALLIANCE:
                creature->setFaction(FACTION_ESCORTEE_A);
                break;
            case HORDE:
                creature->setFaction(FACTION_ESCORTEE_H);
                break;
            }
        }
        return true;
    }

    bool OnQuestAccept(Player* /*player*/, Creature* creature, Quest const* /*_Quest*/)
    {
        DoScriptText(SAY_QUEST_ACCEPT_IRO, creature);
        return false;
    }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_injured_rainspeaker_oracleAI(creature);
    }
};

/*######
## npc_vekjik
######*/

#define GOSSIP_VEKJIK_ITEM1 "Chaman Vekjik, he hablado con los lenguas-grandes y desean la paz. He traido esta ofrenda en su nombre."    //"Shaman Vekjik, I have spoken with the big-tongues and they desire peace. I have brought this offering on their behalf."
#define GOSSIP_VEKJIK_ITEM2 "No no... no tengo intención de traicionar a tu gente. Solo intentaba defenderme, fue todo un malentendido." //"No no... I had no intentions of betraying your people. I was only defending myself. it was all a misunderstanding."

enum eVekjik
{
    GOSSIP_TEXTID_VEKJIK1       = 13137,
    GOSSIP_TEXTID_VEKJIK2       = 13138,

    SAY_TEXTID_VEKJIK1          = -1000208,

    SPELL_FREANZYHEARTS_FURY    = 51469,

    QUEST_MAKING_PEACE          = 12573
};

class npc_vekjik : public CreatureScript
{
public:
    npc_vekjik() : CreatureScript("npc_vekjik") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_MAKING_PEACE) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_VEKJIK_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_VEKJIK1, creature->GetGUID());
            return true;
        }

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_VEKJIK_ITEM2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_VEKJIK2, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                player->CLOSE_GOSSIP_MENU();
                DoScriptText(SAY_TEXTID_VEKJIK1, creature, player);
                creature->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK_DEST, true);
                player->AreaExploredOrEventHappens(QUEST_MAKING_PEACE);
                creature->CastSpell(player, SPELL_FREANZYHEARTS_FURY, false);
                break;
        }

        return true;
    }
};

/*######
## avatar_of_freya
######*/

#define GOSSIP_ITEM_AOF1 "I want to stop the Scourge as much as you do. How can I help?"
#define GOSSIP_ITEM_AOF2 "You can trust me. I am no friend of the Lich King."
#define GOSSIP_ITEM_AOF3 "I will not fail."

enum eFreya
{
    QUEST_FREYA_PACT         = 12621,

    SPELL_FREYA_CONVERSATION = 52045,

    GOSSIP_TEXTID_AVATAR1    = 13303,
    GOSSIP_TEXTID_AVATAR2    = 13304,
    GOSSIP_TEXTID_AVATAR3    = 13305
};

class npc_avatar_of_freya : public CreatureScript
{
public:
    npc_avatar_of_freya() : CreatureScript("npc_avatar_of_freya") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_FREYA_PACT) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_AOF1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

        player->PlayerTalkClass->SendGossipMenu(GOSSIP_TEXTID_AVATAR1, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (uiAction)
        {
        case GOSSIP_ACTION_INFO_DEF+1:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_AOF2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            player->PlayerTalkClass->SendGossipMenu(GOSSIP_TEXTID_AVATAR2, creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_AOF3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            player->PlayerTalkClass->SendGossipMenu(GOSSIP_TEXTID_AVATAR3, creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            player->CastSpell(player, SPELL_FREYA_CONVERSATION, true);
            player->CLOSE_GOSSIP_MENU();
            break;
        }
        return true;
    }
};

/*######
## npc_bushwhacker
######*/

class npc_bushwhacker : public CreatureScript
{
public:
    npc_bushwhacker() : CreatureScript("npc_bushwhacker") { }

    struct npc_bushwhackerAI : public ScriptedAI
    {
        npc_bushwhackerAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void InitializeAI()
        {
            if (me->isDead())
                return;

            if (me->isSummon())
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                    if (summoner)
                        me->GetMotionMaster()->MovePoint(0, summoner->GetPositionX(), summoner->GetPositionY(), summoner->GetPositionZ());

            Reset();
        }

        void UpdateAI(const uint32 /*uiDiff*/)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_bushwhackerAI(creature);
    }
};

/*######
## npc_engineer_helice
######*/

enum eEnums
{
    SPELL_EXPLODE_CRYSTAL       = 62487,
    SPELL_FLAMES                = 64561,

    SAY_WP_7                    = -1800047,
    SAY_WP_6                    = -1800048,
    SAY_WP_5                    = -1800049,
    SAY_WP_4                    = -1800050,
    SAY_WP_3                    = -1800051,
    SAY_WP_2                    = -1800052,
    SAY_WP_1                    = -1800053,

    QUEST_DISASTER              = 12688
};

class npc_engineer_helice : public CreatureScript
{
public:
    npc_engineer_helice() : CreatureScript("npc_engineer_helice") { }

    struct npc_engineer_heliceAI : public npc_escortAI
    {
        npc_engineer_heliceAI(Creature* creature) : npc_escortAI(creature) { }

        uint32 m_uiChatTimer;

        void WaypointReached(uint32 i)
        {
            Player* player = GetPlayerForEscort();
            switch (i)
            {
                case 0:
                    DoScriptText(SAY_WP_2, me);
                    break;
                case 1:
                    DoScriptText(SAY_WP_3, me);
                    me->CastSpell(5918.33f, 5372.91f, -98.770f, SPELL_EXPLODE_CRYSTAL, true);
                    me->SummonGameObject(184743, 5918.33f, 5372.91f, -98.770f, 0, 0, 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN);     //approx 3 to 4 seconds
                    me->HandleEmoteCommand(EMOTE_ONESHOT_LAUGH);
                    break;
                case 2:
                    DoScriptText(SAY_WP_4, me);
                    break;
                case 7:
                    DoScriptText(SAY_WP_5, me);
                    break;
                case 8:
                    me->CastSpell(5887.37f, 5379.39f, -91.289f, SPELL_EXPLODE_CRYSTAL, true);
                    me->SummonGameObject(184743, 5887.37f, 5379.39f, -91.289f, 0, 0, 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN);      //approx 3 to 4 seconds
                    me->HandleEmoteCommand(EMOTE_ONESHOT_LAUGH);
                    break;
                case 9:
                    DoScriptText(SAY_WP_6, me);
                    break;
                case 13:
                    if (player)
                    {
                        player->GroupEventHappens(QUEST_DISASTER, me);
                        DoScriptText(SAY_WP_7, me);
                    }
                    break;
            }
        }

        void Reset()
        {
            m_uiChatTimer = 4000;
        }
        void JustDied(Unit* /*killer*/)
        {
            Player* player = GetPlayerForEscort();
            if (HasEscortState(STATE_ESCORT_ESCORTING))
            {
                if (player)
                    player->FailQuest(QUEST_DISASTER);
            }
        }

        void UpdateAI(const uint32 uiDiff)
        {
            npc_escortAI::UpdateAI(uiDiff);

            if (HasEscortState(STATE_ESCORT_ESCORTING))
            {
                if (m_uiChatTimer <= uiDiff)
                {
                    m_uiChatTimer = 12000;
                }
                else
                    m_uiChatTimer -= uiDiff;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_engineer_heliceAI(creature);
    }

    bool OnQuestAccept(Player* player, Creature* creature, const Quest* quest)
    {
        if (quest->GetQuestId() == QUEST_DISASTER)
        {
            if (npc_engineer_heliceAI* pEscortAI = CAST_AI(npc_engineer_helice::npc_engineer_heliceAI, creature->AI()))
            {
                creature->GetMotionMaster()->MoveJumpTo(0, 0.4f, 0.4f);
                creature->setFaction(113);

                pEscortAI->Start(false, false, player->GetGUID());
                DoScriptText(SAY_WP_1, creature);
            }
        }
        return true;
    }
};

/*#####
## npc_jungle_punch_target
#####*/

#define SAY_OFFER     "Care to try Grimbooze Thunderbrew's new jungle punch?"
#define SAY_HEMET_1   "Aye, I'll try it."
#define SAY_HEMET_2   "That's exactly what I needed!"
#define SAY_HEMET_3   "It's got my vote! That'll put hair on your chest like nothing else will."
#define SAY_HADRIUS_1 "I'm always up for something of Grimbooze's."
#define SAY_HADRIUS_2 "Well, so far, it tastes like something my wife would drink..."
#define SAY_HADRIUS_3 "Now, there's the kick I've come to expect from Grimbooze's drinks! I like it!"
#define SAY_TAMARA_1  "Sure!"
#define SAY_TAMARA_2  "Oh my..."
#define SAY_TAMARA_3  "Tastes like I'm drinking... engine degreaser!"

enum utils
{
    NPC_HEMET   = 27986,
    NPC_HADRIUS = 28047,
    NPC_TAMARA  = 28568,
    SPELL_OFFER = 51962,
    QUEST_ENTRY = 12645,
};

class npc_jungle_punch_target : public CreatureScript
{
public:
    npc_jungle_punch_target() : CreatureScript("npc_jungle_punch_target") { }

    struct npc_jungle_punch_targetAI : public ScriptedAI
    {
        npc_jungle_punch_targetAI(Creature* creature) : ScriptedAI(creature) {}

        uint16 sayTimer;
        uint8 sayStep;

        void Reset()
        {
            sayTimer = 3500;
            sayStep = 0;
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!sayStep)
                return;

            if (sayTimer < uiDiff)
            {
                switch (sayStep)
                {
                    case 0:
                    {
                        switch (me->GetEntry())
                        {
                            case NPC_HEMET:   me->MonsterSay(SAY_HEMET_1, LANG_UNIVERSAL, 0);   break;
                            case NPC_HADRIUS: me->MonsterSay(SAY_HADRIUS_1, LANG_UNIVERSAL, 0); break;
                            case NPC_TAMARA:  me->MonsterSay(SAY_TAMARA_1, LANG_UNIVERSAL, 0);  break;
                        }
                        sayTimer = 3000;
                        sayStep++;
                        break;
                    }
                    case 1:
                    {
                        switch (me->GetEntry())
                        {
                            case NPC_HEMET:   me->MonsterSay(SAY_HEMET_2, LANG_UNIVERSAL, 0);   break;
                            case NPC_HADRIUS: me->MonsterSay(SAY_HADRIUS_2, LANG_UNIVERSAL, 0); break;
                            case NPC_TAMARA:  me->MonsterSay(SAY_TAMARA_2, LANG_UNIVERSAL, 0);  break;
                        }
                        sayTimer = 3000;
                        sayStep++;
                        break;
                    }
                    case 2:
                    {
                        switch (me->GetEntry())
                        {
                            case NPC_HEMET:   me->MonsterSay(SAY_HEMET_3, LANG_UNIVERSAL, 0);   break;
                            case NPC_HADRIUS: me->MonsterSay(SAY_HADRIUS_3, LANG_UNIVERSAL, 0); break;
                            case NPC_TAMARA:  me->MonsterSay(SAY_TAMARA_3, LANG_UNIVERSAL, 0);  break;
                        }
                        sayTimer = 3000;
                        sayStep = 0;
                        break;
                    }
                }
            }
            else
                sayTimer -= uiDiff;
        }

        void SpellHit(Unit* caster, const SpellInfo* proto)
        {
            if (!proto || proto->Id != SPELL_OFFER)
                return;

            if (!caster->ToPlayer())
                return;

            QuestStatusMap::const_iterator itr = caster->ToPlayer()->getQuestStatusMap().find(QUEST_ENTRY);
            if (itr->second.m_status != QUEST_STATUS_INCOMPLETE)
                return;

            for (uint8 i=0; i<3; i++)
            {
                switch (i)
                {
                   case 0:
                       if (NPC_HEMET != me->GetEntry())
                           continue;
                       else
                           break;
                   case 1:
                       if (NPC_HADRIUS != me->GetEntry())
                           continue;
                       else
                           break;
                   case 2:
                       if (NPC_TAMARA != me->GetEntry())
                           continue;
                       else
                           break;
                }

                if (itr->second.m_creatureOrGOcount[i] != 0)
                    continue;

                caster->ToPlayer()->KilledMonsterCredit(me->GetEntry(), 0);
                caster->ToPlayer()->Say(SAY_OFFER, LANG_UNIVERSAL);
                sayStep = 0;
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_jungle_punch_targetAI(creature);
    }
};

/*######
## npc_adventurous_dwarf
######*/

#define GOSSIP_OPTION_ORANGE    "Can you spare an orange?"
#define GOSSIP_OPTION_BANANAS   "Have a spare bunch of bananas?"
#define GOSSIP_OPTION_PAPAYA    "I could really use a papaya."

enum eAdventurousDwarf
{
    QUEST_12634         = 12634,

    ITEM_BANANAS        = 38653,
    ITEM_PAPAYA         = 38655,
    ITEM_ORANGE         = 38656,

    SPELL_ADD_ORANGE    = 52073,
    SPELL_ADD_BANANAS   = 52074,
    SPELL_ADD_PAPAYA    = 52076,

    GOSSIP_MENU_DWARF   = 13307,

    SAY_DWARF_OUCH      = -1571042,
    SAY_DWARF_HELP      = -1571043
};

class npc_adventurous_dwarf : public CreatureScript
{
public:
    npc_adventurous_dwarf() : CreatureScript("npc_adventurous_dwarf") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        DoScriptText(SAY_DWARF_OUCH, creature);
        return NULL;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_12634) != QUEST_STATUS_INCOMPLETE)
            return false;

        if (player->GetItemCount(ITEM_ORANGE) < 1)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_OPTION_ORANGE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

        if (player->GetItemCount(ITEM_BANANAS) < 2)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_OPTION_BANANAS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

        if (player->GetItemCount(ITEM_PAPAYA) < 1)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_OPTION_PAPAYA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

        player->PlayerTalkClass->SendGossipMenu(GOSSIP_MENU_DWARF, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        uint32 spellId = 0;
        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF + 1: spellId = SPELL_ADD_ORANGE;     break;
            case GOSSIP_ACTION_INFO_DEF + 2: spellId = SPELL_ADD_BANANAS;    break;
            case GOSSIP_ACTION_INFO_DEF + 3: spellId = SPELL_ADD_PAPAYA;     break;
        }
        if (spellId)
            player->CastSpell(player, spellId, true);
        DoScriptText(SAY_DWARF_HELP, creature);
        creature->DespawnOrUnsummon();
        return true;
    }
};

const Position CaptiveCrocWaypoints[32] =
{
    {5296.98f, 4449.35f, -97.6785f, 0.0f},
    {5268.84f, 4431.05f, -95.9974f, 0.0f},
    {5253.46f, 4394.40f, -95.0352f, 0.0f},
    {5263.19f, 4365.86f, -98.5669f, 0.0f},
    {5284.49f, 4366.25f, -101.402f, 0.0f},
    {5297.54f, 4358.85f, -105.052f, 0.0f},
    {5354.68f, 4361.32f, -128.512f, 0.0f},
    {5378.45f, 4313.85f, -147.025f, 0.0f},
    {5418.90f, 4345.02f, -146.904f, 0.0f},
    {5448.35f, 4407.74f, -146.738f, 0.0f},
    {5511.23f, 4457.99f, -146.229f, 0.0f},
    {5507.92f, 4540.06f, -145.055f, 0.0f},
    {5496.91f, 4565.59f, -141.307f, 0.0f},
    {5489.50f, 4608.78f, -138.538f, 0.0f},
    {5506.16f, 4640.55f, -134.925f, 0.0f},
    {5577.96f, 4664.14f, -134.699f, 0.0f},
    {5615.76f, 4702.42f, -136.552f, 0.0f},
    {5631.72f, 4729.98f, -134.209f, 0.0f},
    {5648.63f, 4749.76f, -140.618f, 0.0f},
    {5667.33f, 4777.87f, -141.298f, 0.0f},
    {5697.99f, 4814.09f, -139.960f, 0.0f},
    {5707.43f, 4829.78f, -135.915f, 0.0f},
    {5796.30f, 4840.33f, -133.721f, 0.0f},
    {5818.77f, 4842.79f, -140.250f, 0.0f},
    {5851.73f, 4834.99f, -134.428f, 0.0f},
    {5886.75f, 4832.68f, -129.530f, 0.0f},
    {5925.07f, 4836.92f, -113.021f, 0.0f},
    {5948.74f, 4843.23f, -103.147f, 0.0f},
    {5984.39f, 4858.27f, -98.9468f, 0.0f},
    {6055.89f, 4888.39f, -94.4171f, 0.0f},
    {6129.51f, 4929.48f, -95.6752f, 0.0f},
    {6153.20f, 4942.70f, -90.4089f, 0.0f}
};
#define GOSSIP_ITEM1 "Viajar a Refugio Susurraneblina"

class npc_captive_croco_gossip : public CreatureScript
{
public:
    npc_captive_croco_gossip() : CreatureScript("npc_captive_croco_gossip") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {

        if (player->GetQuestStatus(12536) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->CLOSE_GOSSIP_MENU();

        if (!player->HasUnitState(UNIT_STAT_ONVEHICLE))
        {
            if (Creature* pTemp = player->SummonCreature(28308, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), 0))
            {
                pTemp->SetCreatorGUID(player->GetGUID());
                player->EnterVehicle(pTemp, 0);
            }
            if (Unit* base = player->GetVehicleBase())
                if (base->isCharmed())
                    base->RemoveCharmedBy(base->GetCharmer());
        }
        return true;
    }
};

class npc_captive_croco_vehicle : public CreatureScript
{
public:
    npc_captive_croco_vehicle() : CreatureScript("npc_captive_croco_vehicle") { }

    struct npc_captive_croco_vehicleAI : public ScriptedAI
    {
        npc_captive_croco_vehicleAI(Creature* creature) : ScriptedAI(creature) { }

        uint8 count;
        uint64 uiPlayer;
        bool occupied;
        bool wp_reached;
        bool movementStarted;

        void Reset()
        {
            me->SetSpeed(MOVE_SWIM, 2.0f, true);
            count = 0;
            occupied = false;
            wp_reached = false;
            movementStarted = false;
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE || id != count)
                return;

            if (id < 31)
            {
                Unit* player = me->GetVehicleKit()->GetPassenger(0);
                if (player && player->GetTypeId() == TYPEID_PLAYER)
                {
                    ++count;
                    wp_reached = true;
                }
                else
                    me->DisappearAndDie();
            }
            else // reached questgiver, give credit
            {
                Unit* player = me->GetVehicleKit()->GetPassenger(0);
                if (player && player->GetTypeId() == TYPEID_PLAYER)
                {
                    player->ToPlayer()->CompleteQuest(12536);
                    player->ExitVehicle();
                }
                me->DisappearAndDie();
            }
        }

        void UpdateAI(const uint32 /*diff*/)
        {
            if (!me->isCharmed() && !movementStarted)
            {
                movementStarted = true;
                wp_reached = true;
            }

            if (wp_reached)
            {
                wp_reached = false;
                me->GetMotionMaster()->MovePoint(count, CaptiveCrocWaypoints[count]);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_captive_croco_vehicleAI(creature);
    }
};

enum HarkekDefines
{
    QUEST_ROUGH_RIDE       = 12536,
    QUEST_SAPPHIRE_QUEEN   = 12534,
    QUEST_APE_HUNTER_SLAVE = 12529,
    SPELL_ADDITEM_ZEPIK    = 52545,
    ITEM_ZEPIK             = 38512,
    SPELL_ADDITEM_DAJIK    = 52544,
    ITEM_DAJIK             = 38621,
    SPELL_ADDITEM_GOREGEK  = 52542,
    ITEM_GOREGEK           = 38619,
};

#define GOSSIP_ITEM_ZEPIK "Necesito comunicarme con Zepik."
#define GOSSIP_ITEM_DAJIK "Necesito comunicarme con Dajik."
#define GOSSIP_ITEM_GOREGEK "Necesito comunicarme con Goregek."

class npc_harkek_gossip : public CreatureScript
{
public:
    npc_harkek_gossip() : CreatureScript("npc_harkek_gossip") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_ROUGH_RIDE) == QUEST_STATUS_COMPLETE || player->GetQuestStatus(QUEST_ROUGH_RIDE) == QUEST_STATUS_REWARDED)
            if(!player->HasItemCount(ITEM_ZEPIK, 1, true))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ZEPIK, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

        if (player->GetQuestStatus(QUEST_SAPPHIRE_QUEEN) == QUEST_STATUS_COMPLETE || player->GetQuestStatus(QUEST_SAPPHIRE_QUEEN) == QUEST_STATUS_REWARDED)
            if(!player->HasItemCount(ITEM_DAJIK, 1, true))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DAJIK, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

        if (player->GetQuestStatus(QUEST_APE_HUNTER_SLAVE) == QUEST_STATUS_COMPLETE || player->GetQuestStatus(QUEST_APE_HUNTER_SLAVE) == QUEST_STATUS_REWARDED)
            if(!player->HasItemCount(ITEM_GOREGEK, 1, true))
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_GOREGEK, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* /*creature*/, uint32 /*sender*/, uint32 action)
    {
        player->CLOSE_GOSSIP_MENU();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF+1: player->CastSpell(player, SPELL_ADDITEM_ZEPIK, false); break;
            case GOSSIP_ACTION_INFO_DEF+2: player->CastSpell(player, SPELL_ADDITEM_DAJIK, false); break;
            case GOSSIP_ACTION_INFO_DEF+3: player->CastSpell(player, SPELL_ADDITEM_GOREGEK, false); break;
        }
        return true;
    }
};

enum stillEvents
{
    EVENT_BANANA_CLICK,
    EVENT_ORANGE_CLICK,
    EVENT_PAPAYA_CLICK,
    EVENT_VALVE_CLICK,
    EVENT_BRAZIER_CLICK
};

class go_still_tools : public GameObjectScript
{
public:
    go_still_tools(): GameObjectScript("go_still_tools") {}

        bool OnGossipHello(Player* player, GameObject* go)
        {
            if (Creature *pTipsy = go->FindNearestCreature(28566, 15.0f))
            {
                switch(go->GetEntry())
                {
                    case 190639: // Barrel of Papayas
                        pTipsy->AI()->DoAction(EVENT_PAPAYA_CLICK);
                        break;
                    case 190638: // Barrel of Bananas
                        pTipsy->AI()->DoAction(EVENT_BANANA_CLICK);
                        break;
                    case 190637: //Barrel of Oranges
                        pTipsy->AI()->DoAction(EVENT_ORANGE_CLICK);
                        break;
                    case 190636: // Brazier
                        pTipsy->AI()->DoAction(EVENT_BRAZIER_CLICK);
                        break;
                    case 190635: // Preassure Valve
                        pTipsy->AI()->DoAction(EVENT_VALVE_CLICK);
                        break;
                }
            }
            return true;
        }
};

#define GOSSIP_ITEM_TIPSY "Comencemos la destilacion."

class npc_tipsy_gossip : public CreatureScript
{
public:

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_tipsy_gossipAI (creature);
    }

    npc_tipsy_gossip() : CreatureScript("npc_tipsy_gossip") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {

        if (player->GetQuestStatus(12644) == QUEST_STATUS_INCOMPLETE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TIPSY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->CLOSE_GOSSIP_MENU();
        creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        creature->AI()->SetGUID(player->GetGUID());
        return true;
    }
    struct npc_tipsy_gossipAI : public ScriptedAI
    {
        npc_tipsy_gossipAI(Creature* creature) : ScriptedAI(creature) { }

        uint8 uiStep;
        uint32 uiTimer;
        bool bStarted;
        enum States
        {
            NONE     = 0,
            BANANA   = 1,
            ORANGE   = 2,
            PAPAYA   = 3,
            VALVE    = 4,
            BRAZIER  = 5,
        };
        uint8 nextExpectedClick;
        uint64 uiPlayer;

        void SetGUID(const uint64 &uiGuid, int32 /*iId*/)
        {
            uiPlayer = uiGuid;
            bStarted = true;
            me->MonsterSay("Muy bien, vamos alla. Yo te dire lo que necesitamos y tu me lanzaras. Preparate!", LANG_UNIVERSAL, uiPlayer);
            uiTimer = urand(2000, 4000);
            nextExpectedClick = NONE;
        }
        void FinishedStill()
        {
            if (Player* player = me->GetPlayer(*me, uiPlayer))
                player->AddItem(38688, 1);
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->MonsterSay("Hemos terminado, buen trabajo.", LANG_UNIVERSAL, uiPlayer);
            bStarted = false;
            uiStep = 0;
            nextExpectedClick = NONE;

        }

        void FailedStill()
        {
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            me->MonsterSay("Acabas de estropear la mezcla! Tendremos que volver a empezar.", LANG_UNIVERSAL, uiPlayer);
            bStarted = false;
            uiStep = 0;
            nextExpectedClick = NONE;
        }

        void CorrectClick()
        {
            if (nextExpectedClick != VALVE) uiStep++;
            nextExpectedClick = NONE;
        }

        void DoAction(const int32 actionId)
        {
            if (bStarted)
                switch(actionId)
                {
                    case EVENT_BANANA_CLICK:
                        if(nextExpectedClick == BANANA) CorrectClick();
                        else FailedStill();
                        break;

                    case EVENT_ORANGE_CLICK:
                        if(nextExpectedClick == ORANGE) CorrectClick();
                        else FailedStill();
                        break;

                    case EVENT_PAPAYA_CLICK:
                        if(nextExpectedClick == PAPAYA) CorrectClick();
                        else FailedStill();
                        break;

                    case EVENT_VALVE_CLICK:
                        if(nextExpectedClick == VALVE) CorrectClick();
                        else FailedStill();
                        break;

                    case EVENT_BRAZIER_CLICK:
                        if(nextExpectedClick == BRAZIER) CorrectClick();
                        else FailedStill();
                        break;
                }
        }

        void GenerateNextRandom()
        {
            switch(urand(1,4))
            {
                case 1:
                    me->MonsterSay("Necesitamos platanos, deprisa!", LANG_UNIVERSAL, uiPlayer);
                    nextExpectedClick = BANANA;
                    break;
                case 2:
                    me->MonsterSay("Naranjas, naranjas Rapido!", LANG_UNIVERSAL, uiPlayer);
                    nextExpectedClick = ORANGE;
                    break;
                case 3:
                    me->MonsterSay("Papayas, necesitamos mas papayas.", LANG_UNIVERSAL, uiPlayer);
                    nextExpectedClick = PAPAYA;
                    break;
                case 4:
                    me->MonsterSay("La presion esta subiendo demiasiado! Solucionalo ya!", LANG_UNIVERSAL, uiPlayer);
                    nextExpectedClick = VALVE;
                    break;
            }
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (bStarted)
            {
                if (uiTimer <= uiDiff)
                {
                   if(nextExpectedClick != NONE)
                   {FailedStill(); return;}

                   if(uiStep < 6)
                   {
                       GenerateNextRandom();
                       uiTimer = urand(3000,5000);
                   }
                   else if (uiStep == 6)
                   {
                       nextExpectedClick = BRAZIER;
                       me->MonsterSay("Calientalo y habremos terminado.", LANG_UNIVERSAL, uiPlayer);
                       uiTimer = urand(3000,5000);
                   }
                   else
                       FinishedStill();
                }
                else
                {
                uiTimer -= uiDiff;
                }
            }
        }
    };
};
void AddSC_sholazar_basin()
{
    new npc_injured_rainspeaker_oracle();
    new npc_vekjik();
    new npc_avatar_of_freya();
    new npc_bushwhacker();
    new npc_engineer_helice();
    new npc_adventurous_dwarf();
    new npc_jungle_punch_target();
    new npc_captive_croco_gossip();
    new npc_captive_croco_vehicle();
    new npc_harkek_gossip();
    new go_still_tools();
    new npc_tipsy_gossip();
}
