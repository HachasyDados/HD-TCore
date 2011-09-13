-- Remove old data from this quest on DB
DELETE FROM conditions WHERE sourcegroup IN (SELECT gossip_menu_id FROM creature_template WHERE entry IN (36669, 36670));
DELETE FROM `gossip_menu_option` WHERE menu_id IN (SELECT gossip_menu_id FROM creature_template WHERE entry IN (36669, 36670));

-- Update npcs
UPDATE `creature_template` SET `unit_flags` = 2, `AIName` = '', `flags_extra` = 2, `ScriptName` = 'npc_dragonforged_blades_giver' WHERE `entry` IN (36670, 36669);

-- Gossip texts (only called from script)
DELETE FROM npc_text WHERE id IN (537554, 537555);
INSERT INTO npc_text (ID, text0_0) VALUES
(537554, '¡Ahi estas! Empezaba a pensar que te habían interceptado los Atracasol. ¿Estas preparado para entregar el escrito a nuestros representantes en Corona de Hielo?'),
(537555, '¡Ahi estas! Empezaba a pensar que te había interceptado el Pacto de Plata. ¿Estas preparado para entregar el escrito a nuestros representantes en Corona de Hielo?');

-- Says for Magister or Arcanist
SET @entry := -1380573;
DELETE FROM script_texts WHERE entry BETWEEN @entry-4 AND @entry;
INSERT INTO script_texts (entry, content_default, content_loc6, content_loc7, emote) VALUES
(@entry, 'Me alegro de verte al fin, mensajero. Krasus nos ha confiado una de las pocas copias que quedan de Hojas antiguas forjazas por los dragones.', content_default, content_default, 1),
(@entry-1, 'Aquí esta tu libro. Asegurate de que llegue a Caladis Lanza Reluciente en Corona de Hielo antes de que los Atracasol se  den cuenta de lo que esta ocurriendo.', content_default, content_default, 25),
(@entry-2, 'Aquí esta tu libro. Asegurate de que llegue a Myralion Resplandor en Corona de Hielo antes de que los Atracasol se  den cuenta de lo que esta ocurriendo.', content_default, content_default, 25),
(@entry-3, '¡Viaja rápido! Los Atracasol no desperdiciarán ni un minuto en cuanto sepan que tenemos la información que buscan.', content_default, content_default, 274),
(@entry-4, '¡Viaja rápido! El Pacto de Plata no desperdiciará ni un minuto en cuanto sepa que tenemos la información que buscan.', content_default, content_default, 274);