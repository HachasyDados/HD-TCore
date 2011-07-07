-- Ruby sanctum
UPDATE `instance_template` SET `Script`='instance_ruby_sanctum_custom' WHERE `map`=724;
-- Halion
UPDATE `creature_template` SET `ScriptName`='boss_halion_real_custom', `AIName` ='' WHERE `entry`=39863;
UPDATE `creature_template` SET `ScriptName`='boss_halion_twilight_custom', `AIName` ='' WHERE `entry`=40142;
UPDATE `creature_template` SET `ScriptName`='mob_halion_meteor_custom', `AIName` ='' WHERE `entry` = 40029;
UPDATE `creature_template` SET `ScriptName`='mob_halion_flame_custom', `AIName` ='' WHERE `entry` IN (40041);
UPDATE `creature_template` SET `ScriptName`='mob_halion_control_custom', `AIName` ='' WHERE `entry` IN (40146);
UPDATE `creature_template` SET `ScriptName`='mob_halion_orb_custom', `AIName` ='' WHERE `entry` IN (40083,40100);
UPDATE `creature_template` SET `ScriptName`='mob_orb_rotation_focus_custom', `AIName` ='' WHERE `entry` = 40091;
UPDATE `creature_template` SET `ScriptName`='mob_orb_carrier_custom', `AIName` ='' WHERE `entry` = 40081;
UPDATE `creature_template` SET `ScriptName`='mob_fiery_combustion_custom', `AIName` ='' WHERE `entry` = 40001;
UPDATE `creature_template` SET `ScriptName`='mob_soul_consumption_custom', `AIName` ='' WHERE `entry` = 40135;
UPDATE `creature_template` SET `ScriptName`='', `AIName` ='' WHERE `entry` IN (40143, 40144, 40145);

-- spell_halion_fiery_combustion 74562
DELETE FROM `spell_script_names` WHERE `spell_id`=74562 AND `ScriptName`='spell_halion_fiery_combustion';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (74562,'spell_halion_fiery_combustion_custom');

-- spell_halion_soul_consumption 74792
DELETE FROM `spell_script_names` WHERE `spell_id`=74792 AND `ScriptName`='spell_halion_soul_consumption';
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES (74792,'spell_halion_soul_consumption_custom');


UPDATE `gameobject_template` SET `data10` = 74807, `faction` = '0', `ScriptName` = 'go_halion_portal_twilight_custom' WHERE `gameobject_template`.`entry` IN (202794,202795);
UPDATE `gameobject_template` SET `faction` = '0', `ScriptName` = 'go_halion_portal_real_custom' WHERE `gameobject_template`.`entry` IN (202796);

-- Baltharus
UPDATE `creature_template` SET `ScriptName`='boss_baltharus_custom', `AIName` ='', `dmg_multiplier` = 80  WHERE `entry`=39751;
UPDATE `creature_template` SET `ScriptName`='mob_baltharus_clone_custom', `AIName` ='', `dmg_multiplier` = 80  WHERE `entry`=39899;

-- zarithrian
UPDATE `creature_template` SET `ScriptName`='boss_zarithrian_custom', `AIName` ='' WHERE `entry`=39746;
UPDATE `creature_template` SET `unit_flags`=0 WHERE `entry` IN (39746,39805);
UPDATE `creature` SET `position_x` = '3008.552734',`position_y` = '530.471680',`position_z` = '89.195290',`orientation` = '6.16' WHERE `id` = 39746;
UPDATE `creature_template` SET `ScriptName`='mob_flamecaller_ruby_custom', `AIName` ='' WHERE `entry`=39814;

-- Saviana Ragefire
UPDATE `creature_template` SET `ScriptName`='boss_ragefire_custom', `AIName` ='' WHERE `entry`=39747;
DELETE FROM `conditions` WHERE `SourceEntry`=74455;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceGroup`,`SourceEntry`,`ElseGroup`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`,`ConditionValue3`,`ErrorTextId`,`ScriptName`,`Comment`) VALUES
(13,0,74455,0,18,1,39747,0,0, '', 'Ragefire - Conflagration');

