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
 // �ĺ��� ��ȣ���� 1�������� �Է�.
 // �߸��� ���ڰ� �ְų� ��ȣ�� ���� �ĺ��� ���� �ٸ���
 // �ش� �Է��� �����ϰ� false�� ����.
 bool AddVote(const vector<int>& vote);

 typedef vector<Candidate> RoundResult;
 // ���ݱ����� ��ǥ�� �������� ����� ��� ���忡 ���� ���.
 // main() ������ vector<RoundResult>�� ������Ŀ� �µ��� ���.
 vector<RoundResult> ComputeResult() const;

private:
 // �Է¹��� ��ǥ�� ��꿡 ������ ������� �����ϴ� ��� ������ ����.
 RoundResult candidates;
 int num_of_candidates;
 vector<int> /** ���� �ϴٰ� �ڷ� ��. **/
};

bool comp(Candidate a, Candidate b);

#endif // AUS_VOTE_H_INCLUDED
