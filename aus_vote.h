#ifndef AUS_VOTE_H_INCLUDED
#define AUS_VOTE_H_INCLUDED

#include <vector>
#include <string>

using namespace std;

struct Candidate {
 std::string name;
 int votes;
};

class AusVoteSystem {
public:
 AusVoteSystem(const vector<string>& candidate_names);
 ~AusVoteSystem() { candidates.clear(); }
 // 후보별 선호도를 1순위부터 입력.
 // 잘못된 숫자가 있거나 선호도 수가 후보자 수와 다르면
 // 해당 입력을 무시하고 false를 리턴.
 bool AddVote(const vector<int>& vote);

 typedef vector<Candidate> RoundResult;
 // 지금까지의 투표를 바탕으로 결과를 모든 라운드에 대해 계산.
 // main() 에서는 vector<RoundResult>를 출력형식에 맞도록 출력.
 vector<RoundResult> ComputeResult() const;

private:
 // 입력받은 투표를 계산에 적합한 방식으로 저장하는 멤버 변수를 설계.
 RoundResult candidates;
 int num_of_candidates;
 vector<int> /** 여기 하다가 자러 감. **/
};

bool comp(Candidate a, Candidate b);

#endif // AUS_VOTE_H_INCLUDED
