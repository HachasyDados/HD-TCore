-- Fix spell Summon Grom'thar the Thunderbringer for Quest 12151 - Wanton Warlord
DELETE FROM event_scripts WHERE id=17767;
INSERT INTO event_scripts VALUES (17767,2,10,27002,300000,0,2713.821045,445.447998,67.814095,5.241539);