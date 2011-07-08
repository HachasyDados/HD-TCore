-- Q11593 & Q11658
-- cleanup
DELETE FROM creature_ai_scripts WHERE creature_id IN (25342,25343);
-- new script
UPDATE creature_template SET AIName='', ScriptName='npc_fallen_caravan_guard' WHERE entry IN (25342,25343);
