// Definition: The syntax tree abstracts away certain details like parentheses and other punctuation that are not necessary for understanding the structural or semantic meaning of the code.
// Program
// ├── NodeDeclaration: node0, Parent: null, Value: 0
// ├── NodeDeclaration: node1, Parent: node, Value: 1
// └── ForLoop: Variable: node, Start: node0, End: node1
//     └── PrintStatement: Variable: node

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int countTokens(Token *tokens) {
    int count = 0;
    while (tokens[count].value != NULL) {
        count++;
    }
    return count;
}

int isToken(Parser *parser, const char *token) {
    return parser->current < parser->tokenCount && strcmp(parser->tokens[parser->current].value, token) == 0;
}

void advanceToken(Parser *parser) {
    if (parser->current < parser->tokenCount) {
        parser->current++;
    }
}

NodeDeclaration* findNodeByName(NodeDeclaration* head, const char* name) {
    NodeDeclaration* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

NodeDeclaration* parseNodeDeclaration(Parser *parser) {
    NodeDeclaration *nodeDecl = (NodeDeclaration*)malloc(sizeof(NodeDeclaration));
    nodeDecl->name = strdup(parser->tokens[parser->current].value);
    nodeDecl->parents = NULL;
    nodeDecl->parentCount = 0;
    nodeDecl->next = NULL;

    advanceToken(parser); // Move past the "node" token

    // Parse parent nodes
    if (isToken(parser, "parent")) {
        advanceToken(parser); // Move past the "parent" token

        // Allocate initial space for parent nodes
        nodeDecl->parents = (NodeDeclaration**)malloc(sizeof(NodeDeclaration*) * 10); // Initial capacity
        int capacity = 10;

        while (isToken(parser, "node")) {
            if (nodeDecl->parentCount >= capacity) {
                capacity *= 2;
                nodeDecl->parents = (NodeDeclaration**)realloc(nodeDecl->parents, sizeof(NodeDeclaration*) * capacity);
            }
            nodeDecl->parents[nodeDecl->parentCount++] = findNodeByName(parser->nodeDeclarations, parser->tokens[parser->current].value);
            advanceToken(parser); // Move past the parent node token
        }
    }

    return nodeDecl;
}

PrintStatement* parsePrintStatement(Parser *parser) {
    PrintStatement *printStmt = (PrintStatement*)malloc(sizeof(PrintStatement));
    advanceToken(parser); // Skip "print"
    printStmt->variable = parser->tokens[parser->current++].value;
    printStmt->next = NULL;
    return printStmt;
}

ForLoop* parseForLoop(Parser *parser) {
    ForLoop *forLoop = (ForLoop*)malloc(sizeof(ForLoop));
    advanceToken(parser); // Skip "for"
    forLoop->variable = parser->tokens[parser->current++].value;
    advanceToken(parser); // Skip "in"
    forLoop->start = parser->tokens[parser->current++].value;
    forLoop->end = parser->tokens[parser->current++].value;
    forLoop->printStatements = parsePrintStatement(parser);
    forLoop->next = NULL;
    return forLoop;
}

Program* parse(Token *tokens) {
    Parser parser;
    parser.tokens = tokens;
    parser.current = 0;
    parser.tokenCount = countTokens(tokens);

    Program *program = (Program*)malloc(sizeof(Program));
    program->nodeDeclarations = NULL;
    program->forLoops = NULL;
    program->parentNodes = NULL;

    NodeDeclaration **nodeDeclTail = &program->nodeDeclarations;
    ForLoop **forLoopTail = &program->forLoops;

    while (parser.current < parser.tokenCount) {
        if (strncmp(parser.tokens[parser.current].value, "node", 4) == 0) {
            *nodeDeclTail = parseNodeDeclaration(&parser);
            nodeDeclTail = &(*nodeDeclTail)->next;
        } else if (isToken(&parser, "for")) {
            *forLoopTail = parseForLoop(&parser);
            forLoopTail = &(*forLoopTail)->next;
        } else {
            advanceToken(&parser);
        }
    }

    return (Program*)program;
}
