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
SDName: Shadowfang_Keep
SD%Complete: 75
SDComment: npc_shadowfang_prisoner using escortAI for movement to door. Might need additional code in case being attacked. Add proper texts/say().
SDCategory: Shadowfang Keep
EndScriptData */

/* ContentData
npc_shadowfang_prisoner
EndContentData */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"
#include "shadowfang_keep.h"

/*######
## npc_shadowfang_prisoner
######*/

enum eEnums
{
    SAY_FREE_AS             = -1033000,
    SAY_OPEN_DOOR_AS        = -1033001,
    SAY_POST_DOOR_AS        = -1033002,
    SAY_FREE_AD             = -1033003,
    SAY_OPEN_DOOR_AD        = -1033004,
    SAY_POST1_DOOR_AD       = -1033005,
    SAY_POST2_DOOR_AD       = -1033006,

    SPELL_UNLOCK            = 6421,
    NPC_ASH                 = 3850,

    SPELL_DARK_OFFERING     = 7154
};

#define GOSSIP_ITEM_DOOR        "Thanks, I'll follow you to the door."

class npc_shadowfang_prisoner : public CreatureScript
{
public:
    npc_shadowfang_prisoner() : CreatureScript("npc_shadowfang_prisoner") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_shadowfang_prisonerAI(creature);
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        {
            player->CLOSE_GOSSIP_MENU();

            if (npc_escortAI* pEscortAI = CAST_AI(npc_shadowfang_prisoner::npc_shadowfang_prisonerAI, creature->AI()))
                pEscortAI->Start(false, false);
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        InstanceScript* instance = creature->GetInstanceScript();

        if (instance && instance->GetData(TYPE_FREE_NPC) != DONE && instance->GetData(TYPE_RETHILGORE) == DONE)
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DOOR, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }

    struct npc_shadowfang_prisonerAI : public npc_escortAI
    {
        npc_shadowfang_prisonerAI(Creature* c) : npc_escortAI(c)
        {
            instance = c->GetInstanceScript();
            uiNpcEntry = c->GetEntry();
        }

        InstanceScript* instance;
        uint32 uiNpcEntry;

        void WaypointReached(uint32 uiPoint)
        {
            switch (uiPoint)
            {
                case 0:
                    if (uiNpcEntry == NPC_ASH)
                        DoScriptText(SAY_FREE_AS, me);
                    else
                        DoScriptText(SAY_FREE_AD, me);
                    break;
                case 10:
                    if (uiNpcEntry == NPC_ASH)
                        DoScriptText(SAY_OPEN_DOOR_AS, me);
                    else
                        DoScriptText(SAY_OPEN_DOOR_AD, me);
                    break;
                case 11:
                    if (uiNpcEntry == NPC_ASH)
                        DoCast(me, SPELL_UNLOCK);
                    break;
                case 12:
                    if (uiNpcEntry == NPC_ASH)
                        DoScriptText(SAY_POST_DOOR_AS, me);
                    else
                        DoScriptText(SAY_POST1_DOOR_AD, me);

                    if (instance)
                        instance->SetData(TYPE_FREE_NPC, DONE);
                    break;
                case 13:
                    if (uiNpcEntry != NPC_ASH)
                        DoScriptText(SAY_POST2_DOOR_AD, me);
                    break;
            }
        }

        void Reset() {}
        void EnterCombat(Unit* /*who*/) {}
    };

};

class npc_arugal_voidwalker : public CreatureScript
{
public:
    npc_arugal_voidwalker() : CreatureScript("npc_arugal_voidwalker") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_arugal_voidwalkerAI(creature);
    }

    struct npc_arugal_voidwalkerAI : public ScriptedAI
    {
        npc_arugal_voidwalkerAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        uint32 uiDarkOffering;

        void Reset()
        {
            uiDarkOffering = urand(290, 10);
        }

        void UpdateAI(uint32 const uiDiff)
        {
            if (!UpdateVictim())
                return;

            if (uiDarkOffering <= uiDiff)
            {
                if (Creature* pFriend = me->FindNearestCreature(me->GetEntry(), 25.0f, true))
                {
                    if (pFriend)
                        DoCast(pFriend, SPELL_DARK_OFFERING);
                }
                else
                    DoCast(me, SPELL_DARK_OFFERING);
                uiDarkOffering = urand(4400, 12500);
            } else uiDarkOffering -= uiDiff;

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            if (instance)
                instance->SetData(TYPE_FENRUS, instance->GetData(TYPE_FENRUS) + 1);
        }
    };

};

