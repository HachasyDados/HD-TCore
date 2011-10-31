/*
 * Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
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
// Based on /dev/rsa modified by Vlad
// TODO:  Trash mobs, spawn and removal of fire ring/walls, spawn of halion

#include "ScriptPCH.h"
#include "ruby_sanctum.h"

class instance_ruby_sanctum_custom : public InstanceMapScript
{
public:
    instance_ruby_sanctum_custom() : InstanceMapScript("instance_ruby_sanctum_custom", 724) { }

    InstanceScript* GetInstanceScript(InstanceMap* pMap) const
    {
        return new instance_ruby_sanctum_custom_InstanceMapScript(pMap);
    }

    struct instance_ruby_sanctum_custom_InstanceMapScript : public InstanceScript
    {
        instance_ruby_sanctum_custom_InstanceMapScript(Map* pMap) : InstanceScript(pMap) {Initialize();};

        std::string strSaveData;

        //Creatures GUID
        uint32 m_auiEncounter[MAX_ENCOUNTERS+1];

        uint32 m_auiEventTimer;
        uint32 m_auiHalionEvent;

        uint32 m_auiOrbDirection;
        uint32 m_auiOrbNState;
        uint32 m_auiOrbSState;

        uint64 m_uiHalion_pGUID;
        uint64 m_uiHalion_tGUID;
        uint64 m_uiHalionControlGUID;
        uint64 m_uiRagefireGUID;
        uint64 m_uiZarithianGUID;
        uint64 m_uiBaltharusGUID;
        uint64 m_uiCloneGUID;
        uint64 m_uiXerestraszaGUID;

        uint64 m_uiOrbNGUID;
        uint64 m_uiOrbSGUID;
        uint64 m_uiOrbFocusGUID;
        uint64 m_uiOrbCarrierGUID;

        //object GUID
        uint64 m_uiHalionPortal1GUID;
        uint64 m_uiHalionPortal2GUID;
        uint64 m_uiHalionPortal3GUID;
        uint64 m_uiHalionFireWallSGUID;
        uint64 m_uiHalionFireWallMGUID;
        uint64 m_uiHalionFireWallLGUID;
        uint64 m_uiBaltharusTargetGUID;

        uint64 m_uiFireFieldGUID;
        uint64 m_uiFlameWallsGUID;
        uint64 m_uiFlameRingGUID;

        void Initialize()
        {
            for (uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
                m_auiEncounter[i] = NOT_STARTED;

            m_auiEventTimer = 1000;

            m_uiHalion_pGUID = 0;
            m_uiHalion_tGUID = 0;
            m_uiRagefireGUID = 0;
            m_uiZarithianGUID = 0;
            m_uiBaltharusGUID = 0;
            m_uiCloneGUID = 0;
            m_uiHalionPortal1GUID = 0;
            m_uiHalionPortal2GUID = 0;
            m_uiHalionPortal3GUID = 0;
            m_uiXerestraszaGUID = 0;
            m_uiHalionFireWallSGUID = 0;
            m_uiHalionFireWallMGUID = 0;
            m_uiHalionFireWallLGUID = 0;
            m_uiBaltharusTargetGUID = 0;
            m_auiOrbDirection = 0;
            m_uiOrbNGUID = 0;
            m_uiOrbSGUID = 0;
            m_uiOrbFocusGUID = 0;
            m_auiOrbNState = NOT_STARTED;
            m_auiOrbSState = NOT_STARTED;
        }

        bool IsEncounterInProgress() const
        {
            for(uint8 i = 1; i < MAX_ENCOUNTERS ; ++i)
                if (m_auiEncounter[i] == IN_PROGRESS)
                    return true;

            return false;
        }

        void OpenDoor(uint64 guid)
        {
            if(!guid)
                return;

            GameObject* pGo = instance->GetGameObject(guid);
            if(pGo)
                pGo->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
        }

        void CloseDoor(uint64 guid)
        {
            if(!guid)
                return;

            GameObject* pGo = instance->GetGameObject(guid);
            if(pGo)
                pGo->SetGoState(GO_STATE_READY);
        }

        void OpenAllDoors()
        {
            if (m_auiEncounter[TYPE_RAGEFIRE] == DONE &&
                m_auiEncounter[TYPE_BALTHARUS] == DONE &&
                m_auiEncounter[TYPE_XERESTRASZA] == DONE)
                     OpenDoor(m_uiFlameWallsGUID);
            else CloseDoor(m_uiFlameWallsGUID);
        }

        void UpdateWorldState(bool command, uint32 value)
        {
           Map::PlayerList const &players = instance->GetPlayers();

           if (command)
           {
           for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
                  if(Player* player = i->getSource())
                        if(player->isAlive())
                        {
                            player->SendUpdateWorldState(UPDATE_STATE_UI_SHOW,0);
                            if (player->HasAura(74807))
                                player->SendUpdateWorldState(UPDATE_STATE_UI_COUNT_T, 100 - value);
                            else player->SendUpdateWorldState(UPDATE_STATE_UI_COUNT_R, value);
                            player->SendUpdateWorldState(UPDATE_STATE_UI_SHOW,1);
                        }
           }
           else
           {
           for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
                  if(Player* player = i->getSource())
                        if(player->isAlive())
                            player->SendUpdateWorldState(UPDATE_STATE_UI_SHOW,0);
           }
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch(creature->GetEntry())
            {
                case NPC_HALION_REAL:             m_uiHalion_pGUID = creature->GetGUID();        break;
                case NPC_HALION_TWILIGHT:         m_uiHalion_tGUID = creature->GetGUID();        break;
                case NPC_HALION_CONTROL:          m_uiHalionControlGUID = creature->GetGUID();   break;
                case NPC_RAGEFIRE:                m_uiRagefireGUID = creature->GetGUID();        break;
                case NPC_ZARITHIAN:               m_uiZarithianGUID = creature->GetGUID();       break;
                case NPC_BALTHARUS:               m_uiBaltharusGUID = creature->GetGUID();       break;
                case NPC_BALTHARUS_TARGET:        m_uiBaltharusTargetGUID = creature->GetGUID(); break;
                case NPC_CLONE:                   m_uiCloneGUID = creature->GetGUID();           break;
                case NPC_XERESTRASZA:             m_uiXerestraszaGUID = creature->GetGUID();     break;
                case NPC_SHADOW_PULSAR_N:         m_uiOrbNGUID = creature->GetGUID();            break;
                case NPC_SHADOW_PULSAR_S:         m_uiOrbSGUID = creature->GetGUID();            break;
                case NPC_ORB_ROTATION_FOCUS:      m_uiOrbFocusGUID = creature->GetGUID();        break;
                case NPC_ORB_CARRIER:             m_uiOrbCarrierGUID = creature->GetGUID();      break;
            }
        }

        void OnGameObjectCreate(GameObject* pGo)
        {
            switch(pGo->GetEntry())
            {
                case GO_HALION_PORTAL_1:  m_uiHalionPortal1GUID = pGo->GetGUID();  break;
                case GO_HALION_PORTAL_2:  m_uiHalionPortal2GUID = pGo->GetGUID();  break;
                case GO_HALION_PORTAL_3:  m_uiHalionPortal3GUID = pGo->GetGUID();  break;
                case GO_FLAME_WALLS:      m_uiFlameWallsGUID = pGo->GetGUID();     break;
                case GO_FLAME_RING:       m_uiFlameRingGUID = pGo->GetGUID();      break;
                case GO_FIRE_FIELD:       m_uiFireFieldGUID = pGo->GetGUID();      break;
            }
            OpenAllDoors();
        }

        void SetData(uint32 uiType, uint32 uiData)
        {
            switch(uiType)
            {
                case TYPE_EVENT:        m_auiEncounter[uiType] = uiData; uiData = NOT_STARTED; break;
                case TYPE_RAGEFIRE:     m_auiEncounter[uiType] = uiData;
                                           OpenAllDoors();
                                        break;
                case TYPE_BALTHARUS:    m_auiEncounter[uiType] = uiData;
                                           OpenAllDoors();
                                        break;
                case TYPE_XERESTRASZA:  m_auiEncounter[uiType] = uiData;
                                        if (uiData == IN_PROGRESS)
                                           OpenDoor(m_uiFireFieldGUID);
                                        else if (uiData == NOT_STARTED)
                                        {
                                           CloseDoor(m_uiFireFieldGUID);
                                           OpenAllDoors();
                                        }
                                        else if (uiData == DONE)
                                        {
                                           OpenAllDoors();
                                           if (m_auiEncounter[TYPE_ZARITHRIAN] == DONE)
                                           {
                                               m_auiEncounter[TYPE_EVENT] = 200;
                                               m_auiEventTimer = 30000;
                                           };
                                        }
                                        break;
                case TYPE_ZARITHRIAN:    m_auiEncounter[uiType] = uiData;
                                        if (uiData == DONE)
                                        {
                                           OpenDoor(m_uiFlameWallsGUID);
                                           m_auiEncounter[TYPE_EVENT] = 200;
                                           m_auiEventTimer = 30000;
                                        }
                                        else if (uiData == IN_PROGRESS)
                                           CloseDoor(m_uiFlameWallsGUID);
                                        else if (uiData == FAIL)
                                           OpenDoor(m_uiFlameWallsGUID);
                                        break;
                case TYPE_HALION:       m_auiEncounter[uiType] = uiData;
                                        if (uiData == IN_PROGRESS)
                                        {
                                            CloseDoor(m_uiFlameRingGUID);
                                        }
                                        else
                                        {
                                              OpenDoor(m_uiFlameRingGUID);
                                        }
                                        break;
                case TYPE_HALION_EVENT: m_auiHalionEvent  = uiData; uiData = NOT_STARTED; break;
                case TYPE_EVENT_TIMER:  m_auiEventTimer = uiData; uiData = NOT_STARTED;   break;

                case DATA_ORB_DIRECTION:        m_auiOrbDirection = uiData; uiData = NOT_STARTED; break;
                case DATA_ORB_N:                m_auiOrbNState = uiData; uiData = NOT_STARTED;    break;
                case DATA_ORB_S:                m_auiOrbSState = uiData; uiData = NOT_STARTED;    break;
                case TYPE_COUNTER:
                                       if (uiData == 0)
                                           UpdateWorldState(false,0);
                                       else UpdateWorldState(true,uiData);
                                       uiData = NOT_STARTED;
                                       break;
            }

            if (uiData == DONE)
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;

                for(uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
                    saveStream << m_auiEncounter[i] << " ";

                strSaveData = saveStream.str();

                SaveToDB();
                OUT_SAVE_INST_DATA_COMPLETE;
            }
        }

        std::string GetSaveData()
        {
            return strSaveData;
        }

        uint32 GetData(uint32 uiType)
        {
            switch(uiType)
            {
                case TYPE_RAGEFIRE:      return m_auiEncounter[uiType];
                case TYPE_BALTHARUS:     return m_auiEncounter[uiType];
                case TYPE_XERESTRASZA:   return m_auiEncounter[uiType];
                case TYPE_ZARITHRIAN:    return m_auiEncounter[uiType];
                case TYPE_HALION:        return m_auiEncounter[uiType];

                case TYPE_EVENT:         return m_auiEncounter[uiType];

                case TYPE_HALION_EVENT:  return m_auiHalionEvent;

                case TYPE_EVENT_TIMER:   return m_auiEventTimer;
                case TYPE_EVENT_NPC:     switch (m_auiEncounter[TYPE_EVENT])
                                         {
                                              case 10:
                                              case 20:
                                              case 30:
                                              case 40:
                                              case 50:
                                              case 60:
                                              case 70:
                                              case 80:
                                              case 90:
                                              case 100:
                                              case 110:
                                              case 200:
                                              case 210:
                                                     return NPC_XERESTRASZA;
                                                     break;
                                              default:
                                                     break;
                                         };
                                         return 0;

                case DATA_ORB_DIRECTION:        return m_auiOrbDirection;
                case DATA_ORB_N:                return m_auiOrbNState;
                case DATA_ORB_S:                return m_auiOrbSState;

            }
            return 0;
        }

        uint64 GetData64(uint32 uiData)
        {
            switch(uiData)
            {
                case NPC_BALTHARUS:        return m_uiBaltharusGUID;
                case NPC_CLONE:            return m_uiCloneGUID;
                case NPC_ZARITHIAN:        return m_uiZarithianGUID;
                case NPC_RAGEFIRE:         return m_uiRagefireGUID;
                case NPC_HALION_REAL:      return m_uiHalion_pGUID;
                case NPC_HALION_TWILIGHT:  return m_uiHalion_tGUID;
                case NPC_HALION_CONTROL:   return m_uiHalionControlGUID;
                case NPC_XERESTRASZA:      return m_uiXerestraszaGUID;
                case NPC_BALTHARUS_TARGET: return m_uiBaltharusTargetGUID;

                case GO_FLAME_WALLS: return m_uiFlameWallsGUID;
                case GO_FLAME_RING:  return m_uiFlameRingGUID;
                case GO_FIRE_FIELD:  return m_uiFireFieldGUID;

                case GO_HALION_PORTAL_1: return m_uiHalionPortal1GUID;
                case GO_HALION_PORTAL_2: return m_uiHalionPortal2GUID;
                case GO_HALION_PORTAL_3: return m_uiHalionPortal3GUID;

                case NPC_SHADOW_PULSAR_N:    return m_uiOrbNGUID;
                case NPC_SHADOW_PULSAR_S:    return m_uiOrbSGUID;
                case NPC_ORB_ROTATION_FOCUS: return m_uiOrbFocusGUID;
                case NPC_ORB_CARRIER:        return m_uiOrbCarrierGUID;
            }
            return 0;
        }

        void Load(const char* chrIn)
        {
            if (!chrIn)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(chrIn);

            std::istringstream loadStream(chrIn);

            for(uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
            {
                loadStream >> m_auiEncounter[i];

                if (m_auiEncounter[i] == IN_PROGRESS
                    || m_auiEncounter[i] == FAIL)
                    m_auiEncounter[i] = NOT_STARTED;
            }

            m_auiEncounter[TYPE_XERESTRASZA] = NOT_STARTED;

            OUT_LOAD_INST_DATA_COMPLETE;
            OpenAllDoors();
        }
    };
};

/*##############################
# npc_convocadora_carboescala (40417)
###############################*/

