#include <iostream>
#include "aus_vote.h"

inline int process();
int main() { return process(); }

int process()
{
	int num_of_candidates;
    vector<string> names;
    cin >> num_of_candidates;
    for(int i = 0; i < num_of_candidates; i++)
	{
		string name;
		cin >> name;
		names.push_back(name);
	}

	int num_of_voters;
	bool strange_number = false;
	vector<vector<int> > votes;
	cin >> num_of_voters;
	for(int i = 0; i < num_of_voters; i++)
	{
		vector<int> votes_of_one_voter;
		for(int j = 0; j < num_of_candidates; j++)
		{
			int num;
			cin >> num;
			if(num <= 0 || num > num_of_candidates)	strange_number = true;
			votes_of_one_voter.push_back(num);
		}
		votes.push_back(votes_of_one_voter);
	}
	if(strange_number)	return -1;

	AusVoteSystem AVS(names, votes);
	AVS.ComputeResult();

	return 0;
}
