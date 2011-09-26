SET @CGUID := 600061;
SET @GOGUID := 801000;

-- Numa Cloudsister (missing stats in TDB)
DELETE FROM `creature_template` WHERE (`entry`=25710);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES (25710, 0, 0, 0, 0, 0, 3848, 0, 0, 0, 'Numa Cloudsister', '', '', 0, 70, 70, 0, 35, 35, 2, 1, 1.14286, 1, 0, 260, 390, 0, 97, 1, 2000, 2000, 1, 0, 8, 0, 0, 0, 0, 0, 208, 312, 78, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, '', 12340);
-- Numa Cloudsister (spawn location)
DELETE FROM `creature` WHERE `id`=25710 AND guid=@CGUID;
INSERT INTO `creature` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`MovementType`,`npcflag`,`unit_flags`,`dynamicflags`) VALUES
(@CGUID+0, 25710, 547, 3, 1, 0, 0, 132.721, -116.256, -1.59053, 3.85833, 7200, 0, 0, 13000, 0, 0, 0, 0, 0);

-- Numa Cloudsister (has to appear only during midsummer)
DELETE FROM `game_event_creature` WHERE `guid` = @CGUID;
INSERT INTO `game_event_creature` (`eventEntry`, `guid`) VALUES ('1', '@CGUID+0');

-- Ice Block (enviromental)
UPDATE `gameobject_template` SET `flags` = 4 WHERE `entry` = 181247;
DELETE FROM `gameobject` WHERE `id`=181247 OR guid BETWEEN @GOGUID AND @GOGUID+35;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(@GOGUID, 181247, 547, 3, 1, -57.1839, -163.09, -1.86789, 3.03712, 0, 0, 0.998636, 0.0522129, 600, 100, 1),
(@GOGUID+1, 181247, 547, 3, 1, -110.724, -220.009, -1.46231, 4.93604, 0, 0, 0.623781, -0.781599, 600, 100, 1),
(@GOGUID+2, 181247, 547, 3, 1, -111.186, -218.476, -1.45743, 4.64938, 0, 0, 0.72903, -0.684482, 600, 100, 1),
(@GOGUID+3, 181247, 547, 3, 1, -113.038, -220.001, -1.49564, 0.141184, 0, 0, 0.0705332, 0.997509, 600, 100, 1),
(@GOGUID+4, 181247, 547, 3, 1, -113.425, -190.095, -1.62577, 1.29965, 0, 0, 0.605046, 0.796191, 600, 100, 1),
(@GOGUID+5, 181247, 547, 3, 1, -111.629, -181.89, -1.69428, 1.35462, 0, 0, 0.626701, 0.77926, 600, 100, 1),
(@GOGUID+6, 181247, 547, 3, 1, -75.4315, -197.594, -3.81566, 5.745, 0, 0, 0.265858, -0.964012, 600, 100, 1),
(@GOGUID+7, 181247, 547, 3, 1, -75.1775, -199.283, -3.48168, 0.694888, 0, 0, 0.340496, 0.940246, 600, 100, 1),
(@GOGUID+8, 181247, 547, 3, 1, -71.3321, -214.298, -3.50633, 5.98061, 0, 0, 0.15071, -0.988578, 600, 100, 1),
(@GOGUID+9, 181247, 547, 3, 1, -73.5923, -214.702, -3.30814, 5.23056, 0, 0, 0.50235, -0.864664, 600, 100, 1),
(@GOGUID+10, 181247, 547, 3, 1, -73.0391, -212.836, -3.4034, 5.14809, 0, 0, 0.537565, -0.843222, 600, 100, 1),
(@GOGUID+11, 181247, 547, 3, 1, -85.9781, -228.559, -1.12156, 2.22641, 0, 0, 0.897119, 0.441789, 600, 100, 1),
(@GOGUID+12, 181247, 547, 3, 1, -85.0324, -226.669, -1.12005, 3.67154, 0, 0, 0.965099, -0.261885, 600, 100, 1),
(@GOGUID+13, 181247, 547, 3, 1, -113.873, -234.04, -1.57737, 3.45948, 0, 0, 0.987395, -0.158278, 600, 100, 1),
(@GOGUID+14, 181247, 547, 3, 1, -110.716, -245.133, -1.51474, 5.53686, 0, 0, 0.364563, -0.931179, 600, 100, 1),
(@GOGUID+15, 181247, 547, 3, 1, -109.35, -243.441, -1.48757, 3.90716, 0, 0, 0.927628, -0.373505, 600, 100, 1),
(@GOGUID+16, 181247, 547, 3, 1, -111.266, -243.141, -1.52745, 5.6154, 0, 0, 0.327723, -0.944774, 600, 100, 1),
(@GOGUID+17, 181247, 547, 3, 1, -112.785, -161.964, -2.06386, 2.67801, 0, 0, 0.973257, 0.22972, 600, 100, 1),
(@GOGUID+18, 181247, 547, 3, 1, -112.877, -160.442, -2.10365, 1.59809, 0, 0, 0.71669, 0.697392, 600, 100, 1),
(@GOGUID+19, 181247, 547, 3, 1, -114.846, -161.158, -1.99702, 6.27513, 0, 0, 0.00402631, -0.999992, 600, 100, 1),
(@GOGUID+20, 181247, 547, 3, 1, -89.8076, -151.643, -2.04892, 4.72004, 0, 0, 0.704395, -0.709808, 600, 100, 1),
(@GOGUID+21, 181247, 547, 3, 1, -90.496, -152.89, -2.04839, 0.757711, 0, 0, 0.369857, 0.929089, 600, 100, 1),
(@GOGUID+22, 181247, 547, 3, 1, -88.6876, -153.232, -2.1968, 2.42276, 0, 0, 0.936102, 0.35173, 600, 100, 1),
(@GOGUID+23, 181247, 547, 3, 1, -134.157, -253.092, -1.59144, 3.26706, 0, 0, 0.998033, -0.0626902, 600, 100, 1),
(@GOGUID+24, 181247, 547, 3, 1, -132.891, -254.973, -1.59144, 2.06932, 0, 0, 0.859689, 0.510818, 600, 100, 1),
(@GOGUID+25, 181247, 547, 3, 1, -127.004, -273.292, -1.59257, 4.65721, 0, 0, 0.726345, -0.687331, 600, 100, 1),
(@GOGUID+26, 181247, 547, 3, 1, -126.491, -274.995, -1.59257, 5.01456, 0, 0, 0.592624, -0.805479, 600, 100, 1),
(@GOGUID+27, 181247, 547, 3, 1, -124.779, -273.556, -1.59246, 1.40958, 0, 0, 0.647873, 0.761748, 600, 100, 1),
(@GOGUID+28, 181247, 547, 3, 1, -112.831, -290.044, -1.59038, 5.1088, 0, 0, 0.554024, -0.832501, 600, 100, 1),
(@GOGUID+29, 181247, 547, 3, 1, -113.212, -291.668, -1.59038, 2.41489, 0, 0, 0.934711, 0.355409, 600, 100, 1),
(@GOGUID+30, 181247, 547, 3, 1, -115.864, -290.957, -1.59038, 1.27606, 0, 0, 0.595615, 0.80327, 600, 100, 1),
(@GOGUID+31, 181247, 547, 3, 1, -114.275, -288.326, -1.59038, 0.628108, 0, 0, 0.308917, 0.951089, 600, 100, 1),
(@GOGUID+32, 181247, 547, 3, 1, -88.1205, -272.713, -1.23599, 0.879434, 0, 0, 0.425683, 0.904872, 600, 100, 1),
(@GOGUID+33, 181247, 547, 3, 1, -74.3856, -262.839, -0.901379, 0.726281, 0, 0, 0.355212, 0.934786, 600, 100, 1),
(@GOGUID+34, 181247, 547, 3, 1, -72.2233, -260.36, -1.30804, 0.855872, 0, 0, 0.414994, 0.909824, 600, 100, 1),
(@GOGUID+35, 181247, 547, 3, 1, -74.5592, -260.088, -0.965048, 5.36405, 0, 0, 0.443559, -0.896245, 600, 100, 1);

