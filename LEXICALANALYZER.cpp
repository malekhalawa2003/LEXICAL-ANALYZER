#include <iostream>
#include <string>
#include <cctype>
#include <vector>

enum TokenType { KEYWORD, IDENTIFIER, NUMBER, OPERATOR, DELIMITER, UNKNOWN };

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    Lexer(const std::string& input) : input(input), pos(0) {}

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        Token token;
        while ((token = getNextToken()).type != UNKNOWN) {
            tokens.push_back(token);
        }
        return tokens;
    }

private:
    Token getNextToken() {
        while (pos < input.size() && std::isspace(input[pos])) {
            pos++;
        }
        if (pos >= input.size()) {
            return {UNKNOWN, ""};
        }
        char c = input[pos];
        if (std::isdigit(c)) {
            std::string num;
            while (pos < input.size() && std::isdigit(input[pos])) {
                num += input[pos];
                pos++;
            }
            return {NUMBER, num};
        } else if (std::isalpha(c)) {
            std::string id;
            while (pos < input.size() && (std::isalnum(input[pos]) || input[pos] == '_')) {
                id += input[pos];
                pos++;
            }
            if (id == "int" || id == "if" || id == "return") {
                return {KEYWORD, id};
            } else {
                return {IDENTIFIER, id};
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            pos++;
            return {OPERATOR, std::string(1, c)};
        } else if (c == ';' || c == ',' || c == '{' || c == '}' || c == '(' || c == ')') {
            pos++;
            return {DELIMITER, std::string(1, c)};
        } else {
            pos++;
            return {UNKNOWN, std::string(1, c)};
        }
    }
    std::string input;
    size_t pos;
};

int main() {
    std::string code = "int x = 10; if(x > 5){return 1;}";
    Lexer lexer(code);
    std::vector<Token> tokens = lexer.tokenize();

    for (const auto& token : tokens) {
        std::cout << "Token Type: ";
        switch (token.type) {
            case KEYWORD: std::cout << "Keyword"; break;
            case IDENTIFIER: std::cout << "Identifier"; break;
            case NUMBER: std::cout << "Number"; break;
            case OPERATOR: std::cout << "Operator"; break;
            case DELIMITER: std::cout << "Delimiter"; break;
            default: std::cout << "Unknown"; break;
        }
        std::cout << ", Value: " << token.value << std::endl;
    }
    return 0;
}