enum ConvocadoraSpells
{
    SPELL_AGOSTAR = 75412,
    SPELL_OLA_LLAMAS = 75413
};

class npc_convocadora_carboescala : public CreatureScript
{
public:
    npc_convocadora_carboescala() : CreatureScript("npc_convocadora_carboescala") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_convocadora_carboescalaAI(creature);
    }

    struct npc_convocadora_carboescalaAI : public ScriptedAI
    {
        npc_convocadora_carboescalaAI(Creature* creature) : ScriptedAI(creature)
             {
              }

        uint32 uiAgostarTimer;
        uint32 uiOlaTimer;


        void Reset()
        {
            uiAgostarTimer = 3000;
            uiOlaTimer = urand(8*IN_MILLISECONDS,13*IN_MILLISECONDS);
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            if (uiAgostarTimer <= uiDiff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0))
                {
                    if (target && target->isAlive())
                        DoCast(target, SPELL_AGOSTAR);
                }
                uiAgostarTimer = 8000;
            }else uiAgostarTimer -= uiDiff;

            if (uiOlaTimer <= uiDiff)
            {
                DoCast(me, SPELL_OLA_LLAMAS);
                uiOlaTimer = urand(8*IN_MILLISECONDS,13*IN_MILLISECONDS);
            }else uiOlaTimer -= uiDiff;

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* pKiller) { }
    };
};

