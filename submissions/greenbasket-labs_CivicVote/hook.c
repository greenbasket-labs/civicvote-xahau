#include "hookapi.h"

/*
 CivicVote Hook
 Enforces:
  - Voting time window
  - One vote per address
  - Valid voting options only
  - Immutable rules after deployment
*/

int64_t hook(uint32_t reserved)
{
    // Only process transactions with Memo (vote tx)
    if (otxn_type() != ttPAYMENT)
        accept(SBUF("Non-vote transaction"), 0);

    // Get ledger close time
    int64_t now = ledger_last_time();

    // Load voting window from Hook State
    int64_t start_time = 0;
    int64_t end_time   = 0;

    state(&start_time, sizeof(start_time), SBUF("vote_start"));
    state(&end_time, sizeof(end_time), SBUF("vote_end"));

    // Enforce voting window
    if (now < start_time)
        rollback(SBUF("Voting has not started"), 10);

    if (now > end_time)
        rollback(SBUF("Voting has ended"), 11);

    // Get sender address
    uint8_t voter[20];
    otxn_field(voter, sizeof(voter), sfAccount);

    // Build voter key: voter_<address>
    uint8_t voter_key[64];
    int voter_key_len = util_keylet(
        voter_key,
        sizeof(voter_key),
        SBUF("voter_"),
        voter,
        sizeof(voter)
    );

    // Check if voter already voted
    int64_t voted = 0;
    if (state(&voted, sizeof(voted), voter_key, voter_key_len) > 0)
        rollback(SBUF("Address already voted"), 12);

    // Read vote option from Memo
    uint8_t memo[32];
    int memo_len = otxn_field(memo, sizeof(memo), sfMemoData);

    if (memo_len <= 0)
        rollback(SBUF("Missing vote option"), 13);

    // Only allow predefined options: YES or NO
    if (
        !BUFFER_EQUAL(memo, memo_len, SBUF("YES")) &&
        !BUFFER_EQUAL(memo, memo_len, SBUF("NO"))
    )
        rollback(SBUF("Invalid vote option"), 14);

    // Mark voter as voted
    voted = 1;
    state_set(&voted, sizeof(voted), voter_key, voter_key_len);

    // Increment option counter
    int64_t count = 0;
    state(&count, sizeof(count), memo, memo_len);
    count++;
    state_set(&count, sizeof(count), memo, memo_len);

    accept(SBUF("Vote accepted"), 0);
}
