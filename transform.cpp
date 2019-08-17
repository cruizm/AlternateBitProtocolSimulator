#include<string.h>
#include<stdio.h>

// structure to make a single object as we cant pass
// arrays as function arguments
struct merge_line{
    char line[1000];
};

// This structure is to read each line from a file fp
// input: File pointer
// output: the line that the file pointer is pointing.
struct merge_line readline(FILE *fp){

char ch;
int counter = 0;
char line[1000];
struct merge_line line2;

while( (ch = getc(fp))!=EOF && ch!='\n' ){
    line[counter++] = ch;
}

line[counter] = '\0';
strcpy(line2.line,line);
return line2;

}
// This function tells us the type of the line. 
// if line is Time, it returns True else False
int LineType(struct merge_line line){
    if (strlen(line.line) == 12
        && isdigit(line.line[0])
        && isdigit(line.line[1])
        && isdigit(line.line[3])
        && isdigit(line.line[4])
        && isdigit(line.line[6])
        && isdigit(line.line[7])
        && isdigit(line.line[9])
        && isdigit(line.line[10])
        && isdigit(line.line[11])
        && line.line[2]==':'
        && line.line[5]==':'
        && line.line[8]==':')
        return 1;
    else
        return 0;
}

// This function checks the characters if they are
// same or different. if same returns 1 else returns 0
int CheckingChar(char a, char b)
{
    if(a==b)
        return 1;
    else
        return 0;
}
				
void filter(FILE *input, FILE *output){
	
	fpos_t line_pos;
	fpos_t temp_pos;

struct merge_line l;
struct merge_line l2;
FILE *fp;
FILE *out;
fp=input;
out=output;
char ch;
char *str;
int counter = 0;

fprintf(out,"time,value,port,component\n");

char time[13];
char text1[20];
char text2[20];
char text3[20];
int flag;
l = readline(fp);

while(!feof(fp)){
		if (LineType(l)){
				strcpy(time,l.line);
				l = readline(fp);

		}
		else{
				int counter;
				for(counter = strlen(l.line)-1;l.line[counter]!=' ';counter--)
						continue;
				counter++;
				int i;
				for (i=0;counter!=strlen(l.line);i++)
						text3[i] = l.line[counter++];
				text3[i]='\0';


				int colon_counter = 0;
				for(int i = 0;i<strlen(l.line);i++){

				    if(CheckingChar(l.line[i],'[')|| CheckingChar(l.line[i],',')){
                        colon_counter=0;
                        while(l.line[i]!=':' && l.line[i]!=']' )
                            i++;
                        i--;
				    }
				    else if(CheckingChar(l.line[i],':')){
                        if (colon_counter==0 || colon_counter==1){
                            colon_counter++;
                            if (colon_counter==1)
                                i--;
                        }
                        else if(colon_counter==2){
                            colon_counter++;
                            i++;
                            counter = 0;
                            int j = 0;
                            while(l.line[i]!=':'){
                                text1[counter] = l.line[i];
                                counter++;
                                i++;
                            }
                            i--;
                            text1[counter]='\0';
                        }
                        else if (colon_counter==3){
                            while(l.line[i]!='{')
                                i++;
                            i--;
                            colon_counter=0;
                        }
                        else{}
				    }
				    else if(CheckingChar(l.line[i],'{'))
                    {
                        i++;
                        counter=0;
                        while(l.line[i]!='}')
                            text2[counter++] = l.line[i++];
                        text2[counter] = '\0';
                        i--;
                        if(text2[0]!='\0'&& text2[0]>9){
                            fprintf(out,"%s,%s,%s,%s\n",time,text2,text1,text3);
                        }
                    }
				    else if(CheckingChar(l.line[i],'}'))
                    {
                        while(l.line[i]!=']' && l.line[i]!=',')
                            i++;
                        i--;
                    }
				    else if(CheckingChar(l.line[i],']'))
                    {
                        l = readline(fp);
                        flag=1;
                    }
				    else
                    {
                        printf("%c",l.line[i]); //error if prints any other
                    }
                    if (flag==1){
                        flag=0;
                        break;
                    }

				}
		}
}

fclose(out);
}