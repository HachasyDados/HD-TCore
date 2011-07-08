-- Q11795 & Q11887
UPDATE creature_template SET npcflag=npcflag|1, AIName='', ScriptName='npc_recon_pilot' WHERE entry=25841;
