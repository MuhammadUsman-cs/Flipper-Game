#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<strings.h>
#include<windows.h>

//Displays tutorial
void Tutorial(char [52][20]);
//Tells which cards should be faced down (randomly)
void Cards_Flipper(int, char[][20]);
//Shuffles cards
void Cards_Shuffler(char [52][20],char [][20] ,int);
//Displays front side of card
void Display_Cards_Front(char [], int);
//Displays back side of card
void Display_Cards_Back();
// display new lines for cards which are removed from screen
void Display_Removed_Card();
// moves the pointer on the output screen
void gotoxy(int,int);
//Displays player record
void Leaderboards (FILE *,int *);
//Actual Game working
void GameWorking(int,int,int ,int ,char [50],char [5],int ,char [][20],char [][20],FILE *,FILE *);

int main()
{
    int KEY=0,num_cards=0;
    char KEY2='n',status[5],username[50];
    FILE *fptr1,*fptr2;
    char cards_name[52][20]={"A Ace of Hearts","2 Two of Hearts","3 Three of Hearts","4 Four of Hearts","5 Five of Hearts","6 Six of Hearts",
    "7 Seven of Hearts","8 Eight of Hearts","9 Nine of Hearts","10 Ten of Hearts","J Jack of Hearts","Q Queen of Hearts","K King of Hearts","A Ace of Diamonds",
    "2 Two of Diamonds","3 Three of Diamonds","4 Four of Diamonds","5 Five of Diamonds","6 Six of Diamonds","7 Seven of Diamonds","8 Eight of Diamonds",
    "9 Nine of Diamonds","10 Ten of Diamonds","J Jack of Diamonds","Q Queen of Diamonds","K King of Diamonds","A Ace of Clubs","2 Two of Clubs","3 Three of Clubs",
    "4 Four of Clubs","5 Five of Clubs","6 Six of Clubs","7 Seven of Clubs","8 Eight of Clubs","9 Nine of Clubs","10 Ten of Clubs","J Jack of Clubs","Q Queen of Clubs",
    "K King of Clubs","A Ace of Spades","2 Two of Spades","3 Three of Spades","4 Four of Spades","5 Five of Spades","6 Six of Spades","7 Seven of Spades",
    "8 Eight of Spades","9 Nine of Spades","10 Ten of Spades","J Jack of Spades","Q Queen of Spades","K King of Spades"};
    printf("###########    ##             ############    ############                   ############        ##\n");
    printf("##             ##                  ##         ##        ##                        ##             ##\n");
    printf("##             ##                  ##         ##        ##                        ##             ##\n");
    printf("###########    ##                  ##         ############                        ##         ###########\n");
    printf("##             ##                  ##         ##                                  ##             ##\n");
    printf("##             ##                  ##         ##                                  ##             ##\n");
    printf("##             ###########    ############    ##                             ############        ########\n\n\n\n\n");
    printf("\t\t\t\tWelcome to the Flipit Game\n\n\n");
    while (KEY==0)
    {
        printf("=>Enter \"1\" to start New Game\n\t\tOR\n=>Enter \"2\" to load saved game\n\t\tOR\n=>Enter \"3\" to see leaderboards\n\t\tOR\n=>Enter \"4\" to quit game\n\n=>");
        fflush(stdin);
        scanf("%d",&KEY);
        system("cls");
        while (KEY==1||KEY==2||KEY==3)
        {
            if (KEY==3)
            {
                fptr1 = fopen("Leaderboards.txt","a+");
                if (fptr1==NULL)
                {
                    printf("Could not open file Leaderboards.txt");
                    exit (0);
                }
                Leaderboards(fptr1,&KEY);
                fclose(fptr1);
                system("cls");
            }
            else if (KEY==2)
            {
                int nosave=0;
                fptr1 = fopen("Leaderboards.txt","a+");
                if (fptr1==NULL)
                {
                    printf("Could not open file Leaderboards.txt");
                    exit (0);
                }
                fptr2 = fopen("Saved Data.bin","rb");
                if (fptr2==NULL)
                {
                    printf("No saved data found.\n");
                    nosave = 1;

                }
                if (nosave != 1)
                {
                   fread(&num_cards,sizeof(num_cards),1,fptr2);
                    char rand_cards_name[num_cards][20];
                    char flipped_cards[num_cards][20];
                    int j,begin,begin2,time_to_pause;
                    int flag=0,count=0;
                    fread(&j,sizeof(j),1,fptr2);
                    fread(&flag,sizeof(flag),1,fptr2);
                    fread(&begin,sizeof(begin),1,fptr2);
                    fread(&begin2,sizeof(begin2),1,fptr2);
                    for (int k=0;k<num_cards;k++)
                    {
                        fread(rand_cards_name[k],sizeof(rand_cards_name[k]),1,fptr2);
                    }
                    for (int k=0;k<num_cards;k++)
                    {
                        fread(flipped_cards[k],sizeof(flipped_cards[k]),1,fptr2);
                    }
                    fread(username,sizeof(username)*strlen(username),1,fptr2);
                    fclose(fptr2);
                    time_t end2 = time(NULL);
                    time_to_pause = end2 - begin2;
                    for (int i=0;i<num_cards;i++)
                    {
                        if (strcmp(flipped_cards[i],"remove")==0)
                        {
                            Display_Removed_Card();
                        }
                        else if (strcmp(flipped_cards[i],"flipit")==0)
                        {
                            Display_Cards_Back();
                        }
                        else if (strcmp(flipped_cards[i],"flipit")!=0)
                        {
                            Display_Cards_Front(rand_cards_name[i],count);
                        }
                        count++;
                    }
                    GameWorking(time_to_pause,begin,flag,num_cards,username,status,j,rand_cards_name,flipped_cards,fptr1,fptr2);
                }
                printf("\n\n\n\t\t\t\t=>Enter 0 to return to main menu\n\n\t\t\t\t=>");
                scanf("%d",&KEY);
                system("cls");
            }
            else if (KEY==1)
            {
                fptr1 = fopen("Leaderboards.txt","a+");
                if (fptr1==NULL)
                {
                    printf("Could not open file Leaderboards.txt");
                    exit (0);
                }
                system("cls");
                printf("=>Enter username (without space): ");
                fflush(stdin);
                gets(username);
                for (int i=0;i<strlen(username);i++)
                {
                    if (username[i]==' ')
                    {
                        system("cls");
                        printf("\n=>Enter valid username (without space): ");
                        fflush(stdin);
                        gets(username);
                        i=-1;
                    }
                }
                printf("\n\n=>Do you wish to see the tutorial (y/n): ");
                fflush(stdin);
                scanf("%c",&KEY2);
                system("cls");
                if (KEY2=='y')
                {
                    Tutorial(cards_name);
                    printf("\n\n\n\t\t\t\tPress any key to start the game");
                    getch();
                }
                system("cls");
                printf("Choose number of cards you want to play with (within 52):");
                scanf("%d",&num_cards);
                while (num_cards>52)
                {
                    printf("Choose number of cards you want to play with (within 52):");
                    scanf("%d",&num_cards);
                }
                system("cls");
                char rand_cards_name[num_cards][20];
                char flipped_cards[num_cards][20];
                int flag=0,j=0,time_to_pause=0;
                Cards_Shuffler(cards_name,rand_cards_name,num_cards);
                Cards_Flipper(num_cards,flipped_cards);
                time_t begin=time(NULL);
                int count=0;
                for (int i=0;i<num_cards;i++)
                {
                    if (strcmp(flipped_cards[i],"flipit")==0)
                    {
                        Display_Cards_Back();
                    }
                    else if (strcmp(flipped_cards[i],"flipit")!=0)
                    {
                        Display_Cards_Front(rand_cards_name[i],count);
                    }
                    count++;
                }
                GameWorking(time_to_pause,begin,flag,num_cards,username,status,j,rand_cards_name,flipped_cards,fptr1,fptr2);
                printf("\n\n\n\t\t\t\t=>Enter 0 to return to main menu\n\n\t\t\t\t=>");
                scanf("%d",&KEY);
                system("cls");
            }
        }
    }
    if (KEY==4)
    {
        exit(0);
    }
    return 0;
}

