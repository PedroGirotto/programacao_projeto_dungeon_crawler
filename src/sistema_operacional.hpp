#if defined(__linux__)
    #include <termios.h>

    // Leitura imediata do input do usuário
    static struct termios old, current;

    // Termios
    void initTermios(int echo);
    void resetTermios(void);
    char getch_(int echo);
    char getch(void);
    char getche(void);

    // Funções Termios ##############################################################################################
    /* Initialize new terminal i/o settings */
    void initTermios(int echo)
    {
        tcgetattr(0, &old); /* grab old terminal i/o settings */
        current = old; /* make new settings same as old settings */
        current.c_lflag &= ~ICANON; /* disable buffered i/o */
        if (echo) {
            current.c_lflag |= ECHO; /* set echo mode */
        }
        else {
            current.c_lflag &= ~ECHO; /* set no echo mode */
        }
        tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
    }

    /* Restore old terminal i/o settings */
    void resetTermios(void)
    {
        tcsetattr(0, TCSANOW, &old);
    }

    /* Read 1 character - echo defines echo mode */
    char getch_(int echo)   
    {
        char ch;
        initTermios(echo);
        ch = getchar();
        resetTermios();
        return ch;
    }

    /* 
    Read 1 character without echo 
    getch() function definition.
    */
    char getch(void)
    {
        return getch_(0);
    }

    /* 
    Read 1 character with echo 
    getche() function definition.
    */
    char getche(void)
    {
        return getch_(1);
    }

    #define LIMPAR "clear"
#endif

#if defined(__WIN64__) || defined(__WIN32__)
    #include <conio.h>
    #define LIMPAR "cls"
#endif