-- Xerestrasza
UPDATE `creature_template` SET `ScriptName`='mob_xerestrasza_custom', `AIName` ='' WHERE `entry`=40429;

-- Trash mobs
UPDATE `creature_template` SET `ScriptName`='npc_convocadora_carboescala', `AIName`='' WHERE `entry`=40417;
UPDATE `creature_template` SET `ScriptName`='npc_acometedor_carboescala', `AIName`='' WHERE `entry`=40419;
UPDATE `creature_template` SET `ScriptName`='npc_elite_carboescala', `AIName`='' WHERE `entry`=40421;
UPDATE `creature_template` SET `ScriptName`='npc_comandante_carboescala', `AIName`='' WHERE `entry`=40423;

-- Updates dmg & inmunidad
UPDATE `creature_template` SET `mindmg`=600, `maxdmg`=700, `attackpower`=800, `dmg_multiplier`=35 WHERE `entry` IN (39814,39815,40417,40418,40419,40420,40421,40422,40423,40424); -- trash
UPDATE `creature_template` SET `mindmg`=700, `maxdmg`=800, `attackpower`=850, `dmg_multiplier`=35, `mechanic_immune_mask`=617299803 WHERE `entry` IN (39747,39823,39746,39805,39751,39920,39899,39922,39863,39864,40142,39944,39945,40143,40144,40145); -- bosses

-- Respawn
UPDATE `creature` SET `spawntimesecs`=604800 WHERE `map`=724;

-- Loot minibosses
DELETE FROM `creature_loot_template` WHERE `entry`=39747;
INSERT INTO `creature_loot_template` VALUES (39747,49426,100,1,0,1,1);
UPDATE `creature_template` SET `lootid`=39747 WHERE `entry` IN (39747,39823,39751,39920,39746,39805);

-- sound / text
DELETE FROM `script_texts` WHERE `entry` BETWEEN -1666406 AND -1666000;

-- xerestrasza
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) VALUES
('-1666000','Help! I am trapped within this tree! I require aid!','???????! ? ??? ???? ???????. ??? ????? ??????!','17490','6','0','0','SAY_XERESTRASZA_YELL_1'),
('-1666001','Thank you! I could have not held out for much longer. A terrible thing has happened here.','???????! ??? ??? ? ?? ????? ?? ????????????... ????? ????????? ???????? ???????...','17491','0','0','0','SAY_XERESTRASZA_YELL_2'),
('-1666002','We believed that the Sanctum was well fortified, but we were not prepareted for the nature of this assault.','????????? ????????? ????????????, ?? ?? ??? ??? ??? ?? ???????????? ?????? ??????...','17492','0','0','0','SAY_XERESTRASZA_SAY_1'),
('-1666003','The Black Dragonkin materialized from thin air, and set upon us before we could react.','?????? ??????? ??????? ?? ????????. ?? ???? ?? ?????? ?????? ??? ??????????...','17493','0','0','0','SAY_XERESTRASZA_SAY_2'),
('-1666004','We did not stand a chance. As my brethren perished around me, I managed to retreat hear and bar the entrance.','???? ???? ???????, ??? ?????? ????? ???? ?? ??????. ? ? ?????????? ????? ? ?????????? ????.','17494','0','0','0','SAY_XERESTRASZA_SAY_3'),
('-1666005','They slaughtered us with cold efficiency, but the true focus of their interest seemed to be the eggs kept here in the sanctum.','??? ??????? ? ??????????? ???????????, ?? ???????? ????? ????? ???? ?????? ??? ? ?????????.','17495','0','0','0','SAY_XERESTRASZA_SAY_4'),
('-1666006','The commander of the forces on the ground here is a cruel brute named Zarithrian. But I fear there are greater powers at work.',' ?????? ????????? ??????????? ?????????, ??, ?????, ??? ???????? ? ????? ?????????????? ???.','17496','0','0','0','SAY_XERESTRASZA_SAY_5'),
('-1666007','In their initial assault I caught a glimpse of their true leader, a fearsome full-grown Twilight Dragon.','? ????? ?????? ? ??????? ??????????? ?? ?????????? ?????? - ????????? ??????????? ???????.','17497','0','0','0','SAY_XERESTRASZA_SAY_6'),
('-1666008','I know not the extent of their plans heroes, but I know this: they cannot be allowed to succeed!','?????, ??? ?? ?????? ???? ?????????? ??? ??????????. ???? ? ???? ????? - ?? ????? ??????????!','17498','0','0','0','SAY_XERESTRASZA_SAY_7'),

