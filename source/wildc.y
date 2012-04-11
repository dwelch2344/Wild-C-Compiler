%{
#pragma warning( disable:4013; disable:4996; disable:4716 )

/* name: wildc.y
   This code implements a parser and translator for the wildc language
   
   build: bison -l -d wildc.y
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "wildc.h"

struct symbolDef symtab[NSYMS];
DType tmpFnCallParms[NESTCALLDEPTH][NTMPCALLPARMS];
char currentContext[MAX_IDENT_LEN+1];
char genedLabel[MAX_IDENT_LEN+1];
int fnParmIdx = 0;
int tmpFnCallParmIdx[NESTCALLDEPTH] = {0};
int tmpFnCallDepth = -1;
int labelIndex = 0;


int _isDebug = 0; // is a debug run
char myBuffer[100000];
char paramBuffer[100000];
int localIndex = 0;
int tabIndex = 0;
int globals = 0;
char className[50];
%}

%union
{
	DType				dtype;
	int					ival;
	char				*str;
	char				pBuffer[500];
	struct dataDef		datDefType;
	struct dataRef		datRefType;
	struct labelDef		labDefType;
	
}

%token <str> ID
%token <str> INT_CONST
%token <str> FLOAT_CONST
%token <str> STRING_CONST
%token INT FLOAT STRING BOOL VOID
%token ASSIGN IF ELSE WHILE INPUT PRINT TRUE FALSE 
%token LENGTH CHAR SUBSTR RETURN



%left OR
%left AND
%left EQUALS NOT_EQUALS
%left '<' '>' LTE GTE
%left '-' '+'
%left '*' '/'

%type <dtype> data_type
%type <dtype> return_type
%type <dtype> expression
%type <ival> array_declaration
%type <ival> inc_function_call_depth
%type <datDefType> data_type_def
%type <datRefType> data_ref
%type <labDefType> if_test
%type <labDefType> while_test
%type <labDefType> gen_while_labels

%type <str> function_parameter
%type <str> fn_parameter_list

%type <str> data_def;
%type <str> local_definitions;
%type <str> local_defs;

%start wildc_start

%%

wildc_start
	:	init_sys global_defs mid_process function_defs finish_up
	;
	
init_sys
	:	{
			strcpy( currentContext, "@global" );
			printf(".assembly %s {} \n", className);	
			printf(".assembly extern mscorlib {} \n\n");
			
			
			printf(".class public %s extends [mscorlib]System.Object{ \n\n", className);
			globals = 1;
			
		}
	;
	
mid_process
	:	{			
			int n, i;
			globals = 0;
				/* output the MSIL code to make the program class with globals as public static class variables */
				/* add the .cctor() method if global array variables need to be created */
				/* all the functions will be static methods of this class */
			printf("\t.method private hidebysig specialname rtspecialname static void .cctor() cil managed{\n");
			
			for ( i=0; i<NSYMS; i++ ){
				if ( symtab[i].name[0] == "/0"){
					break;
				}
				if ( symtab[i].isArray && strcmp(symtab[i].context, "@global") == 0){
					printf("\t\t ldc.i4 %i \n", symtab[i].arrayMax);
					printf("\t\t newarr %s \n\n", enumType(symtab[i].type));
					printf("\t\t stsfld %s[] %s::%s \n\n", enumType(symtab[i].type), 
						className, symtab[i].name);
				}
			}
			printf("\t\t ret \n");
			printf("\t}\n");
		
			
			tabIndex++;
			
		}
	;
	
finish_up
	:	{
			printf("\n} // end of class");
		}
	;
	
global_defs
	:	data_definitions
		{
			
		}
	|	{
			/* no global defs */
		}

data_definitions
	:	data_def
		{ }
	|	data_definitions data_def
		{ }
	;
	
data_def
	:	data_type_def ID ';'
		{
			setSymbol( currentContext, $2, $1.type, $1.isArray ? $1.arrayMax : 0, FALSE_ );
			
			if(globals != 1)
				sprintf(myBuffer, "[%d] ", getLocalIndex());
			else
				sprintf(myBuffer, ".field public static ", getLocalIndex());
			
			sprintf(myBuffer, "%s %s", myBuffer, enumType($1.type));
			// if array, output the []
			if($1.isArray) sprintf(myBuffer, "%s[]", myBuffer);
			sprintf(myBuffer, "%s %s", myBuffer, $2);
			
			if(globals == 1){
				printf("\t%s\n", myBuffer);
			}else{
				$$ = _strdup(myBuffer);
			}
		}
	;
	
data_type_def
	:	data_type array_declaration
		{
			$$.type = $1;
			$$.isArray = TRUE_;
			$$.arrayMax = $2;
		}
	|	data_type
		{
			$$.type = $1;
			$$.isArray = FALSE_;
			$$.arrayMax = 0;
		}
	;
	
data_type
	:	INT
		{ $$ = int_; }
	|	FLOAT
		{ $$ = float_; }
	|	STRING
		{ $$ = string_; }
	|	BOOL
		{ $$ = bool_; }
	;
	
array_declaration
	:	'[' INT_CONST ']'
		{
			$$ = atoi($2);
			if ( $$ <= 0 )
				yyerror( "data array declaration of %d must be greater than 0", $$ );
		}
	;
	
function_defs
	:	function_def
		{ }
	|	function_defs function_def
		{ }
	;
	
