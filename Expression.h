#ifndef PROJECT_IN_MATAM_EXPRESSION_H
#define PROJECT_IN_MATAM_EXPRESSION_H

#include <map>
#include <memory>
#include "Graph.h"
#include "Tokenize.h"


class IExpression {
public:
    virtual Graph evaluate(const std::set<Graph> &vars) const = 0;
};

std::shared_ptr<IExpression> parseExpression(const std::string &str);

class Variable : public IExpression {
private:
    std::string varName;
public:
    Variable(const std::string &str);

    Graph evaluate(const std::set<Graph> &vars) const override;
};

class UnionOperation : public IExpression {
private:
    std::shared_ptr<IExpression> expr1;
    std::shared_ptr<IExpression> expr2;
public:
    UnionOperation(const std::string &str1, const std::string str2);

    Graph evaluate(const std::set<Graph> &vars) const override;
};


class IntersectionOperation : public IExpression {
private:
    std::shared_ptr<IExpression> expr1;
    std::shared_ptr<IExpression> expr2;
public:
    IntersectionOperation(const std::string &str1, const std::string str2);

    Graph evaluate(const std::set<Graph> &vars) const override;
};


class ComplementaryOperation : public IExpression {
private:
    std::shared_ptr<IExpression> expr1;
public:
    ComplementaryOperation(const std::string &str1);

    Graph evaluate(const std::set<Graph> &vars) const override;
};

class SubtractionOperation : public IExpression {
private:
    std::shared_ptr<IExpression> expr1;
    std::shared_ptr<IExpression> expr2;
public:
    SubtractionOperation(const std::string &str1, const std::string str2);

    Graph evaluate(const std::set<Graph> &vars) const override;
};


class MultOperation : public IExpression {
private:
    std::shared_ptr<IExpression> expr1;
    std::shared_ptr<IExpression> expr2;
public:
    MultOperation(const std::string &str1, const std::string str2);

    Graph evaluate(const std::set<Graph> &vars) const override;
};

class Parentheses : public IExpression {
private:
    std::shared_ptr<IExpression> expr1;
public:
    Parentheses(const std::string &str);

    Graph evaluate(const std::set<Graph> &vars) const override;
};


class Immediate : public IExpression {
private:
    Graph graph;
public:
    Immediate(const std::string &str);

    Graph evaluate(const std::set<Graph> &vars) const override;
};

std::shared_ptr<IExpression> parseExpression(const std::string &str);

#endif //PROJECT_IN_MATAM_EXPRESSION_H
