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
#include "utgarde_pinnacle.h"

enum Spells
{
    SPELL_CALL_FLAMES                             = 48258,
    SPELL_FLAME_VOLLEY                            = 37109,
    H_SPELL_FLAME_VOLLEY                          = 23512,
    SPELL_RITUAL_OF_THE_SWORD                     = 48276, //Effect #1 Teleport,  Effect #2 Dummy
    SPELL_RITUAL_PREPARATION                      = 48267,
    SPELL_RITUAL_STRIKE                           = 48277,
    SPELL_SINSTER_STRIKE                          = 15667,
    H_SPELL_SINSTER_STRIKE                        = 59409,
    SPELL_SVALA_TRANSFORMING1                     = 54140,
    SPELL_SVALA_TRANSFORMING2                     = 54205
};
//not in db
enum Yells
{
    SAY_DIALOG_WITH_ARTHAS_1                      = -1575015,
    SAY_DIALOG_WITH_ARTHAS_2                      = -1575016,
    SAY_DIALOG_WITH_ARTHAS_3                      = -1575017,
    SAY_AGGRO                                     = -1575018,
    SAY_SLAY_1                                    = -1575019,
    SAY_SLAY_2                                    = -1575020,
    SAY_SLAY_3                                    = -1575021,
    SAY_DEATH                                     = -1575022,
    SAY_SACRIFICE_PLAYER_1                        = -1575023,
    SAY_SACRIFICE_PLAYER_2                        = -1575024,
    SAY_SACRIFICE_PLAYER_3                        = -1575025,
    SAY_SACRIFICE_PLAYER_4                        = -1575026,
    SAY_SACRIFICE_PLAYER_5                        = -1575027,
    SAY_DIALOG_OF_ARTHAS_1                        = -1575038,
    SAY_DIALOG_OF_ARTHAS_2                        = -1575039,
};
enum Creatures
{
    CREATURE_ARTHAS                               = 24266, // Image of Arthas
    CREATURE_SVALA_SORROWGRAVE                    = 26668, // Svala after transformation
    CREATURE_SVALA                                = 29281, // Svala before transformation
    CREATURE_RITUAL_CHANNELER                     = 27281,
    CREATURE_RITUAL_TARGET                        = 27327,
    CREATURE_RITUAL_SWORD                         = 27325,
    CREATURE_FLAME_BRAZIER                        = 27273,
    CREATURE_SCOURGE_HULK                         = 26555,
};
enum ChannelerSpells
{
    //ritual channeler's spells
    SPELL_PARALYZE                                = 48278,
    SPELL_SHADOWS_IN_THE_DARK                     = 59407
};
enum HulkDefines
{
    SPELL_MIGHTY_BLOW                             = 48697,
    SPELL_VOLATILE_INFECTION                      = 59228,
    H_SPELL_VOLATILE_INFECTION                    = 56785,

    ACHIEV_INCREDIBLE_HULK                        = 2043
};
enum Misc
{
    DATA_SVALA_DISPLAY_ID                         = 25944
};
enum IntroPhase
{
    IDLE,
    INTRO,
    FINISHED
};
enum CombatPhase
{
    NORMAL,
    SACRIFICING
};

static Position RitualChannelerPos[]=
{
    {296.42f, -355.01f, 90.94f, 0.0f},
    {302.36f, -352.01f, 90.54f, 0.0f},
    {291.39f, -350.89f, 90.54f, 0.0f}
};

static Position FlameCallPos[] =
{
    {285.6f, -357.5f, 91.0833f, 5.75959f},
    {307.0f, -357.5f, 91.0833f, 6.02139f}
};
static Position ArthasPos = { 295.81f, -366.16f, 92.57f, 1.58f };
static Position SvalaPos = { 296.632f, -346.075f, 90.6307f, 1.58f };

