/* QUEST: Jack likes his drink

QUEST DESCRIPTION:
In this quest you are supoused to birbe a waitress (Olga) and make her give Jack Adams an "extra-strong" drink,
Jack gets hammered when drinking it and then you are able to get his debt with Taruk (the quest giver).

SUMMARY:
The script is launched when the money box from gossip option 9014 is accepted. Then the script is fully
handled by Olga, forcing Jack to do the necessary actions.

PROBLEMS:
Gossip menu ids are guessed.
Text of gossip menu option when Jack lies on the ground is guessed.
When Jack vomits he should start the dead animation and remain in the floor for a while;
in the script Jack vomits while dancing and then directly switch to the death state,with no animation.
This last problem might be solved using an emote, but no idea wich one to use.
See InLine comments for more info.

http://www.wowhead.com/quest=11466
http://www.youtube.com/watch?v=fk6gbalyNr4
http://www.wowwiki.com/Quest%3AJack_Likes_His_Drink
*/

SET @NPC_OLGA          := 24639;
SET @NPC_JACK          := 24788;
SET @GOSSIP_OLGA_1     := 9015; -- Already on DB
SET @GOSSIP_OLGA_2     := 9014; -- Guessed
SET @GOSSIP_JACK       := 9013; -- Guessed
SET @SPELL_VOMIT       := 43391;
SET @SPELL_FEIGN_DEATH := 58806; -- This one sux,we need one that plays the animation of falling into ground. Emote?
SET @QUEST_JACK_LIKES  := 11466;
SET @ITEM_JACK_DEBT    := 34116;

-- Set Jack Adams permanent dance state
DELETE FROM `creature_template_addon` WHERE (`entry`=@NPC_JACK );
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(@NPC_JACK ,0,0,0,4097,10,'');

-- Link gossip texts (texts already on DB)
UPDATE `creature_template` SET `gossip_menu_id` = @GOSSIP_JACK WHERE `entry` = @NPC_JACK;
DELETE FROM `gossip_menu` WHERE `entry` IN (@GOSSIP_OLGA_2,@GOSSIP_JACK);
INSERT INTO `gossip_menu` VALUES
(@GOSSIP_OLGA_2,12180),
(@GOSSIP_JACK,12178);

-- Gossip menu options
DELETE FROM `gossip_menu_option` WHERE `menu_id` IN (@GOSSIP_OLGA_1,@GOSSIP_OLGA_2,@GOSSIP_JACK);
INSERT INTO `gossip_menu_option` (`menu_id`,`id`,`option_icon`,`option_text`,`option_id`,`npc_option_npcflag`,`action_menu_id`,`action_poi_id`,`box_coded`,`box_money`,`box_text`) VALUES
(@GOSSIP_OLGA_1,0,0,'I\'d like to buy Jack a drink. Perhaps something... extra strong.',1,1,9014,0,0,0,NULL),
(@GOSSIP_OLGA_2,0,0,'Here\'s a gold,buy yourself something nice.',1,1,0,0,0,10000,'Do you really want to bribe Olga?'),
(@GOSSIP_JACK,0,0,'<Search in Jack Adams pockets for Taruk\' payment.>',1,1,0,0,0,0,NULL); -- Guessed text

