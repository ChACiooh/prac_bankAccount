#include "aus_vote.h"
#include <algorithm>
#include <iostream>

#define INF		999999

/** etc functions **/
bool comp(Candidate a, Candidate b)
{
	return a.votes < b.votes; // ��������
}

ostream& operator<<(ostream& os, AusVoteSystem::RoundResult candidates)
{
	for(size_t i=0;i<candidates.size();i++)
	{
		os << " " << candidates[i].name << " " << candidates[i].votes;
	}
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
	for(size_t i=0;i<candidates.size();i++)
	{
		candidates[i].votes = 0;
	}
}

 // �ĺ��� ��ȣ���� 1�������� �Է�.
 // �߸��� ���ڰ� �ְų� ��ȣ�� ���� �ĺ��� ���� �ٸ���
 // �ش� �Է��� �����ϰ� false�� ����.
 // typedef vector<Candidate> RoundResult
void AusVoteSystem::AddVote(AusVoteSystem::RoundResult& candidates, vector<Voter>& voters) const
{
	for(size_t j=0;j<candidates.size();j++)
	{
		int number = candidates[j].number;
		for(size_t i=0;i<voters.size();i++)
		{
			// j��° �ĺ��� ���� �켱������ �����ϰ� �ִ� ��ǥ�ڰ� ���� �� ��ǥ ���� ���Ѵ�.
			if(number == voters[i].priorities[ voters[i].idx ])
				candidates[j].votes++;
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
	do
	{
		if(num < 0)	break;
		SetVotesToZero(round_result);
		AddVote(round_result, voters);

		RoundResult for_sort = round_result;
		sort(for_sort.begin(), for_sort.end(), comp);
		cout << "Round " << round_score << ":" << round_result << endl;
		round_score++;

		int min_votes = INF;
		vector<int> drops;
		vector<Voter> temp_voters = voters;
		bool there_are_dropout = false; // Ż���ڰ� �ִ°�
		int n = num;
		for(size_t i=0;i<for_sort.size();i++)
		{
			if(min_votes >= for_sort[i].votes)
			{
				min_votes = for_sort[i].votes;
				int number = for_sort[i].number;
				drops.push_back(number);
				n--;
				for(size_t j=0;j<temp_voters.size();j++)
				{
					if(temp_voters[j].priorities[ temp_voters[j].idx ] == number)
						temp_voters[j].idx++;
				}
			}
			else
			{
				there_are_dropout = true;
				break;
			}
		}

		if(there_are_dropout)
		{
			for(size_t i=0;i<drops.size();i++)
			{
				round_result.erase(round_result.begin() + drops[i] - 1);
			}
			voters = temp_voters;
			num = n;
		}
		else if(!there_are_dropout && num > 1)	break;

		if(num == 1)	winner = for_sort[for_sort.size() - 1].name;
	} while(num > 1);

	cout << "Winner: " << winner << endl;

} // AusVoteSystem::ComputeResult end.
// AusVoteSystem end.


