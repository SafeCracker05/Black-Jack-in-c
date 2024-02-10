#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


struct croupier { 
    char  cardscroupier[5];
    char name_player[30]; 

}; 

struct player1 { 
    char  cardsplayer1[5];  // Utilisation d'un tableau pour stocker les cartes du joueur 1
    char name_player[30]; 

}; 

struct player2 { 
    char  cardsplayer2[5];  // Utilisation d'un tableau pour stocker les cartes du joueur 2
    char name_player[30]; 

}; 
struct player3 { 
    char  cardsplayer3[5];  // Utilisation d'un tableau pour stocker les cartes du joueur 2
    char name_player[30]; 
};

char pack_of_cards[52] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A',
                          '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A',
                          '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A',
                          '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};


// Déclaration des fonctions
int calculate_the_total_of_points(char cards[]);
void print_hand();
int determin_winner();
void hit_money_player1(struct player1 *var1);
void hit_money_player2(struct player2 *var3);
void hit_money_player3(struct player3 *var4);
void check_total_point(int n, char c[]);
char* shuffle();
void swap(char *a, char *b);
void show_the_table(struct croupier *var2, struct player1 *var1, struct player2 *var3, struct player3 *var4);
void show_table_hit();

int turn = 0;
int i = 1;
int flag1 = 0; //  joueur 1 dans le jeu (in)
int flag2 = 0; //  joueur 2 dans le jeu (in)
int flag3 = 0; //  joueur 3 dans le jeu (in)

int pasturn1 = 0;
int pasturn2 = 0;
int pasturn3 = 0;

int bet_player_1 = 0;
int bet_player_2 = 0;
int bet_player_3 = 0;

int money_player_1 = 5000;
int money_player_2 = 5000;
int money_player_3 = 5000;

int total_point_croupier;
int total_point_player1;
int total_point_player2;
int total_point_player3;

int bust_croupier = 0;

void initializeCroupier(struct croupier *var2) {
    if(turn == 0)
    {
        bust_croupier = 0;
        total_point_croupier = 0;
    }
    if (turn == 1) {
        var2->cardscroupier[0]  = pack_of_cards[0];
        var2->cardscroupier[1]  = '?';
        var2->cardscroupier[2]  = '?';
        var2->cardscroupier[3]  = '?';
        var2->cardscroupier[4]  = '?';
        // Vous pouvez définir name_croupier ici si nécessaire
    }
    // Après que les 3 joueurs ont fini leur hit
    else if (turn == 5) {
        int index = 2;  // Index pour ajouter des cartes à partir de la troisième position
        while (calculate_the_total_of_points(var2->cardscroupier) < 17 && index < sizeof(var2->cardscroupier)) {
            int i = 1;  // Commencez à partir de la deuxième carte du paquet
            for (; i < sizeof(var2->cardscroupier) / sizeof(var2->cardscroupier[0]); i++) {
                if (var2->cardscroupier[i] == '?') {
                    var2->cardscroupier[i] = pack_of_cards[index];
                    index++;

                    // Assurez-vous que var2->cardscroupier ne dépasse pas la taille de votre tableau
                    if (index >= sizeof(var2->cardscroupier)) {
                        break;
                    }

                    break;
                }
            }
        }
        total_point_croupier += calculate_the_total_of_points(var2->cardscroupier);
    }
}


// Fonction pour initialiser la structure player1
void initializePlayer1(struct player1 *var1) {
    if(turn == 0)
    {
        total_point_player1 = 0;
        pasturn1 = 0;
        flag1 = 0;
        bet_player_1 =  0;
    }
    if(turn == 1)
    {
    var1->cardsplayer1[0] = pack_of_cards[5];
    var1->cardsplayer1[1]  = '?';
    var1->cardsplayer1[2]  = '?';
    var1->cardsplayer1[3]  = '?';
    var1->cardsplayer1[4]  = '?';
    
    // Vous pouvez définir name_player ici si nécessaire
    }
    else if(turn == 2)
    {
    var1->cardsplayer1[1] = pack_of_cards[6];
    
    // Vous pouvez définir name_player ici si nécessaire
    }
}

