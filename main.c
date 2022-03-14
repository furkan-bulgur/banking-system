#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include<time.h>

#define cls printf("\e[1;1H\e[2J");

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
    new_customer->iban = (int*)malloc(30*sizeof(int));
    return new_customer;

}

/*bool store_customer(struct Customer *customer){}*/

void store_customer(struct Customer *customer){
    FILE *store;
    store = fopen("customers.txt","a");
    fprintf(store,"\n%s , ",customer->name);
    fprintf(store,"%s , ",customer->surname);
    fprintf(store,"%s , ",customer->username);
    fprintf(store,"%s , ",customer->mail);
    fprintf(store,"%s , ",customer->password);
    fprintf(store,"fo%d \n",customer->iban);
    fclose(store);
}

void run_login_screen(){
    cls;
    printf("Login screen.\n");
}

int random_iban(struct Customer *customer){
    int i, number;
    srand(time(NULL));
    for(i = 0 ; i < 6 ; i++)
    {
        number = rand()+ 1;
        return(number);
    }
}
void run_signup_screen(){
    cls;
    struct Customer *customer = create_customer();
    printf("Please enter your name.\n");
    scanf("%s",customer->name);
    printf("Please enter your surname.\n");
    scanf("%s",customer->surname);
    printf("Please enter your username.\n");
    scanf("%s",customer->username);
    printf("Please enter your mail address.\n");
    scanf("%s",customer->mail);
    printf("Please enter your password.\n");
    scanf("%s",customer->password);
    customer->iban = random_iban(customer);
    printf("Your special number is :fo%d \n",customer->iban);
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