class boss_svala : public CreatureScript
{
public:
    boss_svala() : CreatureScript("boss_svala") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_svalaAI (creature);
    }

    struct boss_svalaAI : public ScriptedAI
    {
        boss_svalaAI(Creature* c) : ScriptedAI(c)
        {
            instance = c->GetInstanceScript();
        }

        uint32 uiIntroTimer;

        uint8 uiIntroPhase;

        IntroPhase Phase;

        TempSummon* pArthas;
        uint64 uiArthasGUID;

        InstanceScript* instance;

        void Reset()
        {
            Phase = IDLE;
            uiIntroTimer = 1 * IN_MILLISECONDS;
            uiIntroPhase = 0;
            uiArthasGUID = 0;

            if (instance)
                instance->SetData(DATA_SVALA_SORROWGRAVE_EVENT, NOT_STARTED);
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (!who)
                return;

            if (Phase == IDLE && me->IsValidAttackTarget(who) && me->IsWithinDistInMap(who, 40))
            {
                Phase = INTRO;
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                if (Creature* pArthas = me->SummonCreature(CREATURE_ARTHAS, ArthasPos, TEMPSUMMON_MANUAL_DESPAWN))
                {
                    pArthas->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    pArthas->SetFloatValue(OBJECT_FIELD_SCALE_X, 5);
                    uiArthasGUID = pArthas->GetGUID();
                }
            }
        }

        void AttackStart(Unit* /*who*/) {}

        void UpdateAI(const uint32 diff)
        {
            if (Phase != INTRO)
                return;

            if (uiIntroTimer <= diff)
            {
                Creature* pArthas = Unit::GetCreature(*me, uiArthasGUID);
                if (!pArthas)
                    return;

                switch (uiIntroPhase)
                {
                    case 0:
                        DoScriptText(SAY_DIALOG_WITH_ARTHAS_1, me);
                        ++uiIntroPhase;
                        uiIntroTimer = 7000;
                        break;
                    case 1:
                        DoScriptText(SAY_DIALOG_OF_ARTHAS_1, pArthas);
                        ++uiIntroPhase;
                        uiIntroTimer = 16500;
                        break;
                    case 2:
                        DoScriptText(SAY_DIALOG_WITH_ARTHAS_2, me);
                        DoCast(me, SPELL_SVALA_TRANSFORMING1);
                        ++uiIntroPhase;
                        uiIntroTimer = 10000;
                        break;
                    case 3:
                        DoScriptText(SAY_DIALOG_OF_ARTHAS_2, pArthas);
                        ++uiIntroPhase;
                        uiIntroTimer = 6500;
                        break;
                    case 4:
                        DoScriptText(SAY_DIALOG_WITH_ARTHAS_3, me);
                        ++uiIntroPhase;
                        uiIntroTimer = 2800;
                        break;
                    case 5:
                        DoCast(me, SPELL_SVALA_TRANSFORMING2);
                        ++uiIntroPhase;
                        uiIntroTimer = 200;
                        break;
                    case 6:
                        if (Creature* svala = me->SummonCreature(CREATURE_SVALA_SORROWGRAVE, SvalaPos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60*IN_MILLISECONDS))
                        {
                            me->DespawnOrUnsummon();
                            pArthas->DespawnOrUnsummon();
                            uiArthasGUID = 0;
                            Phase = FINISHED;
                        }
                        else
                            Reset();
                        break;
                }
            } else uiIntroTimer -= diff;
        }
    };

};

class mob_ritual_channeler : public CreatureScript
{
public:
    mob_ritual_channeler() : CreatureScript("mob_ritual_channeler") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_ritual_channelerAI(creature);
    }

    struct mob_ritual_channelerAI : public Scripted_NoMovementAI
    {
        mob_ritual_channelerAI(Creature* c) :Scripted_NoMovementAI(c)
        {
            instance = c->GetInstanceScript();
        }

        InstanceScript* instance;

        void Reset()
        {
            DoCast(me, SPELL_SHADOWS_IN_THE_DARK);
            DoAction(0);
        }

        void DoAction(const int32 /*action*/)
        {
            if(Creature* target = me->SummonCreature(CREATURE_RITUAL_TARGET, SvalaPos))
            {
                if(Player* player = me->GetPlayer(*me, instance->GetData64(DATA_SACRIFICED_PLAYER)))
                    target->setFaction(player->ToUnit()->getFaction());

                me->SetUInt64Value(UNIT_FIELD_TARGET, target->GetGUID());
                DoCast(target, SPELL_PARALYZE);
            }
        }
    };

};

