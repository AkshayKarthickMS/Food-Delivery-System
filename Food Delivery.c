#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#define ENTER 13
#define BCKSPC 8
void header(char*);
void login(void);
void signup(void);
void anna(char*);
void bill(float);
void body(char*,int,float);
void takepassword(char*);
void yourorder(char*);
//To read user details
struct user{
	char fullName[50];
	char email[50];
	char password[50];
	char username[50];
	char phone[50];
	char address[50];
};
//To read hotel menu
struct hotel{
    int no;
    char name[20];
    int price;
};
//To store menu
struct items{
    char name[20];
    float price;
    int qty;
};
//To display order
struct orders{
    char date[50];
    int numOfItems;
    struct items itm[50];
};
//Interface
void main()
{
    system("color 0b");
    int k;
    printf("\n\t\t\t\t----------Welcome to rDNA Restaurant----------\n\n");
	printf("\nPlease choose your operation");
	printf("\n1.Signup");
	printf("\n2.Login");
	printf("\n3.Exit");
	printf("\n\nYour choice:\t");
    scanf("%d",&k);
    if(k==1){
        signup();}
    else if(k==2){
        login();
    }
    else{
        printf("Thank You :)");
        exit(1);
    }
}
//Signup
void signup(void)
{
    sign:
    system("cls");
    char filename[20];
    char cpass[50];
    system("cls");
    printf("\n\t\t\t\t----------SIGNUP----------\n\n");
    FILE *su;
    int i,found=0;
    su=fopen("login.txt","a");
    struct user a;
    printf("\nEnter your Full Name:");
    fflush(stdin);
    gets(a.fullName);
    printf("Enter email Id:");
    fflush(stdin);
    scanf("%s",a.email);
    for(i=0;i<strlen(a.email);i++){         //Checking whether it contains @
        if(a.email[i]=='@'){
            found=1;
        }
    }
    if(!found){
        printf("Invalid email. Please use @");
        printf("\n\nPress any key to signup again...");
        getch();
        goto sign;
    }
    for(i=0;i<strlen(a.email);i++){
        if(a.email[i]=='@'){
            break;
        }
        else{
            a.username[i]=a.email[i];           //assigning username
        }
    }
    printf("Enter your mobile number:");
    fflush(stdin);
    scanf("%s",a.phone);
    printf("Enter your home address:");
    fflush(stdin);
    gets(a.address);
    printf("Enter password:");
    fflush(stdin);
    takepassword(a.password);
    printf("\nConfirm password:");
    fflush(stdin);
    takepassword(cpass);
    if(strcmp(a.password,cpass)!=0){
        printf("\n\nPassword Incorrect");
        printf("\n\nPress any key to signup again...");
        getch();
        goto sign;
    }
    system("cls");
    printf("\n\nRegistered successfully");
    strcpy(filename,a.username);
    fwrite(&a,sizeof(struct user),1,su);            //storing in a file
    if((fwrite)!=0){
        printf("\n\nYour Username is: %s\n\nUse this Username to login :)",a.username);
        fclose(su);
        printf("\n\nPress any key to go to login page");
        getch();
        login();}

    else{
    fclose(su);
}
return;}

