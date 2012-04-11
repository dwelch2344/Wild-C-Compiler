
#define NSYMS			500
#define NESTCALLDEPTH	10
#define NTMPCALLPARMS	32
#define TRUE_			1
#define FALSE_			0
#define MAX_IDENT_LEN	132

#define ERROR_MESSAGE 	"\n(%d:%d) Error: "

typedef int boolean;
typedef enum{ unknown_, void_, int_, float_, string_, bool_, func_} DType;

struct symbolDef
{
	char context[MAX_IDENT_LEN+1];	/* @gloabl or function name */
	char name[MAX_IDENT_LEN+1];		/* name of data element or function */
	DType type;						/* type of the data element */
	boolean isArray;				/* is this an array (1) or not (0) */
	boolean isParam;				/* is this a function parameter (1) or not (0) */
	int arrayMax;					/* number of array elements for global and local data; params CAN'T be arrays */
	int fnNumParams;				/* number of parameters to a function if type is func_ */
	int paramSeq;					/* sequence number of a parameter to a function if this is a parameter */
	DType fnRetType;				/* if a function, its return type */
};

struct dataDef
{
	char name[MAX_IDENT_LEN+1];		/* data name */
	DType type;						/* the data type */
	boolean isArray;				/* is this an array (1) or not (0) */
	int arrayMax;					/* number of array elements */
};

struct dataRef
{
	struct symbolDef *symbPtr;		/* pointer to struct in symtab */
	boolean isArrayRef;				/* was this an array reference */
};

struct labelDef
{
	char label1[MAX_IDENT_LEN+1];	/* first generated label */
	char label2[MAX_IDENT_LEN+1];	/* second generated label */
};

// arrayMax == 0 for non-array or fn; arrayMax will later define the number of parameters if a fn
int setSymbol( char *context, char *symbol, DType type, unsigned int arrayMax, boolean isparam );
struct symbolDef *getSymbol( char *context, char *symbol );
int setFuncRetType( char *fnName, DType retType );
char *generateLabel( void );

char *systemType(DType type);
char *primType( DType type );
char *enumType( DType type );
char *getTabs(int count);
void debug(char *output);

void yyerror(char *string, ...);

int getLocalIndex();
int isIntAndFloat(DType val1, DType val2);
