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

/*##########################
# npc_rocket_warhead (27593)
###########################*/

class npc_rocket_warhead : public CreatureScript
{
public:
    npc_rocket_warhead() : CreatureScript("npc_rocket_warhead") { }

    struct npc_rocket_warheadAI : public ScriptedAI
    {
        npc_rocket_warheadAI(Creature* creature) : ScriptedAI(creature) { }

        bool occupied;

        void Reset()
        {
            occupied = false;
            me->SetHover(true);
        }

        void UpdateAI(const uint32 /*diff*/)
        {
            if(!occupied)
                return;

            Unit* player = me->GetVehicleKit()->GetPassenger(0);

            if(!player)
            {
                me->DisappearAndDie();
                return;
            }

            if(player && !me->HasAura(49181, 0)) // Time-Out and no boat reached
            {
                player->ExitVehicle();
                DoCast(71945);            // Visual
                me->DespawnOrUnsummon(1500);
                return;
            }

            Unit* pBombTarget;
            switch(player->ToPlayer()->GetTeam())
            {
                case ALLIANCE: pBombTarget = me->FindNearestCreature(27702, 8.0f); break;
                case HORDE: pBombTarget = me->FindNearestCreature(27688, 8.0f); break;
            }

            if(player && pBombTarget)
            {
                player->ToPlayer()->KilledMonsterCredit(pBombTarget->GetEntry(), 0);
                player->ExitVehicle();
                DoCast(71945);            // Visual
                me->DespawnOrUnsummon(1500);
            }
        }

        void PassengerBoarded(Unit* /*passenger*/, int8 /*seatId*/, bool /*apply*/)
        {
            me->AddAura(49181, me);
            occupied = true;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_rocket_warheadAI(creature);
    }
};

/*###########################
# npc_father_kamaros (31279)
###########################*/

enum NotDeadYet
{
    QUEST_NOT_DEAD_YET_A = 13221,
    QUEST_NOT_DEAD_YET_H = 13229,
    NPC_NOT_DEAD_YET_TRIG = 97002,
    SPELL_PW_FORTITUDE = 23947,
    SPELL_PW_SHIELD = 20697
};

const Position KamarosWp[54] =
{
    {6718.48f, 3439.88f, 682.24f, 0.00f},
    {6723.54f, 3433.79f, 682.20f, 0.00f},
    {6734.04f, 3436.02f, 682.03f, 0.00f},
    {6737.66f, 3439.00f, 680.97f, 0.00f},
    {6742.07f, 3442.76f, 679.93f, 0.00f},
    {6745.65f, 3446.09f, 678.85f, 0.00f},
    {6750.47f, 3450.57f, 677.51f, 0.00f},
    {6755.94f, 3455.28f, 675.78f, 0.00f},
    {6759.58f, 3458.61f, 674.71f, 0.00f},
    {6765.04f, 3463.30f, 673.37f, 0.00f},
    {6769.22f, 3467.40f, 673.00f, 0.00f},
    {6771.95f, 3471.55f, 673.01f, 0.00f},
    {6777.21f, 3477.04f, 672.99f, 0.00f},
    {6782.91f, 3482.89f, 674.34f, 0.00f},
    {6779.54f, 3479.36f, 673.32f, 0.00f},
    {6773.88f, 3473.81f, 673.03f, 0.00f},
    {6786.32f, 3484.85f, 675.62f, 0.00f},
    {6792.51f, 3484.66f, 677.20f, 0.00f},
    {6797.39f, 3484.49f, 678.76f, 0.00f},
    {6800.64f, 3484.44f, 680.03f, 0.00f},
    {6805.98f, 3484.26f, 682.17f, 0.00f},
    {6810.80f, 3484.14f, 683.97f, 0.00f},
    {6816.15f, 3483.58f, 686.18f, 0.00f},
    {6822.91f, 3483.01f, 688.17f, 0.00f},
    {6829.09f, 3481.91f, 689.49f, 0.00f},
    {6836.49f, 3480.96f, 690.69f, 0.00f},
    {6844.57f, 3480.25f, 691.89f, 0.00f},
    {6853.38f, 3479.60f, 692.98f, 0.00f},
    {6859.95f, 3479.59f, 693.60f, 0.00f},
    {6867.60f, 3479.74f, 694.21f, 0.00f},
    {6875.25f, 3479.95f, 694.86f, 0.00f},
    {6882.69f, 3480.14f, 695.82f, 0.00f},
    {6889.85f, 3479.97f, 697.36f, 0.00f},
    {6896.19f, 3479.88f, 698.54f, 0.00f},
    {6902.49f, 3479.66f, 699.74f, 0.00f},
    {6908.08f, 3479.89f, 700.81f, 0.00f},
    {6913.89f, 3480.32f, 701.86f, 0.00f},
    {6920.57f, 3482.18f, 703.10f, 0.00f},
    {6925.61f, 3481.11f, 704.38f, 0.00f},
    {6930.92f, 3480.19f, 705.91f, 0.00f},
    {6936.04f, 3479.73f, 707.06f, 0.00f},
    {6942.06f, 3479.21f, 708.06f, 0.00f},
    {6947.22f, 3477.91f, 709.01f, 0.00f},
    {6953.44f, 3477.53f, 709.63f, 0.00f},
    {6959.23f, 3477.21f, 710.30f, 0.00f},
    {6967.35f, 3474.84f, 711.05f, 0.00f},
    {6980.54f, 3470.97f, 710.86f, 0.00f},
    {6985.85f, 3469.15f, 708.75f, 0.00f},
    {6991.36f, 3467.22f, 705.94f, 0.00f},
    {6997.30f, 3465.15f, 702.91f, 0.00f},
    {7004.14f, 3462.46f, 699.36f, 0.00f},
    {7009.42f, 3460.61f, 696.67f, 0.00f},
    {7018.43f, 3455.71f, 696.67f, 0.00f},
    {7029.21f, 3447.94f, 696.17f, 0.00f}
};

class npc_father_kamaros : public CreatureScript
{
public:
    npc_father_kamaros() : CreatureScript("npc_father_kamaros") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_NOT_DEAD_YET_A || quest->GetQuestId() == QUEST_NOT_DEAD_YET_H)
        {
            creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            creature->AI()->SetGUID(player->GetGUID());
            creature->CastSpell(player,SPELL_PW_FORTITUDE,true);
            player->CastSpell(player,SPELL_PW_SHIELD,true);
        }
        return true;
    }

    struct npc_father_kamarosAI : public ScriptedAI
    {
        npc_father_kamarosAI(Creature* creature) : ScriptedAI(creature) { }

        uint8 count;
        bool wp_reached;
        bool movementStarted;
        bool finished;
        uint64 uiPlayer;
        Player* player;

        void SetGUID(const uint64 &uiGuid, int32 /*iId*/)
        {
            movementStarted = true;
            me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_OOC_NOT_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
            me->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);
            me->GetMotionMaster()->MovePoint(0, KamarosWp[0]);
            uiPlayer = uiGuid;
        }

        void Reset()
        {
            count = 0;
            wp_reached = false;
            movementStarted = false;
            finished = false;
            uiPlayer = 0;
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE || id != count)
                return;

            if (movementStarted && id < 54)
            {
                ++count;
                wp_reached = true;
            }
        }

        void UpdateAI(const uint32 /*diff*/)
        {
            if (movementStarted)
            {
                player = me->GetPlayer(*me, uiPlayer);

                if (!player || !player->isAlive() || me->GetDistance(player) > 30.0f)
                    me->DisappearAndDie();

                if (player->isInCombat() && player->GetUInt64Value(UNIT_FIELD_TARGET))
                    me->Attack(me->GetUnit(*me, player->GetUInt64Value(UNIT_FIELD_TARGET)), true);
            }

            if (wp_reached && !finished)
            {
                wp_reached = false;
                me->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);
                me->GetMotionMaster()->MovePoint(count, KamarosWp[count]);
            }
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (who->GetEntry() == NPC_NOT_DEAD_YET_TRIG && me->IsWithinDistInMap(who,10.0f,true))
            {
                if (Player* player = me->GetPlayer(*me, uiPlayer))
                {
                    switch (player->GetTeam())
                    {
                        case ALLIANCE: player->GroupEventHappens(QUEST_NOT_DEAD_YET_A, me); break;
                        case HORDE: player->GroupEventHappens(QUEST_NOT_DEAD_YET_H, me); break;
                    }
                    movementStarted = false;
                    finished = true;
                    me->DespawnOrUnsummon(10000);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_father_kamarosAI(creature);
    }
};

