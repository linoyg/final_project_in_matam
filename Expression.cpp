#include "Expression.h"

Variable::Variable(const std::string &str) {
    varName = str;
}

Graph Variable::evaluate(const std::set<Graph> &vars) const {
    for (const auto& var : vars) {
        if (getNameOfGraphThatExists(var) == varName) {
            return var;
        }
    }
    throw Graph::invalidName{};
}


UnionOperation::UnionOperation(const std::string &str1, const std::string str2) {
    expr1 = parseExpression(str1);
    expr2 = parseExpression(str2);
}

Graph UnionOperation::evaluate(const std::set<Graph> &vars) const {
    Graph g1 = expr1->evaluate(vars);
    Graph g2 = expr2->evaluate(vars);
    return g1 + g2;
}


SubtractionOperation::SubtractionOperation(const std::string &str1, const std::string str2) {
    expr1 = parseExpression(str1);
    expr2 = parseExpression(str2);
}

Graph SubtractionOperation::evaluate(const std::set<Graph> &vars) const {
    Graph g1 = expr1->evaluate(vars);
    Graph g2 = expr2->evaluate(vars);
    return g1 - g2;
}


IntersectionOperation::IntersectionOperation(const std::string &str1, const std::string str2) {
    expr1 = parseExpression(str1);
    expr2 = parseExpression(str2);
}

Graph IntersectionOperation::evaluate(const std::set<Graph> &vars) const {
    Graph g1 = expr1->evaluate(vars);
    Graph g2 = expr2->evaluate(vars);
    return g1^g2;
}


MultOperation::MultOperation(const std::string &str1, const std::string str2) {
    expr1 = parseExpression(str1);
    expr2 = parseExpression(str2);
}

Graph MultOperation::evaluate(const std::set<Graph> &vars) const {
    Graph g1 = expr1->evaluate(vars);
    Graph g2 = expr2->evaluate(vars);
    return g1 * g2;
}


ComplementaryOperation::ComplementaryOperation(const std::string &str1) {
    expr1 = parseExpression(str1);
}

Graph ComplementaryOperation::evaluate(const std::set<Graph> &vars) const {
    Graph g1 = expr1->evaluate(vars);
    return !g1;
}

Parentheses::Parentheses(const std::string &str) {
    std::string inside = str.substr(1, str.length() - 2);
    expr1 = parseExpression(inside);
}

Graph Parentheses::evaluate(const std::set<Graph> &vars) const {
    return expr1->evaluate(vars);
}

Immediate::Immediate(const std::string &str) : graph(Graph::parseImmediate(splitSentence(str), "temp")) {}

Graph Immediate::evaluate(const std::set<Graph> &vars) const {
    return graph;
}

bool isAllInSingleParentheses(const std::string &str, char open, char close) {
    if (str[0] == open) {
        int count = 1;
        for (unsigned int i = 1; i < str.length(); ++i) {
            if (str[i] == open) {
                count++;
            } else if (str[i] == close) {
                count--;
            }
            if (count == 0) {
                if (i == str.length() - 1) {
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
    return false;
}

std::shared_ptr<IExpression> parseExpression(const std::string &str) {
    if (isAllInSingleParentheses(str, '(', ')')) {
        return std::make_shared<Parentheses>(str);
    }
    if (isAllInSingleParentheses(str, '{', '}')) {
        return std::make_shared<Immediate>(str);
    }

    int count = 0;
    for (int i = str.length() - 1; i >= 0; --i) {
        if (str[i] == '(') {
            count++;
        } else if (str[i] == ')') {
            count--;
        }
        if (count != 0) {
            continue;
        }
        switch (str[i]) {
            case '+': {
                std::string str1 = str.substr(0, i);
                std::string str2 = str.substr(i + 1);
                return std::make_shared<UnionOperation>(str1, str2);
            }

            case '!':{
                std::string str1 = str.substr(i+1);
                return std::make_shared<ComplementaryOperation>(str1);
            }

            case '-': {
                std::string str1 = str.substr(0, i);
                std::string str2 = str.substr(i + 1);
                return std::make_shared<SubtractionOperation>(str1, str2);
            }

            case '*': {
                std::string str1 = str.substr(0, i);
                std::string str2 = str.substr(i + 1);
                return std::make_shared<MultOperation>(str1, str2);
            }

            case '^': {
                std::string str1 = str.substr(0, i);
                std::string str2 = str.substr(i + 1);
                return std::make_shared<IntersectionOperation>(str1, str2);
            }



        }
    }
    return std::make_shared<Variable>(str);
}