class boss_svala_sorrowgrave : public CreatureScript
{
public:
    boss_svala_sorrowgrave() : CreatureScript("boss_svala_sorrowgrave") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_svala_sorrowgraveAI(creature);
    }

    struct boss_svala_sorrowgraveAI : public ScriptedAI
    {
        boss_svala_sorrowgraveAI(Creature* c) : ScriptedAI(c), summons(c)
        {
            instance = c->GetInstanceScript();
        }

        uint32 uiSinsterStrikeTimer;
        uint32 uiCallFlamesTimer;
        uint32 uiRitualOfSwordTimer;
        uint32 uiSacrificeTimer;

        CombatPhase Phase;

        SummonList summons;
        uint64 uiSword;

        bool bSacrificed;

        InstanceScript* instance;

        void Reset()
        {
            uiSinsterStrikeTimer = 7 * IN_MILLISECONDS;
            uiCallFlamesTimer = 10 * IN_MILLISECONDS;
            uiRitualOfSwordTimer = 20 * IN_MILLISECONDS;
            uiSacrificeTimer = 8 * IN_MILLISECONDS;

            bSacrificed = false;

            Phase = NORMAL;

            DoTeleportTo(296.632f, -346.075f, 90.6307f);
            me->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);

            summons.DespawnAll();

            if (instance)
            {
                instance->SetData(DATA_SVALA_SORROWGRAVE_EVENT, NOT_STARTED);
                instance->SetData64(DATA_SACRIFICED_PLAYER, 0);
            }

            me->AddUnitMovementFlag(MOVEMENTFLAG_LEVITATING);
            //me->SetFlying(true);
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoScriptText(SAY_AGGRO, me);

            if (instance)
                instance->SetData(DATA_SVALA_SORROWGRAVE_EVENT, IN_PROGRESS);
        }

        void JustSummoned(Creature* summon)
        {
            if(summon->GetEntry() != CREATURE_RITUAL_CHANNELER)
                return;

            summons.Summon(summon);
        }

        void SummonedCreatureDespawn(Creature* summon)
        {
            summons.Despawn(summon);
        }

        void UpdateAI(const uint32 diff)
        {
            if (Phase == NORMAL)
            {
                //Return since we have no target
                if (!UpdateVictim())
                    return;

                if (uiSinsterStrikeTimer <= diff)
                {
                    DoCast(me->getVictim(), SPELL_SINSTER_STRIKE);
                    uiSinsterStrikeTimer = urand(5 * IN_MILLISECONDS, 9 * IN_MILLISECONDS);
                } else uiSinsterStrikeTimer -= diff;

                if (uiCallFlamesTimer <= diff)
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    {
                        for (uint8 i = 0; i < 2; ++i)
                        {
                            if(Creature* flame = me->SummonCreature(CREATURE_FLAME_BRAZIER, FlameCallPos[i], TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 360000))
                            {
                                flame->SetFlying(true);
                                flame->CastSpell(target, IsHeroic() ? H_SPELL_FLAME_VOLLEY : SPELL_FLAME_VOLLEY, true);
                                flame->DespawnOrUnsummon(3000);
                            }
                        }

                        DoCast(target, SPELL_CALL_FLAMES);
                        uiCallFlamesTimer = urand(8 * IN_MILLISECONDS, 12 * IN_MILLISECONDS);
                    }
                } else uiCallFlamesTimer -= diff;

                if (!bSacrificed)
                {
                    if (uiRitualOfSwordTimer <= diff)
                    {
                        if (Unit* pSacrificeTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                        {
                            DoScriptText(RAND(SAY_SACRIFICE_PLAYER_1, SAY_SACRIFICE_PLAYER_2, SAY_SACRIFICE_PLAYER_3, SAY_SACRIFICE_PLAYER_4, SAY_SACRIFICE_PLAYER_5), me);
                            me->AddAura(SPELL_PARALYZE, pSacrificeTarget);
                            pSacrificeTarget->CastSpell(pSacrificeTarget, SPELL_RITUAL_PREPARATION, true);
                            me->SetFlying(true);
                            me->GetMotionMaster()->MoveIdle();
                            DoTeleportPlayer(pSacrificeTarget, 296.632f, -346.075f, 90.63f, 4.6f);
                            DoCast(pSacrificeTarget, SPELL_RITUAL_OF_THE_SWORD);
                            //Spell doesn't teleport
                            //me->SetUnitMovementFlags(MOVEMENTFLAG_CAN_FLY);
                            Phase = SACRIFICING;
                            if (instance)
                            {
                                instance->SetData64(DATA_SACRIFICED_PLAYER, pSacrificeTarget->GetGUID());
                                for (uint8 i = 0; i < 3; ++i)
                                    me->SummonCreature(CREATURE_RITUAL_CHANNELER, RitualChannelerPos[i], TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 360000);
                            }
                            if(Creature* sword = me->SummonCreature(CREATURE_RITUAL_SWORD, 296.632f, -346.075f, 113.85f))
                                uiSword = sword->GetGUID();

                            bSacrificed = true;
                        }
                    } else uiRitualOfSwordTimer -= diff;
                }

                DoMeleeAttackIfReady();
            }
            else  //SACRIFICING
            {
                if(summons.empty() || !me->GetCreature(*me, uiSword)) // Sacrfing finished
                {
                    summons.DespawnAll();
                    //go down
                    if(Creature* sword = me->GetCreature(*me, uiSword))
                        sword->DespawnOrUnsummon();

                    if(Player* player = me->GetPlayer(*me, instance->GetData64(DATA_SACRIFICED_PLAYER)))
                    {
                        player->RemoveAurasDueToSpell(SPELL_PARALYZE);
                        player->RemoveAurasDueToSpell(SPELL_RITUAL_PREPARATION);
                    }

                    Phase = NORMAL;
                    me->SetFlying(false);
                    me->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);
                    me->RemoveAurasDueToSpell(SPELL_RITUAL_OF_THE_SWORD);

                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                        me->GetMotionMaster()->MoveChase(target);
                }
            }
        }

        void KilledUnit(Unit* /*victim*/)
        {
            DoScriptText(RAND(SAY_SLAY_1, SAY_SLAY_2, SAY_SLAY_3), me);
        }

        void JustDied(Unit* killer)
        {
            if (instance)
            {
                Creature* pSvala = Unit::GetCreature((*me), instance->GetData64(DATA_SVALA));
                if (pSvala && pSvala->isAlive())
                    killer->Kill(pSvala);

                instance->SetData(DATA_SVALA_SORROWGRAVE_EVENT, DONE);
            }
            DoScriptText(SAY_DEATH, me);
        }
    };

};