/*#####
# npc_spring_rabbit
#####*/

enum rabbitSpells
{
    SPELL_SPRING_FLING = 61875,
    SPELL_SPRING_RABBIT_JUMP = 61724,
    SPELL_SPRING_RABBIT_WANDER = 61726,
    SPELL_SUMMON_BABY_BUNNY = 61727,
    SPELL_SPRING_RABBIT_IN_LOVE = 61728,
    NPC_SPRING_RABBIT = 32791
};

class npc_spring_rabbit : public CreatureScript
{
public:
    npc_spring_rabbit() : CreatureScript("npc_spring_rabbit") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_spring_rabbitAI(creature);
    }

    struct npc_spring_rabbitAI : public ScriptedAI
    {
        npc_spring_rabbitAI(Creature* c) : ScriptedAI(c) { }

        bool inLove;
        uint32 jumpTimer;
        uint32 bunnyTimer;
        uint32 searchTimer;
        uint64 rabbitGUID;

        void Reset()
        {
            inLove = false;
            rabbitGUID = 0;
            jumpTimer = urand(5000, 10000);
            bunnyTimer = urand(10000, 20000);
            searchTimer = urand(5000, 10000);
            if (Unit* owner = me->GetOwner())
                me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
        }

        void EnterCombat(Unit * /*who*/) { }

        void DoAction(const int32 /*param*/)
        {
            inLove = true;
            if (Unit* owner = me->GetOwner())
                owner->CastSpell(owner, SPELL_SPRING_FLING, true);
        }

        void UpdateAI(const uint32 diff)
        {
            if (inLove)
            {
                if (jumpTimer <= diff)
                {
                    if (Unit* rabbit = Unit::GetUnit(*me, rabbitGUID))
                        DoCast(rabbit, SPELL_SPRING_RABBIT_JUMP);
                    jumpTimer = urand(5000, 10000);
                }else jumpTimer -= diff;

                if (bunnyTimer <= diff)
                {
                    DoCast(SPELL_SUMMON_BABY_BUNNY);
                    bunnyTimer = urand(20000, 40000);
                }else bunnyTimer -= diff;
            }
            else
            {
                if (searchTimer <= diff)
                {
                    if (Creature* rabbit = me->FindNearestCreature(NPC_SPRING_RABBIT, 10.0f))
                    {
                        if (rabbit == me || rabbit->HasAura(SPELL_SPRING_RABBIT_IN_LOVE))
                            return;

                        me->AddAura(SPELL_SPRING_RABBIT_IN_LOVE, me);
                        DoAction(1);
                        rabbit->AddAura(SPELL_SPRING_RABBIT_IN_LOVE, rabbit);
                        rabbit->AI()->DoAction(1);
                        rabbit->CastSpell(rabbit, SPELL_SPRING_RABBIT_JUMP, true);
                        rabbitGUID = rabbit->GetGUID();
                    }
                    searchTimer = urand(5000, 10000);
                }else searchTimer -= diff;
            }
        }
    };
};

enum ghoulSpells
{
    SPELL_SHINING_LIGTH = 43202,
    SPELL_SHINING_LIGTH_HIT_VISUAL = 46400,
};

class npc_decomposing_ghoul : public CreatureScript
{
public:
    npc_decomposing_ghoul() : CreatureScript("npc_decomposing_ghoul") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_decomposing_ghoulAI(creature);
    }

    struct npc_decomposing_ghoulAI : public ScriptedAI
    {
        npc_decomposing_ghoulAI(Creature* c) : ScriptedAI(c) { }


        void EnterCombat(Unit * who)
        {
            if (who->HasAura(SPELL_SHINING_LIGTH))
            {
                DoCast(SPELL_SHINING_LIGTH_HIT_VISUAL);
                EnterEvadeMode();
            }
        }
    };
};

enum irulonData
{
    QUEST_GUIDED_BY_HONOR = 11289,
    NPC_TIRION            = 24232,
    NPC_CLERIC            = 24233,
    ITEM_ASHBRINGER       = 13262,

    SAY_TIRION_1          = -1002000,
    EMOTE_TIRION_1        = -1002001,
    SAY_IRULON_1          = -1002002,
    SAY_TIRION_2          = -1002003,
    SAY_TIRION_3          = -1002004,
    SAY_IRULON_2          = -1002005,
    EMOTE_TIRION_2        = -1002006,
    SAY_TIRION_4          = -1002007,
    SAY_TIRION_5          = -1002008,
    EMOTE_TIRION_3        = -1002009,
    YELL_TIRION           = -1002010,

