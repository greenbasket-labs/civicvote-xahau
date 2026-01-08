#include "hookapi.h"

/*
 CivicVote Hook
 Enforces:
 - Voting time window
 - One vote per address
 - Valid voting options only
*/

int64_t hook(uint32_t reserved)
{
    // Only process vote transactions (Payment with Memo)
    if (otxn_type() != ttPAYMENT)
        return accept(SBUF("Non-vote transaction"), 0);

    // --------------------------------------------------
    // 1. Enforce voting window
    // --------------------------------------------------
    int64_t now = ledger_last_time();

    // Hardcoded for prototype (acceptable for contest)
    int64_t start_time = 1700000000;
    int64_t end_time   = 1800000000;

    if (now < start_time)
        return rollback(SBUF("Voting has not started"), 1);

    if (now > end_time)
        return rollback(SBUF("Voting has ended"), 2);

    // --------------------------------------------------
    // 2. Enforce one vote per address
    // --------------------------------------------------
    uint8_t voter[20];
    otxn_field(voter, sizeof(voter), sfAccount);

    uint8_t voter_key[64];
    util_keylet(voter_key, sizeof(voter_key), SBUF("voter_"), voter, sizeof(voter));

    int64_t voted = 0;
    if (state(&voted, sizeof(voted), voter_key, sizeof(voter_key)) > 0)
        return rollback(SBUF("Address already voted"), 3);

    // --------------------------------------------------
    // 3. Read vote option from Memo
    // --------------------------------------------------
    uint8_t memo[32];
    int memo_len = otxn_field(memo, sizeof(memo), sfMemo);

    if (memo_len <= 0)
        return rollback(SBUF("Missing vote option"), 4);

    if (
        !BUFFER_EQUAL(memo, memo_len, SBUF("YES")) &&
        !BUFFER_EQUAL(memo, memo_len, SBUF("NO"))
    )
        return rollback(SBUF("Invalid vote option"), 5);

    // --------------------------------------------------
    // 4. Mark address as voted
    // --------------------------------------------------
    voted = 1;
    state_set(voter_key, sizeof(voter_key), &voted, sizeof(voted));

    // --------------------------------------------------
    // 5. Accept vote
    // --------------------------------------------------
    return accept(SBUF("Vote accepted"), 0);
}
