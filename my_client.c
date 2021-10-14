#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

void readVector(int *vector, int n, int id)     //Συνάρτηση για διάβαζμα του διανύσματος από τον χρήστη
{
    for (int i = 0; i < n; i++)
    {
        printf("Please give the %d element of vector %c: \n", i+1, id);
        scanf("%d", &vector[i]);
    }
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n, option, done;
    float r;
    int *vector_a, *vector_b;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    float *new_vector;
    float avg[2];
    int dotprod;
    float mag;

    if (argc < 3)       //Έλεγχος σωστής εκτέλεσης
    {
        fprintf(stderr,"Usage %s <hostname> <port>\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);       //Δημιουργία socket
    if (sockfd < 0)
        error("ERROR opening socket\n");
    
    server = gethostbyname(argv[1]);        //Αναζήτηση ύπαρξης socket server
    if (server == NULL)
    {
        fprintf(stderr,"ERROR, host %s not found!\n", argv[1]);
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    printf("Trying to connect...\n");

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)     //Σύνδεση στο socket server
        error("ERROR connecting\n");
    
    printf("Connected.\n");

    done = 0;

    do
    {
        printf("Please choose an option: \n");
        printf("1: Magnitude of Vector X\n");
        printf("2: Dot Product of Vectors X and Y\n");
        printf("3: Averages of Vectors X and Y\n");
        printf("4: Product of r*(X+Y)\n");
        printf("5: EXIT\n");
        scanf("%d", &option);       //Επιλογή χρήστη

        send(sockfd, &option, sizeof(int), 0);      //Αποστολή επιλογής

        switch (option)
        {
        case 1:     //Λογική του μέτρου διανύσματος
            printf("\nGive the size of the vectors: \n");
            scanf("%d", &n);

            vector_a = malloc(sizeof(int) * n);
            readVector(vector_a, n, 88);

            send(sockfd, &n, sizeof(int), 0);
            send(sockfd, vector_a, (sizeof(int)*n), 0);

            recv(sockfd, &mag, sizeof(float), 0);

            printf("The magnitude of vector X is %f\n\n", mag);

            free(vector_a);
            break;
        
        case 2:     //Λογική εσωτερικού γινομένου διανυσμάτων
            printf("\nGive the size of the vectors: \n");
            scanf("%d", &n);

            vector_a = malloc(sizeof(int) * n);
            vector_b = malloc(sizeof(int) * n);
            readVector(vector_a, n, 88);
            readVector(vector_b, n, 89);

            send(sockfd, &n, sizeof(int), 0);
            send(sockfd, vector_a, (sizeof(int)*n), 0);
            send(sockfd, vector_b, (sizeof(int)*n), 0);

            recv(sockfd, &dotprod, sizeof(int), 0);

            printf("The dot product of vectors X and Y is %d\n\n", dotprod);

            free(vector_a);
            free(vector_b);
            break;

        case 3:     //Λογική της μέσης τιμής των διανυσμάτων
            printf("\nGive the size of the vectors: \n");
            scanf("%d", &n);

            vector_a = malloc(sizeof(int) * n);
            vector_b = malloc(sizeof(int) * n);
            readVector(vector_a, n, 88);
            readVector(vector_b, n, 89);

            send(sockfd, &n, sizeof(int), 0);
            send(sockfd, vector_a, (sizeof(int)*n), 0);
            send(sockfd, vector_b, (sizeof(int)*n), 0);

            recv(sockfd, avg, (sizeof(float) * 2), 0);

            printf("The average of vector X is %f and of vector Y is %f\n\n", avg[0], avg[1]);

            free(vector_a);
            free(vector_b);
            break;

        case 4:     //Λογική της δημιουργίας καινούργιου διανύσματος
            printf("\nGive the size of the vectors: \n");
            scanf("%d", &n);

            vector_a = malloc(sizeof(int) * n);
            vector_b = malloc(sizeof(int) * n);
            readVector(vector_a, n, 88);
            readVector(vector_b, n, 89);

            printf("Give the value of r: \n");
            scanf("%f", &r);

            send(sockfd, &n, sizeof(int), 0);
            send(sockfd, vector_a, (sizeof(int)*n), 0);
            send(sockfd, vector_b, (sizeof(int)*n), 0);
            send(sockfd, &r, sizeof(float), 0);

            new_vector = malloc(sizeof(float) * n);

            recv(sockfd, new_vector, (sizeof(float) * n), 0);

            for (int i = 0; i < n; i++)
                printf("The %d element of the new vector Z is %f\n", i+1, new_vector[i]);

            printf("\n");

            free(vector_a);
            free(vector_b);
            free(new_vector);
            break;
        
        default:
            done = 1;
            break;
        }

    } while (!done);

    close(sockfd);      //Τερματισμός socket

    return 0;
}