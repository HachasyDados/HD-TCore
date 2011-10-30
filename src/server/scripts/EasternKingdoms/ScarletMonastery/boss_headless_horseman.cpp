// The Headless Horseman

#include "ScriptPCH.h"
#include "LFGMgr.h"

enum Yells
{
    SAY_ENTRANCE                = -1189001,
    SAY_REJOINED                = -1189002,
    SAY_LOST_HEAD               = -1189003,
    SAY_CONFLAGRATION           = -1189004,
    SAY_SPROUTING_PUMPKINS      = -1189005,
    SAY_PLAYER_DEATH            = -1189006,
    SAY_DEATH                   = -1189007
};

enum Actions
{
    ACTION_SWITCH_PHASE         = 1
};

enum Entries
{
    NPC_HEAD                    = 23775,
    NPC_PULSING_PUMPKIN         = 23694,
    NPC_PUMPKIN_FIEND           = 23545,
    GO_PUMPKIN_SHRINE           = 186267
};

enum Spells
{
    SPELL_SUMMON_PUMPKIN        = 52236, // 8s trigger 42394

    SPELL_IMMUNED               = 42556,
    SPELL_BODY_REGEN            = 42403, // regenerate health plus model change to unhorsed
    SPELL_CONFUSED              = 43105,
    SPELL_HEAL_BODY             = 43306, // heal to 100%
    SPELL_CLEAVE                = 42587,
    SPELL_WHIRLWIND             = 43116,
    SPELL_CONFLAGRATION         = 42380,

    SPELL_FLYING_HEAD           = 42399, // flying head visual
    SPELL_HEAD                  = 42413, // horseman head visual
    SPELL_HEAD_LANDS            = 42400,
    //SPELL_CREATE_PUMPKIN_TREATS = 42754,
    SPELL_RHYME_BIG             = 42909,
};

uint32 randomLaugh[]            = {11965, 11975, 11976};

static Position flightPos[]=
{
    {1764.957f, 1347.432f, 18.7f, 6.029f},
    {1774.625f, 1345.035f, 20.8f, 6.081f},
    {1789.114f, 1341.439f, 26.8f, 0.198f},
    {1798.446f, 1345.865f, 30.8f, 1.781f},
    {1791.671f, 1360.825f, 30.1f, 2.766f},
    {1777.449f, 1364.652f, 25.1f, 2.911f},
    {1770.126f, 1361.402f, 20.7f, 4.093f},
    {1772.743f, 1354.941f, 18.4f, 5.841f}
};

static char const* Text[]=
{
    "Horseman rise...",
    "Your time is nigh...",
    "You felt death once...",
    "Now, know demise!"
};

#define EMOTE_LAUGH   "Headless Horseman laughs."
#define GOSSIP_OPTION "Call the Headless Horseman."

class boss_headless_horseman : public CreatureScript
{
    public:
        boss_headless_horseman() : CreatureScript("boss_headless_horseman") { }

        struct boss_headless_horsemanAI : public ScriptedAI
        {
            boss_headless_horsemanAI(Creature* c) : ScriptedAI(c), _summons(me)
            {
            }

            SummonList _summons;
            uint8 phase;
            uint8 wpCount;
            uint8 introCount;
            uint32 introTimer;
            uint32 laughTimer;
            uint32 cleaveTimer;
            uint32 summonTimer;
            uint32 conflagTimer;
            bool wpReached;

            void Reset()
            {
                _summons.DespawnAll();

                me->SetVisible(false);
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);

                me->AddUnitMovementFlag(MOVEMENTFLAG_ONTRANSPORT | MOVEMENTFLAG_LEVITATING);
                me->SetSpeed(MOVE_RUN, 2.0f, true);
                me->SetCorpseDelay(60);

                wpCount = 0;
                introCount = 0;
                wpReached = false;
                phase = 0;

                introTimer = 1*IN_MILLISECONDS;
                laughTimer = 5*IN_MILLISECONDS;
                cleaveTimer = 3*IN_MILLISECONDS;
                summonTimer = 1*IN_MILLISECONDS;
                conflagTimer = 4*IN_MILLISECONDS;

                me->SummonGameObject(GO_PUMPKIN_SHRINE, 1776.27f, 1348.74f, 20.4116f, 0, 0, 0, 0.00518764f, -0.999987f, 0);
                DoCast(me, SPELL_HEAD, true);
            }