    ACTION_START,
};

enum iluronEvents
{
    EVENT_NONE,
    EVENT_00,
    EVENT_01,
    EVENT_02,
    EVENT_03,
    EVENT_04,
    EVENT_05,
    EVENT_06,
    EVENT_07,
    EVENT_08,
    EVENT_09,
    EVENT_10,
};

class npc_irulon_trueblade : public CreatureScript
{
public:
    npc_irulon_trueblade() : CreatureScript("npc_irulon_trueblade") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_irulon_truebladeAI(creature);
    }

    bool OnGossipHello(Player* player, Creature* me)
    {
        if (me->isQuestGiver())
            player->PrepareQuestMenu(me->GetGUID());

        player->GroupEventHappens(QUEST_GUIDED_BY_HONOR, me);

        player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, me->GetGUID());
        return true;
    }
    bool OnQuestReward(Player* /*player*/, Creature* me, Quest const* quest, uint32 /*item*/)
    {
        if (quest->GetQuestId() == QUEST_GUIDED_BY_HONOR)
            me->AI()->DoAction(ACTION_START);
        return true;
    }

    struct npc_irulon_truebladeAI : public ScriptedAI
    {
        npc_irulon_truebladeAI(Creature* c) : ScriptedAI(c) { }

        EventMap events;
        uint64 uiTirion;

        void Reset()
        {
            uiTirion = 0;
            events.Reset();
        }

        void DoAction(const int32 actionId)
        {
            switch(actionId)
            {
                case ACTION_START:
                    uiTirion = 0;
                    events.ScheduleEvent(EVENT_00, 1500);
                    break;
            }
        }

        void UpdateAI(const uint32 diff)
        {
            events.Update(diff);
            switch(events.ExecuteEvent())
            {
                case EVENT_00:
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

                    if(Creature* pTirion = me->FindNearestCreature(NPC_CLERIC, 7.0f))
                    {
                        uiTirion = pTirion->GetGUID();
                        DoScriptText(SAY_TIRION_1, pTirion);
                        pTirion->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                        pTirion->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STAND);
                        pTirion->GetMotionMaster()->MovePoint(0, me->GetPositionX() + 3.0f, me->GetPositionY() + 3.0f, me->GetPositionZ() + 0.5f);
                    }
                    events.ScheduleEvent(EVENT_01, 2000);
                    break;
                case EVENT_01:
                    if(Creature* pTirion = me->GetCreature(*me, uiTirion))
                    {
                        DoScriptText(EMOTE_TIRION_1, pTirion);
                        pTirion->UpdateEntry(NPC_TIRION);
                        pTirion->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, 0);
                    }
                    events.ScheduleEvent(EVENT_02, 1000);
                    break;
                case EVENT_02:
                    DoScriptText(SAY_IRULON_1, me);
                    events.ScheduleEvent(EVENT_03, 2000);
                    break;
                case EVENT_03:
                    if(Creature* pTirion = me->GetCreature(*me, uiTirion))
                        DoScriptText(SAY_TIRION_2, pTirion);
                    events.ScheduleEvent(EVENT_04, 3000);
                    break;
                case EVENT_04:
                    if(Creature* pTirion = me->GetCreature(*me, uiTirion))
                        DoScriptText(SAY_TIRION_3, pTirion);
                    events.ScheduleEvent(EVENT_05,1000);
                    break;
                case EVENT_05:
                    DoScriptText(SAY_IRULON_2, me);
                    events.ScheduleEvent(EVENT_06, 2500);
                    break;
                case EVENT_06:
                    if(Creature* pTirion = me->GetCreature(*me, uiTirion))
                        DoScriptText(EMOTE_TIRION_2, pTirion);
                    events.ScheduleEvent(EVENT_07,1000);
                    break;
                case EVENT_07:
                    if(Creature* pTirion = me->GetCreature(*me, uiTirion))
                        DoScriptText(SAY_TIRION_4, pTirion);
                    events.ScheduleEvent(EVENT_08,1500);
                    break;
                case EVENT_08:
                    if(Creature* pTirion = me->GetCreature(*me, uiTirion))
                        DoScriptText(SAY_TIRION_5, pTirion);
                    events.ScheduleEvent(EVENT_09,1500);
                    break;
                case EVENT_09:
                    if(Creature* pTirion = me->GetCreature(*me, uiTirion))
                    {
                        DoScriptText(EMOTE_TIRION_3, pTirion);
                        pTirion->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, ITEM_ASHBRINGER);
                    }
                    events.ScheduleEvent(EVENT_10,2000);
                    break;
                case EVENT_10:
                    if(Creature* pTirion = me->GetCreature(*me, uiTirion))
                    {
                        DoScriptText(YELL_TIRION, pTirion);
                        pTirion->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, 0);
                        pTirion->DespawnOrUnsummon(5000);
                    }
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    break;
            }
        }
    };
};

enum q11429Data
{
    QUEST_DROP_IT_ROCK_IT = 11429,
    NPC_WINTERSKORN_DEFENDER = 24015,
};

class npc_banner_q11429 : public CreatureScript
{
public:
    npc_banner_q11429() : CreatureScript("npc_banner_q11429") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_banner_q11429AI(creature);
    }

    struct npc_banner_q11429AI : public ScriptedAI
    {
        npc_banner_q11429AI(Creature* c) : ScriptedAI(c) { }

        uint32 uiWaveTimer;
        uint8 killCounter;

        void Reset()
        {
            killCounter = 0;
            uiWaveTimer = 2000;
            me->SetReactState(REACT_PASSIVE);
            me->GetMotionMaster()->MoveIdle();
        }

        void JustDied(Unit* /*killer*/)
        {
            if (Player* player = me->GetOwner()->ToPlayer())
                player->FailQuest(QUEST_DROP_IT_ROCK_IT);
        }

        void UpdateAI(const uint32 diff)
        {
            if(uiWaveTimer < diff)
            {
                if(Creature* pVrykul = me->SummonCreature(NPC_WINTERSKORN_DEFENDER, (1476.85f + rand()%20), (-5327.56f + rand()%20), (194.8f  + rand()%2), 0.0f, TEMPSUMMON_CORPSE_DESPAWN))
                {
                    pVrykul->AI()->AttackStart(me);
                    pVrykul->GetMotionMaster()->Clear();
                    pVrykul->GetMotionMaster()->MoveChase(me);
                }
                uiWaveTimer = urand(8000, 16000);
            }
            else
                uiWaveTimer -= diff;
        }

        void SummonedCreatureDespawn(Creature* summon)
        {
            if (summon->GetEntry() == NPC_WINTERSKORN_DEFENDER)
                killCounter++;

            if(killCounter >= 3)
            {
                if (Player* player = me->GetOwner()->ToPlayer())
                    player->GroupEventHappens(QUEST_DROP_IT_ROCK_IT, me);

                me->DespawnOrUnsummon(2000);
            }
        }
    };
};

