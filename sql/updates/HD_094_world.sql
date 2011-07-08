UPDATE `quest_template` SET `SrcSpell` = 43202 WHERE `entry` = 11288;
UPDATE `creature_template` SET `AIName` = '', `ScriptName` = 'npc_decomposing_ghoul' WHERE `entry` = 24177;
UPDATE `creature_template` SET `ScriptName` = 'npc_irulon_trueblade' WHERE `entry` = 24191;

DELETE FROM `script_texts`  WHERE `entry` BETWEEN -1002010 AND -1002000;
INSERT INTO `script_texts` (entry, content_default, TYPE, emote) VALUES
(-1002000, 'That will be enough Irulon.', 0, 1),
(-1002001, 'Cleric of the Crusade removes his disguise.', 2, 0),
(-1002002, 'Lord Fordring, you mustn\'t reveal yourself!', 0, 1),
(-1002003, 'The boy\'s death and, in fact, the deaths of all of the knights involved in the redemption of this blade could have been avoided.', 0, 1),
(-1002004, 'Their passing weighs heavily on my soul.', 0, 1),
(-1002005, 'The path of freedom has always been beset with tragedy, sire. We could not risk losing you. The Order could not have survived such a blow.', 0, 1),
(-1002006, 'Highlord Tirion Fordring grimaces.', 2, 0),
(-1002007, 'It should have been me that carried the blade. That burden was mine to bear.', 0, 1),
(-1002008, 'But you are right, Irulon. The price of our freedom will undoubtedly cost thousands more of their lives.', 0, 1),
(-1002009, 'Highlord Tirion Fordring picks up the Ashbringer.', 2, 0),
(-1002010, 'DO you hear me Arthas? The Silver Hand comes FOR you! Your kingdom shall crumble beneath the weight of justice! BY the Light!', 1, 15););
