#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// =================================================================================================================
// Definições e variáveis globais
// =================================================================================================================
    typedef unsigned char bool; //Definição do tipo de variável booleana
    #define false 0
    #define true !false
  //Variáveis usadas no tópico 1 do trabalho
    char user [50];
    char password [50];

    char loginUser [50];
    char loginPassword [50];
    int controlUser;
    int controlPassword;

  //Variáel usada no tópico 2, 3 e 4 do trabalho
    int items;

    FILE *itens;




void clear_terminal() //Função que realiza a limpeza do terminal, de acordo com o sistema operacional, na execução de cada aba do programa
{
    #ifdef __linux__
      system("clear");
    #else
      system("cls");
    #endif
}
void clear_buffer() //Função para que o caracter gerado pela tecla enter não atrapalhe o funcionamento da função "clique_continuar"
{
    getchar();
}
void press_to_continue() //Função que realiza a instrução de ordenamento e transição entre as funcionalidades do programa
{   
    printf("\n\nPress ENTER to continue... ");
    fflush(NULL);
    getchar();
}


//----------------------------------------------------------------------------------------------------------------

// =================================================================================================================
// Tópico 1
// =================================================================================================================
/* void user_registration() //Função responsável pela exibição e funcionamento da aba de cadastramento do usuário
{
    clear_terminal();
    printf("======================================\nADD USER\n======================================\n\n");
  //Mostrando exemplos dos dados a ser cadastrados
    printf("Username: usuario\n");
    printf("Password: senha\n\n");
  //Cadastrando os dados
    printf("-> username: ");
    scanf("%s", user); //Recebe o cadastramento do usuário
    printf("-> password: ");
    scanf("%s", password); //Recebe o cadastramento da senha do usuário
    clear_buffer();
    press_to_continue();
    clear_terminal();
}
void login() //Função responsável pela exibição e funcionamento da aba de login
{
    do //Aba de login execultará no mínimo uma vez e enquanto o usuário e a senha cadastrados forem diferentes dos fornecidos no login
    {
      printf("\n\n======================================\nLogin\n======================================\n\n"); 
      printf("Enter your username: ");
      scanf("%s", loginUser); //Insere o usuário cadastrado
      printf("Enter your password: ");
      scanf("%s", loginPassword); //Insere a senha cadastrada
      controlUser = strcmp(user, loginUser); //Compara as duas strings (usuario e loginUsuario) atribuindo valor 0 quando elas são iguais, valor menor que 0 se o primeiro parâmetro for menor que o segundo e valor maior que zero se o primeiro parâmetro for maior que o segundo
      controlPassword = strcmp(password, loginPassword);
      if(controlUser != 0 || controlPassword != 0)
      {
        printf("\n-> Login failed (incorrect username or password)!\n");
        clear_buffer();
        press_to_continue();
        clear_terminal();
      }
    }while(controlUser != 0 || controlPassword != 0);
    printf("\n-> Login successful\n"); //Confirma que os dados inseridos estão corretos
    clear_buffer();
    press_to_continue();
    clear_terminal();
}
 */


// =================================================================================================================
// Itens
// =================================================================================================================
void quantity_items() //Função responsável por exibir e escanear a quantidade de itens a serem cadastrados
{
    printf("======================================\nADD ITEMS\n======================================\n\n");
    printf("How many items would you like to insert? "); //Pede ao usuário a quantidade de itens que serão cadastrados
    scanf("%d", &items);
    clear_terminal();
}
//-----------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------
typedef struct _no//Permite que, ao armazenar os dados de uma mesma entidade, isto possa ser feito com uma única variável com o intuito de melhorar o gerenciamento de informações
{
    int code;
    char name [50];
    float price;
    bool available;

    struct _no *next; //Cada item tem um ponteiro apontando para o item seguinte
}Item;
//-----------------------------------------------------------------------------------------------------------------

void PassaListaParaArquivo (Item *lista, FILE *p) {
    Item *auxiliar;
    p = fopen("itens.txt", "a");
    if (p != NULL) {
        for (auxiliar = lista; auxiliar != NULL; auxiliar = lista->next) {
            fprintf(p, "%d*%s*%f%hhd", &lista->code, lista->name, &lista->price, &lista->available);
    
        }

    } else {
        printf("Erro ao abrir arquivo");
    }
}

