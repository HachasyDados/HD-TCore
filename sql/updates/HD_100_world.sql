-- The event is handled by the female vrykul
UPDATE `creature_template` SET `ScriptName` = 'npc_ancient_vrykul' WHERE `entry` = 24315;
-- Lich King extra event
UPDATE `creature_template` SET `ScriptName` = 'npc_lich_king_hfjord' WHERE `entry` = 24248;
-- Make Valkyr's fly and react passive (See SAI below)
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` = 24327;
-- All involved creatures here are inattackable
UPDATE `creature_template` SET `unit_flags` = 2 WHERE `entry` IN (24314, 24315, 24248, 24327);

-- Make Female Ancient Valkyr sit down
DELETE FROM `creature_template_addon` WHERE (`entry`=24315);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (24315, 0, 0, 1, 0, 0, '');

-- Valkyr SAI
DELETE FROM `smart_scripts` WHERE (`entryorguid`=24327 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(24327, 0, 1, 0, 61, 0, 100, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Valkyr - Passive'),
(24327, 0, 0, 1, 25, 0, 100, 0, 0, 0, 0, 0, 60, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Valkyr - Fly');

-- AreaTrigger (LoS for Vrykul handler not working. why??)
DELETE FROM `areatrigger_scripts` WHERE `entry` = 4778;
INSERT INTO `areatrigger_scripts` VALUES
(4778, 'at_ymiron_house');

-- Vrykul Texts
DELETE FROM `script_texts`  WHERE `entry` BETWEEN -1002026 AND -1002011;
INSERT INTO `script_texts` (entry, content_default, TYPE, emote) VALUES
(-1002011, 'So then we too are cursed?', 0, 1),
(-1002012, 'Ancient Male Vrykul points to the infant.', 2, 25),
(-1002013, 'Ancient Female Vrykul sobs.', 2, 18),
(-1002014, 'The gods have forsaken us! We must dispose of it before Ymiron is notified!', 0, 1),
(-1002015, 'NO! You cannot! I beg of you! It is our child!', 0, 1),
(-1002016, 'Then what are we to do, wife? The others cannot find out. Should they learn of this aberration, we will all be executed.', 0, 6),
(-1002017, 'I... I will hide it. I will hide it until I find it a home, far away from here...', 0, 1),
-- LichKing texts
(-1002018, 'The Lich King turns to face you.', 2, 0),
(-1002019, 'The Lich King grins.', 2, 0),
(-1002020, 'Shamanism has brought you here... Its scent permeates the air. *The Lich King laughs* I was once a shaman.', 0, 1),
(-1002021, 'Shall we prepare it for you, my lord?', 0, 1),
(-1002022, 'No, minion. This one is not ready.', 0, 1),
(-1002023, 'Do you feel it, mortal? Death seeps through me, enveloping all that I touch. With just a snap of my finger your soul will languish in damnation for all eternity.', 0, 1),
(-1002024, 'But... It is not yet your time to serve the Lich King. Yes, a greater destiny awaits you. Power... You must become more powerful before you are to serve me.', 0, 1),
(-1002026, 'Now watch, val\'kyr. Observe as I apply pressure. Can you see that it is not yet ripe? Watch as it pops and falls lifeless to the floor.', 0, 1);

-- Spawns
-- Creature
SET @CreatureGUID := 202300;

DELETE FROM creature WHERE id IN(24314, 24315, 24248, 24327);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) values
(@CreatureGUID+0, 24314, 571, 1, 2, 0, 0, 1070.78, -5029.16, 9.80087, 4.93592, 300, 0, 0, 5158, 0, 0, 0, 0, 0, 0),
(@CreatureGUID+1, 24315, 571, 1, 2, 0, 0, 1073.62, -5032.9, 9.88443, 3.24653, 300, 0, 0, 5158, 0, 0, 0, 0, 0, 0),
(@CreatureGUID+2, 24248, 571, 1, 2, 0, 0, 1061.16, -4915.53, 11.3146, 3.29914, 300, 0, 0, 27890000, 0, 0, 0, 0, 0, 0),
(@CreatureGUID+3, 24327, 571, 1, 2, 0, 0, 1064.48, -4907.72, 17.2031, 3.56383, 300, 0, 0, 9610, 0, 0, 0, 0, 0, 0),
(@CreatureGUID+4, 24327, 571, 1, 2, 0, 0, 1069, -4921.13, 17.2031, 3.41617, 300, 0, 0, 9610, 0, 0, 0, 0, 0, 0);

SET @GUID_GO := 153200;

DELETE FROM `gameobject` WHERE `id`=186664;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(@GUID_GO, 186664, 571, 1, 2, 1071.62, -5033.12, 9.88719, 4.8566, 0, 0, 0.654328, -0.756211, 300, 0, 1);
