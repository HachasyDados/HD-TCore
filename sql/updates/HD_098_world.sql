-- Creature Templates
UPDATE `creature_template` SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` IN (26232, 26231);
UPDATE `creature_template` SET `unit_flags` = 2, `AIName` = 'SmartAI' WHERE `entry` = 26231;
-- Random trigger (only for visual)
UPDATE `creature_template` SET `modelid1` = 17856, `modelid2` = 0, `scale` = 10, `unit_flags` = 33554434, `flags_extra` = 0 WHERE `entry` = 26227;

-- Saragosa (Dragon) Event
DELETE FROM `smart_scripts` WHERE (`entryorguid`=26231 AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(26231, 0, 0, 1, 25, 0, 100, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Saragosa - Dragon - Pasivo en Spawn'),
(26231, 0, 1, 2, 61, 0, 100, 0, 0, 0, 0, 0, 12, 26227, 3, 5000, 0, 0, 0, 8, 0, 0, 0, 4031.17, 7326.14, 635.97, 0, 'Saragosa - Dragon - Summon Foco en Spawn'),
(26231, 0, 2, 0, 61, 0, 100, 0, 0, 0, 0, 0, 60, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Saragosa - Dragon - Fly ON'),
(26231, 0, 3, 4, 1, 0, 100, 1, 2000, 2000, 0, 0, 60, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Saragosa - Dragon - Se mueve hacia el suelo'),
(26231, 0, 4, 0, 61, 0, 100, 1, 0, 0, 0, 0, 17, 26, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Saragosa - Dragon - Se mueve hacia el suelo'),
(26231, 0, 10, 0, 1, 0, 100, 1, 5000, 5000, 0, 0, 11, 47842, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Saragosa - Dragon - Cast Aliento'),
(26231, 0, 11, 12, 1, 0, 100, 1, 7000, 7000, 0, 0, 12, 26232, 6, 30000, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Saragosa - Dragon - Summon Saragosa Humana'),
(26231, 0, 12, 0, 61, 0, 100, 1, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Saragosa - Dragon - Summon Saragosa Humana');

-- Saragosa Human Script Update
UPDATE `creature_ai_scripts` SET `action2_type` = 103, `action2_param1` = 50 WHERE `id` = 2623201;
