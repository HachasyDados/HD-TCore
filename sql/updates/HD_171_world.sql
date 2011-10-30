DELETE FROM `spell_script_names` WHERE spell_id IN (24706, 24973);
INSERT INTO `spell_script_names` VALUES
(24706, 'spell_toss_stinky_bomb'),
(24973, 'spell_clean_stinky_bomb');

DELETE FROM `spell_script_names` WHERE `spell_id`=44436;
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(44436, 'spell_gen_tricky_treat');

DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (42965,42966);
INSERT INTO `spell_linked_spell` (`spell_trigger`,`spell_effect`,`type`,`comment`) VALUES
(42965,42919,0, 'Hallows End - Tricky Treat'),
(42966,-42965,0, 'Hallows End - Upset Tummy removes Tricky Treat'),
(42966,-42919,0, 'Hallows End - Upset Tummy removes Tricky Treat');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=17 AND `SourceEntry`=44436;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`) VALUES
(17, 44436, 11, 42966);

DELETE FROM `gameobject` WHERE `id`=186267;
DELETE FROM `game_event_gameobject` WHERE `guid`=54947;
DELETE FROM `gameobject_questrelation` WHERE `id`=186267;

UPDATE `gameobject_template` SET `ScriptName`='go_pumpkin_shrine' WHERE `entry`=186267;
UPDATE `creature_template` SET `ScriptName`='npc_horseman_head' WHERE `entry`=23775;
UPDATE `creature_template` SET `flags_extra` = 130, `ScriptName` = 'npc_halloween_fire_summoner' WHERE `entry` = 23686;

-- heal body
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry`=43306;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`) VALUES
(13, 43306, 18, 1, 23682);

-- set lfg flag
UPDATE `quest_template` SET `SpecialFlags`=9 WHERE `entry`=25482;

-- temporary
UPDATE `creature_template` SET `ScriptName`='' WHERE `entry` IN (23686, 24034, 23694);

-- immunitys
UPDATE `creature_template` SET `mechanic_immune_mask`=`mechanic_immune_mask`|1|2|8|16|32|64|128|256|512|1024|2048|4096|8192|65536|131072|524288|4194304|8388608|33554432|67108864|536870912 WHERE `entry` IN (23682,23775);

-- loot
DELETE FROM `creature_loot_template` WHERE `entry`=23682 AND `item` IN (33154,33292,37012,49126,49128,37011);

DELETE FROM `item_loot_template` WHERE `entry`=54516;
INSERT INTO `item_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES
(54516,33154, 25,1,0, 1, 1),
(54516,33292, 33,1,0, 1, 1),
(54516,37012,  3,1,0, 1, 1),
(54516,49126,  5,1,0, 1, 1),
(54516,49128,  8,1,0, 1, 1),
(54516,37011, 25,1,0, 1, 1),
(54516,40753,100,1,0, 2, 2),
(54516,34068, 33,1,0, 3, 6),
(54516,33226,100,1,0,20,20);

-- spawn
DELETE FROM `creature` WHERE `id`=23682 and `guid`=303110;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(303110,'23682','189','1','1','0','0','1763.1','1347.73','17.5602','6.20833','60','0','0','126000','3994','0','0','0','0');

-- link spawn to Hallow's End event
DELETE FROM game_event_creature WHERE guid=303110;
INSERT INTO game_event_creature VALUES (12,303110);

DELETE FROM gameobject_questrelation WHERE quest IN (12345, 12377);
INSERT INTO gameobject_questrelation VALUES
(190035, 12345),
(190079, 12377);
DELETE FROM gameobject_involvedrelation WHERE quest IN (12345, 12377);
INSERT INTO gameobject_involvedrelation VALUES
(190035, 12345),
(190079, 12377);

SET @GO_GUID := 801056;
SET @CREATURE_GUID := 600680;

DELETE FROM `areatrigger_scripts` WHERE `entry` IN (3991);
INSERT INTO `areatrigger_scripts` VALUES
(3991, 'at_wickerman_festival');

