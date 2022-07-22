#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct card{
    int num;
    char suit;
   struct card *next;
} card;

typedef struct {
    int num;
    int win;
    card * head;
    card * tail;
} player;


card * list_insert (card * atual, int num, char suit){
  printf("entrei no insert com %d%c no inserir %d%c", num, suit, atual->num, atual->suit);
  card *novo = (card *)malloc(sizeof(card) * 1);
  novo->num = num;
  novo->suit = suit;
  printf("%d%c \n", novo->num, novo->suit);
  novo->next = atual->next;
  atual->next = novo;
  return atual;
}


card * enQueue(card * tail, int num, char suit){
    printf("entrei no enQueue\n");
    tail = list_insert(tail, num, suit);
    return tail->next;
}

card * list_delete (card * atual, int * val, char * suit){
  printf("entrei no delete\n");
  card * temp = atual->next;
  atual->next = temp->next;
  *val = temp->num;
  *suit = temp->suit;
  free(temp);
  return atual;
}
card * DeQueue(card * head, card * tail, int * val, char * suit ){
  printf("entrei no deQueue\n");
  head = list_delete(head, val, suit);
  if (head->next == NULL){
    tail = head;
  }
  return head;
}

card * push(card * top, int * num, char * suit){
  return list_insert(top, num, suit);
}

card * pop(card * top, int * num, char * suit){
  return list_delete(top, num, suit);
}


int main(int argc, char const *argv[])
{

    int num_players;
    

    scanf("%d", &num_players);
    player * players = (player*)malloc(sizeof(player) * num_players);
    for (int i = 0; i < num_players; i++){
      card sent;
      players[i].num = i;
      players[i].head->next = &sent;
      players[i].tail = players[i].head;
    }


    char op[4];
    int num_rounds = -1;
    do{
      card * deck;
      card sentinel;
      deck = &sentinel;     
      scanf(" %s", op);
      if(strcmp(op, "DEA") == 0){
          for(int i = 0; i < num_players; i++){
              int num;
              char suit;
              scanf("%d%c", &num, &suit);
              players[i].tail = enQueue(players[i].tail, num, suit);
          }
      }else if (strcmp(op, "RND") == 0){
          num_rounds++;
          for(int i = 0; i < num_players; i++){
            
          }

      }
    } while(strcmp(op, "END") != 0);
    return 0;
    
}
