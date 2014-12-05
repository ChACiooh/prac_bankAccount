#ifndef AUS_VOTE_H_INCLUDED
#define AUS_VOTE_H_INCLUDED

#include <vector>
#include <string>

using namespace std;

struct Candidate {
 string name;
 int number; // �⸶ ��ȣ
 int votes;
};

struct Voter {
 Voter(int num)
 {
 	for(int i=0;i<num;i++)
		priorities.push_back(0);
 }

 vector<int> priorities;
};

class AusVoteSystem {
public:
 AusVoteSystem(const vector<string>& candidate_names, const vector<vector<int> >& votes);
 ~AusVoteSystem() { candidates_.clear(); voters_.clear(); }
 // �ĺ��� ��ȣ���� 1�������� �Է�.
 // �߸��� ���ڰ� �ְų� ��ȣ�� ���� �ĺ��� ���� �ٸ���
 // �ش� �Է��� �����ϰ� false�� ����.

 typedef vector<Candidate> RoundResult;
 // ���ݱ����� ��ǥ�� �������� ����� ��� ���忡 ���� ���.
 void ComputeResult() const;

private:
 // �Է¹��� ��ǥ�� ��꿡 ������ ������� �����ϴ� ��� ������ ����.
 int num_of_candidates;
 int num_of_voters;
 RoundResult candidates_;
 vector<Voter> voters_;

 void SetVotesToZero(RoundResult& candidates) const;
 void AddVote(RoundResult& candidates, vector<Voter>& voters) const;
};

#endif // AUS_VOTE_H_INCLUDED
