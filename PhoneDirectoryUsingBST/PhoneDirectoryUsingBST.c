#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct nodetype {
    char ad[20];
    char telefon[20];
    struct nodetype* left;
    struct nodetype* right;
};
typedef struct nodetype* NODEPTR;

NODEPTR getnode(void) {
    NODEPTR p;
    p = (NODEPTR)malloc(sizeof(struct nodetype));
    return p;
}

NODEPTR Yarat(char ad[20], char telefon[20]) {
    NODEPTR p;
    p = getnode();
    strcpy(p->ad, ad);
    strcpy(p->telefon, telefon);
    p->right = NULL;
    p->left = NULL;
    return p;
}

int BSTgiris(NODEPTR* agac, char ad[20], char telefon[20]) {
    NODEPTR q, p, v;
    q = NULL;
    p = *agac;

    while (p != NULL) {
        if (strcmp(ad, p->ad) == 0)
            return 1;  // Ayni sayi zaten agaçta mevcuttur.
        q = p;
        if (strcmp(ad, p->ad) < 0)
            p = p->left;
        else
            p = p->right;
    }
    v = Yarat(ad, telefon);


    if (q == NULL)
        *agac = v;
    else {
        if (strcmp(ad, q->ad) < 0)
            q->left = v;
        else
            q->right = v;
    }
    return 2;  // Yeni sayi yaprak dügüm olarak basarili bir sekilde girilmistir.
}

void inordertraversal(NODEPTR agac) {
    if (agac != NULL) {
        inordertraversal(agac->left);
        printf("%s - %s\n", agac->ad, agac->telefon);
        inordertraversal(agac->right);
    }
}
void reverseInorderTraversal(NODEPTR agac) {
    if (agac != NULL) {
        reverseInorderTraversal(agac->right);  // Önce sa? alt a?ac? dola?
        printf("%s - %s\n", agac->ad, agac->telefon);             // Kökü yazd?r
        reverseInorderTraversal(agac->left);   // Sonra sol alt a?ac? dola?
    }
}

NODEPTR search(NODEPTR agac, char ad[20]) {
    if (agac == NULL || strcmp(agac->ad, ad) == 0)
        return agac;  // A?aç bo?sa veya aranan de?eri bulduysak

    if (strcmp(ad, agac->ad) < 0)
        return search(agac->left, ad);  // Sol alt a?ac? tara
    else
        return search(agac->right, ad); // Sa? alt a?ac? tara
}


void menu() {
    printf("\n");
    printf("***********************************************************\n");
    printf("*     	             Telefon Rehberi                      *\n");
    printf("*       Lutfen yapmak istedigin islemi asagidan seciniz.  *\n");
    printf("***********************************************************\n");
    printf("*  1. Yeni Arkadas Ekle                                   *\n");
    printf("*  2. Telefon numarasi ara                                *\n");
    printf("*  3. Tum arkadaslarin adini ve telefon numarasini listele*\n");
    printf("*  (ada gore kucukten buyuge sirali olarak)               *\n");
    printf("*  4. Tum arkadaslarin adini ve telefon numarasini listele*\n");
    printf("*  (ada gore buyukten kucuge sirali olarak)               *\n");
    printf("*  5. Cikis                                               *\n");
    printf("***********************************************************\n");
    printf("Seciminiz nedir: ");

}
void freeTree(NODEPTR agac) {
    if (agac != NULL) {
        freeTree(agac->left);
        freeTree(agac->right);
        free(agac);
    }
}

int main() {
    NODEPTR agac = NULL;

    char ad[20];
    int secim;

    do {
        menu();
        scanf("%d", &secim);

        if (secim == 1) {
            printf("Adi girin: ");
            scanf("%s", ad);
            printf("Telefon numarasini girin: ");
            char telefon[20];
            scanf("%s", telefon);
            int sonuc = BSTgiris(&agac, ad, telefon);
            if (sonuc == 1)
                printf("Bu isim zaten rehberde var!\n");
            else
                printf("Rehbere eklendi.\n");
        }
        else if (secim == 2) {
            printf("\nAranacak adi girin: ");
            scanf("%s", ad);
            NODEPTR bulunan = search(agac, ad);
            if (bulunan != NULL)
                printf("Bulunan: %s - %s\n", bulunan->ad, bulunan->telefon);
            else
                printf("Kayit bulunamadi.\n");

        }
        else if (secim == 3) {
            inordertraversal(agac);
        }
        else if (secim == 4) {
            reverseInorderTraversal(agac);
        }
        else if (secim == 5) {
            printf("Ç?k?? Yap?l?yor...\n");
            freeTree(agac);

        }
        else {
            printf("Yanlis secim yaptiniz...\n Yeniden deneyiniz.");
        }

    } while (secim != 5);
    return 0;



}