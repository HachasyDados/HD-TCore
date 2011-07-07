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
SDName: Isle_of_Queldanas
SD%Complete: 100
SDComment: Quest support: 11524, 11525, 11532, 11533, 11542, 11543, 11541
SDCategory: Isle Of Quel'Danas
EndScriptData */

/* ContentData
npc_converted_sentry
npc_greengill_slave
EndContentData */

#include "ScriptPCH.h"

/*######
## npc_converted_sentry
######*/

#define SAY_CONVERTED_1         -1000188
#define SAY_CONVERTED_2         -1000189

#define SPELL_CONVERT_CREDIT    45009

class npc_converted_sentry : public CreatureScript
{
public:
    npc_converted_sentry() : CreatureScript("npc_converted_sentry") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_converted_sentryAI (creature);
    }

    struct npc_converted_sentryAI : public ScriptedAI
    {
        npc_converted_sentryAI(Creature* c) : ScriptedAI(c) {}

        bool Credit;
        uint32 Timer;

        void Reset()
        {
            Credit = false;
            Timer = 2500;
        }

        void MoveInLineOfSight(Unit* /*who*/) {}
        void EnterCombat(Unit* /*who*/) {}

        void UpdateAI(const uint32 diff)
        {
            if (!Credit)
            {
                if (Timer <= diff)
                {
                    uint32 i = urand(1, 2);
                    if (i == 1)
                        DoScriptText(SAY_CONVERTED_1, me);
                    else
                        DoScriptText(SAY_CONVERTED_2, me);

                    DoCast(me, SPELL_CONVERT_CREDIT);
                    if (me->isPet())
                        me->ToPet()->SetDuration(7500);
                    Credit = true;
                } else Timer -= diff;
            }
        }
    };

};

/*######
## npc_greengill_slave
######*/

#define ENRAGE  45111
#define ORB     45109
#define QUESTG  11541
#define DM      25060