DELETE FROM `gameobject` WHERE `id`=188067 AND guid BETWEEN @GOGUID+36 AND @GOGUID+42;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(@GOGUID+36, 188067, 547, 3, 1, -79.397, -219.702, -4.04289, -2.19912, 0, 0, 0, 1, 180, 255, 1),
(@GOGUID+37, 188067, 547, 3, 1, -115.599, -162.772, -1.92403, -0.558504, 0, 0, 0, 1, 180, 255, 1),
(@GOGUID+38, 188067, 547, 3, 1, -71.8962, -145.497, -1.55181, -1.95477, 0, 0, 0, 1, 180, 255, 1),
(@GOGUID+39, 188067, 547, 3, 1, -75.9514, -182.771, -4.88202, -1.15192, 0, 0, 0, 1, 180, 255, 1),
(@GOGUID+40, 188067, 547, 3, 1, -49.2725, -168.986, -1.89881, 2.00713, 0, 0, 0, 1, 180, 255, 1),
(@GOGUID+41, 188067, 547, 3, 1, -75.2318, -217.329, -3.0728, -0.488691, 0, 0, 0, 1, 180, 255, 1),
(@GOGUID+42, 188067, 547, 3, 1, -83.5253, -172.181, -3.81652, 0.017452, 0, 0, 0, 1, 180, 255, 1);

-- Snow Pile (enviromental)
DELETE FROM `gameobject` WHERE `id`=188187 AND guid=@GOGUID+43;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(@GOGUID+43, 188187, 547, 3, 1, -96.8723, -212.842, -1.14914, -2.1293, 0, 0, 0, 1, 180, 255, 1);

DELETE FROM game_event_gameobject WHERE guid BETWEEN @GOGUID AND @GOGUID+43;
INSERT INTO game_event_gameobject VALUES
(1,@GOGUID), (1,@GOGUID+1), (1,@GOGUID+2), (1,@GOGUID+3), (1,@GOGUID+4), (1,@GOGUID+5), (1,@GOGUID+6), (1,@GOGUID+7), (1,@GOGUID+8),
(1,@GOGUID+9),  (1,@GOGUID+10), (1,@GOGUID+11), (1,@GOGUID+12), (1,@GOGUID+13), (1,@GOGUID+14), (1,@GOGUID+15), (1,@GOGUID+16), (1,@GOGUID+17),
(1,@GOGUID+18), (1,@GOGUID+19), (1,@GOGUID+20), (1,@GOGUID+21), (1,@GOGUID+22), (1,@GOGUID+23), (1,@GOGUID+24), (1,@GOGUID+25),
(1,@GOGUID+26), (1,@GOGUID+27), (1,@GOGUID+28), (1,@GOGUID+29), (1,@GOGUID+30), (1,@GOGUID+31), (1,@GOGUID+32), (1,@GOGUID+33),
(1,@GOGUID+34), (1,@GOGUID+35), (1,@GOGUID+36), (1,@GOGUID+37), (1,@GOGUID+38), (1,@GOGUID+39), (1,@GOGUID+40), (1,@GOGUID+41), (1,@GOGUID+42), (1,@GOGUID+43);

