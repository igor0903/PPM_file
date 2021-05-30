#include<stdio.h>
#include <stdlib.h>// pro malloc
#include<math.h>
#include<string.h>

typedef struct rgb RGB;
typedef struct MetaData METADATA;

struct rgb {   // gerenciar os valores de RED, GREEN, BLUE em cada pixell
    unsigned int r;
    unsigned int g;
    unsigned int b;
};

struct MetaData {   //colher os metadados da imagem 
    char magic_number;  
    unsigned int width;//colunas
    unsigned int height;//linhas
    unsigned int max_value;
    RGB** matriz_de_pixels;//matriz tipo cor
};

void imprimir_prompt(METADATA metadata){
        printf("%s\n", &metadata.magic_number);
        printf("%d %d\n", metadata.width, metadata.height);
        printf("%d\n", metadata.max_value);
        for(int a = 0; a < metadata.height; a++){
            //printf("%d eh o a agr\n",a);
            for(int c = 0; c < metadata.width; c++){
                //printf("%d eh o c agr\n",c);
                printf("%d %d %d\n",metadata.matriz_de_pixels[a][c].r, metadata.matriz_de_pixels[a][c].g, metadata.matriz_de_pixels[a][c].b);
        }
    } 
}

int main(int argc, char* argv[]){
    FILE *pf; 
    FILE *pf2;
    METADATA metadata;

    if(argc == 1){
        //usando scanf vc so vai conseguir fazer leitura com entrada <input
        scanf("%s", &metadata.magic_number); // MAGIC NUMBER
        scanf("%d %d", &metadata.width, &metadata.height); //LARGURA E ALTURA
        scanf("%d", &metadata.max_value);

        metadata.matriz_de_pixels = (RGB **) malloc(metadata.height * sizeof(RGB *));
    
        for(int i=0; i< metadata.height; i++){
            (metadata.matriz_de_pixels[i] = (RGB *) malloc(metadata.width * sizeof(RGB)));
        }

        for(int i = 0; i < (metadata.height); i++){ //so avança altura quando a linha toda ja foi preenchida
            for(int j = metadata.width; j > 0; j--){ // avanço da linha
                scanf("%d %d %d", &metadata.matriz_de_pixels[i][j-1].r, &metadata.matriz_de_pixels[i][j-1].g, &metadata.matriz_de_pixels[i][j-1].b); // inverter a linha, mas mantem as colunas em sequencia de leitura
            }
        }
        imprimir_prompt(metadata);
        free(metadata.matriz_de_pixels);
    }

    if(argc == 2){
        pf = fopen(argv[1],"r");

        if(pf == NULL){
            printf("Unable to open the file\n");
        }
        else{
            fscanf(pf, "%s", &metadata.magic_number);
            fscanf(pf, "%d %d\n", &metadata.width, &metadata.height);
            fscanf(pf, "%d\n", &metadata.max_value);

            metadata.matriz_de_pixels = (RGB **) malloc(metadata.height * sizeof(RGB *));
    
            for(int i=0; i< metadata.height; i++){
                (metadata.matriz_de_pixels[i] = (RGB *) malloc(metadata.width * sizeof(RGB)));
            }

            for(int i = 0; i < (metadata.height); i++){ //so avança altura quando a linha toda ja foi preenchida
                for(int j = metadata.width; j > 0; j--){ // avanço da linha
                    fscanf(pf,"%d %d %d\n", &metadata.matriz_de_pixels[i][j-1].r, &metadata.matriz_de_pixels[i][j-1].g, &metadata.matriz_de_pixels[i][j-1].b); // inverter a linha, mas mantem as colunas em sequencia de leitura
                }
            }
        }
        fclose(pf);
        imprimir_prompt(metadata);
        free(metadata.matriz_de_pixels);
    }

    if(argc == 3){
        pf = fopen(argv[1],"r");

        if(pf == NULL){
            printf("Unable to open the file\n");
        }
        else{
            fscanf(pf, "%s", &metadata.magic_number);
            fscanf(pf, "%d %d\n", &metadata.width, &metadata.height);
            fscanf(pf, "%d\n", &metadata.max_value);

            metadata.matriz_de_pixels = (RGB **) malloc(metadata.height * sizeof(RGB *));
    
            for(int i=0; i< metadata.height; i++){
                (metadata.matriz_de_pixels[i] = (RGB *) malloc(metadata.width * sizeof(RGB)));
            }

            for(int i = 0; i < (metadata.height); i++){ //so avança altura quando a linha toda ja foi preenchida
                for(int j = metadata.width; j > 0; j--){ // avanço da linha

                    fscanf(pf,"%u %u %u\n", &metadata.matriz_de_pixels[i][j-1].r, &metadata.matriz_de_pixels[i][j-1].g, &metadata.matriz_de_pixels[i][j-1].b); // inverter a linha, mas mantem as colunas em sequencia de leitura
                }
            }
            fclose(pf);
        
            pf2 = fopen(argv[2],"w"); 

            if(pf2 == NULL){
                printf("Unable to write the file\n");
            }
            else{
                fprintf(pf2, "%s\n", &metadata.magic_number);
                fprintf(pf2, "%u %u\n", metadata.width, metadata.height);
                fprintf(pf2, "%d\n", metadata.max_value);

                for(int a = 0; a < metadata.height; a++){  
                    for(int c = 0; c < metadata.width; c++){
                        fprintf(pf2, "%u %u %u\n",metadata.matriz_de_pixels[a][c].r, metadata.matriz_de_pixels[a][c].g, metadata.matriz_de_pixels[a][c].b);
                    }
                }
            fclose(pf2);
            }
        }
        free(metadata.matriz_de_pixels);
    }
}
