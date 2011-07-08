-- Q11706 & Q11723
UPDATE creature_template SET KillCredit1=25742, KillCredit2=25794 WHERE entry=25629;
DELETE FROM gameobject WHERE guid=950103;
INSERT INTO gameobject VALUES ('950103','300177','571','1','1','3486.24','4516.06','-20.7393','6.00184','0','0','0.140211','-0.990122','300','0','1');
UPDATE item_template SET ScriptName='item_snq_control_unit' WHERE entry=34981;
