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
SDName: GM Helper
SD%Complete: 100
SDComment: Script para determinadas acciones sobre observers
SDCategory: Custom Scripts
EndScriptData */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"



#define GOSSIP_ITEM_1   "Añadir Uniforme de GM"
#define GOSSIP_ITEM_2   "Nivel 80"
#define GOSSIP_ITEM_3   "Limpiar IDs de Instancias de nivel 80"

class npc_gm_helper : public CreatureScript
{
    public:

        npc_gm_helper()
            : CreatureScript("npc_gm_helper")
        {
        }
        CreatureAI* GetAI(Creature* creature) const
        {
            return new example_escortAI(creature);
        }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            player->PrepareGossipMenu(creature, 0);

                      if (player->isGameMaster)
                      {
                              player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                        }
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

                    player->AddItem(2586);
                                    player->AddItem(11508);
                                        player->AddItem(12064);

                    break;
                case GOSSIP_ACTION_INFO_DEF+2:
                    player->CLOSE_GOSSIP_MENU();

                    player->SetLevel(80);
                    break;
                case GOSSIP_ACTION_INFO_DEF+3:
                    player->CLOSE_GOSSIP_MENU();

                    if (pEscortAI)
                        pEscortAI->Start(false, true, player->GetGUID());
                    break;
                default:
                    return false;                                   // nothing defined      -> trinity core handling
            }

            return true;                                            // no default handling  -> prevent trinity core handling
        }
};

void AddSC_npc_gm_helper()
{
    new npc_gm_helper();
}