function_def
	:	'<' return_type '>' ID 
		{
			setSymbol( "@global", $4, func_, 0, FALSE_ ); // add method to global 
			setFuncRetType( $4, $2 ); // set return type
			strcpy( currentContext, $4 ); // switch context to method
			
			printf("%s.method public static %s %s( ",getTabs(tabIndex), enumType($2), $4);
			
			sprintf( currentContext, "%s",  $4);
			
			localIndex = 0;
			
		}'(' function_parameters ')'{
			
			//! Parameters
			/* output the MSIL top code for this function with the parms etc. */
			//! Output the opening signature line for the method. (ex: line 76 in objprimes.il)
			//! also includes the opening brace ({), and the .entrypoint (if main)
			printf(" ) cil managed{ \n\n");
			//! increment tabs
			tabIndex++;
			if( strcmp(currentContext, "main") == 0 ){
				printf("%s.entrypoint\n", getTabs(tabIndex));
				
			}
			printf("%s.maxstack 8\n\n", getTabs(tabIndex));
			
		}
		'{' local_defs
		{
			//! This is handled lower at local_defs -> local_definitions
		}
		function_statements '}'
		{
			//! THIS is where everything is happening
			/* all the function statements have now generated code; if we did not do a "return" in the function we need to generate a */
			/* return here, at the end of the function.  If the function expects to return a value, we must put something on the stack */
			/* for the calling function to use; a (void) call will have to pop this default value or the stack won't be empty at the end */
			/* of the program. */
			
			if ( $2 != void_ ){
				printf("\n%s // if no return value was specified \n", getTabs(tabIndex));
				switch( $2 )
				{
				case int_:
					/* create MSIL code to push 0 */
					printf("%s ldc.i4 0\n", getTabs(tabIndex));
					break;
				case float_:
					/* create MSIL code to push 0.0 */
					printf("%s ldc.r4 0.0\n", getTabs(tabIndex));
					break;
				case string_:
					/* create MSIL code to push "" */
					printf("%s ldstr \"\"\n", getTabs(tabIndex));
					break;
				case bool_:
					printf("%s ldc.i4 0\n", getTabs(tabIndex));
					/* create MSIL code to push "false" */
					break;
				default:
					yyerror( "illegal return type of %d for function %s", $2, $4 );
					break;
				}
			}
			printf("%s ret\n", getTabs(tabIndex));
			tabIndex--;
			printf("%s}\n\n", getTabs(tabIndex));
			/* output MSIL to do a function return */
			/* output MSIL code to end the function */
			
		}
	;
	
return_type
	:	VOID
		{
			$$ = void_;
		}
	|	data_type
		{
			$$ = $1;
		}
	;
	
function_parameters
	:	VOID
		{
			;
		}
	|	fn_parameter_list
		{
			
			//! prints the parameters, unless void
			printf("%s", $1);
			
			sprintf( paramBuffer, ""); //! clear the buffer
		}
	;
	
fn_parameter_list
	:	function_parameter
		{
			sprintf( paramBuffer, "%s", $1); //! Set the first param
		}
	|	fn_parameter_list ',' function_parameter
		{
			
			sprintf( paramBuffer, "%s, %s", paramBuffer, $3);
			$$ = _strdup(paramBuffer); //! happens on each param iteration, thus the use of the buffer
		}
	;
	
function_parameter
	:	data_type ID
		{
			char buff[100];
			setSymbol( currentContext, $2, $1, 0, TRUE_ );
			
			sprintf( buff, "%s %s", enumType($1), $2); 
			$$ = _strdup(buff);
		}
	;
	
local_defs
	:	local_definitions
		{
			int n, i, params;
			struct symbolDef *symbPtr;
			
				printf("%s.locals init(%s", getTabs(tabIndex), $1);
				//! be sure to clear the buffer
				sprintf(myBuffer, "");
				
				if(localIndex > 0) printf(",");
				
				for(i=2; i<6;i++){
					printf("\n\t\t\t [%d] %s _%s,", localIndex++, enumType(i), enumType(i));
				}
				printf("\n\t\t\t [%d] int32 _index", localIndex++);
				
				symbPtr = getSymbol( "@global", currentContext );
				
				if ( !symbPtr )
					yyerror( "function %s does not exist (yet) in symbol table", currentContext );
				
				//! create variables to store the parameters in
				for(n = 1; n <= symbPtr->fnNumParams; n++){
					for ( i=0; i<NSYMS; i++ ){
						if ( symtab[i].name[0] == "/0"){
							break;
						}
						if ( symtab[i].isParam && symtab[i].paramSeq == n && strcmp(symtab[i].context, currentContext) == 0){
							printf(",\n\t\t\t [%i] %s %s", localIndex++, enumType(symtab[i].type), symtab[i].name);
						}
					}
				}
				printf(")\n\n"); // end of locals
				
				
				//! now we need to store the parameters in their variables
				for(n = 1; n <= symbPtr->fnNumParams; n++){
					for ( i=0; i<NSYMS; i++ ){
						if ( symtab[i].name[0] == "/0"){
							break;
						}
						if ( symtab[i].isParam && symtab[i].paramSeq == n && strcmp(symtab[i].context, currentContext) == 0){
							printf("%s ldarg %s\n", getTabs(tabIndex), symtab[i].name);
							printf("%s stloc %s\n", getTabs(tabIndex), symtab[i].name);
						}
					}
				}
				
				//! now we need to initialize any arrays
				for ( i=0; i<NSYMS; i++ ){
					if ( symtab[i].name[0] == "/0"){
						break;
					}
					if ( symtab[i].isArray && strcmp(symtab[i].context, currentContext) == 0){
						printf("%s ldc.i4 %i\n", getTabs(tabIndex), symtab[i].arrayMax);
						printf("%s newarr %s\n", getTabs(tabIndex), enumType(symtab[i].type));
						printf("%s stloc %s\n", getTabs(tabIndex), symtab[i].name);
						
					}
				}
		}
	|	{
			
			//! still need to have the temps / parameters
			int n, i, params;
			struct symbolDef *symbPtr;
			printf("%s.locals init( ", getTabs(tabIndex));

			if(localIndex > 0) printf(",");
			for(i=2; i<6;i++){
				printf("\n\t\t\t [%d] %s _%s,", localIndex++, enumType(i), enumType(i));
			}
			printf("\n\t\t\t [%d] int32 _index", localIndex++);
			
			symbPtr = getSymbol( "@global", currentContext );
			
			if ( !symbPtr )
				yyerror( "function %s does not exist (yet) in symbol table", currentContext );
			
			//! create variables to store the parameters in
			for(n = 1; n <= symbPtr->fnNumParams; n++){
				for ( i=0; i<NSYMS; i++ ){
					if ( symtab[i].name[0] == "/0"){
						break;
					}
					if ( symtab[i].isParam && symtab[i].paramSeq == n && strcmp(symtab[i].context, currentContext) == 0){
						printf(",\n\t\t\t [%i] %s %s", localIndex++, enumType(symtab[i].type), symtab[i].name);
					}
				}
			}
			printf(")\n\n"); // end of locals
					
			
			//! now we need to store the parameters in their variables
			for(n = 1; n <= symbPtr->fnNumParams; n++){
				for ( i=0; i<NSYMS; i++ ){
					if ( symtab[i].name[0] == "/0"){
						break;
					}
					if ( symtab[i].isParam && symtab[i].paramSeq == n && strcmp(symtab[i].context, currentContext) == 0){
						printf("%s ldarg %s\n", getTabs(tabIndex), symtab[i].name);
						printf("%s stloc %s\n", getTabs(tabIndex), symtab[i].name);
					}
				}
			}
			
			//! now we need to initialize any arrays
			for ( i=0; i<NSYMS; i++ ){
				if ( symtab[i].name[0] == "/0"){
					break;
				}
				if ( symtab[i].isArray && strcmp(symtab[i].context, currentContext) == 0){
					printf("%s ldc.i4 %i\n", getTabs(tabIndex), symtab[i].arrayMax);
					printf("%s newarr %s\n", getTabs(tabIndex), enumType(symtab[i].type));
					printf("%s stloc %s\n", getTabs(tabIndex), symtab[i].name);
				}
			}
		}
	;