/*##############################
# npc_acometedor_carboescala (40419)
###############################*/

enum AcometedorSpells
{
    SPELL_RAJAR = 15284,
    SPELL_OLA_CHOQUE = 75417
};

class npc_acometedor_carboescala : public CreatureScript
{
public:
    npc_acometedor_carboescala() : CreatureScript("npc_acometedor_carboescala") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_acometedor_carboescalaAI(creature);
    }

    struct npc_acometedor_carboescalaAI : public ScriptedAI
    {
        npc_acometedor_carboescalaAI(Creature* creature) : ScriptedAI(creature)
             {
              }

        uint32 uiRajarTimer;
        uint32 uiOlaChoqueTimer;


        void Reset()
        {
            uiRajarTimer = 5000;
            uiOlaChoqueTimer = 9000;
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            if (uiRajarTimer <= uiDiff)
            {
                DoCast(me->getVictim(), SPELL_RAJAR);
                uiRajarTimer = 11000;
            }else uiRajarTimer -= uiDiff;

            if (uiOlaChoqueTimer <= uiDiff)
            {
                DoCast(me, SPELL_OLA_CHOQUE);
                uiOlaChoqueTimer = 17000;
            }else uiOlaChoqueTimer -= uiDiff;

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* pKiller) { }
    };
};

