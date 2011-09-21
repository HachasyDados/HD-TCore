UPDATE creature_template SET npcflag=npcflag|129 WHERE entry=35826;
UPDATE creature SET position_z=599.818 WHERE id=35826;
DELETE FROM npc_vendor WHERE entry=35826;
INSERT INTO npc_vendor VALUES
(35826,0,10609,1,10800,0),
(35826,0,13311,1,10800,0),
(35826,0,16054,1,10800,0);