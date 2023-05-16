int a1;
int a1; /* redeclaration allowed in global scope if same type */
int a2;
char a2; /* line 11: conflicting types for 'a2' */
int a3;
int _a1;
int _a1; /* redeclaration allowed in global scope if same type */
char _a2;
int _a2; /* line 17: conflicting types for '_a2'*/
int _a3;
char b1;
char _b1; /* line 23: conflicting types for '_b1' */

int _c1;
int *c1;
int c1; /* line 27: conflicting types for 'c1' */

int fun(int a);
int fun; /* line 30: conflicting types for 'fun' */

int fun1(int a), fun2;

int fun3(int a, int b);
int fun3(int a, int b, int c); /* line 36: conflicting types for 'fun3' */

int fun4(void);
int *fun4(void); /* line 39: conflicting types for 'fun4' */

int fun5(int a, int b);

int fun6[10];
int fun6[10]; /* redeclaration allowed in global scope if same type */

int fun7[10];
int fun7[11]; /* line 48: conflicting types for 'fun7' */

int fun8;
int fun8[10]; /* line 51: conflicting types for 'fun8' */

int fun9[10];
int fun9(int a); /* line 54: conflicting types for 'fun9' */

int fun10(int fun11);
int fun11;
int fun10; /* line 58: conflicting types for 'fun10' */

int fun12[10];
int *fun12; /* line 61: conflicting types for 'fun12' */



int dog(int a)
{
    int b;
}
int dog(int a)
{               /* line 70: redefinition of 'dog' */
    int b;
}
int g(int a)
{
    int b;
}
int *g(int a)
{               /* line 78: redefinition of 'g' */
    int b;
}               /* No conflicting types error */
int e(int a)
{
    int b;
}
 e(int a)
{                  /* line 86: redefinition of 'e' */
    int b;
}                   /* No conflicting types errror */
 scu(int a)
{
    int a;  /* [E3] line 91: redeclaration of 'a' */
}
 lmu(int a, ...)
{
    a = 5;
}
 lmu(int a, ...)
{                       /* line 98: redefinition of 'lmu' */
    a = 5;
}
 foo(int a, ...);
 foo(int a, ...);
char foo(int a, ...); /* line 103: conflicting types for 'foo' */
char foo(int a);    /* line 104: conflicting types for 'foo' */

int brisk(void)
{
    int a;
    int a;  /* line 109: redeclaration of 'a' */

    int foo;
    return huh; /* line 114: 'huh' undeclared */
}

char coen;
 coen; /* line 118: conflicting types for 'coen' */
int cake(void)
{
    int raspberry;
    raspberry = 5;
    raspberry = idk; /* line 123: 'idk' undeclared */
    idk = 5;
    idk2 = 5; /* line 125: 'idk2' undeclared */
    go(); /* line 126: 'go' undeclared */
}