//Login
void login(void)
{
    system("cls");
    printf("\n\t\t\t\t----------LOGIN----------\n\n");
    char username[50],password[50];
    FILE *log;
    log=fopen("login.txt","r");
    struct user a;
    printf("User name:");
    scanf("%s",&username);
    printf("Password:");
    takepassword(password);
    while(fread(&a,sizeof(struct user),1,log)){
        if(strcmp(username,a.username)==0 && strcmp(password,a.password)==0)        //searching for the user in file
        {
            hotels(&a.username);
        }
        else{
            printf("User doesnt exist");
        }
    }
    fclose(log);
    return;
}
//Hiding password
void takepassword(char pwd[50]){
	int i;
	char ch;
	while(1){
		ch = getch();
		if(ch == ENTER){
			pwd[i] = '\0';
			break;
		}else if(ch == BCKSPC){
			if(i>0){
				i--;
				printf("\b \b");
			}
		}else{
			pwd[i++] = ch;
			printf("* \b");
		}
	}
}
//Hotels
void hotels(char* filename)
{
    char ch='y';
    while(ch=='y'){
    system("cls");
    char file[20];
    strcpy(file,filename);
    printf("\n\t\t\t\t----------Hotels Available----------\n\n");
    printf("0.Profile\n\n1.Hotel Hari Bhavan\n2.Hotel Aaryas\n3.SS Hyderabad Biriyani\n4.Street Arabia\n5.Hotel Sri Annapoorna\n\n\n6.EXIT\n\n");
    int k;
    scanf("%d",&k);
    switch(k){
    case 0:
        system("cls");
        profile(&file);
        break;
    case 1:
        system("cls");
        hari(&file);
        break;
    case 2:
        system("cls");
        aaryas(&file);
        break;
    case 3:
        system("cls");
        ssbiri(&file);
        break;
    case 4:
        system("cls");
        arabia(&file);
        break;
    case 5:
        system("cls");
        anna(&file);
        break;
    case 6:
        return;
    }
    printf("\nPress ENTER to go to mainmenu\t");
    fflush(stdin);
    scanf("%c",&ch);}
}
void profile(char* filename){
    printf("\n\t\t\t\t----------PROFILE----------");
    struct user usr;
    char user[50];
    FILE *fp;
    fp = fopen("login.txt","r");
    while(fread(&usr,sizeof(struct user),1,fp)){
        if(strcmp(filename,usr.username)==0){               //searching for user details
        printf("\n\t\t\t\t\t\tWelcome %s",filename);
        strcpy(user,filename);
						printf("\n\n|Full Name:\t%s",usr.fullName);
						printf("\n|Email:\t\t%s",usr.email);
						printf("\n|Username:\t%s",usr.username);
						printf("\n|Contact no.:\t%s",usr.phone);
						printf("\n|Address:\t%s",usr.address);}
    }fclose(fp);
    int w;
    printf("\n\n1.Your Orders\n");
    scanf("%d",&w);
    if(w==1){
        yourorder(&user);
    }
    else{
        return;
    }
    return;
}
void yourorder(char* filename)
{
    system("cls");
    FILE *fp;
    struct orders c;
        fp = fopen(filename,"r");
        if(fp==NULL){
            printf("File not available");
        }
        printf("\n  **Your Previous Orders**\n");
        printf("%s",filename);
        while(fread(&c,sizeof(struct orders),1,fp)){
            float tot = 0.0;
            header(c.date);
            for(int i=0;i<=c.numOfItems;i++){
                body(&c.itm[i].name,c.itm[i].qty,c.itm[i].price);
                tot+=c.itm[i].qty * c.itm[i].price;
            }
            bill(tot);
        }
        fclose(fp);
        printf("Press any key to go to mainmenu");
        getch();
        return;
}
void anna(char* filename)
{
    printf("\n\t\t\t\t----------Welcome to Annapoorna----------\n\n");
    int i=0,j=0,k=0,z=0,u=0;
    float sum=0.0,gst=0.0;
    char v[20];
    FILE *gp;
    struct hotel a[5];
    struct orders ord;
    gp=fopen("Annapoorna.txt","r");
    if(gp==NULL){
        printf("Error");
        exit(1);
    }
    fread(&a,sizeof(struct hotel),5,gp);
    for(i=0;i<5;i++){
    printf("%d\t",a[i].no);
        printf("%s\t\t",a[i].name);
        printf("%d\n",a[i].price);}
    int qty=0;
    one:
    printf("\nEnter your choice:");
    scanf("%d",&k);
    printf("Quantity:");
    scanf("%d",&j);
    strcpy(ord.itm[qty].name,a[k-1].name);
    ord.itm[qty].qty=j;
    ord.itm[qty].price=a[k-1].price;
    sum=sum+(a[k-1].price)*j;
    printf("Enter your choice:\n1.Add more items\n2.Order\n\n");
    scanf("%d",&z);
    if(z==1){
        qty++;
        goto one;
    }
    else if(z==2){
        system("cls");
        time_t date;
        time(&date);
        strcpy(ord.date,ctime(&date));
        ord.numOfItems=qty;
        header(ord.date);
    for(i=0;i<=qty;i++){
        body(&ord.itm[i].name,ord.itm[i].qty,ord.itm[i].price);
    }
        bill(sum);
    fclose(gp);
    FILE *fp;
    fp = fopen(filename,"a+");
            fwrite(&ord,sizeof(struct orders),1,fp);
            if(fwrite != 0)
            printf("\n\nPress any key to go to main menu:\n");
            else
            printf("\nError saving");
            fclose(fp);
    getch();
    return filename;
    }
}
void bill(float total){
    float dis = 0.1*total;
    float netTotal=total-dis;
    float cgst=0.09*netTotal,grandTotal=total + 2*cgst;
    printf("---------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nDelivery Charge\t\t\t%.2f",dis);
    printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n---------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n---------------------------------------\n");
    return;
}
void header(char* t){
    printf("\n\n");

        printf("\t    rDNA Restaurant");
        printf("\n\t   -----------------");
        printf("\nDate:%s",t);
        printf("\n");
        printf("---------------------------------------\n");
        printf("Items\t\t");
        printf("Qty\t\t");
        printf("Total\t\t");
        printf("\n---------------------------------------");
        printf("\n\n");
return;
}
void body(char* item,int qty,float price){
    printf("%s\t\t",item);
        printf("%d\t\t",qty);
        printf("%.2f\t\t",qty * price);
        printf("\n");
return;
}
#include "hari.txt"
#include "ss.txt"
#include "aar.txt"
#include "arabia.txt"
