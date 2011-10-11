UPDATE `creature_template` SET `ScriptName` = 'npc_antelarion_gossip' WHERE `entry` = 22127;
UPDATE `creature_template` SET `ScriptName` = 'npc_evergrove_druid' WHERE `entry` = 22423;
UPDATE `creature_template` SET `unit_flags` = 0, `flags_extra` = 2, `InhabitType` = 5 WHERE `entry` = 22423;
DELETE FROM `creature_template_addon` WHERE `entry`=22423;