local_definitions
	:	data_def
		{
			
			$$ = $1;
		}
	|	local_definitions data_def
		{
			//! push the next definition onto the buffer
			sprintf( myBuffer, "%s,\n\t\t\t %s", $1, $2);
			$$ = _strdup(myBuffer);
			sprintf( myBuffer, "");
		}
	;
	
function_statements
	:	function_statement
		{
			;
		}
	|	function_statements function_statement
		{
			;
		}
	;
	
data_ref
	:	ID
		{
			struct symbolDef *symb;
			char holder [500];
			symb = getSymbol( currentContext, $1 );
			if ( !symb )
			{
				symb = getSymbol( "@global", $1 );
				if ( !symb )
				{
					yyerror( "identifier %s not defined in program", $1 );
				}
			}
			
			;	/* make MSIL code to push ID identifier on the stack according to its type in symb->type */
			//! get the type. Context can change how u push it on the stack
			//! Need to store the reference for when we come back out of data_ref and expression, 
			//!		so we will just have the identifier and the new value
			
			$$.symbPtr = symb;
			$$.isArrayRef = FALSE_;
		}
	|	ID '[' expression ']'
		{
		struct symbolDef *symb;
		
			symb = getSymbol( currentContext, $1 );
			if ( !symb )
			{
				symb = getSymbol( "@global", $1 );
				if ( !symb )
				{
					yyerror( "identifier %s not defined in program\n", $1 );
				}
				if ( !symb->isArray )
					yyerror( "%s is not an array but is being referenced as an array element", $1 );
				
				printf("%s stloc _int32 \t\t// temp store index\n", getTabs(tabIndex));
				printf("%s ldsfld %s[] %s::%s \n", getTabs(tabIndex), enumType(symb->type), className, symb->name);
				printf("%s ldloc _int32 \t\t// reload index\n", getTabs(tabIndex));
				
			}else{
			
				if ( !symb->isArray )
					yyerror( "%s is not an array but is being referenced as an array element", $1 );
		
				$$.symbPtr = symb;
				$$.isArrayRef = TRUE_;
				
				//! store the array expression in the temp
				
					
				
				printf("%s stloc _int32 \t\t// temp store index\n", getTabs(tabIndex));
				printf("%s ldloc %s \t\t// array\n", getTabs(tabIndex), $1);
				printf("%s ldloc _int32 \t\t// index\n", getTabs(tabIndex), enumType(symb->type));
			}
			$$.symbPtr = symb;
			$$.isArrayRef = TRUE_;
		}
	;

if_test
	:	IF '(' expression ')'
		{
		char *label;
		
			/* if $3 is bool_ or can be converted to bool_ then create MSIL code to do so, else yyerror */
			if($3 != bool_){
				if($3 == int_ || $3 == float_){
					printf("%s conv.i4 \t\t// Convert to boolean\n", getTabs(tabIndex));
				}else{
					yyerror("if_	 requires boolean");
				}
			}
			/* create 2 labels; use 1 for if and 2 for if/else */
			//label = generateLabel();
			strcpy($$.label1, generateLabel());
			strcpy($$.label2, generateLabel());
			//label = generateLabel();
			
			
			printf("%s brfalse %s \t// branch to if_else_false or if_exit \n", getTabs(tabIndex), $$.label1);
			/* create MSIL code to test if stack is not True_ and br to label $$.label1 if not */
		}
	;

gen_while_labels
	:	{
		char *label;
		
			/* create 2 labels */
			strcpy( $$.label1, generateLabel());
			strcpy( $$.label2, generateLabel());
			
			/* create MSIL code to output label $$.label1: */
			printf("%s: \t\t\t // while_return \n", $$.label1);
		}

while_test
	:	WHILE gen_while_labels '(' expression ')'
		{
			/* if $4 is bool_ or can be converted to bool_ then create MSIL code to do so, else yyerror */
			/* create MSIL code to test if stack is not True_ and br to label $2.label2 if not */
			if($4 != bool_){
				if($4 == int_ || $4 == float_){
					printf("%s conv.i4 \t\t// Convert to boolean\n", getTabs(tabIndex));
				}else{
					yyerror("while_test requires boolean");
				}
			}
			//! eval of bool already happened
			printf("%s brfalse %s \t\t// branch while_exit \n", getTabs(tabIndex), $2.label2);
			strcpy( $$.label1, $2.label1 );
			strcpy( $$.label2, $2.label2 );
		}
	;
	
