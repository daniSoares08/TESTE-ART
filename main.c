#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "telemetria.h"

int main(void)
{
    const char *nome = "Daniel Soares";
    uint8_t nome_len = (uint8_t)strlen(nome);

    size_t size_req = sizeof(Relatorio) + nome_len;
    Relatorio *r = malloc(size_req);
    if (!r)
        return 1;

    /* campos fixos */
    r->temperatura = 85;
    r->flagBits = B_VALVULA_ABERTA | B_REFRIG_OK;
    r->estado_motor = MOTOR_FRENTE;
    r->latitude_e6 = -23456789;
    r->longitude_e6 = -46789012;
    r->altitude_cm = 87250;
    r->qtd_vagoes = 12;
    r->id_maquinista = 42;

    /* campo nome */
    r->nome_len = nome_len;
    /* memcpy copia os dados de r pro novo bloco  */
    /* memcpy(destino, origem, n) copia exatamente n bytes de origem para destino */
    memcpy(r->nome, nome, nome_len);

    /* serializar e desserializar para teste */
    void *payload = serializar_relato(r);
    free(r);
    if (!payload)
        return 2;

    Relatorio *r2 = NULL;
    desserializar_relato(payload, &r2);
    free(payload);
    if (!r2)
        return 3;

    /* exibe resultado */
    printf("Nome           : %.*s\n", (*r2).nome_len, r2->nome);
    printf("Temperatura    : %d graus C\n", r2->temperatura);
    printf("Valvula aberta : %s\n", is_valvula_aberta(r2) ? "SIM" : "NAO");
    printf("Qtd vagoes     : %d\n", r2->qtd_vagoes);
    printf("ID maquinista  : %d\n", r2->id_maquinista);

    free(r2);
    return 0;
}
