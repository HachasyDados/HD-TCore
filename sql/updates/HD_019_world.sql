-- Apothecary trio
DELETE FROM `creature` WHERE `id`IN (36296, 36565, 36272);
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(1400000, 36296, 33, 1, 1, 0, 0, -207.728, 2216.46, 79.7624, 5.01826, 604800, 0, 0, 269620, 0, 0, 0, 0, 0, 0),
(1400001, 36565, 33, 1, 1, 0, 0, -209.865, 2213.18, 79.763, 5.01826, 604800, 0, 0, 269620, 0, 0, 0, 0, 0, 0),
(1400002, 36272, 33, 1, 1, 0, 0, -204.071, 2215.01, 79.763, 5.01826, 604800, 0, 0, 269620, 0, 0, 0, 0, 0, 0);

DELETE FROM `game_event_creature` WHERE `guid`IN (1400000, 1400001, 1400002);
INSERT INTO `game_event_creature` (`guid`,`event`) VALUES
(1400000, 8),
(1400001, 8),
(1400002, 8);

UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `Health_mod` = 86.189, `lootid` = 36296, `mechanic_immune_mask` = 650854235, `ScriptName` = 'npc_apothecary_hummel' WHERE `entry` = 36296;
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `Health_mod` = 86.189, `lootid` = 36296, `mechanic_immune_mask` = 650854235, `ScriptName` = 'npc_apothecary_baxter' WHERE `entry` = 36565;
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16, `Health_mod` = 86.189, `lootid` = 36296, `equipment_id` = 128, `mechanic_immune_mask` = 536870917, `flags_extra` = 256, `ScriptName` = 'npc_apothecary_frye' WHERE `entry` = 36272;

DELETE FROM `creature_loot_template` WHERE entry = 36296;
INSERT INTO `creature_loot_template` VALUES
(36296, 51808, 0, 1, 1, 1, 1),
(36296, 51805, 0, 1, 1, 1, 1),
(36296, 51804, 0, 1, 1, 1, 1),
(36296, 51806, 0, 1, 1, 1, 1),
(36296, 51807, 0, 1, 1, 1, 1),
(36296, 1, 10, 1, 1, -36296, 1),
(36296, 50250, 0.5, 0, 1, 1, 1);

DELETE FROM `reference_loot_template` WHERE entry = 36296;
INSERT INTO `reference_loot_template` VALUES
(36296, 50471, 0, 1, 1, 1, 1),
(36296, 50741, 0, 1, 1, 1, 1),
(36296, 49715, 0, 1, 1, 1, 1),
(36296, 50446, 0, 1, 1, 1, 1);
