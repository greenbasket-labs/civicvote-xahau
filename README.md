# CivicVote — On-Chain Rule-Enforced Voting on Xahau

CivicVote is a prototype on-chain voting system built on the Xahau blockchain that enforces voting rules directly at the protocol level using Xahau Hooks.

Unlike traditional voting apps that rely on backend servers or administrator logic, CivicVote embeds all voting constraints directly into Hook code. This ensures transparency, immutability, and trustless execution.

This repository serves as a **reference implementation** for governance, DAO signaling, and public decision-making tools on Xahau.

---

## What This Project Demonstrates

- How Xahau Hooks can enforce governance rules on-ledger  
- Protocol-level validation (transactions are rejected if rules are violated)  
- Voting without backend servers or admin control  
- Simple, auditable on-chain governance logic  

---

## Features

- One vote per address (enforced on-chain)
- Time-bounded voting window
- Predefined valid voting options only
- Invalid votes rejected at protocol level
- Fully transparent and verifiable behavior

---

## What This Is / What This Is Not

### What This Is
- A research and learning prototype
- A reference Hook implementation for voting
- Suitable for governance experiments and demos

### What This Is Not
- Not production-ready
- Not audited
- Not a complete DAO framework

---

## Use Cases

- Community governance polls
- DAO signaling votes
- Civic or public decision-making experiments
- Educational examples for Xahau Hooks

---

## Architecture Overview

- **Blockchain:** Xahau Mainnet  
- **Logic Enforcement:** Xahau Hooks  
- **Backend:** None  
- **Admin Privileges:** None  

All voting rules are enforced directly by the ledger.

---

## Hook Logic Summary

The Hook enforces the following rules:

1. Voting is only allowed within a fixed time window  
2. Each address can vote only once  
3. Only predefined vote options are accepted  
4. Rules cannot be changed after deployment  

Transactions that violate any rule are rejected.

---

## Hook Implementation (Prototype)

```c
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

    // Prototype values — hardcoded for demonstration
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
---

## Project Status

Early-stage prototype built for the Xahau Dev Contest (2026).

This project is intended as a reference implementation and learning resource.  
Further work may include configurable voting parameters and a simple web interface.

---

## Repository

https://github.com/greenbasket-labs/civicvote-xahau

---

## Author

Mohammed Musbahu A.  
X (Twitter): https://x.com/GreenBasketLabs  
GitHub: https://github.com/greenbasket-labs  
Contact: greenbasketgloball@gmail.com

---

## License

---

## Why This README Works (Short)

- Clear in **5 seconds**
- Honest about scope
- Invites reuse and learning
- Shows real protocol thinking
- Strong for **judges + public + recruiters**

---

### Next Step
Say **NEXT** and tell me which repo we review next:
- `basic-voting-contract`
- `casper-governance-voting`
- `continuum-protocol`

We’ll apply the **same calm, professional cleanup** repo by repo.
