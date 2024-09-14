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

NodeDeclaration* parseNodeDeclaration(Parser *parser) {
    NodeDeclaration *nodeDecl = (NodeDeclaration*)malloc(sizeof(NodeDeclaration));
    nodeDecl->name = parser->tokens[parser->current++].value;
    advanceToken(parser); // Skip "value" token
    nodeDecl->value = atoi(parser->tokens[parser->current++].value);
    nodeDecl->next = NULL;
    return nodeDecl;
}

EdgeDeclaration* parseEdgeDeclaration(Parser *parser) {
    EdgeDeclaration *edgeDecl = (EdgeDeclaration*)malloc(sizeof(EdgeDeclaration));
    edgeDecl->name = parser->tokens[parser->current++].value; // Token: edge0
    advanceToken(parser); // Skip "to" token
    edgeDecl->to = parser->tokens[parser->current++].value; // Token: node0
    advanceToken(parser); // Skip "from" token
    edgeDecl->from = parser->tokens[parser->current++].value; // Token: null
    edgeDecl->next = NULL;
    return edgeDecl;
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

    NodeDeclaration **nodeDeclTail = &program->nodeDeclarations;
    EdgeDeclaration **edgeDeclTail = &program->edgeDeclarations;
    ForLoop **forLoopTail = &program->forLoops;

    while (parser.current < parser.tokenCount) {
        if (strncmp(parser.tokens[parser.current].value, "node", 4) == 0) {
            *nodeDeclTail = parseNodeDeclaration(&parser);
            if (*nodeDeclTail == NULL) {
                fprintf(stderr, "Failed to parse node declaration\n");
                break;
            }
            nodeDeclTail = &(*nodeDeclTail)->next;
        } else if (strncmp(parser.tokens[parser.current].value, "edge", 4) == 0) {
            *edgeDeclTail = parseEdgeDeclaration(&parser);
            if (*edgeDeclTail == NULL) {
                fprintf(stderr, "Failed to parse edge declaration\n");
                break;
            }
            edgeDeclTail = &(*edgeDeclTail)->next;
        } else if (isToken(&parser, "for")) {
            *forLoopTail = parseForLoop(&parser);
            if (*forLoopTail == NULL) {
                fprintf(stderr, "Failed to parse for loop\n");
                break;
            }
            forLoopTail = &(*forLoopTail)->next;
        } else {
            advanceToken(&parser);
        }
    }

    return (Program*)program;
}
