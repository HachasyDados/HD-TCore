// HyD Lottery Vendor

#include "ScriptPCH.h"

enum PossiblePrizes
{
    BS_BATTLELORD_PLATE_BOOTS = 45089,
    BS_BELT_OF_THE_TITANS = 45088,
    BS_INDEST_PLATE_GIRDLE = 45092,
    BS_PLATE_GIRDLE_RIGHTEOUSNESS = 45090,
    BS_SPIKED_DEATHDEALERS = 45093,
    BS_TREADS_OF_DESTINY = 45091,
    ENCHANT_W_BLADE_WARD = 46027,
    ENCHANT_W_BLOOD_DRAINING = 46348,
    LWK_BELT_OF_ARCTIC_LIFE = 45100,
    LWK_BELT_OF_DRAGONS = 45094,
    LWK_BLUE_BELT_OF_CHAOS = 45096,
    LWK_BOOTS_OF_LIVING_SCALE = 45095,
    LWK_BOOTS_OF_WINTRY_ENDURANCE = 45101,
    LWK_DEATH_WARMED_BELT = 45098,
    LWK_FOOTPADS_OF_SILENCE = 45099,
    LWK_LIGHTNING_GROUNDED_BOOTS = 45097,
    TAIL_CORD_OF_THE_WHITE_DAWN = 45104,
    TAIL_SASH_OF_ANCIENT_POWER = 45102,
    TAIL_SAVIORS_SLIPPERS = 45105,
    TAIL_SPELLSLINGERS_SLIPPERS = 45103
};

#define GOSSIPTEXT 537553

class npc_hyd_lottery : public CreatureScript
{
public:
    npc_hyd_lottery() : CreatureScript("npc_hyd_lottery") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            if (!player->HasItemCount(49426,1))
                return false;

            if (player->GetMoney() < 2000000)
                return false;

            if (player->getLevel() < 75)
                return false;

            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Comprar boleto para Herreros", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Comprar boleto para Encantadores", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Comprar boleto para Peleteros", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Comprar boleto para Sastres", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);

            player->SEND_GOSSIP_MENU(GOSSIPTEXT, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*uiSender*/, uint32 uiAction)
        {
            player->PlayerTalkClass->ClearMenus();
            player->DestroyItemCount(49426,1,true);
            player->ModifyMoney(-2000000);

            if (uiAction ==	GOSSIP_ACTION_INFO_DEF+1)
            {

                switch(urand(1,28))
                {
                    case 1: case 3: case 4: case 5: case 7: case 8: case 9: case 10: case 11: case 13: case 14:
                    case 15: case 16: case 17: case 19: case 20: case 21: case 22: case 24: case 26: case 27: case 28:
                        creature->MonsterWhisper("Vaya, este boleto no tiene premio. Yo en tu lugar lo intentaba de nuevo. Gracias por contribucir a la causa Goblin!", player->GetGUID());
                        break;
                    case 2:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(BS_BATTLELORD_PLATE_BOOTS,1);
                        break;
                    case 6:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(BS_BELT_OF_THE_TITANS,1);
                        break;
                    case 12:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(BS_INDEST_PLATE_GIRDLE,1);
                        break;
                    case 18:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(BS_PLATE_GIRDLE_RIGHTEOUSNESS,1);
                        break;
                    case 23:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(BS_SPIKED_DEATHDEALERS,1);
                        break;
                    case 25:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(BS_TREADS_OF_DESTINY,1);
                        break;
                }
                player->CLOSE_GOSSIP_MENU();
            }

            if (uiAction == GOSSIP_ACTION_INFO_DEF+2)
            {
                switch(urand(1,10))
                {
                    case 1: case 2: case 4: case 5: case 6: case 8: case 9: case 10:
                        creature->MonsterWhisper("Vaya, este boleto no tiene premio. Yo en tu lugar lo intentaba de nuevo. Gracias por contribucir a la causa Goblin!", player->GetGUID());
                        break;
                    case 3:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(ENCHANT_W_BLADE_WARD,1);
                        break;
                    case 7:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(ENCHANT_W_BLOOD_DRAINING,1);
                        break;
                }
                player->CLOSE_GOSSIP_MENU();
            }

            if (uiAction == GOSSIP_ACTION_INFO_DEF+3)
            {
                switch(urand(1,32))
                {
                    case 1: case 2: case 3: case 5: case 6: case 7: case 9: case 10:
                    case 11: case 13: case 14: case 15: case 17: case 18: case 19: case 21:
                    case 22: case 23: case 25: case 26: case 27: case 29: case 30: case 31:
                        creature->MonsterWhisper("Vaya, este boleto no tiene premio. Yo en tu lugar lo intentaba de nuevo. Gracias por contribucir a la causa Goblin!", player->GetGUID());
                        break;

                    case 4:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(LWK_BELT_OF_ARCTIC_LIFE,1);
                        break;

                    case 8:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(LWK_BELT_OF_DRAGONS,1);
                        break;

                    case 12:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(LWK_BLUE_BELT_OF_CHAOS,1);
                        break;

                    case 16:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(LWK_BOOTS_OF_LIVING_SCALE,1);
                        break;

                    case 20:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(LWK_BOOTS_OF_WINTRY_ENDURANCE,1);
                        break;

                    case 24:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(LWK_DEATH_WARMED_BELT,1);
                        break;

                    case 28:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(LWK_FOOTPADS_OF_SILENCE,1);
                        break;

                    case 32:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(LWK_LIGHTNING_GROUNDED_BOOTS,1);
                        break;
                }
                player->CLOSE_GOSSIP_MENU();
            }

            if (uiAction == GOSSIP_ACTION_INFO_DEF+4)
            {
                switch(urand(1,20))
                {
                    case 1: case 2: case 3: case 5: case 6: case 7: case 9: case 10: case 11:
                    case 13: case 14: case 15: case 17: case 18: case 19:
                        creature->MonsterWhisper("Vaya, este boleto no tiene premio. Yo en tu lugar lo intentaba de nuevo. Gracias por contribucir a la causa Goblin!", player->GetGUID());
                        break;

                    case 4:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(TAIL_CORD_OF_THE_WHITE_DAWN,1);
                        break;

                    case 8:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(TAIL_SASH_OF_ANCIENT_POWER,1);
                        break;

                    case 12:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(TAIL_SAVIORS_SLIPPERS,1);
                        break;

                    case 16:
                        creature->MonsterWhisper("Enhorabuena, has adquirido el boleto premiado!", player->GetGUID());
                        player->AddItem(TAIL_SPELLSLINGERS_SLIPPERS,1);
                        break;
                }
                player->CLOSE_GOSSIP_MENU();
            }
            return true;
        }
};

void AddSC_hyd_lottery()
{
    new npc_hyd_lottery();
}