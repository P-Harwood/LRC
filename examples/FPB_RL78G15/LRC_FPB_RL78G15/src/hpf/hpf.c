/*
 * Trap_integrator.c
 *
 *  Created on: 22 Oct 2025
 *      Author: a5126135
 */

#include <hpf.h>

int16_t Hpf_run(Hpf *p_hpf, int16_t input)
{
    if (!p_hpf->run_already)
    {
        p_hpf->run_already = true;
        p_hpf->prev_input      = input;
        p_hpf->state = 0L;
    }
    else
    {
        /* 253/256 = 0.98828125 coefficient in Q8 format*/
        p_hpf->state *= 253;
        p_hpf->state += (input - p_hpf->prev_input) << 8;
        p_hpf->state >>= 8;

        p_hpf->prev_input = input;
    }

    return p_hpf->state;
}

void Hpf_reset(Hpf *p_hpf)
{
    p_hpf->prev_input = 0L;
    p_hpf->state = 0L;
    p_hpf->run_already = false;
}