-- Texts for Olga and Jack
DELETE FROM `creature_text` WHERE `entry` IN (@NPC_OLGA,@NPC_JACK);
INSERT INTO `creature_text` (`entry`,`groupid`,`id`,`text`,`type`,`language`,`probability`,`emote`,`duration`,`sound`,`comment`) VALUES
(@NPC_OLGA,0,0,'Keep quiet,will you? If anyone catches on,we\'re both dead.',15,0,100,0,0,0,"Olga Whisper 01"),
(@NPC_OLGA,1,0,'All right,fellas! Who ordered the spiced rum? Was it you,Jackie boy?',12,0,0,0,0,0,"Olga Say 01"),
(@NPC_OLGA,2,0,'It\'s okay,sweetheart. This one\'s on the house.',12,0,0,0,0,0,"Olga Say 02"),
(@NPC_JACK,0,0,'Sure thing,love. Put it on Harry\'s tab,will ya? He owes me a drink!',12,0,0,0,0,0,"Jack Say 01"),
(@NPC_JACK,1,0,'Free rum? Why... that\s me favorite kind!',12,0,0,16,0,0,"Jack Say 02"),
(@NPC_JACK,2,0,'Sweet Neptulon! That was... one drink... too many!',12,0,0,0,0,0,"Jack Say 03"),
(@NPC_JACK,3,0,'What are you lot looking at? Pour me another drink!',12,0,0,0,0,0,"Jack Say 04");

