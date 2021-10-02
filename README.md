# C-Parser-Lexical-Analyzer
Lexical Analyzer &amp; Recursive Descent Parser for C subset language

Compiled on
    gcc 4.8.4 on Ubuntu 14.04.5 LTS
    
Token Lexical Analyzer 
    reads document for sequences of characters
    tokenizes strings and validates them
    
Recursive Descent Parser
    Uses tokens from Lexical Analyzer to check against custom grammar
    Produces Abstract Syntax Trees (AST) to compare to test trees for validity


      > tar xvf  subc.tar
      >make
      > subc –ast tiny_test_progrs/tiny_01 > tree.01
      > diff tree.01 tiny_test_progs/tiny01.tree
      >subc –ast tiny_test_progs/tiny_02  > tree.02
      > diff tree.02 tiny_test_progs/tiny02.tree
      …
