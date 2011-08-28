DELETE FROM creature_ai_scripts WHERE creature_id=21838;
UPDATE creature_template SET AIName='', ScriptName='npc_terokk' WHERE entry=21838;
DELETE FROM `creature_text` WHERE `entry`=21838;
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(21838,0,0,'Who calls me to this world? The stars are not yet aligned...my powers fail me! You will pay for this!',14,0,0,0,0,0,'Terokk - Summoned & inCombat'),
(21838,1,0,'Show me how tough you are!',12,0,0,0,0,0,'Terokk - Player Chosen'),
(21838,2,0,'Kwa! You cannot kill me, I am immortal!',12,0,0,0,0,0,'Terokk - Immune');
DELETE FROM `creature_template` WHERE (`entry`=97016);
INSERT INTO `creature_template` VALUES (97016, 0, 0, 0, 0, 0, 17519, 11686, 0, 0, 'Terokk Visual Marker Trigger', '', '', 0, 80, 80, 0, 114, 114, 0, 1, 1.14286, 1, 0, 104, 138, 0, 252, 1, 2000, 0, 1, 33587968, 8, 0, 0, 0, 0, 0, 72, 106, 26, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 7, 1.35, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 130, '', 12340);
UPDATE creature_template SET modelid1=11686, modelid2=11686, modelid3=11686, modelid4=11686, npcflag=0, unit_flags=256|512|33554432, flags_extra=2 WHERE entry=97016;