void GameWorking(int time_to_pause,int begin,int counter_flag,int num_cards,char username[50],char status[5],int j,char rand_cards_name[][20],char flipped_cards[][20],FILE *fptr1,FILE *fptr2)
{
    char c_flipper;
    int flipper1,count,flag=0,sec,min,t,score;
    for (j=j;j<num_cards;j++)
    {
        printf("=>Enter \"S\" to save game and continue\n\t\tOR\n=>Enter \"M\" to quit to main menu\n\t\tOR\n=>Enter \"E\" to save and quit to main menu\n\t\tOR\n=>Enter \"C\" to continue without saving\n\n=>");
        fflush(stdin);
        scanf("%c",&c_flipper);
        while (c_flipper!='S'&&c_flipper!='E'&&c_flipper!='M'&&c_flipper!='C')
        {
            printf("=>Enter valid key: ");
            fflush(stdin);
            scanf("%c",&c_flipper);
        }
        if (c_flipper=='S'||c_flipper=='E')
        {
            fptr2 = fopen("Saved Data.bin","wb+");
            if (fptr2==NULL)
            {
                printf("Could not open file Saved Data.bin");
                exit (0);
            }
            time_t begin2=time(NULL);
            fwrite(&num_cards,sizeof(num_cards),1,fptr2);
            fwrite(&j,sizeof(j),1,fptr2);
            fwrite(&counter_flag,sizeof(counter_flag),1,fptr2);
            fwrite(&begin,sizeof(begin),1,fptr2);
            fwrite(&begin2,sizeof(begin2),1,fptr2);
            for (int k=0;k<num_cards;k++)
            {
                fwrite(rand_cards_name[k],sizeof(rand_cards_name[k]),1,fptr2);
            }
            for (int k=0;k<num_cards;k++)
            {
                fwrite(flipped_cards[k],sizeof(flipped_cards[k]),1,fptr2);
            }
            fwrite(username,sizeof(username)*strlen(username),1,fptr2);
            fclose(fptr2);
            if (c_flipper=='E')
                break;
        }
        else if (c_flipper=='M')
        {
            break;
        }
        if (c_flipper == 'S' || c_flipper == 'C')
        {
            printf("=>Enter number of card you want to flip: ");
            fflush(stdin);
            scanf("%d",&flipper1);
        }
        for (int i=0;i<num_cards;i++)
        {
            if ((strcmp(flipped_cards[i],"remove")==0)&&(flipper1==i))
            {
                printf("=>Please Enter a Valid Card Number : ");
                fflush(stdin);
                scanf("%d",&flipper1);
                i=-1;
            }
            if ((strcmp(flipped_cards[i],"flipit")==0)&&(flipper1==i))
            {
                printf("=>Please Enter a Valid Card Number : ");
                fflush(stdin);
                scanf("%d",&flipper1);
                i=-1;
            }
            if (flipper1>=num_cards||flipper1<0)
            {
                printf("=>Please Enter a Valid Card Number : ");
                fflush(stdin);
                scanf("%d",&flipper1);
                i=-1;
            }
        }
        system("cls");
        count=0;
        for (int i=0;(i<num_cards);i++)
        {
            if ((i==flipper1)||(strcmp(flipped_cards[i],"remove")==0))
            {
                Display_Removed_Card();
            }
            else if ((i==flipper1-1)&&(flipper1!=0))
            {
                if (((strcmp(flipped_cards[i],"noflip")!=0)&&(strcmp(flipped_cards[i],"flipit")==0))&&(strcmp(flipped_cards[i],"remove")!=0))
                {
                    Display_Cards_Front(rand_cards_name[i],count);
                    strcpy (flipped_cards[i],"noflip");
                }
                else if (((strcmp(flipped_cards[i],"flipit")!=0))&&(strcmp(flipped_cards[i],"remove")!=0))
                {
                    Display_Cards_Back();
                    strcpy (flipped_cards[i],"flipit");
                }
            }
            else if ((i==flipper1+1)&&(i<num_cards))
            {
                if (((strcmp(flipped_cards[i],"noflip")!=0)&&(strcmp(flipped_cards[i],"flipit")==0))&&(strcmp(flipped_cards[i],"remove")!=0))
                {
                    Display_Cards_Front(rand_cards_name[i],count);
                    strcpy (flipped_cards[i],"noflip");
                }
                else if (((strcmp(flipped_cards[i],"flipit")!=0))&&(strcmp(flipped_cards[i],"remove")!=0))
                {
                    Display_Cards_Back();
                    strcpy (flipped_cards[i],"flipit");
                }
            }
            else if ((i!=flipper1)&&(i!=flipper1+1)&&(i!=flipper1-1)&&(strcmp(flipped_cards[i],"remove")!=0))
            {
                if (strcmp(flipped_cards[i],"flipit")==0)
                {
                    Display_Cards_Back();
                }
                else if (strcmp(flipped_cards[i],"flipit")!=0)
                {
                    Display_Cards_Front(rand_cards_name[i],count);
                }
            }
            count++;
        }
        strcpy(flipped_cards[flipper1],"remove");
        counter_flag++;
        flag=0;
        for (int k=0;k<num_cards;k++)
        {
            if ((strcmp(flipped_cards[k],"flipit")==0)||(strcmp(flipped_cards[k],"remove")==0))
            {
                flag++;
            }
        }
        if (flag==num_cards)
        {
            break;
        }
    }
    time_t end = time(NULL);
    t = (end-begin) - time_to_pause;
    sec=t;
    min=sec/60;
    sec=sec%60;
    system("cls");
    if ((flag==num_cards)&&(counter_flag!=num_cards))
    {
        printf("##########   ##########   ####            ####   ##########        ##########    ##           ##     ###########    ##########\n");
        printf("##           ##      ##   ## ##          ## ##   ##                ##      ##     ##         ##      ##             ##      ##\n");
        printf("##           ##      ##   ##  ##        ##  ##   ##                ##      ##      ##       ##       ##             ##      ##\n");
        printf("##  ######   ##########   ##   ##      ##   ##   ##########        ##      ##       ##     ##        ###########    ##########\n");
        printf("##      ##   ##      ##   ##    ##    ##    ##   ##                ##      ##        ##   ##         ##             ####\n");
        printf("##      ##   ##      ##   ##     ##  ##     ##   ##                ##      ##         ## ##          ##             ## ###\n");
        printf("##########   ##      ##   ##      ####      ##   ##########        ##########          ###           ###########    ##   #####\n");
        printf("\n\n\n\t\t\t\t You Have Lost The Game.\n\n\n");
        if (min>0)
            printf("Time Taken:%d minutes  %d Seconds",min,sec);
        else
            printf("Time Taken:%d Seconds",sec);
        score=0;
        printf("\nScore: %d\n\n",score);
        strcpy(status,"Lost");
    }
    else if(counter_flag==num_cards)
    {
        printf("##########   ##########   ####      ##    ###########  ##########    ##########    ##########    ###########\n");
        printf("##           ##      ##   ## ##     ##    ##           ##      ##    ##      ##        ##        ##\n");
        printf("##           ##      ##   ##  ##    ##    ##           ##      ##    ##      ##        ##        ##\n");
        printf("##           ##      ##   ##   ##   ##    ##   ######  ##########    ##########        ##        ###########\n");
        printf("##           ##      ##   ##    ##  ##    ##       ##  ####          ##      ##        ##                 ##\n");
        printf("##           ##      ##   ##     ## ##    ##       ##  ## ###        ##      ##        ##                 ##\n");
        printf("##########   ##########   ##      ####    ###########  ##   #####    ##      ##        ##        ###########\n");
        printf("\n\n\n\t\t\t\t You Have Won The Game.\n\n\n");
        if (min>0)
            printf("Time Taken:%d minutes  %d Seconds",min,sec);
        else
            printf("Time Taken:%d Seconds",sec);
        score=(num_cards*10000)/ t;
        printf("\nScore: %d\n\n",score);
        strcpy(status,"Won");
    }
    if (flag == num_cards)
    {
        if (min>0)
            fprintf(fptr1,"%s %d %s %d %d %d\n",username,num_cards,status,min,sec,score);
        else
            fprintf(fptr1,"%s %d %s %d %d %d\n",username,num_cards,status,0,sec,score);
        fclose(fptr1);
    }
}