-- Halion
('-1666100','Meddlesome insects, you\'re too late! The Ruby Sanctum is lost.','?????????? ???????! ?? ????????. ????????? ????????? ????!','17499','6','0','0','SAY_HALION_SPAWN'),
('-1666101','Your world teeters on the brink of annihilation. You will all bear witness to the coming of a new age of destruction!','???? ??? ???-??? ??????????? ? ??????. ??? ?????? ????? ?????? ?????? ??? ??????????!','17500','6','0','0','SAY_HALION_AGGRO'),
('-1666102','Another hero falls.','??????? ??? ????? ???????','17501','6','0','0','SAY_HALION_SLAY_1'),
('-1666103','Ha Ha Ha!','','17502','6','0','0','SAY_HALION_SLAY_2'),
('-1666104','Relish this victory mortals, for it will be your last. This world will burn with the Master\'s return!','??? ???? ????????? ??????. ??????????? ?????? ?? ??????. ??? ????? ???????? ??? ????????, ???? ??? ?????? ? ????!','17503','6','0','0','SAY_HALION_DEATH'),
('-1666105','Not good enough!','???????!','17504','6','0','0','SAY_HALION_BERSERK'),
('-1666106','The heavens burn!','?????? ? ????!','17505','6','0','0','SAY_HALION_SPECIAL_1'),
('-1666107','Beware the shadow!','','17506','6','0','0','SAY_HALION_SPECIAL_2'),
('-1666108','You will find only suffering within the realm of Twilight. Enter if you dare.','?? ??????? ?????? ???? ? ???? ???????. ???????, ???? ????????.','17507','6','0','0','SAY_HALION_PHASE_2'),
('-1666109','I am the light AND the darkness! Cower mortals before the Herald of Deathwing!','? ???? ???? ? ? ???? ????! ?????????, ?????????, ????? ??????????? ???????????!','17508','6','0','0','SAY_HALION_PHASE_3'),
('-1666110','<need translate>','?? ??????????? ?????? ?????????? ?????? ???????!','0','3','0','0',''),
('-1666111','<need translate>','???? ???????? ??????????? ??????? ?????? ? ?????????? ???!','0','3','0','0',''),
('-1666112','<need translate>','???? ???????? ??????????? ??????? ?????? ? ???????? ???!','0','3','0','0',''),
('-1666113','<need translate>','???????? ? ????? ? ????? ?? ?????, ?????? ??????????????? ????????? ????.','0','3','0','0',''),

-- Zarthrian
('-1666200','Alexstrasza has chosen capable allies. A pity that I must end you!','?????????? ??????? ????????? ?????????... ????, ??? ???????? ?????????? ???!','17512','6','0','0','SAY_ZARITHRIAN_AGGRO'),
('-1666201','You thought you stood a chance?','????? ???? ? ?????????!','17513','6','0','0','SAY_ZARITHRIAN_SLAY_1'),
('-1666202','It\'s for the best.','??? ?????? ? ???????!','17514','6','0','0','SAY_ZARITHRIAN_SLAY_2'),
('-1666203','Halion! I\'m...aah!','??????! ?...','17515','6','0','0','SAY_ZARITHRIAN_DEATH'),
('-1666204','Turn them to ash, minions!','?????! ???????? ?? ? ?????!','17516','6','0','0','SAY_ZARITHRIAN_SPECIAL_1'),