-- Achiev 271
-- Serverside Spells
DELETE FROM `spell_dbc` WHERE `Id` IN (29710,58934);
INSERT INTO `spell_dbc` (`Id`, `Dispel`, `Mechanic`, `Attributes`, `AttributesEx`, `AttributesEx2`, `AttributesEx3`, `AttributesEx4`, `AttributesEx5`, `Stances`, `StancesNot`, `Targets`, `CastingTimeIndex`, `AuraInterruptFlags`, `ProcFlags`, `ProcChance`, `ProcCharges`, `MaxLevel`, `BaseLevel`, `SpellLevel`, `DurationIndex`, `RangeIndex`, `StackAmount`, `EquippedItemClass`, `EquippedItemSubClassMask`, `EquippedItemInventoryTypeMask`, `Effect1`, `Effect2`, `Effect3`, `EffectDieSides1`, `EffectDieSides2`, `EffectDieSides3`, `EffectRealPointsPerLevel1`, `EffectRealPointsPerLevel2`, `EffectRealPointsPerLevel3`, `EffectBasePoints1`, `EffectBasePoints2`, `EffectBasePoints3`, `EffectMechanic1`, `EffectMechanic2`, `EffectMechanic3`, `EffectImplicitTargetA1`, `EffectImplicitTargetA2`, `EffectImplicitTargetA3`, `EffectImplicitTargetB1`, `EffectImplicitTargetB2`, `EffectImplicitTargetB3`, `EffectRadiusIndex1`, `EffectRadiusIndex2`, `EffectRadiusIndex3`, `EffectApplyAuraName1`, `EffectApplyAuraName2`, `EffectApplyAuraName3`, `EffectAmplitude1`, `EffectAmplitude2`, `EffectAmplitude3`, `EffectMultipleValue1`, `EffectMultipleValue2`, `EffectMultipleValue3`, `EffectMiscValue1`, `EffectMiscValue2`, `EffectMiscValue3`, `EffectMiscValueB1`, `EffectMiscValueB2`, `EffectMiscValueB3`, `EffectTriggerSpell1`, `EffectTriggerSpell2`, `EffectTriggerSpell3`, `EffectSpellClassMaskA1`, `EffectSpellClassMaskA2`, `EffectSpellClassMaskA3`, `EffectSpellClassMaskB1`, `EffectSpellClassMaskB2`, `EffectSpellClassMaskB3`, `EffectSpellClassMaskC1`, `EffectSpellClassMaskC2`, `EffectSpellClassMaskC3`, `MaxTargetLevel`, `SpellFamilyName`, `SpellFamilyFlags1`, `SpellFamilyFlags2`, `SpellFamilyFlags3`, `MaxAffectedTargets`, `DmgClass`, `PreventionType`, `DmgMultiplier1`, `DmgMultiplier2`, `DmgMultiplier3`, `AreaGroupId`, `SchoolMask`, `Comment`) VALUES
('29710','0','0','256','0','0','0','0','0','0','0','0','1','0','0','101','0','0','0','0','0','1','0','-1','0','0','140','0','0','0','0','0','0','0','0','0','0','0','0','0','0','25','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','29531','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','1','1','0','1','Ribbon Pole - Force Cast Ribbon Pole Channel'),
('58934','0','0','536870912','0','0','0','0','0','0','0','0','1','0','0','101','0','0','0','0','0','1','0','-1','0','0','3','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','0','28','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','Burning Hot Pole Dance credit marker');

-- Link Dancer Check Aura and Visual to Ribbon Pole Channel
DELETE FROM `spell_linked_spell` WHERE `spell_trigger` IN (29531,45390);
INSERT INTO `spell_linked_spell` (`spell_trigger`,`spell_effect`,`type`,`comment`) VALUES
(29531,45390,0, 'Ribbon Pole - Dancer Check Aura'),
(45390,45406,2, 'Ribbon Pole - Periodic Visual');

-- Spell Script
DELETE FROM `spell_script_names` WHERE `spell_id`=45390;
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(45390, 'spell_gen_ribbon_pole_dancer_check');

-- Basic torch tossing support
-- torch toss target condition
DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry` IN (46054,45732);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`) VALUES
(13,45732,18,1,25535),
(13,46054,18,1,25535);

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=45723;
INSERT INTO `spell_linked_spell` (`spell_trigger`,`spell_effect`,`type`,`comment`) VALUES
(45723,43313,2, 'Torch Tossing - Target Indicator Visual');

UPDATE `creature_template` SET `ScriptName`='npc_torch_tossing_bunny' WHERE `entry`=25535;

UPDATE `quest_template` SET `RewOrReqMoney`=74000, `RewMoneyMaxLevel`=132300 WHERE `entry` IN (11731,11922);
UPDATE `quest_template` SET `PrevQuestId`=11731, `RewOrReqMoney`=74000, `RewMoneyMaxLevel`=132300 WHERE `entry`=11921;
UPDATE `quest_template` SET `PrevQuestId`=11922, `RewOrReqMoney`=74000, `RewMoneyMaxLevel`=132300 WHERE `entry`=11926;
UPDATE `quest_template` SET `StartScript`=11731 WHERE `entry` IN (11731,11922);
UPDATE `quest_template` SET `StartScript`=11921 WHERE `entry` IN (11921,11926);

-- add torch toss aura on quest accept
DELETE FROM `quest_start_scripts` WHERE `id` IN (11731,11921);
INSERT INTO `quest_start_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`) VALUES
(11731,0,14,45724,0,0,0,0,0,0),
(11731,1,15,45716,0,0,0,0,0,0),
(11921,0,14,45724,0,0,0,0,0,0),
(11921,1,15,46630,0,0,0,0,0,0);

-- more objects
DELETE FROM `gameobject` WHERE `guid` BETWEEN @GOGUID+44 AND @GOGUID+50;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@GOGUID+44,'187708','0','1','1','-8822.4','846.766','99.0875','2.10363','0','0','0.868324','0.495997','300','0','1'),
(@GOGUID+45,'187708','0','1','1','-8817.63','851.846','98.9217','2.93222','0','0','0.994525','0.104495','300','0','1'),
(@GOGUID+46,'187708','0','1','1','-8816.68','854.946','98.9073','2.92043','0','0','0.993892','0.110354','300','0','1'),
(@GOGUID+47,'187708','0','1','1','-8816.66','858.591','98.9913','3.1427','0','0','1','-0.000551387','300','0','1'),
(@GOGUID+48,'300068','0','1','1','-8834.32','857.823','99.8395','6.0196','0','0','0.131411','-0.991328','300','0','1'),
(@GOGUID+49,'187708','1','1','1','1913.57','-4315.85','23.1799','4.90635','0','0','0.635316','-0.772252','300','0','1'),
(@GOGUID+50,'300068','1','1','1','1914.7','-4336.27','22.1744','1.01471','0','0','0.485865','0.874034','300','0','1');

