-- Fix Dalaran teleport location
DELETE FROM `spell_target_position` WHERE `id`=71512;
INSERT INTO `spell_target_position` (`id`,`target_map`,`target_position_x`,`target_position_y`,`target_position_z`,`target_orientation`) VALUES
(71512,571,5804.15,624.77,647.77,1.64);
