#include <stdio.h>//regex finished, A-Z、a-z、0-9、∼、@、#、_、^、*、%、/、.、+、:、= pending
#include <stdlib.h>
#include <string.h>

int merchandise[1000];
int buyerMode();
int sellerMode();
int main(){
    char mode;
    while(1){
        printf("(1)Seller Mode/ (2) Buyer Mode\nenter:");
        //scanf(" %c",&mode);
        mode=49;
        if(mode==49){
            sellerMode();
        }
        else if(mode==50){
            buyerMode();
        }
        else{
            printf("Wrong input!\nPlease input 1, 2, or 3.\n");
        }
    }
    printf("process end");
}

int sellerMode(){
    char cmd[1000],*token,arg[4][1000];
    int quotationFlag,argCounter,j;

    while(1){
        fflush(stdin);
        printf("seller mode>");
        fgets(cmd,1000,stdin);
        quotationFlag=0;
        argCounter=0;
        j=0;//index of each arg[argCount][]
        for(int i=0;i<4;i++){
            strcpy(arg[i],"-1");
        }
        /*ptr=strpbrk(cmd,"\"");
        while(ptr){
            quotationCounter++;
            ptr=strpbrk(ptr+1,"\"");
        }
        //printf("quotationCounter = %d\n",quotationCounter);

        if(0){
            token=strtok(cmd," ");
            while(token){
                if(argCounter==4){
                    strcpy(arg[0],"-1");//result in warning.
                    printf("too many arguments\n");
                    break;
                }
                strcpy(arg[argCounter],token);
                argCounter++;
                token=strtok(NULL," ");
                //printf("%d %s\n",argCounter,token);
            }
        }*/
        for(int i=0;i<strlen(cmd);i++){
            if(argCounter==4){
                strcpy(arg[0],"-1");//result in warning.
                printf("too many arguments\n");
                break;
            }
            if(i==strlen(cmd)-1){
                if(j!=0){
                    arg[argCounter][j]='\0';
                }
                j++;
                printf("argCounter = %d\n",argCounter);
                break;
            }
            if(cmd[i]=='"'){
                if(quotationFlag){
                    arg[argCounter][j]='\0';
                    argCounter++;
                    j=0;
                }
                quotationFlag=(!quotationFlag);
                if(i==strlen(cmd)-2){
                    break;
                } 
            }   
            else if(cmd[i]==' '){
                if(quotationFlag){
                    arg[argCounter][j]=' ';
                    j++;
                }
                else if(j!=0){
                    arg[argCounter][j]='\0';
                    j=0;
                    argCounter++;
                }
            }
            else if(1){//A-Z、a-z、0-9、∼、@、#、_、^、*、%、/、.、+、:、=
                arg[argCounter][j]=cmd[i];
                j++;
            }
            else{
                strcpy(arg[0],"-1");//result in warning.
                printf("character forbidden\n");
                break;
            }
        }
        argCounter--;       
        /*char tempString[1000];
        strcpy(tempString,strtok(arg[argCounter-1],"\n"));
        strcpy(arg[argCounter-1],tempString);*/
        //printf("args[]\n");
        for(int i=0;i<4;i++){
            if(strcmp(arg[i],"-1")!=0){
                printf("%s\n",arg[i]);
            }
            
        }
        for(int i=0;i<10;i++){
            printf("-");
        }
        printf("\n");
    }



    /*
        if(strncmp(cmd,"?",strlen(cmd)-1)==0){
            printf("\ncmds: description\n?: Show the man page of current mode.\nadd <product> <num>: add <product> with <num> quantities.\nbuyer mode: enter buyer mode. \ndelete <product>: delete <product> merchandise.\nexit: exit the script. \nincome: print current total income.\nlist [inc|dec] [name|price|quantity]: show the list of merchandises, including goods name, price, and inventory. \nnew <product> <price> [<num>]: add item <product_name> with price <price> and number <num>. if <quantity> is skipped, the number is set 0 by default. \npasswd: change the password if original password given is correct.\n\n");
        }
        else if(strncmp(cmd,"add",3)==0){///////////////////
            printf("enter add command\n");        

        }
        else if(strncmp(cmd,"buyer mode",strlen(cmd)-1)==0){

        }
        else if(strncmp(cmd,"delete",6)==0){
        }
        else if(strncmp(cmd,"exit",strlen(cmd)-1)==0){
            
        }
        else if(strncmp(cmd,"help",strlen(cmd)-1)==0){
            
        }
        else if(strncmp(cmd,"income",strlen(cmd)-1)==0){
            
        }
        else if(strncmp(cmd,"list",4)==0){
            //cmdCheck(cmd,0);
        }
        else if(strncmp(cmd,"new",3)==0){
            //cmdCheck(cmd,0);
        }
        else if(strncmp(cmd,"passwd",strlen(cmd)-1)==0){
            
        }
        else{
            printf("Wrong input!\n");
        }
    }    
    */


    return 0;
}

int buyerMode(){
    return 0;
}