class npc_greengill_slave : public CreatureScript
{
public:
    npc_greengill_slave() : CreatureScript("npc_greengill_slave") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_greengill_slaveAI(creature);
    }

    struct npc_greengill_slaveAI : public ScriptedAI
    {
        npc_greengill_slaveAI(Creature* c) : ScriptedAI(c) {}

        uint64 PlayerGUID;

        void EnterCombat(Unit* /*who*/){}

        void Reset()
        {
        PlayerGUID = 0;
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (!caster)
                return;

            if (caster->GetTypeId() == TYPEID_PLAYER && spell->Id == ORB && !me->HasAura(ENRAGE))
            {
                PlayerGUID = caster->GetGUID();
                if (PlayerGUID)
                {
                    Unit* player = Unit::GetUnit((*me), PlayerGUID);
                    if (player && CAST_PLR(player)->GetQuestStatus(QUESTG) == QUEST_STATUS_INCOMPLETE)
                        DoCast(player, 45110, true);
                }
                DoCast(me, ENRAGE);
                Unit* Myrmidon = me->FindNearestCreature(DM, 70);
                if (Myrmidon)
                {
                    me->AddThreat(Myrmidon, 100000.0f);
                    AttackStart(Myrmidon);
                }
            }
        }

        void UpdateAI(const uint32 /*diff*/)
        {
            DoMeleeAttackIfReady();
        }
    };

};
enum Says
{
    SAY_THALORIEN_1  = -1016769,
    SAY_THALORIEN_2  = -1016770,
    SAY_THALORIEN_3  = -1016771,
    SAY_THALORIEN_4  = -1016772,
    SAY_THALORIEN_5  = -1016773,
    SAY_THALORIEN_6  = -1016774,
    SAY_THALORIEN_7  = -1016775,
    SAY_THALORIEN_8  = -1016776,
    SAY_THALORIEN_9  = -1016777,
    SAY_THALORIEN_10 = -1016778,
};
class npc_thalorien : public CreatureScript
{
public:
    npc_thalorien() : CreatureScript("npc_thalorien") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_thalorienAI(creature);
    }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            player->PrepareGossipMenu(creature, 0);

                  if ((player->GetQuestStatus(24535) == QUEST_STATUS_INCOMPLETE) || (player->GetQuestStatus(24563) == QUEST_STATUS_INCOMPLETE))
                          player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Examinar los restos.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->SendPreparedGossip(creature);

            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();

            switch(uiAction)
            {
                case GOSSIP_ACTION_INFO_DEF+1:
                    player->CLOSE_GOSSIP_MENU();
                                 creature->AI()->SetGUID(player->GetGUID());
                                    creature->SetPhaseMask(2, true);
                    player->SetPhaseMask(2, true);
                                    creature->AI()->DoAction(1);

                    break;
                default:
                    return false;                                   // nothing defined      -> trinity core handling
            }

            return true;                                            // no default handling  -> prevent trinity core handling
        }

    struct npc_thalorienAI : public ScriptedAI
    {
        npc_thalorienAI(Creature* c) : ScriptedAI(c) {}

        uint64 PlayerGUID;

                EventMap events;
               uint64 uiThalorien;
            uint64 uiMorlen;
               uint64 uiPlayer;
               void Reset()
           {
                      if (Player* player = me->GetPlayer(*me, uiPlayer))
                             player->SetPhaseMask(1, true);
                 if (Creature* pMorlen = me->GetCreature(*me, uiMorlen))
                                pMorlen->DisappearAndDie();
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                     me->SetPhaseMask(1, true);
                     events.Reset();
                        uiThalorien = 0;
                       uiMorlen = 0;
                  uiPlayer = 0;
          }

        void UpdateAI(const uint32 diff)
        {
                  events.Update(diff);

                  switch(events.ExecuteEvent())
                  {
                case 1:
                    // spawn all creatures
                    if (Creature* pThalorien = me->SummonCreature(37205, 11797.0f, -7074.06f, 26.379f, 0.242908f, TEMPSUMMON_CORPSE_DESPAWN, 0))
                    {
                        pThalorien->SetPhaseMask(2,true);
                        uiThalorien = pThalorien->GetGUID();
                                     }

                                     if (Creature* pGuard = me->SummonCreature(37211, 11807.0f, -7070.37f, 25.372f, 3.218f, TEMPSUMMON_TIMED_DESPAWN, 30000))
                                               pGuard->SetPhaseMask(2,true);
                                  if (Creature* pGuard = me->SummonCreature(37211, 11805.7f, -7073.64f, 25.5694f, 3.218f, TEMPSUMMON_TIMED_DESPAWN, 30000))
                                              pGuard->SetPhaseMask(2,true);
                                  if (Creature* pGuard = me->SummonCreature(37211, 11805.6f, -7077.0f, 25.9643f, 3.218f, TEMPSUMMON_TIMED_DESPAWN, 30000))
                                               pGuard->SetPhaseMask(2,true);
                                  if (Creature* pGuard = me->SummonCreature(37211, 11806.0f, -7079.71f, 26.2067f, 3.218f, TEMPSUMMON_TIMED_DESPAWN, 30000))
                                              pGuard->SetPhaseMask(2,true);

                    if (Creature* pMorlen = me->SummonCreature(37542, 11776.8f, -7050.72f, 25.2394f, 5.13752f, TEMPSUMMON_CORPSE_DESPAWN, 0))
                    {
                                             pMorlen->Mount(25678);
                                         pMorlen->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
                        pMorlen->SetPhaseMask(2,true);
                        pMorlen->SetReactState(REACT_PASSIVE);
                        uiMorlen = pMorlen->GetGUID();
                    }

                                  events.ScheduleEvent(2,100);
                    break;
                                case 2:
                                        if (Creature* pThalorien = me->GetCreature(*me, uiThalorien))
                                          DoScriptText(SAY_THALORIEN_1, pThalorien);
                                     events.ScheduleEvent(3,5000);
                                  break;
                         case 3:
                                        if (Creature* pThalorien = me->GetCreature(*me, uiThalorien))
                                          DoScriptText(SAY_THALORIEN_2, pThalorien);
                                     events.ScheduleEvent(4,5000);
                                  break;
                         case 4:
                                        if (Creature* pThalorien = me->GetCreature(*me, uiThalorien))
                                          DoScriptText(SAY_THALORIEN_3, pThalorien);
                                     events.ScheduleEvent(5,10000);
                                 break;
                         case 5:
                                        if (Creature* pThalorien = me->GetCreature(*me, uiThalorien))
                                          DoScriptText(SAY_THALORIEN_4, pThalorien);
                                     events.ScheduleEvent(6,6000);
                                  break;
                         case 6:
                                        if (Creature* pThalorien = me->GetCreature(*me, uiThalorien))
                                          pThalorien->GetMotionMaster()->MovePoint(0, 11787.3f, -7064.11f, 25.8395f);
                                    events.ScheduleEvent(7,6000);
                                  break;
                         case 7:
                                        if (Creature* pThalorien = me->GetCreature(*me, uiThalorien))
                                          DoScriptText(SAY_THALORIEN_5, pThalorien);
                                     events.ScheduleEvent(8,9000);
                                  break;
                         case 8:
                                        if (Creature* pThalorien = me->GetCreature(*me, uiThalorien))
                                          DoScriptText(SAY_THALORIEN_6, pThalorien);
                                     if (Creature* pMorlen = me->GetCreature(*me, uiMorlen))
                                                pMorlen->CastSpell(pMorlen, 50689, true);
                                      events.ScheduleEvent(9,9000);
                                  break;
                         // Intro terminada, comienzan las oleadas.
                             case 9:
                                        if (Creature* pThalorien = me->GetCreature(*me, uiThalorien))
                                          pThalorien->SetHomePosition(pThalorien->GetPositionX(), pThalorien->GetPositionY(), pThalorien->GetPositionZ(), pThalorien->GetOrientation());
                                 SummonWave(37538);
                                     events.ScheduleEvent(10, 30000);
                                       break;
                         case 10:
                                       SummonWave(37539);
                                     events.ScheduleEvent(11, 30000);
                                       break;
                         case 11:
                                       SummonWave(37541);
                                     events.ScheduleEvent(12, 30000);
                                       break;
                         case 12:
                                       if (Creature* pThalorien = me->GetCreature(*me, uiThalorien))
                                  {
                                              if (Creature* pMorlen = me->GetCreature(*me, uiMorlen))
                                                {
                                                      pMorlen->SetReactState(REACT_AGGRESSIVE);
                                                      pMorlen->AddThreat(pThalorien, 100);
                                                   pMorlen->AI()->AttackStart(pThalorien);
                                                }
                                      }
                                      break;
                         // Outro
                               case 13:
                                       if (Creature* pThalorien = me->GetCreature(*me, uiThalorien))
                                          DoScriptText(SAY_THALORIEN_7, pThalorien);
                                     events.ScheduleEvent(14, 3500);
                                        break;
                         case 14:
                                       if (Creature* pThalorien = me->GetCreature(*me, uiThalorien))
                                          DoScriptText(SAY_THALORIEN_8, pThalorien);
                                     events.ScheduleEvent(15, 3500);
                                        break;
                         case 15:
                                       if (Creature* pThalorien = me->GetCreature(*me, uiThalorien))
                                          DoScriptText(SAY_THALORIEN_9, pThalorien);
                                     events.ScheduleEvent(16, 3000);
                                        break;
                         case 16:
                                       if (Creature* pThalorien = me->GetCreature(*me, uiThalorien))
                                          DoScriptText(SAY_THALORIEN_10, pThalorien);
                                    events.ScheduleEvent(17, 12000);
                                       break;
                         case 17:
                                       if (Creature* pThalorien = me->GetCreature(*me, uiThalorien))
                                          pThalorien->DisappearAndDie();
                                 if (Player* player = me->GetPlayer(*me, uiPlayer))
                                             player->KilledMonsterCredit(37601, player->GetGUID());
                                 Reset();
                                       break;
                 }
              }

        void SummonWave(uint32 entry)
               {
                              if (Creature* pThalorien = me->GetCreature(*me, uiThalorien))
                                  {
                                              if (Creature* pZombie = me->SummonCreature(entry, 11768.7f, -7065.83f, 24.0971f, 0.125877f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 0))
                                                {
                                                      pZombie->SetPhaseMask(2,true);
                                                 pZombie->AddThreat(pThalorien, 100);
                                                   pZombie->AI()->AttackStart(pThalorien);
                                                }
                                              if (Creature* pZombie = me->SummonCreature(entry, 11769.5f, -7063.83f, 24.1399f, 6.06035f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 0))
                                         {
                                                      pZombie->SetPhaseMask(2,true);
                                                 pZombie->AddThreat(pThalorien, 100);
                                                   pZombie->AI()->AttackStart(pThalorien);
                                                        // Super Ñapa!
                                                 if (pZombie->GetEntry() == 37541)
                                                              pZombie->DisappearAndDie();
                                            }
                                              if (Creature* pZombie = me->SummonCreature(entry, 11769.8f, -7061.41f, 24.2536f, 6.06035f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 0))
                                         {
                                                      pZombie->SetPhaseMask(2,true);
                                                 pZombie->AddThreat(pThalorien, 100);
                                                   pZombie->AI()->AttackStart(pThalorien);
                                                }
                                              if (Creature* pZombie = me->SummonCreature(entry, 11769.4f, -7057.86f, 24.4624f, 0.00335493f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 0))
                                              {
                                                      pZombie->SetPhaseMask(2,true);
                                                 pZombie->AddThreat(pThalorien, 100);
                                                   pZombie->AI()->AttackStart(pThalorien);
                                                        // Super Ñapa!
                                                 if (pZombie->GetEntry() == 37541)
                                                              pZombie->DisappearAndDie();
                                            }
                                              if (Creature* pZombie = me->SummonCreature(entry, 11769.4f, -7054.56f, 24.6869f, 0.00335493f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 0))
                                              {
                                                      pZombie->SetPhaseMask(2,true);
                                                 pZombie->AddThreat(pThalorien, 100);
                                                   pZombie->AI()->AttackStart(pThalorien);
                                                }
                                      }
              }
              void SummonedCreatureDespawn(Creature* summon)
         {
                      if (summon->GetEntry() == 37205)
                       {
                              Reset();
                               return;
                        }
                      if (summon->GetEntry() == 37542)
                               events.ScheduleEvent(13, 3000);
                }
              void SetGUID(const uint64 &uiGuid, int32 /*iId*/)
              {
                      uiPlayer = uiGuid;
             }
              void DoAction(const int32 actionId)
            {
                      switch(actionId)
                       {
                              case 1:
                                        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                                  events.ScheduleEvent(1,0);
                                     break;
                 }
              }
    };

};

void AddSC_isle_of_queldanas()
{
    new npc_converted_sentry();
    new npc_greengill_slave();
  new npc_thalorien();
}