enum ancientSkullPileData
{
    ITEM_TIMELOST_OFFERING = 32720,
    NPC_TEROKK             = 21838,
};

class go_ancient_skull_pile : public GameObjectScript
{
    public:
        go_ancient_skull_pile() : GameObjectScript("go_ancient_skull_pile") { }

        bool OnGossipHello(Player* player, GameObject* go)
        {
            if (player->HasItemCount(ITEM_TIMELOST_OFFERING, 1))
                player->ADD_GOSSIP_ITEM( 9, "Invocar a Terokk", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

            player->SEND_GOSSIP_MENU(player->GetGossipTextId(go), go->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, GameObject* go, uint32 /*uiSender*/, uint32 uiAction)
        {
            if(uiAction = GOSSIP_ACTION_INFO_DEF+1)
            {
                if(Creature* pTerokk = player->SummonCreature(NPC_TEROKK, go->GetPositionX() + 4.0f, go->GetPositionY() + 2.0f, go->GetPositionZ(), go->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000))
                {
                    pTerokk->AI()->AttackStart(player);
                    pTerokk->GetMotionMaster()->Clear();
                    pTerokk->GetMotionMaster()->MoveChase(player);
                    player->DestroyItemCount(ITEM_TIMELOST_OFFERING, 1, true);
                }
            }
            player->CLOSE_GOSSIP_MENU();
            return true;
        }
};

enum ymironData
{
    QUEST_ECHO_YMIRON     = 11343,
    NPC_ANCIENT_VRYKUL_M  = 24314,
    NPC_ANCIENT_VRYKUL_F  = 24315,
    NPC_LICHKING_HF       = 24248,
    NPC_VALKYR            = 24327,

    SAY_VRYKUL_1          = -1002011, // Male
    EMOTE_VRYKUL_1        = -1002012, // Male
    EMOTE_VRYKUL_2        = -1002013, // Female
    SAY_VRYKUL_2          = -1002014, // Male
    SAY_VRYKUL_3          = -1002015, // Female
    SAY_VRYKUL_4          = -1002016, // Male
    SAY_VRYKUL_5          = -1002017, // Female

    EMOTE_LK_1            = -1002018,
    EMOTE_LK_2            = -1002019,
    SAY_LK_1              = -1002020,
    SAY_LK_2              = -1002021, //Val'kyr
    SAY_LK_3              = -1002022,
    SAY_LK_4              = -1002023,
    SAY_LK_5              = -1002024,
    SAY_LK_6              = -1002025,

    SPELL_ECHO_YMIRON     = 42786,
    SPELL_MAGNETIC_PULL   = 29661,
    SPELL_LK_GRASP        = 43489,
    SPELL_LK_WRATH        = 43488,
};

class npc_ancient_vrykul : public CreatureScript
{
public:
    npc_ancient_vrykul() : CreatureScript("npc_ancient_vrykul") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ancient_vrykulAI(creature);
    }
    struct npc_ancient_vrykulAI : public ScriptedAI
    {
        npc_ancient_vrykulAI(Creature* c) : ScriptedAI(c) { }

        EventMap events;
        Creature* pMale;
        uint64 uiPlayer;
        bool active;

        void Reset()
        {
            uiPlayer = 0;
            active = false;
            events.Reset();

            // Set both passive
            me->SetReactState(REACT_PASSIVE);

            if(Creature* male = me->FindNearestCreature(NPC_ANCIENT_VRYKUL_M, 5.0f))
            {
                male->SetReactState(REACT_PASSIVE);
                pMale = male;
            }
        }

        void SetGUID(const uint64 &uiGuid, int32 /*iId*/)
        {
            if (active)
                return;

            uiPlayer = uiGuid;
            events.ScheduleEvent(1, 2000);
            active = true;
        }

        void UpdateAI(const uint32 diff)
        {
            events.Update(diff);
            switch(events.ExecuteEvent())
            {
                case 1:
                    DoScriptText(SAY_VRYKUL_1, pMale);
                    events.ScheduleEvent(2, 2000);
                    break;
                case 2:
                    DoScriptText(EMOTE_VRYKUL_1, pMale);
                    events.ScheduleEvent(3, 1000);
                    break;
                case 3:
                    DoScriptText(EMOTE_VRYKUL_2, me);
                    events.ScheduleEvent(4, 2000);
                    break;
                case 4:
                    DoScriptText(SAY_VRYKUL_2, pMale);
                    events.ScheduleEvent(5, 3000);
                    break;
                case 5:
                    DoScriptText(SAY_VRYKUL_3, me);
                    events.ScheduleEvent(6,1000);
                    break;
                case 6:
                    DoScriptText(SAY_VRYKUL_4, pMale);
                    events.ScheduleEvent(7, 2500);
                    break;
                case 7:
                    DoScriptText(SAY_VRYKUL_5, me);
                    events.ScheduleEvent(8, 1000);
                    break;
                case 8:
                    if(Player* player = me->GetPlayer(*me, uiPlayer))
                        player->GroupEventHappens(QUEST_ECHO_YMIRON, me);
                    // Set long timer for reset, preventes restarting the event
                    events.ScheduleEvent(9,20000);
                    break;
                case 9:
                    Reset();
                    break;
            }
        }
    };
};

class at_ymiron_house : public AreaTriggerScript
{
    public:
        at_ymiron_house() : AreaTriggerScript("at_ymiron_house") {}

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
        {
            if(player->HasAura(SPELL_ECHO_YMIRON))
            {
                if(Creature * pVrykul = player->FindNearestCreature(NPC_ANCIENT_VRYKUL_F, 10.0f))
                    pVrykul->AI()->SetGUID(player->GetGUID());
            }
            return true;
        }
};

class npc_lich_king_hfjord : public CreatureScript
{
public:
    npc_lich_king_hfjord() : CreatureScript("npc_lich_king_hfjord") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lich_king_hfjordAI(creature);
    }
    struct npc_lich_king_hfjordAI : public ScriptedAI
    {
        npc_lich_king_hfjordAI(Creature* c) : ScriptedAI(c) { }