/*######
## Apothecary trio - Love is in the Air
######*/

enum eSpells
{
    // Any boss
    SPELL_CHAIN_REACTION                        = 68821,

    // Apothecary Hummel
    SPELL_ALLURING_PERFUME                      = 68589,
    SPELL_PERFUME_SPRAY                         = 68607,

    // Apothecary Baxter
    SPELL_IRRESISTIBLE_COLOGNE                  = 68946,
    SPELL_COLOGNE_SPRAY                         = 68948,

    // Apothecary Frye
    SPELL_LINGERING_FUMES                       = 68704,
    SPELL_THROW_PERFUME                         = 68799, // 68798 Need core support
    SPELL_THROW_COLOGNE                         = 68841  // 68614
};

enum eEvents
{
    EVENT_NULL,
    EVENT_CHAIN_REACTION,
    // Apothecary Hummel
    EVENT_SAY_AGGRO_2,
    EVENT_SAY_AGGRO_3,
    EVENT_CALL_BAXTER,
    EVENT_CALL_FRYE,
    EVENT_PERFUME_SPRAY,
    // Apothecary Baxter
    EVENT_COLOGNE_SPRAY,
    // Apothecary Frye
    EVENT_CHANGE_TARGET,
    EVENT_THROW_PERFUME,
    EVENT_THROW_COLOGNE,
    EVENT_LINGERING_FUMES
};

#define SAY_AGGRO_1                 "Did they bother to tell you who I am and why I am doing this?"
#define SAY_AGGRO_2                 "...or are they just using you like they do everybody else?"
#define SAY_AGGRO_3                 "But what does it matter. It is time for this to end."
#define SAY_BAXTER                  "Baxter! Get in there and help! NOW!"
#define SAY_FRYE                    "It is time, Frye! Attack!"
#define SAY_SUMMON                  "Apothecaries! Give your life for the Crown!"
#define SAY_DEATH                   "...please don't think less of me."

#define ACTION_START                1