UPDATE `gameobject_template` SET `flags` = 17 WHERE `entry` = 180433;
DELETE FROM gameobject WHERE id IN (180433, 180432, 180434, 180437,180406,180405) AND guid BETWEEN @GO_GUID+00 AND @GO_GUID+13;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@GO_GUID+00,180433,0,1,1,1734.04,504.05,42.2861,1.4131,0,0,0.649213,0.760607,300,0,0),
(@GO_GUID+01,180432,0,1,1,1749.28,507.611,39.2312,1.49635,0,0,0.680301,0.732933,300,0,1),
(@GO_GUID+02,180432,0,1,1,1712.63,507.05,38.2495,1.58824,0,0,0.713246,0.700914,300,0,1),
(@GO_GUID+03,180405,0,1,1,1746.07,517.066,38.936,2.83466,0,0,0.988247,0.152864,300,0,1),
(@GO_GUID+04,180406,0,1,1,1719.67,522.979,36.8828,2.93283,0,0,0.994557,0.10419,300,0,1),
(@GO_GUID+05,180405,0,1,1,1728,475.099,63.6779,3.08363,0,0,0.99958,0.0289791,300,0,1),
(@GO_GUID+06,180434,0,1,1,1758.89,513.276,35.8655,1.28897,0,0,0.600788,0.799409,300,0,1),
(@GO_GUID+07,180434,0,1,1,1704.48,518.689,35.4045,1.30704,0,0,0.607984,0.793949,300,0,1),
(@GO_GUID+08,180434,0,1,1,1739.78,473.238,61.6565,1.59371,0,0,0.71516,0.698961,300,0,1),
(@GO_GUID+09,180434,0,1,1,1717.32,472.723,61.6566,1.59371,0,0,0.71516,0.698961,300,0,1),
(@GO_GUID+10,180437,0,1,1,1744.62,504.954,40.8518,1.23403,0,0,0.578603,0.81561,300,0,1),
(@GO_GUID+11,180437,0,1,1,1729.13,510.378,40.8719,1.23403,0,0,0.578603,0.81561,300,0,1),
(@GO_GUID+12,180437,0,1,1,1721.77,503.938,41.1381,1.23403,0,0,0.578603,0.81561,300,0,1),
(@GO_GUID+13,180437,0,1,1,1744.96,496.25,41.44,1.24581,0,0,0.583397,0.812187,300,0,1);


DELETE FROM `creature` WHERE `id` IN (15195, 15197, 15199) AND `guid` BETWEEN @CREATURE_GUID+00 AND @CREATURE_GUID+04;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CREATURE_GUID+00,15195,0,1,1,0,0,1713.1,511.295,37.2005,1.48063,300,0,0,45780,0,0,0,0,0),
(@CREATURE_GUID+01,15195,0,1,1,0,0,1750.57,511.697,37.7587,1.25444,300,0,0,45780,0,0,0,0,0),
(@CREATURE_GUID+02,15195,0,1,1,0,0,1732.31,520.874,36.3326,1.30942,300,0,0,45780,0,0,0,0,0),
(@CREATURE_GUID+03,15197,0,1,1,0,0,1734.6,508.803,41.2847,1.6173,300,0,0,15260,0,0,0,0,0),
(@CREATURE_GUID+04,15199,0,1,1,0,0,-813.614,-547.184,15.6377,1.69193,300,0,0,15260,0,0,0,0,0);

DELETE FROM `game_event_gameobject` WHERE `guid` BETWEEN @GO_GUID+00 AND @GO_GUID+13;
INSERT INTO `game_event_gameobject` VALUES
(12, @GO_GUID+00),
(12, @GO_GUID+01),
(12, @GO_GUID+02),
(12, @GO_GUID+03),
(12, @GO_GUID+04),
(12, @GO_GUID+05),
(12, @GO_GUID+06),
(12, @GO_GUID+07),
(12, @GO_GUID+08),
(12, @GO_GUID+09),
(12, @GO_GUID+10),
(12, @GO_GUID+11),
(12, @GO_GUID+12),
(12, @GO_GUID+13);

DELETE FROM `game_event_creature` WHERE `guid` BETWEEN @CREATURE_GUID+00 AND @CREATURE_GUID+04;
INSERT INTO `game_event_creature` VALUES
(12, @CREATURE_GUID+00),
(12, @CREATURE_GUID+01),
(12, @CREATURE_GUID+02),
(12, @CREATURE_GUID+03),
(12, @CREATURE_GUID+04);

-- Wickerman Ashes
DELETE FROM `gossip_menu` WHERE `entry` = 6535;
INSERT INTO `gossip_menu` VALUES
(6535, 100);
DELETE FROM `npc_text` WHERE `ID` = 100;
INSERT INTO `npc_text`(`ID`, `text0_0`) VALUES
(100, 'Las cenizas del hombre de mimbre irradian poder mágico.');
UPDATE `gameobject_template` SET `faction` = 0, `ScriptName` = 'go_wickerman_ember' WHERE `entry` = 180437;

