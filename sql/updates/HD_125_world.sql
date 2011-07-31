-- Trigger para el item
DELETE FROM `creature_template` WHERE (`entry`=97019);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES (97019, 0, 0, 0, 0, 0, 17519, 11686, 0, 0, 'q12110 q12107 hyd trigger', '', '', 0, 80, 80, 0, 114, 114, 0, 1, 1.14286, 1, 0, 104, 138, 0, 252, 1, 2000, 0, 1, 33587968, 8, 0, 0, 0, 0, 0, 72, 106, 26, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 7, 1.35, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 130, '', 12340);

-- Spell Conditions
DELETE FROM conditions WHERE sourcetypeorreferenceid=13 AND sourceentry=47634;
INSERT INTO conditions (sourceTypeOrReferenceId, SourceEntry, ConditionTypeOrReference, conditionvalue1, conditionvalue2, conditionvalue3, errortextid, comment) VALUES
(13,47634,18,1,97019,0,0,'q12107 q12110 - item 36815 a trigger 97019');

-- IA del trigger
DELETE FROM smart_scripts WHERE entryorguid IN (97019);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(97019,0,0,0,8,0,100,0,47634,0,0,0,33,26887,0,0,0,0,0,7,0,0,0,0,0,0,0,'Trigger Q12107&12110 - On Spell Hit - KillCredit');

-- Spawn trigger
DELETE FROM creature WHERE id=97019;
INSERT INTO creature (guid, id, map, spawnMask, phaseMask, position_x, position_y, position_z, orientation, spawntimesecs) VALUES
(600121,97019,571,1,1,3058.174561,1395.285278,116.883369,1.799231,300);

-- Areatrigger for Sanctuary
DELETE FROM areatrigger_scripts WHERE entry=4956;
INSERT INTO areatrigger_scripts VALUES (4956,'at_azure_dragons_sanctuary');