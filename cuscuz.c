#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct card{
    int player;
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


card * list_insert (card * atual, int num, char suit, int player){
  printf("entrei no insert com %d%c no inserir %d%c\n", num, suit, atual->num, atual->suit);
  card *novo = (card *)malloc(sizeof(card) * 1);
  novo->num = num;
  novo->suit = suit;
  novo->player = player;
  printf("%d%c \n", novo->num, novo->suit);
  novo->next = atual->next;
  atual->next = novo;
  return atual;
}


card * enQueue(card * tail, int num, char suit, int player){
    printf("entrei no enQueue\n");
    tail = list_insert(tail, num, suit, player);
    return tail->next;
}

card * list_delete (card * atual, int * val, char * suit, int * player){
  card * temp = atual->next;
  atual->next = temp->next;
  printf("entrei no delete\n");
  *val = temp->num;
  *suit = temp->suit;
  *player = temp->player;
  printf("to tirando a carta: %d%c do player %d\n", *val, *suit, *player);
  free(temp);
  return atual;
}
card * DeQueue(card * head, card * tail, int * val, char * suit, int * player){
  printf("entrei no deQueue com o player %d\n", *player);
  head = list_delete(head, val, suit, player);
  if (head->next == NULL){
    tail = head;
  }
  printf("Voltei do delete\n");
  return head;
}

card * push(card * top, int num, char suit, int player){
  printf("entrei no PUSH com a carta %d%c do player %d\n", num, suit, player);
  return list_insert(top, num, suit, player);
}

card * pop(card * top, int * num, char * suit, int * player){
  printf("entrei no POP com a carta %d%c do player %d\n", *num, *suit, *player);
  return list_delete(top, num, suit, player);
}


/*
 * Varre a Linked List
 * No Caso de empate, retorna -1
 * No caso de exitir um vencedor retorna o indice dele
 *
 */
int buscaMaior(card * top, int * num_cards){    
    card * temp;
    temp = top;
    int maior = 0;
    char suit = 'A';
    int index;
    int num = 0;
    while (temp->next != NULL){
      num++;
      if(temp->num > maior){
        maior = temp->num;
        suit = temp->suit;
        index = temp->player;
      }else if (temp->num == maior){
          if(temp->suit > suit){
            maior = temp->num;
            suit = temp->suit;
            index = temp->player;
          } else if(temp->suit == suit){
            index = -1;
          }
      }
      temp = temp->next;
    }
    *num_cards = num;
    return index;   
}

void printListInOrder(card * head){
  card * temp = head->next;
  while (temp->next->next != NULL){
    printf("%d%c ->", temp->num, temp->suit);
    temp = temp->next;
  }
  printf("NULL\n");
}

int main(int argc, char const *argv[])
{

    int num_players;
    

    scanf("%d", &num_players);
    printf("peguei %d players\n", num_players);

    player * players;
    players = (player*)malloc(sizeof(player) * num_players);

    for (int i = 0; i < num_players; i++){
      card sent;
      players[i].num = i;
      players[i].head = &sent;
      //printf("dei pau no for dos players\n");
      players[i].tail = players[i].head;
    }


    char op[4];
    int num_rounds = -1;

    do{
      printf("entrei no do...While\n");
      //printListInOrder(players[0].head);
      card * deck;
      card sentinel;
      deck = &sentinel;     

      scanf(" %s", op);
      printf("peguei a op : %s\n", op);
      if(strcmp(op, "DEA") == 0){
          for(int i = 0; i < num_players; i++){
              int num;
              char suit;
              scanf(" %d%c", &num, &suit);
              printf("%d e %c e player %d\n", num, suit, i);
              players[i].tail = enQueue(players[i].tail, num, suit, i);
              //printListInOrder(players[i].head);
          }
      }else if (strcmp(op, "RND") == 0){
          num_rounds++;
          int vencedor = -1;
          int num_cards;
          while(vencedor < 0){
            for(int i = 0; i < num_players; i++){
                  int player = i;
                  card temp;
                  players[i].head->next = DeQueue(players[i].head, players[i].tail, &temp.num, &temp.suit, &player);
                  //printListInOrder(players[i].head);
                  deck->next = push(deck->next, temp.num, temp.suit, player);
            }
            vencedor = buscaMaior(deck->next, &num_cards);            
          }         
          card * poped;
          poped = deck->next;
          while(poped->next != NULL){
            players[vencedor].tail = enQueue(players[vencedor].tail, poped->num, poped->suit, vencedor);
            poped = poped->next;
          }
          //printListInOrder(players[0].head);
          printf("%d %d %d\n", num_rounds, vencedor, num_cards);
      }
      free(deck);
      
    } while(strcmp(op, "END") != 0);
    return 0;
    
}