        EventMap events;
        Player* player;
        bool active;

        void Reset()
        {
            player = NULL;
            active = false;
            events.Reset();

            me->SetReactState(REACT_PASSIVE);
            me->SetOrientation(3.29914f);
        }


        void UpdateAI(const uint32 diff)
        {
            if (!active)
            {
                if(Unit *pSelect = me->SelectNearestTarget(20.0f))
                {
                    if (pSelect->GetTypeId() == TYPEID_PLAYER)
                    {
                        player = pSelect->ToPlayer();
                        DoScriptText(EMOTE_LK_1, me);
                        me->CastSpell(player, SPELL_MAGNETIC_PULL, true);
                        me->CastSpell(player, SPELL_LK_GRASP, true);
                        active = true;
                        events.ScheduleEvent(1, 2000);
                     }
                }
            }

            events.Update(diff);
            switch(events.ExecuteEvent())
            {
                case 1:
                    DoScriptText(EMOTE_LK_2, me);
                    events.ScheduleEvent(2, 1000);
                    break;
                case 2:
                    DoScriptText(SAY_LK_1, me);
                    events.ScheduleEvent(3, 2500);
                    break;
                case 3:
                    if (Creature* pValkyr = me->FindNearestCreature(NPC_VALKYR, 5.0f))
                        DoScriptText(SAY_LK_2, pValkyr);
                    events.ScheduleEvent(4, 3000);
                    break;
                case 4:
                    DoScriptText(SAY_LK_3, me);
                    events.ScheduleEvent(5, 300);
                    break;
                case 5:
                    DoScriptText(SAY_LK_4, me);
                    events.ScheduleEvent(6,5500);
                    break;
                case 6:
                    DoScriptText(SAY_LK_5, me);
                    events.ScheduleEvent(7, 5500);
                    break;
                case 7:
                    DoScriptText(SAY_LK_6, me);
                    events.ScheduleEvent(8, 3000);
                    break;
                case 8:
                    if(player)
                        me->CastSpell(player, SPELL_LK_WRATH, true);
                    events.ScheduleEvent(9, 500);
                case 9:
                    if(player)
                        me->Kill(player);
                    // Set long timer for reset, preventes restarting the event
                    events.ScheduleEvent(10,20000);
                    break;
                case 10:
                    Reset();
                    break;
            }
        }
    };
};

enum ironRuneConstructData
{
    QUEST_IRON_RUNE_CONST_JUMP  = 11485,
    QUEST_IRON_RUNE_CONST_DATA  = 11489,
    QUEST_IRON_RUNE_CONST_BLUFF = 11491,

    NPC_IRON_RUNE_CONST_JUMP    = 24823,
    NPC_IRON_RUNE_CONST_DATA    = 24821,
    NPC_IRON_RUNE_CONST_BLUFF   = 24825,

    SPELL_BLUFF                 = 44562,
};

class npc_iron_rune_construct : public CreatureScript
{
public:
    npc_iron_rune_construct() : CreatureScript("npc_iron_rune_construct") { }

    struct npc_iron_rune_constructAI : public ScriptedAI
    {
        npc_iron_rune_constructAI(Creature* creature) : ScriptedAI(creature) { }

        bool ocuppied;
        uint8 seatID;

        void UpdateAI(const uint32 /*diff*/)
        {
            Unit* player = me->GetVehicleKit()->GetPassenger(seatID);

            if (!player)
                me->DisappearAndDie();
        }

        void PassengerBoarded(Unit* passenger, int8 seatId, bool /*apply*/)
        {
            seatID = seatId;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_iron_rune_constructAI(creature);
    }
};

class npc_lebronski : public CreatureScript
{
public:
    npc_lebronski() : CreatureScript("npc_lebronski") { }

    struct npc_lebronskiAI : public ScriptedAI
    {
        npc_lebronskiAI(Creature* creature) : ScriptedAI(creature) { }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            if(spell->Id == SPELL_BLUFF)
                caster->GetVehicleKit()->GetPassenger(0)->ToPlayer()->GroupEventHappens(QUEST_IRON_RUNE_CONST_BLUFF, me);
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_lebronskiAI(creature);
    }
};

class go_iron_rune_construct_workbank : public GameObjectScript
{
    public:
        go_iron_rune_construct_workbank() : GameObjectScript("go_iron_rune_construct_workbank") { }

        bool OnGossipHello(Player* player, GameObject* go)
        {
            if (player->GetQuestStatus(QUEST_IRON_RUNE_CONST_JUMP) == QUEST_STATUS_INCOMPLETE)
            {
                if(Creature* pConstruct = player->SummonCreature(NPC_IRON_RUNE_CONST_JUMP, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetOrientation()))
                {
                    pConstruct->SetLevel(player->getLevel());
                    player->EnterVehicle(pConstruct);
                    player->GroupEventHappens(QUEST_IRON_RUNE_CONST_JUMP, pConstruct);
                }
                return true;
            }

            if (player->GetQuestStatus(QUEST_IRON_RUNE_CONST_DATA) == QUEST_STATUS_INCOMPLETE)
            {
                if(Creature* pConstruct = player->SummonCreature(NPC_IRON_RUNE_CONST_DATA, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetOrientation()))
                {
                    pConstruct->SetLevel(player->getLevel());
                    player->EnterVehicle(pConstruct);
                }
                return true;
            }

            if (player->GetQuestStatus(QUEST_IRON_RUNE_CONST_BLUFF) == QUEST_STATUS_INCOMPLETE)
            {
                if(Creature* pConstruct = player->SummonCreature(NPC_IRON_RUNE_CONST_BLUFF, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetOrientation()))
                {
                    pConstruct->SetLevel(player->getLevel());
                    player->EnterVehicle(pConstruct);
                }
                return true;
            }

            return true;
        }
};

/*############
# npc_terokk
#############*/

enum TerokkData
{
    SPELL_CLEAVE = 15284,
    SPELL_DIVINE_SHIELD = 40733,
    SPELL_FRENZY = 28747,
    SPELL_SHADOW_BOLT_VOLLEY = 40721,
    SPELL_WILL_OF_THE_ARAKKOA = 40722,
    SPELL_VISUAL_MARKER = 40656,
    NPC_MARKER_TRIGGER = 97016,
    SAY_SUMMONED = 0,
    SAY_CHOSEN = 1,
    SAY_IMMUNE = 2
};

class npc_terokk : public CreatureScript
{
public:
    npc_terokk() : CreatureScript("npc_terokk") {}