function_statement
	:	data_ref ASSIGN expression ';'
		{
			if ( $1.symbPtr->isArray && !$1.isArrayRef )
				yyerror( "%s is an array and not referenced as an array element", $1.symbPtr->name );
			
			/* look at type in data_ref and type of "expression"; if they are compatible do store or 'stelem' */
			/* if expression can be converted to $1 type then create code to do the conversion before the store or stelem */
			if( !$1.symbPtr->isArray){
				// Not an array
				if( $1.symbPtr->type != $3){
					int b = 1;
					if( $1.symbPtr->type == int_ ){
						// Ints 
						if($3 == float_){
							b = 1;
						}
					}else if( $1.symbPtr->type == float_ ){
						// Floats
						if( $3 == int_ ){
							printf( "%s conv.r4 \t\t//Converting int to float \n ", getTabs(tabIndex));
							b = 0;
						}else{
							b = 1;
						}
					}
					if(b == 1) 
						yyerror("Cannot cast %s to (%s) variable '%s'!", 
								enumType($3), enumType($1.symbPtr->type), $1.symbPtr->name);  
				}
				if(strcmp($1.symbPtr->context, "@global")){
					printf("%s stloc %s \n", getTabs(tabIndex), $1.symbPtr->name);
				}else{
					printf("%s stsfld %s %s::%s\n", getTabs(tabIndex), 	enumType($1.symbPtr->type),
						className, $1.symbPtr->name);
				}
			}else{
				//! the array and index are already on the stack
				//! the value to be stored is on the stack too! just store it
				printf("%s // the value above this line will be stored in the array \n", getTabs(tabIndex));
				printf("%s stelem %s \n\n", getTabs(tabIndex), enumType($1.symbPtr->type));
				/*if($1.symbPtr->type==string_ || $1.symbPtr->type==bool_)
					printf("%s stelem.ref \n\n", getTabs(tabIndex));
				else
					printf("%s stelem.%s \n\n", getTabs(tabIndex), primType($1.symbPtr->type));
				*/
			}
			
		}
	|	data_ref '(' expression 
		{
			//! then skip this one
			if ( $1.symbPtr->isArray && !$1.isArrayRef )
				yyerror( "%s is an array and not referenced as an array element", $1.symbPtr->name );
			
			;	/* if $1 is not a string_ then yyerror (maybe consider converting to string_) */
				/* if $3 is not int type but can be converted to int then do it here, else yyerror */
				/* create MSIL to check if top of stack ($3) < 0 then throw error */
				/* create MSIL to check if len( $1 ) <= $3 then throw error */
		}
		',' expression 
		{
			;	/* if $6 is not int type but can be converted to int then do it here, else yyerror */
				/* create MSIL to check if top of stack ($3) < 0 then throw error */
				/* create MSIL to check if $3 data + $6 data > len( $1 )+1 then throw error */
		}
		')' ASSIGN expression  ';'
		{
			;	/* if $10 is not string type but can be converted to string then do it here, else yyerror */
				/* create code for:
					a) if $3 == 0, $1 := $10 + $1.substring( $3+$6, to the end )
					b) if $3 != 0, $1 := $1.substring( 0, $3 ) + $10 + $1.substring( $3+$6, to the end )
				*/	
		}
	|	if_test '{' function_statements '}'
		{
			
			;	/* create MSIL code to output label $1.label1: */
			printf("%s: \t\t\t// if_exit \n", $1.label1);
		}
	|	if_test '{' function_statements '}'
		{
			/* create MSIL code to br to label $1.label2 */
			printf("%s br %s \t\t// branch to if_else_exit \n", getTabs(tabIndex), $1.label2);
			/* create MSIL code to output label $1.label1: */
			
			printf("%s: \t\t\t// if_else_false \n", $1.label1);
		}
		ELSE '{' function_statements '}'
		{
			;	/* create MSIL code to output label $1.label2: */
			printf("%s: \t\t\t// if_else_exit  \n", $1.label2);
		}
	|	while_test '{' function_statements '}'
		{
			;	/* create MSIL code to br to label $1.label1 */
				/* create MSIL code to output label $1.label2: */
				
			printf("%s br %s \n", getTabs(tabIndex), $1.label1);
			printf("%s: \t\t\t// while_exit  \n", $1.label2);			
		}
	|	INPUT data_ref ';'
		{
			char* after_notEmpty;
			char* not_true;
			char* after_compare;
			
			if ( $2.symbPtr->isArray && !$2.isArrayRef )
				yyerror( "%s is an array and not referenced as an array element", $2.symbPtr->name );
			
			//! Display & catch input
			if(_isDebug == 1){
				printf("%s ldstr \"(%s): \" \n", getTabs(tabIndex), 
					enumType($2.symbPtr->type));
				printf("%s call void [mscorlib]System.Console::Write(string) \n", getTabs(tabIndex));
			}
			printf("%s call string [mscorlib]System.Console::ReadLine() \n", 
				getTabs(tabIndex), $2.symbPtr->name);
			
			after_notEmpty = generateLabel();
			printf("%s dup \n", getTabs(tabIndex));
			printf("%s callvirt instance int32 [mscorlib]System.String::get_Length() \n", getTabs(tabIndex));
			printf("%s ldc.i4 0 \n", getTabs(tabIndex));
			printf("%s bgt %s\n\n", getTabs(tabIndex), after_notEmpty);
			printf("%s pop \t\t// pop the empty input\n", getTabs(tabIndex), after_notEmpty);
			printf("%s ldstr \"0\" \n", getTabs(tabIndex));
			printf("%s: \t\t\t// label after_notEmpty \n", after_notEmpty);
			switch($2.symbPtr->type){
				case string_:
					// don't need to cast it at all
					break;
					
				case int_:
					printf("%s call int32 [mscorlib]System.Int32::Parse(string) \n", getTabs(tabIndex));
					break;
					
				case float_:
					printf("%s call float32 [mscorlib]System.Single::Parse(string) \n", getTabs(tabIndex));
					break;
					
				case bool_:
					
					
					// the hard one. push 
					
					// set to lowercase
					printf("%s callvirt instance string [mscorlib]System.String::ToLower() \n", 
						getTabs(tabIndex));
			
					printf("%s ldstr \"true\" \t\t// 't' for comparison \n", getTabs(tabIndex));
					printf("%s callvirt instance int32 [mscorlib]System.String::CompareTo(string) \t\t// compare strings \n", getTabs(tabIndex));
					// we now have a 0 only if it was some variation of "true". Get labels
					not_true = generateLabel();
					after_compare = generateLabel();
					// we'll jump below if it's not 0, otherwise set it to 0
					printf("%s ldc.i4 0 \n", getTabs(tabIndex));
					printf("%s bne.un %s \t\t// branch not_true \n", getTabs(tabIndex), not_true);
						// it's true, so push a 1
						printf("%s ldc.i4 1 \n", getTabs(tabIndex));
						printf("%s br %s // branch after_compare \n", getTabs(tabIndex), after_compare);
					// else
						// it's false
						printf("%s: \t\t\t// not_true label \n", not_true);
						printf("%s ldc.i4 0 \n", getTabs(tabIndex));
						
					printf("%s: \t\t\t// after_compare label  \n", after_compare);
					break;
										
				default:
					yyerror("Could not cast input to datatype %s", enumType($2.symbPtr->type));
					break;
			}
			printf("%s stloc %s \n", getTabs(tabIndex), $2.symbPtr->name);
		}
	|	PRINT print_list ';'
		{
			;	/* code generation happens in print_list */
		}
	|	RETURN expression ';'
		{
		struct symbolDef *symbPtr;

			symbPtr = getSymbol( "@global", currentContext );
			if ( !symbPtr )
				yyerror( "internal fault: function %s can't be found in symbol table", currentContext );
				
			if ( symbPtr->fnRetType == void_ )
				yyerror( "function %s has a return type of VOID so an expression cannot be returned", currentContext );
			
			if ( symbPtr->fnRetType == $2 ){
				//! don't need to load it from storage
				printf("%s ret \n", getTabs(tabIndex));
			}else{
				yyerror( "function %s has a return type of '%s', not '%s'", currentContext, enumType(symbPtr->fnRetType), enumType($2) );
			}
			/* see if $2 (a type) is compatible with symbPtr->fnRetType; if they are the same type then just output MSIL to return */
			/* (the return value is already on the stack); if type $2 can be converted to symbPtr->fnRetType then output MSIL code */
			/* to do the translation and then output a return; else error */
		
		}
	|	'(' VOID ')' ID inc_function_call_depth '(' function_call_parameters ')' ';'
		{
			struct symbolDef *symbPtr;
			int params, n, i, depth;
			symbPtr = getSymbol( "@global", $4 );
			if ( !symbPtr )
				yyerror( "function %s does not exist (yet) in symbol table", $4 );
			
			if ( symbPtr->type != func_ )
				yyerror( "%s is not a function ", $4 );
				
			
			/* notice that functions have to be defined before they are used */
			/* write code to confirm fn parameters for ID correspond to tmpFnCallParms in number and type else yyerror */
			/* i.e., confirm fn parameters for ID correspond to the tmpFnCallParmIdx[$5] types in tmpFnCallParms[$5] produced in function_call_list else yyerror */
			/* create code to call fn with parameters */
			/* if we called a function that returned a value that is on the stack remove it or the stack will not be empty when we end */
			
			
			params = symbPtr->fnNumParams;
			tmpFnCallParmIdx[$5]--;
			for(n = params; n > 0; n--){
				for ( i=0; i<NSYMS; i++ ){
					if ( symtab[i].name[i] == "/0"){
						break;
					}
					
					if ( symtab[i].isParam && symtab[i].paramSeq == n && !strcmp(symtab[i].context, $4) ){

						if(tmpFnCallParms[$5][ tmpFnCallParmIdx[$5]-- ] != symtab[i].type)
							yyerror("Incorrect parameters passed to method. (%s:%s)",
								symtab[i].context, symtab[i].name);
								
						
						break;
					}
				}
			}
			// we're all good. call it
			
			
			printf("%s call %s %s::%s( ", getTabs(tabIndex), enumType(symbPtr->fnRetType),
				className, $4);		
			for(n = 1; n <= params; n++){
				for ( i=0; i<NSYMS; i++ ){
					if ( symtab[i].name[i] == "/0"){
						break;
					}
					if ( symtab[i].isParam && symtab[i].paramSeq == n && !strcmp(symtab[i].context, $4) ){
						printf("%s", enumType(symtab[i].type));
						if(params > n) printf(", ");
					}
				}
			}
			printf(" )\n\n");
			
			
			if ( symbPtr->fnRetType != void_ )
				switch( symbPtr->fnRetType )
				{
				case int_:
				case float_:
				case string_:
				case bool_:
					printf("%s pop\n", getTabs(tabIndex));
					break;
				default:
					yyerror( "illegal return type of %d for function %s", symbPtr->fnRetType, $4 );
					break;
				}
			tmpFnCallDepth--;
		}
	;

