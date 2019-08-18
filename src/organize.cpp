/** \brief A filter function to format the output
* As input it takes the output files and
* formats the output for all the files
*/

#include<string.h>
#include<stdio.h>

// structure to make a single object as we cant pass
// arrays as function arguments
struct merge_line{
    char line[2000];
};

// This structure is to read each line from a file
// input: File pointer
// output: the line that the file pointer is pointing.
struct merge_line readline(FILE *fp){

char ch;
int count = 0;
char line[2000];
struct merge_line line2;

while( (ch = getc(fp))!=EOF && ch!='\n' ){
    line[count++] = ch;
}

line[count] = '\0';
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
int count = 0;

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
				int count;
				for(count = strlen(l.line)-1;l.line[count]!=' ';count--)
						continue;
				count++;
				int i;
				for (i=0;count!=strlen(l.line);i++)
						text3[i] = l.line[count++];
				text3[i]='\0';


				int colon_count = 0;
				for(int i = 0;i<strlen(l.line);i++){

				    if(CheckingChar(l.line[i],'[')|| CheckingChar(l.line[i],',')){
                        colon_count=0;
                        while(l.line[i]!=':' && l.line[i]!=']' )
                            i++;
                        i--;
				    }
				    else if(CheckingChar(l.line[i],':')){
                        if (colon_count==0 || colon_count==1){
                            colon_count++;
                            if (colon_count==1)
                                i--;
                        }
                        else if(colon_count==2){
                            colon_count++;
                            i++;
                            count = 0;
                            int j = 0;
                            while(l.line[i]!=':'){
                                text1[count] = l.line[i];
                                count++;
                                i++;
                            }
                            i--;
                            text1[count]='\0';
                        }
                        else if (colon_count==3){
                            while(l.line[i]!='{')
                                i++;
                            i--;
                            colon_count=0;
                        }
                        else{}
				    }
				    else if(CheckingChar(l.line[i],'{'))
                    {
                        i++;
                        count=0;
                        while(l.line[i]!='}')
                            text2[count++] = l.line[i++];
                        text2[count] = '\0';
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