class npc_scourge_hulk : public CreatureScript
{
public:
    npc_scourge_hulk() : CreatureScript("npc_scourge_hulk") { }

    struct npc_scourge_hulkAI : public ScriptedAI
    {
        npc_scourge_hulkAI(Creature *creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;
        uint32 lastSpellHit;
        uint32 uiBlowTimer;
        uint32 uiInfectionTimer;

        void Reset()
        {
            lastSpellHit = 0;
            uiBlowTimer = urand(4000,9000);
            uiInfectionTimer = urand(10000,14000);
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if(!UpdateVictim())
                return;

            if(uiBlowTimer < uiDiff)
            {
                if(Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                {
                    if(!target->HasAura(SPELL_PARALYZE))
                    {
                        DoCast(target, SPELL_MIGHTY_BLOW);
                        uiBlowTimer = urand(12000, 17000);
                    }
                    else
                        uiBlowTimer = urand(2000, 4000);
                }
            }
            else
                uiBlowTimer -= uiDiff;

            if(uiInfectionTimer < uiDiff)
            {
                if(Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                   DoCast(target, SPELL_VOLATILE_INFECTION);
                uiInfectionTimer = urand(13000, 17000);
            }
            else
                uiInfectionTimer -= uiDiff;

            DoMeleeAttackIfReady();
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_scourge_hulkAI(creature);
    }
};


class npc_sword_ritual : public CreatureScript
{
public:
    npc_sword_ritual() : CreatureScript("npc_sword_ritual") { }

    struct npc_sword_ritualAI : public ScriptedAI
    {
        npc_sword_ritualAI(Creature *creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* instance;

        void Reset()
        {
            me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
            me->SetReactState(REACT_PASSIVE);
            me->SetFlying(true);
            me->GetMotionMaster()->MovePoint(1, SvalaPos.GetPositionX(), SvalaPos.GetPositionY(), SvalaPos.GetPositionZ() + 2.0f);
        }

        void KilledUnit(Unit* victim)
        {
            if(!IsHeroic())
                return;

            if(Creature* hulk = victim->ToCreature())
                if(hulk->GetEntry() == CREATURE_SCOURGE_HULK)
                    instance->DoCompleteAchievement(ACHIEV_INCREDIBLE_HULK);
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if(Player* player = me->GetPlayer(*me, instance->GetData64(DATA_SACRIFICED_PLAYER)))
            {
                me->CastSpell(player, SPELL_RITUAL_STRIKE, true);
                player->RemoveAurasDueToSpell(SPELL_PARALYZE);
                player->RemoveAurasDueToSpell(SPELL_RITUAL_PREPARATION);
                me->DealDamage(player, (uint32)((double)(player->GetMaxHealth())*0.75));
                me->setFaction(player->ToUnit()->getFaction());
                me->CastSpell(me, SPELL_RITUAL_STRIKE, true);
                me->DespawnOrUnsummon(500);
            }
        }
    };
    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_sword_ritualAI(creature);
    }
};

void AddSC_boss_svala()
{
    new boss_svala();
    new mob_ritual_channeler();
    new boss_svala_sorrowgrave();
    new npc_scourge_hulk();
    new npc_sword_ritual();
}