void Display_Cards_Front(char rcname[],int count)
{
    int i;
    char copystr[20];
    char *token1, *token2, *token3,*token4;
    int num;
    strcpy(copystr,rcname);
    token1 = strtok(copystr," ");
    num = atoi(token1);
    token2 = strtok(NULL," ");
    token3 = strtok(NULL," ");
    token4 = strtok(NULL," ");
    printf("*********\n");
     for (i=0;i<=8;i++)
    {
        if (!(i==2||i==3||i==4||i==0||i==8))
            printf("*");
        if (i==0)
        {
            if (num==10)
                printf("*%s     *",token1);
            else
                printf("*%s      *",token1);
        }
        if (i==2)
        {
            printf("  %s",token2);
        }
        if (i==3)
        {
            printf("   of           (%d)",count);
        }
        if (i==4)
        {
            printf(" %s",token4);
        }
        if (i==8)
        {
            if (num==10)
                printf("*     %s*",token1);
            else
                printf("*      %s*",token1);
        }
        if (!(i==2||i==3||i==4||i==0||i==8))
            printf("%8c",'*');
        printf("\n");
    }
    printf("*********\n\n\n");
}

void Display_Cards_Back()
{
    int i,j;
    for (i=0;i<=8;i++)
    {
        printf("|");
        for (j=0;j<=7;j++)
        {
            printf("*");
        }
        printf("|");
    printf("\n");
    }
    printf("\n\n");
}

