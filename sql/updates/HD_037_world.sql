-- fix 12856 (Cold Hearted)
-- captive proto-drake
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=29708;
INSERT INTO `npc_spellclick_spells` (`npc_entry`,`spell_id`,`quest_start`,`quest_start_active`,`quest_end`,`cast_flags`,`aura_required`,`aura_forbidden`,`user_type`)
VALUES (29708,55028,12856,1,12856,1,0,0,0);

-- freed proto-drake
DELETE FROM `creature_template_addon` WHERE `entry`=29709;
INSERT INTO `creature_template_addon` (`entry`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(29709,0,50331648,257,0, NULL);
UPDATE `creature_template` SET `unit_flags`=`unit_flags`|16777216, `ScriptName`='' WHERE `entry`=29708;
UPDATE `creature_template` SET `InhabitType`=7 WHERE `entry`=29709;
UPDATE `creature_template` SET `AIName`='', `ScriptName`='npc_freed_protodrake' WHERE `entry`=29709;
update creature_template set spell1=55046 where entry=29709;