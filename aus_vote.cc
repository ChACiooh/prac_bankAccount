#include "aus_vote.h"
#include <algorithm>
#include <iostream>

#define INF		999999
#define FIRST_PRIORITY	0

/** etc functions **/
bool comp(Candidate a, Candidate b)
{
	return a.votes < b.votes; // ��������
}

ostream& operator<<(ostream& os, AusVoteSystem::RoundResult candidates)
{
	for(size_t i=0;i<candidates.size();i++)
		os << " " << candidates[i].name << " " << candidates[i].votes;

	return os;
}
// etc functions end.

/** AusVoteSystem **/
AusVoteSystem::AusVoteSystem(const vector<string>& candidate_names, const vector<vector<int> >& votes)
: num_of_candidates(candidate_names.size()), num_of_voters(votes.size())
{
	for(int i=0;i<num_of_candidates;i++)
	{
		Candidate cand;
		cand.name = candidate_names[i];
		cand.number = i + 1;
		cand.votes = 0;
		candidates_.push_back(cand);
	}

	for(int i=0;i<num_of_voters;i++)
	{
		Voter voter(votes[i].size());
		for(size_t j=0;j<votes[i].size();j++)
			voter.priorities[j] = votes[i][j];
		voters_.push_back(voter);
	}
}

void AusVoteSystem::SetVotesToZero(AusVoteSystem::RoundResult& candidates) const
{
	// ��ǥ �� �ʱ�ȭ.
	for(size_t i=0;i<candidates.size();i++)
		candidates[i].votes = 0;
}

 // �ĺ��� ��ȣ���� 1�������� �Է�.
 // typedef vector<Candidate> RoundResult
void AusVoteSystem::AddVote(AusVoteSystem::RoundResult& candidates, vector<Voter>& voters) const
{
	for(size_t j=0;j<candidates.size();j++)
	{
		int number = candidates[j].number;
		for(size_t i=0;i<voters.size();i++)
		{
			// j��° �ĺ��� ���� �켱������ �����ϰ� �ִ� ��ǥ�ڰ� ���� �� ��ǥ ���� ���Ѵ�.
			if(number == voters[i].priorities[ FIRST_PRIORITY ])
				candidates[j].votes++;
		}
	}
}

// �켱�������� Ż���ڵ��� �����Ѵ�.
void DeleteCandidateInPriority(const vector<int>& drops, Voter& voter)
{
    for(size_t i = 0; i < voter.priorities.size(); i++)
    {
        for(size_t j = 0; j < drops.size(); j++)
        {
            int num = drops[j];
            if(num == voter.priorities[i])
            {
                voter.priorities.erase(voter.priorities.begin() + i);
                i--;
                break;
                // i��° �ĺ��� ���������Ƿ�, i��°���� �ٽ� j�� ���� �ϱ� ���� break�� ��.
            }
        }
    }
}

 // ���ݱ����� ��ǥ�� �������� ����� ��� ���忡 ���� ���.
void AusVoteSystem::ComputeResult() const
{
	int num = num_of_candidates;
	RoundResult round_result = candidates_;
	vector<Voter> voters = voters_;
	size_t round_score = 1;
	string winner = "";
	bool is_get_over_half = false;
	vector<int> drops; // Ż���� ���

	while(!is_get_over_half)
	{
		SetVotesToZero(round_result);
		AddVote(round_result, voters);

		RoundResult for_sort = round_result;
		sort(for_sort.begin(), for_sort.end(), comp);
		cout << "Round " << round_score << ":" << round_result << endl;
		round_score++;
		if(num <= 1)	break; // ���ʿ��� ����� ���ϱ� ����.

		is_get_over_half = (for_sort[for_sort.size()-1].votes >= (num_of_voters+1)/2);

		int min_votes = INF;
		bool there_are_dropout = false; // Ż���ڰ� �ִ°�
		int n = num;
		for(size_t i=0;i<for_sort.size();i++)
		{
			if(min_votes >= for_sort[i].votes) // ó���� �ݵ�� �����Ѵ�.
			{
				min_votes = for_sort[i].votes;
				int number = for_sort[i].number;
				drops.push_back(number);
				n--;
			}
			else // ������ else�� ������ �ʴ°�쿡�� Ż���ڰ� ���ٴ� ���̹Ƿ�, else �� �ȿ� true�� �����ϵ��� ��.
			{
				there_are_dropout = true;
				break;
			}
		}

		for(size_t i = 0; i < voters.size(); i++)
            DeleteCandidateInPriority(drops, voters[i]);

		if(there_are_dropout)
		{
			for(size_t i=0;i<drops.size();i++)
			{
				for(size_t j = 0; j < round_result.size(); j++)
				{
					if(round_result[j].number == drops[i])
					{
						round_result.erase(round_result.begin() + j);
						break;
					}
				}
			}
			num = n;
		}
		else if(!there_are_dropout && num > 1)	break;

		if(num <= 1 || is_get_over_half)
			winner = for_sort[for_sort.size() - 1].name;
	}

	cout << "Winner: " << winner << endl;

} // AusVoteSystem::ComputeResult end.
// AusVoteSystem end.