// Fonction pour initialiser la structure player2
void initializePlayer2(struct player2 *var3) {
    if(turn == 0)
    {
        total_point_player2 = 0;
        pasturn2 = 0;
        flag2 = 0;
        bet_player_2 =  0;
    }
    if(turn == 1){
    var3->cardsplayer2[0] = pack_of_cards[2];
    var3->cardsplayer2[1]  = '?';
    var3->cardsplayer2[2]  = '?';
    var3->cardsplayer2[3]  = '?';
    var3->cardsplayer2[4]  = '?';


    
    // Vous pouvez définir name_player ici si nécessaire
    }
    else if(turn == 2){
    var3->cardsplayer2[1] = pack_of_cards[3];
    // Vous pouvez définir name_player ici si nécessaire
    }

}
// Fonction pour initialiser la structure player2
void initializePlayer3(struct player3 *var4) {
    if(turn == 0)
    {
        total_point_player3 = 0;
        pasturn3 = 0;
        flag3 = 0;
        bet_player_3 =  0;
    }
    if(turn == 1){
    var4->cardsplayer3[0] = pack_of_cards[14];
    var4->cardsplayer3[1]  = '?';
    var4->cardsplayer3[2]  = '?';
    var4->cardsplayer3[3]  = '?';
    var4->cardsplayer3[4]  = '?';

    // Vous pouvez définir name_player ici si nécessaire
    }
    else if(turn == 2){
    var4->cardsplayer3[1] = pack_of_cards[15];
    // Vous pouvez définir name_player ici si nécessaire
    }

}

// Fonction principale
int main(void) {
    struct croupier var2;
    struct player1 var1;
    struct player2 var3;
    struct player3 var4;

   do {
    if(turn == 0)
    {
        printf("\033[H\033[J");
        initializeCroupier(&var2);
        initializePlayer1(&var1); // Mettre à jour la main du joueur 1 après le mélange
        initializePlayer2(&var3); // Mettre à jour la main du joueur 2 après le mélange
        initializePlayer3(&var4); // Mettre à jour la main du joueur 3 après le mélange
        show_table_hit();
        printf("\nPress Enter to continue...");
        getchar(); // Consume the newline character
        getchar(); // Wait for Enter key
        turn++;
    }
    else if (turn == 1) // tour du croupier
    {
        printf("\033[H\033[J");
        shuffle();
        initializeCroupier(&var2);
        initializePlayer1(&var1); // Mettre à jour la main du joueur 1 après le mélange
        initializePlayer2(&var3); // Mettre à jour la main du joueur 2 après le mélange
        initializePlayer3(&var4); // Mettre à jour la main du joueur 3 après le mélange
        show_the_table(&var2, &var1, &var3, &var4); // mettre a jour les carte des joueur sur le table
        printf("\nPress Enter to continue...");
        getchar(); // Consume the newline character
        getchar(); // Wait for Enter key
        turn++;
    }
    else if (turn == 2)
    {
        printf("\033[H\033[J");
        shuffle();
        initializeCroupier(&var2);
        initializePlayer1(&var1); // Mettre à jour la main du joueur 1 après le mélange
        initializePlayer2(&var3); // Mettre à jour la main du joueur 2 après le mélange
        initializePlayer3(&var4); // Mettre à jour la main du joueur 3 après le mélange
        show_the_table(&var2, &var1, &var3, &var4);
        printf("\nPress Enter to continue...");
        getchar(); // Consume the newline character
        hit_money_player1(&var1);
        turn++;
    }
    else if (turn == 3)
    {
        printf("\033[H\033[J");
        shuffle();
        initializeCroupier(&var2);
        initializePlayer1(&var1); // Mettre à jour la main du joueur 1 après le mélange
        initializePlayer2(&var3); // Mettre à jour la main du joueur 2 après le mélange
        initializePlayer3(&var4); // Mettre à jour la main du joueur 3 après le mélange
        show_the_table(&var2, &var1, &var3, &var4);
        hit_money_player2(&var3);
        printf("\nPress Enter to continue...");
        getchar(); // Consume the newline character
        getchar(); // Wait for Enter key
        turn++;

    }
    else if (turn == 4)
    {
        printf("\033[H\033[J");
        shuffle();
        initializeCroupier(&var2);
        initializePlayer1(&var1); // Mettre à jour la main du joueur 1 après le mélange
        initializePlayer2(&var3); // Mettre à jour la main du joueur 2 après le mélange
        initializePlayer3(&var4); // Mettre à jour la main du joueur 3 après le mélange
        show_the_table(&var2, &var1, &var3, &var4);
        hit_money_player3(&var4);
        
        turn++;

    }
    else if (turn == 5)
    {
        printf("\033[H\033[J");
        shuffle();
        initializeCroupier(&var2);
        initializePlayer1(&var1); // Mettre à jour la main du joueur 1 après le mélange
        initializePlayer2(&var3); // Mettre à jour la main du joueur 2 après le mélange
        initializePlayer3(&var4); // Mettre à jour la main du joueur 3 après le mélange
        determin_winner();
        show_the_table(&var2, &var1, &var3, &var4);
        turn = 0;
        getchar(); // Consume the newline character
        getchar(); // Wait for Enter key
    }
    } while (1);


    return 0;
}

