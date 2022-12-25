#include <stdio.h>
#include <string.h>

FILE *iniFptr,*objFptr,*bgFptr,*mskFptr,*outputFptr;
struct {
    unsigned size;
    char reserved[4];
    unsigned offsetBits;
    unsigned infoSize;
    unsigned width;
    unsigned height;
    short unsigned planes;
    short unsigned bitPerPixel;
    unsigned compression;
    unsigned imageSize;
    unsigned XResolution;
    unsigned YResolution;
    unsigned colors;
    unsigned importantColors;   
}bmpinfo;
int fc(void);
void deleteEnter(char*);
int main(){
    char buffer[1000],*token;
    unsigned spec[3][4];
    int index;
    iniFptr=fopen("setting2.ini","rb");
    while(fgets(buffer,1000,iniFptr)!=NULL){
        token=strtok(buffer," ;");
        deleteEnter(token);      
        if(strstr(token,"OUTPUT")){
            token=strtok(buffer,"=");
            token=strtok(NULL,"=");
            printf("%s\n",token);
            outputFptr=fopen(token,"wb");
            if(outputFptr==NULL){
                printf("output file path error\n");
                return -1;
            }
        }
        else if(strstr(token,"OBJ")){
            token=strtok(buffer,"=");
            token=strtok(NULL,"=");
            printf("%s: ",token);
            objFptr=fopen(token,"rb");
            if(objFptr==NULL){
                printf("object file path error\n");
                return -1;
            }
            fseek(objFptr,2,0);
            fread(&bmpinfo,1,52,objFptr);
            printf("%d/ %d/ %d/ %d\n",bmpinfo.width,bmpinfo.height,bmpinfo.XResolution,bmpinfo.YResolution);
            spec[0][0]=bmpinfo.width;
            spec[0][1]=bmpinfo.height;
            spec[0][2]=bmpinfo.XResolution;
            spec[0][3]=bmpinfo.YResolution;
        } 
        else if(strstr(token,"MSK")){
            token=strtok(buffer,"=");
            token=strtok(NULL,"=");
            printf("%s: ",token);
            mskFptr=fopen(token,"rb");
            if(mskFptr==NULL){
                printf("mask file path error\n");
                return -1;
            }  
            fseek(mskFptr,2,0);
            fread(&bmpinfo,1,52,mskFptr);
            printf("%d/ %d/ %d/ %d\n",bmpinfo.width,bmpinfo.height,bmpinfo.XResolution,bmpinfo.YResolution);
            spec[1][0]=bmpinfo.width;
            spec[1][1]=bmpinfo.height;
            spec[1][2]=bmpinfo.XResolution;
            spec[1][3]=bmpinfo.YResolution;                      
          
        }   
        else if(strstr(token,"BG")){
            token=strtok(buffer,"=");
            token=strtok(NULL,"=");
            printf("%s: ",token);
            bgFptr=fopen(token,"rb");
            if(bgFptr==NULL){
                printf("background file path error\n");
                return -1;
            }
            fseek(bgFptr,2,0);
            fread(&bmpinfo,1,52,bgFptr);
            printf("%d/ %d/ %d/ %d\n",bmpinfo.width,bmpinfo.height,bmpinfo.XResolution,bmpinfo.YResolution);
            spec[2][0]=bmpinfo.width;
            spec[2][1]=bmpinfo.height;
            spec[2][2]=bmpinfo.XResolution;
            spec[2][3]=bmpinfo.YResolution;
        }
    }
    if(spec[0][0]!=spec[1][0]||spec[0][1]!=spec[1][1]){
        printf("The size of object and mask aren't same.\n");
        return -1;
    }
    if(spec[0][0]!=spec[2][0]||spec[0][1]!=spec[2][1]){
        printf("The size of object and background aren't same.\n");
        return -1;        
    }
    rewind(objFptr);
    for(int i=0;i<54;i++){
        fputc(fgetc(objFptr),outputFptr);
    }
    index=0;
    for(int i=0;i<spec[0][1];i++){
        for(int j=0;j<spec[0][0]||index%4!=0;j++){
            for(int k=0;k<3;k++){
                if(j>=spec[0][0]){
                    fputc(0,outputFptr);
                    fgetc(bgFptr);
                    fgetc(objFptr);
                    fgetc(mskFptr);
                    printf("padding\n");
                }
                else{
                    fputc(fc(),outputFptr);
                }
            }

        }
    }


    fclose(objFptr);
    fclose(bgFptr);
    fclose(iniFptr);
    fclose(outputFptr);
    fclose(mskFptr);
}

void deleteEnter(char* token){
    if(token[strlen(token)-1]=='\n'){
        token[strlen(token)-1]='\0';
    }
}

int fc(void){
    int o=fgetc(objFptr),b=fgetc(bgFptr),m=fgetc(mskFptr);
    return b*m/255+o*(255-m)/255;
}