-- baltharus
('-1666300','Ah, the entertainment has arrived...','?-?-?, ???? ???????.','17520','6','0','0','SAY_BALTHARUS_AGGRO'),
('-1666301','Baltharus leaves no survivors!','?????? ?? ????????? ?????!','17521','6','0','0','SAY_BALTHARUS_SLAY_1'),
('-1666302','This world has enough heroes!','? ???? ??????? ?????? ? ??? ????...','17522','6','0','0','SAY_BALTHARUS_SLAY_2'),
('-1666303','I...didn\'t see that coming...','???… ??? ????? ??????????..','17523','1','0','0','SAY_BALTHARUS_DEATH'),
('-1666304','Twice the pain and half the fun!','????? ??????? ?????????.','17524','6','0','0','SAY_BALTHARUS_SPECIAL_1'),
('-1666305','Your power wanes, ancient one! Soon, you will join your friends!','???? ???? ?? ??????, ??????????! ????? ?? ?????????????? ? ????? ???????!','17525','6','0','0','SAY_BALTHARUS_YELL'),

-- saviana
('-1666400','You will suffer for this intrusion...','???-?-?? ???? ?-c????? ?????? ?? ??? ?????????!','17528','6','0','0','SAY_SAVIANA_AGGRO'),
('-1666401','As it should be!','??? ? ?????? ????!','17529','6','0','0','SAY_SAVIANA_SLAY_1'),
('-1666402','Halion will be pleased...','?????? ????? ???????!','17530','6','0','0','SAY_SAVIANA_SLAY_2'),
('-1666403','<screaming>','?...','17531','6','0','0','SAY_SAVIANA_DEATH'),
('-1666404','Burn in the master\'s flame!','?????? ? ???? ???????!','17532','6','0','0','SAY_SAVIANA_SPECIAL_1'),
('-1666405','<need translate>','|3-3(%s) ??????? ? ???????????!','0','3','0','0','');

update script_texts set content_loc6='¡Ayuda! ¡Estoy atrapada dentro del árbol! ¡Ayudadme!', content_loc7=content_loc6 where entry=-1666000;
update script_texts set content_loc6='Gracias. No podía aguantar mucho más. Aquí ha sucedido algo terrible.', content_loc7=content_loc6 where entry=-1666001;
update script_texts set content_loc6='Creíamos que el Sagrario estaba bien protegido, pero no estábamos preparados para un ataque como este.', content_loc7=content_loc6 where entry=-1666002;
update script_texts set content_loc6='Los dragonantes negros aparecieron de la nada, y atacaron antes de que pudiésemos reaccionar.', content_loc7=content_loc6 where entry=-1666003;
update script_texts set content_loc6='La defensa fue inútil. Mientras mis hermanos morían, conseguí retirarme aquí y bloquear la entrada.', content_loc7=content_loc6 where entry=-1666004;
update script_texts set content_loc6='Fue una masacre calculada y eficaz. Pero su verdadero objetivo eran los huevos que guardamos en el Sagrario.', content_loc7=content_loc6 where entry=-1666005;
update script_texts set content_loc6='El comandante de las fuerzas terrestres, es un bruto cruel llamado Zarithrian, pero me temo que hay implicados poderes mayores.', content_loc7=content_loc6 where entry=-1666006;
update script_texts set content_loc6='En el ataque inicial, pude ver a su verdadero líder: un temible dragón crepuscular, adulto.', content_loc7=content_loc6 where entry=-1666007;
update script_texts set content_loc6='No conozco todos sus planes, héroes, pero sé que no debemos permitir que tengan éxito.', content_loc7=content_loc6 where entry=-1666008;

