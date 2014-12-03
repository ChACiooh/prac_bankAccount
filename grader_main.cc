// grader_main.cc
#include <algorithm>
#include <iostream>
#include <vector>
#include "grader.h"

inline bool CompareStudent(const pair<string, double>& a, const pair<string, double>& b) {
    // 여기에 성적 내림차순으로 정렬되도록 대소비교문 작성.
    return a.second > b.second;
}

double GetNumberGrade(const string& str) {
    if (str == "A+")  return 4.5;
    if (str == "A" || str == "P") return 4.0;
    if (str == "B+")  return 3.5;
    if (str == "B") return 3.0;
    if (str == "C+")  return 2.5;
    if (str == "C") return 2.0;
    if (str == "D+")  return 1.5;
    if (str == "D") return 1.0;
    return 0.0;
}

double GetTotalCredit(const vector<Subject*>& subjects, const vector<int>& scores)
{
    double grade_sum = 0.0;
    int credit_sum = 0;
    for(size_t i=0;i<subjects.size();i++)
    {
        string grade = subjects[i]->GetGrade(scores[i]);
        int credit = subjects[i]->credit();
        cout << grade << "      ";
        grade_sum += GetNumberGrade(grade) * credit;
        credit_sum += credit;
    }
    grade_sum /= credit_sum;
    return grade_sum;
}

int main() {
    vector<pair<string, double> > students_grade;
    vector<Subject*> subjects;
    string cmd;
    do
    {
        cin >> cmd;
        if(cmd == "subject")
        {
            string name;
            int credit;
            cin >> name >> credit;

            string kind;
            cin >> kind;
            Subject *sp;
            if(kind == "PF")
            {
                int pass_score;
                cin >> pass_score;
                sp = new SubjectPassFail(name, credit, pass_score);
                subjects.push_back(sp);
            }
            else if(kind == "G")
            {
                int A, B, C, D;
                cin >> A >> B >> C >> D;
                sp = new SubjectGrade(name, credit, A, B, C, D);
                subjects.push_back(sp);
            }
            else if(kind == "G+")
            {
                int A, B, C, D;
                cin >> A >> B >> C >> D;
                sp = new SubjectGradePlus(name, credit, (MAX_SCORE+A)/2, A, (A+B)/2, B, (B+C)/2, C, (C+D)/2, D);
                subjects.push_back(sp);
            }
        }
        else if(cmd == "eval")
        {
            string name;
            cin >> name;
            vector<int> scores;
            for(size_t i=0;i<subjects.size();i++) // 지금까지 입력해 놓은 과목의 수만큼 점수가 있음.
            {
                int num;
                cin >> num;
                scores.push_back(num);
            }
            cout << "     " << name << " ";
            students_grade.push_back(make_pair(name, GetTotalCredit(subjects, scores) ) );
            cout << endl;
        }
    } while(cmd != "quit");

    for(size_t i=0;i<subjects.size();i++)
        delete subjects[i];

    sort(students_grade.begin(), students_grade.end(), CompareStudent);
    for(size_t i=0;i<students_grade.size();i++)
        cout << students_grade[i].first << " " << students_grade[i].second << endl;

    return 0;
}
