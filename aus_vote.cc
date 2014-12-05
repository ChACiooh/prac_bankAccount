#include "aus_vote.h"
#include <algorithm>
#include <iostream>

#define INF		999999
#define FIRST_PRIORITY	0

/** etc functions **/
bool comp(Candidate a, Candidate b)
{
	return a.votes < b.votes; // 오름차순
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
	// 득표 수 초기화.
	for(size_t i=0;i<candidates.size();i++)
		candidates[i].votes = 0;
}

 // 후보별 선호도를 1순위부터 입력.
 // typedef vector<Candidate> RoundResult
void AusVoteSystem::AddVote(AusVoteSystem::RoundResult& candidates, vector<Voter>& voters) const
{
	for(size_t j=0;j<candidates.size();j++)
	{
		int number = candidates[j].number;
		for(size_t i=0;i<voters.size();i++)
		{
			// j번째 후보를 가장 우선적으로 지지하고 있는 투표자가 있을 때 득표 수를 더한다.
			if(number == voters[i].priorities[ FIRST_PRIORITY ])
				candidates[j].votes++;
		}
	}
}

// 우선순위에서 탈락자들을 제거한다.
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
                // i번째 후보를 제거했으므로, i번째부터 다시 j를 보게 하기 위해 break를 함.
            }
        }
    }
}

 // 지금까지의 투표를 바탕으로 결과를 모든 라운드에 대해 계산.
void AusVoteSystem::ComputeResult() const
{
	int num = num_of_candidates;
	RoundResult round_result = candidates_;
	vector<Voter> voters = voters_;
	size_t round_score = 1;
	string winner = "";
	bool is_get_over_half = false;
	vector<int> drops; // 탈락자 명단

	while(!is_get_over_half)
	{
		SetVotesToZero(round_result);
		AddVote(round_result, voters);

		RoundResult for_sort = round_result;
		sort(for_sort.begin(), for_sort.end(), comp);
		cout << "Round " << round_score << ":" << round_result << endl;
		round_score++;
		if(num <= 1)	break; // 불필요한 계산을 피하기 위함.

		is_get_over_half = (for_sort[for_sort.size()-1].votes >= (num_of_voters+1)/2);

		int min_votes = INF;
		bool there_are_dropout = false; // 탈락자가 있는가
		int n = num;
		for(size_t i=0;i<for_sort.size();i++)
		{
			if(min_votes >= for_sort[i].votes) // 처음은 반드시 만족한다.
			{
				min_votes = for_sort[i].votes;
				int number = for_sort[i].number;
				drops.push_back(number);
				n--;
			}
			else // 끝까지 else가 나오지 않는경우에는 탈락자가 없다는 뜻이므로, else 문 안에 true로 설정하도록 함.
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


