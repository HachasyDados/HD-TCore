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
Name: wg_commandscript
%Complete: 100
Comment: All wg related commands
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "Chat.h"
#include "OutdoorPvPMgr.h"
#include "OutdoorPvPWG.h"

class wg_commandscript : public CommandScript
{
public:
    wg_commandscript() : CommandScript("wg_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand wgCommandTable[] =
        {
            { "status",         SEC_ADMINISTRATOR,  false, &HandleWgStatusCommand,             "", NULL },
            { "enable",         SEC_ADMINISTRATOR,  false, &HandleWgEnableCommand,             "", NULL },
            { "start",          SEC_ADMINISTRATOR,  false, &HandleWgStartCommand,              "", NULL },
            { "stop",           SEC_ADMINISTRATOR,  false, &HandleWgStopCommand,               "", NULL },
            { "switch",         SEC_ADMINISTRATOR,  false, &HandleWgSwitchCommand,             "", NULL },
            { "timer",          SEC_ADMINISTRATOR,  false, &HandleWgTimerCommand,              "", NULL },
            { NULL,             0,                  false, NULL,                               "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "wg",             SEC_ADMINISTRATOR,  false, NULL,                     "", wgCommandTable },
            { NULL,             0,                  false, NULL,                               "", NULL }
        };
        return commandTable;
    }

    static bool HandleWgStatusCommand(ChatHandler* handler, const char* /*args*/)
    {
        OutdoorPvPWG *pvpWG = (OutdoorPvPWG*)sOutdoorPvPMgr->GetOutdoorPvPToZoneId(4197);
        if (!pvpWG || !sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED))
        {
            handler->SendSysMessage(LANG_BG_WG_DISABLE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        handler->PSendSysMessage(LANG_BG_WG_STATUS, sObjectMgr->GetTrinityStringForDBCLocale(
            pvpWG->getDefenderTeam() == TEAM_ALLIANCE ? LANG_BG_AB_ALLY : LANG_BG_AB_HORDE),
            secsToTimeString(pvpWG->GetTimer(), true).c_str(),
            pvpWG->isWarTime() ? "Yes" : "No",
            pvpWG->GetNumPlayersH(),
            pvpWG->GetNumPlayersA());

        return true;
    }

    static bool HandleWgEnableCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        OutdoorPvPWG *pvpWG = (OutdoorPvPWG*)sOutdoorPvPMgr->GetOutdoorPvPToZoneId(4197);
        if (!pvpWG || !sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED))
        {
            handler->SendSysMessage(LANG_BG_WG_DISABLE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!strncmp(args, "on", 3))
        {
            if (!sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED))
            {
                pvpWG->forceStopBattle();
                sWorld->setBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED, true);
            }
            handler->PSendSysMessage(LANG_BG_WG_ENABLE);
            return true;
        }
        else if (!strncmp(args, "off", 4))
        {
            if (sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED))
            {
                pvpWG->forceStopBattle();
                sWorld->setBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED, false);
            }
            handler->PSendSysMessage(LANG_BG_WG_DISABLE);
            return true;
        }
        else
        {
            handler->SendSysMessage(LANG_USE_BOL);
            handler->SetSentErrorMessage(true);
            return false;
        }
    }

    static bool HandleWgStartCommand(ChatHandler* handler, const char* /*args*/)
    {
        OutdoorPvPWG *pvpWG = (OutdoorPvPWG*)sOutdoorPvPMgr->GetOutdoorPvPToZoneId(4197);
        if (!pvpWG || !sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED))
        {
            handler->SendSysMessage(LANG_BG_WG_DISABLE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        pvpWG->forceStartBattle();
        handler->PSendSysMessage(LANG_BG_WG_BATTLE_FORCE_START);

        return true;
    }

    static bool HandleWgStopCommand(ChatHandler* handler, const char* /*args*/)
    {
        OutdoorPvPWG *pvpWG = (OutdoorPvPWG*)sOutdoorPvPMgr->GetOutdoorPvPToZoneId(4197);
        if (!pvpWG || !sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED))
        {
            handler->SendSysMessage(LANG_BG_WG_DISABLE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        pvpWG->forceStopBattle();
        handler->PSendSysMessage(LANG_BG_WG_BATTLE_FORCE_STOP);

        return true;
    }

    static bool HandleWgSwitchCommand(ChatHandler* handler, const char* /*args*/)
    {
        OutdoorPvPWG *pvpWG = (OutdoorPvPWG*)sOutdoorPvPMgr->GetOutdoorPvPToZoneId(4197);
        if (!pvpWG || !sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED))
        {
            handler->SendSysMessage(LANG_BG_WG_DISABLE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        pvpWG->forceChangeTeam();
        pvpWG->setTimer(pvpWG->GetTimer());
        handler->PSendSysMessage(LANG_BG_WG_SWITCH_FACTION, handler->GetTrinityString(pvpWG->getDefenderTeam() == TEAM_ALLIANCE ? LANG_BG_AB_ALLY : LANG_BG_AB_HORDE));

        return true;
    }

    static bool HandleWgTimerCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        OutdoorPvPWG *pvpWG = (OutdoorPvPWG*)sOutdoorPvPMgr->GetOutdoorPvPToZoneId(4197);
        if (!pvpWG || !sWorld->getBoolConfig(CONFIG_OUTDOORPVP_WINTERGRASP_ENABLED))
        {
            handler->SendSysMessage(LANG_BG_WG_DISABLE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        int32 time = atoi (args);

        // Min value 1 min
        if (1 > time)
            time = 1;
        // Max value during wartime = 60. No wartime = 1440 (day)
        if (pvpWG->isWarTime())
        {
            if (60 < time)
                return false;
        }
        else if (1440 < time)
            return false;

        time *= MINUTE * IN_MILLISECONDS;
        pvpWG->setTimer((uint32)time);
        sWorld->SendWintergraspState(); // Update WG timer at player's bg tab
        handler->PSendSysMessage(LANG_BG_WG_CHANGE_TIMER, secsToTimeString(pvpWG->GetTimer(), true).c_str());

        return true;
    }
};

void AddSC_wg_commandscript()
{
    new wg_commandscript();
}
