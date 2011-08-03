DELETE FROM `worldstates` WHERE `entry` = 20005;

DROP TABLE IF EXISTS `stored_db_queries`;

CREATE TABLE `stored_db_queries` (
  `active` TINYINT(1) UNSIGNED ZEROFILL DEFAULT '0' COMMENT 'if 1, query will be executed on next server start',
  `comment` VARCHAR(256) NOT NULL,
  `group` TINYINT(1) ZEROFILL DEFAULT '0',
  `query` VARCHAR(21000) NOT NULL
) ENGINE=INNODB DEFAULT CHARSET=utf8;


INSERT  INTO `stored_db_queries`(`active`,`comment`,`query`) VALUES
(2,'Borrado de los rangos de Sigilo','DELETE FROM `character_spell` WHERE spell IN (1785, 1786, 1787);'),
(2,'Borrado de los rangos de Exponer Armadura','DELETE FROM `character_spell` WHERE spell IN (8649, 8650, 11197, 11198, 26866, 48669);'),
(0,'Borrado de las quest de la Semana de los niños','DELETE FROM `character_queststatus_rewarded` WHERE quest IN(SELECT DISTINCT quest FROM `world_tdb`.`creature_questrelation` WHERE id IN (14305, 14444, 22818, 22817) UNION(SELECT DISTINCT quest FROM `world_tdb`.`creature_involvedrelation` WHERE id IN (14305, 14444, 22818, 22817)));');