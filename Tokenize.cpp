
#include "Tokenize.h"

std::vector<std::string> splitSentence(const std::string &sentence) {
    std::vector<std::string> words;
    std::string c = "";
    int count = 0;
    int num_of_not_operator = 0;
    int num_of_open=0;
    for (unsigned int i = 0; i < sentence.length(); i++) {

        if (sentence[i] == ' ' && count == 0) {
            if (num_of_not_operator > 0 && num_of_open==0) {
                for (int i = num_of_not_operator; i > 0; i--) {
                    std::string s1;
                    s1.push_back('(');
                    words.push_back(s1);
                }
                num_of_not_operator = 0;
                continue;
            } else {
                continue;
            }
        } else if (sentence[i] == ' ' && count != 0) {
            words.push_back(c);
            c = "";
            count = 0;
            if (num_of_not_operator > 0 && num_of_open==0) {
                for (int i = num_of_not_operator; i >= 0; i--) {
                    std::string s1;
                    s1.push_back('(');
                    words.push_back(s1);
                }
                num_of_not_operator = 0;
            }
            continue;
        }
        else if (sentence[i] == '!') {
            std::string s1;
            s1.push_back('(');
            words.push_back(s1);
            std::string s;
            s.push_back(sentence[i]);
            words.push_back(s);
            num_of_not_operator++;
            continue;
        }
        else if ((sentence[i] == '{' || sentence[i] == '}' || sentence[i] == '<' ||
                  sentence[i] == '>' || sentence[i] == ',' || sentence[i] == '+' || sentence[i] == '*' ||
                  sentence[i] == '^' || sentence[i] == '-' || sentence[i] == '=' || sentence[i] == '|' ||
                  sentence[i] == '(' || sentence[i] == ')') && count == 0) {
            if (sentence[i] == ')' && num_of_not_operator > 0 && num_of_open==1) {
                for (int i = num_of_not_operator; i > 0; i--) {
                    std::string s1;
                    s1.push_back(')');
                    words.push_back(s1);
                }
                num_of_open=0;
                num_of_not_operator = 0;
                std::string s;
                s.push_back(sentence[i]);
                words.push_back(s);
                continue;
            } else {
                if(sentence[i]=='(' && num_of_not_operator>0){
                    num_of_open++;
                }
                if(sentence[i]==')' && num_of_not_operator>0){
                    num_of_open--;
                }
                std::string s;
                s.push_back(sentence[i]);
                words.push_back(s);
                continue;
            }
        } else if ((sentence[i] == '{' || sentence[i] == '}' || sentence[i] == '<' ||
                    sentence[i] == '>' || sentence[i] == ',' || sentence[i] == '+' || sentence[i] == '*' ||
                    sentence[i] == '^' || sentence[i] == '-' || sentence[i] == '=' || sentence[i] == '|' ||
                    sentence[i] == '(' || sentence[i] == ')') && count != 0) {

            if ((sentence[i] == '{' || sentence[i] == '<' || sentence[i] == '>' || sentence[i] == '+' ||
                 sentence[i] == '*' || sentence[i] == '^' || sentence[i] == '-' || sentence[i] == '=' ||
                 sentence[i] == '(' || sentence[i] == ')') && num_of_not_operator > 0) {

                words.push_back(c);
                c = "";
                count = 0;
                if((num_of_open==1 && sentence[i]==')') || num_of_open==0) {
                    for (int i = num_of_not_operator; i > 0; i--) {
                        std::string s1;
                        s1.push_back(')');
                        words.push_back(s1);
                    }
                    num_of_not_operator = 0;
                }
                if( num_of_not_operator>num_of_open){
                    std::string s1;
                    s1.push_back(')');
                    words.push_back(s1);
                    num_of_not_operator--;
                }
                std::string s;
                s.push_back(sentence[i]);
                words.push_back(s);
                if(sentence[i]==')' && num_of_open>0){
                    num_of_open--;
                }
                if(sentence[i]=='(' && num_of_open>0){
                    num_of_open++;
                }
                continue;
            }
            else {
                words.push_back(c);
                std::string s;
                s.push_back(sentence[i]);
                words.push_back(s);
                c = "";
                count = 0;
                continue;
            }

        }
        else {
            c = c + sentence[i];
            count++;
        }
    }

    if (count != 0) {
        if (num_of_not_operator > 0) {
            words.push_back(c);
            for (int i = num_of_not_operator; i > 0; i--) {
                std::string s1;
                s1.push_back(')');
                words.push_back(s1);
            }

        }
        else {
            words.push_back(c);
        }
    }

    return words;
}


//chack if the function is a equal or a keep word
bool findEqual(const std::vector<std::string> &words) {
    if (std::find(words.begin(), words.end(), "=") != words.end()) {
        return true;
    }
    return false;
}

bool findOperator(const std::vector<std::string> &words) {
    return (std::find(words.begin(), words.end(), "!") != words.end()) ||
           (std::find(words.begin(), words.end(), "^") != words.end())
           || (std::find(words.begin(), words.end(), "*") != words.end()) ||
           (std::find(words.begin(), words.end(), "-") != words.end())
           || (std::find(words.begin(), words.end(), "+") != words.end());
}
