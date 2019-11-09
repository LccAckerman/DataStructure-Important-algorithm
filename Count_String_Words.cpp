#include <iostream>

int countStringWord(char *s){
    int k = 0;
    bool inWord = false;
    for (int i = 0; s[i] != '\0' ; ++i) {
        if ((s[i] == ' '||'\0') && inWord)
        {
            k++;
            inWord = false;
            continue;
        }
        if (s[i] != ' ' && (!inWord)){
            inWord = true;
        }
    }
    return k;
}
int main() {
    char * s = " i am lccackerman ";
    std::cout<<countStringWord(s);
    return 0;
}