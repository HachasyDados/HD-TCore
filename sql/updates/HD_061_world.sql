DELETE FROM npc_spellclick_spells WHERE npc_entry=28222 AND spell_id=46598;
INSERT INTO npc_spellclick_spells (npc_entry, spell_id, cast_flags) VALUES (28222,46598,1);
UPDATE creature_template SET vehicleid=22, spell1=50978, spell2=50980, spell3=50983, spell4=50985, AIName='', ScriptName='' WHERE entry=28222;
UPDATE creature_template SET flags_extra=flags_extra|64 WHERE entry IN (28218,28220);
DELETE FROM conditions WHERE sourcetypeorreferenceid=17 AND sourceentry IN (50978,50980,50983,50985);
INSERT INTO conditions (sourceTypeOrReferenceId, SourceEntry, ConditionTypeOrReference, conditionvalue1, errortextid, comment) VALUES
(17,50978,23,4282,1335,'Spell1 Etimidiano limitada a Avalancha (Sholazar)'),
(17,50980,23,4282,1335,'Spell2 Etimidiano limitada a Avalancha (Sholazar)'),
(17,50983,23,4282,1335,'Spell3 Etimidiano limitada a Avalancha (Sholazar)'),
(17,50985,23,4282,1335,'Spell4 Etimidiano limitada a Avalancha (Sholazar)');