//-----------------------------------------------------------------------------------------------------------------
void insertItemAtTheAndOfTheList(Item **list, int code, char name[50], float price, bool available) //procedimento para inserir os itens no final de uma lista
{ 
    Item *newItem = (Item *) malloc(sizeof(Item)); //Alocação que retorna o ponteiro tipo Item
    Item *aux; //Ponteiro auxiliar para percorrer a lista

    if(newItem)//verificar se a memória foi alocada corretamente
    {
        newItem->code = code;
        strcpy(newItem->name, name);
        newItem->price = price;
        newItem->available = available;

        newItem->next = NULL;

        //eh o primeiro? Verifica se a lista está vazia
        if(*list == NULL) //Se a lista está vazia o conteudo da lista vai ser o novo item cadastrado
            *list = newItem; 
        else //Se a lista não está vazia
        {
            aux = *list;
            while (aux->next) //Percorre a lista enquanto próximo for diferente de null
            {
              aux = aux->next;
            }
            aux->next = newItem; //Quando o próximo for null, aux->next vai receber o novo item
        }
    }
    else //Verifica se teve erra de alocação de memória
    {
        printf("**Error allocating memory!**\n");
    }
}
//-----------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------
void printItems(Item *item) //Função para printar a lista completa de itens
{
    if(item == NULL) //Verifica se a lista está vazia
    {
        printf("\n-> Add a new item first!\n");
        return;
    }
    printf("======================================\nINSERTED ITEMS\n======================================\n\n");
    while (item!=NULL)
    {   
        printf("%d | %s | $%.2f | %s\n",item->code,item->name,item->price,item->available ? "available" : "NOT available"); //Estrutura que mostra: número, código, nome, preço e disponibilidade dos item.
        item = item->next; //Percorre a lista
    }

}
//-----------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------
void printItem(int code, char name[50], float price, bool available) //Função para printar os dados individuais de cada item
{
    printf("\t-> Item code: %d\n",code);
    printf("\t-> Item name: %s\n",name);
    printf("\t-> Item price: %.2f\n",price);
    printf("\t-> Item availability: %d\n",available);
}
//-----------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------
void itemsRegistration(Item **list) //Função responsável pela exibição e funcionamento da aba de cadastro de itens com 4 tipos diferentes de dados
{ 
    int c = 0;
    //Gravando as informações dos itens inseridos pelo usuário
    int code;
    char name[50];
    float price = 0;
    bool available;

    for(int q = 0;q<items;q++) //A estrutura for serve para realizar um looping da informação entre chaves a seguir
    {
        printf("\n====================================\nADD ITEMS %d/%d\n====================================\n\n",++c, items);
        printf("+ Enter the item code: "); //Entrada e saída de dados do tipo inteiro
        scanf("%d", &code); //Recebe o código do produto
        getchar(); //É usado entre o scanf e fgets para que o computador não entenda a linha de comando como entrada vazia

        printf("+ Enter the item name: ");
        scanf("%[^\n]", name);
        getchar();

        printf("+ Enter the item price: ");//Dados de entrada e saída do tipo decimal
        scanf("%f", &price);
        getchar();

        printf("+ Is the item available? (1=yes/0=no): "); //Dados do tipo booleano aceita apenas dois valores falso=0 verdadeiro!=0
        scanf("%hhd", &available);

        insertItemAtTheAndOfTheList(list, code, name, price, available); //Adicionar o item na lista
        printf("\n");
        printItem(code,name,price,available); //Printar os dados do item cadastrado

        clear_buffer();
        press_to_continue();
        clear_terminal();
    }
    /*PassaListaParaArquivo(*list, itens);*/
}
//-----------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------
void editItems(Item **list) // Função responsável pela edição de uma item de acordo com o código informado pelo usuário
{
    int option;

    if (*list == NULL) //Verifica se a lista está vazia
    {
        printf("-> Add a new item first!\n");
        return;
    }

    int code;
    printf("======================================\nEDIT ITEMS\n======================================\n\n");
    printf("Item code: "); //Escaneia o código do item a ser editado de acordo com a inserção do usuário
    scanf("%d", &code);

    Item *aux = *list;
    bool found = false;

    while (aux != NULL) //Procura pelo código informado pelo usuário até que chegue ao final da lista
    {
        if (aux->code == code) //Identifica se o item apontado pelo ponteiro apresenta o mesmo código informado pelo usuário
        {
            found = true;

            printf("\n");
            printItem(aux->code, aux->name, aux->price, aux->available); //Exibindo os dados antigos dos itens
            printf("\n");
            
            printf("(1) Name\t(2) Price\t(3) Availability\t(4) All Information\t(0) Back\n\nChoose an option: ");
            scanf("%d", &option);
            printf("\n");
            // Editando os dados do item encontrado
            switch (option)
            {
              case 0:
                return;
                break;

              case 1: //Editar somente o nome do item
                printf("+ Enter the new item name: ");
                getchar(); // Limpa o buffer do teclado
                scanf("%[^\n]", aux->name);
                printf("\n-> Item edited successfully!\n");
                getchar();
                break;
              
              case 2: //Editar somente o valor do item
                printf("+ Enter the new item price: ");
                scanf("%f", &(aux->price));
                printf("\n-> Item edited successfully!\n");
                getchar();
                break;
              
              case 3: //Editar somente a disponibilidade do item
                printf("+ Is the item available? (1=yes/0=no): ");
                scanf("%hhd", &(aux->available));
                printf("\n-> Item edited successfully!\n");
                getchar();
                break;

              case 4: //Editar todas as informações do item, exeto o código
                printf("+ Enter the new item name: ");
                getchar(); // Limpa o buffer do teclado
                scanf("%[^\n]", aux->name);

                printf("+ Enter the new item price: ");
                scanf("%f", &(aux->price));

                printf("+ Is the item available? (1=yes/0=no): ");
                scanf("%hhd", &(aux->available));

                printf("\n-> Item edited successfully!\n");
                getchar();
                break;

              default:
                printf("**Invalid option**");
                break;
            }

        }
        aux = aux->next; //Se o item verificado não apresentar o mesmo código informado pelo usuário, o ponteiro vai para o prŕoximo item
    }

    if (found==false) //Verificação se existe um item com esse código
    {
        printf("\n-> Item with code %d not found.\n", code);
        getchar();
        return;
    }
}
//----------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------
void searchItem (Item **list) //Função responsável pela busca de um item de acordo com código do item
{
    Item *aux;
    bool found = false;

    aux = *list;

    int code;

    if (*list == NULL) //Verifica se a lista está vazia
    {
        printf("-> Add a new item first!\n");
        return;
    }

    printf("======================================\nSEARCH ITEMS\n======================================\n\n");
    printf("Item code: ");
    scanf("%d", &code); //Escaneia o código do item a ser procurado de acordo com a inserção do usuário
    printf("\n");

    while(aux!=NULL) //Verifica se existe um item, isto é, se e lista é diferente de null e se o code é diferente do code inserido pelo usuário
    {
        if(aux->code == code)
        {
            found = true;
            printf("\tItem data: \n");
            printItem(aux->code, aux->name, aux->price, aux->available); //Exibir dados do item
            getchar();
            break;
        }
        aux = aux->next; //Caminha pela lista, se esse elemento não existir em algum momento chegará em null (que é conndição de parada do while)
    }
    if (!found) //Verificação se existe um item com esse código
    {
        printf("-> Item with code %d not found.\n", code);
        getchar();
        return;
    }
    
}
//----------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------
void removeItem(Item **list) //Função responsável pela remoção de um item da lista
{
    Item *removing = NULL;
    Item *aux;

    bool option;
    bool found = false;

    int code;

    if (*list == NULL) //Verifica se a lista está vazia
    {
        printf("-> Add a new item first!\n");
        return;
    }

    printf("======================================\nREMOVE ITEMS\n======================================\n\n");
    printf("Item code: ");
    scanf("%d", &code); //Escaneia o código do item a ser removido de acordo com a inserção do usuário
    printf("\n");

    if(*list!=NULL)
    {
        //Remoção do primeiro nó da lista
        if((*list)->code==code) //Se o código do primeiro item for igual ao inserido pelo usuário, remove-se o primeiro item
        {
            found=true;

            removing = *list; //Conteúdo a ser removido
            *list = removing->next; //O primeiro nó da lista passa a ser o próximo depois de remover

            printf("Item that will be removed: \n"); //Printa os dados do item que será removido
            printItem(removing->code, removing->name, removing->price, removing->available);

            printf("\nConfirm? (1 = Yes / 0 = No): "); //Pede a confirmação do usuário para remover o item
            scanf("%hhd", &option);
            if(option==true)
            {
                free(removing); //Libera o espaço de memória
                printf("\n-> Item removed successfully!\n");
                getchar();
            }
            else
            {
                printf("\n-> Operation cancelled!\n");
                //Retaura a lista se a operação for cancelada
                removing->next = *list;
                *list = removing;
                getchar();
            }

        }
        else //Se não for o primeiro nó a ser removido, temos que percorrer a lista
        {
            aux = *list;
            while (aux->next!=NULL && aux->next->code!=code)
            {
                aux = aux->next; //Percorre a lista
            }
            if((aux->next)!=NULL)
            {
                found = true;

                removing = aux->next; //O proximo item tem codigo igual ao requerido pelo usuário, cria um ponteiro para o nó que se quer remover
                aux->next = removing->next; //Ponteiro que aponta para o proximo depois de aux->next, mantém a lista ligada

                printf("Item that will be removed: ");
                printItem(removing->code, removing->name, removing->price, removing->available); //Printa os dados do item que será removido

                printf("\nConfirm? (1 = Yes / 0 = No): "); //Pede a confirmação do usuário para remover o item
                scanf("%hhd", &option);
                if(option==true)
                {
                    free(removing); //Libera o espaço de memória
                    printf("\n-> Item removed successfully!\n");
                    getchar();
                }
                else
                {
                    printf("\n-> Operation cancelled!");
                    //Restaura a lista se a operação for cancelada
                    aux->next = removing;
                    getchar();
                }
            }
        }
    }
    if (!found) //Verificação se existe um item com esse código
    {
        printf("-> Item with code %d not found.\n", code);
        getchar();
        return;
    }
}
//----------------------------------------------------------------------------------------------------------------


