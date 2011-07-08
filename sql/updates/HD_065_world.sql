-- NPC 97000 - q11796 trigger
DELETE FROM `creature_template` WHERE (`entry`=97000);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES (97000, 0, 0, 0, 0, 0, 17519, 11686, 0, 0, 'q11796 trigger', '', '', 0, 80, 80, 0, 114, 114, 0, 1, 1.14286, 1, 0, 104, 138, 0, 252, 1, 2000, 0, 1, 33587968, 8, 0, 0, 0, 0, 0, 72, 106, 26, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 7, 1.35, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 130, 'npc_q11796_trigger', 12340);

-- trigger spawns
DELETE FROM creature WHERE guid IN (3334440,3334441,3334442);
INSERT INTO creature (guid, id, map, spawnMask, phaseMask, position_x, position_y, position_z, orientation, spawntimesecs) VALUES
(3334440,97000,571,1,1,3604.6,5065,13.2919,5.39233,100),
(3334441,97000,571,1,1,3476.66,4918.67,13.8639,4.62499,100),
(3334442,97000,571,1,1,3355.87,5049.47,14.2951,6.05756,100);

-- spell conditions
DELETE FROM conditions WHERE sourcetypeorreferenceid=13 AND sourceentry=46171;
INSERT INTO conditions (sourceTypeOrReferenceId, SourceEntry, ConditionTypeOrReference, conditionvalue1, conditionvalue2, conditionvalue3, errortextid, comment) VALUES
(13,46171,18,1,97000,0,1335,'q11796 - antorcha limitada al trigger 97000');