void Display_Removed_Card()
{
    for (int i=0;i<=8;i++)
    {
        printf("\n");
    }
    printf("\n\n");
}

void Cards_Shuffler(char cards_name[52][20],char rand_cards_name[][20],int num_cards)
{
    int rand_num,i=0;
    srand(time(0));
    for (i=0;i<num_cards;i++)
    {
        rand_num= rand() % 52;
        strcpy(rand_cards_name[i],cards_name[rand_num]);
    }
}

void Cards_Flipper(int num_cards, char flipped_cards[][20])
{
    int i,flipnum,flip;
    srand(time(0));
    flipnum = rand() % (num_cards);
    if (num_cards%2!=0)
     {
        while (flipnum%2!=0||flipnum==1)
        {
            flipnum = rand() % (num_cards);
        }
     }
     else if (num_cards%2==0)
     {
        while (flipnum%2==0)
        {
            flipnum = rand() % (num_cards);
        }
     }
    for (i=1;i<=flipnum;i++)
    {
        flip = rand() % (num_cards);
        while (strcmp(flipped_cards[flip],"flipit")==0)
        {
            flip = rand() % (num_cards);
        }
        strcpy(flipped_cards[flip],"flipit");
    }
}

void Tutorial(char cards_name[52][20])
{
    printf("=> Choose the number of cards you want to play with (must not be greater than 52)\n\n\n");
    printf("=> Cards will be randomly displayed in face up and down manner like shown below.\n\n\n");
    for (int i=0;i<3;i++)
    {
        if ((i==0)||(i==2))
            Display_Cards_Back();
        else
            Display_Cards_Front(cards_name[i],1);
    }
    printf("=> Face up card has a number in front of them. Select any face up card you want to remove by entering its number.\n\n\n");
    printf("=> In the above case if you enter 1 the face up card will be removed and its neighbouring cards will be flipped.\n\n\n");
    Display_Cards_Front(cards_name[4],0);
    Display_Removed_Card();
    Display_Cards_Front(cards_name[2],2);
    printf("=> Remove all the cards from the table to win the game.\n\n\n=>Complete the game as fast as you can to get higher scores.\n\n\nNOTE:- \"YOU CAN ONLY REMOVE THE CARDS WHICH ARE FACED UP\".\n\n");
}

