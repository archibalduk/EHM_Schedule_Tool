#pragma once

// Application headers
#include "include/data_types/attribute/current_ability.h"

namespace ehm_dal::data_types {
/*!
 * \brief The PotentialAbility class is a qint16 class for potential ability ranges.
 */
class PotentialAbility : public CurrentAbility
{
public:
    PotentialAbility(const qint16 value = 0)
        : CurrentAbility(value)
    {}

    /*!
     * \brief The POTENTIAL_ABILITY_RANDOM_VALUES enum denotes the EHM random Potential Ability values
     */
    enum POTENTIAL_ABILITY_RANDOM_VALUES {
        MINUS_1
        = -1, /*!< 1-20 (the worst young players - they will likely retire at a young age and keep getting recycled back into the regen pool) */
        MINUS_2 = -2, /*!< 10-40 */
        MINUS_3 = -3, /*!< 30-60 */
        MINUS_4 = -4, /*!< 50-80 */
        MINUS_5 = -5, /*!< 70-100 */
        MINUS_6 = -6, /*!< 90-120 */
        MINUS_7
        = -7, /*!< 110-140 (quite rare: a good prospect with a decent chance of being an NHL regular) */
        MINUS_8
        = -8, /*!< 130-160 (rare: a top prospect with a good chance of being a talented NHL player) */
        MINUS_9
        = -9, /*!< 150-180 (very rare: a top 10 prospect who is considered a can’t miss NHL talent) */
        MINUS_10
        = -10, /*!< 170-200 (extremely rare: the top player available in a draft, but not every year) */
        MINUS_11 = -11, /*!< 20-80 (intended for very young, hard-to-predict players) */
        MINUS_12 = -12, /*!< 40-100 (intended for very young, hard-to-predict players) */
        MINUS_13 = -13, /*!< 60-130 (intended for very young, hard-to-predict players) */
        MINUS_14 = -14, /*!< 90-160 (intended for very young, hard-to-predict players) */
        MINUS_15 = -15, /*!< 110-190 (intended for very young, hard-to-predict players) */
        MINUS_16 = -16, /*!< 70-120 (perfect for European kids - non-NHL drafted) */
        MINUS_17 = -17, /*!< 90-140 (perfect for B grade NHL prospect F) */
        MINUS_18 = -18, /*!< 110-160 (perfect for B grade NHL prospect D) */
        MINUS_19 = -19, /*!< 130-180 (ideal for later first-rounders) */
        MINUS_20 = -20, /*!< 150-200 (ideal for can't miss first round picks) */
        LOWEST_VALUE = MINUS_20
    };

private:
    inline constexpr qint16 lowerLimit() const override { return LOWEST_VALUE; }
};

} // namespace ehm_dal::data_types