    struct npc_terokkAI : public ScriptedAI
    {
        npc_terokkAI(Creature* creature) : ScriptedAI(creature) {}

        bool inCombat;
        bool Chosen;
        bool isImmune;
        uint32 CleaveTimer;
        uint32 VolleyTimer;
        uint32 ShieldTimer;
        uint32 MarkerTimer;

        void Reset()
        {
            inCombat = false;
            Chosen = false;
            isImmune = false;
            CleaveTimer = 5000;
            VolleyTimer = 3000;
            ShieldTimer = 999999;
            MarkerTimer = 15000;
        }

        void EnterCombat (Unit* /*who*/)
        {
            if (!inCombat)
            {
                Talk(SAY_SUMMONED);
                inCombat = true;
            }
        }

        void UpdateAI (const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (CleaveTimer <= diff)
            {
                DoCast(me->getVictim(),SPELL_CLEAVE);
                CleaveTimer = urand(9000,15000);
            } else CleaveTimer -= diff;

            if (VolleyTimer <= diff)
            {
                DoCast(me, SPELL_SHADOW_BOLT_VOLLEY);
                VolleyTimer = urand(12000,20000);
            } else VolleyTimer -= diff;

            if (MarkerTimer <= diff)
            {
                switch (urand(1,4))
                {
                    case 1:
                        if (Creature* trigger = me->SummonCreature(NPC_MARKER_TRIGGER,me->GetPositionX()+30,me->GetPositionY(),me->GetPositionZ(),0.0f,TEMPSUMMON_TIMED_DESPAWN,30000))
                            trigger->AddAura(SPELL_VISUAL_MARKER,trigger);
                            break;
                    case 2:
                        if (Creature* trigger = me->SummonCreature(NPC_MARKER_TRIGGER,me->GetPositionX(),me->GetPositionY()+30,me->GetPositionZ(),0.0f,TEMPSUMMON_TIMED_DESPAWN,30000))
                            trigger->AddAura(SPELL_VISUAL_MARKER,trigger);
                            break;
                    case 3:
                        if (Creature* trigger = me->SummonCreature(NPC_MARKER_TRIGGER,me->GetPositionX()-30,me->GetPositionY(),me->GetPositionZ(),0.0f,TEMPSUMMON_TIMED_DESPAWN,30000))
                            trigger->AddAura(SPELL_VISUAL_MARKER,trigger);
                            break;
                    case 4:
                        if (Creature* trigger = me->SummonCreature(NPC_MARKER_TRIGGER,me->GetPositionX(),me->GetPositionY()-30,me->GetPositionZ(),0.0f,TEMPSUMMON_TIMED_DESPAWN,30000))
                            trigger->AddAura(SPELL_VISUAL_MARKER,trigger);
                            break;
                }
                MarkerTimer = urand(25000,30000);
            } else MarkerTimer -= diff;

            if (HealthBelowPct(50) && !Chosen)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0))
                {
                    if (target && target->isAlive())
                    {
                        Talk(SAY_CHOSEN);
                        DoCast(target, SPELL_WILL_OF_THE_ARAKKOA);
                        Chosen = true;
                    }
                }
            }

            if (HealthBelowPct(25) && !isImmune)
            {
                if (ShieldTimer <= diff)
                {
                    Talk(SAY_IMMUNE);
                    DoCast(me, SPELL_DIVINE_SHIELD);
                    ShieldTimer = 60000;
                    isImmune = true;
                } else ShieldTimer -= diff;
            }

            if (me->FindNearestCreature(NPC_MARKER_TRIGGER,5.0f,true) && isImmune)
            {
                me->RemoveAura(SPELL_DIVINE_SHIELD);
                DoCast(me, SPELL_FRENZY);
                isImmune = false;
            }
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_terokkAI(creature);
    }
};

/*###################
# spell_fumping_39238
####################*/

enum FumpingSpellData
{
    SPELL_FUMPING = 39238,
    NPC_MATURE_BONE_SIFTER = 22482,
    NPC_SAND_GNOME = 22483
};

class spell_fumping_39238 : public SpellScriptLoader
{
public:
    spell_fumping_39238() : SpellScriptLoader("spell_fumping_39238") {}

    class spell_fumping_39238SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fumping_39238SpellScript)

        bool Validate(SpellInfo const * /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_FUMPING))
                return false;
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* player = GetCaster())
            {
                switch (urand(1,2))
                {
                    case 1: player->SummonCreature(NPC_MATURE_BONE_SIFTER, player->GetPositionX()+rand()%10, player->GetPositionY()+rand()%10, player->GetPositionZ()+5, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0); break;
                    case 2: player->SummonCreature(NPC_SAND_GNOME, player->GetPositionX()+rand()%10, player->GetPositionY()+rand()%10, player->GetPositionZ()+5, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0); break;
                }
            }
        }
        void Register()
        {
            OnEffectHit += SpellEffectFn(spell_fumping_39238SpellScript::HandleDummy, EFFECT_ALL, SPELL_EFFECT_ANY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_fumping_39238SpellScript();
    }
};

/*###################
# spell_fumping_39246
####################*/

enum AnotherFumpingSpellData
{
    SPELL_FUMPING2 = 39246,
    NPC_HAISHULUD = 22038
};

class spell_fumping_39246 : public SpellScriptLoader
{
public:
    spell_fumping_39246() : SpellScriptLoader("spell_fumping_39246") {}

    class spell_fumping_39246SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_fumping_39246SpellScript)

        bool Validate(SpellInfo const * /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_FUMPING2))
                return false;
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (Unit* player = GetCaster())
            {
                switch (urand(1,3))
                {
                    case 1:
                        player->SummonCreature(NPC_MATURE_BONE_SIFTER, player->GetPositionX()+rand()%10, player->GetPositionY()+rand()%10, player->GetPositionZ()+5, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);
                        player->SummonCreature(NPC_MATURE_BONE_SIFTER, player->GetPositionX()+rand()%10, player->GetPositionY()-rand()%10, player->GetPositionZ()+5, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);
                        player->SummonCreature(NPC_MATURE_BONE_SIFTER, player->GetPositionX()-rand()%10, player->GetPositionY()+rand()%10, player->GetPositionZ()+5, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);
                        break;
                    case 2:
                        player->SummonCreature(NPC_SAND_GNOME, player->GetPositionX()+rand()%10, player->GetPositionY()+rand()%10, player->GetPositionZ()+5, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);
                        player->SummonCreature(NPC_SAND_GNOME, player->GetPositionX()+rand()%10, player->GetPositionY()-rand()%10, player->GetPositionZ()+5, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);
                        player->SummonCreature(NPC_SAND_GNOME, player->GetPositionX()-rand()%10, player->GetPositionY()+rand()%10, player->GetPositionZ()+5, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);
                        break;
                    case 3:
                        player->SummonCreature(NPC_HAISHULUD, player->GetPositionX()+rand()%5, player->GetPositionY()+rand()%5, player->GetPositionZ()+5, 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 600000);
                        break;
                }
            }
        }
        void Register()
        {
            OnEffectHit += SpellEffectFn(spell_fumping_39246SpellScript::HandleDummy, EFFECT_ALL, SPELL_EFFECT_ANY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_fumping_39246SpellScript();
    }
};

