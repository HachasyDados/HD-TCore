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
SDName: Boss_Broggok
SD%Complete: 70
SDComment: pre-event not made
SDCategory: Hellfire Citadel, Blood Furnace
EndScriptData */

#include "ScriptPCH.h"
#include "blood_furnace.h"

enum eEnums
{
    SAY_AGGRO               = -1542008,

    SPELL_SLIME_SPRAY       = 30913,
    SPELL_POISON_CLOUD      = 30916,
    SPELL_POISON_BOLT       = 30917,

    SPELL_POISON            = 30914
};

class boss_broggok : public CreatureScript
{
    public:

        boss_broggok()
            : CreatureScript("boss_broggok")
        {
        }

        struct boss_broggokAI : public ScriptedAI
        {
            boss_broggokAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;

            uint32 AcidSpray_Timer;
            uint32 PoisonSpawn_Timer;
            uint32 PoisonBolt_Timer;

            void Reset()
            {
                AcidSpray_Timer = 10000;
                PoisonSpawn_Timer = 5000;
                PoisonBolt_Timer = 7000;
                if (instance)
                {
                    instance->SetData(TYPE_BROGGOK_EVENT, NOT_STARTED);
                    instance->HandleGameObject(instance->GetData64(DATA_DOOR4), true);
                }
            }

            void EnterCombat(Unit* /*who*/)
            {
                DoScriptText(SAY_AGGRO, me);
                if (instance)
                {
                    instance->SetData(TYPE_BROGGOK_EVENT, IN_PROGRESS);
                    instance->HandleGameObject(instance->GetData64(DATA_DOOR4), false);
                    instance->HandleGameObject(instance->GetData64(DATA_DOOR5), false);
                }
            }

            void JustSummoned(Creature* summoned)
            {
                summoned->setFaction(16);
                summoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                summoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                summoned->CastSpell(summoned, SPELL_POISON, false, 0, 0, me->GetGUID());
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (AcidSpray_Timer <= diff)
                {
                    DoCast(me->getVictim(), SPELL_SLIME_SPRAY);
                    AcidSpray_Timer = 4000+rand()%8000;
                }
                else
                    AcidSpray_Timer -=diff;

                if (PoisonBolt_Timer <= diff)
                {
                    DoCast(me->getVictim(), SPELL_POISON_BOLT);
                    PoisonBolt_Timer = 4000+rand()%8000;
                }
                else
                    PoisonBolt_Timer -=diff;

                if (PoisonSpawn_Timer <= diff)
                {
                    DoCast(me, SPELL_POISON_CLOUD);
                    PoisonSpawn_Timer = 20000;
                }
                else
                    PoisonSpawn_Timer -=diff;

                DoMeleeAttackIfReady();
            }

            void JustDied(Unit* /*who*/)
            {
                if (instance)
                {
                    instance->HandleGameObject(instance->GetData64(DATA_DOOR4), true);
                    instance->HandleGameObject(instance->GetData64(DATA_DOOR5), true);
                    instance->SetData(TYPE_BROGGOK_EVENT, DONE);
                }
            }

        };

        CreatureAI* GetAI(Creature* Creature) const
        {
            return new boss_broggokAI (Creature);
        }
};

class go_broggok_lever : public GameObjectScript
{
public:
    go_broggok_lever() : GameObjectScript("go_broggok_lever") { }

    enum LeverData
    {
        NPC_LAUGHING_SKULL_WARDEN = 17624,
        NPC_FEL_ORC_NEOPHYTE = 17429
    };

    bool OnGossipHello(Player* /*player*/, GameObject* go)
    {
        if (InstanceScript* instance = go->GetInstanceScript())
        {
            go->SummonCreature(NPC_LAUGHING_SKULL_WARDEN,464.566986f,54.492401f,9.614540f,1.621839f,TEMPSUMMON_CORPSE_DESPAWN,0);
            go->SummonCreature(NPC_LAUGHING_SKULL_WARDEN,447.079010f,52.09660f,9.617910f,1.127570f,TEMPSUMMON_CORPSE_DESPAWN,0);
            go->SummonCreature(NPC_FEL_ORC_NEOPHYTE,449.192993f,52.041500f,9.620020f,1.257160f,TEMPSUMMON_CORPSE_DESPAWN,0);
            go->SummonCreature(NPC_FEL_ORC_NEOPHYTE,461.744995f,51.934700f,9.620450f,1.736250f,TEMPSUMMON_CORPSE_DESPAWN,0);
            instance->HandleGameObject(instance->GetData64(DATA_DOOR5), true);
        }
        return true;
    }
};

void AddSC_boss_broggok()
{
    new boss_broggok();
    new go_broggok_lever();
}
