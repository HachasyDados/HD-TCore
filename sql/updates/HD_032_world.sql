-- ICC weapons procs
-- (71845) Item - Icecrown 25 Normal Caster Weapon Proc
DELETE FROM `spell_proc_event` WHERE `entry` IN (71845);
INSERT INTO `spell_proc_event` VALUES (71845, 0x01, 0x00, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00000000, 0, 2, 40);
-- (71845) Item - Icecrown 25 Normal Caster Weapon Proc
DELETE FROM `spell_proc_event` WHERE `entry` IN (71845);
INSERT INTO `spell_proc_event` VALUES (71845, 0x01, 0x00, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00000000, 0, 2, 45);
-- (71865) Item - Icecrown 25 Normal Healer Weapon Proc
DELETE FROM `spell_proc_event` WHERE `entry` IN (71865);
INSERT INTO `spell_proc_event` VALUES (71865, 0x01, 0x0A, 0x00000000, 0x00000000, 0x00000000, 0x00044000, 0x00000018, 0, 1, 0);
-- (71868) Item - Icecrown 25 Heroic Healer Weapon Proc
DELETE FROM `spell_proc_event` WHERE `entry` IN (71868);
INSERT INTO `spell_proc_event` VALUES (71868, 0x01, 0x0A, 0x00000000, 0x00000000, 0x00000000, 0x00044000, 0x00000018, 0, 1, 0);
-- (71871) Item - Icecrown 25 Normal Tank Weapon Proc
DELETE FROM `spell_proc_event` WHERE `entry` IN (71871);
INSERT INTO `spell_proc_event` VALUES (71871, 0x01, 0x0A, 0x00000000, 0x00000000, 0x00000000, 0x00000014, 0x00000018, 0, 37, 30);
-- (71873) Item - Icecrown 25 Heroic Tank Weapon Proc
DELETE FROM `spell_proc_event` WHERE `entry` IN (71873);
INSERT INTO `spell_proc_event` VALUES (71873, 0x01, 0x00, 0x00000000, 0x00000000, 0x00000000, 0x00000014, 0x00000018, 0, 37, 35);
