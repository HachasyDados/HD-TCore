/* QUEST: The Mosswalker Savior (12580)
http://www.wowhead.com/quest=12580
http://www.youtube.com/watch?v=15m-I07uRmY */

SET @ENTRY  := 28113;
SET @GOSSIP := 9728; -- Already on DB
SET @QUEST  := 12580;
-- Update flags. Removed NOT_SELECTABLE and added STUNED (avoids turning when talking with him)
UPDATE `creature_template` SET `unit_flags` = 262912,`AIName` = 'SmartAI' WHERE `entry` = @ENTRY;

-- Set movement to IDLE for current spawns (currently they're in RANDOM)
UPDATE `creature` SET `MovementType` = 0 WHERE `id` = @ENTRY;

-- Aura for Feing Death,we need to remove the DeathState if player manages to save the Mosswalker,so it's easier to remove an aura
DELETE FROM `creature_template_addon` WHERE (`entry`=@ENTRY);
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES (@ENTRY,0,0,0,0,0,'58806 0 58806 1');

-- Add gossip menu option
DELETE FROM `gossip_menu_option` WHERE `menu_id` = @GOSSIP;
INSERT INTO `gossip_menu_option` (`menu_id`,`option_text`,`option_id`,`npc_option_npcflag`) VALUES
(@GOSSIP,'<Check for the pulse...>',1,1);

-- Texts
DELETE FROM `creature_text` WHERE `entry` = @ENTRY;
INSERT INTO `creature_text` VALUES
(@ENTRY,2,0,'I do something bad? I sorry....',12,0,100,0,0,0,"Mosswalker Victim - Say Fail 1"),
(@ENTRY,2,1,'Use my shinies...make weather good again...make undead things go away.',12,0,100,0,0,0,"Mosswalker Victim - Say Fail 2"),
(@ENTRY,2,2,'We gave shinies to shrine... we not greedy... why this happen?',12,0,100,0,0,0,"Mosswalker Victim - Say Fail 3"),
(@ENTRY,2,3,'Thank...you.',12,0,100,0,0,0,"Mosswalker Victim - Say Fail 4"),
(@ENTRY,2,4,'We not do anything... to them... I no understand.',12,0,100,0,0,0,"Mosswalker Victim - Say Fail 5"),
(@ENTRY,1,0,'Thank you! You good!',12,0,100,0,0,0,"Mosswalker Victim - Say Save 1"),
(@ENTRY,1,1,'Maybe you make weather better too?',12,0,100,0,0,0,"Mosswalker Victim - Say Save 2"),
(@ENTRY,1,2,'Help more mosswalkers,okay?',12,0,100,0,0,0,"Mosswalker Victim - Say Save 1"),
(@ENTRY,1,3,'You save us! Yay for you!',12,0,100,0,0,0,"Mosswalker Victim - Say Save 1");

/* SmartScript of Mosswaalker Victim calls a random timed action action list when gossip selected.
@ENTRY*100+0 contains script for unsuccessful saving, @ENTRY*100+1 contains the script for the successful save*/
DELETE FROM `smart_scripts` WHERE (`entryorguid` IN (@ENTRY*100,@ENTRY*100+1) AND `source_type`=9);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=@ENTRY AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,0,0,1,62,0,100,1,@GOSSIP,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mosswalker Victim - Remove gossip"),
(@ENTRY,0,1,2,61,0,100,1,0,0,0,0,87,@ENTRY*100+0,@ENTRY*100+0,@ENTRY*100+0,@ENTRY*100+1,@ENTRY*100+1,0,1,0,0,0,0,0,0,0,"Mosswalker Victim - Randomize save chance(40%)"),
(@ENTRY,0,2,0,61,0,100,1,0,0,0,0,41,5000,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mosswalker Victim - Set timed despawn"),
(@ENTRY*100+0,9,0,0,0,0,100,1,750,750,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mosswalker Victim - Save FAIL - Say"),
(@ENTRY*100+1,9,0,0,0,0,100,1,1000,1000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mosswalker Victim - Save OK - Say"),
(@ENTRY*100+1,9,1,0,0,0,100,1,0,0,0,0,33,28644,0,0,0,0,0,7,0,0,0,0,0,0,0,"Mosswalker Victim - Save OK - KillCredit"),
(@ENTRY*100+1,9,2,0,0,0,100,1,0,0,0,0,28,58806,0,0,0,0,0,1,0,0,0,0,0,0,0,"Mosswalker Victim - Save OK - Remove feing death state");

-- Conditions for the Gossip Menu Option (Show only if quest is incomplete in log)
DELETE FROM `conditions` WHERE (SourceTypeOrReferenceId = 15 AND SourceGroup = @GOSSIP);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(15,@GOSSIP,0,0,9,@QUEST,0,0,0,'',"Mosswalker victim - Show only pulse option if player has quest The Mosswalker Savior");