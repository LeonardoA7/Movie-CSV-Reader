/* Leonardo Alfaro
 * 9082565608
*/

/* This function takes a string as input and removes 
 * leading and trailing whitespace including spaces
 * tabs and newlines. It also removes multiple internal
 * spaces in a row. Arrays are passed by reference.
 */

#include <stdio.h>
#include <stdlib.h>
#include "student_functions.h"

int helper_length(char str[]) {
    int counter = 0;
    for(int i = 0; i < 100; i++) {
        if(str[i] == '\0') {
     	    break;
	}
        counter = counter + 1;
    }
    counter++;
    return counter;
}
void Clean_Whitespace(char str[]) {
   //Trailing White Space, VIA Mike's Pro Tips
   int length = helper_length(str);
   for (int i = (length - 1); i >= 0; i--) {
       if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\0') {
           str[i+1] = '\0';
           break;
       }
    }
    // Initial White Space
    int white_space = 0;
    length = helper_length(str);
    for (int i = 0; i < length; i++) {
        if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n') {
            white_space = white_space + 1;
        }else {
            break;
        }
    }
        length = helper_length(str);
        for (int i = white_space; i < length; i++) {
            str[i - white_space] = str[i];
        }
    // Internal Double Space
    length = helper_length(str);
    int double_whitespace = 0;
    for(int i = 0; i < length; i++) { 
        if(str[i] == ' ') {
            for(int j = i; j < length; j++) { 
               if (str[j] == ' ') {
                   double_whitespace = double_whitespace + 1;
               } else {
                   break;
               }
            }
            length = helper_length(str);
            double_whitespace--;
            if(double_whitespace >= 1) { 
	       for (int k = double_whitespace + i; k < length; k++) {        
		       str[k - double_whitespace] = str[k];
               }      
	    } 
	    double_whitespace = 0;
        }
    }  
	return;
}

/* This function takes a string and makes the first
 * letter of every word upper case and the rest of the
 * letters lower case
 */ 
void Fix_Case(char str[]) {
    // do your work here
    Clean_Whitespace(str);
    int length = helper_length(str);
    for (int i = length - 2; i >= 0; i--) {
        if (i != 0 && str[i-1] == ' ') {
            if (str[i] >= 'a' && 'z' >= str[i]) {
                str[i] = str[i] - 32;
            }
        }else if (i == 0) {
            if (str[i] >= 'a' && 'z' >= str[i]) {
                str[i] = str[i] - 32;            
            } 
	}else { 
            if (str[i] >= 65 && str[i] <= 90) { 
                str[i] = str[i] + 32;      
	    }  
       	}
    }
    return;
}

/* this function takes a string and returns the 
 * integer equivalent
 */
int String_To_Year(char str[]) {
    // do your work her
    
    return atoi(str);
}

void Director_Last_Name(char str[]) {
    // do your work here
        Clean_Whitespace(str);
	Fix_Case(str);
        int length = helper_length(str) - 2;
	int counter = 0;
       	    for (int i = length; i >= 0 ; i--) { 
                if (str[i] == ' ') {
	            break;
	        }
	        counter++;			
	    }
	    counter--;
	    char temp[counter];
	   for (int j = 0; j <= counter; j++) { 
	       temp[j] = str[length - (counter - j)];
	       if (j == counter) {
	           temp[j+1] = '\0';
	       }
	   }
	   length = helper_length(temp);
           for (int i = 0; i < length; i++) { 
	       str[i] = temp[i];
	   }
    return;
}


/* this function takes the a string and returns
 * the floating point equivalent
 */
float String_To_Rating(char str[]) {
    // do your work here
    return atof(str);
}


/* this function takes a string representing
 * the revenue of a movie and returns the decimal
 * equivlaent. The suffix M or m represents millions,
 * K or k represents thousands.
* example: "123M" -> 123000000 
*/
long long String_To_Dollars(char str[])  {
    // do your work here
     long long dollars = 1;
     int length = helper_length(str);
     for (int i = 0; i < length; i++) { 
	     if(str[i] == 'm' || str[i] == 'M') {
		     str[i] = '\0';
		     dollars = dollars * 1000000;
		     break;
	     } else if (str[i] == 'k' || str[i] == 'K') { 
		     str[i] = '\0';
		     dollars = dollars * 1000;
		     break;
	     }
     }
     dollars = atoll(str) * dollars;
     return dollars;
}


