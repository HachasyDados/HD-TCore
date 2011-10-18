/*WorldStates Characters DB*/
DELETE FROM `worldstates` WHERE `entry` IN (31001,31002,31003,31004);
INSERT INTO `worldstates` VALUES
('31001', '0', 'WG war status'),
('31002', '0', 'WG clock'),
('31003', '0', 'WG Fortress Defender'),
('31004', '0', 'WG TEMP Battle Control Faction');
