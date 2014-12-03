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

// ������ Pass / Fail �� �����Ͽ� ������ִ� Ŭ����.
// ������ pass_score���� ���ų� ������ "P", �ƴϸ� "F"�� ����.

class SubjectPassFail : public Subject {
 public:
  SubjectPassFail(const string& name, int credit, int pass_score);
  virtual ~SubjectPassFail();
  virtual string GetGrade(int score) const;

 private:
  int pass_score_;
};

// ������ A, B, C, D, F �� �����Ͽ� ������ִ� Ŭ����.
// ������ ���ϴ� ������ ����
// 100 >= "A" >= cutA > "B" >= cutB > "C" >= cutC > "D" >= cutD > "F".


class SubjectGrade : public Subject {
 public:
  SubjectGrade(const string& name, int credit, int cutA, int cutB, int cutC, int cutD);
  virtual ~SubjectGrade();
  virtual string GetGrade(int score) const;

 protected:
  int cutA_, cutB_, cutC_, cutD_;
};

// +�� �ִ� ������� ��� �� Ŭ������ �̿��Ѵ�.
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
