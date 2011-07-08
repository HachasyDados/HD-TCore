-- Quests 12470 & 13343
UPDATE creature_template SET ScriptName='npc_hourglass' WHERE entry IN (27840,32327);

-- Quest completion
DELETE FROM smart_scripts WHERE entryorguid IN (27900);
UPDATE creature_template SET AIName='SmartAI' WHERE entry=27900;
INSERT INTO smart_scripts (entryorguid, source_type, id, link, event_type, event_phase_mask, event_chance,
event_flags, event_param1, event_param2, event_param3, event_param4, action_type, action_param1, action_param2,
action_param3, action_param4, action_param5, action_param6, target_type, target_param1, target_param2, target_param3, target_x, target_y,
target_z, target_o, comment) VALUES
(27900,0,0,0,0,0,100,0,5000,8000,11000,15000,11,51020,0,0,0,0,0,2,0,0,0,0,0,0,0,'Infinite Timerender - Cast Time Lapse'),
(27900,0,1,0,6,0,100,0,0,0,0,0,26,12470,0,0,0,0,0,0,0,0,0,0,0,0,0,'Infinite Timerender - Complete Q12470 on die'),
(27900,0,2,0,6,0,100,0,0,0,0,0,26,13343,0,0,0,0,0,0,0,0,0,0,0,0,0,'Infinite Timerender - Complete Q13343 on die');
update creature_template set faction_A=16, faction_H=16 where entry in (27896,27897,27898,27900);
update creature_template set minlevel=80, maxlevel=80, exp=2 where entry=32327;