-- Wickerman Guardians
UPDATE `creature_template` SET `Armor_mod` = 2.6, `minlevel` = 80, `maxlevel` = 80, `mechanic_immune_mask` = 748240635 WHERE `entry` = 15195;

DELETE FROM `spell_script_names` WHERE spell_id IN (24720, 24717, 24718, 24719, 24737);
INSERT INTO `spell_script_names` VALUES
(24720, 'spell_halloween_wand'),
(24717, 'spell_halloween_wand'),
(24718, 'spell_halloween_wand'),
(24719, 'spell_halloween_wand'),
(24737, 'spell_halloween_wand');

SET @CREATURE_GUID := 600685;

UPDATE `item_template` SET `ScriptName` = 'item_water_bucket' WHERE `entry` = 32971;
UPDATE `creature_template` SET `ScriptName` = 'npc_halloween_fire' WHERE `entry` = 23537;

DELETE FROM `creature` WHERE `id` IN (23537,23686) AND `guid` BETWEEN @CREATURE_GUID+00 AND @CREATURE_GUID+12;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
-- Spawn fire dummys for fire effigys
(@CREATURE_GUID+00,23537,530,1,1,0,0,-4192.38,-12268.1,2.53389,-1.72788,300,0,0,45780,0,0,0,0,0),
(@CREATURE_GUID+01,23537,530,1,1,0,0,-4207.84,-12276.7,4.82085,-0.069813,300,0,0,45780,0,0,0,0,0),
(@CREATURE_GUID+02,23537,0,1,1,0,0,-5753.24,-533.652,405.022,1.15192,300,0,0,45780,0,0,0,0,0),
(@CREATURE_GUID+03,23537,0,1,1,0,0,-5761.17,-528.193,404.855,1.16937,300,0,0,15260,0,0,0,0,0),
(@CREATURE_GUID+04,23537,0,1,1,0,0,-5747.52,-527.634,401.297,0.610865,300,0,0,15260,0,0,0,0,0),
(@CREATURE_GUID+05,23537,1,1,1,0,0,286.565,-4561.45,28.5742,2.42601,300,0,0,15260,0,0,0,0,0),
(@CREATURE_GUID+06,23537,530,1,1,0,0,9235.05,-6783.4,26.4426,1.5708,300,0,0,15260,0,0,0,0,0),
(@CREATURE_GUID+07,23537,0,1,1,0,0,2240.44,459.159,39.2838,0.820305,300,0,0,15260,0,0,0,0,0),
(@CREATURE_GUID+08,23537,0,1,1,0,0,2239.49,487.861,38.3446,-0.715585,300,0,0,15260,0,0,0,0,0),
(@CREATURE_GUID+09,23537,0,1,1,0,0,-9328.25,56.2778,63.2509,2.60054,300,0,0,15260,0,0,0,0,0),
(@CREATURE_GUID+10,23537,0,1,1,0,0,-9314.1,52.4562,77.7343,2.93215,300,0,0,15260,0,0,0,0,0),
-- Spawn Fire Handlers for villages
(@CREATURE_GUID+11,23686,1,1,1,0,0,305.144,-4724.5,9.83766,3.68348,300,0,0,7185,7196,0,0,0,0),
(@CREATURE_GUID+12,23686,0,1,1,0,0,-9465.54,63.2228,55.8587,6.25841,300,0,0,7185,7196,0,0,0,0);

DELETE FROM `game_event_creature` WHERE `guid` BETWEEN @CREATURE_GUID+00 AND @CREATURE_GUID+12;
INSERT INTO `game_event_creature` VALUES
(12, @CREATURE_GUID+00),
(12, @CREATURE_GUID+01),
(12, @CREATURE_GUID+02),
(12, @CREATURE_GUID+03),
(12, @CREATURE_GUID+04),
(12, @CREATURE_GUID+05),
(12, @CREATURE_GUID+06),
(12, @CREATURE_GUID+07),
(12, @CREATURE_GUID+08),
(12, @CREATURE_GUID+09),
(12, @CREATURE_GUID+10),
(12, @CREATURE_GUID+11),
(12, @CREATURE_GUID+12);