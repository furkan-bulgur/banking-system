#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define cls printf("\n");//printf("\e[1;1H\e[2J");

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

int check_information(char information[], int check){
    //1-nickname 2-mail 3-iban
    FILE *checkInf;
    char inf[30];
    if((checkInf = fopen("customers.txt","r"))!=NULL){
        while (!feof(checkInf))
        {   
            switch(check){
                case 1: //nickname check
                fscanf(checkInf,"%s%*s%*s%*s%*s%*s%*s%*s%*s%*s%*s\n",inf);
                if(strcmp(inf,information)== 0)return 0;break;
                case 2: //mail check
                fscanf(checkInf,"%*s%*s%*s%*s%*s%*s%s%*s%*s%*s%*s",inf);
                if(strcmp(inf,information)== 0)return 0;break;
                case 3: //iban check
                fscanf(checkInf,"%*s%*s%*s%*s%*s%*s%*s%*s%*s%*s%s",inf);
                if(strcmp(inf,information)== 0)return 0;break;
            }
        }
        return 1;
    }
    fclose(checkInf);
}

void random_iban(struct Customer *customer, char iban[]){
    re_iban:
    int number;
    srand(time(0));
    number = rand()%1000000;
    sprintf(iban, "fo%d", number);
    if (check_information(iban,3)==0){
        goto re_iban;
    }

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

int check_login_info(char username[],char password[]){
    FILE *checkInf;
    int size=210,count=0;
    char inf[size],piece[size];
    if((checkInf = fopen("customers.txt","r"))!=NULL){
        while (!feof(checkInf)){
            while (fgets(inf,size,checkInf))
            {
                char *piece_;
                piece_=strtok(inf,"");
                if(strlen(piece_)!=1){
                    piece[count]=*piece_;
                    printf("count: %d\npiece: %sarray: %s\n\n",count,piece_,piece);
                    count++;
                }
            }
        }
    }
    //printf("username: %s \n password: ",piece);
    fclose(checkInf);
}

void run_login_screen(){
    cls;
    char username[30],password[30];
    printf("***Log In Screen***\n");
    printf("Username: \n");scanf("%s",&username);
    printf("Password: \n");scanf("%s",&password);
    check_login_info(username,password);
    }

void run_signup_screen(){
    cls;
    char iban_[8];
    struct Customer *customer = create_customer();

    printf("\nPlease enter your name:  ");
    scanf("%s",customer->name);

    printf("\nPlease enter your surname:  ");
    scanf("%s",customer->surname);

    re_username:
    printf("\nPlease enter your username:  ");
    scanf("%s",customer->username);

    if (check_information(customer->username,1)==0){
        printf("You can't use this username [%s].\nPlease pick new one.",customer->username);
        goto re_username;
    }

    re_mail:
    printf("\nPlease enter your mail address:  ");
    scanf("%s",customer->mail);

    if (check_information(customer->mail,2)==0){
        printf("You can't use this mail [%s].\nPlease pick new one.",customer->mail);
        goto re_mail;
    }

    printf("\nPlease enter your password:  ");
    scanf("%s",customer->password);

    random_iban(customer,iban_);
    customer->iban = iban_;
    printf("\nYour special number is:  %s \n",iban_);

    printf("\nCustomer account has been successfully created.\n\n*** WELCOME %s ***",customer->name);
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