// =================================================================================================================
// MENU
// =================================================================================================================
void itemsMenu(Item **list) //Função responsável pela exibição do menu de configurações dos items
{   
    
    int option;

    do
    {
        clear_terminal(); 
        printf("===========================================================================================\n\t\t\t\t\tITEMS MENU\n===========================================================================================\n");
        printf("1. Add items\n");
        printf("2. Edit items\n");
        printf("3. Search items\n");
        printf("4. List items\n");
        printf("5. Delete items\n");
        printf("0. Back");
        printf("\n\nChoose an option: ");
        scanf("%d",&option);
        clear_buffer();

        switch (option)
        {
          case 0: //Caso para retornar para o menu principal
            return;
            break;
          case 1: //Caso para adicionar um novo item
            clear_terminal();
            quantity_items();
            itemsRegistration(list);
            break;
          case 2: //Caso para editar um item
            clear_terminal();
            editItems(list);
            press_to_continue();
            //clear_terminal();
            break;
          case 3: //Caso para pesquisar um item
            clear_terminal();
            searchItem(list);
            press_to_continue();
            break;
          case 4: //Caso para imprimir a lista de itens
            clear_terminal();
            printItems(*list);
            press_to_continue();
            break;
          case 5: //Caso para deletar um item
            clear_terminal();
            removeItem(list);
            press_to_continue();
            break;
          default:
            printf("\n**Invalid option. Please try again!**\n");
            press_to_continue();
            break;
        }
  }while (option!=0);
}
//----------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------
void mainMenu() //Função responsável pela exibição do menu principal do programa
{
    int option;
    Item *list = NULL;
    do //Ocorre a repetição do menu até que opção para fechar o programa seja ativada
    {
        clear_terminal();
        printf("===========================================================================================\n\t\t\t\t\tMAIN MENU\n===========================================================================================\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Edit Profiles\n");
        printf("4. Items\n");
        printf("0. Exit\n");

        printf("\nChoose an option: ");
        scanf("%d",&option);
        clear_buffer();

        switch (option)
        {
          case 0: //Encerra o programa
            exit(1);
            break;
          case 1:
            
            break;
          case 2:
            
            break;
          case 3:
            
            break;
          case 4: //Acessa o menu de configurações de itens
            //if() -> Fazer a verificação se o usuário está logado para poder configurar itens
            itemsMenu(&list);
            break;
          default:
            printf("\n**Invalid option. Please, try again!**\n");
            press_to_continue();
            clear_terminal();
            break;
        }
    }while (option!=0);
}
//----------------------------------------------------------------------------------------------------------------


// =================================================================================================================
// MAIN
// =================================================================================================================
void main()
{
    mainMenu();
}
