all: grader bank_account aus_vote
grader: grader.cc grader_main.cc
	g++ -o grader grader.cc grader_main.cc

bank_account: bank_account.cc bank_account_main.cc
	g++ -o bank_account bank_account.cc bank_account_main.cc

aus_vote: aus_vote.cc aus_vote_main.cc
	g++ -o aus_vote aus_vote.cc aus_vote_main.cc

