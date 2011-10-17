-- Faction template for Tartek
UPDATE `creature_template` SET `faction_A` = 14, `faction_H` = 14 WHERE `entry` = 28105;

/* Mount for Tartek, we should also add it for summoning on Tartek AI Agrro
and convert EventAI to SmartAI, but couldn't find the mount correct NPC*/
DELETE FROM `creature_template_addon` WHERE (`entry`=28105);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (28105, 0, 28044, 0, 0, 0, '');

-- Invisible trap for checking the conditions of summoning
DELETE FROM `gameobject_template` WHERE (`entry`=190577);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `AIName`, `ScriptName`, `WDBVerified`) VALUES (190577, 6, 0, 'Mistwhisper Treasure', '', '', '', 35, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 'go_mistwhisper_treasure', 11723);

-- Spawn for invisible trap, linked trap not working, Why?
DELETE FROM `gameobject` WHERE `id`=190577;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(1098451, 190577, 571, 1, 1, 6713.84, 5124.42, -18.9935, 2.04098, 0, 0, 0.852363, 0.52295, 300, 0, 1);