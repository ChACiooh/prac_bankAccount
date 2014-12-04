#include "aus_vote.h"
#include <algorithm>

/** AusVoteSystem **/
AusVoteSystem::AusVoteSystem(const vector<string>& candidate_names) : num_of_candidates(candidate_names.size())
{
	for(int i=0; i<num_of_candidates; i++)
	{
		Candidate c;
		c.name = candidate_names[i];
		c.votes = 0;
		candidates.push_back(c);
	}
}

 // 후보별 선호도를 1순위부터 입력.
 // 잘못된 숫자가 있거나 선호도 수가 후보자 수와 다르면
 // 해당 입력을 무시하고 false를 리턴.
bool AusVoteSystem::AddVote(const vector<int>& vote)
{
	if(vote.size() != num_of_candidates)	return false;
	size_t i = 0;
	while(i<vote.size() && vote[i] <= num_of_candidates && vote[i]>0)	i++;
	if(i<vote.size())	return false;

	// vote는 선호도 순서대로 나열한 것.
	// 즉 i번째 vote에 해당하는 사람에게 투표수를 증가시키면 된다.
	for(i=0;i<vote.size();i++)
		candidates[ vote[i]-1 ].votes++;

	return true;
}

 // 지금까지의 투표를 바탕으로 결과를 모든 라운드에 대해 계산.
 // main() 에서는 vector<RoundResult>를 출력형식에 맞도록 출력.
 // typedef vector<Candidate> RoundResult;
vector<AusVoteSystem::RoundResult> AusVoteSystem::ComputeResult() const
{
	vector<RoundResult> r_result;
	int num = num_of_candidates;
	int priority = 1; // 선호도 우선순위
	while(num > 1)
	{
		RoundResult rr = candidates;
		sort(rr.begin(), rr.end(), comp);
	}
	return r_result;
}


/** compare function for sorting **/
bool comp(Candidate a, Candidate b)
{
	return a.votes > b.votes;
}
