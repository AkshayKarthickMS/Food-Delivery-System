void hari(char* filename)
{
    printf("%s",filename);
    printf("\n\t\t\t\t----------Welcome to Haribhavan----------\n\n");
    int i=0,j=0,k=0,z=0,u=0;
    float sum=0.0,gst=0.0;
    char v[20];
    FILE *gp;
    struct hotel a[5];
    struct orders ord;
    gp=fopen("Haribhavan.txt","r");
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
            printf("\nSuccessfully saved");
            else
            printf("\nError saving");
            fclose(fp);
    printf("\n%s",filename);
    printf("\n\nPress any key to go to main menu:\n");
    getch();
    return filename;
    }
}
