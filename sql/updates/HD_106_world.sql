-- Texts
DELETE FROM `script_texts` WHERE `entry` BETWEEN -1002038 AND -1002030;
INSERT INTO `script_texts` (entry, content_default, TYPE, emote) VALUES
(-1002030, 'Stay close to me, $N. I could not bear for any harm to come to you.', 0, 1),
(-1002031, 'MALYGOS!!', 1, 1),
(-1002032, 'Come, Lord of Magic, and recover your precious consort...', 1, 1),
(-1002033, '...what remains of her!', 1, 1),
(-1002034, 'Come, $N. Let us see the fruits of our efforts.', 0, 1),
(-1002035, 'Saragosa! What has become of you?', 1, 1),
(-1002036, 'Hurry, $N! Flee! Live to finish what we\'ve begun here....', 0, 1),
(-1002037, 'Keristrasza! You\'ve bested my consort... and now YOU shall take her place!', 1, 1),
(-1002038, 'Never!', 1, 1);

-- Script names
UPDATE `creature_template` SET `ScriptName` = 'npc_keristrasza_coldarra' WHERE `entry` = 26237;
UPDATE `creature_template` SET `ScriptName` = 'npc_signal_fire' WHERE `entry` = 33087;
UPDATE `creature_template` SET `InhabitType` = 5 WHERE `entry` IN (26237,26310);
UPDATE `creature_template` SET `flags_extra` = 128 WHERE `entry` = 33087;

-- Spell required target
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 13 AND `SourceEntry` = 44550;
INSERT INTO `conditions` VALUES
(13, 0, 62272, 0, 18, 1, 33087, 0, 0, '', (NULL));

-- Make Corpse of Saragosa look dead
DELETE FROM `creature_template_addon` WHERE (`entry`=26299);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (26299, 0, 0, 7, 0, 65, '');

-- Spawns
DELETE FROM `creature` WHERE `id`=33087;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(250050, 33087, 571, 1, 1, 0, 0, 4055.08, 7103.51, 169.522, 3.75432, 300, 0, 0, 42, 0, 0, 0, 0, 0, 0);

DELETE FROM `gameobject` WHERE `id`=194151;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(177960, 194151, 571, 1, 1, 4055.08, 7103.51, 169.522, 3.75432, 0, 0, 0.953436, -0.301594, 300, 0, 1);
