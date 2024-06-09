#pragma once


namespace ehm_dal::flags {

// Flag table indexes
enum class FlagIndex : char {
    NO_TABLE = -1,
    AFFILIATION_DEPENDENCY = 0,
    AFFILIATION_TYPE,
    ARENA_ICE_CONDITION,
    ARENA_RINK_SIZE,
    ARENA_RULES,
    AWARD_TYPE,
    BASIC_RULES_FLAGS,
    CLUB_VALUATION,
    COMP_CLASSIFICATION,
    COMP_SCOPE,
    COMP_SELECTED_FLAG,
    COMP_TYPE,
    CONTINENTAL_LICENCE,
    DAY,
    DECLARED_NATION,
    DEVELOPMENT_STATE,
    EXTRA_MATCH_RULES,
    EXTRA_RULE_TYPE,
    FATE_RULES,
    FATE_TO_DRAW_FROM,
    FIGHTING_PENALTY,
    GAME_IMPORTANCE,
    GENDER,
    GROUP,
    GROUP_MEMBERSHIP,
    HANDEDNESS,
    IIHF_JUNIOR_DIVISION,
    IIHF_SENIOR_DIVISION,
    JOB,
    JOB_LEVEL,
    JUNIOR_PREFERENCE,
    LANGUAGE,
    LEAGUE_SELECTED,
    MATCH_RULES,
    MISCONDUCT_ACCUMULATOR_TYPE,
    MONTH,
    NAME_EXTRA_FLAGS,
    PLAYER_POSITION,
    PLAYER_ROLE,
    PRIZE_MONEY_TYPE,
    PROFESSIONAL_STATUS,
    REGION_ACTUAL,
    REGION_APPROXIMATE,
    REPLAY_RULES,
    ROUND,
    ROUND_RULES,
    RULING_BODY_FLAGS,
    RULING_BODY_TYPE,
    SALARY_CAP,
    SORT_RULE,
    SQUAD_SELECTED,
    STAFF_CLASSIFICATION,
    STAFF_EXTRA_FLAGS,
    STAGE,
    STAGE_TYPE,
    STATS_SCOPE,
    TACTIC,
    TEAM_PICKING_RULES,
    TIME_OF_DAY,
    TRANSFER_RULES_FLAGS,
    TRANSFER_SYSTEM,
    TV_TYPE,
    WIN_PCT_TYPE,
    FLAG_TABLE_COUNT
};

} // namespace ehm_dal::flags


