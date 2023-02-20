#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct items{
    char item[20];
    float price;
    int qty;
};

struct orders{
    char customer[50];
    char date[50];
    int numofitems;
    struct items itm[50];
};

void generatebillheader(char name[50],char date[30]){
    printf("\n\n");
    printf("\t ADV. restaurant");
    printf("\n\t ---------------");
    printf("\ndate:%s",date);
    printf("\ninvoice to: %s",name);
    printf("\n");
    printf("---------------------------\n");
    printf("items\t\t");
    printf("qty\t\t");
    printf("total\t\t");
    printf("\n--------------------------------");
    printf("\n\n");

}
void generatebillbody(char item[30],int qty,float price){
    printf("%s\t\t",item);
       printf("%d\t\t",qty);
       printf("%.2f\t\t",qty* price);
       printf("\n");
}


void generatebillfooter(float total){
    printf("\n");
    float dis=0.1*total;
    float nettotal=total-dis;
    float cgst=0.09*nettotal,grandtotal=nettotal + 2*cgst;
    printf("----------------------------------------\n");
    printf("sub total\t\t\t%.2f",total);
    printf("\ndiscount @10%s\t\tt\t%.2f","%",dis);
    printf("\n\t\t\t\t------");
    printf("\nnet total\t\t\t%.2f",nettotal);
    printf("\ncgst @9%s\t\t\t%.2f","%",cgst);
    printf("\nsgst @9%s\t\t\t%.2f","%",cgst);
    printf("\n--------------------------------------");
    printf("\ngrand total\t\t\t%.2f",grandtotal);
    printf("\n-------------------------------------\n");


}
int main(){
    int opt,n,tot;
    struct orders ord;
    struct orders order;
    char savebill='y',contflag='y';
    char name[50];
    FILE *fp;
    while(contflag=='y'){
        system("clear");
        float total=0;
        int invoicefound = 0;
    
    printf("\t=============ADV.  RESTAURANT==================");
    printf("\n\n please select  your prefered operation");
    printf("\n\n1.generate invoice");
    printf("\n2.show all invoices");
    printf("\n3.search invoice");
    printf("\n4.exit");

    printf("\n\nyour choice:\t");
    scanf("%d",&opt);
    fgetc(stdin);
    
    switch(opt){
        case 1:
        system("clear");
        printf("\nplease enter the name of the customer:\t");
        fgets(ord.customer,50,stdin);
        ord.customer[strlen(ord.customer)-1]=0;
        strcpy(ord.date,__DATE__);
        printf("\nplease enter the number of items:\t");
        scanf("%d",&n);
        ord.numofitems = n;

        for(int i=0;i<n;i++){
             fgetc(stdin);
             printf("\n\n");
             printf("please enter the item %d:\t",i+1);
             fgets(ord.itm[1].item,20,stdin);
             ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
             printf("please enter the quantity:\t");
             scanf("%d",&ord.itm[i].qty);
             printf("please enter the unit  price:\t");
             scanf("%f",&ord.itm[i].price);
             total += ord.itm[i].qty * ord.itm[i].price;
        }
        generatebillheader(ord.customer,ord.date);
           for(int i=0;i<ord.numofitems;i++){
              generatebillbody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
           }
        generatebillfooter(total);

        printf("\ndo you want to save the invoice [y/n]:\t");
        scanf("%s",&savebill);

        if(savebill== 'y'){
            fp=fopen("restaurantbill.dat","a+");
            fwrite(&ord,sizeof(struct orders),1,fp);
            if(fwrite != 0)
            printf("\nsuccessful saved");
            else
            printf("\nerror saving");
            fclose(fp);
        }
        break;

        case 2:
        system("clear");
        fp=fopen("restaurantbill.dat","r");
        printf("\n *****your previous invoices*****\n");
        while(fread(&order,sizeof(struct orders),1,fp))
        
              generatebillheader(order.customer,order.date);
              for(int i=0;i<order.numofitems;i++){
                generatebillbody(order.itm[1].item,order.itm[1].qty,order.itm[1].price);
                tot += order.itm[i].qty * order.itm[i].price;
              }
              generatebillfooter(tot);
    
    fclose(fp);
    break;

    case 3:
    printf("\nenter the name of customer:\t");
    //fgetc(stdin);
    fgets(name,50,stdin);
    name[strlen(name)-1]=0;
    system("clear");
        fp=fopen("restaurantbill.dat","r");
        printf("\t *****invoice of %s*****",name);
        while(fread(&order,sizeof(struct orders),1,fp))
        if(!strcmp(order.customer,name)){
            generatebillheader(order.customer,order.date);
              for(int i=0;i<order.numofitems;i++){
                generatebillbody(order.itm[1].item,order.itm[1].qty,order.itm[1].price);
                tot += order.itm[i].qty * order.itm[i].price;

        }
              generatebillfooter(tot);
              invoicefound =1;
        }
    if(!invoicefound){
        printf("sorry the invoice for %s doesnot exists",name);
    }

    
    fclose(fp);
    break;

    case 4:
    printf("\n\t\t bye bye:)\n\n");
    exit(0);
    break;

    default:
    printf("sorry invalid option");
    break;
    }
    
    printf("\ndo you want to perform another operation?[y/n]:\t");
    scanf("%s",&contflag);
    

}
    printf("\n\t\t bye bye:)\n\n");
    printf("\n\n");

    return 0;
}