expression
	:	expression '+' expression
		{
			/* confirm compatability of two types, gen code to cast if needed, else yyerror */
			/* gen code to do '+' operation */
			//$$ = compatible type;
			//! Check to make sure it happens. Cast if possible or error as necessary.
			
			// Set the return type
			int i = isIntAndFloat($1, $3);
			if( i < 0)
				yyerror("Could not perform operation on types '%s' and '%s'! ", 
					enumType($1),enumType($3));
			
			// All good. Set the expression type and output
			printf("%s add \n", getTabs(tabIndex));
			$$ = i;
		}
	|	expression '-' expression
		{
			int i = isIntAndFloat($1, $3);		
			if( i < 0)
				yyerror("Could not perform operation on types '%s' and '%s'! ", 
					enumType($1),enumType($3));
			
			// All good. Set the expression type and output
			printf("%s sub \n", getTabs(tabIndex));
			$$ = i;
		}
	|	expression '*' expression
		{
			int i = isIntAndFloat($1, $3);
			if( i < 0)
				yyerror("Could not perform operation on types '%s' and '%s'! ", 
					enumType($1),enumType($3));
			
			// All good. Set the expression type and output
			printf("%s mul \n", getTabs(tabIndex));
			$$ = i;
		}
	|	expression '/' expression
		{
			int i = isIntAndFloat($1, $3);
			if( i < 0)
				yyerror("Could not perform operation on types '%s' and '%s'! ", 
					enumType($1),enumType($3));
			
			// All good. Set the expression type and output
			printf("%s div \n", getTabs(tabIndex));
			$$ = i;
		}
	|	expression AND expression
		{
			
			char* trueLabel;
			char* afterLabel;
			/* confirm types are bool_ or can be casted to bool_, else yyerror */
			/* gen code to do AND operation */
			if( $1 != bool_ && $3 != bool_)
				yyerror("Could not perform operation on types '%s' and '%s'! ", 
					enumType($1),enumType($3));
			
			//! both expressions should have pushed a one, so we if add the stack and whats on the stack isn't 2, its false
			printf("%s add \n", getTabs(tabIndex));
			
			//! push 2 onto stack for comparison
			printf("%s ldc.i4 2 \n", getTabs(tabIndex));
			
			//! generate labels
			trueLabel = generateLabel();
			afterLabel = generateLabel();
			
			//! branch to trueLabel if stack is >= 2
			printf("%s bge %s \t//&& branch if true \n\n", getTabs(tabIndex), trueLabel);
			
				//! if your here, it's not >=2; push 0 for false, then branch to afterLabel
				printf("%s ldc.i4 0 \t//&& push false \n", getTabs(tabIndex));
				printf("%s br %s \n", getTabs(tabIndex), afterLabel);
				
				//! print the true label, then generate the one
				printf("%s: \t\t//&& TRUE LABEL \n", trueLabel);
				printf("%s ldc.i4 1 \n", getTabs(tabIndex));
			
			//! print after label, then be done
			printf("%s: \t\t//&& AFTER LABEL\n", afterLabel);
			$$ = bool_;
		}
	|	expression OR expression
		{
			
			char* trueLabel;
			char* afterLabel;
			/* confirm types are bool_ or can be casted to bool_, else yyerror */
			/* gen code to do || operation */
			if( $1 != bool_ && $3 != bool_)
				yyerror("Could not perform operation on types '%s' and '%s'! ", 
					enumType($1),enumType($3));
			
			//! both expressions should have pushed a one, so we if add the stack and whats on the stack isn't 2, its false
			printf("%s add \n", getTabs(tabIndex));
			
			//! push 0 onto stack for comparison
			printf("%s ldc.i4 0 \n", getTabs(tabIndex));
			
			//! generate labels
			trueLabel = generateLabel();
			afterLabel = generateLabel();
			
			//! branch to trueLabel if stack is > 0
			printf("%s bgt %s \t//|| branch if true \n\n", getTabs(tabIndex), trueLabel);
			
				//! if your here, it's not >=2; push 0 for false, then branch to afterLabel
				printf("%s ldc.i4 0 \t//|| push false \n", getTabs(tabIndex));
				printf("%s br %s \n", getTabs(tabIndex), afterLabel);
				
				//! print the true label, then generate the one
				printf("%s: \t\t//|| TRUE LABEL \n", trueLabel);
				printf("%s ldc.i4 1 \n", getTabs(tabIndex));
			
			//! print after label, then be done
			printf("%s: \t\t//|| AFTER LABEL\n", afterLabel);
			$$ = bool_;
		}
	|	expression EQUALS expression
		{
			$$ = bool_;
			// start here
			if($1 == string_ && $3 != bool_){
				printf("%s callvirt instance int32 [mscorlib]System.String::CompareTo(%s)\n", 
					getTabs(tabIndex), enumType($3));
				// if they're equal, we get 0, so then we just compare 0 to 0 to get true	
				printf("%s ldc.i4 0", getTabs(tabIndex));
			}else if($1 != $3){
				if(isIntAndFloat($1, $3) == -1){
					printf("%s pop \n", getTabs(tabIndex));
					printf("%s pop \n", getTabs(tabIndex));
					printf("%s ldc.i4 0 \n", getTabs(tabIndex));
					printf("%s ldc.i4 1 \n", getTabs(tabIndex));
				}
			}
			printf("%s ceq \t// Are they equal \n", getTabs(tabIndex));
			
			
		}
	|	expression NOT_EQUALS expression
		{
			$$ = bool_;
			// start here
			if($1 == string_ && $3 != bool_){
				printf("%s callvirt instance int32 [mscorlib]System.String::CompareTo(%s)\n", 
					getTabs(tabIndex), enumType($3));
				// if they're equal, we get 0, so then we just compare 0 to 0 to get true	
				printf("%s ldc.i4 0", getTabs(tabIndex));
			}else if($1 != $3){
				if(isIntAndFloat($1, $3) == -1){
					printf("%s pop \n", getTabs(tabIndex));
					printf("%s pop \n", getTabs(tabIndex));
					printf("%s ldc.i4 0 \n", getTabs(tabIndex));
					printf("%s ldc.i4 1 \n", getTabs(tabIndex));
				}
			}
			printf("%s ceq \t// Are they equal? \n", getTabs(tabIndex));
			//! if they're equal, we have a true on the stack. So if we compare with a false, we'll get the right answer
			printf("%s ldc.i4 0 \t// 0 for comparing our answer \n", getTabs(tabIndex));
			
			printf("%s ceq \t// Invert our answer \n", getTabs(tabIndex));
		}
	|	expression '<' expression
		{
			/* confirm compatability of two types, gen code to cast if needed, else yyerror */
			/* gen code to do '<' */
			if( ($1 != int_ && $1 != float_) ||
				($3 != int_ && $3 != float_))
				yyerror("Could not perform operation on types '%s' and '%s'! ", enumType($1),enumType($3));
			
			// Convert the top item ($3) to the second item($1)'s type
			if($1 != $3) 
				printf("%s conv.%s \t\t//convert to other type \n", getTabs(tabIndex), primType($1));
			
			printf("%s clt \t\t//tos+1 < tos \n", getTabs(tabIndex));
			$$ = bool_;
		}
	|	expression '>' expression
		{
			/* confirm compatability of two types, gen code to cast if needed, else yyerror */
			/* gen code to do '>' */
			if( ($1 != int_ && $1 != float_) ||
				($3 != int_ && $3 != float_))
				yyerror("Could not perform operation on types '%s' and '%s'! ", enumType($1),enumType($3));
			
			if($1 != $3) 
				printf("%s conv.%s \t\t//convert to other type \n", getTabs(tabIndex), primType($1));
				
			printf("%s cgt \t\t//tos+1 < tos \n", getTabs(tabIndex));
			$$ = bool_;
		}
	|	expression LTE expression
		{
			/* confirm compatability of two types, gen code to cast if needed, else yyerror */
			/* gen code to do LTE */
			if( ($1 != int_ && $1 != float_) ||
				($3 != int_ && $3 != float_))
				yyerror("Could not perform operation on types '%s' and '%s'! ", enumType($1),enumType($3));
			
			if($1 != $3) 
				printf("%s conv.%s //convert to other type \n", getTabs(tabIndex), primType($1));
				
			// subtract them
			printf("%s sub \n", getTabs(tabIndex));
			
			printf("%s ldc.i4 0 \n", getTabs(tabIndex));
			// if result < 0, it's true
			printf("%s clt \n", getTabs(tabIndex));
			
			$$ = bool_;
		}
	|	expression GTE expression
		{
			/* confirm compatability of two types, gen code to cast if needed, else yyerror */
			/* gen code to do GTE */
			if( ($1 != int_ && $1 != float_) ||
				($3 != int_ && $3 != float_))
				yyerror("Could not perform operation on types '%s' and '%s'! ", enumType($1),enumType($3));
			
			if($1 != $3) 
				printf("%s conv.%s //convert to other type \n", getTabs(tabIndex), primType($1));
				
			// subtract them
			printf("%s sub \n", getTabs(tabIndex));
			
			printf("%s ldc.i4 0 \n", getTabs(tabIndex));
			// if result > 0, it's true
			printf("%s cgt \n", getTabs(tabIndex));
			
			$$ = bool_;
		}
	|	'(' expression ')'
		{
			$$ = $2;
		}
	|	INT_CONST
		{
			printf("%s ldc.i4 %s \n", getTabs(tabIndex), $1);
			$$ = int_;
		}
	|	FLOAT_CONST
		{
			/* push $1 */
			printf("%s ldc.r4 %s \n", getTabs(tabIndex), $1);
			$$ = float_;
		}
	|	STRING_CONST
		{
			/* push $1 */
			printf("%s ldstr \"%s\" \n", getTabs(tabIndex), $1);
			
			$$ = string_;
		}
	|	TRUE
		{
			/* push boolean true */
			printf("%s ldc.i4 1 \n", getTabs(tabIndex));
			$$ = bool_;
		}
	|	FALSE
		{
			/* push boolean false */
			printf("%s ldc.i4 0 \n", getTabs(tabIndex));
			$$ = bool_;
		}
	|	data_ref
		{
			//! if array, but not ref'd as array, error
			if ( $1.symbPtr->isArray && !$1.isArrayRef )
				yyerror( "%s is an array and not referenced as an array element", $1.symbPtr->name );
			
			
			//! Push the variable's contents onto the stack
			if( $1.symbPtr->isArray){
				printf("%s ldelem %s\n", getTabs(tabIndex), enumType($1.symbPtr->type));
			}else{
				if( strcmp($1.symbPtr->context, "@global")){
					printf("%s ldloc %s \n", getTabs(tabIndex), $1.symbPtr->name);
				}else{
					printf("%s ldsfld %s %s::%s \n", getTabs(tabIndex), 
						enumType($1.symbPtr->type), className, $1.symbPtr->name);
				}
			}
			
			
			/* push '$1' */
			$$ = $1.symbPtr->type;
		}
	|	data_ref '.' LENGTH
		{			
			if ( $1.symbPtr->isArray && !( $1.isArrayRef ))
				printf("%s ldc.i4 %i \n", getTabs(tabIndex), $1.symbPtr->arrayMax);
			else if ( $1.symbPtr->type == string_ ){
				printf("%s ldloc %s \n", getTabs(tabIndex), $1.symbPtr->name);
				printf("%s callvirt instance int32 [mscorlib]System.String::get_Length() \n", getTabs(tabIndex));
			}
			else
				yyerror( "identifier %s is not an array name or a string", $1.symbPtr->name );
				
			$$ = int_;
		}
	|	data_ref '.' CHAR '(' expression ')'
		{
			if ( $1.symbPtr->isArray && !$1.isArrayRef )
				yyerror( "%s is an array and not referenced as an array element", $1.symbPtr->name );
			
			if ( $5 != int_ )
			{
				if($5 == float_ )
					printf("%s conv.i4 \n", getTabs(tabIndex));
				else
					yyerror( "function CHAR requires int; Cannot convert %s (%s) ",
						$1.symbPtr->name, enumType($1.symbPtr->type) );
				
			}
			// expression should be on there
			printf("%s stloc _int32 \n", getTabs(tabIndex));
			
			printf("%s ldloc %s \n", getTabs(tabIndex), $1.symbPtr->name);
			printf("%s callvirt instance char[] [mscorlib]System.String::ToCharArray() \n", getTabs(tabIndex));
			// now we have a character array on the stack
			printf("%s ldloc _int32 \t\t// the character to get\n", getTabs(tabIndex));
			printf("%s ldelem.u2 \t\t// load the character\n", getTabs(tabIndex));
			printf("%s call int32 [mscorlib]System.Convert::ToInt32(char)\n", getTabs(tabIndex));
			
			$$ = int_;
		}
	|	CHAR '(' expression ')'
		{
			if ( $3 != int_ )
			{
				;	/* see if $3 can be casted to int_; if yes, then do so; if no, then yyerror */
			}
			
			;	/* create code to push the string consisting of the single ASCII character of value $3 on stack */
			
			$$ = string_;
		}
	|	data_ref '.' SUBSTR '(' expression ',' expression ')'
		{
			if ( $1.symbPtr->isArray && !$1.isArrayRef )
				yyerror( "%s is an array and not referenced as an array element", $1.symbPtr->name );
			
			if ( $5 != int_ )
			{
				;	/* see if $5 can be casted to int_; if yes, then do so; if no, then yyerror */
			}
			if ( $7 != int_ )
			{
				;	/* see if $7 can be casted to int_; if yes, then do so; if no, then yyerror */
			}
			
			;	/* create code to push string $1.substring( $5, $7 ) on stack */
				/* make sure the .NET method used will throw an exsception if $5 to $7 is outside of $1 */
				
			$$ = string_;
		}
	|	ID inc_function_call_depth '(' function_call_parameters ')'
		{
		struct symbolDef *symbPtr;
		int i, n;
		int params;
			symbPtr = getSymbol( "@global", $1 );
			if ( !symbPtr )
				yyerror( "function %s does not exist (yet) in symbol table", $1 );
				
			/* confirm fn parameters for ID correspond to the tmpFnCallParmIdx[$2] types in tmpFnCallParms[$2] produced in function_call_list else yyerror */
			/* confirm fn return type not VOID else yyerror */
			/* create code to call fn with parameters (they are already on the stack) */
			
			//! this needs to be passed the return value, then the parameter list inside of the ()			
			printf("%s call %s %s::%s(", getTabs(tabIndex), 
				enumType(symbPtr->fnRetType), className, symbPtr->name);

			params = symbPtr->fnNumParams;
			for(n = 1; n <= params; n++){
				for ( i=0; i<NSYMS; i++ ){
					if ( symtab[i].name[0] == "/0"){
						break;
					}
					if ( symtab[i].isParam && symtab[i].paramSeq == n && strcmp(symtab[i].context, $1) == 0){
						if(n != 1) printf(",");
						printf(" %s", enumType(symtab[i].type));
					}
				}
			}
			printf(" ) \n");
			
			tmpFnCallDepth--;
			$$ = symbPtr->fnRetType;
		}
	;
	