            void MovementInform(uint32 type, uint32 id)
            {
                if (type != POINT_MOTION_TYPE || id != wpCount)
                    return;

                if (id < 7)
                {
                    ++wpCount;
                    wpReached = true;
                }
                else // start fighting
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NOT_SELECTABLE);
                    me->RemoveUnitMovementFlag(MOVEMENTFLAG_ONTRANSPORT | MOVEMENTFLAG_LEVITATING);
                    DoZoneInCombat(me, 100.0f);

                    if (me->getVictim())
                        me->GetMotionMaster()->MoveChase(me->getVictim());

                    DoScriptText(SAY_ENTRANCE, me);
                }
            }

            void EnterCombat(Unit* /*who*/)
            {
                DoZoneInCombat(me, 100.0f);
            }

            void KilledUnit(Unit* victim)
            {
                if (!victim->ToPlayer())
                    return;

                DoScriptText(SAY_PLAYER_DEATH, me);
            }

            void JustSummoned(Creature* summon)
            {
                _summons.Summon(summon);
                summon->SetInCombatWithZone();

                // DoScriptText(SAY_SPROUTING_PUMPKINS, me);
            }

            void JustDied(Unit* /*killer*/)
            {
                DoScriptText(SAY_DEATH, me);
                _summons.DespawnAll();

                // TODO: unhack
                Map* map = me->GetMap();
                if (map && map->IsDungeon())
                {
                    Map::PlayerList const& players = map->GetPlayers();
                    if (!players.isEmpty())
                        for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
                            if (Player* player = i->getSource())
                                if (player->GetDistance(me) < 120.0f)
                                    sLFGMgr->RewardDungeonDoneFor(285, player);
                }
            }

            void DamageTaken(Unit* /*attacker*/, uint32 &damage)
            {
                if (phase > 3)
                {
                    me->RemoveAllAuras();
                    return;
                }

                if (damage >= me->GetHealth())
                {
                    damage = me->GetHealth() - 1;

                    DoCast(me, SPELL_IMMUNED, true);
                    DoCast(me, SPELL_BODY_REGEN, true);
                    DoCast(me, SPELL_CONFUSED, true);

                    Position randomPos;
                    me->GetRandomNearPosition(randomPos, 20.0f);

                    if (Creature* head = me->SummonCreature(NPC_HEAD, randomPos))
                    {
                        head->AI()->SetData(0, phase);

                        switch (phase)
                        {
                            case 2: head->SetHealth(uint32(head->GetMaxHealth() * 2 / 3)); break;
                            case 3: head->SetHealth(uint32(head->GetMaxHealth() / 3)); break;
                        }
                    }

                    me->RemoveAurasDueToSpell(SPELL_HEAD);
                }
            }

            void DoAction(int32 const action)
            {
                switch (action)
                {
                    case ACTION_SWITCH_PHASE:
                        me->RemoveAllAuras();
                        DoCast(me, SPELL_HEAL_BODY, true);
                        DoCast(me, SPELL_HEAD, true);

                        ++phase;
                        if (phase > 3)
                            me->DealDamage(me, me->GetHealth());
                        else
                            DoScriptText(SAY_REJOINED, me);

                        break;
                }
            }

            void UpdateAI(uint32 const diff)
            {
                if (!UpdateVictim())
                    return;

                if (phase == 0)
                {
                    if (introTimer <= diff)
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                        {
                            if (introCount < 3)
                                target->ToPlayer()->Say(Text[introCount], 0);
                            else
                            {
                                DoCast(me, SPELL_RHYME_BIG, true);
                                target->ToPlayer()->Say(Text[introCount], 0);
                                target->HandleEmoteCommand(ANIM_EMOTE_SHOUT);
                                phase = 1;
                                wpReached = true;
                                me->SetVisible(true);
                            }
                        }
                        introTimer = 3*IN_MILLISECONDS;
                        ++introCount;
                    }
                    else
                        introTimer -= diff;

                    return;
                }

                if (wpReached)
                {
                    wpReached = false;
                    me->GetMotionMaster()->MovePoint(wpCount, flightPos[wpCount]);
                }

                if (me->HasAura(SPELL_BODY_REGEN))
                {
                    if (me->IsFullHealth())
                    {
                        me->RemoveAllAuras();
                        DoCast(me, SPELL_HEAD, true);

                        if (Creature* head = me->FindNearestCreature(NPC_HEAD, 250.0f, true))
                        {
                            head->SetFullHealth();
                            head->RemoveAllAuras();
                            head->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                            head->DespawnOrUnsummon(3000);
                            head->CastSpell(me, SPELL_FLYING_HEAD, true);
                        }
                    }
                    else if (!me->HasAura(SPELL_WHIRLWIND) && me->GetHealthPct() > 10.0f)
                        DoCast(me, SPELL_WHIRLWIND, true);

                    return;
                }

                if (laughTimer <= diff)
                {
                    me->MonsterTextEmote(EMOTE_LAUGH, 0);
                    DoPlaySoundToSet(me, randomLaugh[rand()%3]);
                    laughTimer = urand(11, 22) *IN_MILLISECONDS;
                }
                else
                    laughTimer -= diff;

                if (me->HasReactState(REACT_PASSIVE))
                    return;

                if (cleaveTimer <= diff)
                {
                    DoCastVictim(SPELL_CLEAVE);
                    cleaveTimer = urand(2, 6) *IN_MILLISECONDS;
                }
                else
                    cleaveTimer -= diff;

                switch (phase)
                {
                    case 2:
                        if (conflagTimer <= diff)
                        {
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 30.0f, true))
                                DoCast(target, SPELL_CONFLAGRATION);
                            conflagTimer = urand(8, 12) *IN_MILLISECONDS;
                        }
                        else
                            conflagTimer -= diff;
                        break;
                    case 3:
                        if (summonTimer <= diff)
                        {
                            DoCast(me, SPELL_SUMMON_PUMPKIN, true);
                            summonTimer = 15*IN_MILLISECONDS;
                        }
                        else
                            summonTimer -= diff;
                        break;
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_headless_horsemanAI(creature);
        }
};


