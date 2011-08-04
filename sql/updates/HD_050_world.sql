-- Captive Crocolisk ScriptName (Gossip)
UPDATE `creature_template` SET `ScriptName` = 'npc_captive_croco_gossip' WHERE `entry` = 28298;

-- Captive Crocolisk Stats (Vehicle)
DELETE FROM `creature_template` WHERE (`entry`=28308);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(28308, 0, 0, 0, 0, 0, 25107, 0, 0, 0, 'Captive Crocolisk', '', '', 0, 80, 80, 2, 2, 2, 0, 1, 2, 1, 1, 2, 2, 0, 24, 1, 2000, 0, 1, 16777472, 8, 6, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 115, 0, 0, '', 0, 3, 5, 1, 1, 0, 0, 0, 0, 0, 0, 0, 180, 1, 0, 0, 0, 'npc_captive_croco_vehicle', 12340);

-- QuestTaker Summoner (item)
UPDATE `quest_template` SET `SrcItemId` = '38512*' WHERE `entry` = 12536;
UPDATE `creature_template` SET `ScriptName` = 'npc_harkek_gossip' WHERE `entry` = 28138;
