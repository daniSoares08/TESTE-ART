#ifndef TELEMETRIA_H
#define TELEMETRIA_H

#include <stdint.h>
#include <string.h> 

/* bit masks para campo flagBits */
#define B_VALVULA_ABERTA 0x01
#define B_REFRIG_OK 0x02
#define B_LUZES_ACESAS 0x04

/* estado do motor */
typedef enum
{
    MOTOR_PARADO = 0,
    MOTOR_FRENTE,
    MOTOR_REVERSO
} EstadoMotor;

/*
 * Relatorio de telemetria com array flexivel para nome:
 *  - nome_len: numero de bytes validos em nome[]
 *  - nome[]:    conteudo do nome (nao inclui terminador '\\0')
 */
typedef struct
{
    int16_t temperatura; /* graus C inteiros (-30 a 350) */
    uint8_t flagBits; /* bits de estado */
    uint8_t estado_motor; /* EstadoMotor  */

    /* elevamos lat, long a sexta potência e dividimos metro pra cm pra não usar float*/
    int32_t latitude_e6;
    int32_t longitude_e6;
    int32_t altitude_cm;

    /* Considerando 255 o máximo de vagões*/
    uint8_t qtd_vagoes;
    uint16_t id_maquinista; /* 0 à 999 */

    uint8_t nome_len; /* comprimento do nome em bytes */
    char nome[];  /* nome sem '\\0' */
} Relatorio;

/* macro e função inline para bit de válvula */
static inline void set_valvula_aberta(Relatorio *r, int on)
{
    if (on)
        r->flagBits |= B_VALVULA_ABERTA;
    else
        r->flagBits &= ~B_VALVULA_ABERTA;
}

static inline int is_valvula_aberta(const Relatorio *r)
{
    return (r->flagBits & B_VALVULA_ABERTA) != 0;
}

/* protótipos de serialização */
void *serializar_relato(const Relatorio *src);
/* devolve buffer alocado com payload pronto e tamanho total = sizeof(Relatorio)+nome_len */
void desserializar_relato(const void *buf, Relatorio **out);

#endif /* TELEMETRIA_H */
