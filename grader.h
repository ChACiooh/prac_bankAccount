#ifndef GRADER_H_INCLUDED
#define GRADER_H_INCLUDED

#define MAX_SCORE   100

#include <string>

using namespace std;

class Subject {
 public:
  Subject(const string& name, int credit)  : name_(name), credit_(credit) {}
  virtual ~Subject() {}
  const string& name() const { return name_; }
  int credit() const { return credit_; }
  virtual string GetGrade(int score) const = 0;

 private:
  string name_;
  int credit_;
};

// 성적을 Pass / Fail 로 구분하여 출력해주는 클래스.
// 성적이 pass_score보다 같거나 높으면 "P", 아니면 "F"를 리턴.

class SubjectPassFail : public Subject {
 public:
  SubjectPassFail(const string& name, int credit, int pass_score);
  virtual ~SubjectPassFail();
  virtual string GetGrade(int score) const;

 private:
  int pass_score_;
};

// 성적을 A, B, C, D, F 로 구분하여 출력해주는 클래스.
// 성적이 속하는 구간에 따라
// 100 >= "A" >= cutA > "B" >= cutB > "C" >= cutC > "D" >= cutD > "F".


class SubjectGrade : public Subject {
 public:
  SubjectGrade(const string& name, int credit, int cutA, int cutB, int cutC, int cutD);
  virtual ~SubjectGrade();
  virtual string GetGrade(int score) const;

 protected:
  int cutA_, cutB_, cutC_, cutD_;
};

// +가 있는 과목들의 경우 이 클래스를 이용한다.
class SubjectGradePlus : public SubjectGrade {
public:
    SubjectGradePlus(const string& name, int credit,
                     int cutAp, int cutA, int cutBp, int cutB,
                     int cutCp, int cutC, int cutDp, int cutD);
    virtual ~SubjectGradePlus();
    virtual string GetGrade(int score) const;

private:
    int cutAp_, cutBp_, cutCp_, cutDp_;
};

#endif // GRADER_H_INCLUDED
