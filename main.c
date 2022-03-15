#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define cls printf("silindi........\n")//printf("\e[1;1H\e[2J");

struct Account{
    int current_money;
};

struct Customer{
    char *name;  
    char *surname;
    char *username;
    char *password;
    char *phone;
    char *mail;
    char *iban;
    struct Account *account;
};

struct Customer* create_customer(){
    struct Customer *new_customer = (struct Customer*)malloc(sizeof(struct Customer));
    new_customer->name = (char*)malloc(30*sizeof(char));
    new_customer->surname = (char*)malloc(30*sizeof(char));
    new_customer->username = (char*)malloc(30*sizeof(char));
    new_customer->mail = (char*)malloc(30*sizeof(char));
    new_customer->password = (char*)malloc(30*sizeof(char));
    new_customer->iban = (char*)malloc(30*sizeof(char));
    return new_customer;

}

char random_iban(struct Customer *customer){
    int number;
	char string_of_number[8],iban[8]="fo";
    srand(time(0));
    number = rand()%1000000;
    sprintf(string_of_number, "%d", number);
    strcat(iban,string_of_number);
    return iban;
}

void store_customer(struct Customer *customer){
    FILE *store;
    store = fopen("customers.txt","a");
    fprintf(store,"\n%s , ",customer->username);
    fprintf(store,"%s , ",customer->name);
    fprintf(store,"%s , ",customer->surname);
    fprintf(store,"%s , ",customer->mail);
    fprintf(store,"%s , ",customer->password);
    fprintf(store,"%s \n",customer->iban);
    fclose(store);
}

void run_login_screen(){
    cls;
    printf("***Log In Screen***");
    }

bool check_nick(char nickname[]){
    char nick[30];
    int i=0;
    FILE *checkNick;
    if((checkNick = fopen("customers.txt","r"))!=NULL){
        while (!feof(checkNick))
        {
            fscanf(checkNick,"%s",&nick);
            if(nick==nickname)return 0;
        }
        return 1;
    }
    else printf("File is empty.");
    return 0;

    fclose(checkNick);

}

void run_signup_screen(){
    cls;
    struct Customer *customer = create_customer();
    printf("Please enter your name.\n");
    scanf("%s",customer->name);
    printf("Please enter your surname.\n");
    scanf("%s",customer->surname);
    re_election:
    printf("Please enter your username.\n");
    scanf("%s",customer->username);

    if (check_nick(customer->username)==0){
        printf("You can't use this username.\nPlease pick new one.");
        goto re_election;
    }

    printf("Please enter your mail address.\n");
    scanf("%s",customer->mail);
    printf("Please enter your password.\n");
    scanf("%s",customer->password);
    customer->iban = random_iban(customer);
    printf("Your special number is :%s \n",customer->iban);
    printf("Customer account has been successfully created.");
    store_customer(customer);
}


void run_initial_screen(){
    bool invalid_input = false;
    check:
    cls;
    if(invalid_input){
        printf("1 - Login\n2 - Signup\n\nPlease enter a valid choice.\nChoose one: ");
    }else{
        printf("1 - Login\n2 - Signup\n\nChoose one: ");
    }
    int res; 
    scanf("%d",&res);
    switch (res)
    {
    case 1:
        run_login_screen();
        break;
    case 2:
        run_signup_screen();
        break;
    default:
        invalid_input = true;
        goto check;
        break;
    }
}


int main(){
    run_initial_screen();
    return 0;
}