class npc_apothecary_hummel : public CreatureScript
{
public:
    npc_apothecary_hummel() : CreatureScript("npc_apothecary_hummel") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_apothecary_hummelAI (creature);
    }

    struct npc_apothecary_hummelAI : public ScriptedAI
    {
        npc_apothecary_hummelAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = c->GetInstanceScript();
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        EventMap events;
        InstanceScript* pInstance;

        void Reset()
        {
            events.Reset();
            me->RemoveAllAuras();
            me->ResetLootMode();
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->AddAura(SPELL_ALLURING_PERFUME, me);

            // Respawn
            if (Creature* Baxter = me->GetCreature(*me, pInstance->GetData64(DATA_BAXTER)))
                if (Baxter->isDead())
                {
                    Baxter->Respawn(true);
                    Baxter->GetMotionMaster()->MoveTargetedHome();
                }
            if (Creature* Frye = me->GetCreature(*me, pInstance->GetData64(DATA_FRYE)))
                if (Frye->isDead())
                {
                    Frye->Respawn(true);
                    Frye->GetMotionMaster()->MoveTargetedHome();
                }
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoZoneInCombat();
            me->MonsterSay(SAY_AGGRO_1, 0, 0);
            events.ScheduleEvent(EVENT_SAY_AGGRO_2, 5000);
            events.ScheduleEvent(EVENT_SAY_AGGRO_3, 10000);
            events.ScheduleEvent(EVENT_CALL_BAXTER, 20000);
            events.ScheduleEvent(EVENT_CALL_FRYE, 30000);
            events.ScheduleEvent(EVENT_PERFUME_SPRAY, 15000);
            events.ScheduleEvent(EVENT_CHAIN_REACTION, 30000);

            if (Creature* Baxter = me->GetCreature(*me, pInstance->GetData64(DATA_BAXTER)))
            {
                Baxter->AI()->DoZoneInCombat();
                Baxter->GetMotionMaster()->MovePoint(0, -224.01f, 2207.83f, 79.76f);
            }

            if (Creature* Frye = me->GetCreature(*me, pInstance->GetData64(DATA_FRYE)))
            {
                Frye->AI()->DoZoneInCombat();
                Frye->GetMotionMaster()->MovePoint(0, -197.22f, 2198.52f, 79.76f);
            }
        }

        void JustDied(Unit* /*Killer*/)
        {
            me->MonsterSay(SAY_DEATH, 0, 0);

            if (Creature* Baxter = me->GetCreature(*me, pInstance->GetData64(DATA_BAXTER)))
                if (Baxter->isAlive())
                    me->SetLootRecipient(NULL);

            if (Creature* Frye = me->GetCreature(*me, pInstance->GetData64(DATA_FRYE)))
                if (Frye->isAlive())
                    me->SetLootRecipient(NULL);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_SAY_AGGRO_2:
                        me->MonsterSay(SAY_AGGRO_2, 0, 0);
                        events.CancelEvent(EVENT_SAY_AGGRO_2);
                        break;
                    case EVENT_SAY_AGGRO_3:
                        me->MonsterSay(SAY_AGGRO_3, 0, 0);
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        events.CancelEvent(EVENT_SAY_AGGRO_3);
                        break;
                    case EVENT_CALL_BAXTER:
                        me->MonsterSay(SAY_BAXTER, 0, 0);
                        if (Creature* Baxter = me->GetCreature(*me, pInstance->GetData64(DATA_BAXTER)))
                            Baxter->AI()->DoAction(ACTION_START);
                        events.CancelEvent(EVENT_CALL_BAXTER);
                        break;
                    case EVENT_CALL_FRYE:
                        me->MonsterSay(SAY_FRYE, 0, 0);
                        if (Creature* Frye = me->GetCreature(*me, pInstance->GetData64(DATA_FRYE)))
                            Frye->AI()->DoAction(ACTION_START);
                        events.CancelEvent(EVENT_CALL_FRYE);
                        break;
                    case EVENT_PERFUME_SPRAY:
                        DoCastVictim(SPELL_PERFUME_SPRAY);
                        events.RescheduleEvent(EVENT_PERFUME_SPRAY, urand(4000, 6000));
                        break;
                    case EVENT_CHAIN_REACTION:
                        DoCast(SPELL_CHAIN_REACTION);
                        events.RescheduleEvent(EVENT_PERFUME_SPRAY, 6000);
                        events.RescheduleEvent(EVENT_CHAIN_REACTION, 40000);
                        break;
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };

};