class npc_horseman_head : public CreatureScript
{
    public:
        npc_horseman_head() : CreatureScript("npc_horseman_head") { }

        struct npc_horseman_headAI : public ScriptedAI
        {
            npc_horseman_headAI(Creature* c) : ScriptedAI(c)
            {
                me->SetDisplayId(21908);
                me->SetReactState(REACT_PASSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED | UNIT_FLAG_NOT_SELECTABLE);
                me->GetMotionMaster()->MoveRandom(30.0f);
                DoCast(me, SPELL_HEAD, true);
                DoCast(me, SPELL_HEAD_LANDS, true);
                DoScriptText(SAY_LOST_HEAD, me);
            }

            void SetData(uint32 /*type*/, uint32 data)
            {
                _phase = data;
            }

            void DamageTaken(Unit* /*attacker*/, uint32 &damage)
            {
                int32 healthPct;

                switch (_phase)
                {
                    case 1: healthPct = 66; break;
                    case 2: healthPct = 33; break;
                    default: healthPct = 1; break;
                }

                if (me->HealthBelowPctDamaged(healthPct, damage) || damage >= me->GetHealth())
                {
                    damage = 0;
                    me->RemoveAllAuras();
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    me->DespawnOrUnsummon(3000);

                    if (me->ToTempSummon())
                        if (Unit* horseman = me->ToTempSummon()->GetSummoner())
                        {
                            if (_phase < 3)
                                DoCast(horseman, SPELL_FLYING_HEAD, true);
                            horseman->ToCreature()->AI()->DoAction(ACTION_SWITCH_PHASE);
                        }
                }
            }

        private:
            uint8 _phase;
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_horseman_headAI(creature);
        }
};

class go_pumpkin_shrine : public GameObjectScript
{
    public:
        go_pumpkin_shrine() : GameObjectScript("go_pumpkin_shrine") { }

        bool OnGossipHello(Player* player, GameObject* go)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_OPTION, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            player->SEND_GOSSIP_MENU(player->GetGossipTextId(go), go->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* player, GameObject* go, uint32 /*sender*/, uint32 action)
        {
            player->PlayerTalkClass->ClearMenus();

            if (action == GOSSIP_ACTION_INFO_DEF)
            {
                if (Unit* horseman = go->GetOwner())
                {
                    horseman->ToCreature()->AI()->AttackStart(player);
                    horseman->AddThreat(player, 1000.0f);
                    go->Delete();
                }
            }
            return true;
        }
};

void AddSC_boss_headless_horseman()
{
    new boss_headless_horseman();
    new npc_horseman_head();
    new go_pumpkin_shrine();
}
