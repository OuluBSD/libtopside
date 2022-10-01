topic "struct Compiler";
[i448;a25;kKO9; $$1,0#37138531426314131252341829483380:structitem]
[l288;2 $$2,0#27521748481378242620020725143825:desc]
[0 $$3,0#96390100711032703541132217272105:end]
[ $$0,0#00000000000000000000000000000000:Default]
[{_}%EN-US 
[s1;:Topside`:`:Compiler`:`:struct:%- [@(0.0.255) struct]_[* Compiler]&]
[s2; This compiler has multiple stages. It has [/ weak] handmade parser, 
which currently adds 1`-2 stages, depending how you compare it 
to others. Stages simplify the process and you can read single 
stages more clearly.&]
[s2; Stages:&]
[s2;i150;O0; [* Tokeniser]: converts raw text to tokens&]
[s2;i150;O0; [* Token structure parser]: parses tokens to certainly 
separate blocks of code&]
[s2;i150;O0; [* Semantic parser]: parses blocks of tokens and builds 
ast at the same time (for semantic understanding of tokens)&]
[s2;i150;O0; [* Ast`-runner]: this is a concept introduced in the FOG 
c`+`+ compiler, which compiles meta`-code to ast`-nodes. And 
yes, it`'s much more than macro compiler (it`'s also in different 
position of the pipeline).&]
[s2;i150;O0; [* Ast`-exporter]: this exports ast to programming language 
or IR assembly.&]
[s0; ]]