update script_texts set content_loc6='Insectos entrometidos. Llegáis tarde. El Sagrario Rubí está perdido.', content_loc7=content_loc6 where entry=-1666100;
update script_texts set content_loc6='Vuestro mundo está al borde de la aniquilación. ¡Todos seréis testigos de la llegada de una nueva era de destrucción!', content_loc7=content_loc6 where entry=-1666101;
update script_texts set content_loc6='Cae otro "héroe".', content_loc7=content_loc6 where entry=-1666102;
update script_texts set content_loc6='¡Ha ha ha ha ha!', content_loc7=content_loc6 where entry=-1666103;
update script_texts set content_loc6='Disfrutad la victoria mortales, porque será la última. Este mundo arderá cuando vuelva el maestro.', content_loc7=content_loc6 where entry=-1666104;
update script_texts set content_loc6='¡No es suficiente!', content_loc7=content_loc6 where entry=-1666105;
update script_texts set content_loc6='¡Los cielos arden!', content_loc7=content_loc6 where entry=-1666106;
update script_texts set content_loc6='¡Temed la sombra!', content_loc7=content_loc6 where entry=-1666107;
update script_texts set content_loc6='En el reino del Crepúsculo solo encontraréis sufrimiento. Entrad, si os atrevéis.', content_loc7=content_loc6 where entry=-1666108;
update script_texts set content_loc6='¡Yo soy la luz y la oscuridad! ¡Temed, mortales, la llegada de Alamuerte!', content_loc7=content_loc6 where entry=-1666109;
update script_texts set content_loc6='unk0', content_loc7=content_loc6 where entry=-1666110;
update script_texts set content_loc6='unk1', content_loc7=content_loc6 where entry=-1666111;
update script_texts set content_loc6='unk2', content_loc7=content_loc6 where entry=-1666112;
update script_texts set content_loc6='unk3', content_loc7=content_loc6 where entry=-1666113;

update script_texts set content_loc6='Alexstrasza sabe elegir a sus aliados. ¡Lástima tener que mataros!', content_loc7=content_loc6 where entry=-1666200;
update script_texts set content_loc6='¡¿Pensabas sobrevivir?!', content_loc7=content_loc6 where entry=-1666201;
update script_texts set content_loc6='¡Es por tu bien!', content_loc7=content_loc6 where entry=-1666202;
update script_texts set content_loc6='Halion, yo... ¡Aah!', content_loc7=content_loc6 where entry=-1666203;
update script_texts set content_loc6='¡Reducidlos a cenizas, esbirros!', content_loc7=content_loc6 where entry=-1666204;

update script_texts set content_loc6='¡Ah, ha llegado la diversión!', content_loc7=content_loc6 where entry=-1666300;
update script_texts set content_loc6='¡Baltharus no deja supervivientes!', content_loc7=content_loc6 where entry=-1666301;
update script_texts set content_loc6='¡Ya hay suficientes héroes!', content_loc7=content_loc6 where entry=-1666302;
update script_texts set content_loc6='¡Oaaah! No lo ví venir...', content_loc7=content_loc6 where entry=-1666303;
update script_texts set content_loc6='¡El doble de dolor y la mitad de diversión!', content_loc7=content_loc6 where entry=-1666304;
update script_texts set content_loc6='¡Tu poder decae, ancestro! ¡Pronto te unirás a tus amigos!', content_loc7=content_loc6 where entry=-1666305;

update script_texts set content_loc6='¡Sufriréis por esta intrusión!', content_loc7=content_loc6 where entry=-1666400;
update script_texts set content_loc6='¡Como debe ser!', content_loc7=content_loc6 where entry=-1666401;
update script_texts set content_loc6='¡Halion estará satisfecho!', content_loc7=content_loc6 where entry=-1666402;
update script_texts set content_loc6='¡Uaaaaaaagh!', content_loc7=content_loc6 where entry=-1666403;
update script_texts set content_loc6='¡Arded en la llama del maestro!', content_loc7=content_loc6 where entry=-1666404;
update script_texts set content_loc6='¡Saviana ha enfurecido!', content_loc7=content_loc6 where entry=-1666405;