/*##############################
# npc_elite_carboescala (40421)
###############################*/

enum EliteSpells
{
    SPELL_MACHACAR_CRANEOS = 15621
};

class npc_elite_carboescala : public CreatureScript
{
public:
    npc_elite_carboescala() : CreatureScript("npc_elite_carboescala") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_elite_carboescalaAI(creature);
    }

    struct npc_elite_carboescalaAI : public ScriptedAI
    {
        npc_elite_carboescalaAI(Creature* creature) : ScriptedAI(creature)
           {
              }

        uint32 uiMachaqueTimer;


        void Reset()
        {
            uiMachaqueTimer = 5000;
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            if (uiMachaqueTimer <= uiDiff)
            {
                DoCast(me->getVictim(), SPELL_MACHACAR_CRANEOS);
                            uiMachaqueTimer = 12000;
            }else uiMachaqueTimer -= uiDiff;

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* pKiller) { }
    };
};

/*##############################
# npc_comandante_carboescala (40423)
###############################*/

enum ComandanteSpells
{
    SPELL_GOLPE_MORTAL = 13737,
    SPELL_GRITO_CONVOCACION = 75414
};

class npc_comandante_carboescala : public CreatureScript
{
public:
    npc_comandante_carboescala() : CreatureScript("npc_comandante_carboescala") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_comandante_carboescalaAI(creature);
    }

    struct npc_comandante_carboescalaAI : public ScriptedAI
    {
        npc_comandante_carboescalaAI(Creature* creature) : ScriptedAI(creature)
           {
              }

        uint32 uiGolpeTimer;
        uint32 uiGritoTimer;


        void Reset()
        {
            uiGolpeTimer = 9000;
            uiGritoTimer = 1000;
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            if (uiGolpeTimer <= uiDiff)
            {
                DoCast(me->getVictim(), SPELL_GOLPE_MORTAL);
                           uiGolpeTimer = 9000;
            }else uiGolpeTimer -= uiDiff;

            if (uiGritoTimer <= uiDiff)
            {
                DoCast(me, SPELL_GRITO_CONVOCACION);
                uiGritoTimer = 100000;
            }else uiGritoTimer -= uiDiff;

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* pKiller) { }
    };
};

void AddSC_instance_ruby_sanctum_custom()
{
    new instance_ruby_sanctum_custom;
    new npc_convocadora_carboescala;
    new npc_acometedor_carboescala;
    new npc_elite_carboescala;
    new npc_comandante_carboescala;
}
