-- NPC 97001 - q13355 q13320 trigger
DELETE FROM `creature_template` WHERE (`entry`=97001);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES (97001, 0, 0, 0, 0, 0, 17519, 11686, 0, 0, 'q13355 q13320 trigger', '', '', 0, 80, 80, 0, 114, 114, 0, 1, 1.14286, 1, 0, 104, 138, 0, 252, 1, 2000, 0, 1, 33587968, 8, 0, 0, 0, 0, 0, 72, 106, 26, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 7, 1.35, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 130, 'npc_q13355_q13320_trigger', 12340);

-- trigger spawns
DELETE FROM creature WHERE guid IN (3334443,3334444,3334445);
INSERT INTO creature (guid, id, map, spawnMask, phaseMask, position_x, position_y, position_z, orientation, spawntimesecs) VALUES
(3334443,97001,571,1,1,7989.700195,2328.669922,484.492004,3.14159,100),
(3334444,97001,571,1,1,7998.149902,2366.790039,484.192993,3.14159,100),
(3334445,97001,571,1,1,8039.359863,2374.530029,484.931000,3.14159,100);

-- spell conditions
DELETE FROM conditions WHERE sourcetypeorreferenceid=13 AND sourceentry=60256;
INSERT INTO conditions (sourceTypeOrReferenceId, SourceEntry, ConditionTypeOrReference, conditionvalue1, conditionvalue2, conditionvalue3, errortextid, comment) VALUES
(13,60256,18,1,97001,0,1335,'q13355 q13320 - item 44251 a trigger 97001');