// Fonction pour échanger deux entiers
void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

// Fonction pour mélanger le paquet de cartes
char* shuffle() {
    int n = 52;

    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        // Choisissez un indice aléatoire de 0 à i
        int j = rand() % (i + 1);

        // Échangez arr[i] avec l'élément à l'indice aléatoire
        swap(&pack_of_cards[i], &pack_of_cards[j]);
    }
    return 0;
}

void show_the_table(struct croupier *var2, struct player1 *var1, struct player2 *var3, struct player3 *var4)
{
    printf("\t\t\t\t\t\t\t\t+-------------------------------------+\n");
    printf("\t\t\t\t\t\t\t\t|            BLACKJACK TABLE          |\n");
    printf("\t\t\t\t\t\t\t\t+-------------------------------------+\n\n\n\n\n\n");


    printf("\t\t\t\t\t\t\t\t+-------------------------------------+\n");
printf("\t\t\t\t\t\t\t\t|                                     |\n");
printf("\t\t\t\t\t\t\t\t|             DEALER AREA             |\n");
printf("\t\t\t\t\t\t\t\t|    [");

// Imprimer les cartes du croupier
for (int i = 0; i < sizeof(var2->cardscroupier) / sizeof(var2->cardscroupier[0]); i++) {
    printf("%c", var2->cardscroupier[i]);
    if (i < sizeof(var2->cardscroupier) / sizeof(var2->cardscroupier[0]) - 1) {
        printf(", ");
    }
}

printf("]                  |\n");
printf("\t\t\t\t\t\t\t\t|                                     |\n");
printf("\t\t\t\t\t\t\t\t+-------------------------------------+\n\n\n\n");

    printf("\t\t+-------------------------------------+\t\t\t\t\t\t\t\t+-------------------------------------+\n");
printf("\t\t|                                     |\t\t\t\t\t\t\t\t|                                     |\n");
printf("\t\t|               PLAYER 1              |\t\t\t\t\t\t\t\t|              PLAYER 3               |\n");
printf("\t\t|          [");

// Imprimer les cartes du joueur 1
for (int i = 0; i < sizeof(var1->cardsplayer1) / sizeof(var1->cardsplayer1[0]); i++) {
    printf("%c", var1->cardsplayer1[i]);
    if (i < sizeof(var1->cardsplayer1) / sizeof(var1->cardsplayer1[0]) - 1) {
        printf(", ");
    }
}

printf("]            |\t\t\t\t\t\t\t\t|   [");

// Imprimer les cartes du joueur 3
for (int i = 0; i < sizeof(var4->cardsplayer3) / sizeof(var4->cardsplayer3[0]); i++) {
    printf("%c", var4->cardsplayer3[i]);
    if (i < sizeof(var4->cardsplayer3) / sizeof(var4->cardsplayer3[0]) - 1) {
        printf(", ");
    }
}

printf("]                   |\n");
printf("\t\t|                                     |\t\t\t\t\t\t\t\t|                                     |\n");
printf("\t\t+-------------------------------------+\t\t\t\t\t\t\t\t+-------------------------------------+\n");


   printf("\t\t\t\t\t\t\t\t+-------------------------------------+\n");
printf("\t\t\t\t\t\t\t\t|                                     |\n");
printf("\t\t\t\t\t\t\t\t|              PLAYER 2               |\n");
printf("\t\t\t\t\t\t\t\t|    [");

// Imprimer les cartes du joueur 2
for (int i = 0; i < sizeof(var3->cardsplayer2) / sizeof(var3->cardsplayer2[0]); i++) {
    printf("%c", var3->cardsplayer2[i]);
    if (i < sizeof(var3->cardsplayer2) / sizeof(var3->cardsplayer2[0]) - 1) {
        printf(", ");
    }
}

printf("]                  |\n");
printf("\t\t\t\t\t\t\t\t|                                     |\n");
printf("\t\t\t\t\t\t\t\t+-------------------------------------+\n");

    
    char result_player1[30];
    char result_player2[30];
    char result_player3[30];


    check_total_point(total_point_player1, result_player1);
    check_total_point(total_point_player2, result_player2);
    check_total_point(total_point_player3, result_player3);

    printf("+-----------------------------------------------------------------------------------------------+\n");
    printf("|                                                                                               \n");
    printf("|                       BET AREA                                                                \n");
    printf("|          Dealer total point : %d                                                              \n", total_point_croupier);
    printf("|          Player 1 Bet: %d $ , total point : %s  ,   total money :    %d                       \n", bet_player_1, result_player1, money_player_1);  // Changer le montant du pari au besoin
    printf("|          Player 2 Bet: %d $ , total point : %s  ,   total money :    %d                       \n", bet_player_2, result_player2, money_player_2);
    printf("|          Player 3 Bet: %d $ , total point : %s  ,   total money :    %d                       \n", bet_player_3, result_player3, money_player_3);
    printf("|                                                                                                \n");
    printf("+-----------------------------------------------------------------------------------------------+\n");
}
int calculate_the_total_of_points(char cards[])
{
    int total = 0;
    int numAces = 0; // Pour gérer les As

    for (int i = 0; cards[i] != '\0' && cards[i] != '?'; i++)
    {
        switch (cards[i])
        {
        case 'A':
            numAces++;
            break;
        case 'K':
        case 'Q':
        case 'J':
        case 'T':
            total += 10;
            break;
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            total += (cards[i] - '0');
            break;
        default:
            // Ignorer les caractères inconnus
            break;
        }
    }

    // Ajouter les As en fonction du total actuel des points
    for (int i = 0; i < numAces; i++)
    {
        if (total + 11 <= 21)
        {
            total += 11;
        }
        else
        {
            total += 1;
        }
    }

    return total;
}


