DELETE FROM areatrigger_scripts WHERE entry=4548;
INSERT INTO areatrigger_scripts VALUES (4548,'at_legion_hold_smvalley');

UPDATE `creature_template` SET `AIName`= 'SmartAI' WHERE `entry`=21633;
DELETE FROM `smart_scripts` WHERE `entryorguid` IN (21633);
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(21633,0,0,0,1,0,100,1,1000,1000,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,'Jovaan - Say Text 0'),
(21633,0,1,0,1,0,100,1,4000,4000,0,0,1,0,0,0,0,0,0,9,21502,0,3,25,0,0,0,'Razuun - Say Text 0'),
(21633,0,2,0,1,0,100,1,12000,12000,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,'Jovaan - Say Text 1'),
(21633,0,3,0,1,0,100,1,16000,16000,0,0,1,1,0,0,0,0,0,9,21502,0,3,25,0,0,0,'Razuun - Say Text 1'),
(21633,0,4,0,1,0,100,1,22000,22000,0,0,1,2,0,0,0,0,0,1,0,0,0,0,0,0,0,'Jovaan - Say Text 2'),
(21633,0,5,0,1,0,100,1,28000,28000,0,0,1,2,0,0,0,0,0,9,21502,0,3,25,0,0,0,'Razuun - Say Text 2'),
(21633,0,6,0,1,0,100,1,30000,30000,0,0,1,3,0,0,0,0,0,1,0,0,0,0,0,0,0,'Jovaan - Say Text 3'),
(21633,0,7,0,1,0,100,1,32000,32000,0,0,1,3,0,0,0,0,0,9,21502,0,3,25,0,0,0,'Razuun - Say Text 3'),
(21633,0,8,0,1,0,100,0,35000,35000,0,0,33,21502,0,0,0,0,0,21,0,0,0,0,0,0,0,'Jovaan - KillCredit to nearest Player'); -- > this doesn't work for some reason

DELETE FROM `creature_text` WHERE `entry` IN (21502,21633);
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES
(21502,0,0,'Doom Lord Kazzak will be pleased. You are to increase the pace of your attacks. Destroy the orcish and dwarven strongholds with all haste.',12,0,100,1,0,0,'Razuun'),
(21502,1,0,'Don''t worry about that. I''ve increased production at the Deathforge. You''ll have all the infernals you need to carry out your orders. Don''t fail, Jovaan.',0,0,100,1,0,0,'Razuun'),
(21502,2,0,'Yes?',12,0,100,1,0,0,'Razuun'),
(21502,3,0,'Crate? I didn''t send you a crate, Jovaan. Don''t you have more important things to worry about? Go see to them!',12,0,100,1,0,0,'Razuun'),
(21633,0,0,'Everything is in readiness, warbringer.',12,0,100,1,0,0,'Jovaan'),
(21633,1,0,'Warbringer, that will require the use of all the hold''s infernals. It may leave us vulnerable to a counterattack.',0,0,100,1,0,0,'Jovaan'),
(21633,2,0,'It shall be as you say, warbringer. One last question, if I may...',12,0,100,1,0,0,'Jovaan'),
(21633,3,0,'What''s in the crate?',12,0,100,1,0,0,'Jovaan');