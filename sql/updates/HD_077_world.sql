UPDATE `creature_template` SET `ScriptName` = 'npc_shredders_taker' WHERE `entry` IN (27371, 27423);
UPDATE `creature_template` SET `ScriptName` = 'npc_brokendown_shredders' WHERE `entry` = 27354;

delete from `npc_spellclick_spells` where npc_entry = 27354;

insert into `npc_spellclick_spells` (`npc_entry`, `spell_id`, `quest_start`, `quest_start_active`, `quest_end`, `cast_flags`, `aura_required`, `aura_forbidden`, `user_type`) values('27354','48533','12244','1','0','1','0','0','0');
insert into `npc_spellclick_spells` (`npc_entry`, `spell_id`, `quest_start`, `quest_start_active`, `quest_end`, `cast_flags`, `aura_required`, `aura_forbidden`, `user_type`) values('27354','48533','12270','1','0','1','0','0','0');
