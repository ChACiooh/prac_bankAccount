#ifndef AUS_VOTE_H_INCLUDED
#define AUS_VOTE_H_INCLUDED

#include <vector>
#include <string>

using namespace std;

struct Candidate {
 std::string name;
 int votes;
};

struct Voter {
 Voter(int num) : priorities(new int[num]) { for(size_t i=0;i<num;i++)  priorities[i] = 0; }
 ~Voter() { delete[] priorities; }
 int* priorities;
};

class AusVoteSystem {
public:
 AusVoteSystem(const vector<string>& candidate_names);
 ~AusVoteSystem() { candidates.clear(); voters.clear(); }
 // �ĺ��� ��ȣ���� 1�������� �Է�.
 // �߸��� ���ڰ� �ְų� ��ȣ�� ���� �ĺ��� ���� �ٸ���
 // �ش� �Է��� �����ϰ� false�� ����.
 bool AddVote(const vector<int>& vote);

 typedef vector<Candidate> RoundResult;
 // ���ݱ����� ��ǥ�� �������� ����� ��� ���忡 ���� ���.
 // main() ������ vector<RoundResult>�� ������Ŀ� �µ��� ���.
 vector<RoundResult> ComputeResult() const;
 int NumOfCandidates() const { return num_of_candidates; }

private:
 // �Է¹��� ��ǥ�� ��꿡 ������ ������� �����ϴ� ��� ������ ����.
 void SetVoteZero();
 int num_of_candidates;
 RoundResult candidates;
 vector<Voter> voters;
};

bool comp(Candidate a, Candidate b);

#endif // AUS_VOTE_H_INCLUDED