DELETE FROM `game_event_gameobject` WHERE `guid` BETWEEN @GOGUID+44 AND @GOGUID+50;
INSERT INTO `game_event_gameobject` (`eventEntry`, `guid`) VALUES
(1,@GOGUID+44),
(1,@GOGUID+45),
(1,@GOGUID+46),
(1,@GOGUID+47),
(1,@GOGUID+48),
(1,@GOGUID+49),
(1,@GOGUID+50);

-- more bunnies
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+1 AND @CGUID+12;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`,  `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+1,'25535','0','1','1','0','0','-8825.75','845.668','100.848','2.15624','30','0','0','4120','0','0','0','0','0'),
(@CGUID+2,'25535','0','1','1','0','0','-8822.48','846.841','100.883','2.2018','30','0','0','4120','0','0','0','0','0'),
(@CGUID+3,'25535','0','1','1','0','0','-8819.42','848.453','100.745','2.70837','30','0','0','4120','0','0','0','0','0'),
(@CGUID+4,'25535','0','1','1','0','0','-8817.56','851.801','100.717','2.7767','30','0','0','4120','0','0','0','0','0'),
(@CGUID+5,'25535','0','1','1','0','0','-8816.67','854.896','100.703','2.9275','30','0','0','4120','0','0','0','0','0'),
(@CGUID+6,'25535','0','1','1','0','0','-8816.57','858.57','100.787','3.28328','30','0','0','4120','0','0','0','0','0'),
(@CGUID+7,'25535','1','1','1','0','0','1925.17','-4321.24','23.4473','4.69918','30','0','0','4120','0','0','0','0','0'),
(@CGUID+8,'25535','1','1','1','0','0','1923.89','-4315.22','24.2852','4.59786','30','0','0','4120','0','0','0','0','0'),
(@CGUID+9,'25535','1','1','1','0','0','1920.46','-4319.27','23.6163','5.01334','30','0','0','4120','0','0','0','0','0'),
(@CGUID+10,'25535','1','1','1','0','0','1918.05','-4314.94','24.6482','5.04868','30','0','0','4120','0','0','0','0','0'),
(@CGUID+11,'25535','1','1','1','0','0','1913.58','-4315.8','24.9737','5.22382','30','0','0','4120','0','0','0','0','0'),
(@CGUID+12,'25535','1','1','1','0','0','1915.54','-4320.43','23.6154','5.09658','30','0','0','4120','0','0','0','0','0');

DELETE FROM `game_event_creature` WHERE `guid` BETWEEN @CGUID+1 AND @CGUID+12;
INSERT INTO `game_event_creature` (`eventEntry`, `guid`) VALUES
(1,@CGUID+1),
(1,@CGUID+2),
(1,@CGUID+3),
(1,@CGUID+4),
(1,@CGUID+5),
(1,@CGUID+6),
(1,@CGUID+7),
(1,@CGUID+8),
(1,@CGUID+9),
(1,@CGUID+10),
(1,@CGUID+11),
(1,@CGUID+12);

-- Allow stealing flames from other faction cities & other fixes
UPDATE `gameobject_template` SET `faction`=1735 WHERE `entry`=188128;
UPDATE `gameobject_template` SET `faction`=1732 WHERE `entry`=188129;

-- move one loremaster to stormwind
UPDATE `creature` SET `position_x`=-8833.497, `position_y`=864.7697, `position_z`=98.9, `orientation`=5.89 WHERE `guid`=94857;

-- add flame of the exodar
DELETE FROM `gameobject` WHERE `id`=188128 OR guid=@GOGUID+51;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@GOGUID+51,'188128','530','1','1','-3796.45','-11503.7','-134.772','0.350275','0','0','0.174244','0.984703','300','0','1');

DELETE FROM `game_event_gameobject` WHERE `guid`=@GOGUID+51;
INSERT INTO `game_event_gameobject` (`eventEntry`, `guid`) VALUES
(1,@GOGUID+51);

-- create flame items
DELETE FROM `spell_scripts` WHERE `id` IN (29137,29135,29126,46671,29139,29136,29138,46672);
INSERT INTO `spell_scripts` (`id`, `effIndex`, `delay`, `command`, `datalong`, `datalong2`, `dataint`, `x`, `y`, `z`, `o`) VALUES
(29137,2,0,15,29101,2,0,0,0,0,0), -- flame of stormwind
(29135,2,0,15,29102,2,0,0,0,0,0), -- flame of ironforge
(29126,2,0,15,29099,2,0,0,0,0,0), -- flame of darnassus
(46671,2,0,15,46690,2,0,0,0,0,0), -- flame of the exodar
(29139,2,0,15,29133,2,0,0,0,0,0), -- flame of the undercity
(29136,2,0,15,29130,2,0,0,0,0,0), -- flame of orgrimmar
(29138,2,0,15,29132,2,0,0,0,0,0), -- flame of thunder bluff
(46672,2,0,15,46689,2,0,0,0,0,0); -- flame of silvermoon

-- correct some relations
DELETE FROM `creature_questrelation` WHERE `id`=16817 AND `quest`=11935;
DELETE FROM `creature_questrelation` WHERE `id`=16818 AND `quest`=11933;
UPDATE `creature_questrelation` SET `id`=16818 WHERE `quest`=9339;
UPDATE `creature_involvedrelation` SET `id`=16818 WHERE `quest`=9339;
UPDATE `creature_questrelation` SET `id`=16817 WHERE `quest`=9365;
UPDATE `creature_involvedrelation` SET `id`=16817 WHERE `quest`=9365;

