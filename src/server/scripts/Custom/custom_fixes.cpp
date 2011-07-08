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

void AddSC_custom_fixes()
{
    new go_not_a_bug;
}