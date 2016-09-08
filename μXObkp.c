#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void p(long);char f(long);int main(){long b=0;srand(time(NULL));if(rand()&1){b|=1<<19;}
printf("Welcome to μXO.\n");while(!f(b)){p(b);printf("It's %c's turn. Where would you like your symbol? (0-9) ",((b>>19)&1?'O':'X'));int i;scanf("%d",&i);b|=(1<<((b>>19&1)?i:i+9));b^=(1<<19);}
p(b);printf("\n\n%c wins.",((b^(1<<19))>>19)&1?'O':'X');return 0;}
char f(long b){char r=0;for(int i=0;i<=3;++i){r|=((b&0x7<<(i*3))==0x7<<(i*3));r|=((b&0x7<<(i*3+9))==0x7<<(i*3+9));r|=((b&0x49<<i)==0x49<<i);r|=((b&0x49<<(i+9))==0x49<<(i+9));}r|=((b&0x54)==0x54);r|=((b&0x54<<9)==0x54<<9);r|=((b&0x111)==0x111);
return r|=((b&0x111<<9)==0x111<<9);}
void p(long b){for(int i=0;i<9;++i){if(i%3==0){printf("\n");}
if((b>>i)&1){printf("O ");}else if((b>>(i+9))&1){printf("X ");}else{printf("  ");}}}