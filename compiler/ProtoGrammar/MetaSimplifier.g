FileInput, 1	= AstCompilationUnit([0,*,0,0]);
ExprStmt,0		= <AstBeginStmt AstExpressionStatement([0]);
CallWithArgs, 0	= AstCall < id = [1,0,__name__] > ([2,*,0]);
Arg, 0			= AstCallArg < pre = [ArgQual], pos = [ArgQualOp] > ([ArgSpec,0]);
Call, 0			= AstCall < id = [0,0,__name__] > ();
ArgId, 0		= AstIdentifier([1,0]);
IdLit, 0		= AstIdentifier([1]);
