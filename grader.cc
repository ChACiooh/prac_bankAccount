#include "grader.h"

// SubjectPassFail
SubjectPassFail::SubjectPassFail(const string& name, int credit, int pass_score) : Subject(name, credit), pass_score_(pass_score) {}
SubjectPassFail::~SubjectPassFail() {}
string SubjectPassFail::GetGrade(int score) const
{
    return score >= pass_score_ ? "P" : "F";
}
// SubjectPassFail end.


// SubjectGrade
SubjectGrade::SubjectGrade(const string& name, int credit, int cutA, int cutB, int cutC, int cutD)
: Subject(name, credit), cutA_(cutA), cutB_(cutB), cutC_(cutC), cutD_(cutD) {}
SubjectGrade::~SubjectGrade() {}
string SubjectGrade::GetGrade(int score) const
{
    return score >= cutA_ ? "A" :
             score >= cutB_ ? "B" :
             score >= cutC_ ? "C" :
             score >= cutD_ ? "D" : "F";
}
// SubjectGrade end.

// SubjectGradePlus
SubjectGradePlus::SubjectGradePlus(const string& name, int credit,
                     int cutAp, int cutA, int cutBp, int cutB,
                     int cutCp, int cutC, int cutDp, int cutD) : SubjectGrade(name, credit, cutA, cutB, cutC, cutD)
{
    cutAp_ = cutAp;
    cutBp_ = cutBp;
    cutCp_ = cutCp;
    cutDp_ = cutDp;
}

SubjectGradePlus::~SubjectGradePlus() {}
string SubjectGradePlus::GetGrade(int score) const
{
    return
        score >= cutAp_ ? "A+" :
        score >= SubjectGrade::cutA_ ? "A" :
        score >= cutBp_ ? "B+" :
        score >= SubjectGrade::cutB_ ? "B" :
        score >= cutCp_ ? "C+" :
        score >= SubjectGrade::cutC_ ? "C" :
        score >= cutDp_ ? "D+" :
        score >= SubjectGrade::cutD_ ? "D" : "F";
}
// SubjectGradePlus end.