inc_function_call_depth
	:	{
			$$ = ++tmpFnCallDepth;
		}
	;

function_call_parameters
	:	{
			tmpFnCallParmIdx[ tmpFnCallDepth ] = 0;
		}
		function_call_list
	|	{
			tmpFnCallParmIdx[ tmpFnCallDepth ] = 0;	/* no parameters to function */
		}
	;
	
function_call_list
	:	expression
		{
			tmpFnCallParms[ tmpFnCallDepth ][ tmpFnCallParmIdx[ tmpFnCallDepth ]++ ] = $1;
		}
	|	function_call_list ',' expression
		{
			tmpFnCallParms[ tmpFnCallDepth ][ tmpFnCallParmIdx[ tmpFnCallDepth ]++ ] = $3;
		}
	;
	
print_list
	:	expression
		{
			;	/* output code to print and pop data type $1, which is on the stack */
			printf("%s call void [mscorlib]System.Console::Write(%s) \n", getTabs(tabIndex), enumType($1));
			
		}
	|	print_list ',' expression
		{
			;	/* output code to print and pop data type $3, which is on the stack */
			printf("%s call void [mscorlib]System.Console::Write(%s) \n", getTabs(tabIndex), enumType($3));
		}
	;
	
%%

// arrayMax == 0 for non-array or fn or fn parameter
// fnNumParams will define the number of parameters if symbol is a fn
// paramSeq will define the sequence of parameters to a fn
int setSymbol( char *context, char *symbol, DType type, unsigned int arrayMax, boolean isparam ){
	int i;
	struct symbolDef *func;

	if ( isparam && ( arrayMax != 0 ))
		yyerror( "internal fault: symbol %s in context %s can't be declared an array and a parameter", symbol, context );
	if ( isparam && ( type < int_ || type > bool_ ))
		yyerror( "internal fault: symbol %s in context %s being set as type other than int, float, string, or bool", symbol, context );
		
	for ( i=0; i<NSYMS; i++ )
		if ( symtab[i].name[0] != '\0' )
		{
			if ( !strcmp( symtab[i].context, context ) && !strcmp( symtab[i].name, symbol ))
				yyerror( "identifier %s already defined in context %s\n", symbol, context );
		}

	if ( strlen( context ) > MAX_IDENT_LEN )
		yyerror( "context name %s has exceeded compiler max length of %d", context, MAX_IDENT_LEN );
		
	if ( strlen( symbol ) > MAX_IDENT_LEN )
		yyerror( "symbol name %s has exceeded compiler max length of %d", symbol, MAX_IDENT_LEN );
		
	for ( i=0; i<NSYMS; i++ )
		if ( symtab[i].name[0] == '\0' )
		{
			strcpy( symtab[i].context, context );
			strcpy( symtab[i].name, symbol );
			symtab[i].type = type;
			if ( arrayMax )
			{
				symtab[i].isArray = TRUE_;
				symtab[i].arrayMax = arrayMax;
			}
			else
			{
				symtab[i].isArray = FALSE_;
				symtab[i].arrayMax = 0;
			}
			symtab[i].isParam = isparam;
			if ( isparam )
			{
				func = getSymbol( "@global", context );
				if ( !func )
					yyerror( "internal fault: function %s not in symbol table when setting parameter %s in symbol table", context, symbol );
				func->fnNumParams++;
				symtab[i].paramSeq = func->fnNumParams;
			}
			else
				symtab[i].paramSeq = 0;
			symtab[i].fnNumParams = 0;
			symtab[i].fnRetType = unknown_;
			return 1;
		}

	yyerror( "symbol table is full; identifier %s can't be defined in context %s", symbol, context );

}


