# CivicVote — On-chain Rule-Enforced Voting on Xahau

## Project Title
CivicVote — On-chain Rule-Enforced Voting on Xahau

## Brief Description
CivicVote is a user-facing voting service built on the Xahau Mainnet that enforces voting rules directly on-chain using Xahau Hooks.

Instead of relying on backend servers or administrator-controlled logic, CivicVote embeds voting constraints—such as one-vote-per-address, voting time windows, and valid options—directly into Hook logic. This ensures transparency, immutability, and trustless execution.

The project demonstrates how Xahau Hooks can power real-world governance use cases such as community polls, DAO signaling, and public decision-making tools.

## Participants
Mohammed Musbahu A. (solo)

## Participants’ Social Media
- X (Twitter): https://x.com/GreenBasketLabs  
- GitHub: https://github.com/greenbasket-labs

##Contact Email
greenbasketgloball@gmail.com

## Link to the Online Project
TBD — Web interface will be publicly accessible before judging.

## Xahau Address (Prize Address)
TBD — Will be added before final submission.

## Link to Documentation
https://github.com/greenbasket-labs/civicvote-xahau

## Hooks Code
- Language: C  
- Purpose: Enforce voting rules directly on-ledger  
- Files: hook.c (to be added)

## Hook Logic Summary
The Hook enforces:
- Voting allowed only within a defined time window  
- One vote per address  
- Only predefined vote options accepted  
- Voting rules cannot be modified after deployment  

Invalid transactions are rejected at the protocol level.

## Hook Hash
TBD — Will be added after deployment.

## Hook Account
TBD — Will be added after deployment.

## Project Repository
https://github.com/greenbasket-labs/civicvote-xahau

## Other Links
- Demo video: TBD  
- Screenshots: To be included in repository

## Notes for Judges
- No backend servers  
- No admin overrides  
- All rules enforced on-chain using Hooks  
- Open-source Hook code provided  
- Designed for real-world governance use cases

## Ownership
This project remains the property of its creator.