/* This function takes the array of strings representing 
 * the csv movie data and divides it into the individual
 * components for each movie.
 * Use the above helper functions.
 */
void Split(char csv[10][1024], int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
    // do your work her
    int count = 0;
    for (int i = 0; i < num_movies; i++) {
	// GETS THE NEXT STRING INPUT
	char str[1024];
	int w = 0;
        for (int j = 0; j < 1024; j++) {
       	    if (csv[i][j] == ',' || csv[i][j] == '\n') {
	        str[w] = '\0';
		Clean_Whitespace(str);
		if (count == 0) {
		    Fix_Case(str);
	            for (int z = 0; z < 1024; z++) {
		        titles[i][z] = str[z];  
		    }
		}
		if (count == 1) {
	            years[i] = String_To_Year(str);
		}
		if (count == 2) {
		    // DO NOTHING
		}	
		if (count == 3) {
		    Fix_Case(str);
		    Director_Last_Name(str);
	            for (int x = 0; x < 1024; x++) {
		        directors[i][x] = str[x];      
		    }
		}
		if (count == 4) {
	            ratings[i] = String_To_Rating(str);      
		}
		if (count == 5) {
	            dollars[i] = String_To_Dollars(str);
		}
		count++;
		str[0] = '\0';
		w = 0;
	    }else {
	        str[w] = csv[i][j];
		w++;
	    }
	}
        count = 0;	
    }
    return;
}

/* This function prints a well formatted table of
 * the movie data 
 * Row 1: Header - use name and field width as below
 * Column 1: Id, field width = 3, left justified
 * Column 2: Title, field width = lenth of longest movie + 2 or 7 which ever is larger, left justified, first letter of each word upper case, remaining letters lower case, one space between words
 * Column 3: Year, field with = 6, left justified
 * Column 4: Director, field width = length of longest director last name + 2 or 10 (which ever is longer), left justified, only last name, first letter upper case, remaining letters lower case
 * column 5: Rating, field width = 6, precision 1 decimal place (e.g. 8.9, or 10.0), right justified
 * column 6: Revenue, field width = 11, right justified
 */
void Print_Table(int num_movies, char titles[10][1024], int years[10], char directors[10][1024], float ratings[10], long long dollars[10]) {
    // do your work herei
    int maxTitleLength = 0;
    int length = 0; 
    for (int i = 0; i < num_movies; i++) {
        for (int j = 0; j < 1024; j++) {
            if (titles[i][j] == '\0') {
	        break;
	    }
	    length++;
	} 
        if (length > maxTitleLength) {
            maxTitleLength = length;
	}
	length = 0;	
    }
    maxTitleLength = maxTitleLength + 2;
    if (maxTitleLength < 7) {
        maxTitleLength = 7;
    }
    int maxDirectorLength = 0;
    length = 0;
    for (int i = 0; i < num_movies; i++) {
        for (int j = 0; j < 1024; j++) {
	    if (directors[i][j] == '\0') {
                break;
	    }
	    length++;
	}
	if (length > maxDirectorLength) {
            maxDirectorLength = length;
	}
	length = 0;
    }
    maxDirectorLength = maxDirectorLength + 2;
    if (maxDirectorLength < 10) {
            maxDirectorLength = 10;
     }	    

    char id[] = "Id";
    char titleId[] = "Title";
    char yearId[] = "Year";
    char ratingId[] = "Rating";
    char directorId[] = "Director";
    char revenueId[] = "Revenue";

    printf("%-3s", id);
    printf("%-*s", maxTitleLength, titleId);
    printf("%-6s", yearId);
    printf("%-*s", maxDirectorLength ,directorId);
    printf("%6s", ratingId);
    printf("%11s", revenueId);
    printf("\n");    
    int counter = 0;
    for (int i = 0; i < num_movies; i++) {
        if (counter == 0) {
	    int j = i + 1;
	    printf("%-3d", j);	
            printf("%-*s", maxTitleLength, titles[i]);
	    counter++;
	}
	if (counter == 1) { 
            printf("%-6d", years[i]);
	    counter++;
	}
	if (counter == 2) {
            printf("%-*s", maxDirectorLength, directors[i]);
	    counter++;
	}
	if (counter == 3) {
	    printf("%6.1f", ratings[i]);
            counter++;
	}
	if (counter == 4) {
	    printf("%11.1lld\n", dollars[i]);
            counter = 0;
	}
    }
 
    return;
}


