UPDATE creature_template SET AIName='', ScriptName='npc_ele_power_extractor' WHERE entry IN (18865,18881);
DELETE FROM creature_ai_scripts WHERE creature_id IN (18865,18881);
UPDATE gameobject_template SET flags=0 WHERE entry=183933;