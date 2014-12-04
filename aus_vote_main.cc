#include <iostream>
#include "aus_vote.h"

int main()
{
    int num_of_candidate;
    vector<string> names;
    cin >> num_of_candidate;

    for(int i = 0; i < num_of_candidate; i++)
	{
		string name;
		cin >> name;
		names.push_back(name);
	}

	AusVoteSystem AVS(names);

    return 0;
}