int setFuncRetType( char *fnName, DType retType ){
	struct symbolDef *fnPtr;

	fnPtr = getSymbol( "@global", fnName );
	if ( !fnPtr )
		yyerror( "function %s does not exist (yet) in symbol table", fnName );

	if ( fnPtr->fnRetType != unknown_ )
		yyerror( "function %s already has a return type set in symbol table", fnName );
		
	fnPtr->fnRetType = retType;
	return 1;
}


struct symbolDef *getSymbol( char *context, char *symbol ){
	int i;
	for ( i=0; i<NSYMS; i++ )
		if ( !strcmp( context, symtab[i].context ) && !strcmp( symbol, symtab[i].name ))
			return symtab+i;
	
	return NULL;	
}


char *generateLabel( void ){
	sprintf( genedLabel, "label%d", labelIndex++ );
	return _strdup(genedLabel);
}

char *enumType(DType type){
	switch(type){
		case 1:
			return "void";
			break;
		case 2:
			// Int
			return "int32";
			break;
		case 3:
			// float
			return "float32";
			break;
		case 4:
			return "string";
			// String
			break;
		case 5:
			// bool
			return "bool";
			break;
			
		default:
			return "unknown";
	}
}

char *primType(DType type){
	switch(type){
		case 1:
			return "";
			break;
		case 2:
			// Int
			return "i4";
			break;
		case 3:
			// float
			return "r4";
			break;
		case 4:
			return "string";
			// String
			break;
		case 5:
			// bool
			return "i4";
			break;
			
		default:
			return "unknown";
	}
}
char *systemType(DType type){
	switch(type){
		case 2:
			// Int
			return "System.Int32";
			break;
		case 3:
			// float
			return "System.Single";
			break;
		case 4:
			return "System.String";
			// String
			break;
		case 5:
			// bool
			return "System.Boolean";
			break;
			
		default:
			return "unknown";
	}
}
char *getTabs(int count){
	int i=0;
	char tabBuffer[255];
	if(count > 0){
		sprintf(tabBuffer, "\t");
		i++;
	}
	while(i < count){
		sprintf(tabBuffer, "%s\t", tabBuffer);
		i++;
	}
	return _strdup(tabBuffer);
}

void debug(char *output){
	if(_isDebug == 1)
		printf("\n\t// Debug: %s\n", output);
}
void main(){
	sprintf(className, "myclass");
	yyparse();
}
int getLocalIndex(){
	return localIndex++;
}

int isIntAndFloat(DType val1, DType val2){
		if(val1 == val2 && val1 == int_)
			return int_;
		
		if(val1 == val2 && val1 == float_)
			return float_;			
		if(val1 == float_ && val2 == int_){
			printf("%s conv.r4 // Cast int to double\n", getTabs(tabIndex));
			return float_;			
		}
		if(val1 == int_ && val2 == float_){

			printf("%s stloc _float32 // temp store \n", getTabs(tabIndex));
			printf("%s conv.r4 // Cast int to double\n", getTabs(tabIndex));
			printf("%s ldloc _float32 // load temp \n", getTabs(tabIndex));
			return float_;
		}
		return -1;
}