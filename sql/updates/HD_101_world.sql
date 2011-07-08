-- Iron Rune Constructs Templates and Spells
UPDATE `creature_template` SET `minlevel` = 73, `maxlevel` = 73, `VehicleId` = 22, ScriptName = 'npc_iron_rune_construct' WHERE `entry` IN (24821, 24823, 24825);
UPDATE `creature_template` SET `spell1` = 44550 WHERE `entry` = 24821;
UPDATE `creature_template` SET `spell1` = 44498 WHERE `entry` = 24823;
UPDATE `creature_template` SET `spell1` = 44562 WHERE `entry` = 24825;

-- Gameobject for summoning
UPDATE `gameobject_template` SET `ScriptName` = 'go_iron_rune_construct_workbank' WHERE `entry` = 186958;
UPDATE `gameobject_template` SET `data0` = 1635 WHERE `entry` = 186958;

-- Iron Rune Constructs and You: Rocket Jumping
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` = 44498;
INSERT INTO `spell_linked_spell` VALUES
(44498, 34873, 2, 'Rocket Jump -> Fly');

-- Iron Rune Constructs and You: Collecting Data
UPDATE `creature_template` SET `modelid1` = 17856, `unit_flags` = 33587200 WHERE `entry` = 24820;
UPDATE `quest_template` SET `ReqSpellCast1` = 44550 WHERE `entry` = 11489;
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId` = 13 AND `SourceEntry` = 44550;
INSERT INTO `conditions` VALUES
(13, 0, 44550, 0, 18, 1, 24820, 0, 0, '', (NULL));

--  Iron Rune Constructs and You: Bluff
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_lebronski' WHERE `entry` = 24718;