class npc_apothecary_baxter : public CreatureScript
{
public:
    npc_apothecary_baxter() : CreatureScript("npc_apothecary_baxter") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_apothecary_baxterAI (creature);
    }

    struct npc_apothecary_baxterAI : public ScriptedAI
    {
        npc_apothecary_baxterAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = c->GetInstanceScript();
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        EventMap events;
        InstanceScript* pInstance;

        void Reset()
        {
            events.Reset();
            me->RemoveAllAuras();
            me->ResetLootMode();
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->AddAura(SPELL_IRRESISTIBLE_COLOGNE, me);

            // Respawn
            if (Creature* Hummel = me->GetCreature(*me, pInstance->GetData64(DATA_HUMMEL)))
                if (Hummel->isDead())
                {
                    Hummel->Respawn(true);
                    Hummel->GetMotionMaster()->MoveTargetedHome();
                }
            if (Creature* Frye = me->GetCreature(*me, pInstance->GetData64(DATA_FRYE)))
                if (Frye->isDead())
                {
                    Frye->Respawn(true);
                    Frye->GetMotionMaster()->MoveTargetedHome();
                }
        }

        void JustDied(Unit* /*Killer*/)
        {
            if (Creature* Hummel = me->GetCreature(*me, pInstance->GetData64(DATA_HUMMEL)))
                if (Hummel->isAlive())
                    me->SetLootRecipient(NULL);

            if (Creature* Frye = me->GetCreature(*me, pInstance->GetData64(DATA_FRYE)))
                if (Frye->isAlive())
                    me->SetLootRecipient(NULL);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_COLOGNE_SPRAY:
                        DoCastVictim(SPELL_COLOGNE_SPRAY);
                        events.RescheduleEvent(EVENT_COLOGNE_SPRAY, urand(4000, 6000));
                        break;
                    case EVENT_CHAIN_REACTION:
                        DoCast(SPELL_CHAIN_REACTION);
                        events.RescheduleEvent(EVENT_COLOGNE_SPRAY, 6000);
                        events.RescheduleEvent(EVENT_CHAIN_REACTION, 40000);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void DoAction(const int32 action)
        {
            switch (action)
            {
                case ACTION_START:
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    DoZoneInCombat();
                    events.ScheduleEvent(EVENT_COLOGNE_SPRAY, 4000);
                    events.ScheduleEvent(EVENT_CHAIN_REACTION, 20000);
                    break;
            }
        }
    };

};

class npc_apothecary_frye : public CreatureScript
{
public:
    npc_apothecary_frye() : CreatureScript("npc_apothecary_frye") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_apothecary_fryeAI (creature);
    }

    struct npc_apothecary_fryeAI : public ScriptedAI
    {
        npc_apothecary_fryeAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = c->GetInstanceScript();
        }

        EventMap events;
        InstanceScript* pInstance;

        void Reset()
        {
            events.Reset();
            me->RemoveAllAuras();
            me->ResetLootMode();
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            // Respawn
            if (Creature* Hummel = me->GetCreature(*me, pInstance->GetData64(DATA_HUMMEL)))
                if (Hummel->isDead())
                {
                    Hummel->Respawn(true);
                    Hummel->GetMotionMaster()->MoveTargetedHome();
                }
            if (Creature* Baxter = me->GetCreature(*me, pInstance->GetData64(DATA_BAXTER)))
                if (Baxter->isDead())
                {
                    Baxter->Respawn(true);
                    Baxter->GetMotionMaster()->MoveTargetedHome();
                }
        }

        void JustDied(Unit* /*Killer*/)
        {
            if (Creature* Hummel = me->GetCreature(*me, pInstance->GetData64(DATA_HUMMEL)))
                if (Hummel->isAlive())
                    me->SetLootRecipient(NULL);

            if (Creature* Baxter = me->GetCreature(*me, pInstance->GetData64(DATA_BAXTER)))
                if (Baxter->isAlive())
                    me->SetLootRecipient(NULL);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch(eventId)
                {
                    case EVENT_CHANGE_TARGET:
                        if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                            me->AI()->AttackStart(target);
                        events.RescheduleEvent(EVENT_CHANGE_TARGET, 10000);
                        break;
                    case EVENT_THROW_PERFUME:
                        if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                            DoCast(target, SPELL_THROW_PERFUME);
                        events.RescheduleEvent(EVENT_THROW_PERFUME, 35000);
                        break;
                    case EVENT_THROW_COLOGNE:
                        if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                            DoCast(target, SPELL_THROW_COLOGNE);
                        events.RescheduleEvent(EVENT_THROW_COLOGNE, 35000);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }

        void DoAction(const int32 action)
        {
            switch (action)
            {
                case ACTION_START:
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    events.ScheduleEvent(EVENT_CHANGE_TARGET, 0);
                    events.ScheduleEvent(EVENT_THROW_PERFUME, 5000);
                    events.ScheduleEvent(EVENT_THROW_COLOGNE, 15000);
                    break;
            }
        }
    };

};

void AddSC_shadowfang_keep()
{
    new npc_shadowfang_prisoner();
    new npc_arugal_voidwalker();
    new npc_apothecary_hummel();
    new npc_apothecary_baxter();
    new npc_apothecary_frye();
}