-- Quest script
UPDATE `creature_template` SET `AIName` = 'SmartAI' WHERE `entry` IN (@NPC_OLGA,@NPC_JACK);
DELETE FROM `smart_scripts` WHERE (`entryorguid` IN (@NPC_OLGA,@NPC_JACK) AND `source_type`=0);
DELETE FROM `smart_scripts` WHERE (`entryorguid`=@NPC_OLGA*100 AND `source_type`=9);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@NPC_JACK,0,0,0,62,0,100,0,@GOSSIP_JACK,0,0,0,56,@ITEM_JACK_DEBT,1,0,0,0,0,7,0,0,0,0,0,0,0,"Jack Adams - Give Jack Adams Debt"),
(@NPC_JACK,0,1,0,62,0,100,0,@GOSSIP_JACK,0,0,0,72,0,0,0,0,0,0,7,0,0,0,0,0,0,0,'Jack Adams - Close Gossip'),
(@NPC_OLGA,0,0,1,62,0,100,0,9014,0,0,0,83,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Olga,the Scalawag Wench - Remove Gossip Flag"),
(@NPC_OLGA,0,1,2,61,0,100,0,0,0,0,0,1,0,0,0,0,0,0,7,0,0,0,0,0,0,0,"Olga,the Scalawag Wench - Whisper to player"),
(@NPC_OLGA,0,2,0,61,0,100,0,0,0,0,0,80,2463900,0,0,0,0,0,1,0,0,0,0,0,0,0,"Olga,the Scalawag Wench - Call timed event list"),
(@NPC_OLGA*100,9,0,0,0,0,100,1,0,0,0,0,59,0,0,0,0,0,0,1,0,0,0,0,0,0,0,"Olga,the Scalawag Wench - Make her walk"),
(@NPC_OLGA*100,9,1,0,0,0,100,1,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-89.95,-3539.48,7.71437,5.05535,"Olga,the Scalawag Wench - Move point 1"),
(@NPC_OLGA*100,9,2,0,0,0,100,1,3000,3000,0,0,69,0,0,0,0,0,0,8,0,0,0,-87.1169,-3544.68,7.71665,0.29741,"Olga,the Scalawag Wench - Move point 2"),
(@NPC_OLGA*100,9,3,0,0,0,100,1,2500,2500,0,0,66,0,0,0,0,0,0,19,@NPC_JACK,0,0,0,0,0,0,"Olga,the Scalawag Wench - Face Jack"),
(@NPC_OLGA*100,9,4,0,0,0,100,1,500,500,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Olga,the Scalawag Wench - Say 1"),
(@NPC_OLGA*100,9,5,0,0,0,100,1,5000,5000,0,0,84,0,0,0,0,0,0,11,@NPC_JACK,5,0,0,0,0,0,"Jack Adams - Say 1"),
(@NPC_OLGA*100,9,6,0,0,0,100,1,5000,5000,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,"Olga,the Scalawag Wench - Say 2"),
(@NPC_OLGA*100,9,7,0,0,0,100,1,5000,5000,0,0,84,1,0,0,0,0,0,11,@NPC_JACK,5,0,0,0,0,0,"Jack Adams - Say 2"),
(@NPC_OLGA*100,9,8,0,0,0,100,1,2800,2800,0,0,5,92,0,0,0,0,0,11,@NPC_JACK,5,0,0,0,0,0,"Jack Adams - Emote drink"),
(@NPC_OLGA*100,9,9,0,0,0,100,1,500,500,0,0,84,2,0,0,0,0,0,11,@NPC_JACK,5,0,0,0,0,0,"Jack Adams - Say 3"),
(@NPC_OLGA*100,9,10,0,0,0,100,1,5000,5000,0,0,86,@SPELL_VOMIT,1,11,@NPC_JACK,5,0,1,0,0,0,0,0,0,0,"Jack Adams - Cast Vomit"),
(@NPC_OLGA*100,9,11,0,0,0,100,1,3000,3000,0,0,81,1,0,0,0,0,0,11,@NPC_JACK,5,0,0,0,0,0,"Jack Adams - Add gossip flag"),
(@NPC_OLGA*100,9,12,0,0,0,100,1,0,0,0,0,86,58806,1,11,@NPC_JACK,5,0,1,0,0,0,0,0,0,0,"Jack Adams - Cast Feign death"),
(@NPC_OLGA*100,9,13,0,0,0,100,1,0,0,0,0,18,262144,0,0,0,0,0,11,@NPC_JACK,5,0,0,0,0,0,"Jack Adams - Add Stunned flag (prevents turning on gossip hello)"),
(@NPC_OLGA*100,9,14,0,0,0,100,1,0,0,0,0,5,11,0,0,0,0,0,11,24642,5,0,0,0,0,0,"Olga,the Scalawag Wench - Near pirates laughs..."),
(@NPC_OLGA*100,9,21,0,0,0,100,1,0,0,0,0,69,0,0,0,0,0,0,8,0,0,0,-91.8194,-3532.71,7.7126,0,"Olga,the Scalawag Wench - Back to home"),
(@NPC_OLGA*100,9,22,0,0,0,100,1,6000,6000,0,0,66,0,0,0,0,0,0,8,0,0,0,0,0,0,5.07891,"Olga,the Scalawag Wench - Restore orientation"),
(@NPC_OLGA*100,9,23,0,0,0,100,1,35000,40000,0,0,81,1,0,0,0,0,0,1,0,0,0,0,0,0,0,"Olga,the Scalawag Wench - Restore gossip flag"),
(@NPC_OLGA*100,9,24,0,0,0,100,1,0,0,0,0,81,0,0,0,0,0,0,11,@NPC_JACK,20,0,0,0,0,0,"Jack Adams - Remove gossip flag"),
(@NPC_OLGA*100,9,25,0,0,0,100,1,0,0,0,0,1,3,0,0,0,0,0,11,@NPC_JACK,20,0,0,0,0,0,"Jack Adams - Say 4 (on restore)"),
(@NPC_OLGA*100,9,26,0,0,0,100,1,0,0,0,0,28,58806,0,0,0,0,0,11,@NPC_JACK,20,0,0,0,0,0,"Jack Adams - Remove lied state"),
(@NPC_OLGA*100,9,27,0,0,0,100,1,0,0,0,0,19,262144,0,0,0,0,0,11,@NPC_JACK,20,0,0,0,0,0,"Jack Adams - Remove stunned flag");

-- Conditions
DELETE FROM `conditions` WHERE (SourceTypeOrReferenceId = 15 AND SourceGroup IN (@GOSSIP_OLGA_1,@GOSSIP_JACK));
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(15,@GOSSIP_OLGA_1,0,0,9,@QUEST_JACK_LIKES,0,0,0,'',"Olga,the Scalawag Wench - Show Birbe option only if player is in @QUEST_JACK_LIKES"),
(15,@GOSSIP_JACK,0,0,9,@QUEST_JACK_LIKES,0,0,0,'',"Jack Adams - Show steal option only if player is in @QUEST_JACK_LIKES");