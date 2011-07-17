-- TEMP Nearby Tubers
DELETE FROM `gameobject` WHERE `map`='47' AND `id`='300011';

INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('300011','47','1','1','2082.74','1671.82','61.2396','3.66079','0','0','0.966493','-0.256693','43200','100','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('300011','47','1','1','2159.43','1687.49','57.5433','3.66079','0','0','0.966493','-0.256693','43200','100','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('300011','47','1','1','2080.89','1703.36','56.6447','0.553757','0','0','0.273354','0.961913','43200','100','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('300011','47','1','1','2055.28','1767.7','58.4559','2.98378','0','0','0.996889','0.0788245','43200','100','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('300011','47','1','1','2196.64','1827.96','61.4706','2.11277','0','0','0.870583','0.492022','43200','100','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('300011','47','1','1','2030.32','1867.61','56.2866','5.6777','0','0','0.298139','-0.954522','43200','100','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('300011','47','1','1','2091.33','1861.73','51.0341','1.25355','0','0','0.586536','0.809923','43200','100','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('300011','47','1','1','2200.15','1897.64','71.3191','2.6492','0','0','0.969846','0.243717','43200','100','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('300011','47','1','1','2075.75','1742.04','76.7184','1.33994','0','0','0.620962','0.78384','43200','100','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('300011','47','1','1','2126','1661.15','82.4824','0.0220437','0','0','0.0110216','0.999939','43200','100','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('300011','47','1','1','2207.92','1596.91','80.7375','3.60582','0','0','0.973182','-0.230035','43200','100','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('300011','47','1','1','2156.98','1542.26','72.849','2.43086','0','0','0.937519','0.347934','43200','100','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('300011','47','1','1','2179.95','1514.06','69.0709','0.778385','0','0','0.379441','0.925216','43200','100','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('300011','47','1','1','2000.85','1533.93','80.3971','4.919','0','0','0.630419','-0.776255','43200','100','1');
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES('300011','47','1','1','1991.49','1608.53','81.1601','1.1004','0','0','0.522858','0.85242','43200','100','1');

-- Generated by Event Horizon - SAI Editor (http://devsource-eventhorizon.tk/)

-- Snufflenose Gopher
SET @ENTRY := 4781;
SET @SOURCETYPE := 0;

DELETE FROM `smart_scripts` WHERE `entryorguid`=@ENTRY AND `source_type`=@SOURCETYPE;
UPDATE creature_template SET AIName="SmartAI" WHERE entry=@ENTRY LIMIT 1;
INSERT INTO `smart_scripts` (`entryorguid`,`source_type`,`id`,`link`,`event_type`,`event_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action_type`,`action_param1`,`action_param2`,`action_param3`,`action_param4`,`action_param5`,`action_param6`,`target_type`,`target_param1`,`target_param2`,`target_param3`,`target_x`,`target_y`,`target_z`,`target_o`,`comment`) VALUES
(@ENTRY,@SOURCETYPE,0,1,8,0,100,0,8283,0,0,0,8,0,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"NPC 4781 Quest 1221 react 0"),
(@ENTRY,@SOURCETYPE,1,2,61,0,100,0,10000,20000,60000,60000,89,5,0,0,0,0,0,0,0,0,0,0.0,0.0,0.0,0.0,"NPC 4781 Quest 1221 random move"),
(@ENTRY,@SOURCETYPE,2,0,61,0,100,0,0,0,0,0,11,6900,0,0,0,0,0,1,0,0,0,0.0,0.0,0.0,0.0,"NPC 4781 Quest 1221 cast 6900 create tuber");

-- Blueleaf Tuber
UPDATE `gameobject_template` SET `faction` = 0 WHERE `entry` = 20920; -- original faction = 5
