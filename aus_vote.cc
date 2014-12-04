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

 // �ĺ��� ��ȣ���� 1�������� �Է�.
 // �߸��� ���ڰ� �ְų� ��ȣ�� ���� �ĺ��� ���� �ٸ���
 // �ش� �Է��� �����ϰ� false�� ����.
bool AusVoteSystem::AddVote(const vector<int>& vote)
{
	if(vote.size() != num_of_candidates)	return false;
	size_t i = 0;
	while(i<vote.size() && vote[i] <= num_of_candidates && vote[i]>0)	i++;
	if(i<vote.size())	return false;

	// vote�� ��ȣ�� ������� ������ ��.
	// �� i��° vote�� �ش��ϴ� ������� ��ǥ���� ������Ű�� �ȴ�.
	for(i=0;i<vote.size();i++)
		candidates[ vote[i]-1 ].votes++;

	return true;
}

 // ���ݱ����� ��ǥ�� �������� ����� ��� ���忡 ���� ���.
 // main() ������ vector<RoundResult>�� ������Ŀ� �µ��� ���.
 // typedef vector<Candidate> RoundResult;
vector<AusVoteSystem::RoundResult> AusVoteSystem::ComputeResult() const
{
	vector<RoundResult> r_result;
	int num = num_of_candidates;
	int priority = 1; // ��ȣ�� �켱����
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
