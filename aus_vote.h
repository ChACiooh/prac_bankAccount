#ifndef AUS_VOTE_H_INCLUDED
#define AUS_VOTE_H_INCLUDED

#include <vector>
#include <string>

using namespace std;

struct Candidate {
 string name;
 int number; // 출마 번호
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
 // 후보별 선호도를 1순위부터 입력.
 // 잘못된 숫자가 있거나 선호도 수가 후보자 수와 다르면
 // 해당 입력을 무시하고 false를 리턴.

 typedef vector<Candidate> RoundResult;
 // 지금까지의 투표를 바탕으로 결과를 모든 라운드에 대해 계산.
 void ComputeResult() const;

private:
 // 입력받은 투표를 계산에 적합한 방식으로 저장하는 멤버 변수를 설계.
 int num_of_candidates;
 int num_of_voters;
 RoundResult candidates_;
 vector<Voter> voters_;

 void SetVotesToZero(RoundResult& candidates) const;
 void AddVote(RoundResult& candidates, vector<Voter>& voters) const;
};

#endif // AUS_VOTE_H_INCLUDED