enum keristraszaData
{
    QUEST_SPRINGING_TRAP = 11969,

    NPC_KERISTRASZA = 26237,
    NPC_SARAGOSA    = 26299,
    NPC_MALYGOS     = 26310,
    GO_SIGNAL_FIRE  = 194151,

    SPELL_RAELORASZ_SPARK = 62272,
    SPELL_FIRE_CORPSE     = 39199,
    SPELL_FIRE_BREATH     = 31962,
    SPELL_MALYGOS_EARTHQ  = 46853,
    SPELL_TAXI_KERISTASZA = 46814,
    SPELL_ICE_BLOCK       = 56644,
    SPELL_FROSTBOLT       = 61461,

    SAY_KERISTRASZA_1     = -1002030,
    YELL_KERISTRASZA_1    = -1002031,
    YELL_KERISTRASZA_2    = -1002032,
    YELL_KERISTRASZA_3    = -1002033,
    SAY_KERISTRASZA_2     = -1002034,

    //After Fligth
    YELL_MALYGOS_1        = -1002035,
    SAY_KERISTRASZA_3     = -1002036,
    YELL_MALYGOS_2        = -1002037,
    YELL_KERISTRASZA_4    = -1002038,
};
const Position posKeristrasza[6] =
{
    {4157.00f, 7035.00f, 215.87f, 0.00f}, // Summon position
    {4063.72f, 7084.12f, 174.86f, 0.00f}, // Land position
    {4054.51f, 7084.29f, 168.12f, 0.00f}, // Burn Corpse positon
    {4048.90f, 7083.94f, 168.21f, 0.00f}, // Saragosa Corpse Spawn
    {3800.47f, 6557.50f, 170.98f, 1.55f}, // Keristrasza 2º Spawn
    {3791.76f, 6603.61f, 179.91f, 0.00f}, // Malygos Spawn
};
class npc_signal_fire : public CreatureScript
{
public:
    npc_signal_fire() : CreatureScript("npc_signal_fire") { }

    struct npc_signal_fireAI : public ScriptedAI
    {
        npc_signal_fireAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;
        Creature* pKeristrasza;
        Creature* pSaragosa;
        Player* player;
        bool eventRunning;

        void Reset()
        {
            // Reset al variables
            events.Reset();
            pKeristrasza, pSaragosa, player = NULL;
            eventRunning = false;
            // Unlit signal
            if(GameObject* pGo = me->FindNearestGameObject(GO_SIGNAL_FIRE, 2.0f))
                pGo->SetGoState(GO_STATE_READY);
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            if (eventRunning)
                return;

            // The invisible trigger handles the event until the Fly of Keristrasza
            if(spell->Id == SPELL_RAELORASZ_SPARK)
            {
                player = caster->ToPlayer();
                // Lit the fire signal
                if(GameObject* pGo = me->FindNearestGameObject(GO_SIGNAL_FIRE, 2.0f))
                    pGo->SetGoState(GO_STATE_ACTIVE);
                // Summon Keristrasza
                if(Creature* pFind = me->SummonCreature(NPC_KERISTRASZA, posKeristrasza[0]))
                {
                    pKeristrasza = pFind;
                    pFind->SetFlying(true);
                    pFind->GetMotionMaster()->MovePoint(1, posKeristrasza[1]);
                }
                eventRunning = true;
                events.ScheduleEvent(1, 6000);
            }
        }

        void UpdateAI(const uint32 diff)
        {
            events.Update(diff);

            switch(events.ExecuteEvent())
            {
            case 1:
                pKeristrasza->SetFlying(false);
                DoScriptText(SAY_KERISTRASZA_1, pKeristrasza, player);
                events.ScheduleEvent(2, 3000);
                break;
            case 2:
                DoScriptText(YELL_KERISTRASZA_1, pKeristrasza);
                pKeristrasza->GetMotionMaster()->MovePoint(1, posKeristrasza[2]);
                events.ScheduleEvent(3, 5000);
                break;
            case 3:
                DoScriptText(YELL_KERISTRASZA_2, pKeristrasza);
                // Summon Saragosa and make her die
                if(Creature* pCorpse = me->SummonCreature(NPC_SARAGOSA, posKeristrasza[3]))
                    pSaragosa = pCorpse;
                events.ScheduleEvent(4, 3000);
                break;
            case 4:
                DoScriptText(YELL_KERISTRASZA_3, pKeristrasza);
                pKeristrasza->CastSpell(pSaragosa, SPELL_FIRE_BREATH, true);
                events.ScheduleEvent(5, 1000);
                break;
            case 5:
                me->AddAura(SPELL_FIRE_CORPSE, pSaragosa);
                events.ScheduleEvent(6, 1000);
                break;
            case 6:
                player->CastSpell(player, SPELL_MALYGOS_EARTHQ, true);
                events.ScheduleEvent(7, 3000);
                break;
            case 7:
                DoScriptText(SAY_KERISTRASZA_2, pKeristrasza, player);
                events.ScheduleEvent(8, 3000);
                break;
            case 8:
                // Passes the control to Keristrasza
                player->CastSpell(player, SPELL_TAXI_KERISTASZA, true);
                pKeristrasza->AI()->SetGUID(player->GetGUID());
                pSaragosa->DespawnOrUnsummon(10000);
                events.ScheduleEvent(9, 20000);
                break;
            case 9:
                Reset();
                break;
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_signal_fireAI(creature);
    }
};

class npc_keristrasza_coldarra : public CreatureScript
{
public:
    npc_keristrasza_coldarra() : CreatureScript("npc_keristrasza_coldarra") { }

