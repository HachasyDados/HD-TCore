-- Gossip Text
DELETE FROM gossip_menu WHERE entry=37552;
INSERT INTO gossip_menu VALUES (37552, 537552);

DELETE FROM npc_text WHERE id = 537552;
INSERT INTO npc_text (ID, text0_0) VALUES (537552, 'Parece que estos son los restos te Thalorien Buscalba, el último portador de Quel\'Delar');

-- NPCs
DELETE FROM `creature_template` WHERE `entry` IN (37552, 37205, 37542, 37541, 37539, 37538);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(37552, 0, 0, 0, 0, 0, 30659, 0, 0, 0, 'Thalorien Dawnseeker\'s Remains', '', '', 0, 80, 80, 0, 35, 35, 1, 1, 1.14286, 1, 1, 0, 0, 0, 0, 1, 0, 0, 2, 32772, 44, 0, 0, 0, 0, 0, 0, 0, 0, 7, 1024, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 3, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'npc_thalorien', 12340),
(37205, 0, 0, 0, 0, 0, 30570, 0, 0, 0, 'Thalorien Dawnseeker', '', '', 0, 80, 80, 0, 35, 35, 0, 1, 1.14286, 1, 1, 400, 600, 0, 472, 2, 1500, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 4096, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 3, 10.3181, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 37158, 0, 0, '', 12340),
(37542, 0, 0, 0, 0, 0, 30657, 0, 0, 0, 'Morlen Coldgrip', '', '', 0, 80, 80, 0, 16, 16, 0, 1, 1.14286, 1, 1, 400, 600, 0, 472, 1, 1500, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 2048, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 3, 7.076, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', 12340),
(37541, 0, 0, 0, 0, 0, 30651, 30653, 30654, 0, 'Crypt Raider', '', '', 0, 80, 80, 0, 16, 16, 0, 1, 1.14286, 1, 0, 400, 600, 0, 472, 1, 1500, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 3, 3.538, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', 12340),
(37539, 0, 0, 0, 0, 0, 30647, 30648, 30649, 30650, 'Ghoul Invader', '', '', 0, 80, 80, 0, 16, 16, 0, 1, 1.14286, 1, 0, 400, 600, 0, 472, 1, 1500, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 3, 2.9483, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', 12340),
(37538, 0, 0, 0, 0, 0, 30645, 30644, 30643, 30646, 'Scourge Zombie', '', '', 0, 80, 80, 0, 16, 16, 0, 1, 1.14286, 1, 0, 400, 600, 0, 472, 1, 1500, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'SmartAI', 0, 3, 1.887, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', 12340);

DELETE FROM `creature_template_addon` WHERE (`entry`=37552);
INSERT INTO `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) VALUES (37552, 0, 0, 0, 0, 0, '25824 0 31261 0 31261 1');

DELETE FROM `smart_scripts` WHERE (`entryorguid` IN (37552, 37205, 37542, 37541, 37539, 37538) AND `source_type`=0);
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(37205, 0, 0, 0, 0, 0, 100, 30, 5000, 7000, 15000, 15000, 11, 67541, 3, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Thalorien - Filotormenta'),
(37205, 0, 1, 0, 0, 0, 100, 0, 2000, 2000, 13000, 13000, 11, 67542, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Thalorien - Golpe mortal'),
(37205, 0, 2, 0, 0, 0, 100, 0, 19000, 19000, 19000, 19000, 11, 67716, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Thalorien - Torbellino'),
(37205, 0, 3, 0, 0, 0, 100, 0, 1000, 1000, 8000, 8000, 11, 57846, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Thalorien - Golpe heroico'),
(37542, 0, 0, 0, 0, 0, 100, 30, 2000, 3000, 9000, 10000, 11, 50688, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Morlen Manosfrias - Golpe de peste'),
(37541, 0, 0, 0, 0, 0, 100, 30, 1000, 2000, 4000, 5000, 11, 31600, 2, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 'Asaltante de la cripta - Escarabajos de la cripta'),
(37539, 0, 0, 0, 0, 0, 100, 30, 1000, 2000, 9000, 10000, 11, 38056, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Invasor necrofago - Desgarrar carne'),
(37538, 0, 0, 0, 0, 0, 100, 30, 1000, 2000, 9000, 10000, 11, 49861, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 'Zombi de la plaga - Mordedura infectada');