SET @GUID := 153100;
DELETE FROM `gameobject` WHERE `id` IN(201959, 202338, 202339, 202340);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@GUID+0, 201959, 631, 1, 1, 4203.65, 2484.56, 364.873, 6.28004, 0, 0, 0.00157252, -1, -120, 0, 1),
(@GUID+1, 202339, 631, 2, 1, 4203.65, 2484.56, 364.873, 6.28004, 0, 0, 0.00157252, -1, -120, 0, 1),
(@GUID+2, 202338, 631, 4, 1, 4203.65, 2484.56, 364.873, 6.28004, 0, 0, 0.00157252, -1, -120, 0, 1),
(@GUID+3, 202340, 631, 8, 1, 4203.65, 2484.56, 364.873, 6.28004, 0, 0, 0.00157252, -1, -120, 0, 1);