    struct npc_keristrasza_coldarraAI : public ScriptedAI
    {
        npc_keristrasza_coldarraAI(Creature* creature) : ScriptedAI(creature) { }

        EventMap events;
        uint64 uiPlayer;
        bool waiting;
        bool finishedWay;
        Creature* pMalygos;

        void SetGUID(const uint64 &guid, int32 /*iId*/)
        {
            me->NearTeleportTo(posKeristrasza[4].GetPositionX(), posKeristrasza[4].GetPositionY(), posKeristrasza[4].GetPositionZ(), posKeristrasza[4].GetOrientation());
            me->SetVisible(false);
            uiPlayer = guid;
            waiting = true;
        }
        void Reset()
        {
            events.Reset();
            me->SetSpeed(MOVE_FLIGHT, 3.2f, true);
            pMalygos = NULL;
            uiPlayer = 0;
            waiting = false;
            finishedWay = false;
            me->SetReactState(REACT_PASSIVE);
        }


        void UpdateAI(const uint32 diff)
        {
            if(!waiting)
                return;

            if(!finishedWay)
            {
                if(Player* player = me->GetPlayer(*me, uiPlayer))
                {
                    if (!player->isInFlight())
                    {
                        if(me->IsWithinDist(player, 10.0f))
                        {
                            finishedWay = true;
                            me->SetVisible(true);
                            player->ToPlayer()->KilledMonsterCredit(NPC_KERISTRASZA, 0);
                            events.ScheduleEvent(1, 0);
                        }else
                            me->DespawnOrUnsummon(0);
                    }
                    else
                        return;
                }
            }

            events.Update(diff);

            switch(events.ExecuteEvent())
            {
            case 1:
                me->SetFlying(false);
                if(Player* player = me->GetPlayer(*me, uiPlayer))
                    DoScriptText(SAY_KERISTRASZA_3, me, player);
                events.ScheduleEvent(2, 5000);
                break;
            case 2:
                if(Creature* pSumm = me->SummonCreature(NPC_MALYGOS, posKeristrasza[5]))
                {
                    pMalygos = pSumm;
                    pSumm->SetFlying(true);
                    pSumm->SetReactState(REACT_PASSIVE);
                    pSumm->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_OOC_NOT_ATTACKABLE);
                    pSumm->SetFloatValue(OBJECT_FIELD_SCALE_X, 0.4f);
                    DoScriptText(YELL_MALYGOS_2, pMalygos);
                    pMalygos->SetUInt64Value(UNIT_FIELD_TARGET, me->GetGUID());
                    me->SetUInt64Value(UNIT_FIELD_TARGET, pMalygos->GetGUID());
                }
                events.ScheduleEvent(3, 6000);
                break;
            case 3:
                DoScriptText(YELL_KERISTRASZA_4, me);
                me->AddAura(SPELL_ICE_BLOCK, me);

                if(pMalygos)
                    pMalygos->DespawnOrUnsummon(7000);
                me->DespawnOrUnsummon(7000);
                break;
            }

        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_keristrasza_coldarraAI(creature);
    }
};

enum evergroveData
{
    SPELL_DRUID_SIGNAL = 38782,
    SPELL_DRUID_FORM   = 39158,
    SPELL_CROW_FORM    = 38776,

    QUEST_DEATH_DOOR   = 10910,
    ITEM_DRUID_SIGNAL  = 31763,
};
class npc_evergrove_druid : public CreatureScript
{
public:
    npc_evergrove_druid() : CreatureScript("npc_evergrove_druid") { }

    struct npc_evergrove_druidAI : public ScriptedAI
    {
        npc_evergrove_druidAI(Creature* creature) : ScriptedAI(creature) { }

        Player* player;
        Position playerPos;
        bool summoned;
        float x,y,z;

        void Reset()
        {
            // Reset all variables
            me->SetFlying(true);
            me->SetSpeed(MOVE_FLIGHT, 3.2f, true);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER | UNIT_NPC_FLAG_GOSSIP);
            me->SetVisible(false);
            player = NULL;
            summoned = false;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell)
        {
            if(summoned)
                return;

            if(spell->Id == SPELL_DRUID_SIGNAL)
            {
                summoned = true;

                if(caster)
                    player = caster->ToPlayer();

                // Prepare visuals
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER | UNIT_NPC_FLAG_GOSSIP);
                me->SetUInt64Value(UNIT_FIELD_TARGET, player->GetGUID());
                me->SetVisible(true);
                me->CastSpell(me, SPELL_CROW_FORM, true);

                // Move to player
                if(player)
                {
                    x = player->GetPositionX(); y = player->GetPositionY(); z = player->GetPositionZ();
                    me->GetMotionMaster()->MovePoint(0, x, y, z);
                }
            }
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if(!player)
                return;

            me->UpdatePosition( x, y, z, 0.0f, true);
            if(!player->IsFlying())
            {
                me->CastSpell(me, SPELL_DRUID_FORM, true);
                me->RemoveAurasDueToSpell(SPELL_CROW_FORM);
                me->SetFlying(false);
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STAND);
            }
            me->DespawnOrUnsummon(60000);
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_evergrove_druidAI(creature);
    }
};

#define GOSSIP_ITEM_DRUID_SIGNAL "He perdido mi Señal para druida."

class npc_antelarion_gossip : public CreatureScript
{
public:
    npc_antelarion_gossip() : CreatureScript("npc_antelarion_gossip") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if ((player->GetQuestStatus(QUEST_DEATH_DOOR) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(QUEST_DEATH_DOOR) == QUEST_STATUS_REWARDED) && !player->HasItemCount(ITEM_DRUID_SIGNAL, 1))
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DRUID_SIGNAL, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
    {
        player->CLOSE_GOSSIP_MENU();
        player->AddItem(ITEM_DRUID_SIGNAL, 1);
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
    new npc_rocket_warhead;
    new npc_father_kamaros;
    new npc_spring_rabbit;
    new npc_decomposing_ghoul();
    new npc_irulon_trueblade();
    new npc_banner_q11429();
    new go_ancient_skull_pile();
    new npc_ancient_vrykul();
    new at_ymiron_house();
    new npc_lich_king_hfjord();
    new npc_iron_rune_construct();
    new npc_lebronski();
    new go_iron_rune_construct_workbank();
    new npc_terokk();
    new spell_fumping_39238();
    new spell_fumping_39246();
    new npc_signal_fire();
    new npc_keristrasza_coldarra();
    new npc_evergrove_druid();
    new npc_antelarion_gossip();
}