-- torch catching
DELETE FROM `spell_script_names` WHERE `spell_id` IN (45907,45671);
INSERT INTO `spell_script_names` (`spell_id`,`ScriptName`) VALUES
(45907, 'spell_gen_torch_target_picker'),
(45671, 'spell_gen_juggle_torch_catch');

DELETE FROM `conditions` WHERE `SourceTypeOrReferenceId`=13 AND `SourceEntry` IN (45907,45671);
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`) VALUES
(13,45907,18,1,25515),
(13,45671,18,1,0),
(13,45671,18,1,25515);

DELETE FROM `spell_linked_spell` WHERE `spell_trigger`=46747;
INSERT INTO `spell_linked_spell` (`spell_trigger`,`spell_effect`,`type`,`comment`) VALUES
(46747,45907,0, 'Fling Torch - Torch Target Picker');

UPDATE `creature_template` SET `flags_extra`=`flags_extra`|128 WHERE `entry`=25515;

UPDATE `quest_template` SET `RewOrReqMoney`=74000, `RewMoneyMaxLevel`=132300 WHERE `entry`=11923;
UPDATE `quest_template` SET `PrevQuestId`=11657 WHERE `entry`=11924;
UPDATE `quest_template` SET `PrevQuestId`=11923, `RewOrReqMoney`=74000, `RewMoneyMaxLevel`=132300 WHERE `entry`=11925;

DELETE FROM creature WHERE guid BETWEEN @CGUID+13 AND @CGUID+44;
DELETE FROM `creature` WHERE `id`=25515;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`,  `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+13,'25515','1','1','1','0','0','1921.68','-4326.24','21.7631','4.69113','30','0','0','42','0','0','0','0','0'),
(@CGUID+14,'25515','0','1','1','0','0','-8820.57','863.37','98.9602','1.09525','30','0','0','42','0','0','0','0','0'),
(@CGUID+15,'25515','0','1','1','0','0','-8819.07','881.422','98.6388','4.52744','30','0','0','42','0','0','0','0','0'),
(@CGUID+16,'25515','0','1','1','0','0','-8812.03','885.719','98.5385','4.4489','30','0','0','42','0','0','0','0','0'),
(@CGUID+17,'25515','0','1','1','0','0','-8814.08','873.969','98.8659','1.10232','30','0','0','42','0','0','0','0','0'),
(@CGUID+18,'25515','0','1','1','0','0','-8814.7','864.967','99.0339','1.1141','30','0','0','42','0','0','0','0','0'),
(@CGUID+19,'25515','0','1','1','0','0','-8821.88','870.852','98.7882','4.06092','30','0','0','42','0','0','0','0','0'),
(@CGUID+20,'25515','0','1','1','0','0','-8807.15','878.687','98.8254','3.52921','30','0','0','42','0','0','0','0','0'),
(@CGUID+21,'25515','0','1','1','0','0','-8823.06','855.943','99.045','1.4479','30','0','0','42','0','0','0','0','0'),
(@CGUID+22,'25515','1','1','1','0','0','1932.16','-4325.71','20.1871','4.38482','30','0','0','42','0','0','0','0','0'),
(@CGUID+23,'25515','1','1','1','0','0','1946.67','-4327.83','22.6344','3.60335','30','0','0','42','0','0','0','0','0'),
(@CGUID+24,'25515','1','1','1','0','0','1943','-4339.9','21.5222','3.88609','30','0','0','42','0','0','0','0','0'),
(@CGUID+25,'25515','1','1','1','0','0','1934.19','-4334.65','20.0495','3.48554','30','0','0','42','0','0','0','0','0'),
(@CGUID+26,'25515','1','1','1','0','0','1930.03','-4346.83','19.7546','3.8429','30','0','0','42','0','0','0','0','0'),
(@CGUID+27,'25515','1','1','1','0','0','1940.22','-4353.12','20.1355','4.05967','30','0','0','42','0','0','0','0','0'),
(@CGUID+28,'25515','1','1','1','0','0','1932.25','-4361.06','20.9716','2.11973','30','0','0','42','0','0','0','0','0'),
(@CGUID+29,'25515','0','1','1','0','0','1833.6','223.202','60.3987','2.25109','30','0','0','42','0','0','0','0','0'),
(@CGUID+30,'25515','0','1','1','0','0','1831.21','233.347','60.134','1.62277','30','0','0','42','0','0','0','0','0'),
(@CGUID+31,'25515','0','1','1','0','0','1832.31','244.952','59.9711','1.24735','30','0','0','42','0','0','0','0','0'),
(@CGUID+32,'25515','0','1','1','0','0','1832.3','256.49','59.6549','2.65793','30','0','0','42','0','0','0','0','0'),
(@CGUID+33,'25515','0','1','1','0','0','1822.36','261.071','59.9183','4.76437','30','0','0','42','0','0','0','0','0'),
(@CGUID+34,'25515','0','1','1','0','0','1823.9','252.272','60.0337','4.96229','30','0','0','42','0','0','0','0','0'),
(@CGUID+35,'25515','0','1','1','0','0','1814.4','247.51','60.5868','5.74847','30','0','0','42','0','0','0','0','0'),
(@CGUID+36,'25515','0','1','1','0','0','1821.79','238.343','60.6741','4.77144','30','0','0','42','0','0','0','0','0'),
(@CGUID+37,'25515','0','1','1','0','0','-4698.32','-1214.39','501.66','1.4847','30','0','0','42','0','0','0','0','0'),
(@CGUID+38,'25515','0','1','1','0','0','-4701.21','-1204.98','501.66','2.14051','30','0','0','42','0','0','0','0','0'),
(@CGUID+39,'25515','0','1','1','0','0','-4711.01','-1195.42','501.675','2.40362','30','0','0','42','0','0','0','0','0'),
(@CGUID+40,'25515','0','1','1','0','0','-4724.79','-1194.03','501.696','5.31745','30','0','0','42','0','0','0','0','0'),
(@CGUID+41,'25515','0','1','1','0','0','-4714.44','-1204.85','501.66','5.40384','30','0','0','42','0','0','0','0','0'),
(@CGUID+42,'25515','0','1','1','0','0','-4727.47','-1205.35','501.696','4.54775','30','0','0','42','0','0','0','0','0'),
(@CGUID+43,'25515','0','1','1','0','0','-4718.13','-1216.85','501.66','5.08575','30','0','0','42','0','0','0','0','0'),
(@CGUID+44,'25515','0','1','1','0','0','-4692.04','-1200.08','501.66','3.52281','30','0','0','42','0','0','0','0','0');

DELETE FROM `game_event_creature` WHERE `guid` BETWEEN @CGUID+13 AND @CGUID+44;
INSERT INTO `game_event_creature` (`eventEntry`, `guid`) VALUES
(1,@CGUID+13),
(1,@CGUID+14),
(1,@CGUID+15),
(1,@CGUID+16),
(1,@CGUID+17),
(1,@CGUID+18),
(1,@CGUID+19),
(1,@CGUID+20),
(1,@CGUID+21),
(1,@CGUID+22),
(1,@CGUID+23),
(1,@CGUID+24),
(1,@CGUID+25),
(1,@CGUID+26),
(1,@CGUID+27),
(1,@CGUID+28),
(1,@CGUID+29),
(1,@CGUID+30),
(1,@CGUID+31),
(1,@CGUID+32),
(1,@CGUID+33),
(1,@CGUID+34),
(1,@CGUID+35),
(1,@CGUID+36),
(1,@CGUID+37),
(1,@CGUID+38),
(1,@CGUID+39),
(1,@CGUID+40),
(1,@CGUID+41),
(1,@CGUID+42),
(1,@CGUID+43),
(1,@CGUID+44);

DELETE FROM `gameobject` WHERE `guid` IN (@GOGUID+52,@GOGUID+53);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(@GOGUID+52,'300068','0','1','1','1823.19','221.194','60.9658','4.08421','0','0','0.890974','-0.454055','300','0','1'),
(@GOGUID+53,'300068','0','1','1','-4702.18','-1221.19','502.491','5.2232','0','0','0.505528','-0.86281','300','0','1');

DELETE FROM `game_event_gameobject` WHERE `guid` IN (@GOGUID+52,@GOGUID+53);
INSERT INTO `game_event_gameobject` (`eventEntry`, `guid`) VALUES
(1,@GOGUID+52),
(1,@GOGUID+53);

-- Ice stone spawn
DELETE FROM gameobject WHERE guid IN (@GOGUID+54,@GOGUID+55);
DELETE FROM `gameobject` WHERE `id`=187882;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(@GOGUID+54, 187882, 547, 3, 1, -57.1839, -163.09, -1.86789, 3.03712, 0, 0, 0.998636, 0.0522129, 30, 0, 1),
(@GOGUID+55, 187882, 547, 3, 1, 131.836090, -108.008392, -1.590550, 3.614859, 0, 0, 0.998636, 0.0522129, 30, 0, 1);
DELETE FROM game_event_gameobject WHERE guid IN (@GOGUID+54,@GOGUID+55);
INSERT INTO game_event_gameobject VALUES (1,@GOGUID+54), (1,@GOGUID+55);
UPDATE gameobject_template SET ScriptName='go_ice_stone_midsummer' WHERE entry=187882;
DELETE FROM gameobject_involvedrelation WHERE id=187882;

-- Fix honor the flames quest/achiev
-- unify money reward
UPDATE `quest_template` SET `RewOrReqMoney`=37000, `RewMoneyMaxLevel`=66300 WHERE `title`='Honor the Flame';

/*######################
## flame warden (A) ##
######################*/
UPDATE `quest_template` SET `RequiredRaces`=1101 WHERE `entry`=11583 OR `entry` BETWEEN 11804 AND 11834;
UPDATE `creature_template` SET `npcflag`=`npcflag`|2 WHERE `entry`=25883 OR `entry` BETWEEN 25887 AND 25917;

-- questrelations
DELETE FROM `creature_questrelation` WHERE `quest`=11583 OR `quest` BETWEEN 11804 AND 11834;
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
-- outland
(25889,11807), -- blades edge
(25903,11821), -- nagrand
(25905,11823), -- shadowmoon
(25912,11829), -- nagrand
(25900,11818), -- hellfire
(25913,11830), -- netherstorm
(25907,11825), -- terokkar
-- kalimdor
(25883,11805), -- ashenvale
(25891,11809), -- bloodmyst
(25894,11812), -- desolace
(25899,11817), -- feralas
(25906,11824), -- teldrassil
(25888,11806), -- azuremyst
(25893,11811), -- darkshore
(25897,11815), -- dustwallow marsh
(25914,11831), -- silithus
(25916,11833), -- tanaris
(25917,11834), -- winterspring
-- eastern kingdoms
(25887,11804), -- arathi highlands
(25892,11810), -- burning steppes
(25896,11814), -- duskwood
(25901,11819), -- hillsbrad foothills
(25904,11822), -- redridge mountains
(25908,11826), -- hinterlands
(25909,11827), -- western plaguelands
(25890,11808), -- blasted lands
(25895,11813), -- dun morogh
(25898,11816), -- elwynn forest
(25902,11820), -- loch modan
(25915,11832), -- stranglethorn vale
(25911,11828), -- wetlands
(25910,11583); -- westfall

-- involvedrelations
DELETE FROM `creature_involvedrelation` WHERE `quest`=11583 OR `quest` BETWEEN 11804 AND 11834;
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
-- outland
(25889,11807), -- blades edge
(25903,11821), -- nagrand
(25905,11823), -- shadowmoon
(25912,11829), -- nagrand
(25900,11818), -- hellfire
(25913,11830), -- netherstorm
(25907,11825), -- terokkar
-- kalimdor
(25883,11805), -- ashenvale
(25891,11809), -- bloodmyst
(25894,11812), -- desolace
(25899,11817), -- feralas
(25906,11824), -- teldrassil
(25888,11806), -- azuremyst
(25893,11811), -- darkshore
(25897,11815), -- dustwallow marsh
(25914,11831), -- silithus
(25916,11833), -- tanaris
(25917,11834), -- winterspring
-- eastern kingdoms
(25887,11804), -- arathi highlands
(25892,11810), -- burning steppes
(25896,11814), -- duskwood
(25901,11819), -- hillsbrad foothills
(25904,11822), -- redridge mountains
(25908,11826), -- hinterlands
(25909,11827), -- western plaguelands
(25890,11808), -- blasted lands
(25895,11813), -- dun morogh
(25898,11816), -- elwynn forest
(25902,11820), -- loch modan
(25915,11832), -- stranglethorn vale
(25911,11828), -- wetlands
(25910,11583); -- westfall

-- spawn missing warden
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+45 AND @CGUID+55;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`,  `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+45,'25888','530','1','1','0','0','-4204.55','-12333.2','2.34492','2.74105','30','0','0','1524','0','0','0','0','0'),
(@CGUID+46,'25889','530','1','1','0','0','2024.83','6607.65','137.407','0.480902','30','0','0','1524','0','0','0','0','0'),
(@CGUID+47,'25891','530','1','1','0','0','-2175.01','-11885','32.3573','2.36091','30','0','0','1524','0','0','0','0','0'),
(@CGUID+48,'25892','0','1','1','0','0','-8231.91','-2611.69','133.167','1.84443','30','0','0','1524','0','0','0','0','0'),
(@CGUID+49,'25899','1','1','1','0','0','-4396.98','3459.2','10.8561','5.49229','30','0','0','1524','0','0','0','0','0'),
(@CGUID+50,'25903','530','1','1','0','0','-2491.53','7538.32','-1.03453','2.51409','30','0','0','3052','0','0','0','0','0'),
(@CGUID+51,'25905','530','1','1','0','0','-3926.57','2037.81','95.1806','6.08835','30','0','0','42','0','0','0','0','0'),
(@CGUID+52,'25907','530','1','1','0','0','-2983.44','4165.95','7.86408','3.07031','30','0','0','42','0','0','0','0','0'),
(@CGUID+53,'25909','0','1','1','0','0','1004.72','-1447.66','61.8342','5.14376','30','0','0','42','0','0','0','0','0'),
(@CGUID+54,'25912','530','1','1','0','0','244.981','5998.43','23.8744','2.19129','30','0','0','42','0','0','0','0','0'),
(@CGUID+55,'25913','530','1','1','0','0','3120.33','3709.94','144.328','5.38094','30','0','0','42','0','0','0','0','0');

-- warden event relation
DELETE FROM `game_event_creature` WHERE `guid` BETWEEN @CGUID+45 AND @CGUID+55;
INSERT INTO `game_event_creature` (`eventEntry`, `guid`) VALUES
(1,@CGUID+45),
(1,@CGUID+46),
(1,@CGUID+47),
(1,@CGUID+48),
(1,@CGUID+49),
(1,@CGUID+50),
(1,@CGUID+51),
(1,@CGUID+52),
(1,@CGUID+53),
(1,@CGUID+54),
(1,@CGUID+55);

/*######################
## flame keeper (H) ##
######################*/
UPDATE `quest_template` SET `RequiredRaces`=690 WHERE `entry`=11584 OR `entry` BETWEEN 11835 AND 11863;
UPDATE `creature_template` SET `npcflag`=`npcflag`|3 WHERE `entry`=25884 OR `entry` BETWEEN 25918 AND 25923 OR `entry` BETWEEN 25925 AND 25947;

-- questrelations
DELETE FROM `creature_questrelation` WHERE `quest`=11584 OR `quest` BETWEEN 11835 AND 11863;
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES
-- outland
(25926,11843), -- blades edge
(25937,11854), -- nagrand
(25938,11855), -- shadowmoon
(25947,11863), -- nagrand
(25934,11851), -- hellfire
(25918,11835), -- netherstorm
(25942,11858), -- terokkar
-- kalimdor
(25884,11841), -- ashenvale
(25929,11846), -- durotar
(25928,11845), -- desolace
(25932,11849), -- feralas
(25943,11859), -- the barrens
(25940,11856), -- stonetalon mountains
(25936,11852), -- mulgore
(25930,11847), -- dustwallow marsh
(25919,11836), -- silithus
(25921,11838), -- tanaris
(25922,11839), -- winterspring
(25945,11861), -- thousand needles
-- eastern kingdoms
(25925,11842), -- badlands
(25931,11848), -- eversong woods
(25935,11853), -- hillsbrad foothills
(25920,11837), -- stranglethorn vale
(25944,11860), -- hinterlands
(25923,11840), -- arathi highlands
(25927,11844), -- burning steppes
(25933,11850), -- ghostlands
(25939,11584), -- silverpine forest
(25941,11857), -- swamp of sorrows
(25946,11862); -- tirisfal glades

-- involvedrelations
DELETE FROM `creature_involvedrelation` WHERE `quest`=11584 OR `quest` BETWEEN 11835 AND 11863;
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES
-- outland
(25926,11843), -- blades edge
(25937,11854), -- nagrand
(25938,11855), -- shadowmoon
(25947,11863), -- nagrand
(25934,11851), -- hellfire
(25918,11835), -- netherstorm
(25942,11858), -- terokkar
-- kalimdor
(25884,11841), -- ashenvale
(25929,11846), -- durotar
(25928,11845), -- desolace
(25932,11849), -- feralas
(25943,11859), -- the barrens
(25940,11856), -- stonetalon mountains
(25936,11852), -- mulgore
(25930,11847), -- dustwallow marsh
(25919,11836), -- silithus
(25921,11838), -- tanaris
(25922,11839), -- winterspring
(25945,11861), -- thousand needles
-- eastern kingdoms
(25925,11842), -- badlands
(25931,11848), -- eversong woods
(25935,11853), -- hillsbrad foothills
(25920,11837), -- stranglethorn vale
(25944,11860), -- hinterlands
(25923,11840), -- arathi highlands
(25927,11844), -- burning steppes
(25933,11850), -- ghostlands
(25939,11584), -- silverpine forest
(25941,11857), -- swamp of sorrows
(25946,11862); -- tirisfal glades

-- spawn missing keeper
DELETE FROM `creature` WHERE `guid` BETWEEN @CGUID+56 AND @CGUID+59;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`,  `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+56,'25918','530','1','1','0','0','2939.25','3707.13','143.35','2.41213','30','0','0','42','0','0','0','0','0'),
(@CGUID+57,'25926','530','1','1','0','0','2299.3','6140.85','134.987','2.15454','30','0','0','42','0','0','0','0','0'),
(@CGUID+58,'25936','1','1','1','0','0','-2325.35','-612.436','-8.94079','0.669778','30','0','0','42','0','0','0','0','0'),
(@CGUID+59,'25938','530','1','1','0','0','-3079.78','2433.31','63.9935','0.138969','30','0','0','42','0','0','0','0','0');

-- keeper event relation
DELETE FROM `game_event_creature` WHERE `guid` BETWEEN @CGUID+56 AND @CGUID+59;
INSERT INTO `game_event_creature` (`eventEntry`, `guid`) VALUES
(1,@CGUID+56),
(1,@CGUID+57),
(1,@CGUID+58),
(1,@CGUID+59);

-- update slave pens npc stats
UPDATE creature_template SET faction_A=16, faction_H=16, minlevel=83, maxlevel=83, EXP=0, mindmg=700, maxdmg=800, attackpower=750, dmg_multiplier=7.5, mechanic_immune_mask=617299803, health_mod=92.8444 WHERE entry=25740; -- Ahune (N)
UPDATE creature_template SET faction_A=16, faction_H=16, minlevel=83, maxlevel=83, EXP=0, mindmg=700, maxdmg=800, attackpower=750, dmg_multiplier=13, mechanic_immune_mask=617299803, health_mod=92.8444 WHERE entry=26338; -- Ahune (H)
UPDATE creature_template SET faction_A=16, faction_H=16, minlevel=83, maxlevel=83, EXP=0, health_mod=86.7769, mechanic_immune_mask=617299803, unit_flags=131076 WHERE entry IN (25865,26339); -- Frozen Core (N/H)
UPDATE creature_template SET faction_A=16, faction_H=16, minlevel=80, maxlevel=80, EXP=0, health_mod=18.8693, mindmg=600, maxdmg=700, attackpower=650, dmg_multiplier=7.5 WHERE entry IN (25755,26342); -- Hailstone (N/H)
UPDATE creature_template SET faction_A=16, faction_H=16, minlevel=80, maxlevel=80, EXP=0, health_mod=3.5380, mindmg=400, maxdmg=500, attackpower=450, dmg_multiplier=7.5 WHERE entry IN (25756,26340); -- Coldwave (N/H)
UPDATE creature_template SET faction_A=16, faction_H=16, mindmg=400, maxdmg=500, attackpower=450, dmg_multiplier=7.5 WHERE entry IN (25757,26341); -- Frostwind (N/H)

-- ahune script
UPDATE `creature_template` SET `ScriptName`='boss_ahune' WHERE `entry` = 25740;
UPDATE `creature_template` SET `ScriptName`='mob_frozen_core' WHERE `entry` = 25865;
UPDATE `creature_template` SET `ScriptName`='mob_ahunite_hailstone' WHERE `entry` = 25755;
UPDATE `creature_template` SET `ScriptName`='mob_ahunite_coldwave' WHERE `entry` = 25756;
UPDATE `creature_template` SET `ScriptName`='mob_ahunite_frostwind' WHERE `entry` = 25757;
UPDATE gameobject SET spawnmask = 0 WHERE id = 187892;
UPDATE `gameobject_template` SET `faction` = 0 WHERE `entry` = 187892;

-- Ice Chest Loot
DELETE FROM gameobject_loot_template WHERE entry=28682;
INSERT INTO gameobject_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount) VALUES
(28682,35723,100,1,0,1,1),
(28682,35557,95,1,0,1,2),
(28682,35720,90,1,0,1,6),
(28682,35498,5,1,1,1,1),
(28682,54805,0,1,2,1,1),
(28682,54804,0,1,2,1,1),
(28682,54803,0,1,2,1,1),
(28682,54802,0,1,2,1,1),
(28682,54801,0,1,2,1,1);

DELETE FROM creature WHERE id=25740 OR guid=@CGUID+60;
DELETE FROM game_event_creature WHERE guid=@CGUID+60;
INSERT INTO creature (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`,  `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES
(@CGUID+60,25740,547,3,1,0,0,-97.084167,-205.559113,-1.198052,1.644453,86400,0,0,0,0,0,0,0,0);

-- Uncomment this if you don't use TDB
/* Gameobject from TDB
DELETE FROM gameobject_template WHERE entry = 300068;
INSERT INTO gameobject_template (entry, type, displayId, name, IconName, castBarCaption, unk1, faction, flags, size, questItem1, questItem2, questItem3, questItem4, questItem5, questItem6, data0, data1, data2, data3, data4, data5, data6, data7, data8, data9, data10, data11, data12, data13, data14, data15, data16, data17, data18, data19, data20, data21, data22, data23, AIName, ScriptName, WDBVerified) VALUES
('300068','8','0','TEMP Midsummer Bonfire','','','','0','0','1','0','0','0','0','0','0','1365','10','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','','1');*/