void hit_money_player1(struct player1 *var1)
{
    int choice;
    int hit = 0;
    int j = 0;
    printf("+-------------------------------------+\n");
    printf("|             Choice                  |\n");
    printf("|    1 - Hit money.                   |\n"); 
    printf("|    2 - Stand.                       |\n");
    printf("|    3 - Double down.                 |\n");
    printf("|    4 - Surrender.                   |\n");
    printf("+-------------------------------------+\n");

    
    while (j < 5)
    {
    
       printf("\nEnter your choice : \n");
       scanf("%d", &choice);
       shuffle();
       if(flag1 == 0 && pasturn1 == 0)
       {
         if (choice == 1 && calculate_the_total_of_points(var1->cardsplayer1) <=  21)
         {
                        // Trouver le premier emplacement vide dans le tableau du joueur 1
            int emptySlot = -1;
            for (int i = 0; i < sizeof(var1->cardsplayer1) / sizeof(var1->cardsplayer1[0]); i++)
            {
                if (var1->cardsplayer1[i] == '?')
                {
                    emptySlot = i;
                    break;
                }
            }

            // Ajouter une nouvelle carte au premier emplacement vide
            if (emptySlot != -1)
            {
  
                // Ajouter la carte au tableau du joueur 1
                var1->cardsplayer1[emptySlot] = pack_of_cards[26];

                 // Afficher le tableau après l'ajout de la carte
                printf("Updated cardsplayer1: ");
                printf("[");

                // Imprimer les cartes du joueur 1
                for (int i = 0; i < sizeof(var1->cardsplayer1) / sizeof(var1->cardsplayer1[0]); i++) {
                    printf("%c", var1->cardsplayer1[i]);
                    if (i < sizeof(var1->cardsplayer1) / sizeof(var1->cardsplayer1[0]) - 1) {
                    printf(", ");
                    }
                }

                printf("]\n");
                if(calculate_the_total_of_points(var1->cardsplayer1) > 21)
                {
                   total_point_player1 += calculate_the_total_of_points(var1->cardsplayer1);
                   break;
                }
                else if (calculate_the_total_of_points(var1->cardsplayer1) ==  21)
                {
                    printf("Black Jack!!");
                    flag1 = 1;
                    pasturn1 = 1;
                    total_point_player1 += calculate_the_total_of_points(var1->cardsplayer1);
                     money_player_1 += 2 * bet_player_1;
                    break;
                }

            }
            j++;

        }
        else if (choice == 2)
        {
            flag1 = 0;
            pasturn1 = 1;
            total_point_player1 += calculate_the_total_of_points(var1->cardsplayer1);
            break;
        }
        else if (choice == 3)
        {
            flag1 = 0;
            pasturn1 = 0;
            bet_player_1 = 2 * bet_player_1;
        }
        else if (choice == 4 || calculate_the_total_of_points(var1->cardsplayer1) > 21)
        {
          flag1 = 1; // le joueur 1 est out pour ce turn
          pasturn1 = 0;
          total_point_player1 += calculate_the_total_of_points(var1->cardsplayer1);
          break;
        }
       
        }
    }
}
void check_total_point(int n, char c[])
{

    if (n == 21)
    {
        strcpy(c, "Black jack");// mettre la valeur "black jack" dans le parametre char result ;
    }
    else if (n < 21)
    {
         // Convertit le nombre entier 'n' en une chaîne de caractères et stocke le résultat dans le tableau 'c'.
         sprintf(c, "%d", n);
    }
    else if(n > 21)
    {
        strcpy(c, "Bust");// mettre la valeur "black jack" dans le parametre char result ;

    }
}
void hit_money_player2(struct player2 *var3)
{
    int choice;
    int hit = 0;
    int j = 0;
    printf("+-------------------------------------+\n");
    printf("|             Choice                  |\n");
    printf("|    1 - Hit money.                   |\n"); 
    printf("|    2 - Stand.                       |\n");
    printf("|    3 - Double down.                 |\n");
    printf("|    4 - Surrender.                   |\n");
    printf("+-------------------------------------+\n");

    
    while (j < 5)
    {
    
       printf("\nEnter your choice : \n");
       scanf("%d", &choice);
       shuffle();
       if(flag2 == 0 && pasturn2 == 0)
       {
         if (choice == 1 && calculate_the_total_of_points(var3->cardsplayer2) <=  21)
         {
                        // Trouver le premier emplacement vide dans le tableau du joueur 1
            int emptySlot = -1;
            for (int i = 0; i < sizeof(var3->cardsplayer2) / sizeof(var3->cardsplayer2[0]); i++)
            {
                if (var3->cardsplayer2[i] == '?')
                {
                    emptySlot = i;
                    break;
                }
            }

            // Ajouter une nouvelle carte au premier emplacement vide
            if (emptySlot != -1)
            {
            
                // Ajouter la carte au tableau du joueur 1
                var3->cardsplayer2[emptySlot] = pack_of_cards[46];

                 // Afficher le tableau après l'ajout de la carte
                printf("Updated cardsplayer2: ");
                printf("[");

                // Imprimer les cartes du joueur 1
                for (int i = 0; i < sizeof(var3->cardsplayer2) / sizeof(var3->cardsplayer2[0]); i++) {
                    printf("%c", var3->cardsplayer2[i]);
                    if (i < sizeof(var3->cardsplayer2) / sizeof(var3->cardsplayer2[0]) - 1) {
                    printf(", ");
                    }
                }

                printf("]\n");
                if( calculate_the_total_of_points(var3->cardsplayer2) > 21)
                {
                   total_point_player2 += calculate_the_total_of_points(var3->cardsplayer2);
                   break;
                }
                else if (calculate_the_total_of_points(var3->cardsplayer2) ==  21)
                {
                    printf("Black Jack!!");
                    flag2 = 1;
                    pasturn2 = 1;
                    total_point_player2 += calculate_the_total_of_points(var3->cardsplayer2);
                     money_player_2 += 2 * bet_player_2;
                    break;
                }


            }
            j++;

        }
        else if (choice == 2)
        {
            flag2 = 0;
            pasturn2 = 1;
            total_point_player2 += calculate_the_total_of_points(var3->cardsplayer2);
            break;
        }
        else if (choice == 3)
        {

            flag2 = 0;
            pasturn2 = 0;
            bet_player_2 = 2 * bet_player_2;
        }
        else if (choice == 4 || calculate_the_total_of_points(var3->cardsplayer2) > 21)
        {
          flag2 = 1; // le joueur 1 est out pour ce turn
          pasturn2 = 0;
          total_point_player2 += calculate_the_total_of_points(var3->cardsplayer2);
          break;
        }
       
        }
    }
}
void hit_money_player3(struct player3 *var4)
{
    int choice;
    int hit = 0;
    int j = 0;
    printf("+-------------------------------------+\n");
    printf("|             Choice                  |\n");
    printf("|    1 - Hit money.                   |\n"); 
    printf("|    2 - Stand.                       |\n");
    printf("|    3 - Double down.                 |\n");
    printf("|    4 - Surrender.                   |\n");
    printf("+-------------------------------------+\n");

    
    while (j < 5)
    {
    
       printf("\nEnter your choice : \n");
       scanf("%d", &choice);
       shuffle();
       if(flag3 == 0 && pasturn3 == 0)
       {
         if (choice == 1 && calculate_the_total_of_points(var4->cardsplayer3) <=  21)
         {
                        // Trouver le premier emplacement vide dans le tableau du joueur 1
            int emptySlot = -1;
            for (int i = 0; i < sizeof(var4->cardsplayer3) / sizeof(var4->cardsplayer3[0]); i++)
            {
                if (var4->cardsplayer3[i] == '?')
                {
                    emptySlot = i;
                    break;
                }
            }

            // Ajouter une nouvelle carte au premier emplacement vide
            if (emptySlot != -1)
            {
        
                // Ajouter la carte au tableau du joueur 1
                var4->cardsplayer3[emptySlot] = pack_of_cards[39];


                 // Afficher le tableau après l'ajout de la carte
                printf("Updated cardsplayer3: ");
                printf("[");
                // Imprimer les cartes du joueur 1
                for (int i = 0; i < sizeof(var4->cardsplayer3) / sizeof(var4->cardsplayer3[0]); i++) {
                    printf("%c", var4->cardsplayer3[i]);
                    if (i < sizeof(var4->cardsplayer3) / sizeof(var4->cardsplayer3[0]) - 1) {
                    printf(", ");
                    }
                }

                printf("]\n");
                if( calculate_the_total_of_points(var4->cardsplayer3) > 21)
                {
                   total_point_player3 += calculate_the_total_of_points(var4->cardsplayer3);
                   break;
                }
                else if (calculate_the_total_of_points(var4->cardsplayer3) ==  21)
                {
                    printf("Black Jack!!");
                    flag3 = 1;
                    pasturn3 = 1;
                    total_point_player3 += calculate_the_total_of_points(var4->cardsplayer3);
                    money_player_3 += 2 * bet_player_3;
                    break;
                }

            }
            j++;

        }
        else if (choice == 2)
        {
            flag3 = 0;
            pasturn3 = 1;
            total_point_player3 += calculate_the_total_of_points(var4->cardsplayer3);
            break;
        }
        else if (choice == 3)
        {
            flag3 = 0;
            pasturn3 = 0;
            bet_player_3 = 2 * bet_player_3;
        }
        else if (choice == 4 || calculate_the_total_of_points(var4->cardsplayer3) > 21)
        {
          flag3 = 1; // le joueur 1 est out pour ce turn
          pasturn3 = 0;
          total_point_player3 += calculate_the_total_of_points(var4->cardsplayer3);
          break;
        }
       
        }
    }
}
void show_table_hit() {
    int c = 0;

    printf("\t\t\t\t\t\t\t\t+-------------------------------------+\n");
    printf("\t\t\t\t\t\t\t\t|            BLACKJACK TABLE          |\n");
    printf("\t\t\t\t\t\t\t\t+-------------------------------------+\n\n\n\n\n\n");

    while (c < 3) {
        int bet;
        printf("Hello Player %d, how much do you want to bet for this game: ", c + 1);

        while (1) {
            // la condition va verfier si il a bien rentre un integer dans le parametre bet si ou il verifie si il positive ou pas si ou il va a la condition else et lui demande de mettre un nombre positive
            if (scanf("%d", &bet) == 1) {
                if (bet > 0) {
                    break; // Valid input donc il sort de la loop pour aller le mettre dans le bon bet_player
                } else {
                    printf("Please enter a positive integer greater than 0: ");
                }
            } else {
                // si se n'est pas un integer il va faire un while jusque que le utilisateur va rentrer un integer
                while (getchar() != '\n');
                printf("Invalid input. Please enter a positive integer: ");
            }
        }

        printf("\n");

        // Assign the bet value to the appropriate player variable
        switch (c) {
            case 0:
                bet_player_1 = bet;
                break;
            case 1:
                bet_player_2 = bet;
                break;
            case 2:
                bet_player_3 = bet;
                break;
        }

        c++;
    }
}
int determin_winner()
{

   if(total_point_croupier > 21)
      bust_croupier = 1;
   if(total_point_player1 > 21)
      money_player_1 -= bet_player_1;
   else if ((total_point_croupier > total_point_player1 && bust_croupier == 0) || flag1 == 1)
      money_player_1 -= bet_player_1;
   else if(total_point_player1 > total_point_croupier  && bust_croupier == 0 && flag1 == 0)
      money_player_1 += 2 * bet_player_1;
   if(total_point_player2 > 21)
      money_player_2 -= bet_player_2; 
   else if (total_point_player2 > total_point_croupier && bust_croupier == 0 && flag2 == 0)
      money_player_2 += 2 * bet_player_2;
   else if ((total_point_croupier > total_point_player2 && bust_croupier == 0) || flag2 == 1)
      money_player_2 -= bet_player_2;
   if(total_point_player3 > 21)
      money_player_3 -= bet_player_3;
   else if((total_point_croupier > total_point_player3 && bust_croupier == 0) || flag3 == 1)
      money_player_3 -= bet_player_3;
   else if(total_point_player3 > total_point_croupier && bust_croupier == 0 && flag3 == 0)
      money_player_3 += 2 * bet_player_3;     

       
}



