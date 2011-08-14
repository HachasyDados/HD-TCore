-- Q12886
UPDATE creature_template SET InhabitType=7, AIName='', ScriptName='npc_hyldsmeet_protodrake_hyd' WHERE entry=29679;
UPDATE creature_template SET vehicleid=190 WHERE entry=29798;
DELETE FROM npc_spellclick_spells WHERE npc_entry=29798;
INSERT INTO npc_spellclick_spells VALUES (29798,54952,12886,1,12886,1,0,0,0);
delete from creature_ai_scripts where id in (2969402,2969403);
insert into creature_ai_scripts (id, creature_id, event_type, event_chance, event_flags, event_param1,
event_param2, event_param3, event_param4, action1_type, action1_param1, action1_param2, action1_param3, comment) values
(2969402,29694,4,100,1,500,500,0,0,33,29800,1,0,'KC en aggro q12886'),
(2969403,29694,0,100,1,1000,1000,0,0,41,0,0,0,'Despawn');
UPDATE creature_template SET AIName='', ScriptName='npc_column_ornament' WHERE entry=29754;