void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void Leaderboards(FILE *fptr,int *KEY)
{
    int file_chk,num_cards,min,sec,score;
    int x=0;
    int y=2;
    file_chk = fgetc(fptr);
    char Name[30],status[6];
    if (file_chk==EOF)
    {
        printf("No records found. Enter 1 to start game: ");
        scanf("%d",&*KEY);
    }
    else
    {
        ungetc(file_chk,fptr);
        printf("Name\t\t\t     Cards\t\tStatus\t\tTime Taken\t\t\tScore\n");
        printf("----\t\t\t     -----\t\t------\t\t----------\t\t\t-----\n");
        while (!feof(fptr))
        {
            fscanf(fptr,"%s %d %s %d %d %d\n",Name,&num_cards,status,&min,&sec,&score);
            gotoxy(x,y);
            printf("%s",Name);
            x=x+30;
            gotoxy(x,y);
            printf("%d",num_cards);
            x=x+20;
            gotoxy(x,y);
            printf("%s",status);
            x=x+15;
            gotoxy(x,y);
            printf("%d mins %d secs",min,sec);
            x=x+32;
            gotoxy(x,y);
            printf("%d",score);
            x=0;
            y++;
        }
        while (*KEY!=0)
        {
            printf("\n\n\n\n\t\t\t\t=>Enter \"0\" to return to main menu\n\n\t\t\t\t=>: ");
            scanf("%d",&*KEY);
        }
    }
}
