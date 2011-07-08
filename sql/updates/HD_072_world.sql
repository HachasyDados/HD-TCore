-- Q11300 - Una derrota asombrosa en el círculo
-- StartScript
UPDATE quest_template SET StartScript=11300 WHERE entry=11300;
DELETE FROM quest_start_scripts WHERE id=11300;
INSERT INTO quest_start_scripts (id, delay, command, datalong, datalong2, dataint, x, y, z, o) VALUES
(11300,3,10,24213,300000,0,799.653931,-4718.678711,-96.236053,4.992353);
-- cleanup eai
DELETE FROM creature_ai_scripts WHERE creature_id IN (24213,24215,24214,23931);
-- sai
UPDATE creature_template SET AIName='SmartAI' WHERE entry IN (24213,24215,24214,23931);
DELETE FROM smart_scripts WHERE entryorguid IN (24213,24215,24214,23931);
INSERT INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance,
event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2,
action_param3, action_param4, action_param5, action_param6, target_type, target_param1, target_param2, target_param3, target_x, target_y,
target_z, target_o, comment) VALUES
(24213,0,0,0,0,0,100,0,3000,6000,12000,15000,11,15284,0,0,0,0,0,2,0,0,0,0,0,0,0,'Firjus - Cleave'),
(24213,0,1,0,0,0,100,0,10000,10000,10000,10000,11,43348,0,0,0,0,0,2,0,0,0,0,0,0,0,'Firjus - Head Crush'),
(24213,0,2,0,6,0,100,1,0,0,0,0,12,24215,1,300000,0,0,0,8,0,0,0,799.653931,-4718.678711,-96.236053,4.992353,'Firjus - Summon Jlarborn'),
(24215,0,0,0,0,0,100,1,1000,2000,0,0,11,19131,0,0,0,0,0,2,0,0,0,0,0,0,0,'Jlarborn - Shield Charge'),
(24215,0,1,0,0,0,100,0,4000,5000,15000,16000,11,12169,0,0,0,0,0,1,0,0,0,0,0,0,0,'Jlarborn - Shield Block'),
(24215,0,2,0,0,0,100,0,7000,8000,18000,19000,11,38233,0,0,0,0,0,2,0,0,0,0,0,0,0,'Jlarborn - Shield Bash'),
(24215,0,3,0,0,0,100,0,10000,10000,10000,10000,11,8374,0,0,0,0,0,2,0,0,0,0,0,0,0,'Jlarborn - Arcing Smash'),
(24215,0,4,0,6,0,100,1,0,0,0,0,12,24214,1,300000,0,0,0,8,0,0,0,799.653931,-4718.678711,-96.236053,4.992353,'Jlarborn - Summon Yorus'),
(24214,0,0,0,0,0,100,0,3000,6000,12000,15000,11,15284,0,0,0,0,0,2,0,0,0,0,0,0,0,'Yorus - Cleave'),
(24214,0,1,0,0,0,100,0,8000,9000,18000,19000,11,41057,0,0,0,0,0,1,0,0,0,0,0,0,0,'Yorus - Whirlwind'),
(24214,0,2,0,6,0,100,1,0,0,0,0,12,23931,1,300000,0,0,0,8,0,0,0,799.653931,-4718.678711,-96.236053,4.992353,'Yorus - Summon Oluf'),
(23931,0,0,0,0,0,100,0,3000,6000,12000,15000,11,15284,0,0,0,0,0,2,0,0,0,0,0,0,0,'Oluf - Cleave'),
(23931,0,1,0,0,0,100,0,8000,9000,28000,29000,11,13730,0,0,0,0,0,1,0,0,0,0,0,0,0,'Oluf - Demoralizing Shout'),
(23931,0,2,0,0,0,100,0,7000,7000,21000,21000,11,6533,0,0,0,0,0,2,0,0,0,0,0,0,0,'Oluf - Net'),
(23931,0,3,0,0,0,100,1,1000,1000,0,0,11,42870,0,0,0,0,0,2,0,0,0,0,0,0,0,'Oluf - Throw Harpoon'),
(23931,0,4,0,0,0,100,0,10000,10000,10000,10000,11,41057,0,0,0,0,0,1,0,0,0,0,0,0,0,'Oluf - Whirlwind'),
(23931,0,5,0,6,0,100,1,0,0,0,0,50,186640,90000,0,0,0,0,8,0,0,0,799.653931,-4718.678711,-96.236053,4.992353,'Oluf - Summon Ancient Cipher');
